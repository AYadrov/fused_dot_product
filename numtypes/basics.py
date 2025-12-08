import typing as tp

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.utils.utils import *
from fused_dot_product.ast.AST import *


############ Constructors ##############

def _binary_operator(op: tp.Callable, x: Node, y: Node, out: Node, name: str) -> Op:
    def sign(x: StaticType, y: StaticType, out: StaticType) -> StaticType:
        return out
    
    def impl(x: RuntimeType, y: RuntimeType, out: RuntimeType) -> RuntimeType:
        val = op(x, y)
        # TODO: check for truncation
        val = mask(val, out.total_bits())
        # TODO: add a check whether val is in ranges
        out.val = val
        return out
    
    return Op(
        impl=impl,
        sign=sign,
        args=[x, y, out],
        name=name)

def _unary_operator(op: tp.Callable, x: Node, out: Node, name: str) -> Op:
    def sign(x: StaticType, out: StaticType) -> StaticType:
        return out
    
    def impl(x: RuntimeType, out: RuntimeType) -> RuntimeType:
        val = op(x)
        # TODO: check for truncation
        val = mask(val, out.total_bits())
        # TODO: add a check whether val is in ranges
        out.val = val
        return out
    
    return Op(
        impl=impl,
        sign=sign,
        args=[x, out],
        name=name)

########### Binary Operators ###########

def basic_add(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x.val + y.val,
        x=x,
        y=y,
        out=out,
        name="basic_add",
    )

def basic_sub(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x.val - y.val,
        x=x,
        y=y,
        out=out,
        name="basic_sub",
    )

def basic_mul(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x.val * y.val,
        x=x,
        y=y,
        out=out,
        name="basic_mul",
    )

def basic_max(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: max(x.val, y.val),
        x=x,
        y=y,
        out=out,
        name="basic_max",
    )

def basic_min(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: min(x.val, y.val),
        x=x,
        y=y,
        out=out,
        name="basic_min",
    )

def basic_rshift(x: Node, amount: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, amount: x.val >> amount.val,
        x=x,
        y=amount,
        out=out,
        name="basic_rshift",
    )

def basic_lshift(x: Node, amount: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, amount: x.val << amount.val,
        x=x,
        y=amount,
        out=out,
        name="basic_lshift",
    )

def basic_or(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x.val | y.val,
        x=x,
        y=y,
        out=out,
        name="basic_or",
    )
 
def basic_xor(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x.val ^ y.val,
        x=x,
        y=y,
        out=out,
        name="basic_xor",
    )

def basic_and(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: x.val & y.val,
        x=x,
        y=y,
        out=out,
        name="basic_and",
    )

########### Unary Operators ###########

def basic_select(x: Node, start: int, end: int, out: Node) -> Op:
    assert start >= end and end >= 0, "Bad indexing"
    return _unary_operator(
        op=lambda x: mask(x.val >> end, start - end + 1),
        x=x,
        out=out,
        name="basic_select",
    )

def basic_invert(x: Node, out: Node) -> Op:
    return _unary_operator(
        op=lambda x: ((1 << x.total_bits()) - 1) - x.val,
        x=x,
        out=out,
        name="basic_invert",
    )

def basic_identity(x: Node, out: Node) -> Op:
    return _unary_operator(
        op=lambda x: x.val,
        x=x,
        out=out,
        name="basic_identity",
    )

