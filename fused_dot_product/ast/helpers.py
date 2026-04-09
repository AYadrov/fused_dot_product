from ..types.runtime import RuntimeType, Tuple
from ..types.static import StaticType, TupleT
from .node import Node
from .nodes import Op, Primitive


@Primitive(name="Copy", spec=lambda x, ctx: x, c_inline=True)
def Copy(x: Node) -> Node:
    return x


def _basic_get_item(x: Node, idx: int) -> Op:
    if idx >= len(x.node_type.args) or idx < 0:
        raise IndexError(f"Index is out of range for tuple {str(x)}, given {str(idx)}")
    
    def sign(x: TupleT) -> StaticType:
        return x.args[idx]
    
    def op(x: Tuple) -> RuntimeType:
        return x.args[idx]
    
    return Op(
        impl=op,
        sign=sign,
        c_lowering=lambda lowered_args: f"{lowered_args[0]}[{idx}]",
        args=[x],
        name=f"_basic_get_item_{idx}",
    )

def Tuple_get_item(x: Node, idx: int) -> Primitive:
    @Primitive(name=f"Tuple_get_item_{idx}", spec=lambda x, ctx: x[idx], c_inline=True)
    def impl(x: Node) -> Node:
        return _basic_get_item(x, idx)
    
    return impl(x)

@Primitive(name="if_then_else", spec=lambda sel, in1, in0, ctx: (ctx.real_val(1) - sel) * in0 + sel * in1)
def if_then_else(sel: Node, in1: Node, in0: Node) -> Node:
    from ..components.basics import basic_mux_2_1
    assert in1.node_type == in0.node_type, "Non-deterministic type"
    return basic_mux_2_1(sel=sel, in0=in0, in1=in1, out=in1.copy())
