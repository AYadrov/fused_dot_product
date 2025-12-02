from fused_dot_product.ast.AST import *
from fused_dot_product.config import *
from fused_dot_product.utils.operators import *
from fused_dot_product.utils.composites import *

from fused_dot_product.numtypes.UQ import *
from fused_dot_product.numtypes.BFloat16 import *
from fused_dot_product.numtypes.Q import Q_add_sign

import numpy as np


def Conventional(a0: Node, a1: Node, a2: Node, a3: Node,
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
    
    bf16_bias = Const(
        val=Q.from_int(BFloat16.exponent_bias),
        name="BFloat16.exponent_bias"
    )
    
    ########## EXPONENTS ###############
    
    # Step 1. Exponents add. Each E_p is shifted by bias twice!
    E_p = [uq_add(E_a[i], E_b[i]) for i in range(N)]  # UQ9.0
    
    # Step 2. Calculate maximum exponent
    E_m = MAX_EXPONENT4(*E_p)  # UQ9.0
    
    # Step 3. Calculate global shifts
    Sh_p = [uq_sub(E_m, E_p[i]) for i in range(N)]
    
    ########## MANTISSAS ###############
    
    # Step 1. Convert mantissas to UQ1.7
    M_a = [mantissa_add_implicit_bit(M_a[i]) for i in range(N)] # UQ1.7
    M_b = [mantissa_add_implicit_bit(M_b[i]) for i in range(N)] # UQ1.7
    
    # Step 2. Multiply mantissas
    M_p = [uq_mul(M_a[i], M_b[i]) for i in range(N)] # UQ2.14
    
    # Step 3. Shift mantissas
    # Make room for the right shift first, accuracy requirement is Wf
    M_p = [uq_resize(M_p[i], 2, Wf - 2) for i in range(N)]
    M_p = [uq_rshift(M_p[i], Sh_p[i]) for i in range(N)]
    
    # Step 4. Adjust sign for mantissas using xor operation
    S_p = [uq_xor(S_a[i], S_b[i]) for i in range(N)]
    
    M_p = [uq_to_q(M_p[i]) for i in range(N)] # Q3.{Wf - 2}
    M_p = [Q_add_sign(M_p[i], S_p[i]) for i in range(N)]
    
    # Step 5. Adder tree
    M_sum = ADDER_TREE4(*M_p) # Q5.{Wf - 2}
    
    ########## RESULT ##################
     # Subtract bias that is left! 
    E_m = uq_to_q(E_m)  # Q10.0
    E_m = q_sub(E_m, bf16_bias)  # Q11.0
    root = Q_E_encode_Float32(M_sum, E_m)
    
    return Composite(
            spec=spec,
            impl=root,
            sign=sign,
            args=[a0, a1, a2, a3,
                  b0, b1, b2, b3],
            name="Conventional")


if __name__ == '__main__':
    from tqdm import tqdm
    from time import time
    
    # Compile design
    a = [
        Var(name="a_0", signature=BFloat16T()),
        Var(name="a_1", signature=BFloat16T()),
        Var(name="a_2", signature=BFloat16T()),
        Var(name="a_3", signature=BFloat16T()),
    ]
    
    b = [
        Var(name="b_0", signature=BFloat16T()),
        Var(name="b_1", signature=BFloat16T()),
        Var(name="b_2", signature=BFloat16T()),
        Var(name="b_3", signature=BFloat16T()),
    ]
    
    design = Conventional(*a, *b)
    design.static_typecheck()
    design.print_tree(depth=1)
    
    # Test the design
    random_gen, exp_reshuffle = BFloat16.random_generator(seed=int(time()), shared_exponent_bits=5)
    for _ in tqdm(range(100), desc=f"Quick tests of the design"):
        exp_reshuffle()
        for i in range(N):
            a[i].load_val(random_gen())
            b[i].load_val(random_gen())
        tqdm.write(str(design.evaluate()[0]))

