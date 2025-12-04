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


def _uq_select_shape(x: Node, start: int, end: int) -> Op:
    def spec(x):
        return 0.0
    
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
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x],
        name="_uq_select_shape")


############## Public API ##############

def uq_zero_extend(x: Node, n: int) -> Op:
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
        name="uq_zero_extend")


def uq_add(x: Node, y: Node) -> Composite:
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
    
    return Composite(
        spec=spec,
        impl=impl,
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
    
    return Composite(
        spec=spec,
        impl=impl,
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
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_max")


def uq_min(x: Node, y: Node) -> Composite:
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
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y],
        name="uq_min")


def uq_mul(x: Node, y: Node) -> Composite:
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
    
    return Composite(
            spec=spec,
            impl=impl,
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


# TODO: spec does not match impl due to truncation
def uq_rshift(x: Node, amount: Node) -> Composite:
    def impl(x: Node, amount: Node) -> Node:
        root = basic_rshift(
            x=x,
            amount=amount,
            out=x.copy(),
        )
        return root
    
    def spec(x: float, amount: float) -> float:
        return x / (2 ** int(amount))
    
    # TODO: Would be nice to not care about amount type, just bits amount
    def sign(x: UQT, amount: StaticType) -> UQT:
        return UQT(x.int_bits, x.frac_bits)
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, amount],
        name="uq_rshift")


# TODO: spec does not match impl due to truncation
def uq_lshift(x: Node, amount: Node) -> Composite:
    def impl(x: Node, amount: Node) -> Node:
        root = basic_lshift(
            x=x,
            amount=amount,
            out=x.copy(),
        )
        return root
        
    def spec(x: float, amount: float) -> float:
        return x * (2 ** int(amount))
    
    # TODO: Would be nice to not care about amount type, just bits amount
    def sign(x: UQT, amount: StaticType) -> UQT:
        return UQT(x.int_bits, x.frac_bits)
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, amount],
        name="uq_lshift")



def uq_select(x: Node, start: int, end: int) -> Composite:
    width = start - end + 1
    
    def spec(x: float) -> float:
        return (x // 2 ** end) % 2 ** width
    
    def sign(x: UQT) -> UQT:
        frac_bits = max(0, min(start, x.frac_bits - 1) - end + 1) if x.frac_bits > 0 else 0
        int_bits = width - frac_bits
        return UQT(int_bits, frac_bits)
        
    def impl(x: Node) -> Node:
        out = _uq_select_shape(x, start, end)
        root = basic_select(x, start, end, out)
        return root
    
    return Composite(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="uq_select")


# TODO: Truncation catch, rounding
def uq_resize(x: Node, int_bits: int, frac_bits: int) -> Op:
    def spec(x: float) -> float:
        return x
    
    def impl(x: UQ) -> UQ:
        # assert int_bits >= x.int_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        # assert frac_bits >= x.frac_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        
        shift = frac_bits - x.frac_bits
        if shift >= 0:
            val_adj = x.val << shift  # Fraction bits extension
        else:
            val_adj = x.val >> abs(shift)  # Fraction bits truncation
        
        val_masked = mask(val_adj, int_bits + frac_bits)  # Possible int bits Truncation
        return UQ(val_masked, int_bits, frac_bits)
    
    def sign(x: UQT) -> UQT:
        return UQT(int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x],
        name="uq_resize")

########### Not Really Good ############

# TODO: n is needed only for spec
def uq_invert(x: Node, n: int) -> Op:
    def spec(x):
        if float(int(x)) != x:
            raise ValueError("invert operation is not implemented yet for fractions")
        else:
            return (2**n - 1) - x
   
    def sign(x: UQT) -> UQT:
        return x
    
    def impl(x: UQ) -> UQ:
        val = ((1 << x.total_bits()) - 1) - x.val
        return x.copy(val=val)
    
    return Op(
        spec=spec,
        signature=sign,
        impl=impl,
        args=[x],
        name="uq_invert")

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
    
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = _uq_aligner(
            x=x, 
            y=y, 
            int_aggr=lambda x, y: max(x, y), 
            frac_aggr=lambda x, y: max(x, y),
        )
        impl = _uq_orer(x_adj, y_adj)
        return impl
    
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
    
    def impl(x: Node, y: Node) -> Node:
        x_adj, y_adj = _uq_aligner(
            x=x, 
            y=y, 
            int_aggr=lambda x, y: max(x, y), 
            frac_aggr=lambda x, y: max(x, y),
        )
        root = _uq_xorer(x_adj, y_adj)
        return root
    
    return Composite(
        spec=spec,
        impl=impl,
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

