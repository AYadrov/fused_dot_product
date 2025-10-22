from fused_dot_product.ast.AST  import CTree, Operator, FreeVar
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *



class Optimized(CTree):
    def __init__(self):
        super().__init__()
        self.free_vars = self.define_free_vars()
        self.root = self.build_tree()
        
    def define_free_vars(self):
        self.E_a = [FreeVar("e_a_0"), FreeVar("e_a_1"), FreeVar("e_a_2"), FreeVar("e_a_3")]
        self.E_b = [FreeVar("e_b_0"), FreeVar("e_b_1"), FreeVar("e_b_2"), FreeVar("e_b_3")]
        
        self.M_a = [FreeVar("m_a_0"), FreeVar("m_a_1"), FreeVar("m_a_2"), FreeVar("m_a_3")]
        self.M_b = [FreeVar("m_b_0"), FreeVar("m_b_1"), FreeVar("m_b_2"), FreeVar("m_b_3")]
        
        self.S_a = [FreeVar("s_a_0"), FreeVar("s_a_1"), FreeVar("s_a_2"), FreeVar("s_a_3")]
        self.S_b = [FreeVar("s_b_0"), FreeVar("s_b_1"), FreeVar("s_b_2"), FreeVar("s_b_3")]
        
        self.s = FreeVar("s")
        self.Wf = FreeVar("Wf")
        self.bf16_bias = FreeVar("BF16_bias")
        self.bf16_exponent_bits = FreeVar("BF16_exponent_bits")
        self.bf16_mantissa_bits = FreeVar("BF16_mantissa_bits")
        
        return [self.S_a, self.M_a, self.E_a, self.S_b, self.M_b, self.E_b,
                self.s, self.Wf, self.bf16_bias, self.bf16_exponent_bits, self.bf16_mantissa_bits]
    
    def build_tree(self):
        ########## EXPONENTS ###############
        # Step 1. Exponents add
        E_p = [exponents_adder(self.E_a[i], self.E_b[i]) for i in range(N)]
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(E_p[i]) for i in range(N)]

        # for e in E_p:
        #     assert e.bit_length() <= BF16_EXPONENT_BITS + 1

        # Step 2. Estimate local shifts
        L_shifts = [invert_bits(take_last_n_bits(E_p[i], self.s), self.s) for i in range(N)]

        # for sh, e in zip(LOCAL_SHIFTS, E_p):
        #     assert sh.bit_length() <= s
        #     assert sh >= 0
        
        # Step 3. Take leading {9-s} bits for max exponent and a global shift
        E_lead = [drop_last_n_bits(E_p[i], self.s) for i in range(N)]

        # Step 4. Take max exponent
        # TODO: maybe no need to add 1
        E_max = OPTIMIZED_MAX_EXP(
            *E_lead, 
            Sub(Add(self.bf16_exponent_bits, 1), self.s)
        )

        # assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1 - s

        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        G_shifts = [Lshift(Sub(E_max, E_lead[i]), self.s) for i in range(N)]

        # for gsh in GLOBAL_SHIFTS:
        #     assert gsh.bit_length() <= BF16_EXPONENT_BITS + 1
        #     assert gsh >= 0

        # Step 6. Append {s} 1s at the end of the max exponent for a normalization
        E_max = Add(Lshift(E_max, self.s), Sub(Lshift(1, self.s), 1))
    
        # assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1
    
        ########## MANTISSAS ###############
    
        # Step 1. Convert mantissas to FixedPoint
        M_a = [bf16_mantissa_to_FXP(self.M_a[i]) for i in range(N)]
        M_b = [bf16_mantissa_to_FXP(self.M_b[i]) for i in range(N)]
        
        # Step 2. Multiply mantissas using FixedPoint
        M_p = [Mul_fxp(M_a[i], M_b[i]) for i in range(N)]

        # for m in M_p:
        #     assert m.n == 2 * BF16_MANTISSA_BITS and m.m == 2

        # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
        output_length = Add(Mul(2, Add(self.bf16_mantissa_bits, 1)), Sub(Lshift(1, self.s), 1))
        M_p = [RIGHT_SHIFT_FXP(M_p[i], L_shifts[i], output_length) for i in range(N)]

        # for m in M_p:
        #     assert m.n == output_length - 2 and m.m == 2

        # Step 4. Globally shift mantissas by GLOBAL_SHIFTS[i] amount
        output_length = Add(self.Wf, Sub(Lshift(1, self.s), 1))
        M_p = [RIGHT_SHIFT_FXP(M_p[i], G_shifts[i], output_length) for i in range(N)]

        # for m in M_p:
        #     assert m.n == output_length - 2 and m.m == 2

        # Step 5. Adjust signs using xor operation
        # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
        S_p = [Xor(self.S_a[i], self.S_b[i]) for i in range(N)]
        M_p = [FXP_ADD_SIGN(M_p[i], S_p[i]) for i in range(N)]

        # for m in M_p:
        #     assert m.n == (Wf + (2**s - 1)) - 2
        #     assert m.m == 3

        ########## ADDER TREE ##############
    
        # Adder tree 
        # Output should have {Wf + Log2(N) + 2**s - 1 + 1(sign)} bits
        M_sum = CSA_TREE4(*M_p)

        # assert float(fx_sum) == float(sum(M_p)), \
        #     f"Carry-save tree failed, {float(fx_sum)} != {float(sum(M_p))}"
        # Unfortunately, we are off by 2 bits with signed logic from the design
        # assert fx_sum.n + fx_sum.m == Wf + (2**s - 1) + math.ceil(math.log2(N)) + 2

        ########## RESULT ##################

        root = FXP_E2float(M_sum, E_max)
        return root
        
    def __call__(self, a, b):
        for i in range(N):
            self.S_a[i].load_val(a[i][0]); self.E_a[i].load_val(a[i][1]); self.M_a[i].load_val(a[i][2]);
            self.S_b[i].load_val(b[i][0]); self.E_b[i].load_val(b[i][1]); self.M_b[i].load_val(b[i][2]);
        
        self.s.load_val(s)
        self.Wf.load_val(Wf)
        self.bf16_bias.load_val(BF16_BIAS)
        self.bf16_exponent_bits.load_val(BF16_EXPONENT_BITS)
        self.bf16_mantissa_bits.load_val(BF16_MANTISSA_BITS)
        
        return self.root.evaluate()
        
if __name__ == '__main__':
    design = Optimized()
    design.print_tree()
    print("Depth =", design.depth())
    print("Critical path cost =", design.critical_path_cost())
