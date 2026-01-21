from fused_dot_product.numtypes.basics import _unary_operator, _binary_operator
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

def is_less(x: Node, y: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: 1 if x.val < y.val else 0,
        x=x,
        y=y,
        out=Const(Bool(0)),
        name="is_less",
    )

def is_less_or_equal(x: Node, y: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: 1 if x.val <= y.val else 0,
        x=x,
        y=y,
        out=Const(Bool(0)),
        name="is_less_or_equal",
    )

def is_greater(x: Node, y: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: 1 if x.val > y.val else 0,
        x=x,
        y=y,
        out=Const(Bool(0)),
        name="is_greater",
    )

def is_greater_or_equal(x: Node, y: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: 1 if x.val >= y.val else 0,
        x=x,
        y=y,
        out=Const(Bool(0)),
        name="is_greater_or_equal",
    )

def is_equal(x: Node, y: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: 1 if x.val == y.val else 0,
        x=x,
        y=y,
        out=Const(Bool(0)),
        name="is_equal",
    )

def is_not_equal(x: Node, y: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: 0 if x.val == y.val else 1,
        x=x,
        y=y,
        out=Const(Bool(0)),
        name="is_not_equal",
    )

def negate(x: Node) -> Op:
    assert isinstance(x.node_type, BoolT)
    return _unary_operator(
        op=lambda x: 0 if x.val == 1 else 1,
        x=x,
        out=Const(Bool(0)),
        name="negate",
    )
