class Type:
    """Base class for numerical types."""
    pass

class Q(Type):
    """Signed fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, int_bits, frac_bits = val, int_bits, frac_bits
        
        total_bits = int_bits + frac_bits
        min_val = -(1 << (total_bits - 1))
        max_val = (1 << (total_bits - 1)) - 1
        assert min_val <= val <= max_val, (
            f"Value {val} doesn't fit in signed {total_bits}-bit range "
            f"({min_val}..{max_val})"
        )

class UQ(Type):
    """Unsigned fixed-point type."""
    def __init__(self, val: int, int_bits: int, frac_bits: int):
        self.val, int_bits, frac_bits = val, int_bits, frac_bits
        
        assert val >= 0, f"Unsigned value must be non-negative, got {val}"
        total_bits = int_bits + frac_bits
        assert max(1, val.bit_length()) <= total_bits, (
            f"Value {val} requires {max(1, val.bit_length())} bits, "
            f"but only {total_bits} provided ({int_bits}+{frac_bits})"
        )

class Int(Type):
    """Signed integer bits."""
    def __init__(self, val: int, width: int = None):
        self.val = val
        if width is None:
            self.width = max(1, val.bit_length())
        else:
            self.width = width
            
        assert max(1, val.bit_length()) <= self.width, \
                f"Value {val} needs {max(1, val.bit_length())} bits, but width={self.width} is too small"
