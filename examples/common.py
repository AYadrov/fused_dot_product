from fused_dot_product import *
from cvc5.pythonic import FreshReal, Solver, If, Or, And

def mantissa_add_implicit_bit(x: Node) -> Primitive:
    int_bits = x.node_type.int_bits
    def spec(prim, mantissa, s):
        out = prim._spec_outputs(s)
        s.add(out == (mantissa / (2 ** int_bits)) + 1.0)
        return out
    
    def sign(mantissa: UQT) -> UQT:
        assert mantissa.frac_bits == 0
        return UQT(1, mantissa.int_bits)
    
    def impl(x: Node) -> Node:
        return basic_concat(
            x=Const(UQ(1, 1, 0)),  # 1.
            y=x,  # xxxxxxx.
            out=Const(UQ(0, 1, int_bits)),
        )
    
    return Primitive(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="mantissa_add_implicit_bit")


def sign_xor(x: Node, y: Node) -> Primitive:
    def spec(prim, x, y, s):
        out = prim._spec_outputs(s)
        s.add(out == If(Or(And(x==0, y==1), And(x==1, y==0)), 1, 0))
        return out
    
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
