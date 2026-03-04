from ..types.runtime import RuntimeType, Tuple
from ..types.static import StaticType, TupleT
from .node import Node
from .nodes import Op, Primitive


def Copy(x: Node) -> Primitive:
    def sign(x: StaticType) -> StaticType:
        return x

    def spec(x, ctx):
        return x

    def impl(x):
        return x

    return Primitive(
        sign=sign,
        spec=spec,
        impl=impl,
        args=[x],
        name="Copy",
    )


def Tuple_get_item(x: Node, idx: int) -> Primitive:
    if idx >= len(x.node_type.args) or idx < 0:
        raise IndexError(f"Index is out of range for tuple {str(x)}, given {str(idx)}")

    def sign(x: TupleT) -> StaticType:
        if not isinstance(x, TupleT):
            raise IndexError(f"{x} is not an instance of TupleT to iterate over it")
        return x.args[idx]

    def impl(x: Node) -> Node:
        def op(x: Tuple) -> RuntimeType:
            return x.args[idx]

        return Op(
            impl=op,
            sign=sign,
            args=[x],
            name="basic_get_item",
        )

    def spec(x, ctx):
        return x[idx]

    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name=f"Tuple_get_item_{idx}",
    )

