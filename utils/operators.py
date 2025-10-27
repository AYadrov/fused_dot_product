# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *
from fused_dot_product.config import *

import math

########## CUSTOM OPERATORS ########
    
def UQ_E_to_float(fxp, fraction_bits, exponent) -> Operator:
    """
    Convert a signed fixed-point mantissa and exponent into a floating-point value.

    Args:
        fxp: Fixed-point mantissa (signed integer).
        fraction_bits: Number of fractional bits in the mantissa.
        exponent: Exponent value.

    Returns:
        Operator encoding float = mantissa * 2^(exponent - BF16_BIAS - fraction_bits)
    """

    def spec(m: int, frac_bits: int, e: int) -> float:
        """Mathematical reference implementation."""
        return float(m) * 2.0 ** (e - BF16_BIAS - frac_bits)

    # implementation matches spec; can differ if optimized later
    def impl(m: int, frac_bits: int, e: int) -> float:
        return float(m) * 2.0 ** (e - BF16_BIAS - frac_bits)

    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[fxp, fraction_bits, exponent],
        name="UQ_E_to_float",
    )
    
def bf16_mantissa_to_UQ(m) -> Operator:
    """
    Converts the fractional part of a BF16 mantissa into an unsigned fixed-point mantissa
    by restoring the implicit leading 1 bit.

    Args:
        m: Fractional bits of the BF16 mantissa (without the hidden leading 1).

    Returns:
        Operator producing m | (1 << BF16_MANTISSA_BITS) 8 bits long
    """
    return Or(m, Lshift(1, BF16_MANTISSA_BITS))

# Function extends mantissa length by one
def to_twos_complement(mantissa, sign, bit_width) -> Operator:
    """
    Converts unsigned fixed-point mantissa into a signed fixed-point
    using twos complements.
    
    Args:
        mantissa (int): unsinged fixed point
        sign (int): sign bit
        bit_width (int): bit width of mantissa
    
    Returns:
        Operator producing sign?mantissa:2**bit_width - mantissa, {bit-width + 1} bits long
    """
    full_width = Add(bit_width, 1)
    two_pow = Lshift(1, full_width)
    # Compute both candidates
    neg = Sub(two_pow, mantissa)  # 2^(bit_width+1) - mantissa
    pos = mantissa
    # Select one using sign mask: result = pos*(1-sign) + neg*sign
    return Add(Mul(Sub(1, sign), pos), Mul(sign, neg))

def twos_complement_sign_bit(mantissa, bit_width) -> Operator:
    """
    Extracts the sign bit (MSB) from a two's complement integer.

    Args:
        mantissa: Two's complement integer value.
        bit_width: Total bit width of the integer.

    Returns:
        Operator producing 0 for non-negative values and 1 for negative values.
    """
    return Rshift(
        mantissa, Sub(bit_width, 1)
    )
    
def from_twos_complement(mantissa, bit_width) -> Operator:
    """
    Converts a two's complement encoded integer into a signed value.

    Args:
        mantissa: The two's complement encoded integer value.
        bit_width: The total bit width of the two's complement representation.

    Returns:
        Operator producing mantissa - (sign_bit << bit_width), {bit_width - 1} bits long.
    """
    return Sub(
        mantissa,
        Lshift(twos_complement_sign_bit(mantissa, bit_width), bit_width)
    )
    
def extend_twos_complement(mantissa, bit_width, bit_width_new) -> Operator:
    """
    Extends a two's complement integer to a larger bit width.

    Args:
        mantissa: The original two's complement encoded integer value.
        bit_width: The current bit width of the input value.
        bit_width_new: The target bit width after extension.

    Returns:
        Operator producing a new two's complement value of width bit_width_new,
        where the sign bit is replicated into the extended upper bits.
    """
    extend_bits = Sub(bit_width_new, bit_width)
    sign = twos_complement_sign_bit(mantissa, bit_width)
    upper_bits = Sub(Lshift(sign, extend_bits), sign)
    return Or(mantissa, Lshift(upper_bits, bit_width))
 
def conventional_max_exponent(e0, e1, e2, e3):
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
    return Max(Max(e0, e1), Max(e2, e3))

def conventional_adder_tree(x0, x1, x2, x3, bit_width) -> Operator:
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
    res1 = Add_twos_complement(x0, bit_width, x1, bit_width)
    res2 = Add_twos_complement(x2, bit_width, x3, bit_width) 
    bit_width_ = Add(1, bit_width)
    return Add_twos_complement(res1, bit_width_, res2, bit_width_)

def OPTIMIZED_MAX_EXP(e0, e1, e2, e3, bit_width) -> Operator:
    """
    Computes the maximum exponent value among four inputs using a bitwise comparison tree.

    Args:
        e0: First exponent value.
        e1: Second exponent value.
        e2: Third exponent value.
        e3: Fourth exponent value.
        bit_width: Bit width of each exponent value.

    Returns:
        Operator that determines the maximum exponent among the four inputs by performing
        bitwise comparison from the most significant bit (MSB) to the least significant bit (LSB).
        The implementation constructs a logical comparison tree that avoids direct integer
        comparison operations for hardware-efficient synthesis.
    """
    def spec(e0: int, e1: int, e2: int, e3: int, bit_width: int) -> int:
        return max(max(e0, e1), max(e2, e3))
    
    def impl(e0: int, e1: int, e2: int, e3: int, bit_width: int) -> int:
        assert bit_width > 0
        exponents = [e0, e1, e2, e3]
        num_elements = len(exponents)
        
        # Binary representations of exponents, extra element {0} for convenience
        ep_bits = [
            [0] + list(map(int, f'{e:0{bit_width}b}'))
            for e in exponents
        ]
        
        smaller = [[0] * (bit_width + 1) for _ in range(num_elements)] # extra element for convenience
        maxexp = [0] * (bit_width + 1)
        
        # Process bits from MSB to LSB
        for i in range(1, bit_width + 1):
            data_for_or_tree = []
            for j in range(num_elements):
                res = not ((maxexp[i-1] and (not ep_bits[j][i-1])) or smaller[j][i-1])
                smaller[j][i] = not res
                data_for_or_tree.append(ep_bits[j][i] and res)
            maxexp[i] = OR_tree(data_for_or_tree)
        
        return int(''.join(map(str, map(int, maxexp))), 2)
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[e0, e1, e2, e3, bit_width],
        name="OPTIMIZED_MAX_EXP"
    )

def Add_twos_complement(x, x_bits, y, y_bits) -> Operator:
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
    output_len = Add(Max(x_bits, y_bits), 1)
    x_ = extend_twos_complement(x, x_bits, output_len)
    y_ = extend_twos_complement(y, y_bits, output_len)
    mask = Sub(Lshift(1, output_len), 1)
    return And(Add(x_, y_), mask)

# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
def CSA_TREE4(m0, m1, m2, m3, bit_width) -> Operator:
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
    s1, c1 = CSA(m0, m1, m2)
    m3_ = extend_twos_complement(m3, bit_width, Add(1, bit_width))
    s1_ = extend_twos_complement(s1, bit_width, Add(1, bit_width))
    s2, c2 = CSA(m3_, s1_, c1)
    return Add_twos_complement(s2, Add(1, bit_width), c2, Add(2, bit_width))

# Depending on a task, you may not need to shift carry every time after CSA
def CSA(a, b, c):
    """
    Performs a single-stage carry-save addition (CSA) of three operands.

    Args:
        a: First input operand.
        b: Second input operand.
        c: Third input operand.

    Returns:
        A tuple (sum_, carry) where:
            sum_: Bitwise sum of the three operands without carry propagation.
            carry: Bitwise carry output left-shifted by one bit to align with
                   the next higher bit position for subsequent addition stages.
    """
    sum_  = Xor(Xor(a, b), c)
    carry = Or(Or(And(a, b), And(a, c)), And(b, c))
    return sum_, Lshift(carry, 1)

def take_last_n_bits(x, n) -> Operator:
    """
    Extracts the least significant n bits from an integer value.

    Args:
        x: Input integer value.
        n: Number of least significant bits to extract.

    Returns:
        Operator producing x & ((1 << n) - 1),
        effectively masking all but the lowest n bits.
    """
    return And(x, (Sub(Lshift(1, n), 1)))

def drop_last_n_bits(x, n) -> Operator:
    """
    Drops the least significant n bits of an integer by performing an arithmetic right shift.

    Note:
        This implementation is incorrect for negative values of x,
        as it performs a logical right shift instead of preserving the sign.

    Args:
        x: Input integer value.
        n: Number of least significant bits to drop.

    Returns:
        Operator performing floor(x / 2^n) as specified in spec,
        implemented as a bitwise right shift by n bits.
    """
    def spec(x: int, n: int) -> int:
        return math.floor(x / (2**n))
    
    def impl(x: int, n: int) -> int:
        return x >> n
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[x, n],
        name="drop_last_n_bits"
    )

def invert_bits(x, s) -> Operator:
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
    return Sub(Sub(Lshift(1, s), 1), x)

def EXP_OVERFLOW_UNDERFLOW_HANDLING(e) -> Operator:
    """
    Handles exponent overflow and underflow conditions by clamping or raising exceptions.

    Args:
        e: Exponent value to be checked.

    Returns:
        Operator that:
            - In the spec function, clamps e to the range [0, 255].
            - In the impl function, raises an exception on underflow (e <= 0)
              or overflow (e >= 255), otherwise returns e clamped to [0, 255].
    """
    def spec(e: int) -> int:
        return min(max(e, 0), 255)
    def impl(e: int) -> int:
        if e <= 0:
            raise Exception("Underflow")
        elif e >= 255:
            raise Exception("Overflow")
        return min(max(e, 0), 255)
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[e],
        name="EXP_OVERFLOW_UNDERFLOW_HANDLING"
    )

def exponents_adder(x, y) -> Operator:
    """
    Adds two exponent values and adjusts the result by subtracting the BF16 bias.

    Args:
        x: First exponent value.
        y: Second exponent value.

    Returns:
        Operator producing (x + y - BF16_BIAS),
        which represents the correctly biased exponent sum for BF16 arithmetic.
    """
    return Sub(Add(x, y), BF16_BIAS)

