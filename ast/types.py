from typing import Tuple
import struct

from fused_dot_product.ast.AST import *

class Type:
    """Base class for numerical types."""
    def to_spec(self):
        raise NotImplementedError
        
    def __str__(self):
        raise NotImplementedError


class Q(Type):
    """Signed fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, self.int_bits, self.frac_bits = val, int_bits, frac_bits
        
        total_bits = int_bits + frac_bits
        
        assert int_bits >= 0, f"int bits can not be negative, {int_bits} is provided"
        assert frac_bits >= 0, f"frac bits can not be negative, {frac_bits} is provided"
        assert val >= 0, f"signed fixed-point can not be negative, {val} is provided"
        assert max(1, val.bit_length()) <= total_bits, (
            f"Value {val} requires {max(1, val.bit_length())} bits, "
            f"but only {total_bits} provided ({int_bits}+{frac_bits})"
        )
        
    def __str__(self):
        return f"Q{self.int_bits}.{self.frac_bits} " + str(self.to_spec())

    def sign_bit(self):
        return self.val >> (self.frac_bits + self.int_bits - 1)

    @staticmethod
    def sign_extend(x, n: int):
        assert n >= 0, f"Extend bits can not be negative, {n} is provided"
        total_bits = x.int_bits + x.frac_bits
        sign = x.sign_bit()
        upper_bits = (sign << n) - sign
        res = x.val | (upper_bits << total_bits)
        return Q(res, x.int_bits + n, x.frac_bits)
        
    @staticmethod
    def align(x, y):
        # Step 1. Align fractional bits
        if x.frac_bits > y.frac_bits:
            shift = x.frac_bits - y.frac_bits
            y = Q(y.val << shift, y.int_bits, x.frac_bits)
        elif x.frac_bits < y.frac_bits:
            shift = y.frac_bits - x.frac_bits
            x = Q(x.val << shift, x.int_bits, y.frac_bits)

        # Step 2. Align integer bits
        if x.int_bits > y.int_bits:
            y = Q.sign_extend(y, x.int_bits - y.int_bits)
        elif x.int_bits < y.int_bits:
            x = Q.sign_extend(x, y.int_bits - x.int_bits)
        
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
        
    def __str__(self):
        return f"UQ{self.int_bits}.{self.frac_bits} " + str(self.to_spec())
    
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
                
    def __str__(self):
        return str(self.val)
    
    def to_spec(self):
        return self.val
        
# TODO: SUBNORMALS, ENCODINGS
class Float(Type):
    """Single-precision floating-point format, IEEE754-1985"""
    mantissa_bits = 23
    exponent_bits = 8
    exponent_bias = 127
        
    def __init__(self, sign: int, mantissa: int, exponent: int):
        assert sign in (0, 1), f"Invalid sign: {sign}"
        assert mantissa >= 0, f"Mantissa must be non-negative, got {mantissa}"
        assert exponent >= 0, f"Exponent must be non-negative, got {exponent}"
        assert mantissa.bit_length() <= self.mantissa_bits, \
            f"Mantissa too large: needs {mantissa.bit_length()} bits (max {self.mantissa_bits})"
        assert exponent.bit_length() <= self.exponent_bits, \
            f"Exponent too large: needs {exponent.bit_length()} bits (max {self.exponent_bits})"

        self.sign = sign
        self.mantissa = mantissa
        self.exponent = exponent
       
    def __str__(self):
        return str(self.to_spec())
    
    def to_spec(self):
        """Converts to actual floating-point value (IEEE754-style)."""
        if self.exponent == 0:
            # Subnormal numbers (no implicit 1)
            frac = self.mantissa / (2 ** self.mantissa_bits)
            exp_val = 1 - self.exponent_bias
        else:
            frac = 1.0 + self.mantissa / (2 ** self.mantissa_bits)
            exp_val = self.exponent - self.exponent_bias

        value = (-1) ** self.sign * frac * (2 ** exp_val)
        return float(value)
        

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
            
def UQ_Mul(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        return x * y
        
    def impl(x: UQ, y: UQ) -> UQ:
        val_ = x.val * y.val
        int_bits_ = x.int_bits + y.int_bits
        frac_bits_ = x.frac_bits + y.frac_bits
        return UQ(val_, int_bits_, frac_bits_)
   
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="UQ_Mul")
        
def UQ_Resize(x: Node, new_int_bits: Node, new_frac_bits: Node) -> Op:
    def spec(x: float, new_int_bits: int, new_frac_bits: int) -> float:
        return x
    
    def impl(x: UQ, new_int_bits: Int, new_frac_bits: Int) -> UQ:
        assert new_int_bits.val >= x.int_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        assert new_frac_bits.val >= x.frac_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        
        return UQ(x.val << (new_frac_bits.val - x.frac_bits), new_int_bits.val, new_frac_bits.val)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, new_int_bits, new_frac_bits],
            name="UQ_Resize")
            
# TODO: spec does not match impl (I guess as it should)
def UQ_Rshift(x: Node, amount: Node) -> Op:
    def spec(x: float, amount: int) -> float:
        return x / (2 ** amount)
        
    def impl(x: UQ, amount: Int) -> UQ:
        return UQ(x.val >> amount.val, x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, amount],
            name="UQ_Rshift")

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
