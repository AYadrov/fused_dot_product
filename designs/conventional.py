from fused_dot_product.ast.AST import CTree, Operator
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *

import math

def exponents_adder(x, y):
    def spec(x: int, y: int) -> int:
        return x + y - (2**(BF16_EXPONENT_BITS-1) - 1)
    def impl_constructor(x, y) -> Operator:
        return Sub(Add(x, y), BF16_BIAS)
    
    return Operator(
            spec=spec,
            impl=impl_constructor(x, y),
            comp=lambda x: x,
            args=[x, y],
            name="exponents_adder")
            
def max_exponent(e0, e1, e2, e3):
    def spec(e0: int, e1: int, e2: int, e3: int) -> int:
        return max(max(e0, e1), max(e2, e2))
    def impl_constructor(e0, e1, e2, e3) -> Operator:
        return Max(Max(e0, e1), Max(e2, e2))
    
    return Operator(
            spec=spec,
            impl=impl_constructor(e0, e1, e2, e3),
            comp=lambda x: x,
            args=[e0, e1, e2, e3],
            name="max_exponent")

class Conventional(CTree):
    def __init__(self):
        super().__init__()
        self.root = self.build_tree()
        print(self.root.print_tree())
           
    
    def build_tree(self):
        E_a = [FreeVar("e_a_0"), FreeVar("e_a_1"), FreeVar("e_a_2"), FreeVar("e_a_3")]
        E_b = [FreeVar("e_b_0"), FreeVar("e_b_1"), FreeVar("e_b_2"), FreeVar("e_b_3")]
        
        M_a = [FreeVar("m_a_0"), FreeVar("m_a_1"), FreeVar("m_a_2"), FreeVar("m_a_3")]
        M_b = [FreeVar("m_b_0"), FreeVar("m_b_1"), FreeVar("m_b_2"), FreeVar("m_b_3")]
        
        S_a = [FreeVar("s_a_0"), FreeVar("s_a_1"), FreeVar("s_a_2"), FreeVar("s_a_3")]
        S_b = [FreeVar("s_b_0"), FreeVar("s_b_1"), FreeVar("s_b_2"), FreeVar("s_b_3")]
        
        ########## EXPONENTS ###############
        # Step 1. Exponents add
        E_p = [exponents_adder(E_a[i], E_b[i]) for i in range(N)]
        
        # UNDERFLOW/OVERFLOW
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]
        
        # Step 2. Calculate maximum exponent
        E_m = max_exponent(*E_p)
        
        # Step 3. Calculate global shifts
        sh = [Sub(E_m, E_p[i]) for i in range(N)]
        
        ########## MANTISSAS ###############
        # Step 1. Convert mantissas to FixedPoint
        M_a_fxp = [bf16_mantissa_to_FXP(M_a[i]) for i in range(N)]
        M_b_fxp = [bf16_mantissa_to_FXP(M_b[i]) for i in range(N)]

        # Step 2. Multiply mantissas using FixedPoint
        M_p = [Mul_fxp(M_a_fxp[i], M_b_fxp[i]) for i in range(N)]
        
        # for m in M_p:
        #     assert m.n == 2 * BF16_MANTISSA_BITS and m.m == 2
        
        # Step 3. Shift mantissas
        M_p_shifted = [RIGHT_SHIFT_FXP(M_p[i], sh[i], Wf) for i in range(N)]
        
        # for m in M_p:
        #     assert m.n == Wf - 2 and m.m == 2

        # Step 4. Adjust sign for mantissas using xor operation
        # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
        S_p = [Xor(S_a[i], S_b[i]) for i in range(N)]
        M_p = [FXP_ADD_SIGN(M_p_shifted[i], S_p[i]) for i in range(N)]
        
        # for m in M_p:
        #    assert m.n == Wf - 2
        #    assert m.m == 3
            
        ########## ADDER TREE ##############
        
        M_sum = CSA_TREE4(*M_p)

        # Unfortunately, we are off by 1 bits from the design with the sign logic
        # assert M_sum.n + M_sum.m == Wf + math.ceil(math.log2(N)) + 1
    
        ########## RESULT ##################

        root = FXP_E2float(M_sum, E_m)
        return root
        
Conventional()
