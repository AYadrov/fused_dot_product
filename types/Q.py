import struct

from fused_dot_product.types.types import *
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
        total_width = x.int_bits + x.frac_bits
        mask = (1 << total_width) - 1

        # Two’s complement negation: invert bits, add 1, mask back to width
        neg_val = (~x.val + 1) & mask
        return Q(neg_val, x.int_bits, x.frac_bits)

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
        # Mask for handling overflow
        mask = (1 << (x_adj.int_bits + x_adj.frac_bits)) - 1
        sum_ = (x_adj.val + y_adj.val) & mask
        return Q(sum_, x_adj.int_bits + 1, x_adj.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, y],
        name="Q_Add"
    )
    
def Q_Xor(x: Node, y: Node) -> Op:
    # https://stackoverflow.com/questions/14461011/xor-between-floats-in-python
    def spec(x: float, y: float) -> float:
        f1 = int.from_bytes(struct.pack('>d', x), 'big')
        f2 = int.from_bytes(struct.pack('>d', y), 'big')
        orv = f1 ^ f2
        return struct.unpack('>d', orv.to_bytes(8, 'big'))[0]
        
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
        f1 = int.from_bytes(struct.pack('>d', x), 'big')
        f2 = int.from_bytes(struct.pack('>d', y), 'big')
        orv = f1 & f2
        return struct.unpack('>d', orv.to_bytes(8, 'big'))[0]
        
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
        f1 = int.from_bytes(struct.pack('>d', x), 'big')
        f2 = int.from_bytes(struct.pack('>d', y), 'big')
        orv = f1 | f2
        return struct.unpack('>d', orv.to_bytes(8, 'big'))[0]
        
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
            mask = (1 << total_width) - 1
            neg_val = (~x.val + 1) & mask
            return Q(neg_val, x.int_bits, x.frac_bits)
        else:
            return Q(x.val, x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec, 
            impl=impl, 
            args=[x, sign], 
            name="Q_add_sign")

