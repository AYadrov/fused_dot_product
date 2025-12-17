import typing as tp

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.utils.utils import *
from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.Tuple import _make_fixed_arguments


############ Constructors ##############

def _impl_constructor(op):
    # To be called with op's arguments and output
    def impl(*args: RuntimeType) -> RuntimeType:
        *op_args, out = args
        val = op(*op_args)
        # TODO: check for truncation
        val = mask(val, out.total_bits())
        # TODO: add a check whether val is in ranges
        out.val = val
        return out
    return impl

def _sign_constructor() -> StaticType:
    # To be called with arguments and output
    def sign(*args: StaticType) -> StaticType:
        return args[-1]
    return sign


def _ternary_operator(op: tp.Callable, x: Node, y: Node, z: Node, out: Node, name: str) -> Op:
    return Op(
        impl=_make_fixed_arguments(_impl_constructor(op), RuntimeType, 4),
        sign=_make_fixed_arguments(_sign_constructor(), StaticType, 4),
        args=[x, y, z, out],
        name=name)

def _binary_operator(op: tp.Callable, x: Node, y: Node, out: Node, name: str) -> Op:
    return Op(
        impl=_make_fixed_arguments(_impl_constructor(op), RuntimeType, 3),
        sign=_make_fixed_arguments(_sign_constructor(), StaticType, 3),
        args=[x, y, out],
        name=name)

def _unary_operator(op: tp.Callable, x: Node, out: Node, name: str) -> Op:
    return Op(
        impl=_make_fixed_arguments(_impl_constructor(op), RuntimeType, 2),
        sign=_make_fixed_arguments(_sign_constructor(), StaticType, 2),
        args=[x, out],
        name=name)

########## Ternary Operators ###########

def basic_mux_2_1(sel: Node, in0: Node, in1: Node, out: Node) -> Op:
    def op(sel: Node, in0: Node, in1: Node) -> int:
        assert sel.val in (0, 1), "out of range"
        return in1.val if sel.val == 1 else in0.val
    return _ternary_operator(
        op=op,
        x=sel,
        y=in0,
        z=in1,
        out=out,
        name="basic_mux_2_1",
    )

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
    def op(x, y):
        return x.val - y.val
    
    return _binary_operator(
        op=op,
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

def basic_concat(x: Node, y: Node, out: Node) -> Op:
    return _binary_operator(
        op=lambda x, y: (x.val << y.total_bits()) | y.val,
        x=x,
        y=y,
        out=out,
        name="basic_concat",
    )

########### Unary Operators ###########

# TODO: Truncation is possible if out is too small
def basic_select(x: Node, start: int, end: int, out: Node) -> Op:
    assert start >= end and end >= 0, "Bad indexing"
    return _unary_operator(
        op=lambda x: mask(x.val >> end, start - end + 1),
        x=x,
        out=out,
        name="basic_select",
    )

# TODO: Truncation is possible if out is too small
def basic_invert(x: Node, out: Node) -> Op:
    return _unary_operator(
        op=lambda x: ((1 << x.total_bits()) - 1) - x.val,
        x=x,
        out=out,
        name="basic_invert",
    )

# TODO: Truncation is possible if out is too small
def basic_identity(x: Node, out: Node) -> Op:
    return _unary_operator(
        op=lambda x: x.val,
        x=x,
        out=out,
        name="basic_identity",
    )

def basic_or_reduce(x: Node, out: Node) -> Op:
    return _unary_operator(
        op=lambda x: 1 if x.val > 0 else 0,
        x=x,
        out=out,
        name="basic_or_reduce",
    )

def basic_and_reduce(x: Node, out: Node) -> Op:
    return _unary_operator(
        op=lambda x: 1 if x.val == ((1 << x.total_bits()) - 1) else 0,
        x=x,
        out=out,
        name="basic_and_reduce",
    )

