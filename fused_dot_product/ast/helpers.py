from ..types.runtime import RuntimeType, Tuple
from ..types.static import StaticType, TupleT
from .node import Node
from .nodes import Op, Primitive


@Primitive(name="Copy", spec=lambda x, ctx: x)
def Copy(x: Node) -> Node:
    return x


def Tuple_get_item(x: Node, idx: int) -> Node:
    @Primitive(name=f"Tuple_get_item_{idx}", spec=lambda x, ctx: x[idx])
    def impl(x: Node) -> Node:
        if idx >= len(x.node_type.args) or idx < 0:
            raise IndexError(f"Index is out of range for tuple {str(x)}, given {str(idx)}")

        def sign(x: TupleT) -> StaticType:
            return x.args[idx]

        def op(x: Tuple) -> RuntimeType:
            return x.args[idx]

        return Op(
            impl=op,
            sign=sign,
            args=[x],
            name=f"basic_get_item_{idx}",
        )

    return impl(x)
