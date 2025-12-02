import typing as tp

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.utils.utils import *
from fused_dot_product.ast.AST import *


############ Constructors ##############

def _binary_operator(op: tp.Callable, x: Node, y: Node, out: Node, name: str) -> Op:
    def spec(x, y, out):
        return op(x, y)
    
    def sign(x: StaticType, y: StaticType, out: StaticType) -> StaticType:
        return out
    
    def impl(x: RuntimeType, y: RuntimeType, out: RuntimeType) -> RuntimeType:
        val = op(x.val, y.val)
        # TODO: check for truncation
        val = mask(val, out.total_bits())
        # TODO: add a check whether val is in ranges
        out.val = val
        return out
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y, out],
        name=name)

def _unary_operator(op: tp.Callable, x: Node, out: Node, name: str) -> Op:
    def spec(x, out):
        return op(x)
    
    def sign(x: StaticType, out: StaticType) -> StaticType:
        return out
    
    def impl(x: RuntimeType, out: RuntimeType) -> RuntimeType:
        val = op(x.val)
        # TODO: check for truncation
        val = mask(val, out.total_bits())
        # TODO: add a check whether val is in ranges
        out.val = val
        return out
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, out],
        name=name)

########### Binary Operators ###########

def basic_add(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x + y,
        x=x,
        y=y,
        out=out,
        name="basic_add",
    )

def basic_sub(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x - y,
        x=x,
        y=y,
        out=out,
        name="basic_sub",
    )

def basic_mul(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x * y,
        x=x,
        y=y,
        out=out,
        name="basic_mul",
    )

def basic_max(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: max(x, y),
        x=x,
        y=y,
        out=out,
        name="basic_max",
    )

def basic_min(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: min(x, y),
        x=x,
        y=y,
        out=out,
        name="basic_min",
    )

def basic_rshift(x: Node, amount: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, amount: x >> amount if isinstance(amount, int) else x / 2 ** int(amount),
        x=x,
        y=amount,
        out=out,
        name="basic_rshift",
    )

########### Unary Operators ###########

def basic_select(x: Node, start: int, end: int, out: Node) -> Op:
    assert start >= end and end >= 0, "Bad indexing"
    return _unary_operator(
        op=lambda x: mask(x >> end, start - end + 1) if isinstance(x, int) else (x / 2 ** end) % 2 ** (start - end + 1),
        x=x,
        out=out,
        name="basic_select",
    )


