from fused_dot_product import *
from .encode_Float32 import *
from .common import *

import numpy as np

def Conventional(a0: Node, a1: Node, a2: Node, a3: Node,
                 b0: Node, b1: Node, b2: Node, b3: Node) -> Composite:
                 
    def spec(a0: Math, a1: Math, a2: Math, a3: Math,
                    b0: Math, b1: Math, b2: Math, b3: Math, asserts):
        return a0 * b0 + a1 * b1 + a2 * b2 + a3 * b3
    
    def sign(a0: BFloat16T, a1: BFloat16T, a2: BFloat16T, a3: BFloat16T,
             b0: BFloat16T, b1: BFloat16T, b2: BFloat16T, b3: BFloat16T) -> Float32T:
        return Float32T()
    
    def impl(a0: Node, a1: Node, a2: Node, a3: Node,
             b0: Node, b1: Node, b2: Node, b3: Node) -> Node:
        ########## INPUT ###################
        
        S_a, M_a, E_a = [0] * N, [0] * N, [0] * N
        S_b, M_b, E_b = [0] * N, [0] * N, [0] * N
        
        S_a[0], M_a[0], E_a[0] = bf16_decode(a0)
        S_a[1], M_a[1], E_a[1] = bf16_decode(a1)
        S_a[2], M_a[2], E_a[2] = bf16_decode(a2)
        S_a[3], M_a[3], E_a[3] = bf16_decode(a3)
        
        S_b[0], M_b[0], E_b[0] = bf16_decode(b0)
        S_b[1], M_b[1], E_b[1] = bf16_decode(b1)
        S_b[2], M_b[2], E_b[2] = bf16_decode(b2)
        S_b[3], M_b[3], E_b[3] = bf16_decode(b3)
        
        ########## CONSTANTS ###############
        
        bf16_bias = Const(
            val=Q.from_int(BFloat16.exponent_bias),
            name="BFloat16.exponent_bias",
        )
        
        ########## EXPONENTS ###############
        
        # Step 1. Exponents add. Each E_p is shifted by bias twice!
        E_p = [uq_add(E_a[i], E_b[i]) for i in range(N)]
        
        # Step 2. Calculate maximum exponent
        E_m = uq_max(uq_max(E_p[0], E_p[1]), uq_max(E_p[2], E_p[3]))
        
        # Step 3. Calculate global shifts
        Sh_p = [uq_sub(E_m, E_p[i]) for i in range(N)]
        
        ########## MANTISSAS ###############
        
        # Step 1. Convert mantissas to UQ1.7
        M_a = [mantissa_add_implicit_bit(M_a[i]) for i in range(N)]
        M_b = [mantissa_add_implicit_bit(M_b[i]) for i in range(N)]
        
        # Step 2. Multiply mantissas
        M_p = [uq_mul(M_a[i], M_b[i]) for i in range(N)]
        
        # Step 3. Shift mantissas
        # Make room for the right shift first, accuracy requirement is Wf
        M_p_resized = [uq_resize(M_p[i], 2, Wf - 2) for i in range(N)]
        
        M_p_shifted = [uq_rshift(M_p_resized[i], Sh_p[i]) for i in range(N)]
        
        # Step 4. Adjust sign for mantissas using xor operation
        S_p = [sign_xor(S_a[i], S_b[i]) for i in range(N)]
        
        M_p_q = [uq_to_q(M_p_shifted[i]) for i in range(N)]
        
        M_p_q = [q_add_sign(M_p_q[i], S_p[i]) for i in range(N)]
        
        # Step 5. Adder tree
        M_sum = q_add(
            q_add(M_p_q[0], M_p_q[1]),
            q_add(M_p_q[2], M_p_q[3]),
        )
        
        ########## RESULT ##################
         # Subtract bias that is left!
        E_m_q = uq_to_q(E_m)
        
        E_m_q_biased = q_sub(E_m_q, bf16_bias)
        
        return encode_Float32(M_sum, E_m_q_biased)
    
    return Composite(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[a0, a1, a2, a3,
                  b0, b1, b2, b3],
            name="Conventional")


if __name__ == '__main__':
    from time import time
    from pprint import pprint
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
    
    design = Conventional(*a, *b)
    design.print_tree(depth=1)
    report = design.check_spec()
    pprint(report)

