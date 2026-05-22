from fused_dot_product import *
from .common import *
from .encode_Float32 import *

def helper(x, ctx):
    x_val, x_norm, x_sub, x_zero, x_inf, x_nan = x
    sign = ctx.fresh_real("sign")
    exponent = ctx.fresh_real("exponent")
    mantissa = ctx.fresh_real("mantissa")

    # zero = ctx.real_val(0)
    # one = ctx.real_val(1)
    # two = ctx.real_val(2)
    # minus_one = ctx.real_val(-1)
    # inf_code = ctx.real_val((1 << Float32.exponent_bits) - 1)
    # mantissa_limit = ctx.real_val(1 << Float32.mantissa_bits)
    # bias = ctx.real_val(Float32.exponent_bias)
    # sub_scale = two ** ctx.real_val(1 - Float32.exponent_bias - Float32.mantissa_bits)

    # is_norm = x_norm.eq(one)
    # is_sub = x_sub.eq(one)
    # is_zero = x_zero.eq(one)
    # is_inf = x_inf.eq(one)
    # is_nan = x_nan.eq(one)

    # ctx.assume(sign.eq(zero).or_(sign.eq(one)))
    # ctx.assume((exponent >= zero).and_(exponent < ctx.real_val(1 << Float32.exponent_bits)))
    # ctx.assume((mantissa >= zero).and_(mantissa < mantissa_limit))
    # ctx.assume((x_norm + x_sub + x_zero + x_inf + x_nan).eq(one))

    # normal_value = (minus_one ** sign) * (one + mantissa * two ** (-ctx.real_val(Float32.mantissa_bits))) * two ** (exponent - bias)
    # subnormal_value = (minus_one ** sign) * mantissa * sub_scale

    # ctx.assume(
    #     (~is_norm).or_(
    #         (exponent >= one)
    #         .and_(exponent < inf_code)
    #         .and_(x_val.eq(normal_value))
    #     )
    # )
    # ctx.assume(
    #     (~is_sub).or_(
    #         exponent.eq(zero)
    #         .and_(mantissa > zero)
    #         .and_(x_val.eq(subnormal_value))
    #     )
    # )
    # ctx.assume(
    #     (~is_zero).or_(
    #         exponent.eq(zero)
    #         .and_(mantissa.eq(zero))
    #         .and_(x_val.eq(zero))
    #     )
    # )
    # ctx.assume(
    #     (~is_inf).or_(
    #         exponent.eq(inf_code)
    #         .and_(mantissa.eq(zero))
    #         .and_(x_val.eq(zero))
    #     )
    # )
    # ctx.assume(
    #     (~is_nan).or_(
    #         exponent.eq(inf_code)
    #         .and_(mantissa > zero)
    #         .and_(x_val.eq(zero))
    #     )
    # )

    return sign, exponent, mantissa

# TODO: NaN payload
def spec(x, y, ctx):
    return x[0] + y[0], ctx.real_val(1), ctx.real_val(0), ctx.real_val(0), ctx.real_val(0), ctx.real_val(0)
 
    # zero = ctx.real_val(0)
    # one = ctx.real_val(1)
    # two = ctx.real_val(2)
    # minus_one = ctx.real_val(-1)
    # bias = ctx.real_val(Float32.exponent_bias)

    # # x argument
    # x_val, x_norm, x_sub, x_zero, x_inf, x_nan = x
    # x_sign, x_exponent, x_mantissa = helper(x, ctx)
    # x_normal_value = (minus_one ** x_sign) * (one + x_mantissa * two ** (-ctx.real_val(Float32.mantissa_bits))) * two ** (x_exponent - bias)
    # x_subnormal_value = (minus_one ** x_sign) * x_mantissa * two ** (-ctx.real_val(Float32.mantissa_bits)) * two ** (x_exponent - bias)
    # ctx.assume(x_val.eq(If(x_norm.eq(one), x_normal_value, x_subnormal_value)))

    # # y argument
    # y_val, y_norm, y_sub, y_zero, y_inf, y_nan = y
    # y_sign, y_exponent, y_mantissa = helper(y, ctx)
    # y_normal_value = (minus_one ** y_sign) * (one + y_mantissa * two ** (-ctx.real_val(Float32.mantissa_bits))) * two ** (y_exponent - bias)
    # y_subnormal_value = (minus_one ** y_sign) * y_mantissa * two ** (-ctx.real_val(Float32.mantissa_bits)) * two ** (y_exponent - bias)
    # ctx.assume(y_val.eq(If(y_norm.eq(one), y_normal_value, y_subnormal_value)))

    # r_val, r_norm, r_sub, r_zero, r_inf, r_nan = ctx.fresh_real("r_val"), ctx.fresh_real("r_norm"), ctx.fresh_real("r_sub"), ctx.fresh_real("r_zero"), ctx.fresh_real("r_inf"), ctx.fresh_real("r_nan")
    
    


    
    # sum_val = x_val + y_val
    # abs_sum_val = abs(sum_val)
    
    # invalid_inf_sum = x_inf.eq(one).and_(y_inf.eq(one)).and_(x_sign.ne(y_sign))
    # res_nan_b = x_nan.eq(one).or_(y_nan.eq(one)).or_(invalid_inf_sum)
    # finite_overflow = (~res_nan_b).and_(~x_inf.eq(one)).and_(~y_inf.eq(one)).and_(abs_sum_val > max_finite)
    # res_inf_b = ((x_inf.eq(one).or_(y_inf.eq(one))).and_(~res_nan_b)).or_(finite_overflow)
    # res_zero_b = (~res_nan_b).and_(~res_inf_b).and_(sum_val.eq(zero))
    # res_sub_b = (~res_nan_b).and_(~res_inf_b).and_(~res_zero_b).and_(abs_sum_val < min_normal)
    # res_norm_b = (~res_nan_b).and_(~res_inf_b).and_(~res_zero_b).and_(~res_sub_b)
    
    # res_val = If(res_nan_b.or_(res_inf_b), zero, sum_val)
    
    # return (
    #     res_val,
    #     If(res_norm_b, one, zero),
    #     If(res_sub_b, one, zero),
    #     If(res_zero_b, one, zero),
    #     If(res_inf_b, one, zero),
    #     If(res_nan_b, one, zero),
    # )


@Composite(name="FP32_IEEE_adder", spec=spec)
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
    pprint(adder.check_spec())
    with open("examples/adder_jit.hpp", "w") as file:
        file.write(adder.to_cpp(jittable=True))
    
    with open("examples/adder_no_jit.hpp", "w") as file:
        file.write(adder.to_cpp(jittable=False))
