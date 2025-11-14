from dataclasses import dataclass

from fused_dot_product.numtypes.RuntimeTypes import *

class StaticType:
    @property
    def total_bits(self):
        raise NotImplementedError
    
    def __repr__(self):
        raise NotImplementedError
    
    def __eq__(self):
        raise NotImplementedError


@dataclass(frozen=True)
class QT(StaticType):
    int_bits: int
    frac_bits: int
    
    def __post_init__(self):
        assert self.int_bits >= 0 and self.frac_bits >= 0
        assert self.int_bits + self.frac_bits >= 1
    
    @property
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    def __repr__(self):
        return f"Q<{self.int_bits},{self.frac_bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, QT)
            and self.int_bits == other.int_bits
            and self.frac_bits == other.frac_bits
        )


@dataclass(frozen=True)
class UQT(StaticType):
    int_bits: int
    frac_bits: int
    
    def __post_init__(self):
        assert self.int_bits >= 0 and self.frac_bits >= 0
        assert self.int_bits + self.frac_bits >= 1
    
    @property
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    def __repr__(self):
        return f"UQ<{self.int_bits},{self.frac_bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, UQT)
            and self.int_bits == other.int_bits
            and self.frac_bits == other.frac_bits
        )


@dataclass(frozen=True)
class IntT(StaticType):
    bits: int
    
    def __post_init__(self):
        assert self.bits >= 1
    
    @property
    def total_bits(self):
        return self.bits
    
    def __repr__(self):
        return f"Int<{self.bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, IntT)
            and self.bits == other.bits
        )


@dataclass(frozen=True)
class Float32T(StaticType):
    
    sign_bits = 1
    mantissa_bits = 23
    exponent_bits = 8
    
    @property
    def total_bits(self):
        return self.sign_bits + self.mantissa_bits + self.exponent_bits
    
    def __repr__(self):
        return f"Float<32>"
    
    def __eq__(self, other):
        return isinstance(other, Float32T)


@dataclass(frozen=True)
class BFloat16T(StaticType):
    
    sign_bits = 1
    mantissa_bits = 7
    exponent_bits = 8
    
    @property
    def total_bits(self):
        return self.sign_bits + self.mantissa_bits + self.exponent_bits
    
    def __repr__(self):
        return f"BFloat<16>"
    
    def __eq__(self, other):
        return isinstance(other, BFloat16T)


if __name__ == '__main__':
    print(QT(1,3))
    print(UQT(1,3))
    print(IntT(1))
    print(Float32T())
    print(BFloat16T())

