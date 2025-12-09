from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.UQ import *


def mantissa_add_implicit_bit(x: Node) -> Primitive:
    def spec(mantissa: float) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
    
    def sign(mantissa: UQT) -> UQT:
        assert mantissa.frac_bits == 0
        return UQT(1, mantissa.int_bits)
    
    def impl(x: Node) -> Node:
        return basic_concat(
            x=Const(UQ(1, 1, 0)),  # 1.
            y=x,  # xxxxxxx.
            out=Const(UQ(0, 1, 7)),
        )
    
    return Composite(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="mantissa_add_implicit_bit")


def sign_xor(x: Node, y: Node) -> Primitive:
    def spec(x, y):
        return 0.0 if x == y else 1.0
    
    def sign(x: UQT, y: UQT) -> UQT:
        return UQT(1, 0)
    
    def impl(x: UQ, y: UQ) -> UQ:
        return basic_xor(
            x=x,
            y=y,
            out=Const(UQ(0, 1, 0)),  # 0.
        )
    
    return Primitive(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x, y],
        name="sign_xor")

