from fused_dot_product import *
from .common import *
from .encode_Float32 import *
import random
import struct

import numpy as np

Wf = 30


@Primitive(
    name="fp32_select",
    spec=lambda sel, in0, in1, ctx: (ctx.real_val(1) - sel) * in0 + sel * in1,
)
def fp32_select(sel: Node, in0: Node, in1: Node) -> Node:
    in0_s, in0_e, in0_m = fp32_unpack(in0)
    in1_s, in1_e, in1_m = fp32_unpack(in1)
    out_s = basic_mux_2_1(
        sel=sel,
        in0=in0_s,
        in1=in1_s,
        out=Const(UQ(0, 1, 0)),
    )
    out_e = basic_mux_2_1(
        sel=sel,
        in0=in0_e,
        in1=in1_e,
        out=Const(UQ(0, Float32.exponent_bits, 0)),
    )
    out_m = basic_mux_2_1(
        sel=sel,
        in0=in0_m,
        in1=in1_m,
        out=Const(UQ(0, Float32.mantissa_bits, 0)),
    )
    return fp32_pack(out_s, out_e, out_m)


@Composite(name="FP32_IEEE_adder", spec=lambda x, y, ctx: x + y)
def FP32_IEEE_adder(x: Node, y: Node) -> Node:
    x_is_nan = fp32_is_nan(x) 
    y_is_nan = fp32_is_nan(y)
    
    x_s, x_e, x_m = fp32_unpack(x)
    y_s, y_e, y_m = fp32_unpack(y)

    max_exp = uq_max(x_e, y_e)
    x_shift_amount = uq_sub(max_exp, x_e)
    y_shift_amount = uq_sub(max_exp, y_e)

    x_m_implicit = add_implicit_bit(x_m)
    y_m_implicit = add_implicit_bit(y_m)

    # Make some room for right shift
    x_m_resized = uq_resize(x_m_implicit, 1, Wf-1)
    y_m_resized = uq_resize(y_m_implicit, 1, Wf-1)

    x_m_shifted = uq_rshift(x_m_resized, x_shift_amount)
    y_m_shifted = uq_rshift(y_m_resized, y_shift_amount)

    x_m_q = uq_to_q(x_m_shifted)
    y_m_q = uq_to_q(y_m_shifted)

    x_m_signed = q_add_sign(x_m_q, x_s)
    y_m_signed = q_add_sign(y_m_q, y_s)

    m_sum = q_add(x_m_signed, y_m_signed)

    encoded_float = encode_Float32(m_sum, uq_to_q(max_exp))

    out = fp32_select(y_is_nan, encoded_float, y)
    out = fp32_select(x_is_nan, out, x)

    return out


if __name__ == '__main__':
    from pprint import pprint
    adder = FP32_IEEE_adder(
        Var(name="a", sign=Float32T()),
        Var(name="b", sign=Float32T()),
    )
    pprint(adder.check_spec())
    with open("examples/adder.cpp", "w") as file:
        file.write(adder.to_cpp())
    
