import typing as tp

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.basics import *
from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.Q import _q_alloc

########### Private Helpers ############

def _uq_aligner(x: Node,
                y: Node,
                int_aggr: tp.Callable,
                frac_aggr: tp.Callable) -> Op:
    def sign(x: UQT, y: UQT) -> TupleT:
        int_bits = int_aggr(x.int_bits, y.int_bits)
        frac_bits = frac_aggr(x.frac_bits, y.frac_bits)
        
        return TupleT(
            UQT(int_bits, frac_bits),
            UQT(int_bits, frac_bits),
        )
    
    def impl(x: UQ, y: UQ) -> Tuple:
        # TODO: Truncation
        int_bits = int_aggr(x.int_bits, y.int_bits)
        frac_bits = frac_aggr(x.frac_bits, y.frac_bits)
        
        def align(x):
            if x.frac_bits < frac_bits:
                shift = frac_bits - x.frac_bits
                x = UQ(x.val << shift, int_bits, frac_bits)
            else:
                x = UQ(x.val, int_bits, frac_bits)
            return x
        
        return Tuple(align(x), align(y))
    
    return Op(
        impl=impl,
        sign=sign,
        args=[x, y],
        name="_uq_aligner")


def _uq_select_shape(x: Node, start: int, end: int) -> Op:
    def sign(x: UQT) -> UQT:
        frac_bits = max(0, min(start, x.frac_bits - 1) - end + 1) if x.frac_bits > 0 else 0
        width = start - end + 1
        int_bits = width - frac_bits
        return UQT(int_bits, frac_bits)
    
    def impl(x: UQ) -> UQ:
        frac_bits = max(0, min(start, x.frac_bits - 1) - end + 1) if x.frac_bits > 0 else 0
        width = start - end + 1
        int_bits = width - frac_bits
        return UQ(0, int_bits, frac_bits)
    
    return Op(
        impl=impl,
        sign=sign,
        args=[x],
        name="_uq_select_shape")


# Function does not care about int_bits/frac_bits types, it takes their values
# Allocates UQ at runtime
def _uq_alloc(int_bits: Node,
             frac_bits: Node) -> Op:
    def sign(int_bits: StaticType, frac_bits: StaticType) -> UQT:
        if int_bits.runtime_val is not None and frac_bits.runtime_val is not None:
            return UQT(int_bits.runtime_val.val, frac_bits.runtime_val.val)
        raise TypeError("_uq_alloc's arguments depend on a variable")
    
    def impl(int_bits: RuntimeType, frac_bits: RuntimeType) -> UQ:
        return UQ(0, int_bits.val, frac_bits.val)
    
    return Op(
        sign=sign,
        impl=impl,
        args=[int_bits, frac_bits],
        name="_uq_alloc")


# These functions are possible because x.node_type is known at compile time and does not change
def _uq_frac_bits(x: Node) -> Node:
    assert isinstance(x.node_type, UQT)
    return Const(UQ.from_int(x.node_type.frac_bits))

def _uq_int_bits(x: Node) -> Node:
    assert isinstance(x.node_type, UQT)
    return Const(UQ.from_int(x.node_type.int_bits))


############## Public API ##############

def uq_zero_extend(x: Node, n: int) -> Primitive:
    assert isinstance(n, int) and n >= 0
    def sign(x: UQT) -> UQT:
        return UQT(x.int_bits + n, x.frac_bits)
    
    def spec(x):
        return x
    
    def impl(x: Node) -> Node:
        int_bits = uq_add(_uq_int_bits(x), Const(UQ.from_int(n)))
        frac_bits = _uq_frac_bits(x)
        out = _uq_alloc(int_bits, frac_bits)
        return basic_identity(x=x, out=out)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="uq_zero_extend")


def uq_add(x: Node, y: Node) -> Primitive:
    def spec(x: float, y: float) -> float:
        return x + y
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits) + 1
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = _uq_aligner(
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
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_add")


def uq_sub(x: Node, y: Node) -> Primitive:
    def spec(x: float, y: float) -> float:
        return x - y
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits) + 1
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
        
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = _uq_aligner(
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
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_sub")


def uq_max(x: Node, y: Node) -> Primitive:
    def spec(x: float, y: float) -> float:
        return max(x, y)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = _uq_aligner(
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
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_max")


def uq_min(x: Node, y: Node) -> Primitive:
    def spec(x: float, y: float) -> float:
        return min(x, y)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
        
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = _uq_aligner(
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
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_min")


def uq_mul(x: Node, y: Node) -> Primitive:
    def spec(x: float, y: float) -> float:
        return x * y
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = x.int_bits + y.int_bits
        frac_bits = x.frac_bits + y.frac_bits
        return UQT(int_bits, frac_bits)
    
    def impl(x: Node, y: Node) -> Node:
        # Ugly
        out, _ = _uq_aligner(
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
    
    return Primitive(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[x, y],
            name="uq_mul")


def uq_to_q(x: Node) -> Primitive:
    def impl(x: Node) -> Node:
        int_bits = uq_add(_uq_int_bits(x), Const(UQ.from_int(1)))
        frac_bits = _uq_frac_bits(x)
        out = _q_alloc(int_bits, frac_bits)
        return basic_identity(x=x, out=out)
    
    def spec(x):
        return x
    
    def sign(x: UQT) -> QT:
        return QT(x.int_bits + 1, x.frac_bits)
    
    return Primitive(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[x],
            name="uq_to_q")


# TODO: truncation
def uq_rshift(x: Node, amount: Node) -> Primitive:
    x_frac_bits = x.node_type.frac_bits
    def impl(x: Node, amount: Node) -> Node:
        root = basic_rshift(
            x=x,
            amount=amount,
            out=x.copy(),
        )
        return root
    
    def spec(x: float, amount: float) -> float:
        raw = int(round(x * (2 ** x_frac_bits)))
        shifted = raw >> int(amount)
        return float(shifted) / (2 ** x_frac_bits)
    
    # TODO: Would be nice to not care about amount type, just bits amount
    def sign(x: UQT, amount: StaticType) -> UQT:
        return UQT(x.int_bits, x.frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, amount],
        name="uq_rshift")

# TODO: truncation
def uq_lshift(x: Node, amount: Node) -> Primitive:
    x_frac_bits = x.node_type.frac_bits
    x_total_bits = x.node_type.int_bits + x.node_type.frac_bits
    def impl(x: Node, amount: Node) -> Node:
        root = basic_lshift(
            x=x,
            amount=amount,
            out=x.copy(),
        )
        return root
        
    def spec(x: float, amount: float) -> float:
        raw = int(round(x * (2 ** x_frac_bits)))
        shifted = (raw << int(amount)) & ((1 << x_total_bits) - 1)
        return float(shifted) / (2 ** x_frac_bits)
    
    def sign(x: UQT, amount: StaticType) -> UQT:
        return UQT(x.int_bits, x.frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, amount],
        name="uq_lshift")



def uq_select(x: Node, start: int, end: int) -> Primitive:
    width = start - end + 1
    x_frac_bits = x.node_type.frac_bits
    
    def spec(x: float) -> float:
        # Interpret `x` using its fractional layout, then slice bits [start:end].
        raw = int(round(x * (2 ** x_frac_bits)))
        sliced = (raw >> end) & ((1 << width) - 1)
        # The output fractional width mirrors `_uq_select_shape`.
        out_frac_bits = max(0, min(start, x_frac_bits - 1) - end + 1) if x_frac_bits > 0 else 0
        return float(sliced) / (2 ** out_frac_bits)
    
    def sign(x: UQT) -> UQT:
        frac_bits = max(0, min(start, x.frac_bits - 1) - end + 1) if x.frac_bits > 0 else 0
        int_bits = width - frac_bits
        return UQT(int_bits, frac_bits)
        
    def impl(x: Node) -> Node:
        out = _uq_select_shape(x, start, end)
        root = basic_select(x, start, end, out)
        return root
    
    return Primitive(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="uq_select")


# TODO: Truncation
def uq_resize(x: Node, int_bits: int, frac_bits: int) -> Primitive:
    def spec(x):
        return x
    
    def impl(x: Node) -> Node:
        shift = uq_sub(
            Const(UQ.from_int(frac_bits)), 
            _uq_frac_bits(x),
        )
        
        out = basic_lshift(
            x=x, 
            amount=shift,
            out=Const(UQ(0, int_bits, frac_bits)),
        )
        return out
    
    def sign(x: UQT) -> UQT:
        if x.int_bits > int_bits or x.frac_bits > frac_bits:
            raise ValueError("User tries to truncate, not implemented yet")
        return UQT(int_bits, frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="uq_resize")
