from dataclasses import dataclass

class StaticType:
    def __init__(self):
        self.runtime_val = None

    def copy(self) -> "StaticType":
        """Return a fresh StaticType instance with the same shape."""
        new = self._clone_impl()
        new.runtime_val = self.runtime_val
        return new
    
    def runtime_type(self) -> "RuntimeType":
        raise NotImplementedError

    def _clone_impl(self) -> "StaticType":
        raise NotImplementedError
    
    @property
    def total_bits(self):
        raise NotImplementedError
    
    def __repr__(self):
        raise NotImplementedError
    
    def __eq__(self, other):
        raise NotImplementedError


class BoolT(StaticType):
    def __init__(self):
        super().__init__()
    
    @property
    def total_bits(self):
        return 1
    
    def runtime_type(self) -> "RuntimeType":
        from fused_dot_product.numtypes.RuntimeTypes import Bool

        return Bool(0)
    
    def __repr__(self):
        return f"Bool<1>"
    
    def __eq__(self, other):
        return isinstance(other, BoolT)
        
    def _clone_impl(self) -> "QT":
        return BoolT()
     

class QT(StaticType):
    def __init__(self, int_bits: int, frac_bits: int):
        super().__init__()
        assert int_bits >= 0 and frac_bits >= 0
        assert int_bits + frac_bits >= 1
        self.int_bits, self.frac_bits = int_bits, frac_bits
    
    @property
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    def runtime_type(self) -> "RuntimeType":
        from fused_dot_product.numtypes.RuntimeTypes import Q

        return Q(0, self.int_bits, self.frac_bits)
    
    def __repr__(self):
        return f"Q<{self.int_bits},{self.frac_bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, QT)
            and self.int_bits == other.int_bits
            and self.frac_bits == other.frac_bits
        )

    def _clone_impl(self) -> "QT":
        return QT(self.int_bits, self.frac_bits)


class UQT(StaticType):
    def __init__(self, int_bits: int, frac_bits: int):
        super().__init__()
        assert int_bits >= 0 and frac_bits >= 0
        assert int_bits + frac_bits >= 1
        self.int_bits, self.frac_bits = int_bits, frac_bits
    
    @property
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    def runtime_type(self) -> "RuntimeType":
        from fused_dot_product.numtypes.RuntimeTypes import UQ

        return UQ(0, self.int_bits, self.frac_bits)
    
    def __repr__(self):
        return f"UQ<{self.int_bits},{self.frac_bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, UQT)
            and self.int_bits == other.int_bits
            and self.frac_bits == other.frac_bits
        )

    def _clone_impl(self) -> "UQT":
        return UQT(self.int_bits, self.frac_bits)


class Float32T(StaticType):
    def __init__(self):
        super().__init__()
        self.sign_bits = 1
        self.mantissa_bits = 23
        self.exponent_bits = 8
    
    @property
    def total_bits(self):
        return self.sign_bits + self.mantissa_bits + self.exponent_bits
    
    def runtime_type(self) -> "RuntimeType":
        from fused_dot_product.numtypes.RuntimeTypes import Float32

        return Float32(0, 0, 0)
    
    def __repr__(self):
        return f"Float<32>"
    
    def __eq__(self, other):
        return (
            isinstance(other, Float32T)
            and self.sign_bits == other.sign_bits
            and self.mantissa_bits == other.mantissa_bits
            and self.exponent_bits == other.exponent_bits
        )

    def _clone_impl(self) -> "Float32T":
        return Float32T()


class BFloat16T(StaticType):
    def __init__(self):
        super().__init__()
        self.sign_bits = 1
        self.mantissa_bits = 7
        self.exponent_bits = 8
    
    @property
    def total_bits(self):
        return self.sign_bits + self.mantissa_bits + self.exponent_bits
    
    def runtime_type(self) -> "RuntimeType":
        from fused_dot_product.numtypes.RuntimeTypes import BFloat16

        return BFloat16(0, 0, 0)
    
    def __repr__(self):
        return f"BFloat<16>"
    
    def __eq__(self, other):
        return (
            isinstance(other, BFloat16T)
            and self.sign_bits == other.sign_bits
            and self.mantissa_bits == other.mantissa_bits
            and self.exponent_bits == other.exponent_bits
        )

    def _clone_impl(self) -> "BFloat16T":
        return BFloat16T()

class TupleT(StaticType):
    def __init__(self, *args: StaticType):
        super().__init__()
        for x in args:
            assert isinstance(x, StaticType), f"TupleT can not contain non-StaticType, given: {x}"
        self.args = args
    
    @property
    def total_bits(self):
        return sum([x.total_bits for x in self.args])
    
    def runtime_type(self) -> "RuntimeType":
        from fused_dot_product.numtypes.RuntimeTypes import Tuple

        return Tuple(*[arg.runtime_type() for arg in self.args])
    
    def __repr__(self):
        return f"Tuple<{', '.join([repr(x) for x in self.args])}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, TupleT)
            and len(self.args) == len(other.args)
            and all([arg1 == arg2 for arg1, arg2 in zip(self.args, other.args)])
        )

    def _clone_impl(self) -> "TupleT":
        return TupleT(*[arg.copy() for arg in self.args])


if __name__ == '__main__':
    print(QT(1,3))
    print(UQT(1,3))
    print(IntT(1))
    print(Float32T())
    print(BFloat16T())
    print(TupleT(IntT(2)))
    print(TupleT(IntT(2), QT(1,3)))
