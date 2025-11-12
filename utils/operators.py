# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *

from fused_dot_product.numtypes.Int import *
from fused_dot_product.numtypes.Float import *
from fused_dot_product.numtypes.Q import *

import math
import numpy as np

########## CUSTOM OPERATORS ########

# TODO: loss of accuracy, NaNs
def Q_E_encode_Float(m: Node, e: Node) -> Op:
    def spec(m: float, e: int) -> float:
        """Mathematical reference implementation."""
        return float(np.float32(m * (2.0 ** (e - Float.exponent_bias))))

    # implementation matches spec; can differ if optimized later
    def impl(m: Q, e: Int) -> Float:
        
        def normalize_to_1_xxx(m, e, frac_bits):
            # Normalize so that mantissa is 1.xxxxx
            while (m >> frac_bits) == 0:
                m <<= 1
                e -= 1
            
            while (m >> (frac_bits + 1)) != 0:
                m >>= 1
                e += 1
            return m, e
        
        frac_bits = m.frac_bits
        total_bits = m.int_bits + frac_bits
        
        sign = m.sign_bit()
        if sign:
            m = m.negate()
        mantissa = m.val
        exponent = e.val
        
        # 0.0 * 2^e = 0.0
        if mantissa == 0:
            return Float.nZero() if sign == 1 else Float.Zero()
        
        mantissa, exponent = normalize_to_1_xxx(mantissa, exponent, frac_bits)
        
        # Infinity
        if exponent >= Float.inf_code:
            return Float.nInf() if sign == 1 else Float.Inf()
        
        # Subnormal/zero
        elif exponent <= 0:
            # Shifting to 0.00000xxxx until exponent is 1 (subnormal)
            while (mantissa != 0) and exponent < 1:
                mantissa >>= 1
                exponent += 1
            
            # Zero
            if mantissa == 0:
                return Float.nZero() if sign == 1 else Float.Zero()
            
            # Subnormal
            else:
                mantissa = round_to_the_nearest_even(mantissa, frac_bits, Float.mantissa_bits)
                
                # Handle rounding overflow
                if mantissa >> Float.mantissa_bits:
                    # Normal (rare case), drop implicit bit, exponent = 1
                    mantissa = mask(mantissa, Float.mantissa_bits)
                    return Float(sign, mantissa, exponent)
                else:
                    return Float(sign, mantissa, Float.sub_code) # Subnormal
        
        # Normal value
        else:
            # Strip implicit leading 1 for Float mantissa
            mantissa = mask(mantissa, frac_bits)
            mantissa = round_to_the_nearest_even(mantissa, frac_bits, Float.mantissa_bits)
            
            # Handle rounding overflow
            if mantissa >> Float.mantissa_bits:
                mantissa = mask(mantissa, Float.mantissa_bits)
                exponent += 1
                # Infinity
                if exponent >= Float.inf_code:
                    return Float.nInf() if sign == 1 else Float.Inf()
            
            return Float(sign=sign, mantissa=mantissa, exponent=exponent)
    
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


