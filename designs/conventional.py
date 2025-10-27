from fused_dot_product.ast.AST import CTree, Operator
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *


class Conventional(CTree):
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
        
        self.Wf = FreeVar("Wf")
        
        return [self.S_a, self.M_a, self.E_a, self.S_b, self.M_b, self.E_b, self.Wf]
    
    def build_tree(self):
        ########## EXPONENTS ###############
        # Step 1. Exponents add
        E_p = [exponents_adder(self.E_a[i], self.E_b[i]) for i in range(N)]
        
        # UNDERFLOW/OVERFLOW
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]
        
        # Step 2. Calculate maximum exponent
        E_m = MAX_EXPONENT4(*E_p)
        
        # Step 3. Calculate global shifts
        sh = [Sub(E_m, E_p[i]) for i in range(N)]
        
        ########## MANTISSAS ###############
        # Step 1. Convert mantissas to UQ
        M_a = [bf16_mantissa_to_UQ(self.M_a[i]) for i in range(N)] # UQ1.7
        M_b = [bf16_mantissa_to_UQ(self.M_b[i]) for i in range(N)] # UQ1.7
        mantissa_length = Add(1, BF16_MANTISSA_BITS) # 1 + 7 = 8

        # Step 2. Multiply mantissas
        M_p = [Mul(M_a[i], M_b[i]) for i in range(N)] # UQ2.14
        mantissa_length = Lshift(mantissa_length, 1) # 16
        
        # Step 3. Shift mantissas
        # Make room for the right shift first, accuracy requirement is Wf
        extend_bits = Sub(self.Wf, mantissa_length) # Wf - 16
        M_p = [Lshift(M_p[i], extend_bits) for i in range(N)]
        M_p = [Rshift(M_p[i], sh[i]) for i in range(N)] # UQ2.{Wf - 2}
        mantissa_length = self.Wf
        
        # Step 4. Adjust sign for mantissas using xor operation
        # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
        S_p = [Xor(self.S_a[i], self.S_b[i]) for i in range(N)]
        M_p = [UQ_to_Q(M_p[i], S_p[i], mantissa_length) for i in range(N)] # Q3.{Wf - 2}
        mantissa_length = Add(1, mantissa_length)
        
        ########## ADDER TREE ##############
        
        M_sum = ADDER_TREE4(*M_p, mantissa_length) # Q5.{Wf - 2}
        mantissa_length = Add(2, mantissa_length) # Wf + 3

        M_sum = Q_to_signed_UQ(M_sum, mantissa_length) # UQ4.{Wf - 2}
        mantissa_length = Sub(mantissa_length, 1) # Wf + 2
        
        ########## RESULT ################## 
       
        fraction_bits = Sub(self.Wf, 2)
        root = signed_UQ_E_to_float(M_sum, fraction_bits, E_m)
        return root
    
    def __call__(self, a, b):
        for i in range(N):
            self.S_a[i].load_val(a[i][0]); self.E_a[i].load_val(a[i][1]); self.M_a[i].load_val(a[i][2]);
            self.S_b[i].load_val(b[i][0]); self.E_b[i].load_val(b[i][1]); self.M_b[i].load_val(b[i][2]);
            
        self.Wf.load_val(Wf)
        
        return self.root.evaluate()

if __name__ == '__main__':
    design = Conventional()
    design.print_tree()
    print("Depth =", design.depth())
    print("Critical path cost =", design.critical_path_cost())

