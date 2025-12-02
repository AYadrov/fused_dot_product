import typing as tp

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.basics import *
from fused_dot_product.ast.AST import *

########### Private Helpers ############

def _uq_aligner(x: Node,
                y: Node,
                int_aggr: tp.Callable,
                frac_aggr: tp.Callable) -> Op:
    def spec(x, y):
        return x, y
    
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
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="_uq_aligner")

def _uq_zero_extend(x: Node, n: int) -> Op:
    assert isinstance(n, int) and n >= 0
    def spec(x):
        return x
    
    def sign(x: UQT) -> UQT:
        return UQT(x.int_bits + n, x.frac_bits)
    
    def impl(x: UQ) -> Tuple:
        return UQ(x.val, x.int_bits + n, x.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x],
        name="_uq_extend_by_one_bit")
        
def _uq_orer(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        or_res = x_fixed | y_fixed
        return float(or_res / 2**31)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
    def impl(x: UQ, y: UQ) -> UQ:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQ(x.val | y.val, int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="_uq_orer")


def _uq_xorer(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        or_res = x_fixed ^ y_fixed
        return float(or_res / 2**31)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
    def impl(x: UQ, y: UQ) -> UQ:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQ(x.val ^ y.val, int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="_uq_xorer")


############## Public API ##############

def uq_add(x: Node, y: Node) -> Composite:
    def spec(x: float, y: float) -> float:
        return x + y
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits) + 1
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
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
    
    return Composite(
        spec=spec,
        impl=root,
        sign=sign,
        args=[x, y],
        name="uq_add")


def uq_sub(x: Node, y: Node) -> Composite:
    def spec(x: float, y: float) -> float:
        return x - y
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits) + 1
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
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
    return Composite(
        spec=spec,
        impl=root,
        sign=sign,
        args=[x, y],
        name="uq_sub")


def uq_max(x: Node, y: Node) -> Composite:
    def spec(x: float, y: float) -> float:
        return max(x, y)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
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
    return Composite(
        spec=spec,
        impl=root,
        sign=sign,
        args=[x, y],
        name="uq_max")


def uq_mul(x: Node, y: Node) -> Composite:
    def spec(x: float, y: float) -> float:
        return x * y
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = x.int_bits + y.int_bits
        frac_bits = x.frac_bits + y.frac_bits
        return UQT(int_bits, frac_bits)
    
    # Ugly, we need x_adj only for the shape
    x_adj, _ = _uq_aligner(
        x=x,
        y=y,
        int_aggr=lambda x, y: x + y,
        frac_aggr=lambda x, y: x + y,
    )
    root = basic_mul(
        x=x,
        y=y,
        out=x_adj.copy()
    )
    
    return Composite(
            spec=spec,
            impl=root,
            sign=sign,
            args=[x, y],
            name="uq_mul")


def uq_to_q(x: Node) -> Op:
    def impl(x: UQ) -> Q:
        return Q(x.val, x.int_bits + 1, x.frac_bits)
        
    def spec(x: float) -> float:
        return x
    
    def sign(x: UQT) -> QT:
        return QT(x.int_bits + 1, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="uq_to_q")


########### Not Really Good ############

def uq_resize(x: Node, new_int_bits: Node, new_frac_bits: Node) -> Op:
    def spec(x: float, new_int_bits: float, new_frac_bits: float) -> float:
        return x
    
    def impl(x: UQ, new_int_bits: UQ, new_frac_bits: UQ) -> UQ:
        assert new_int_bits.frac_bits == 0
        assert new_frac_bits.frac_bits == 0
        # assert new_int_bits.val >= x.int_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        # assert new_frac_bits.val >= x.frac_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        
        
        return UQ(x.val << (new_frac_bits.val - x.frac_bits), new_int_bits.val, new_frac_bits.val)
    
    def sign(x: UQT, new_int_bits: UQT, new_frac_bits: UQT) -> UQT:
        if new_int_bits.runtime_val and new_frac_bits.runtime_val:
            return UQT(new_int_bits.runtime_val.val, new_frac_bits.runtime_val.val)
        else:
            raise TypeError("uq_resize depends on a variable. Impossible to typecheck")
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, new_int_bits, new_frac_bits],
            name="uq_resize")

# TODO: spec does not match impl (I guess as it should)
def UQ_Rshift(x: Node, amount: Node) -> Op:
    def impl(x: UQ, amount: UQ) -> UQ:
        assert amount.frac_bits == 0
        return UQ(x.val >> amount.val, x.int_bits, x.frac_bits)
    
    def spec(x: float, amount: float) -> float:
        return x / (2 ** int(amount))
    
    def sign(x: UQT, amount: UQT) -> UQT:
        return UQT(x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, amount],
            name="UQ_Rshift")
            
            
def uq_or(x: Node, y: Node) -> Composite:
    def spec(x: float, y: float) -> float:
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        or_res = x_fixed | y_fixed
        return float(or_res / 2**31)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
    x_adj, y_adj = _uq_aligner(
        x=x, 
        y=y, 
        int_aggr=lambda x, y: max(x, y), 
        frac_aggr=lambda x, y: max(x, y),
    )
    impl = _uq_orer(x_adj, y_adj)
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_or")
        
        
def uq_xor(x: Node, y: Node) -> Composite:
    def spec(x: float, y: float) -> float:
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        or_res = x_fixed ^ y_fixed
        return float(or_res / 2**31)
    
    def sign(x: UQT, y: UQT) -> UQT:
        int_bits = max(x.int_bits, y.int_bits)
        frac_bits = max(x.frac_bits, y.frac_bits)
        return UQT(int_bits, frac_bits)
    
    x_adj, y_adj = _uq_aligner(
        x=x, 
        y=y, 
        int_aggr=lambda x, y: max(x, y), 
        frac_aggr=lambda x, y: max(x, y),
    )
    root = _uq_xorer(x_adj, y_adj)
    return Composite(
        spec=spec,
        impl=root,
        sign=sign,
        args=[x, y],
        name="uq_xor")
 

if __name__ == '__main__':
    assert UQ_to_Q(
                Const(UQ(val=100, int_bits=12, frac_bits=34)) 
            ).static_typecheck() == QT(13, 34)
    assert UQ_Mul(
                Const(UQ(val=100, int_bits=12, frac_bits=34)),
                Const(UQ(val=100, int_bits=34, frac_bits=12))
            ).static_typecheck() == UQT(46, 46)
    assert UQ_Resize(
                Const(UQ(val=100, int_bits=12, frac_bits=34)), 
                Const(Int(100)),
                Const(Int(150)),
            ).static_typecheck() == UQT(100, 150)
    assert UQ_Rshift(
                Const(UQ(val=100, int_bits=12, frac_bits=34)), 
                Const(Int(8)),
            ).static_typecheck() == UQT(12, 34)

