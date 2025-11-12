from fused_dot_product.ast.AST import *
from fused_dot_product.config import *
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.composites import *

from fused_dot_product.numtypes.Int import *
from fused_dot_product.numtypes.UQ import *
from fused_dot_product.numtypes.BFloat16 import *
from fused_dot_product.numtypes.Q import *

import numpy as np

def Optimized(a0: Node, a1: Node, a2: Node, a3: Node, 
              b0: Node, b1: Node, b2: Node, b3: Node) -> Composite:
    
    def spec(a0: float, a1: float, a2: float, a3: float, 
             b0: float, b1: float, b2: float, b3: float) -> float:
        out = 0
        out += a0 * b0
        out += a1 * b1
        out += a2 * b2
        out += a3 * b3
        return float(np.float32(out))
    
    ########## INPUT ###################
    
    S_a = [
        BF16_sign(a0),
        BF16_sign(a1),
        BF16_sign(a2),
        BF16_sign(a3),
    ]
    
    S_b = [
        BF16_sign(b0),
        BF16_sign(b1),
        BF16_sign(b2),
        BF16_sign(b3),
    ]
    
    E_a = [
        BF16_exponent(a0),
        BF16_exponent(a1),
        BF16_exponent(a2),
        BF16_exponent(a3),
    ]
    
    E_b = [
        BF16_exponent(b0),
        BF16_exponent(b1),
        BF16_exponent(b2),
        BF16_exponent(b3),
    ]
    
    M_a = [
        BF16_mantissa(a0),
        BF16_mantissa(a1),
        BF16_mantissa(a2),
        BF16_mantissa(a3),
    ]
    
    M_b = [
        BF16_mantissa(b0),
        BF16_mantissa(b1),
        BF16_mantissa(b2),
        BF16_mantissa(b3),
    ]
    
    ########## CONSTANTS ###############
    
    Wf_ = Const(Int(val=Wf), "Wf")
    s_ = Const(Int(val=s), "s")
    pow2s_sub1 = Sub(Lshift(Const(Int(1)), s_), Const(Int(1)))
    
    ########## EXPONENTS ###############
    
    # Step 1. Exponents add
    E_p = [exponents_adder(E_a[i], E_b[i]) for i in range(N)]
    
    # Step 2. Estimate local shifts
    L_shifts = [invert_bits(take_last_n_bits(E_p[i], s_), s_) for i in range(N)]
    
    # Step 3. Take leading {9-s} bits for max exponent and a global shift
    E_lead = [Rshift(E_p[i], s_) for i in range(N)]
    
    # Step 4. Take max exponent
    E_m = OPTIMIZED_MAX_EXP4(*E_lead)
    
    # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
    G_shifts = [Lshift(Sub(E_m, E_lead[i]), s_) for i in range(N)]
    
    # Step 6. Append {s} 1s at the end of the max exponent for a normalization
    E_m = Add(Lshift(E_m, s_), pow2s_sub1)
    
    ########## MANTISSAS ###############
    
    # Step 1. Convert mantissas to UQ1.7
    M_a = [BF16_mantissa_to_UQ(M_a[i]) for i in range(N)] # UQ1.7
    M_b = [BF16_mantissa_to_UQ(M_b[i]) for i in range(N)] # UQ1.7
    
    # Step 2. Multiply mantissas into UQ2.14
    M_p = [UQ_Mul(M_a[i], M_b[i]) for i in range(N)]
    
    # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
    # Make room for the right shift, UQ2.14 + (2**s - 1)
    extend_bits = pow2s_sub1
    
    M_p = [UQ_Resize(M_p[i], Const(Int(2)), Add(Const(Int(14)), extend_bits)) for i in range(N)]
    M_p = [UQ_Rshift(M_p[i], L_shifts[i]) for i in range(N)]
    
    # Step 4. Globally shift mantissas by G_shifts[i] amount
    # Make room for the right shift
    acc_req = Sub(Add(Wf_, pow2s_sub1), Const(Int(2)))
    
    M_p = [UQ_Resize(M_p[i], Const(Int(2)), acc_req) for i in range(N)] # UQ2.{Wf + (2**s - 1) - 2}
    M_p = [UQ_Rshift(M_p[i], G_shifts[i]) for i in range(N)] # UQ2.{Wf + (2**s - 1) - 2}
    
    # Step 5. Adjust signs using xor operation
    S_p = [Xor(S_a[i], S_b[i]) for i in range(N)]
    M_p = [UQ_to_Q(M_p[i]) for i in range(N)] # Q3.{Wf - 2}
    M_p = [Q_add_sign(M_p[i], S_p[i]) for i in range(N)]
    
    # Step 6. Adder Tree
    
    # Adder tree
    M_sum = CSA_ADDER_TREE4(*M_p) # Q6.{Wf + (2**s - 1) - 2}
    
    root = Q_E_encode_Float(M_sum, E_m)
    
    return Composite(
            spec=spec,
            impl=root,
            args=[a0, a1, a2, a3,
                  b0, b1, b2, b3],
            name="Optimized")

        
if __name__ == '__main__':
    from tqdm import tqdm
    import time

    # Compile design
    a = [Var("a_0"), Var("a_1"), Var("a_2"), Var("a_3")]
    b = [Var("b_0"), Var("b_1"), Var("b_2"), Var("b_3")]
    design = Optimized(*a, *b)
    design.print_tree(depth=1)
    
    # Test the design
    random_gen, exp_reshuffle = BFloat16.random_generator(seed=int(time.time()), shared_exponent_bits=5)
    for _ in tqdm(range(100), desc=f"Quick tests of the design"):
        exp_reshuffle()
        for i in range(N):
            a[i].load_val(random_gen())
            b[i].load_val(random_gen())
        design.evaluate()
