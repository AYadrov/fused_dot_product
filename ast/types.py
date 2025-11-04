from typing import Tuple
from struct import pack, unpack

from fused_dot_product.ast.AST import *

class Type:
    """Base class for numerical types."""
    def to_spec(self):
        raise NotImplementedError

class Q(Type):
    """Signed fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, self.int_bits, self.frac_bits = val, int_bits, frac_bits
        
        total_bits = int_bits + frac_bits
        min_val = -(1 << (total_bits - 1))
        max_val = (1 << (total_bits - 1)) - 1
        
        assert int_bits >= 0, f"int bits can not be negative, {int_bits} is provided"
        assert frac_bits >= 0, f"frac bits can not be negative, {frac_bits} is provided"
        assert min_val <= val <= max_val, (
            f"Value {val} doesn't fit in signed {total_bits}-bit range "
            f"({min_val}..{max_val})"
        )

    def sign_bit(self):
        return self.val >> (self.frac_bits + self.int_bits - 1)

    def sign_extend(self, n: int) -> Q:
        assert n >= 0, f"Extend bits can not be negative, {n} is provided"
        total_bits = self.int_bits + self.frac_bits
        sign = self.sign_bit()
        upper_bits = (sign << n) - sign
        res = self.val | (upper_bits << total_bits)
        return Q(res, self.int_bits + n, self.frac_bits)
        
    @staticmethod
    def align(x: Q, y: Q) -> Tuple[Q, Q]:
        # Step 1. Align fractional bits
        if x.frac_bits > y.frac_bits:
            shift = x.frac_bits - y.frac_bits
            y = Q(y.val << shift, y.int_bits, x.frac_bits)
        elif x.frac_bits < y.frac_bits:
            shift = y.frac_bits - x.frac_bits
            x = Q(x.val << shift, x.int_bits, y.frac_bits)

        # Step 2. Align integer bits
        if x.int_bits > y.int_bits:
            y = y.sign_extend(x.int_bits - y.int_bits)
        elif x.int_bits < y.int_bits:
            x = x.sign_extend(y.int_bits - x.int_bits)
        
        return x, y

    def to_spec(self):
        sign_bit = self.sign_bit()
        total_bits = self.int_bits + self.frac_bits
        signed_val = self.val - (sign_bit << total_bits)
        return float(signed_val) / (2 ** self.frac_bits)

class UQ(Type):
    """Unsigned fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, self.int_bits, self.frac_bits = val, int_bits, frac_bits
        
        assert int_bits >= 0, f"int bits can not be negative, {int_bits} is provided"
        assert frac_bits >= 0, f"frac bits can not be negative, {frac_bits} is provided"
        assert val >= 0, f"Unsigned value must be non-negative, got {val}"
        total_bits = int_bits + frac_bits
        assert max(1, val.bit_length()) <= total_bits, (
            f"Value {val} requires {max(1, val.bit_length())} bits, "
            f"but only {total_bits} provided ({int_bits}+{frac_bits})"
        )
    
    def to_spec(self):
        return float(self.val) / (2 ** self.frac_bits)

class Int(Type):
    """Signed integer bits."""
    def __init__(self, val: int, width: int = None):
        self.val = val
        if width is None:
            self.width = max(1, val.bit_length())
        else:
            self.width = width
        
        assert self.width > 0, f"Integer width can not be less than zero, {self.width} is provided"
        assert max(1, val.bit_length()) <= self.width, \
                f"Value {val} needs {max(1, val.bit_length())} bits, but width={self.width} is too small"
                
    def to_spec(self):
        return self.val
        

# TODO: loss of accuracy can happen here
def Int_to_UQ(x: Node, int_bits: Node, frac_bits: Node) -> Op:
    def spec(x: int, int_bits: int, frac_bits: int) -> float:
        return x / 2 ** frac_bits

    def impl(x: Int, int_bits: Int, frac_bits: Int) -> UQ:
        total_bits = int_bits.val + frac_bits.val
        assert total_bits >= x.width
        return UQ(x.val, int_bits.val, frac_bits.val)

    return Op(
            spec=spec,
            impl=impl,
            args=[x, int_bits, frac_bits],
            name="Int_to_UQ")

def UQ_to_Q(x: Node) -> Op:
    def spec(x: float) -> float:
        return x
    
    def impl(x: UQ) -> Q:
        return Q(x.val, x.int_bits + 1, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="UQ_to_Q")

def Q_sign_bit(x: Node) -> Op:
    """
    Extracts the sign bit (MSB) from a two's complement integer.

    Args:
        mantissa: Two's complement integer value.
        bit_width: Total bit width of the integer.

    Returns:
        Composite producing 0 for non-negative values and 1 for negative values.
    """
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

def Q_negate(x: Node) -> Op:
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
            name="Q_negate")
            
def Q_Add(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        return x + y
        
    def impl(x: Q, y: Q) -> Q:
        x_adj, y_adj = Q.align(x, y)
        
        x_ext = x_adj.sign_extend(1)  # Extending to avoid overflow
        y_ext = y_adj.sign_extend(1)
        
        return Q(x_ext.val + y_ext.val, x_ext.int_bits, x_ext.frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[x, y],
        name="Q_add"
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

