# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *

from fused_dot_product.numtypes.Q import *

import math
import numpy as np

########## CUSTOM OPERATORS ########

# TODO: loss of accuracy, NaNs
def Q_E_encode_Float32(m: Node, e: Node) -> Op:
    def spec(m: float, e: int) -> float:
        """Mathematical reference implementation."""
        return float(np.float32(m * (2.0 ** (e - Float32.exponent_bias))))
        
    def signature(m: QT, e: QT) -> Float32T:
        return Float32T()

    # implementation matches spec; can differ if optimized later
    def impl(m: Q, e: Q) -> Float32:
    
        # Extracts signed bits from a signed fixed point
        def twos_complement(e: Q):
            N = e.int_bits + e.frac_bits
            if e.val & (1 << (N - 1)):   # sign bit is 1
                return e.val - (1 << N)
            else:                        # sign bit is 0
                return  e.val
                
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
        exponent = twos_complement(e)
        
        # 0.0 * 2^e = 0.0
        if mantissa == 0:
            return Float32.nZero() if sign == 1 else Float32.Zero()
        
        mantissa, exponent = normalize_to_1_xxx(mantissa, exponent, frac_bits)
        
        # Infinity
        if exponent >= Float32.inf_code:
            return Float32.nInf() if sign == 1 else Float32.Inf()
        
        # Subnormal/zero
        elif exponent <= 0:
            # Shifting to 0.00000xxxx until exponent is 1 (subnormal)
            while (mantissa != 0) and exponent < 1:
                mantissa >>= 1
                exponent += 1
            
            # Zero
            if mantissa == 0:
                return Float32.nZero() if sign == 1 else Float32.Zero()
            
            # Subnormal
            else:
                mantissa = round_to_the_nearest_even(mantissa, frac_bits, Float32.mantissa_bits)
                
                # Handle rounding overflow
                if mantissa >> Float32.mantissa_bits:
                    # Normal (rare case), drop implicit bit, exponent = 1
                    mantissa = mask(mantissa, Float32.mantissa_bits)
                    return Float32(sign, mantissa, exponent)
                else:
                    return Float32(sign, mantissa, Float32.sub_code) # Subnormal
        
        # Normal value
        else:
            # Strip implicit leading 1 for Float32 mantissa
            mantissa = mask(mantissa, frac_bits)
            mantissa = round_to_the_nearest_even(mantissa, frac_bits, Float32.mantissa_bits)
            
            # Handle rounding overflow
            if mantissa >> Float32.mantissa_bits:
                mantissa = mask(mantissa, Float32.mantissa_bits)
                exponent += 1
                # Infinity
                if exponent >= Float32.inf_code:
                    return Float32.nInf() if sign == 1 else Float32.Inf()
            
            return Float32(sign=sign, mantissa=mantissa, exponent=exponent)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=signature,
        args=[m, e],
        name="Q_E_encode_Float32",
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
    def spec(e0, e1, e2, e3):
        return max(max(e0, e1), max(e2, e3))
    
    def signature(e0: UQT, e1: UQT, e2: UQT, e3: UQT) -> UQT:
        int_bits = max(max(e0.int_bits, e1.int_bits), max(e2.int_bits, e3.int_bits))
        frac_bits = max(max(e0.frac_bits, e1.frac_bits), max(e2.frac_bits, e3.frac_bits))
        return UQT(int_bits, frac_bits)
    
    def impl(e0: UQ, e1: UQ, e2: UQ, e3: UQ):
        int_bits = max(max(e0.int_bits, e1.int_bits), max(e2.int_bits, e3.int_bits))
        frac_bits = max(max(e0.frac_bits, e1.frac_bits), max(e2.frac_bits, e3.frac_bits))
        bit_width = int_bits + frac_bits
        
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
        
        return UQ(int(''.join(map(str, map(int, maxexp))), 2), int_bits, frac_bits)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=signature,
        args=[e0, e1, e2, e3],
        name="OPTIMIZED_MAX_EXP4"
    )

