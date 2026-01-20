from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.numtypes.basics import _binary_operator, _unary_operator, _ternary_operator

def assert_type(x: Node, t: StaticType) -> Op:
    if x.node_type != t:
        raise TypeError(f"{x.node_type} does not statically match {t}")
        
    def op(x: RuntimeType) -> int:
        if x.static_type() == t:
            raise TypeError(f"{x.node_type} does not dynamically match {t}")
        return x.val
    
    return _unary_operator(
        op=op,
        x=x,
        out=x.copy(),
        name="assert_type",
    )
