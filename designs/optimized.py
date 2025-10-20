from fused_dot_product.ast.AST  import CTree, Operator
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.utils import *
import math


class Optimized(CTree):
    def __init__(self):
        super().__init__()

        # Operators for exponents
        self.exponents_adder = Operator(
                spec=lambda x, y: x + y - (2**(BF16_EXPONENT_BITS-1) - 1),
                impl=lambda x, y: x + y - BF16_BIAS)
        self.estimate_local_shift = Operator(
                spec=lambda e, s: (2**s - 1 - (e % 2**s)),
                impl=lambda e, s: invert_bits(take_last_bits(e, s), s))
        self.estimate_global_shift = Operator(
                spec=lambda x, y, s: (x - y) * 2**s,
                impl=lambda x, y, s: (x - y) * 2**s)
        self.get_leading_n_bits = Operator(
                spec=lambda e, n: math.floor(e / (2**s)),
                impl=lambda e, n: e >> n)
                
        self.max_exp = OPTIMIZED_MAX_EXP
        
        # Operators for mantissas
        self.mantissa2FXP = bf16_mantissa_to_FXP
        self.mantissas_mul = MxM2FXP
        self.right_shift = RIGHT_SHIFT
        self.add_sign_to_FXP = FXP_ADD_SIGN
        self.adder_tree = CARRY_SAVE_ADDER_TREE
        
        self.calculate_sign = Operator(
                spec=lambda x, y: 0 if x == y else 1,
                impl=lambda x, y: x ^ y)
        
        # Converting back to float
        self.to_float = FXP_E2float

    def __call__(self, a, b):
        ########## EXPONENTS ###############
        # Step 1. Exponents add
        E_p = [self.exponents_adder(a[i][1], b[i][1]) for i in range(N)]

        # UNDERFLOW/OVERFLOW
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]

        for e in E_p:
            assert e.bit_length() <= BF16_EXPONENT_BITS + 1

        # Step 2. Estimate local shifts
        LOCAL_SHIFTS = [self.estimate_local_shift(e, s) for e in E_p]

        for sh, e in zip(LOCAL_SHIFTS, E_p):
            assert sh.bit_length() <= s
            assert sh >= 0
        
        # Step 3. Take leading {9-s} bits for max exponent and a global shift
        LEADING_EXPONENTS = [self.get_leading_n_bits(e, s) for e in E_p]

        # Step 4. Take max exponent
        MAX_EXP = self.max_exp(LEADING_EXPONENTS, BF16_EXPONENT_BITS + 1 - s)

        assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1 - s

        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        GLOBAL_SHIFTS = [self.estimate_global_shift(MAX_EXP, LEADING_EXPONENTS[i], s) for i in range(N)]

        for gsh in GLOBAL_SHIFTS:
            assert gsh.bit_length() <= BF16_EXPONENT_BITS + 1
            assert gsh >= 0

        # Step 6. Append {s} 1s at the end of the max exponent for a normalization
        MAX_EXP = MAX_EXP * 2**s + (2**s - 1)
    
        assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1
    
        ########## MANTISSAS ###############
    
        # Step 1. Convert mantissas to FixedPoint
        M_a = [self.mantissa2FXP(x[2]) for x in a]
        M_b = [self.mantissa2FXP(x[2]) for x in b]

        # Step 2. Multiply mantissas using FixedPoint
        M_p = [self.mantissas_mul(x, y) for x, y in zip(M_a, M_b)]

        for m in M_p:
            assert m.n == 2 * BF16_MANTISSA_BITS and m.m == 2

        # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
        output_length = (2 * BF16_MANTISSA_BITS + 2) + (2**s - 1)
        M_p = [self.right_shift(m, sh, output_length) for m, sh in zip(M_p, LOCAL_SHIFTS)]

        for m in M_p:
            assert m.n == output_length - 2 and m.m == 2

        # Step 4. Globally shift mantissas by GLOBAL_SHIFTS[i] amount
        output_length = Wf + 2**s - 1
        M_p = [self.right_shift(x, shift, output_length) for x, shift in zip(M_p, GLOBAL_SHIFTS)]

        for m in M_p:
            assert m.n == output_length - 2 and m.m == 2

        # Step 5. Adjust signs using xor operation
        # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
        S_p = [self.calculate_sign(x[0], y[0]) for x, y in zip(a, b)] 
        M_p = [self.add_sign_to_FXP(x, s) for x, s in zip(M_p, S_p)]

        for m in M_p:
            assert m.n == (Wf + (2**s - 1)) - 2
            assert m.m == 3

        ########## ADDER TREE ##############
    
        # Adder tree 
        # Output should have {Wf + Log2(N) + 2**s - 1 + 1(sign)} bits
        fx_sum = self.adder_tree(M_p)

        assert float(fx_sum) == float(sum(M_p)), \
            f"Carry-save tree failed, {float(fx_sum)} != {float(sum(M_p))}"
        # Unfortunately, we are off by 2 bits with signed logic from the design
        assert fx_sum.n + fx_sum.m == Wf + (2**s - 1) + math.ceil(math.log2(N)) + 2

        ########## RESULT ##################

        res = FXP_E2float(fx_sum, MAX_EXP)
        return res
