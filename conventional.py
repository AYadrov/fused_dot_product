# Conventional many-fused floating-point dot-product unit from
# Optimized Fused Floating-Point Many-Term Dot-Product Hardware for Machine Learning Accelerators
# Himanshu Kaul et al.
#
# In this example, we are using dot product of 1x4 vectors
# [a1, a2, a3, a4] x [b1, b2, b3, b4] = a1*b1 + a2*b2 + a3*b3 + a4*b4
# a1*b1 + a2*b2 + a3*b3 + a4*b4 = ∑_i=[1,4] a_m_i * (2 ^ a_e_i) * b_m_i * (2 ^ b_e_i)

from config import *
from utils import *

import math
from fixedpoint import FixedPoint

def conventional_dot_product(a, b):
    ########## DOT PRODUCT #############
    
    ########## EXPONENTS ###############

    # Step 1. Exponents add
    E_p = [a[i][1] + b[i][1] - BF16_BIAS for i in range(N)]
    
    # UNDERFLOW/OVERFLOW
    E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]

    # Step 2. Calculate maximum exponent
    E_m = max(E_p)

    # Step 3. Calculate global shifts
    sh = [E_m - E_p[i] for i in range(N)]

    ########## MANTISSAS ###############
    # Step 1. Convert mantissas to FixedPoint
    M_a = [bf16_mantissa_to_FXP(x[2]) for x in a]
    M_b = [bf16_mantissa_to_FXP(x[2]) for x in b]

    # Step 2. Multiply mantissas using FixedPoint
    M_p = [MxM2FXP(x, y) for x, y in zip(M_a, M_b)]
    for m in M_p:
        assert m.n == 2 * BF16_MANTISSA_BITS and m.m == 2

    # Step 3. Shift mantissas
    M_p = [RIGHT_SHIFT(x, shift, Wf) for x, shift in zip(M_p, sh)]
    for m in M_p:
        assert m.n == Wf - 2 and m.m == 2

    # Step 4. Adjust sign for mantissas using xor operation
    # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
    S_p = [x[0] ^ y[0] for x, y in zip(a, b)]
    M_p = [FXP_ADD_SIGN(x, s) for x, s in zip(M_p, S_p)]
    
    for m in M_p:
        assert m.n == Wf - 2
        assert m.m == 3

    ########## ADDER TREE ############## 
   
    s1 = M_p[0] + M_p[1]
    s2 = M_p[2] + M_p[3]
    fx_sum = s1 + s2

    # Unfortunately, we are off by 1 bits from the design with the sign logic
    assert fx_sum.n + fx_sum.m == Wf + math.ceil(math.log2(N)) + 1
    
    ########## RESULT ##################

    res = FXP_E2float(fx_sum, E_m)
    return res
