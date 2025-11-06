from fused_dot_product.ast.AST import *
from fused_dot_product.config import *
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.composites import *

from fused_dot_product.types.Int import Sub, Int, Xor
from fused_dot_product.types.UQ import UQ_Mul, UQ_Resize, UQ_Rshift, UQ_to_Q
from fused_dot_product.types.BFloat16 import *
from fused_dot_product.types.Q import Q_add_sign


def Conventional(a0: Node, a1: Node, a2: Node, a3: Node, 
                 b0: Node, b1: Node, b2: Node, b3: Node) -> Composite:
                 
    def spec(a0: float, a1: float, a2: float, a3: float, 
             b0: float, b1: float, b2: float, b3: float) -> float:
        out = 0
        out += a0 * b0
        out += a1 * b1
        out += a2 * b2
        out += a3 * b3
        return out
   
    ########## CONSTANTS ###############
    
    Wf_ = Const(Int(val=Wf), "Wf")
    bf16_mantissa_bits = Const(Int(val=BFloat16.mantissa_bits), "BF16_MANTISSA_BITS")
    
    ########## EXPONENTS ###############
    
    # Step 1. Exponents add
    E_p = [
        exponents_adder(BF16_exponent(a0), BF16_exponent(b0)),
        exponents_adder(BF16_exponent(a1), BF16_exponent(b1)),
        exponents_adder(BF16_exponent(a2), BF16_exponent(b2)),
        exponents_adder(BF16_exponent(a3), BF16_exponent(b3)),
    ]
    
    # UNDERFLOW/OVERFLOW
    E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(E_p[i]) for i in range(N)]
    
    # Step 2. Calculate maximum exponent
    E_m = MAX_EXPONENT4(*E_p)
    
    # Step 3. Calculate global shifts
    sh = [Sub(E_m, E_p[i]) for i in range(N)]
    
    ########## MANTISSAS ###############
    
    # Step 1. Convert mantissas to UQ1.7
    M_a = [
        BF16_mantissa_to_UQ(BF16_mantissa(a0)),
        BF16_mantissa_to_UQ(BF16_mantissa(a1)),
        BF16_mantissa_to_UQ(BF16_mantissa(a2)),
        BF16_mantissa_to_UQ(BF16_mantissa(a3)),
    ]
    
    M_b = [
        BF16_mantissa_to_UQ(BF16_mantissa(b0)),
        BF16_mantissa_to_UQ(BF16_mantissa(b1)),
        BF16_mantissa_to_UQ(BF16_mantissa(b2)),
        BF16_mantissa_to_UQ(BF16_mantissa(b3)),
    ]
    
    # Step 2. Multiply mantissas
    M_p = [UQ_Mul(M_a[i], M_b[i]) for i in range(N)] # UQ2.14
    
    # Step 3. Shift mantissas
    # Make room for the right shift first, accuracy requirement is Wf
    M_p = [UQ_Resize(M_p[i], Const(Int(2)), Sub(Wf_, Const(Int(2)))) for i in range(N)]
    M_p = [UQ_Rshift(M_p[i], sh[i]) for i in range(N)] # UQ2.{Wf - 2}
    
    # Step 4. Adjust sign for mantissas using xor operation
    # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
    S_p = [
        Xor(BF16_sign(a0), BF16_sign(b0)), \
        Xor(BF16_sign(a1), BF16_sign(b1)), \
        Xor(BF16_sign(a2), BF16_sign(b2)), \
        Xor(BF16_sign(a3), BF16_sign(b3)), \
    ]
    
    M_p = [UQ_to_Q(M_p[i]) for i in range(N)] # Q3.{Wf - 2}
    M_p = [Q_add_sign(M_p[i], S_p[i]) for i in range(N)]
    
    ########## ADDER TREE ##############
    
    M_sum = ADDER_TREE4(*M_p) # Q5.{Wf - 2}
    
    ########## RESULT ##################
    
    root = Q_E_encode_Float(M_sum, E_m)
    return Composite(
            spec=spec, \
            impl=root, \
            args=[a0, a1, a2, a3, \
                  b0, b1, b2, b3], \
            name="Conventional")

if __name__ == '__main__':
    a = [Var("a_0"), Var("a_1"), Var("a_2"), Var("a_3")]
    b = [Var("b_0"), Var("b_1"), Var("b_2"), Var("b_3")]
    
    design = Conventional(*a, *b)
    design.print_tree()
    
    random_gen = BFloat16.random_generator(seed=25, shared_exponent_bits=5)
    for i in range(N):
        a[i].load_val(random_gen())
        b[i].load_val(random_gen())
    
    print(design.evaluate())
