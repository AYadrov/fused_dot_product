from fused_dot_product.numtypes.basics import _unary_operator
from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.ast.AST import *

def is_typeof(x: Node, t: StaticType) -> Op:
    if x.node_type != t:
        raise TypeError(f"Node {x.name} with type {x.node_type} does not statically match {t}")
    
    def op(x: RuntimeType) -> int:
        if x.static_type() != t:
            return 0
        else:
            return 1
    
    return _unary_operator(
        op=op,
        x=x,
        out=Const(Bool(0)),
        name="is_typeof",
    )
