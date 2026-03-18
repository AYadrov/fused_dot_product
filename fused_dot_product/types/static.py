class StaticType:
    def __init__(self):
        self.runtime_val = None

    def copy(self) -> "StaticType":
        """Return a fresh StaticType instance with the same shape."""
        new = self._clone_impl()
        new.runtime_val = self.runtime_val
        return new

    def _clone_impl(self) -> "StaticType":
        raise NotImplementedError
    
    def total_bits(self):
        raise NotImplementedError
    
    def __repr__(self):
        raise NotImplementedError
    
    def __eq__(self, other):
        raise NotImplementedError
    
    def to_spec(self, name, ctx):
        raise NotImplementedError


class BoolT(StaticType):
    def __init__(self):
        super().__init__()
    
    def total_bits(self):
        return 1
    
    def __repr__(self):
        return f"Bool<1>"
    
    def __str__(self):
        return f"Bool<1>"
    
    def __eq__(self, other):
        return isinstance(other, BoolT)
        
    def _clone_impl(self) -> "QT":
        return BoolT()
    
    def to_spec(self, name, ctx):
        return ctx.fresh_bool(name)
     

class QT(StaticType):
    def __init__(self, int_bits: int, frac_bits: int):
        super().__init__()
        assert int_bits >= 0 and frac_bits >= 0
        assert int_bits + frac_bits >= 1
        self.int_bits, self.frac_bits = int_bits, frac_bits
    
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    def __repr__(self):
        return f"Q<{self.int_bits},{self.frac_bits}>"
    
    def __str__(self):
        return f"Q<{self.int_bits},{self.frac_bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, QT)
            and self.int_bits == other.int_bits
            and self.frac_bits == other.frac_bits
        )

    def _clone_impl(self) -> "QT":
        return QT(self.int_bits, self.frac_bits)
    
    def to_spec(self, name, ctx):
        return ctx.fresh_real(name)


class UQT(StaticType):
    def __init__(self, int_bits: int, frac_bits: int):
        super().__init__()
        assert int_bits >= 0 and frac_bits >= 0
        assert int_bits + frac_bits >= 1
        self.int_bits, self.frac_bits = int_bits, frac_bits
    
    def total_bits(self):
        return self.int_bits + self.frac_bits
    
    def __repr__(self):
        return f"UQ<{self.int_bits},{self.frac_bits}>"
    
    def __str__(self):
        return f"UQ<{self.int_bits},{self.frac_bits}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, UQT)
            and self.int_bits == other.int_bits
            and self.frac_bits == other.frac_bits
        )

    def _clone_impl(self) -> "UQT":
        return UQT(self.int_bits, self.frac_bits)
    
    def to_spec(self, name, ctx):
        return ctx.fresh_real(name)


class Float32T(StaticType):
    def __init__(self):
        super().__init__()
        self.sign_bits = 1
        self.mantissa_bits = 23
        self.exponent_bits = 8
    
    def total_bits(self):
        return self.sign_bits + self.mantissa_bits + self.exponent_bits
    
    def __repr__(self):
        return f"Float<32>"
    
    def __str__(self):
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
    
    def to_spec(self, name, ctx):
        return ctx.fresh_real(name)


class BFloat16T(StaticType):
    def __init__(self):
        super().__init__()
        self.sign_bits = 1
        self.mantissa_bits = 7
        self.exponent_bits = 8
    
    def total_bits(self):
        return self.sign_bits + self.mantissa_bits + self.exponent_bits
    
    def __repr__(self):
        return f"BFloat<16>"
    
    def __str__(self):
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
    
    def to_spec(self, name, ctx):
        return ctx.fresh_real(name)

class TupleT(StaticType):
    def __init__(self, *args: StaticType):
        super().__init__()
        for x in args:
            assert isinstance(x, StaticType), f"TupleT can not contain non-StaticType, given: {x}"
        assert len(args) != 0, "tuple can not be empty"
        self.args = args
    
    def total_bits(self):
        return sum([x.total_bits() for x in self.args])
    
    def __repr__(self):
        return f"Tuple<{', '.join([repr(x) for x in self.args])}>"
    
    def __str__(self):
        return f"Tuple<{', '.join([repr(x) for x in self.args])}>"
    
    def __eq__(self, other):
        return (
            isinstance(other, TupleT)
            and len(self.args) == len(other.args)
            and all([arg1 == arg2 for arg1, arg2 in zip(self.args, other.args)])
        )

    def _clone_impl(self) -> "TupleT":
        return TupleT(*[arg.copy() for arg in self.args])
    
    def to_spec(self, name, ctx):
        return tuple(x.to_spec(name=f"{name}_{i}", ctx=ctx) for i, x in enumerate(self.args))


__all__ = [
    "StaticType",
    "BoolT",
    "QT",
    "UQT",
    "Float32T",
    "BFloat16T",
    "TupleT",
]
