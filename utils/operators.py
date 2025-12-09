# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *

from fused_dot_product.numtypes.Q import *

import math
import numpy as np

########## CUSTOM OPERATORS ########

# TODO: loss of accuracy, NaNs
def Q_E_encode_Float32(m: Node, e: Node) -> Op:
    def sign(m: QT, e: QT) -> Float32T:
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
        impl=impl,
        sign=sign,
        args=[m, e],
        name="Q_E_encode_Float32",
    )

