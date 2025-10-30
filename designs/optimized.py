from fused_dot_product.ast.AST import *
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.composites import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *


class Optimized:
    def __init__(self):
        super().__init__()
        self.free_vars = self.define_free_vars()
        self.root = self.build_tree()
        
    def define_free_vars(self):
        self.E_a = [Var("e_a_0"), Var("e_a_1"), Var("e_a_2"), Var("e_a_3")]
        self.E_b = [Var("e_b_0"), Var("e_b_1"), Var("e_b_2"), Var("e_b_3")]
        
        self.M_a = [Var("m_a_0"), Var("m_a_1"), Var("m_a_2"), Var("m_a_3")]
        self.M_b = [Var("m_b_0"), Var("m_b_1"), Var("m_b_2"), Var("m_b_3")]
        
        self.S_a = [Var("s_a_0"), Var("s_a_1"), Var("s_a_2"), Var("s_a_3")]
        self.S_b = [Var("s_b_0"), Var("s_b_1"), Var("s_b_2"), Var("s_b_3")]
        
        self.s = Var("s")
        self.Wf = Var("Wf")
        self.bf16_bias = Var("BF16_bias")
        self.bf16_exponent_bits = Var("BF16_exponent_bits")
        self.bf16_mantissa_bits = Var("BF16_mantissa_bits")
        
        return [self.S_a, self.M_a, self.E_a, self.S_b, self.M_b, self.E_b,
                self.s, self.Wf, self.bf16_bias, self.bf16_exponent_bits, self.bf16_mantissa_bits]
        
    def build_tree(self):
        ########## CONSTANTS ###############
        
        pow2s_sub1 = Sub(Lshift(1, self.s), 1)
        
        ########## EXPONENTS ###############
        
        # Step 1. Exponents add
        E_p = [exponents_adder(self.E_a[i], self.E_b[i]) for i in range(N)]
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(E_p[i]) for i in range(N)]
        
        # Step 2. Estimate local shifts
        L_shifts = [invert_bits(take_last_n_bits(E_p[i], self.s), self.s) for i in range(N)]
        
        # Step 3. Take leading {9-s} bits for max exponent and a global shift
        E_lead = [Rshift(E_p[i], self.s) for i in range(N)]
        
        # Step 4. Take max exponent
        E_max = OPTIMIZED_MAX_EXP4(
            *E_lead, 
            Sub(self.bf16_exponent_bits, self.s)
        )
        
        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        G_shifts = [Lshift(Sub(E_max, E_lead[i]), self.s) for i in range(N)]
        
        # Step 6. Append {s} 1s at the end of the max exponent for a normalization
        E_max = Add(Lshift(E_max, self.s), pow2s_sub1)
        
        # assert MAX_EXP.bit_length() <= BF16_EXPONENT_BITS + 1
        
        ########## MANTISSAS ###############
        
        # Step 1. Convert mantissas to UQ1.7
        M_a = [bf16_mantissa_to_UQ(self.M_a[i]) for i in range(N)] # UQ1.{BF16_mantissa_bits}
        M_b = [bf16_mantissa_to_UQ(self.M_b[i]) for i in range(N)] # UQ1.{BF16_mantissa_bits}
        mantissa_length = Add(1, self.bf16_mantissa_bits)
        
        # Step 2. Multiply mantissas into UQ2.14
        M_p = [Mul(M_a[i], M_b[i]) for i in range(N)] # UQ2.{BF16_mantissa_bits * 2}
        mantissa_length = Lshift(mantissa_length, 1)
        
        # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
        # Make room for the right shift
        extend_bits = pow2s_sub1
        M_p = [Lshift(M_p[i], extend_bits) for i in range(N)] # UQ2.{BF16_mantissa_bits * 2 + (2**s - 1)}
        M_p = [Rshift(M_p[i], L_shifts[i]) for i in range(N)] # UQ2.{BF16_mantissa_bits * 2 + (2**s - 1)}
        mantissa_length = Add(mantissa_length, extend_bits)
        
        # Step 4. Globally shift mantissas by G_shifts[i] amount
        # Make room for the right shift
        acc_req_after_global_shift = Add(self.Wf, pow2s_sub1)
        extend_bits = Sub(acc_req_after_global_shift, mantissa_length)
        
        M_p = [Lshift(M_p[i], extend_bits) for i in range(N)] # UQ2.{Wf + (2**s - 1) - 2}
        M_p = [Rshift(M_p[i], G_shifts[i]) for i in range(N)] # UQ2.{Wf + (2**s - 1) - 2}
        
        mantissa_length = Add(mantissa_length, extend_bits) # Wf + (2**s - 1)
        
        # Step 5. Adjust signs using xor operation
        S_p = [Xor(self.S_a[i], self.S_b[i]) for i in range(N)]
        
        M_p = [UQ_to_Q(M_p[i], S_p[i], mantissa_length) for i in range(N)] # Q3.{Wf + (2**s - 1) - 2}
        mantissa_length = Add(mantissa_length, 1) # Wf + (2**s - 1) + 1
        
        ########## ADDER TREE ##############
        
        # Adder tree
        M_sum = CSA_ADDER_TREE4(*M_p, mantissa_length) # Q6.{Wf + (2**s - 1) - 2}
        mantissa_length = Add(mantissa_length, 3) # Wf + (2**s - 1) + 4
        
        M_sum = Q_to_signed_UQ(M_sum, mantissa_length) # UQ5.{Wf + (2**s - 1) - 2}
        mantissa_length = Sub(mantissa_length, 1) # Wf + (2**s - 1) + 3
        
        ########## RESULT ##################
        
        fraction_bits = Sub(mantissa_length, 5) # Wf + (2**s - 1) - 2
        root = signed_UQ_E_to_float(M_sum, fraction_bits, E_max)
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
    design.root.print_tree()

