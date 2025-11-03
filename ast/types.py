class Type:
    """Base class for numerical types."""
    pass

    def to_spec(self):
        raise NotImplementedError

class Q(Type):
    """Signed fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, int_bits, frac_bits = val, int_bits, frac_bits
        
        total_bits = int_bits + frac_bits
        min_val = -(1 << (total_bits - 1))
        max_val = (1 << (total_bits - 1)) - 1
        
        assert int_bits >= 0, f"int bits can not be negative, {int_bits} is provided"
        assert frac_bits >= 0, f"frac bits can not be negative, {frac_bits} is provided"
        assert min_val <= val <= max_val, (
            f"Value {val} doesn't fit in signed {total_bits}-bit range "
            f"({min_val}..{max_val})"
        )

    def to_spec(self):
        total_bits = self.int_bits + self.frac_bits
        sign_bit = (self.val >> (total_bits - 1)) & 1
    
        if sign_bit == 1:
            signed_val = self.val - (1 << total_bits)
        else:
            signed_val = self.val
    
        return float(signed_val) / (2 ** self.frac_bits)

class UQ(Type):
    """Unsigned fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, int_bits, frac_bits = val, int_bits, frac_bits
        
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

# TODO: loss of accuracy can happen here
def Int_to_UQ(x: Node, int_bits: Node, frac_bits: Node) -> Op:
    def spec(x: int, int_bits: int, frac_bits: int) -> float:
        return x / 2 ** frac_bits

    def impl(x: Int, int_bits: Int, frac_bits: Int) -> UQ:
        total_bits = int_bits.val + frac_bits.val
        assert total_bits >= x.width
        return UQ(x.val, int_bits, frac_bits)

    return Op(
            spec=spec,
            impl=impl,
            args=[x, int_bits, frac_bits],
            name="Int_to_UQ")

def UQ_to_Q(x: Node) -> Op:
    def spec(x: float) -> float:
        return x
    
    def impl(x: UQ):
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
        total_width = x.frac_bits + x.int_bits
        res = x.val >> (total_width - 1)
        assert res == 1 or res == 0
        return Int(res)

def Q_negate(x: Node) -> Op:
    def spec(x: float) -> float:
        return (-1) * x

    def impl(x: Q) -> Q:
        total_width = x.int_bits + x.frac_bits
        mask = (1 << total_width) - 1

        # Two’s complement negation: invert bits, add 1, mask back to width
        neg_val = (~x.val + 1) & mask
        return Q(neg, x.int_bits, x.frac_bits)

    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="Q_negate")
