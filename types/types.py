import random
import time

from fused_dot_product.config import *

class Type:
    """Base class for numerical types."""
    def to_spec(self):
        raise NotImplementedError
        
    def __str__(self):
        raise NotImplementedError
    
    @classmethod
    def random_generator(cls):
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
        
        
class BFloat16(Type):
    """Brain Floating Point 16-bit (bfloat16) format — 1 sign, 8 exponent, 7 mantissa bits."""
    mantissa_bits = BF16_MANTISSA_BITS
    exponent_bits = BF16_EXPONENT_BITS
    exponent_bias = BF16_BIAS
        
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
    
    # TODO: add Subnormals
    def to_spec(self):
        """Converts to IEEE754-style float value."""
        frac = 1.0 + self.mantissa / (2 ** self.mantissa_bits)
        exp_val = self.exponent - self.exponent_bias

        value = (-1) ** self.sign * frac * (2 ** exp_val)
        return float(value)
    
    @classmethod   
    def random_generator(cls, seed=int(time.time()), shared_exponent_bits=0):
        random.seed(seed)
        
        assert 0 <=  shared_exponent_bits < (1 << cls.exponent_bits)
        unshared_exponent_bits = cls.exponent_bits - shared_exponent_bits
        shared_exp = random.getrandbits(shared_exponent_bits) << unshared_exponent_bits
        
        def gen():
            sign = random.getrandbits(1)
            mantissa = random.getrandbits(cls.mantissa_bits)
            exponent = shared_exp + random.getrandbits(unshared_exponent_bits)
            return BFloat16(sign=sign, mantissa=mantissa, exponent=exponent)
        return gen
        
