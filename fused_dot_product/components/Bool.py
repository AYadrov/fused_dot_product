from .basics import _unary_operator, _binary_operator, basic_invert
from ..types import *
from ..ast import *
from ..egglog import *
from ..spec import *

def is_typeof(x: Node, t: StaticType) -> Op:
    if x.node_type != t:
        raise TypeError(f"Node {x.name} with type {x.node_type} does not statically match {t}")
        
    def op(x: RuntimeType) -> int:
        return 0 if x.static_type() != t else 1
    
    return _unary_operator(
        op=op,
        x=x,
        out=Const(Bool(0)),
        name="is_typeof",
    )


def negate(x: Node) -> Primitive:
    assert isinstance(x.node_type, BoolT)
    def spec(x, ctx):
        return ~x
    
    def impl(x: Bool):
        return basic_invert(x, out=Const(Bool(0)))
    
    def sign(x: BoolT) -> BoolT:
        return x
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="negate")
