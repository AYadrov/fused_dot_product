from ..types import *
from ..ast import *
from ..utils import make_fixed_arguments

def make_Tuple(*args: Node) -> Primitive:
    if not args:
        raise TypeError("Tuple cannot be empty")

    def sign(*args: StaticType) -> TupleT:
        return TupleT(*args)

    sign_fixed = make_fixed_arguments(sign, [StaticType] * len(args))
    
    def impl(*nodes: Node) -> Node:
        def op(*vals: RuntimeType) -> Tuple:
            return Tuple(*vals)
        return Op(
            impl=make_fixed_arguments(op, [RuntimeType] * len(nodes)),
            sign=sign_fixed,
            args=[*nodes],
            name=f"basic_tuple_maker_{len(nodes)}",
        )
    
    def spec(*args, ctx):
        return tuple(args)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign_fixed,
        args=args,
        name="make_Tuple")
