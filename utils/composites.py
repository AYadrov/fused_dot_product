from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Int import *
from fused_dot_product.numtypes.Q import *

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
    def spec(e0: int, e1: int, e2: int, e3: int) -> int:
        return max(max(e0, e1), max(e2, e3))
    
    def sign(e0: IntT, e1: IntT, e2: IntT, e3: IntT) -> IntT:
        return IntT(max(max(e0.total_bits, e1.total_bits), max(e2.total_bits, e3.total_bits)))
    
    impl = Max(Max(e0, e1), Max(e2, e3))
    
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
 
