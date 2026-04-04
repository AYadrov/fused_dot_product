from ..types.runtime import RuntimeType, Tuple
from ..types.static import StaticType, TupleT
from .node import Node
from .nodes import Op, Primitive


@Primitive(name="Copy", spec=lambda x, ctx: x, c_inline=True)
def Copy(x: Node) -> Node:
    return x


def basic_get_item(x: Node, idx: int) -> Op:
    if idx >= len(x.node_type.args) or idx < 0:
        raise IndexError(f"Index is out of range for tuple {str(x)}, given {str(idx)}")
    
    def sign(x: TupleT) -> StaticType:
        return x.args[idx]
    
    def op(x: Tuple) -> RuntimeType:
        return x.args[idx]
    
    return Op(
        impl=op,
        sign=sign,
        c_lowering=lambda lowered_args: f"std::get<{idx}>({lowered_args[0]})",
        args=[x],
        name=f"basic_get_item_{idx}",
    )

def Tuple_get_item(x: Node, idx: int) -> Primitive:
    @Primitive(name=f"Tuple_get_item_{idx}", spec=lambda x, ctx: x[idx], c_inline=True)
    def impl(x: Node) -> Node:
        return basic_get_item(x, idx)
    
    return impl(x)
