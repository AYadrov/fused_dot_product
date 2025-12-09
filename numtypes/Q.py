import struct

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.basics import *
from fused_dot_product.ast.AST import *


########### Private Helpers ############

# Function does not care about int_bits/frac_bits types, it takes their values
def _q_alloc(int_bits: Node, frac_bits: Node) -> Op:
    def sign(x: StaticType, y: StaticType) -> QT:
        if x.runtime_val is not None and y.runtime_val is not None:
            return QT(x.runtime_val.val, y.runtime_val.val)
        raise TypeError("q_alloc's arguments depend on a variable")
    
    def impl(x: RuntimeType, y: RuntimeType) -> Q:
        return Q(0, x.val, y.val)
    
    return Op(
        sign=sign,
        impl=impl,
        args=[int_bits, frac_bits],
        name="_q_alloc")

def q_aligner(x: Node,
               y: Node,
               int_aggr: tp.Callable,
               frac_aggr: tp.Callable) -> Op:
    def sign(x: QT, y: QT) -> TupleT:
        int_bits = int_aggr(x.int_bits, y.int_bits)
        frac_bits = frac_aggr(x.frac_bits, y.frac_bits)
        return TupleT(
            QT(int_bits, frac_bits),
            QT(int_bits, frac_bits),
        )
    
    def impl(x: Q, y: Q) -> Tuple:
        def sign_extend(x, n):
            assert n >= 0
            sign = x.val >> (x.total_bits() - 1)
            upper_bits = (sign << n) - sign
            res = x.val | (upper_bits << x.total_bits())
            return Q(res, x.int_bits + n, x.frac_bits)
        
        # TODO: check if aggregation results are less then original ones
        int_bits = int_aggr(x.int_bits, y.int_bits)
        frac_bits = frac_aggr(x.frac_bits, y.frac_bits)
        
        def align(x):
            # Step 1. Align fractional bits
            if x.frac_bits < frac_bits:
                shift = frac_bits - x.frac_bits
                x = Q(x.val << shift, x.int_bits, frac_bits)
            # Step 2. Align integer bits
            if x.int_bits < int_bits:
                shift = int_bits - x.int_bits
                x = sign_extend(x, shift)
            return x
        
        return Tuple(align(x), align(y))

    return Op(
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_aligner")


def _q_frac_bits(x: Node) -> Op:
    def sign(x: QT) -> UQT:
        return UQ.from_int(x.frac_bits).static_type()
    
    def impl(x: Q) -> UQ:
        return UQ.from_int(x.frac_bits)
    
    return Op(
        sign=sign,
        impl=impl,
        args=[x],
        name="_q_frac_bits")

def _q_int_bits(x: Node) -> Op:
    def sign(x: QT) -> UQT:
        return UQ.from_int(x.int_bits).static_type()
    
    def impl(x: Q) -> UQ:
        return UQ.from_int(x.int_bits)
    
    return Op(
        sign=sign,
        impl=impl,
        args=[x],
        name="_q_int_bits")

############## Public API ##############

def q_sign_extend(x: Node, n: int) -> Op:
    assert isinstance(n, int) and n >= 0, f"n should be a non-negative integer, {n} is given"
    def sign(x: QT) -> QT:
        return QT(x.int_bits + n, x.frac_bits)
    
    def impl(x: Q) -> Q:
        sign = x.sign_bit()
        upper_bits = (sign << n) - sign
        res = x.val | (upper_bits << x.total_bits())
        return Q(res, x.int_bits + n, x.frac_bits)
    
    return Op(
        impl=impl,
        sign=sign,
        args=[x],
        name="q_sign_extend")


def q_neg(x: Node) -> Composite:
    def spec(x):
        return -x    
    
    def impl(x: Node) -> Node:
        x = basic_invert(
            x=x,
            out=x.copy(),
        )
        x = basic_add(
            x=x,
            y=Const(UQ.from_int(1)),
            out=x.copy(),
        )
        return x
   
    def sign(x: QT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="q_neg")


def q_add(x: Node, y: Node) -> Composite:
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = q_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: max(x, y) + 1,
            frac_aggr=lambda x, y: max(x, y),
        )
        return basic_add(x_adj, y_adj, x_adj.copy())
    
    def spec(x: float, y: float) -> float:
        return x + y
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_add",
    )


def q_sub(x: Node, y: Node) -> Composite:
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = q_aligner(
            x=x, 
            y=y,
            int_aggr=lambda x, y: max(x, y) + 1,
            frac_aggr=lambda x, y: max(x, y),
        )
        root = basic_sub(x_adj, y_adj, x_adj.copy())
        return root
    
    def spec(x: float, y: float) -> float:
        return x - y
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_sub",
    )


def q_lshift(x: Node, n: Node) -> Composite:
    def spec(x: float, n: float) -> float:
        return x * 2**int(n)
        
    def sign(x: QT, n: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    def impl(x: Node, n: Node) -> Node:
        impl = basic_lshift(
            x=x,
            amount=n,
            out=x.copy()
        )
        return impl
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, n],
        name="q_lshift",
    )


def q_rshift(x: Node, n: Node) -> Composite:
    def spec(x: float, n: float) -> float:
        return x / 2**int(n)
        
    def sign(x: QT, n: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    def impl(x: Node, n: Node) -> Node:
        impl = basic_rshift(
            x=x,
            amount=n,
            out=x.copy()
        )
        return impl
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, n],
        name="q_rshift",
    )


def q_add_sign(x: Node, s: Node) -> Op:
    def impl(x: Q, s: UQ) -> Q:
        assert s.val in (0, 1)
        if s.val == 1:
            total_width = x.int_bits + x.frac_bits
            neg_val = mask(~x.val + 1, total_width)
            return Q(neg_val, x.int_bits, x.frac_bits)
        else:
            return Q(x.val, x.int_bits, x.frac_bits)
            
    def sign(x: QT, n: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x, s], 
            name="q_add_sign")
