# Optimized many-fused floating-point dot-product unit from 
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

def optimized_dot_product(a, b):
    ########## DOT PRODUCT #############
    
    ########## EXPONENTS ###############
    
    # Step 1. Add exponents
    E_p = [a[i][1] + b[i][1] - BF16_BIAS for i in range(N)]
    
    # UNDERFLOW/OVERFLOW
    E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]
    
    for e in E_p:
        assert e.bit_length() <= BF16_EXPONENT_BITS + 1
    
    # Step 2. Take last inverted {s} bits of exponents for a local shift
    LOCAL_SHIFTS = [invert_bits(take_last_bits(e, s), s) for e in E_p]
     
    for sh, e in zip(LOCAL_SHIFTS, E_p):
        assert sh.bit_length() <= s
        assert sh >= 0
        assert invert_bits(e % 2**s, s) == sh
        assert (2**s - 1 - (e % 2**s)) == sh
    
    # Step 3. Take leading {9-s} bits for max exponent and a global shift
    LEADING_EXPONENTS = [e >> s for e in E_p]
    
    for e, old_e in zip(LEADING_EXPONENTS, E_p):
        assert e.bit_length() <= BF16_EXPONENT_BITS + 1 - s
        assert math.floor(old_e / (2**s)) == e
    
    # Step 4. Take max exponent
    MAX_EXP = OPTIMIZED_MAX_EXP(LEADING_EXPONENTS, BF16_EXPONENT_BITS + 1 - s)
    
    assert MAX_EXP == max(LEADING_EXPONENTS)
    assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1 - s
    
    # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
    GLOBAL_SHIFTS = [(MAX_EXP - LEADING_EXPONENTS[i]) * 2**s for i in range(N)]
    
    for gsh in GLOBAL_SHIFTS:
        assert gsh.bit_length() <= BF16_EXPONENT_BITS + 1
        assert gsh >= 0
    
    # Step 6. Append {s} 1s at the end of the max exponent for a normalization
    MAX_EXP = MAX_EXP * 2**s + (2**s - 1)
    
    assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1

    ########## MANTISSAS ###############

    # Step 1. Multiply mantissas multiplication FixedPoint
    M_p = [MxM2FXP(x[2], y[2]) for x, y in zip(a, b)]

    for m in M_p:
        assert m.n == 2 * BF16_MANTISSA_BITS and m.m == 2

    # Step 2. Locally shift mantissas by the inverted last {s} bits of E_p
    output_length = (2 * BF16_MANTISSA_BITS + 2) + (2**s - 1)
    M_p = [RIGHT_SHIFT(m, sh, output_length) for m, sh in zip(M_p, LOCAL_SHIFTS)]

    for m in M_p:
        assert m.n == output_length - 2 and m.m == 2

    # Step 3. Globally shift mantissas by GLOBAL_SHIFTS[i] amount
    output_length = Wf + 2**s - 1
    M_p = [RIGHT_SHIFT(x, shift, output_length) for x, shift in zip(M_p, GLOBAL_SHIFTS)]

    for m in M_p:
        assert m.n == output_length - 2 and m.m == 2

    # Step 4. Adjust signs using xor operation
    # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
    S_p = [x[0] ^ y[0] for x, y in zip(a, b)] 
    M_p = [FXP_ADD_SIGN(x, s) for x, s in zip(M_p, S_p)]

    for m in M_p:
        assert m.n == (Wf + (2**s - 1)) - 2
        assert m.m == 3

    ########## ADDER TREE ##############

    # Adder tree 
    # Output should have {Wf + Log2(N) + 2**s - 1 + 1(sign)} bits
    fx_sum = CARRY_SAVE_ADDER_TREE(M_p)

    assert float(fx_sum) == float(sum(M_p)), \
        f"Carry-save tree failed, {float(fx_sum)} != {float(sum(M_p))}"
    # Unfortunately, we are off by 2 bits with signed logic from the design
    assert fx_sum.n + fx_sum.m == Wf + (2**s - 1) + math.ceil(math.log2(N)) + 2

    ########## RESULT ##################

    res = FXP_E2float(fx_sum, MAX_EXP)
    return res
