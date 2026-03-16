from fused_dot_product import *

def implic_spec(mantissa, ctx):
    int_bits = mantissa.int_bits
    return (mantissa * (ctx.real_val(2) ** (-ctx.real_val(int_bits)))) + ctx.real_val(1)

@Primitive(name="mantissa_add_implicit_bit", spec=implic_spec)
def mantissa_add_implicit_bit(x: Node) -> Node:
    int_bits = x.node_type.int_bits
    return basic_concat(x=Const(UQ(1, 1, 0)), y=x, out=Const(UQ(0, 1, int_bits)))

def sign_xor_spec(x, y, ctx):
    return x * y

@Primivite(name="sign_xor", spec=sign_xor_spec)
def sign_xor(x: Node, y: Node) -> Primitive:
    assert x.node_type.total_bits() == 1 and y.node_type.total_bits() == 1
    return basic_xor(x=x, y=y, out=Const(UQ(0, 1, 0)))
