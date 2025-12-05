from fused_dot_product.ast.AST import *
from fused_dot_product.config import *
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.composites import *
from fused_dot_product.designs.CSA import CSA_tree4

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
    
    def sign(a0: BFloat16T, a1: BFloat16T, a2: BFloat16T, a3: BFloat16T, 
             b0: BFloat16T, b1: BFloat16T, b2: BFloat16T, b3: BFloat16T) -> Float32T:
        return Float32T()
    
    def impl(a0: Node, a1: Node, a2: Node, a3: Node, 
             b0: Node, b1: Node, b2: Node, b3: Node) -> Node:
        ########## INPUT ###################
        
        S_a, M_a, E_a = [0] * N, [0] * N, [0] * N
        S_b, M_b, E_b = [0] * N, [0] * N, [0] * N
        
        S_a[0], M_a[0], E_a[0] = BF16_decode(a0)
        S_a[1], M_a[1], E_a[1] = BF16_decode(a1)
        S_a[2], M_a[2], E_a[2] = BF16_decode(a2)
        S_a[3], M_a[3], E_a[3] = BF16_decode(a3)
        
        S_b[0], M_b[0], E_b[0] = BF16_decode(b0)
        S_b[1], M_b[1], E_b[1] = BF16_decode(b1)
        S_b[2], M_b[2], E_b[2] = BF16_decode(b2)
        S_b[3], M_b[3], E_b[3] = BF16_decode(b3)
        
        ########## CONSTANTS ###############
        
        s_ = Const(
            val=UQ.from_int(s),
            name="s",
        )
        bf16_bias = Const(
            val=Q.from_int(BFloat16.exponent_bias),
            name="BFloat16.exponent_bias",
        )
        pow2s_sub1 = Const(
            val=UQ.from_int((1 << s) - 1),
            name="pow2s_sub1",
        )
        
        ########## EXPONENTS ###############
        
        # Step 1. Exponents add. Each E_p is shifted by bias twice!
        E_p = [uq_add(E_a[i], E_b[i]) for i in range(N)]
        
        # Step 2. Estimate local shifts
        trailing_bits = [uq_select(E_p[i], s-1, 0) for i in range(N)]
        L_shifts = [basic_invert(x=trailing_bits[i], out=trailing_bits[i].copy()) for i in range(N)]
        
        # Step 3. Take leading {9-s} bits for max exponent and a global shift
        E_lead = [uq_select(E_p[i], 8, s) for i in range(N)]
        
        # Step 4. Take max exponent
        E_m = OPTIMIZED_MAX_EXP4(*E_lead)
        
        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        G_shifts = [uq_sub(E_m, E_lead[i]) for i in range(N)]
        G_shifts = [uq_resize(G_shifts[i], 9, 0) for i in range(N)]
        G_shifts = [uq_lshift(G_shifts[i], s_) for i in range(N)]
        
        # Step 6. Append {s} 1s at the end of the max exponent for a normalization
        E_m = uq_resize(E_m, 9, 0)
        E_m = uq_lshift(E_m, s_)
        E_m = basic_or(x=E_m, y=pow2s_sub1, out=E_m.copy())
        
        ########## MANTISSAS ###############
        
        # Step 1. Convert mantissas to UQ1.7
        M_a = [mantissa_add_implicit_bit(M_a[i]) for i in range(N)] # UQ1.7
        M_b = [mantissa_add_implicit_bit(M_b[i]) for i in range(N)] # UQ1.7
        
        # Step 2. Multiply mantissas into UQ2.14
        M_p = [uq_mul(M_a[i], M_b[i]) for i in range(N)]
        
        # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
        # Make room for the right shift, UQ2.14 + (2**s - 1)
        M_p = [uq_resize(M_p[i], 2, 14 + 2**s - 1) for i in range(N)]
        M_p = [uq_rshift(M_p[i], L_shifts[i]) for i in range(N)]
        
        # Step 4. Globally shift mantissas by G_shifts[i] amount
        # Make room for the right shift
        M_p = [uq_resize(M_p[i], 2, Wf - 2 + 2**s - 1) for i in range(N)]  # UQ2.{Wf + (2**s - 1) - 2}
        M_p = [uq_rshift(M_p[i], G_shifts[i]) for i in range(N)]  # UQ2.{Wf + (2**s - 1) - 2}
        
        # Step 5. Adjust signs using xor operation
        S_p = [basic_xor(x=S_a[i], y=S_b[i], out=S_a[i].copy()) for i in range(N)]
        M_p = [uq_to_q(M_p[i]) for i in range(N)]  # Q3.{Wf - 2 + (2**s - 1)}
        M_p = [q_add_sign(M_p[i], S_p[i]) for i in range(N)]
        
        # Step 6. Adder Tree
        M_sum = CSA_tree4(*M_p) # Q6.{Wf + (2**s - 1) - 2}
        
        ########## RESULT ##################
        E_m = uq_to_q(E_m)  # Q10.0
        E_m = q_sub(E_m, bf16_bias)  # Q11.0
        
        root = Q_E_encode_Float32(M_sum, E_m)
        return root
    
    return Composite(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[a0, a1, a2, a3,
                  b0, b1, b2, b3],
            name="Optimized")


if __name__ == '__main__':
    from tqdm import tqdm
    from time import time

    # Compile design
    a = [
        Var(name="a_0", sign=BFloat16T()),
        Var(name="a_1", sign=BFloat16T()),
        Var(name="a_2", sign=BFloat16T()),
        Var(name="a_3", sign=BFloat16T()),
    ]
    
    b = [
        Var(name="b_0", sign=BFloat16T()),
        Var(name="b_1", sign=BFloat16T()),
        Var(name="b_2", sign=BFloat16T()),
        Var(name="b_3", sign=BFloat16T()),
    ]
    
    design = Optimized(*a, *b)
    design.static_typecheck()
    design.print_tree(depth=1)
    
    # Test the design
    random_gen, exp_reshuffle = BFloat16.random_generator(seed=0, shared_exponent_bits=5)
    for _ in tqdm(range(100), desc=f"Quick tests of the design"):
        exp_reshuffle()
        for i in range(N):
            a[i].load_val(random_gen())
            b[i].load_val(random_gen())
        tqdm.write(str(design.evaluate()))

