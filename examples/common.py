from fused_dot_product import *


def add_implicit_bit(x: Node) -> Primitive:
    int_bits = x.node_type.int_bits
    
    def spec(x, ctx):
        return (x * (ctx.real_val(2) ** (-ctx.real_val(int_bits)))) + ctx.real_val(1)

    @Primitive(name="add_implicit_bit", spec=spec)
    def impl(x):
        return basic_concat(x=Const(UQ(1, 1, 0)), y=x, out=Const(UQ(0, 1, int_bits)))
        
    return impl(x)

# Expects UQ<1, ...> as an input, returns UQ<0, ...>
def drop_implicit_bit(x: Node) -> Primitive:
    frac_bits = x.node_type.frac_bits
    
    def spec(x, ctx):
        return x - ctx.real_val(1)

    @Primitive(name="drop_implicit_bit", spec=spec)
    def impl(x: Node):
        return uq_select(x, frac_bits - 1, 0)
    return impl(x)

@Primitive(name="sign_xor", spec=lambda x, y, ctx: x * y)
def sign_xor(x: Node, y: Node) -> Node:
    return basic_xor(x=x, y=y, out=Const(UQ(0, 1, 0)))
