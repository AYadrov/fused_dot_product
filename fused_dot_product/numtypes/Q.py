import struct

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.basics import *
from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.Tuple import make_Tuple

from z3 import FreshReal, Solver, If

########### Private Helpers ############

# Does not have spec
def _q_is_min_val(x: Node) -> Op:
    def impl(x: Q) -> UQ:
        if x.val == (1 << (x.total_bits() - 1)):
            res = 1
        else:
            res = 0
        return UQ(res, 1, 0)
    
    def sign(x: QT) -> UQT:
        return UQT(1, 0)
    
    return Op(
        impl=impl,
        sign=sign,
        args=[x],
        name="_q_is_min_val")
        

############# Public API ###############

# Function does not care about int_bits/frac_bits types, it takes their values
def q_alloc(int_bits: Node, frac_bits: Node) -> Op:
    def sign(x: StaticType, y: StaticType) -> QT:
        if x.runtime_val is None or y.runtime_val is None:
            raise TypeError("q_alloc's arguments depend on a variable")
        return QT(x.runtime_val.val, y.runtime_val.val)

    def impl(x: RuntimeType, y: RuntimeType) -> Q:
        return Q(0, x.val, y.val)

    return Op(
        sign=sign,
        impl=impl,
        args=[int_bits, frac_bits],
        name="q_alloc")


def q_signs_xor(x: Node, y: Node) -> Primitive:
    def impl(x: Q, y: Q) -> Bool:
        return basic_xor(
            q_sign_bit(x),
            q_sign_bit(y),
            out=Const(Bool(0))
        )
    
    def spec(x, y, out):
        return ((x < 0) != (y < 0)) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_signs_xor")

def q_less(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = q_aligner(x, y, max, max)
        return basic_mux_2_1(
            sel=q_signs_xor(x, y),
            in0=basic_less(aligned_x, aligned_y, Const(Bool(0))),  # same signs
            in1=basic_mux_2_1(  # different signs!
                sel=q_sign_bit(x),
                in0=Const(Bool(0)),  # x > y
                in1=Const(Bool(1)),  # x < y
                out=Const(Bool(0))),
            out=Const(Bool(0)))
    
    def spec(x, y, out):
        return (x < y) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_less"
    )

def q_less_or_equal(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = q_aligner(x, y, max, max)
        return basic_mux_2_1(
            sel=q_signs_xor(x, y),
            in0=basic_less_or_equal(aligned_x, aligned_y, Const(Bool(0))),  # same signs
            in1=basic_mux_2_1(  # different signs!
                sel=q_sign_bit(x),
                in0=Const(Bool(0)),  # x > y
                in1=Const(Bool(1)),  # x < y
                out=Const(Bool(0))),
            out=Const(Bool(0)))
    
    def spec(x, y, out):
        return (x <= y) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_less_or_equal",
    )

def q_greater(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = q_aligner(x, y, max, max)
        return basic_mux_2_1(
            sel=q_signs_xor(x, y),
            in0=basic_greater(aligned_x, aligned_y, Const(Bool(0))),  # same signs
            in1=basic_mux_2_1(  # different signs!
                sel=q_sign_bit(x),
                in0=Const(Bool(1)),  # x > y
                in1=Const(Bool(0)),  # x < y
                out=Const(Bool(0))),
            out=Const(Bool(0)))
    
    def spec(x, y, out):
        return (x > y) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_greater",
    )

def q_greater_or_equal(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = q_aligner(x, y, max, max)
        return basic_mux_2_1(
            sel=q_signs_xor(x, y),
            in0=basic_greater_or_equal(aligned_x, aligned_y, Const(Bool(0))),  # same signs
            in1=basic_mux_2_1(  # different signs!
                sel=q_sign_bit(x),
                in0=Const(Bool(1)),  # x > y
                in1=Const(Bool(0)),  # x < y
                out=Const(Bool(0))),
            out=Const(Bool(0)))
    
    def spec(x, y, out):
        return (x >= y) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_greater_or_equal",
    )

def q_equal(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = q_aligner(x, y, max, max)
        return basic_equal(aligned_x, aligned_y, out=Const(Bool(0)))
    
    def spec(x, y, out): 
        return (x == y) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_equal",
    )

def q_not_equal(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        aligned_x, aligned_y = q_aligner(x, y, max, max)
        return basic_not_equal(aligned_x, aligned_y, out=Const(Bool(0)))
    
    def spec(x, y, out): 
        return (x != y) == out
    
    def sign(x: QT, y: QT) -> BoolT:
        return BoolT()
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_not_equal",
    )

def q_aligner(x: Node,
              y: Node,
              int_aggr: tp.Callable,
              frac_aggr: tp.Callable) -> Primitive:
    int_bits = int_aggr(x.node_type.int_bits, y.node_type.int_bits)
    frac_bits = frac_aggr(x.node_type.frac_bits, y.node_type.frac_bits)
   
    def sign(x: QT, y: QT) -> TupleT:
        return TupleT(QT(int_bits, frac_bits), QT(int_bits, frac_bits))
    
    def spec(x: float, y: float, out: tuple):
        return x == out[0] and y == out[1]
    
    def impl(x: Q, y: Q) -> Tuple:
        def align(x):
            # Step 1. Align frac bits
            shift = frac_bits - x.node_type.frac_bits
            assert shift >= 0, "truncation is not implemented yet"
            x = basic_lshift(
                x,
                Const(UQ.from_int(shift)), 
                Const(Q(0, x.node_type.int_bits, frac_bits)))
            
            # Step 2. Align integer bits
            shift = int_bits - x.node_type.int_bits
            assert shift >= 0, "truncation is not implemented yet"
            return q_sign_extend(x, shift)
        
        return make_Tuple(align(x), align(y))

    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_aligner")

def q_sign_bit(x: Node) -> Primitive:
    def sign(x: QT) -> UQT:
        return UQT(1, 0)
    
    def spec(x: float, out: float):
        return (1.0 if x < 0 else 0.0) == out

    def impl(x: Node) -> Node:
        start = x.node_type.int_bits + x.node_type.frac_bits - 1
        return basic_select(
            x=x,
            start=start,
            end=start,
            out=Const(UQ(0, 1, 0)),
        )
    
    return Primitive(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="q_sign_bit")

def q_sign_extend(x: Node, n: int) -> Primitive:
    assert isinstance(n, int) and n >= 0, f"n should be a non-negative integer, {n} is given"
    def sign(x: QT) -> QT:
        return QT(x.int_bits + n, x.frac_bits)
    
    def spec(x: float, out: float):
        return x == out
    
    def impl(x: Node) -> Node:
        if n == 0:
            return x.copy()
        
        sign_bit = q_sign_bit(x)
        shift_amount = Const(UQ.from_int(n))
        
        shifted = basic_lshift(
            x=sign_bit,
            amount=shift_amount,
            out=Const(UQ(0, n + 1, 0)),
        )
        
        upper_bits = basic_sub(
            x=shifted,
            y=sign_bit,
            out=Const(UQ(0, n, 0)),
        )
        # A little bit ugly, only because of cycles
        int_bits = Const(UQ.from_int(x.node_type.int_bits + n))
        frac_bits = Const(UQ.from_int(x.node_type.frac_bits))
        out = q_alloc(int_bits, frac_bits)
        
        res = basic_concat(
            x=upper_bits,
            y=x,
            out=out,
        )
        return res
    
    return Primitive(
        impl=impl,
        sign=sign,
        spec=spec,
        args=[x],
        name="q_sign_extend")


# TODO: can overflow if x==Min-val
# Ex: q_neg(b10) overflows as -2 is represented, but 2 can not be represented in 2 bits
# Therefore, spec does not really matches for this special case
def q_neg(x: Node) -> Primitive:
    def spec(x: float, out: float):
        return (0.0 if x == 0 else -x) == out
    
    def impl(x: Node) -> Node:
        x_inv = basic_invert(x, x.copy())
        x_neg = basic_add(x_inv, Const(UQ.from_int(1)), x.copy())
        
        x_is_min = _q_is_min_val(x)
        x_overflow = basic_invert(basic_xor(x, x, x.copy()), x.copy())
        
        return basic_mux_2_1(sel=x_is_min, in0=x_neg, in1=x_overflow, out=x.copy())
   
    def sign(x: QT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="q_neg")


def q_add(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = q_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: max(x, y) + 1,
            frac_aggr=lambda x, y: max(x, y),
        )
        return basic_add(x_adj, y_adj, x_adj.copy())
    
    def spec(x, y, s):
        out = FreshReal("out")
        s.add(out == x + y)
        return out
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_add",
    )


def q_sub(x: Node, y: Node) -> Primitive:
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = q_aligner(
            x=x,
            y=y,
            int_aggr=lambda x, y: max(x, y) + 1,
            frac_aggr=lambda x, y: max(x, y),
        )
        root = basic_sub(x_adj, y_adj, x_adj.copy())
        return root
    
    def spec(x, y, s):
        out = FreshReal("out")
        s.add(out == x - y)
        return out
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="q_sub",
    )


# TODO: spec is broken
def q_lshift(x: Node, n: Node) -> Primitive:
    def spec(x: float, n: float, out: float):
        return x * 2**int(n) == out
        
    def sign(x: QT, n: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    def impl(x: Node, n: Node) -> Node:
        impl = basic_lshift(
            x=x,
            amount=n,
            out=x.copy()
        )
        return impl
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, n],
        name="q_lshift",
    )


# assumes that x is already positive
def q_to_uq(x: Node) -> Primitive:
    int_bits = x.node_type.int_bits - 1
    frac_bits = x.node_type.frac_bits
    
    def impl(x: Node) -> Node:
        return basic_identity(x=x, out=Const(UQ(0, int_bits, frac_bits)))
    
    def spec(x: float, out: float):
        assert x >= 0, "q_to_uq assumes that x is positive"
        return x == out
    
    def sign(x: QT) -> UQT:
        return UQT(int_bits, frac_bits)
    
    return Primitive(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[x],
            name="q_to_uq")


def q_rshift(x: Node, n: Node) -> Primitive:
    def spec(x: float, n: float, out: float):
        return x / 2**int(n) == out
    
    def sign(x: QT, n: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    def impl(x: Node, n: Node) -> Node:
        impl = basic_rshift(
            x=x,
            amount=n,
            out=x.copy()
        )
        return impl
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, n],
        name="q_rshift",
    )


def q_add_sign(x: Node, s: Node) -> Primitive:
    def spec(x, sign, s):
        out = FreshReal('out')
        s.add(out == x * If(sign == 0, 1.0, -1.0))
        return out
    
    def impl(x: Node, s: Node) -> Node:
        return basic_mux_2_1(
            sel=s,
            in0=x.copy(),
            in1=q_neg(x),
            out=x.copy(),
        )
    
    def sign(x: QT, s: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, s],
        name="q_add_sign")

def q_abs(x: Node) -> Primitive:
    def spec(x: float, out: float):
        return abs(x) == out
    
    def impl(x: Node) -> Node:
        sign_bit = q_sign_bit(x)  # UQ1.0
        return q_add_sign(x, sign_bit)
    
    def sign(x: QT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="q_abs")
