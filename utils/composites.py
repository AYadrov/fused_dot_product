from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Int import *
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.UQ import *


def mantissa_add_implicit_bit(x: Node) -> Composite:
    def sign(x: float) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
    
    def sign(mantissa: IntT) -> UQT:
        assert mantissa.frac_bits == 0
        return UQT(1, mantissa.int_bits)
    
    n = Const(UQ(7, 3, 0))  # 7
    x = uq_resize(x, n, n)  # xxxxxxx.0000000
    x = UQ_Rshift(x, n)  # 0000000.xxxxxxx
    x = uq_resize(x, Const(UQ(1, 1, 0)), n)  # 0.xxxxxxx
    one = Const(UQ(1, 1, 0))  # 1.0000000
    x = UQ_Or(x, one)  # 1.xxxxxxx
    return x

def BF16_mantissa_to_UQ(mantissa: Node) -> Composite:
    def spec(mantissa: int) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
    
    def sign(mantissa: IntT) -> UQT:
        return UQT(1, 7)
    
    mantissa_ = Or(mantissa, Lshift(Const(Int(1)), Const(Int(BFloat16.mantissa_bits), "BF16_MANTISSA_BITS")))
    impl = Int_to_UQ(mantissa_, Const(Int(1)), Const(Int(BFloat16.mantissa_bits), "BF16_MANTISSA_BITS"))
    
    return Composite(spec=spec,
                     impl=impl,
                     sign=sign,
                     args=[mantissa],
                     name="BF16_mantissa_to_UQ")

def MAX_EXPONENT4(e0: Node, e1: Node, e2: Node, e3: Node) -> Composite:
    """
    Computes the maximum exponent value among four inputs using pairwise comparison.
    
    Args:
        e0: First exponent value.
        e1: Second exponent value.
        e2: Third exponent value.
        e3: Fourth exponent value.
    
    Returns:
        The maximum value among e0, e1, e2, and e3.
    """
    def spec(e0: float, e1: float, e2: float, e3: float) -> float:
        return max(max(e0, e1), max(e2, e3))
    
    def sign(e0: UQT, e1: UQT, e2: UQT, e3: UQT) -> UQT:
        int_bits = max(max(e0.int_bits, e1.int_bits), max(e2.int_bits, e3.int_bits))
        frac_bits = max(max(e0.frac_bits, e1.frac_bits), max(e2.frac_bits, e3.frac_bits))
        return UQT(int_bits, frac_bits)
    
    impl = UQ_Max(UQ_Max(e0, e1), UQ_Max(e2, e3))
    
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
    
    res1 = Q_Add(x0, x1)
    res2 = Q_Add(x2, x3)
    impl = Q_Add(res1, res2)
    
    return Composite(spec=spec, 
                     impl=impl,
                     sign=sign, 
                     args=[x0, x1, x2, x3], 
                     name="ADDER_TREE4")

# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
def CSA_ADDER_TREE4(m0: Node, m1: Node, m2: Node, m3: Node) -> Composite:
    """
    Performs a four-operand addition using a carry-save adder (CSA) tree structure.
    
    Args:
        m0: First two's complement operand.
        m1: Second two's complement operand.
        m2: Third two's complement operand.
        m3: Fourth two's complement operand.
    
    Returns:
        Composite producing the sum of the four operands using a two-level CSA tree.
        Output has {bit_width + 3} bit width.
    """
    def spec(m0: float, m1: float, m2: float, m3: float) -> float:
        return m0 + m1 + m2 + m3
    
    def sign(m0: QT, m1: QT, m2: QT, m3: QT) -> QT:
        frac_bits = max(max(m0.frac_bits, m1.frac_bits), max(m2.frac_bits, m3.frac_bits))
        int_bits = max(max(m0.int_bits, m1.int_bits), max(m2.int_bits, m3.int_bits)) + 3
        return QT(int_bits, frac_bits)
    
    def CSA(a, b, c):
        sum_  = Q_Xor(Q_Xor(a, b), c)
        carry = Q_Or(Q_Or(Q_And(a, b), Q_And(a, c)), Q_And(b, c))
        return  sum_, Q_Lshift(carry, Const(Int(1)))
    
    s1, c1 = CSA(m0, m1, m2)
    s2, c2 = CSA(m3, s1, c1)
    impl = Q_Add(s2, c2)
    
    return Composite(spec=spec,
                     impl=impl,
                     sign=sign,
                     args=[m0, m1, m2, m3],
                     name="CSA_ADDER_TREE4")
 
