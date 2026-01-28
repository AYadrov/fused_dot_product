from fused_dot_product import *

def mantissa_add_implicit_bit(x: Node) -> Primitive:
    int_bits = x.node_type.int_bits
    def spec(mantissa: float, out: float):
        return (float(mantissa) / (2 ** int_bits)) + 1.0 == out
    
    def sign(mantissa: UQT) -> UQT:
        assert mantissa.frac_bits == 0
        return UQT(1, mantissa.int_bits)
    
    def impl(x: Node) -> Node:
        return basic_concat(
            x=Const(UQ(1, 1, 0)),  # 1.
            y=x,  # xxxxxxx.
            out=Const(UQ(0, 1, int_bits)),
        )
    
    return Composite(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="mantissa_add_implicit_bit")


def sign_xor(x: Node, y: Node) -> Primitive:
    def spec(x: float, y: float, out: float):
        return (0.0 if x == y else 1.0) == out
    
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

