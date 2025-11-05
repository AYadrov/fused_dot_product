from fused_dot_product.ast.AST import *
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.composites import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *


class Conventional:
    def __init__(self):
        self.free_vars = self.define_free_vars()
        self.root = self.build_tree()
    
    def define_free_vars(self):
        self.E_a = [Var("e_a_0"), Var("e_a_1"), Var("e_a_2"), Var("e_a_3")]
        self.E_b = [Var("e_b_0"), Var("e_b_1"), Var("e_b_2"), Var("e_b_3")]
        
        self.M_a = [Var("m_a_0"), Var("m_a_1"), Var("m_a_2"), Var("m_a_3")]
        self.M_b = [Var("m_b_0"), Var("m_b_1"), Var("m_b_2"), Var("m_b_3")]
        
        self.S_a = [Var("s_a_0"), Var("s_a_1"), Var("s_a_2"), Var("s_a_3")]
        self.S_b = [Var("s_b_0"), Var("s_b_1"), Var("s_b_2"), Var("s_b_3")]
        
        self.Wf = Const(Int(val=Wf), "Wf")
        self.bf16_mantissa_bits = Const(Int(val=BF16_MANTISSA_BITS), "BF16_MANTISSA_BITS")

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
        
        # Step 2. Multiply mantissas
        M_p = [UQ_Mul(M_a[i], M_b[i]) for i in range(N)] # UQ2.14
        
        # Step 3. Shift mantissas
        # Make room for the right shift first, accuracy requirement is Wf
        M_p = [UQ_Resize(M_p[i], Const(Int(2)), Sub(self.Wf, Const(Int(2)))) for i in range(N)]
        M_p = [UQ_Rshift(M_p[i], sh[i]) for i in range(N)] # UQ2.{Wf - 2}
        
        # Step 4. Adjust sign for mantissas using xor operation
        # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
        S_p = [Xor(self.S_a[i], self.S_b[i]) for i in range(N)]
        M_p = [UQ_to_Q(M_p[i]) for i in range(N)] # Q3.{Wf - 2}
        M_p = [Q_add_sign(M_p[i], S_p[i]) for i in range(N)]
        
        ########## ADDER TREE ##############
        
        M_sum = ADDER_TREE4(*M_p) # Q5.{Wf - 2}
        
        ########## RESULT ##################
        
        root = Q_E_encode_float(M_sum, E_m)
        return root
        
    def __call__(self, a, b):
        for i in range(N):
            s_a = Int(a[i][0], 1)
            e_a = Int(a[i][1], BF16_EXPONENT_BITS)
            m_a = Int(a[i][2], BF16_MANTISSA_BITS)
            
            s_b = Int(b[i][0], 1)
            e_b = Int(b[i][1], BF16_EXPONENT_BITS)
            m_b = Int(b[i][2], BF16_MANTISSA_BITS)
            
            self.S_a[i].load_val(s_a); self.E_a[i].load_val(e_a); self.M_a[i].load_val(m_a);
            self.S_b[i].load_val(s_b); self.E_b[i].load_val(e_b); self.M_b[i].load_val(m_b);
         
        return self.root.evaluate()

if __name__ == '__main__':
    import random
    random.seed(25)
    design = Conventional()
    design.root.print_tree()
    
    a, b = generate_BF16_2x4x1(5)
    fp_a = [S_E_M2float(x[0], x[1], x[2]) for x in a]
    fp_b = [S_E_M2float(x[0], x[1], x[2]) for x in b]
    
    print(design(a, b))
    print(unfused_dot_product(fp_a, fp_b))
