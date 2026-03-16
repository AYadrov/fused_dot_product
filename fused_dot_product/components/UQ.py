import typing as tp

from ..types import *
from .basics import *
from .Q import q_alloc
from .Tuple import make_Tuple
from ..ast import *
from ..spec import *


############## Public API ##############

# Function does not care about int_bits/frac_bits types, it takes their values
# Allocates UQ at runtime
def uq_alloc(int_bits: Node,
              frac_bits: Node) -> Op:
    def sign(int_bits: StaticType, frac_bits: StaticType) -> UQT:
        if int_bits.runtime_val is not None and frac_bits.runtime_val is not None:
            return UQT(int_bits.runtime_val.val, frac_bits.runtime_val.val)
        raise TypeError("uq_alloc's arguments depend on a variable")

    def impl(int_bits: RuntimeType, frac_bits: RuntimeType) -> UQ:
        return UQ(0, int_bits.val, frac_bits.val)

    return Op(
        sign=sign,
        impl=impl,
        args=[int_bits, frac_bits],
        name="uq_alloc")

def uq_less(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x < y

    @Primitive(name="uq_less", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = uq_aligner(x, y, max, max)
        return basic_less(aligned_x, aligned_y, out=Const(Bool(0)))

    return impl(x, y)


def uq_less_or_equal(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x <= y

    @Primitive(name="uq_less_or_equal", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = uq_aligner(x, y, max, max)
        return basic_less_or_equal(aligned_x, aligned_y, out=Const(Bool(0)))

    return impl(x, y)


def uq_greater(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x > y

    @Primitive(name="uq_greater", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = uq_aligner(x, y, max, max)
        return basic_greater(aligned_x, aligned_y, out=Const(Bool(0)))

    return impl(x, y)


def uq_greater_or_equal(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x >= y

    @Primitive(name="uq_greater_or_equal", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = uq_aligner(x, y, max, max)
        return basic_greater_or_equal(aligned_x, aligned_y, out=Const(Bool(0)))

    return impl(x, y)


def uq_equal(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x.eq(y)

    @Primitive(name="uq_equal", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = uq_aligner(x, y, max, max)
        return basic_equal(aligned_x, aligned_y, out=Const(Bool(0)))

    return impl(x, y)


def uq_not_equal(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x.ne(y)

    @Primitive(name="uq_not_equal", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = uq_aligner(x, y, max, max)
        return basic_not_equal(aligned_x, aligned_y, out=Const(Bool(0)))

    return impl(x, y)

def uq_aligner(x: Node,
                y: Node,
                int_aggr: tp.Callable,
                frac_aggr: tp.Callable) -> Node:
    int_bits = int_aggr(x.node_type.int_bits, y.node_type.int_bits)
    frac_bits = frac_aggr(x.node_type.frac_bits, y.node_type.frac_bits)

    def spec(x, y, ctx):
        return (x, y)

    @Primitive(name="uq_aligner", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        def align(x):
            shift = frac_bits - x.node_type.frac_bits
            assert shift >= 0, "truncation is not implemented yet"
            return basic_lshift(x, Const(UQ.from_int(shift)), Const(UQ(0, int_bits, frac_bits)))

        return make_Tuple(align(x), align(y))

    return impl(x, y)


# These functions are possible because x.node_type is known at compile time and does not change
def uq_frac_bits(x: Node) -> Node:
    assert isinstance(x.node_type, UQT)
    return Const(UQ.from_int(x.node_type.frac_bits))


def uq_int_bits(x: Node) -> Node:
    assert isinstance(x.node_type, UQT)
    return Const(UQ.from_int(x.node_type.int_bits))


def uq_zero_extend(x: Node, n: int) -> Node:
    assert isinstance(n, int) and n >= 0

    def spec(x, ctx):
        return x

    @Primitive(name="uq_zero_extend", spec=spec)
    def impl(x: Node) -> Node:
        int_bits = uq_add(uq_int_bits(x), Const(UQ.from_int(n)))
        frac_bits = uq_frac_bits(x)
        out = uq_alloc(int_bits, frac_bits)
        return basic_identity(x=x, out=out)

    return impl(x)


def uq_add(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x + y

    @Primitive(name="uq_add", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = uq_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: max(x, y) + 1,
            frac_aggr=lambda x, y: max(x, y),
        )
        root = basic_add(
            x=x_adj,
            y=y_adj,
            out=x_adj.copy(),
        )
        return root

    return impl(x, y)


def uq_sub(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x - y

    @Primitive(name="uq_sub", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = uq_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: max(x, y) + 1,
            frac_aggr=lambda x, y: max(x, y),
        )
        root = basic_sub(
            x=x_adj, 
            y=y_adj,
            out=x_adj.copy()
        )
        return root

    return impl(x, y)


def uq_max(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x.max(y)

    @Primitive(name="uq_max", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = uq_aligner(
            x=x, 
            y=y, 
            int_aggr=lambda x, y: max(x, y), 
            frac_aggr=lambda x, y: max(x, y),
        )
        root = basic_max(
            x=x_adj, 
            y=y_adj,
            out=x_adj.copy()
        )
        return root

    return impl(x, y)


def uq_min(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x.min(y)

    @Primitive(name="uq_min", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = uq_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: max(x, y), 
            frac_aggr=lambda x, y: max(x, y),
        )
        root = basic_min(
            x=x_adj, 
            y=y_adj,
            out=x_adj.copy()
        )
        return root

    return impl(x, y)


def uq_mul(x: Node, y: Node) -> Node:
    def spec(x, y, ctx):
        return x * y

    @Primitive(name="uq_mul", spec=spec)
    def impl(x: Node, y: Node) -> Node:
        # Ugly
        out, _ = uq_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: x + y,
            frac_aggr=lambda x, y: x + y,
        )
        # x and y are preserved untouched!! important
        root = basic_mul(
            x=x,
            y=y,
            out=out,
        )
        return root

    return impl(x, y)


def uq_to_q(x: Node) -> Node:
    def spec(x, ctx):
        return x

    @Primitive(name="uq_to_q", spec=spec)
    def impl(x: Node) -> Node:
        int_bits = uq_add(uq_int_bits(x), Const(UQ.from_int(1)))
        frac_bits = uq_frac_bits(x)
        out = q_alloc(int_bits, frac_bits)
        return basic_identity(x=x, out=out)

    return impl(x)


# TODO: truncation
def uq_rshift(x: Node, amount: Node) -> Node:
    def spec(x, amount, ctx):
        return x * (ctx.real_val(2) ** (-amount))

    @Primitive(name="uq_rshift", spec=spec)
    def impl(x: Node, amount: Node) -> Node:
        root = basic_rshift(
            x=x,
            amount=amount,
            out=x.copy(),
        )
        return root

    return impl(x, amount)

# TODO: truncation
def uq_lshift(x: Node, amount: Node) -> Node:
    def spec(x, amount, ctx):
        return x * (ctx.real_val(2) ** amount)

    @Primitive(name="uq_lshift", spec=spec)
    def impl(x: Node, amount: Node) -> Node:
        root = basic_lshift(
            x=x,
            amount=amount,
            out=x.copy(),
        )
        return root

    return impl(x, amount)


def uq_select(x: Node, start: int, end: int) -> Node:
    width = start - end + 1
    x_frac_bits = x.node_type.frac_bits

    frac_bits = max(0, min(start, x_frac_bits - 1) - end + 1) if x_frac_bits > 0 else 0
    int_bits = width - frac_bits

    def spec(x, ctx):
        slice1 = ctx.fresh_real("slice1")
        slice2 = ctx.fresh_real("slice2")
        ctx.assume(x.eq(slice1 + slice2))
        return slice1

    @Primitive(name="uq_select", spec=spec)
    def impl(x: Node) -> Node:
        out = Const(UQ(0, int_bits, frac_bits))
        root = basic_select(x, start, end, out)
        return root

    return impl(x)


def uq_split(x: Node, idx: int) -> Node:
    # Returns Tuple(lo, hi), where lo are the lowest `idx` bits.
    assert isinstance(idx, int), f"idx must be int, given: {idx}"
    total_bits = x.node_type.total_bits()
    if idx <= 0 or idx >= total_bits:
        raise ValueError(f"idx must be in (0, {total_bits}), given: {idx}")

    x_int_bits = x.node_type.int_bits
    x_frac_bits = x.node_type.frac_bits

    lo_width = idx
    lo_frac_bits = min(x_frac_bits, lo_width)
    lo_int_bits = lo_width - lo_frac_bits

    hi_width = total_bits - lo_width
    hi_frac_bits = x_frac_bits - lo_frac_bits
    hi_int_bits = hi_width - hi_frac_bits

    def spec(x, ctx):
        lo = ctx.fresh_real("lo")
        hi = ctx.fresh_real("hi")
        
        two = ctx.real_val(2)
        
        # x = hi * 2^lo_int_bits + lo * 2^-hi_frac_bits
        ctx.assume(
            x.eq(
                (hi * two ** ctx.real_val(lo_int_bits))
                + (lo * two ** (-ctx.real_val(hi_frac_bits)))
            )
        )
        return (lo, hi)

    @Primitive(name="uq_split", spec=spec)
    def impl(x: Node) -> Node:
        lo = Const(UQ(0, lo_int_bits, lo_frac_bits))
        lo = basic_select(x, idx - 1, 0, lo)

        hi = Const(UQ(0, hi_int_bits, hi_frac_bits))
        hi = basic_select(x, total_bits - 1, idx, hi)

        return make_Tuple(lo, hi)

    return impl(x)

def uq_resize(x: Node, int_bits: int, frac_bits: int) -> Node:
    def spec(x, ctx):
        return x

    @Primitive(name="uq_resize", spec=spec)
    def impl(x: Node) -> Node:
        assert frac_bits >= x.node_type.frac_bits, "Truncation at uq_resize"
        shift = Const(UQ.from_int(frac_bits - x.node_type.frac_bits))

        out = basic_lshift(
            x=x,
            amount=shift,
            out=Const(UQ(0, int_bits, frac_bits)),
        )
        return out

    def _check_resize_shape(x: UQT) -> None:
        if x.int_bits > int_bits or x.frac_bits > frac_bits:
            raise ValueError("User tries to truncate, not implemented yet")

    _check_resize_shape(x.node_type)
    return impl(x)
