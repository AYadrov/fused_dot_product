# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *

from fused_dot_product.types.Int import *
from fused_dot_product.types.Float import *
from fused_dot_product.types.Q import *

import math

########## CUSTOM OPERATORS ########

def Q_E_encode_Float(m: Node, e: Node) -> Op:
    def spec(m: float, e: int) -> float:
        """Mathematical reference implementation."""
        return m * (2.0 ** (e - Float.exponent_bias))

    # implementation matches spec; can differ if optimized later
    def impl(m: Q, e: Int) -> Float:
        frac_bits = m.frac_bits
        total_bits = m.int_bits + frac_bits
        
        sign = m.sign_bit()
        if sign:
            m = m.negate()
        mantissa_val = m.val
        exponent_val = e.val
        
        if mantissa_val == 0:
            return Float(sign=0, mantissa=0, exponent=0)
        
        # Normalize so that the integer part is 1.xxxxx
        while (mantissa_val >> frac_bits) == 0:
            mantissa_val <<= 1
            exponent_val -= 1
        
        while (mantissa_val >> (frac_bits + 1)) != 0:
            mantissa_val >>= 1
            exponent_val += 1
        
        # Strip implicit leading 1 for Float mantissa
        mantissa_field = mantissa_val & ((1 << frac_bits) - 1)
        
        bits_to_truncate = max(0, frac_bits - Float.mantissa_bits)
        
        if bits_to_truncate > 0:
            # Bit positions relative to mantissa_field
            guard_pos = bits_to_truncate - 1
            guard_bit = (mantissa_field >> guard_pos) & 1
            
            round_pos = bits_to_truncate - 2
            round_bit = (mantissa_field >> round_pos) & 1 if bits_to_truncate >= 2 else 0
            
            sticky_mask = (1 << max(0, bits_to_truncate - 2)) - 1
            sticky_bit = (mantissa_field & sticky_mask) != 0
            
            mantissa_field >>= bits_to_truncate
            
            # IEEE-754 round-to-nearest-even
            lsb = mantissa_field & 1
            if guard_bit and (round_bit or sticky_bit or lsb):
                mantissa_field += 1
        
        # Construct Float
        return Float(sign=sign, mantissa=mantissa_field, exponent=exponent_val)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[m, e],
        name="Q_E_encode_Float",
    )

def OPTIMIZED_MAX_EXP4(e0: Node, 
                       e1: Node, 
                       e2: Node,
                       e3: Node) -> Op:
    """
    Computes the maximum exponent value among four inputs using a bitwise comparison tree.

    Args:
        e0: First exponent value.
        e1: Second exponent value.
        e2: Third exponent value.
        e3: Fourth exponent value.

    Returns:
        Operator that determines the maximum exponent among the four inputs by performing
        bitwise comparison from the most significant bit (MSB) to the least significant bit (LSB).
        The implementation constructs a logical comparison tree that avoids direct integer
        comparison operations for hardware-efficient synthesis.
    """
    def spec(e0: int, e1: int, e2: int, e3: int) -> int:
        return max(max(e0, e1), max(e2, e3))
    
    def impl(e0: Int, e1: Int, e2: Int, e3: Int) -> int:
        assert e0.width == e1.width and e1.width == e2.width and e2.width == e3.width
        bit_width = e0.width
        exponents = [e0.val, e1.val, e2.val, e3.val]
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
            maxexp[i] = int(any(data_for_or_tree))  # Or-tree
        
        return Int(int(''.join(map(str, map(int, maxexp))), 2), bit_width)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[e0, e1, e2, e3],
        name="OPTIMIZED_MAX_EXP4"
    )

def EXP_OVERFLOW_UNDERFLOW_HANDLING(e: Node) -> Op:
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
        
    def impl(e: Int) -> Int:
        if e.val <= 0:
            raise Exception("Underflow")
        elif e.val >= 255:
            raise Exception("Overflow")
        return Int(min(max(e.val, 0), 255), e.width)
    
    return Op(
        spec=spec,
        impl=impl,
        args=[e],
        name="EXP_OVERFLOW_UNDERFLOW_HANDLING"
    )
