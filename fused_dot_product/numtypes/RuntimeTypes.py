import random
import time

from fused_dot_product.config import *
from fused_dot_product.utils.utils import *
from fused_dot_product.numtypes.StaticTypes import *

class RuntimeType:
    def to_spec(self):
        raise NotImplementedError
    
    def __str__(self):
        raise NotImplementedError
    
    @classmethod
    def random_generator(cls):
        raise NotImplementedError
    
    def static_type(self):
        raise NotImplementedError
    
    def copy(self):
        raise NotImplementedError
    
    def total_bits(self):
        raise NotImplementedError
    
    def __eq__(self, other):
        raise NotImplementedError


# TODO: Tuple should have a default self.val field
class Tuple(RuntimeType):
    def __init__(self, *args: RuntimeType):
        if not args:
            raise TypeError("Tuple cannot be empty")
        for x in args:
            if not isinstance(x, RuntimeType):
                raise TypeError("Tuple must contain RuntimeType instances")
        
        self.args = args
    
    def to_spec(self):
        return tuple(x.to_spec() for x in self.args)
    
    def __str__(self):
        return f"Tuple[{', '.join([str(x) for x in self.args])}]"
    
    def static_type(self):
        return TupleT(*[x.static_type() for x in self.args])
    
    def total_bits(self):
        return sum([x.total_bits() for x in self.args])
    
    def copy(self):
        return Tuple(*[x.copy() for x in self.args])
    
    def __eq__(self, other):
        return (
            isinstance(other, Tuple)
            and all([x == y for x, y in zip(self.args, other.args)])
        )


class Bool(RuntimeType):
    def __init__(self, val: int):
        assert val in (0, 1)
        self.val = val
        
    def __str__(self):
        return f"Bool({self.val})"
    
    def to_spec(self):
        return self.val
    
    def static_type(self):
        return BoolT()
    
    def copy(self, val=None):
        if val is None:
            val = self.val
        return Bool(val)
    
    def total_bits(self):
        return 1
    
    def __eq__(self, other):
        return (
            isinstance(other, Bool)
            and other.val == self.val
        )
    

class Q(RuntimeType):
    """Signed fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, self.int_bits, self.frac_bits = val, int_bits, frac_bits
        
        assert self.int_bits >= 1  # at least one bit for the sign
        assert self.frac_bits >= 0
        assert self.int_bits + self.frac_bits >= 2
        assert 0 <= self.val < (1 << self.total_bits())
    
    def __str__(self):
        return f"Q{self.int_bits}.{self.frac_bits}({str(self.to_spec())})"
    
    def to_spec(self):
        sign_bit = self.val >> (self.total_bits() - 1)
        if sign_bit == 1:
            signed_val = self.val - (sign_bit << self.total_bits())
            return float(signed_val) / (2 ** self.frac_bits)
        else:
            return float(self.val) / (2 ** self.frac_bits)
    
    def static_type(self):
        return QT(self.int_bits, self.frac_bits)
    
    def copy(self, val=None):
        if val is None:
            val = self.val
        return Q(val, self.int_bits, self.frac_bits)
    
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    # Custom methods
    @staticmethod
    def from_int(x: int):
        if x < 0:
            magnitude = abs(x)
            int_bits = max(2, (magnitude - 1).bit_length() + 1)
            val = (1 << int_bits) + x
        else:
            int_bits = max(2, x.bit_length() + 1)
            val = x
        return Q(val, int_bits, 0)
        
    
    @staticmethod
    def from_float(x: float, target_int: int, target_frac: int):
        W = target_int + target_frac
        scale = 1 << target_frac

        # Float -> bits
        q = int(round(x * scale))

        # Clamps overflow/underflow
        min_q = -(1 << (W - 1))
        max_q =  (1 << (W - 1)) - 1
        if q < min_q:
            q = min_q
        elif q > max_q:
            q = max_q

        # encode to raw two's-complement bits
        bits = q & ((1 << W) - 1)

        return Q(bits, target_int, target_frac)
    
    def __eq__(self, other):
        return (
            isinstance(other, Q)
            and other.int_bits == self.int_bits 
            and other.frac_bits == self.frac_bits 
            and other.val == self.val
        )


class UQ(RuntimeType):
    """Unsigned fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        total_bits = int_bits + frac_bits
        
        assert int_bits >= 0
        assert frac_bits >= 0
        assert int_bits > 0 or frac_bits > 0
        assert 0 <= val < (1 << total_bits), (
            f"Value {val} requires {max(1, val.bit_length())} bits, "
            f"but only {total_bits} provided ({int_bits}+{frac_bits})"
        )
        
        self.val, self.int_bits, self.frac_bits = val, int_bits, frac_bits
    
    def __str__(self):
        return f"UQ{self.int_bits}.{self.frac_bits}({str(self.to_spec())})"
    
    def to_spec(self):
        return float(self.val) / (2 ** self.frac_bits)
    
    def static_type(self):
        return UQT(self.int_bits, self.frac_bits)
    
    def copy(self, val=None):
        if val is None:
            val = self.val
        return UQ(val, self.int_bits, self.frac_bits)
    
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    # Custom methods
    @staticmethod
    def from_int(x: int):
        return UQ(x, max(1, x.bit_length()), 0)
    
    def __eq__(self, other):
        return (
            isinstance(other, UQ)
            and other.int_bits == self.int_bits 
            and other.frac_bits == self.frac_bits 
            and other.val == self.val
        )


class Float32(RuntimeType):
    """Single-precision floating-point format, IEEE754-1985"""
    mantissa_bits = 23
    exponent_bits = 8
    exponent_bias = 127
    inf_code = 255
    sub_code = 0
    nan_code = 255
    zero_code = 0
    
    def __init__(self, sign: int, mantissa: int, exponent: int):
        assert sign in (0, 1)
        assert 0 <= mantissa < (1 << self.mantissa_bits)
        assert 0 <= exponent < (1 << self.exponent_bits)
        
        self.val = (sign << (self.exponent_bits + self.mantissa_bits)) \
                 | (exponent << self.mantissa_bits) \
                 | mantissa
        self.sign = sign
        self.mantissa = mantissa
        self.exponent = exponent
    
    def __str__(self):
        return f"Float({str(self.to_spec())})"
    
    def to_spec(self):
        """Converts to actual floating-point value (IEEE754-style)."""
        # Infinity
        if self.exponent == self.inf_code and self.mantissa == 0:
            return float('-inf') if self.sign == 1 else float('inf')
        # NaN
        elif self.exponent == self.nan_code and self.mantissa != 0:
            return float('nan')
        # Zero/subnormal
        elif self.exponent == 0:
            # Subnormal numbers (no implicit 1)
            frac = self.mantissa / (2 ** self.mantissa_bits)
            exp_val = 1 - self.exponent_bias
            return float((-1) ** self.sign * frac * (2 ** exp_val))
        # Normal
        else:
            frac = 1.0 + self.mantissa / (2 ** self.mantissa_bits)
            exp_val = self.exponent - self.exponent_bias
            return float((-1) ** self.sign * frac * (2 ** exp_val))
    
    def static_type(self):
        return Float32T()
    
    @classmethod
    def nInf(cls):
        return cls(1, 0, cls.inf_code)
    
    @classmethod
    def Inf(cls):
        return cls(0, 0, cls.inf_code)
    
    @classmethod
    def nZero(cls):
        return cls(1, 0, cls.zero_code)
    
    @classmethod
    def Zero(cls):
        return cls(0, 0, cls.zero_code)
    
    @classmethod
    def NaN(cls):
        return cls(0, 1, cls.nan_code)
    
    def copy(self):
        return Float32(self.sign, self.mantissa, self.exponent)
    
    def total_bits(self):
        return 32
    
    def __eq__(self, other):
        return (
            isinstance(other, Float32)
            and self.val == other.val
        )


class BFloat16(RuntimeType):
    """Brain Floating Point 16-bit (bfloat16) format — 1 sign, 8 exponent, 7 mantissa bits."""
    mantissa_bits = 7
    exponent_bits = 8
    exponent_bias = 127
    
    def __init__(self, sign: int, mantissa: int, exponent: int):
        assert sign in (0, 1)
        assert 0 <= mantissa < (1 << self.mantissa_bits)
        assert 0 <= exponent < (1 << self.exponent_bits)
        
        self.val = (sign << (self.exponent_bits + self.mantissa_bits)) \
                 | (exponent << self.mantissa_bits) \
                 | mantissa
        self.sign = sign
        self.mantissa = mantissa
        self.exponent = exponent
    
    def __str__(self):
        # out = f"BFloat16(\n"
        # out += f"\tsign={self.sign}\n"
        # out += f"\tmantissa={self.mantissa}\n"
        # out += f"\texponent={self.exponent}\n"
        # out += f"\tval={str(self.to_spec())}\n)"
        # return out
        return f"BFloat16({str(self.to_spec())})"
    
    # TODO: add Subnormals
    def to_spec(self):
        """Converts to IEEE754-style float value."""
        frac = 1.0 + self.mantissa / (2 ** self.mantissa_bits)
        exp_val = self.exponent - self.exponent_bias
        
        value = (-1) ** self.sign * frac * (2 ** exp_val)
        return float(value)
    
    def static_type(self):
        return BFloat16T()
    
    @classmethod
    def random_generator(cls, seed: int = int(time.time()), shared_exponent_bits: int = 0):
        assert 0 <=  shared_exponent_bits < (1 << cls.exponent_bits)
        
        rnd = random.Random(seed)
        unshared_exponent_bits = cls.exponent_bits - shared_exponent_bits
        shared_exp = rnd.getrandbits(shared_exponent_bits) << unshared_exponent_bits
        
        def gen():
            sign = rnd.getrandbits(1)
            mantissa = rnd.getrandbits(cls.mantissa_bits)
            exponent = shared_exp + rnd.getrandbits(unshared_exponent_bits)
            return BFloat16(sign=sign, mantissa=mantissa, exponent=exponent)
        
        def gen_shared_exp():
            nonlocal shared_exp
            shared_exp = rnd.getrandbits(shared_exponent_bits) << unshared_exponent_bits
            return shared_exp
        
        return gen, gen_shared_exp
    
    def copy(self):
        return BFloat16(self.sign, self.mantissa, self.exponent)
    
    def total_bits(self):
        return 16
    
    def __eq__(self, other):
        return (
            isinstance(other, BFloat16)
            and self.val == other.val
        )


if __name__ == '__main__':
    s = Tuple(Int(2), Q(2, 2, 3))
    print(s)
    print(s.to_spec())
    print(s.static_type())
    
