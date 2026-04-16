from ..types import *
from ..ast import *
from ..utils import make_fixed_arguments

def basic_tuple_maker(*args) -> Op:
    def sign(*args: StaticType) -> TupleT:
        return TupleT(*args)
    
    def op(*vals: RuntimeType) -> Tuple:
        return Tuple(*vals)
    
    return Op(
        impl=make_fixed_arguments(op, [RuntimeType] * len(args)),
        sign=make_fixed_arguments(sign, [StaticType] * len(args)),
        c_lowering=lambda lowered_args, jittable: (
            f"std::array<uint_fast64_t, {len(args)}>{{"
            + ", ".join(f"static_cast<uint_fast64_t>({arg})" for arg in lowered_args)
            + "}"
        ) if jittable else f"std::make_tuple({', '.join(lowered_args)})",
        args=[*args],
        name=f"basic_tuple_maker_{len(args)}",
    )


@Primitive(name="make_Tuple", spec=lambda *args, ctx: tuple(args), c_inline=True)
def make_Tuple(*args: Node) -> Node:
    return basic_tuple_maker(*args)
