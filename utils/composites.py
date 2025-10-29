from fused_dot_product.ast.AST import *
from fused_dot_product.config import *
from fused_dot_product.utils.basics import *

def bf16_mantissa_to_UQ(mantissa: Node | int) -> Composite:
    """
    Converts the fractional part of a BF16 mantissa into an unsigned fixed-point mantissa
    by restoring the implicit leading 1 bit.

    Args:
        mantissa: Fractional bits of the BF16 mantissa (without the hidden leading 1).

    Returns:
        Composite producing mantissa | (1 << BF16_MANTISSA_BITS) {BF16_MANTISSA_BITS + 1} bits long
    """
    def spec(mantissa: int) -> int:
        return int(2 ** BF16_MANTISSA_BITS + mantissa)
        
    impl = Or(mantissa, Lshift(1, BF16_MANTISSA_BITS))
    
    return Composite(spec, impl, [mantissa], "bf16_mantissa_to_UQ")
    
def UQ_to_Q(mantissa: Node | int, 
            sign: Node | int, 
            bit_width: Node | int) -> Composite:
    """
    Converts unsigned fixed-point mantissa into a signed fixed-point
    using twos complements.
    
    Args:
        mantissa (int): unsinged fixed point
        sign (int): sign bit
        bit_width (int): bit width of mantissa
    
    Returns:
        Composite producing sign?mantissa:2**bit_width - mantissa, {bit-width + 1} bits long
    """
    def spec(mantissa: int, sign: int, bit_width: int) -> int:
        return int(mantissa) if sign == 0 else int(2**bit_width - mantissa)
    
    full_width = Add(bit_width, 1)
    two_pow = Lshift(1, full_width)
    # Compute both candidates
    neg = Sub(two_pow, mantissa)  # 2^(bit_width+1) - mantissa
    pos = mantissa
    # Select one using sign mask: result = pos*(1-sign) + neg*sign
    impl = Add(Mul(Sub(1, sign), pos), Mul(sign, neg))
    
    return Composite(spec, impl, [mantissa, sign, bit_width], "UQ_to_Q")
    
def Q_sign_bit(mantissa: Node | int, 
               bit_width: Node | int) -> Composite:
    """
    Extracts the sign bit (MSB) from a two's complement integer.

    Args:
        mantissa: Two's complement integer value.
        bit_width: Total bit width of the integer.

    Returns:
        Composite producing 0 for non-negative values and 1 for negative values.
    """
    def spec(mantissa: int, bit_width: int) -> int:
        return int(mantissa / 2**(bit_width - 1))
    
    impl = Rshift(mantissa, Sub(bit_width, 1))
    
    return Composite(spec, impl, [mantissa, bit_width], "Q_sign_bit")
    
def Q_to_signed_UQ(mantissa: Node | int, 
                   bit_width: Node | int) -> Composite:
    """
    Converts a two's complement encoded integer into a signed value.

    Args:
        mantissa: The two's complement encoded integer value.
        bit_width: The total bit width of the two's complement representation.

    Returns:
        Composite producing mantissa - (sign_bit << bit_width), {bit_width - 1} bits long.
    """
    def spec(mantissa: int, bit_width: int) -> int:
        sign_bit = Q_sign_bit(mantissa, bit_width).evaluate_spec()
        return int(mantissa - sign_bit * 2 ** bit_width)

    impl = Sub(
        mantissa,
        Lshift(Q_sign_bit(mantissa, bit_width), bit_width)
    )
    
    return Composite(spec, impl, [mantissa, bit_width], "Q_to_signed_UQ")
    
def extend_Q(mantissa: Node | int, 
             bit_width: Node | int, 
             bit_width_new: Node | int) -> Composite:
    """
    Extends a two's complement integer to a larger bit width.

    Args:
        mantissa: The original two's complement encoded integer value.
        bit_width: The current bit width of the input value.
        bit_width_new: The target bit width after extension.

    Returns:
        Composite producing a new two's complement value of width bit_width_new,
        where the sign bit is replicated into the extended upper bits.
    """
    def spec(mantissa: int, bit_width: int, bit_width_new: int) -> int:
        sign = (mantissa >> (bit_width - 1)) & 1
        if sign == 0:
            return mantissa
        else:
            return mantissa | (((1 << (bit_width_new - bit_width)) - 1) << bit_width)

    extend_bits = Sub(bit_width_new, bit_width)
    sign = Q_sign_bit(mantissa, bit_width)
    upper_bits = Sub(Lshift(sign, extend_bits), sign)
    impl = Or(mantissa, Lshift(upper_bits, bit_width))
    
    return Composite(spec, impl, [mantissa, bit_width, bit_width_new], "extend_Q")

def MAX_EXPONENT4(e0: Node | int,
                  e1: Node | int,
                  e2: Node | int,
                  e3: Node | int) -> Composite:
    """
    Computes the maximum exponent value among four inputs using pairwise comparison.

    Args:
        e0: First exponent value.
        e1: Second exponent value.
        e2: Third exponent value.
        e3: Fourth exponent value.

    Returns:
        The maximum value among e0, e1, e2, and e3.
    """
    def spec(e0: int, e1: int, e2: int, e3: int) -> int:
        return max(max(e0, e1), max(e2, e3))
        
    impl = Max(Max(e0, e1), Max(e2, e3))
    
    return Composite(spec, impl, [e0, e1, e2, e3], "MAX_EXPONENT4")
    
def ADDER_TREE4(x0: Node | int,
                x1: Node | int,
                x2: Node | int,
                x3: Node | int,
                bit_width: Node | int) -> Composite:
    """
    Performs a two-level addition of four two's complement operands using an adder tree structure.

    Args:
        x0: First two's complement operand.
        x1: Second two's complement operand.
        x2: Third two's complement operand.
        x3: Fourth two's complement operand.
        bit_width: Bit width of each input operand.

    Returns:
        Operator producing the summed result of all four operands.
        Each addition step increases the bit width by one to accommodate potential overflow.
    """
    def spec(x0: int, x1: int, x2: int, x3: int, bit_width: int) -> int:
        return (x0 + x1) + (x2 + x3)
    
    res1 = Add_twos_complement(x0, bit_width, x1, bit_width)
    res2 = Add_twos_complement(x2, bit_width, x3, bit_width) 
    bit_width_ = Add(1, bit_width)
    impl = Add_twos_complement(res1, bit_width_, res2, bit_width_)
    
    return Composite(spec, impl, [x0, x1, x2, x3, bit_width], "ADDER_TREE4")
    
def Add_twos_complement(x: Node | int,
                        x_bits: Node | int, 
                        y: Node | int, 
                        y_bits: Node | int) -> Composite:
    """
    Adds two two's complement integers of potentially different bit widths.

    Args:
        x: First two's complement operand.
        x_bits: Bit width of the first operand.
        y: Second two's complement operand.
        y_bits: Bit width of the second operand.

    Returns:
        Operator producing the two's complement sum of x and y.
        Output has {max(x_bits, y_bits) + 1} bit width.
    """
    def spec(x: int, x_bits: int, y: int, y_bits: int) -> int:
        x_ = Q_to_signed_UQ(x, x_bits).evaluate_spec()
        y_ = Q_to_signed_UQ(y, y_bits).evaluate_spec()
        sum_ = x_ + y_
        return UQ_to_Q(sum_, 1 if sum_ < 0 else 0, max(x_bits, y_bits) + 1).evaluate_spec()
        
    output_len = Add(Max(x_bits, y_bits), 1)
    x_ = extend_Q(x, x_bits, output_len)
    y_ = extend_Q(y, y_bits, output_len)
    mask = Sub(Lshift(1, output_len), 1)
    impl = And(Add(x_, y_), mask)
    
    return Composite(spec, impl, [x, x_bits, y, y_bits], "Add_twos_complement")
    
# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
def CSA_ADDER_TREE4(m0: Node | int,
                    m1: Node | int, 
                    m2: Node | int, 
                    m3: Node | int, 
                    bit_width: Node | int) -> Composite:
    """
    Performs a four-operand addition using a carry-save adder (CSA) tree structure.

    Args:
        m0: First two's complement operand.
        m1: Second two's complement operand.
        m2: Third two's complement operand.
        m3: Fourth two's complement operand.
        bit_width: Bit width of each input operand.

    Returns:
        Operator producing the sum of the four operands using a two-level CSA tree.
        Output has {bit_width + 3} bit width.
    """
    def spec(m0: int, m1: int, m2: int, m3: int, bit_width: int) -> int:
        return Add_twos_complement(
            Add_twos_complement(m0, bit_width, m1, bit_width).evaluate_spec(), 
            bit_width + 1,
            Add_twos_complement(m2, bit_width, m3, bit_width).evaluate_spec(),
            bit_width + 1
        ).evaluate_spec()
    
    def CSA(a, b, c):
        sum_  = Xor(Xor(a, b), c)
        carry = Or(Or(And(a, b), And(a, c)), And(b, c))
        return  sum_, Lshift(carry, 1)
    
    s1, c1 = CSA(m0, m1, m2)
    m3_ = extend_Q(m3, bit_width, Add(1, bit_width))
    s1_ = extend_Q(s1, bit_width, Add(1, bit_width))
    s2, c2 = CSA(m3_, s1_, c1)
    impl = Add_twos_complement(s2, Add(1, bit_width), c2, Add(2, bit_width))
    
    return Composite(spec, impl, [m0, m1, m2, m3, bit_width], "CSA_ADDER_TREE4")

def take_last_n_bits(x: Node | int, n: Node | int) -> Composite:
    """
    Extracts the least significant n bits from an integer value.

    Args:
        x: Input integer value.
        n: Number of least significant bits to extract.

    Returns:
        Operator producing x & ((1 << n) - 1),
        effectively masking all but the lowest n bits.
    """
    spec = lambda x, n: x % (2 ** n)
    impl = And(x, (Sub(Lshift(1, n), 1)))
    
    return Composite(spec, impl, [x, n], "take_last_n_bits")
    
def invert_bits(x: Node | int, s: Node | int) -> Composite:
    """
    Inverts (negates) the lowest s bits of an integer.

    Args:
        x: Input integer value.
        s: Number of bits to invert, greater than log2(x).

    Returns:
        Operator producing (2^s - 1) - x,
        effectively flipping all bits.
        
    Example:
        invert_bits(3, 2) -> 0   # 0b11 -> 0b00
        invert_bits(0, 2) -> 3   # 0b00 -> 0b11
    """
    spec = lambda x, s: (2**s - 1) - x
    impl = Sub(Sub(Lshift(1, s), 1), x)
    
    return Composite(spec, impl, [x, s], "invert_bits")
    
def exponents_adder(x: Node | int, y: Node | int) -> Composite:
    """
    Adds two exponent values and adjusts the result by subtracting the BF16 bias.

    Args:
        x: First exponent value.
        y: Second exponent value.

    Returns:
        Operator producing (x + y - BF16_BIAS),
        which represents the correctly biased exponent sum for BF16 arithmetic.
    """
    spec = lambda x, y: x + y - BF16_BIAS
    impl = Sub(Add(x, y), BF16_BIAS)
    
    return Composite(spec, impl, [x, y], "exponents_adder")

