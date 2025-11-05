# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *
from fused_dot_product.config import *

import math

########## CUSTOM OPERATORS ########
    
def Q_E_encode_float(m: Node, e: Node) -> Op:
    def spec(m: float, e: int) -> float:
        """Mathematical reference implementation."""
        return float(m) * 2.0 ** (e - BF16_BIAS)

    # implementation matches spec; can differ if optimized later
    def impl(m: Q, e: Int) -> Float:
        frac_bits = m.frac_bits
        total_bits = m.int_bits + frac_bits

        sign = m.sign_bit()
        if sign:
            mantissa_val = ((~m.val) + 1) & ((1 << total_bits) - 1)
        else:
            mantissa_val = m.val
        exponent_val = e.val
        
        if mantissa_val == 0:
            return Float(sign=0, mantissa=0, exponent=0)
        
        # Normalize so that the integer part is 1.xxxxx
        while (mantissa_val >> frac_bits) == 0:
            mantissa_val <<= 1
            exponent_val -= 1

        while (mantissa_val >> (frac_bits + 1)) > 0:
            mantissa_val >>= 1
            exponent_val += 1

        # Strip implicit leading 1 for Float mantissa
        mantissa_field = mantissa_val & ((1 << frac_bits) - 1)
        
        # Truncate mantissa to 23 bits
        current_width = max(1, mantissa_field.bit_length())
        bits_to_truncate = max(0, current_width - 23)
        mantissa_field = mantissa_field >> bits_to_truncate

        # Construct Float
        return Float(sign=sign, mantissa=mantissa_field, exponent=exponent_val)

    return Op(
        spec=spec,
        impl=impl,
        args=[m, e],
        name="Q_E_encode_float",
    )

def OPTIMIZED_MAX_EXP4(e0: Node, 
                       e1: Node, 
                       e2: Node,
                       e3: Node,
                       bit_width: Node) -> Op:
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
    
    return Op(
        spec=spec,
        impl=impl,
        args=[e0, e1, e2, e3, bit_width],
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
        return Int(min(max(e.val, 0), 255))
    
    return Op(
        spec=spec,
        impl=impl,
        args=[e],
        name="EXP_OVERFLOW_UNDERFLOW_HANDLING"
    )
