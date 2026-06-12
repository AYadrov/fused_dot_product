from fused_dot_product import *
from .common import *
from .encode_Float32 import *


_FP32_INPUT_CLASS_CASES = {
    "norm": (1, 0, 0, 0, 0),
    "sub": (0, 1, 0, 0, 0),
    "zero": (0, 0, 1, 0, 0),
    "inf": (0, 0, 0, 1, 0),
    "nan": (0, 0, 0, 0, 1),
}


_FP32_OUTPUT_CLASS_CASES = {
    "norm": (1, 0, 0, 0, 0),
    "sub": (0, 1, 0, 0, 0),
    "zero": (0, 0, 1, 0, 0),
    "inf": (0, 0, 0, 1, 0),
    "nan": (0, 0, 0, 0, 1),
}


def _fp32_flags(spec_value):
    if len(spec_value) == 9:
        return spec_value[4:9]
    if len(spec_value) == 6:
        return spec_value[1:6]
    raise ValueError(
        f"Expected a 6- or 9-field Float32 spec tuple, got {len(spec_value)} fields"
    )


def _assume_fp32_case(spec_value, class_bits, ctx):
    flags = _fp32_flags(spec_value)
    for flag, bit in zip(flags, class_bits):
        ctx.assume(flag.eq(ctx.real_val(bit)))


def _append_fp32_case_name(name, case_label):
    if name.endswith("]") and "[" in name:
        return f"{name[:-1]},{case_label}]"
    return f"{name}[{case_label}]"


def _split_fp32_output_cases(ctx, spec_inner, spec_outer):
    split_ctxs = []
    for inner_out_label, inner_out_case in _FP32_OUTPUT_CLASS_CASES.items():
        for outer_out_label, outer_out_case in _FP32_OUTPUT_CLASS_CASES.items():
            case_ctx = ctx.copy()
            case_ctx.name = _append_fp32_case_name(
                ctx.name,
                f"inner_out={inner_out_label},outer_out={outer_out_label}",
            )
            _assume_fp32_case(spec_inner, inner_out_case, case_ctx)
            _assume_fp32_case(spec_outer, outer_out_case, case_ctx)
            split_ctxs.append(case_ctx)
    return split_ctxs


def _split_fp32_input_cases(ctx, inputs, spec_inner, spec_outer):
    if len(inputs) != 2:
        return [ctx]
    
    split_ctxs = []
    for x_label, x_case in _FP32_INPUT_CLASS_CASES.items():
        for y_label, y_case in _FP32_INPUT_CLASS_CASES.items():
            case_ctx = ctx.copy()
            case_ctx.name = f"{ctx.name}[x={x_label},y={y_label}]"
            _assume_fp32_case(inputs[0], x_case, case_ctx)
            _assume_fp32_case(inputs[1], y_case, case_ctx)
            split_ctxs.extend(_split_fp32_output_cases(case_ctx, spec_inner, spec_outer))
    return split_ctxs


# TODO: NaN payload
def spec(x, y, ctx):
    x_val, x_sign, x_exp, x_man, x_norm, x_sub, x_zero, x_inf, x_nan = x
    y_val, y_sign, y_exp, y_man, y_norm, y_sub, y_zero, y_inf, y_nan = y
    
    zero = ctx.real_val(0)
    
    # IEEE invalid: +inf + -inf
    invalid_inf_sum = (
        x_inf.eq(ctx.real_val(1))
        & y_inf.eq(ctx.real_val(1))
        & x_sign.ne(y_sign)
    )
    
    res_nan_b = x_nan.eq(ctx.real_val(1)) | y_nan.eq(ctx.real_val(1)) | invalid_inf_sum
    res_inf_b = (~res_nan_b) & (x_inf.eq(ctx.real_val(1)) | y_inf.eq(ctx.real_val(1)))
    
    _sum = x_val + y_val
    
    return ctx.encode_fp32(
        value=_sum,
        encode_inf=If(res_inf_b, ctx.real_val(1), ctx.real_val(0)),
        encode_nan=If(res_nan_b, ctx.real_val(1), ctx.real_val(0)),
    ).as_tuple()


@Composite(name="FP32_IEEE_adder", spec=spec, case_splitter=_split_fp32_input_cases)
def FP32_IEEE_adder(x: Node, y: Node) -> Node:
    x_s, x_e, x_m, x_norm, x_sub, x_zero, x_inf, x_nan = fp32_decode(x)
    y_s, y_e, y_m, y_norm, y_sub, y_zero, y_inf, y_nan = fp32_decode(y)
    
    # Nan encoding
    infs_diff_signs = bit_and(bit_and(x_inf, y_inf), bit_xor(x_s, y_s))
    any_is_nan = bit_or(x_nan, y_nan)
    encode_nan = bit_or(infs_diff_signs, any_is_nan)
    
    # Inf encoding
    encode_inf = bit_and(bit_neg(encode_nan), bit_or(x_inf, y_inf))
    
    # Signed zero encoding
    both_negative_zeros = bit_and(bit_and(x_zero, y_zero), bit_and(x_s, y_s))
    
    # UQ<23, 0> -> UQ<0, 23>
    x_m_fraction = integer_to_fraction(x_m)
    y_m_fraction = integer_to_fraction(y_m)
    
    # UQ<1, 23>
    x_m_formatted = if_then_else(x_norm, add_implicit_bit(x_m_fraction), uq_resize(x_m_fraction, 1, Float32.mantissa_bits))
    y_m_formatted = if_then_else(y_norm, add_implicit_bit(y_m_fraction), uq_resize(y_m_fraction, 1, Float32.mantissa_bits))
    
    # Subnormals have exponent field 0 but effective exponent 1-bias.
    effective_subnormal_e = Const(UQ(1, x_e.node_type.int_bits, x_e.node_type.frac_bits))
    x_effective_e = if_then_else(x_sub, effective_subnormal_e, x_e)
    y_effective_e = if_then_else(y_sub, effective_subnormal_e, y_e)
    
    max_exp = uq_max(x_effective_e, y_effective_e)
    x_shift_amount = uq_sub(max_exp, x_effective_e)
    y_shift_amount = uq_sub(max_exp, y_effective_e)
    
    # Make room for latter correct rounding
    x_m_resized = uq_resize(x_m_formatted, 1, Float32.mantissa_bits + 3)
    y_m_resized = uq_resize(y_m_formatted, 1, Float32.mantissa_bits + 3)
    
    x_m_shifted = uq_rshift_jam(x_m_resized, x_shift_amount)
    y_m_shifted = uq_rshift_jam(y_m_resized, y_shift_amount)
    
    x_m_signed = q_add_sign(uq_to_q(x_m_shifted), x_s)
    y_m_signed = q_add_sign(uq_to_q(y_m_shifted), y_s)
    
    m_sum = q_add(x_m_signed, y_m_signed)
    
    sign_bit = q_sign_bit(m_sum)
    inf_sign_bit = if_then_else(x_inf, x_s, y_s)
    
    # Signed zero case
    sign_bit = if_then_else(both_negative_zeros, Const(UQ(1, 1, 0)), sign_bit)
    sign_bit = if_then_else(encode_inf, inf_sign_bit, sign_bit)
    
    return fp32_encode(
        sign_bit,               # sign: UQ
        uq_to_q(max_exp),       # exponent: Q
        q_to_uq(q_abs(m_sum)),  # mantissa: UQ
        encode_nan,
        encode_inf,
    )


if __name__ == '__main__':
    from pprint import pprint
    adder = FP32_IEEE_adder(
        Var(name="a", sign=Float32T()),
        Var(name="b", sign=Float32T()),
    )
    #adder.check_spec()
    pprint(adder.check_spec())
    with open("examples/adder_jit.hpp", "w") as file:
        file.write(adder.to_cpp(jittable=True))
    
    with open("examples/adder_no_jit.hpp", "w") as file:
        file.write(adder.to_cpp(jittable=False))
