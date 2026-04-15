from fused_dot_product import *
from .common import *
from .encode_Float32 import *
import random
import struct

import numpy as np


# TODO: NaN payload
@Composite(name="FP32_IEEE_adder", spec=lambda x, y, ctx: x + y)
def FP32_IEEE_adder(x: Node, y: Node) -> Node:
    x_norm, x_sub, x_zero, x_inf, x_nan = fp32_classify(x)
    y_norm, y_sub, y_zero, y_inf, y_nan = fp32_classify(y)
    
    x_s, x_e, x_m = fp32_unpack(x)
    y_s, y_e, y_m = fp32_unpack(y)
    
    # Nan encoding
    infs_diff_signs = bit_and(bit_and(x_inf, y_inf), bit_xor(x_s, y_s))
    any_is_nan = bit_or(x_nan, y_nan)
    encode_nan = bit_or(infs_diff_signs, any_is_nan)
    
    # Inf encoding
    encode_inf = bit_and(bit_neg(encode_nan), bit_or(x_inf, y_inf))
    
    # Signed zero encoding
    both_negative_zeros = bit_and(bit_and(x_zero, y_zero), bit_and(x_s, y_s))
    
    with context() as ctx:
        # Spec does not have nan/inf yet
        ctx.check(ctx.spec_of(encode_inf).eq(ctx.real_val(0)))
        ctx.check(ctx.spec_of(encode_nan).eq(ctx.real_val(0)))
    
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
    
    with context() as ctx:
        # This check basically makes sure that if statement was useless
        #   since on spec level we pretend that we do not have subnormals
        ctx.check(ctx.spec_of(x_m_formatted).eq(ctx.spec_of(x_m_fraction) + ctx.real_val(1)))
        ctx.check(ctx.spec_of(y_m_formatted).eq(ctx.spec_of(y_m_fraction) + ctx.real_val(1)))
    
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
    
    # Signed zero case
    sign_bit = if_then_else(both_negative_zeros, Const(UQ(1, 1, 0)), sign_bit)
    
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
    with open("examples/adder.hpp", "w") as file:
        file.write(adder.to_cpp())
