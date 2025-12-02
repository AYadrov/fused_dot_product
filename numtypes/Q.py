import struct

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.basics import *
from fused_dot_product.ast.AST import *


########### Private Helpers ############

def _q_aligner(x: Node,
               y: Node,
               int_aggr: tp.Callable,
               frac_aggr: tp.Callable) -> Op:
    def spec(x, y):
        return x, y
    
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
                x = UQ(x.val << shift, x.int_bits, frac_bits)
            # Step 2. Align integer bits
            if x.int_bits < int_bits:
                shift = int_bits - x.int_bits
                x = sign_extend(x, shift)
            return x
        
        return Tuple(align(x), align(y))
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="_q_aligner")

def _q_sign_extend(x: Node, n: int) -> Op:
    def spec(x):
        return x
    
    def sign(x: QT) -> QT:
        return QT(x.int_bits + n, x.frac_bits)
    
    def impl(x: Q) -> Q:
        assert isinstance(n, int) and n >= 0
        sign = x.val >> (x.total_bits() - 1)
        upper_bits = (sign << n) - sign
        res = x.val | (upper_bits << x.total_bits())
        return Q(res, x.int_bits + n, x.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x],
        name="_q_sign_extend")


############## Public API ##############

def Q_sign_bit(x: Node) -> Op:
    def impl(x: Q) -> Int:
        res = x.sign_bit()
        assert res == 1 or res == 0
        return Int(res)
        
    def spec(x: float) -> int:
        return 1 if x < 0 else 0
        
    def sign(x: QT) -> IntT:
        return IntT(1)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="Q_sign_bit")


def q_neg(x: Node) -> Op:
    def impl(x: Q) -> Q:
        total_width = x.total_bits() 
        val = mask((~x.val + 1), total_width)
        return Q(val, x.int_bits, x.frac_bits)
    
    def spec(x: float) -> float:
        return (-1) * x
    
    def sign(x: QT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="q_neg")


def q_add(x: Node, y: Node) -> Composite:
    x_adj, y_adj = _q_aligner(
        x=x, 
        y=y,
        int_aggr=lambda x, y: max(x, y) + 1,
        frac_aggr=lambda x, y: max(x, y),
    )
    root = basic_add(x_adj, y_adj, x_adj.copy())
    
    def spec(x: float, y: float) -> float:
        return x + y
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Composite(
        spec=spec,
        impl=root,
        sign=sign,
        args=[x, y],
        name="q_add",
    )


def q_sub(x: Node, y: Node) -> Composite:
    x_adj, y_adj = _q_aligner(
        x=x, 
        y=y,
        int_aggr=lambda x, y: max(x, y) + 1,
        frac_aggr=lambda x, y: max(x, y),
    )
    root = basic_sub(x_adj, y_adj, x_adj.copy())
    
    def spec(x: float, y: float) -> float:
        return x - y
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Composite(
        spec=spec,
        impl=root,
        sign=sign,
        args=[x, y],
        name="q_sub",
    )


# TODO: This specifiation works here - but it is unstable for a general case
def q_xor(x: Node, y: Node) -> Op:
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        return Q(x_adj.val ^ y_adj.val, x_adj.int_bits, x_adj.frac_bits)
    
    def spec(x: float, y: float) -> float:
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        xor_res = x_fixed ^ y_fixed
        return float(xor_res / 2**31)

    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits)
        return QT(int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="q_xor"
    )
    
def q_and(x: Node, y: Node) -> Op:  
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        return Q(x_adj.val & y_adj.val, x_adj.int_bits, x_adj.frac_bits)
    
    def spec(x: float, y: float) -> float:
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        and_res = x_fixed & y_fixed
        return float(and_res / 2**31)
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits)
        return QT(int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="q_and"
    )

def q_or(x: Node, y: Node) -> Op:
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        return Q(x_adj.val | y_adj.val, x_adj.int_bits, x_adj.frac_bits)
    
    def spec(x: float, y: float) -> float:
        # Converting to a signed fixed-point
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        or_res = x_fixed | y_fixed
        return float(or_res / 2**31)
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits)
        return QT(int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="q_or"
    )
    
def Q_Lshift(x: Node, n: Node) -> Op:
    def impl(x: Q, n: Int) -> Q:
        return Q(x.val << n.val, x.int_bits + n.val, x.frac_bits)
        
    def spec(x: float, n: int) -> float:
        return x * 2**n
        
    def sign(x: QT, n: IntT) -> QT:
        if n.runtime_val is None:
            raise TypeError("Amount of Q_Lshift depends on a variable. Impossible to typecheck")
        else:
            int_bits = x.int_bits + n.runtime_val.val
            frac_bits = x.frac_bits
            return QT(int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, n],
        name="Q_Lshift"
    )
    
def Q_add_sign(x: Node, s: Node) -> Op:
    def impl(x: Q, s: UQ) -> Q:
        assert s.val in (0, 1)
        if s.val == 1:
            total_width = x.int_bits + x.frac_bits
            neg_val = mask(~x.val + 1, total_width)
            return Q(neg_val, x.int_bits, x.frac_bits)
        else:
            return Q(x.val, x.int_bits, x.frac_bits)
            
    def spec(x: float, s: int) -> float:
        return ((-1) ** s) * x
            
    def sign(x: QT, n: UQT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec, 
            impl=impl,
            signature=sign,
            args=[x, s], 
            name="Q_add_sign")

if __name__ == '__main__':
    assert Q_sign_bit(
            Const(Q(val=100, int_bits=12, frac_bits=34)) 
        ).static_typecheck() == IntT(1)
    assert Q_Negate(
            Const(Q(val=100, int_bits=12, frac_bits=34))
        ).static_typecheck() == QT(12, 34)
    assert Q_Add(
            Const(Q(val=100, int_bits=12, frac_bits=34)), 
            Const(Q(val=100, int_bits=34, frac_bits=12))
        ).static_typecheck() == QT(35, 34)
    assert Q_Xor(
            Const(Q(val=100, int_bits=12, frac_bits=34)), 
            Const(Q(val=100, int_bits=34, frac_bits=12))
        ).static_typecheck() == QT(34, 34)
    assert Q_And(
            Const(Q(val=100, int_bits=12, frac_bits=34)), 
            Const(Q(val=100, int_bits=34, frac_bits=12))
        ).static_typecheck() == QT(34, 34)
    assert Q_Or(
            Const(Q(val=100, int_bits=12, frac_bits=34)), 
            Const(Q(val=100, int_bits=34, frac_bits=12))
        ).static_typecheck() == QT(34, 34)
    assert Q_Lshift(
            Const(Q(val=100, int_bits=12, frac_bits=34)), 
            Const(Int(4))
        ).static_typecheck() == QT(16, 34)
    assert Q_add_sign(
            Const(Q(val=100, int_bits=12, frac_bits=34)), 
            Const(Int(1))
        ).static_typecheck() == QT(12, 34)

