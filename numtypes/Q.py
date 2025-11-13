import struct

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *

        
def Q_sign_bit(x: Node) -> Op:
    def spec(x: float) -> int:
        return 1 if x < 0 else 0
    
    def impl(x: Q) -> Int:
        res = x.sign_bit()
        assert res == 1 or res == 0
        return Int(res)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="Q_sign_bit")

def Q_Negate(x: Node) -> Op:
    def spec(x: float) -> float:
        return (-1) * x

    def impl(x: Q) -> Q:
        return x.negate()

    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="Q_Negate")

def Q_Add(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        return x + y
    
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        x_ext = Q.sign_extend(x_adj, 1)
        y_ext = Q.sign_extend(y_adj, 1)
        
        # Mask for handling overflow
        sum_ = mask(y_ext.val + x_ext.val, y_ext.int_bits + y_ext.frac_bits)
        return Q(sum_, y_ext.int_bits, y_ext.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, y],
        name="Q_Add"
    )

# TODO: This specifiation works here - but it is unstable for a general case
def Q_Xor(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        # Converting to a signed fixed-point
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        xor_res = x_fixed ^ y_fixed
        return float(xor_res / 2**31)

    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        return Q(x_adj.val ^ y_adj.val, x_adj.int_bits, x_adj.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, y],
        name="Q_Xor"
    )
    
def Q_And(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        # Converting to a signed fixed-point
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        and_res = x_fixed & y_fixed
        return float(and_res / 2**31)
        
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        return Q(x_adj.val & y_adj.val, x_adj.int_bits, x_adj.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, y],
        name="Q_And"
    )
    
def Q_Or(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        # Converting to a signed fixed-point
        x_fixed = int(round(x * 2**31))
        y_fixed = int(round(y * 2**31))
        or_res = x_fixed | y_fixed
        return float(or_res / 2**31)
    
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        return Q(x_adj.val | y_adj.val, x_adj.int_bits, x_adj.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, y],
        name="Q_Or"
    )
    
def Q_Lshift(x: Node, n: Node) -> Op:
    def spec(x: float, n: int) -> float:
        return x * 2**n
        
    def impl(x: Q, n: Int) -> Q:
        return Q(x.val << n.val, x.int_bits + n.val, x.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, n],
        name="Q_Lshift"
    )
    
def Q_add_sign(x: Node, sign: Node) -> Op:
    def spec(x: float, sign: int) -> float:
        return ((-1) ** sign) * x

    def impl(x: Q, sign: Int) -> Q:
        if sign.val == 1:
            total_width = x.int_bits + x.frac_bits
            neg_val = mask(~x.val + 1, total_width)
            return Q(neg_val, x.int_bits, x.frac_bits)
        else:
            return Q(x.val, x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec, 
            impl=impl, 
            args=[x, sign], 
            name="Q_add_sign")

