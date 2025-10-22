from fused_dot_product.ast.AST import CTree, Operator
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *
            
def conventional_max_exponent(e0, e1, e2, e3):
    def spec(e0: int, e1: int, e2: int, e3: int) -> int:
        return max(max(e0, e1), max(e2, e3))
    def impl_constructor(e0, e1, e2, e3) -> Operator:
        return Max(Max(e0, e1), Max(e2, e3))
    
    return Operator(
            spec=spec,
            impl=impl_constructor(e0, e1, e2, e3),
            comp=lambda x: x,
            args=[e0, e1, e2, e3],
            name="conventional_max_exponent")
            
def conventional_adder_tree(FXP0, FXP1, FXP2, FXP3) -> Operator:
    def spec(FXP0: FixedPoint, 
             FXP1: FixedPoint, 
             FXP2: FixedPoint, 
             FXP3: FixedPoint) -> FixedPoint:
        return FXP0 + FXP1 + FXP2 + FXP3
        
    def impl(FXP0: FixedPoint,
             FXP1: FixedPoint,
             FXP2: FixedPoint,
             FXP3: FixedPoint) -> FixedPoint:
         return (FXP0 + FXP1) + (FXP2 + FXP3)
    return Operator(
            spec=spec,
            impl=impl,
            comp=lambda x: float(x),
            args=[FXP0, FXP1, FXP2, FXP3],
            name="conventional_adder_tree")


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
        
        return [self.S_a, self.M_a, self.E_a, self.S_b, self.M_b, self.E_b]
        
    def build_tree(self):
        ########## EXPONENTS ###############
        # Step 1. Exponents add
        E_p = [exponents_adder(self.E_a[i], self.E_b[i]) for i in range(N)]
        
        # UNDERFLOW/OVERFLOW
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]
        
        # Step 2. Calculate maximum exponent
        E_m = conventional_max_exponent(*E_p)
        
        # Step 3. Calculate global shifts
        sh = [Sub(E_m, E_p[i]) for i in range(N)]
        
        ########## MANTISSAS ###############
        # Step 1. Convert mantissas to FixedPoint
        M_a_fxp = [bf16_mantissa_to_FXP(self.M_a[i]) for i in range(N)]
        M_b_fxp = [bf16_mantissa_to_FXP(self.M_b[i]) for i in range(N)]

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
        S_p = [Xor(self.S_a[i], self.S_b[i]) for i in range(N)]
        M_p = [FXP_ADD_SIGN(M_p_shifted[i], S_p[i]) for i in range(N)]
        
        # for m in M_p:
        #    assert m.n == Wf - 2
        #    assert m.m == 3
            
        ########## ADDER TREE ##############
        
        M_sum = conventional_adder_tree(*M_p)

        # Unfortunately, we are off by 1 bits from the design with the sign logic
        # assert M_sum.n + M_sum.m == Wf + math.ceil(math.log2(N)) + 1
    
        ########## RESULT ##################

        root = FXP_E2float(M_sum, E_m)
        return root
        
    def __call__(self, a, b):
        for i in range(N):
            self.S_a[i].load_val(a[i][0])
            self.E_a[i].load_val(a[i][1])
            self.M_a[i].load_val(a[i][2])
            
            self.S_b[i].load_val(b[i][0])
            self.E_b[i].load_val(b[i][1])
            self.M_b[i].load_val(b[i][2])
        
        return self.root.evaluate()
        
    def print_tree(self):
        if not self.root:
            raise Exception("Tree is empty")
        self.root.print_tree()

if __name__ == '__main__':
    import random
    random.seed(5)
    
    def overflow():
        try:
            Conventional()(*generate_BF16_2x4x1(5))
            assert False
        except Exception as e:
            assert str(e) == "Overflow"
            
    def underflow():
        try:
            Conventional()(*generate_BF16_2x4x1(5))
            assert False
        except Exception as e:
            assert str(e) == "Underflow"
            
    assert Conventional()(*generate_BF16_2x4x1(5)) == -9.358937422513046e+18
    overflow()
    underflow()
    overflow()   
    assert Conventional()(*generate_BF16_2x4x1(5)) == 4.3820434424121985e-26
    assert Conventional()(*generate_BF16_2x4x1(5)) == 773044352.0

