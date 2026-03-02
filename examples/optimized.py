from fused_dot_product import *
from .encode_Float32 import *
from .CSA import CSA_tree4
from .common import *
from .max_exponent import *

import numpy as np

def _est_global_shift(E_max: Node, E_p: Node, s: int) -> Primitive:
    def spec(E_max, E_p, asserts):
        return (E_max + (- E_p)) * Math.exp2(Math.lit(s))
    
    def sign(E_max: UQT, E_p: UQT) -> UQT:
        return UQT(E_max.int_bits + s, 0)
    
    def impl(E_max: Node, E_p: Node) -> Node:
        # out = UQ(E_max.int_bits + s, E_max.frac_bits)
        out_int_bits = uq_add(uq_int_bits(E_max), Const(UQ.from_int(s)))
        out_frac_bits = uq_frac_bits(E_max)
        out = uq_alloc(out_int_bits, out_frac_bits)
        
        return basic_concat(
            x=uq_sub(E_max, E_p),  # In theory produces UQ<7,0>, in practice UQ<8,0> (can be neglected)
            y=Const(UQ(0, s, 0)),
            out=out,
        )
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[E_max, E_p],
        name="_est_global_shift")


def _est_local_shift(E_trail: Node) -> Primitive:
    E_trail_width = E_trail.node_type.total_bits()
    
    def spec(x, asserts):
        return (Math.exp2(Math.lit(E_trail_width)) + (- Math.lit(1))) + (- x)
    
    def sign(E_trail: UQT) -> UQT:
        return E_trail
    
    def impl(E_trail: Node) -> Node:
        out = basic_invert(x=E_trail, out=E_trail.copy())
        return out
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[E_trail],
        name="_est_local_shift")

# xxx. -> xxx11.
def _prepend_ones(x: Node, s: int) -> Primitive:
    def spec(x, asserts):
        return x * Math.exp2(Math.lit(s)) + (Math.exp2(Math.lit(s)) + (- Math.lit(1)))
    
    def sign(x: UQT) -> UQT:
        return UQT(x.int_bits + s, 0)
    
    def impl(x: Node) -> Node:
        # out = UQ(E_max.int_bits + s, E_max.frac_bits)
        out_int_bits = uq_add(uq_int_bits(x), Const(UQ.from_int(s)))
        out_frac_bits = uq_frac_bits(x)
        out = uq_alloc(out_int_bits, out_frac_bits)
        
        return basic_concat(
            x=x,
            y=Const(UQ.from_int((1 << s) - 1)),
            out=out,
        )
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="_prepend_ones")


def Optimized(a0: Node, a1: Node, a2: Node, a3: Node,
              b0: Node, b1: Node, b2: Node, b3: Node) -> Composite:
    
    def spec(a0: Math, a1: Math, a2: Math, a3: Math,
             b0: Math, b1: Math, b2: Math, b3: Math, asserts):
        return a0 * b0 + a1 * b1 + a2 * b2 + a3 * b3
    
    def sign(a0: BFloat16T, a1: BFloat16T, a2: BFloat16T, a3: BFloat16T,
             b0: BFloat16T, b1: BFloat16T, b2: BFloat16T, b3: BFloat16T) -> Float32T:
        return Float32T()
    
    def impl(a0: Node, a1: Node, a2: Node, a3: Node,
             b0: Node, b1: Node, b2: Node, b3: Node) -> Node:
        
        ############## INPUT ###############
        
        S_a, M_a, E_a = [0] * N, [0] * N, [0] * N
        S_b, M_b, E_b = [0] * N, [0] * N, [0] * N
        
        E_lead, E_trail = [0] * N, [0] * N
        
        S_a[0], M_a[0], E_a[0] = bf16_decode(a0)
        S_a[1], M_a[1], E_a[1] = bf16_decode(a1)
        S_a[2], M_a[2], E_a[2] = bf16_decode(a2)
        S_a[3], M_a[3], E_a[3] = bf16_decode(a3)
        
        S_b[0], M_b[0], E_b[0] = bf16_decode(b0)
        S_b[1], M_b[1], E_b[1] = bf16_decode(b1)
        S_b[2], M_b[2], E_b[2] = bf16_decode(b2)
        S_b[3], M_b[3], E_b[3] = bf16_decode(b3)
        
        ############ CONSTANTS #############
        
        bf16_bias = Const(
            val=Q.from_int(BFloat16.exponent_bias),
            name="BFloat16.exponent_bias",
        )
        
        ############ EXPONENTS #############
        
        # Step 1. Exponents add. Each E_p is shifted by bias twice!
        E_p = [uq_add(E_a[i], E_b[i]) for i in range(N)]
        
        for i in range(N):
            E_trail[i], E_lead[i] = uq_split(E_p[i], s)
        
        # Step 2. Estimate local shifts
        L_shifts = [_est_local_shift(E_trail[i]) for i in range(N)]
        
        # Step 4. Take max exponent
        E_m = OPTIMIZED_MAX_EXP4(*E_lead)
        
        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        G_shifts = [_est_global_shift(E_m, E_lead[i], s) for i in range(N)]
        
        ############# MANTISSAS ############
        
        # Step 1. Convert mantissas to UQ1.7
        M_a = [mantissa_add_implicit_bit(M_a[i]) for i in range(N)]
        M_b = [mantissa_add_implicit_bit(M_b[i]) for i in range(N)]
        
        # Step 2. Multiply mantissas into UQ2.14
        M_p = [uq_mul(M_a[i], M_b[i]) for i in range(N)]
        
        # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
        # Make room for the right shift
        M_p = [uq_resize(M_p[i], 2, 14 + 2**s - 1) for i in range(N)]
        
        M_p = [uq_rshift(M_p[i], L_shifts[i]) for i in range(N)]
        
        # Step 4. Globally shift mantissas by G_shifts[i] amount
        # Make room for the right shift
        M_p = [uq_resize(M_p[i], 2, Wf - 2 + 2**s - 1) for i in range(N)]
        
        M_p = [uq_rshift(M_p[i], G_shifts[i]) for i in range(N)]
        
        # Step 5. Adjust signs using xor operation
        S_p = [sign_xor(S_a[i], S_b[i]) for i in range(N)]
        
        M_p = [uq_to_q(M_p[i]) for i in range(N)]
        
        M_p = [q_add_sign(M_p[i], S_p[i]) for i in range(N)]
        
        # Step 6. Adder Tree
        M_sum = CSA_tree4(*M_p)
        
        ############# RESULT ###############
        # Append {s} 1s at the end of the max exponent for a normalization
        E_m = _prepend_ones(E_m, s)
        
        # Subtract bias since E_m is biased twice
        E_m = uq_to_q(E_m)
        
        E_m = q_sub(E_m, bf16_bias)
        
        root = encode_Float32(M_sum, E_m)
        return root
    
    return Composite(
            spec=spec,
            impl=impl,
            sign=sign,
            args=[a0, a1, a2, a3,
                  b0, b1, b2, b3],
            name="Optimized")


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
    
    design = Optimized(*a, *b)
    design.print_tree(depth=1)
    report = design.check_spec()
    pprint(report)

