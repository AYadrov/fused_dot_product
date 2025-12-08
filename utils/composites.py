from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.UQ import *


def mantissa_add_implicit_bit(x: Node) -> Composite:
    def spec(mantissa: float) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
    
    def sign(mantissa: UQT) -> UQT:
        assert mantissa.frac_bits == 0
        return UQT(1, mantissa.int_bits)
    
    def impl(x: Node) -> Node:
        return basic_concat(
            x=Const(UQ(1, 1, 0)),
            y=x,
            out=Const(UQ(0, 1, 7)),
        )
    
    return Composite(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="mantissa_add_implicit_bit")


def MAX_EXPONENT4(e0: Node, e1: Node, e2: Node, e3: Node) -> Composite:
    def spec(e0: float, e1: float, e2: float, e3: float) -> float:
        return max(max(e0, e1), max(e2, e3))
    
    def sign(e0: UQT, e1: UQT, e2: UQT, e3: UQT) -> UQT:
        int_bits = max(max(e0.int_bits, e1.int_bits), max(e2.int_bits, e3.int_bits))
        frac_bits = max(max(e0.frac_bits, e1.frac_bits), max(e2.frac_bits, e3.frac_bits))
        return UQT(int_bits, frac_bits)
    
    def impl(e0: Node, e1: Node, e2: Node, e3: Node) -> Node:
        return uq_max(uq_max(e0, e1), uq_max(e2, e3))
    
    return Composite(spec=spec,
                     impl=impl,
                     sign=sign,
                     args=[e0, e1, e2, e3],
                     name="MAX_EXPONENT4")

def ADDER_TREE4(x0: Node, x1: Node, x2: Node, x3: Node) -> Composite:
    def spec(x0: float, x1: float, x2: float, x3: float) -> float:
        return (x0 + x1) + (x2 + x3)
    
    def sign(x0: QT, x1: QT, x2: QT, x3: QT) -> QT:
        frac_bits = max(max(x0.frac_bits, x1.frac_bits), max(x2.frac_bits, x3.frac_bits))
        int_bits = max(max(x0.int_bits, x1.int_bits), max(x2.int_bits, x3.int_bits)) + 2
        return QT(int_bits, frac_bits)
    
    def impl(x0: Node, x1: Node, x2: Node, x3: Node) -> Node:
        res1 = q_add(x0, x1)
        res2 = q_add(x2, x3)
        return q_add(res1, res2)
    
    return Composite(spec=spec,
                     impl=impl,
                     sign=sign,
                     args=[x0, x1, x2, x3],
                     name="ADDER_TREE4")

 
