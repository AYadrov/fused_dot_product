from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.numtypes.numtypes import *
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
    
    impl = Max(Max(e0, e1), Max(e2, e3))
    
    return Composite(spec, impl, [e0, e1, e2, e3], "MAX_EXPONENT4")
    
def ADDER_TREE4(x0: Node, x1: Node, x2: Node, x3: Node) -> Composite:
    def spec(x0: float, x1: float, x2: float, x3: float) -> float:
        return (x0 + x1) + (x2 + x3)
    
    res1 = Q_Add(x0, x1)
    res2 = Q_Add(x2, x3)
    impl = Q_Add(res1, res2)
    
    return Composite(spec, impl, [x0, x1, x2, x3], "ADDER_TREE4")
    
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
    
    def CSA(a, b, c):
        sum_  = Q_Xor(Q_Xor(a, b), c)
        carry = Q_Or(Q_Or(Q_And(a, b), Q_And(a, c)), Q_And(b, c))
        return  sum_, Q_Lshift(carry, Const(Int(1)))
    
    s1, c1 = CSA(m0, m1, m2)
    s2, c2 = CSA(m3, s1, c1)
    impl = Q_Add(s2, c2)
    
    return Composite(spec, impl, [m0, m1, m2, m3], "CSA_ADDER_TREE4")

def take_last_n_bits(x: Node, n: Node) -> Composite:
    """
    Extracts the least significant n bits from an integer value.

    Args:
        x: Input integer value.
        n: Number of least significant bits to extract.

    Returns:
        Composite producing x & ((1 << n) - 1),
        effectively masking all but the lowest n bits.
    """
    spec = lambda x, n: x % (2 ** n)
    impl = And(x, (Sub(Lshift(Const(Int(1)), n), Const(Int(1)))))
    
    return Composite(spec, impl, [x, n], "take_last_n_bits")
    
def invert_bits(x: Node, s: Node) -> Composite:
    """
    Inverts (negates) the lowest s bits of an integer.

    Args:
        x: Input integer value.
        s: Number of bits to invert, greater than log2(x).

    Returns:
        Composite producing (2^s - 1) - x,
        effectively flipping all bits.
    
    Example:
        invert_bits(3, 2) -> 0   # 0b11 -> 0b00
        invert_bits(0, 2) -> 3   # 0b00 -> 0b11
    """
    spec = lambda x, s: (2**s - 1) - x
    impl = Sub(Sub(Lshift(Const(Int(1)), s), Const(Int(1))), x)
    
    return Composite(spec, impl, [x, s], "invert_bits")
    
 
if __name__ == '__main__':
    import inspect
    import sys
    
    def get_local_functions():
        current_module = sys.modules[__name__]
        funcs = inspect.getmembers(current_module, inspect.isfunction)

        local_funcs = [
            (name, func)
            for name, func in funcs
            if func.__module__ == current_module.__name__
        ]
        
        return local_funcs
    
        
    local_functions = get_local_functions()
    for name, func in local_functions:
        if name == "get_local_functions":
            continue
        sig = inspect.signature(func)
        composite_inputs = [Var(name) for name, _ in sig.parameters.items()]
        print(f"{name} -> {sig}")
        func(*composite_inputs).print_tree(depth=1)
        print("\n")

 
