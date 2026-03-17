from fused_dot_product import *


def mantissa_add_implicit_bit(x: Node) -> Primitive:
    int_bits = x.node_type.int_bits
    
    def spec_mantissa_add_implicit_bit(x, ctx):
        return (x * (ctx.real_val(2) ** (-ctx.real_val(int_bits)))) + ctx.real_val(1)

    @Primitive(name="mantissa_add_implicit_bit", spec=spec_mantissa_add_implicit_bit)
    def impl(x):
        return basic_concat(x=Const(UQ(1, 1, 0)), y=x, out=Const(UQ(0, 1, int_bits)))
        
    return impl(x)


@Primitive(name="sign_xor", spec=lambda x, y, ctx: x * y)
def sign_xor(x: Node, y: Node) -> Node:
    return basic_xor(x=x, y=y, out=Const(UQ(0, 1, 0)))
