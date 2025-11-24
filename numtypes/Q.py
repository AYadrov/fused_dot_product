import struct

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *

        
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

def Q_Negate(x: Node) -> Op:
    def impl(x: Q) -> Q:
        return x.negate()
    
    def spec(x: float) -> float:
        return (-1) * x
    
    def sign(x: QT) -> QT:
        return QT(x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="Q_Negate")

def Q_Add(x: Node, y: Node) -> Op:
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        x_ext = Q.sign_extend(x_adj, 1)
        y_ext = Q.sign_extend(y_adj, 1)
        
        # Mask for handling overflow
        sum_ = mask(y_ext.val + x_ext.val, y_ext.int_bits + y_ext.frac_bits)
        return Q(sum_, y_ext.int_bits, y_ext.frac_bits)
    
    def spec(x: float, y: float) -> float:
        return x + y
    
    def sign(x: QT, y: QT) -> QT:
        frac_bits = max(x.frac_bits, y.frac_bits)
        int_bits = max(x.int_bits, y.int_bits) + 1
        return QT(int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="Q_Add"
    )

# TODO: This specifiation works here - but it is unstable for a general case
def Q_Xor(x: Node, y: Node) -> Op:
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
        name="Q_Xor"
    )
    
def Q_And(x: Node, y: Node) -> Op:  
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
        name="Q_And"
    )
    
def Q_Or(x: Node, y: Node) -> Op:
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
        name="Q_Or"
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
    def impl(x: Q, s: Int) -> Q:
        if s.val == 1:
            total_width = x.int_bits + x.frac_bits
            neg_val = mask(~x.val + 1, total_width)
            return Q(neg_val, x.int_bits, x.frac_bits)
        else:
            return Q(x.val, x.int_bits, x.frac_bits)
    
    def spec(x: float, s: int) -> float:
        return ((-1) ** s) * x
    
    def sign(x: QT, n: IntT) -> QT:
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

