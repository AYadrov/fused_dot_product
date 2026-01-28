from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.utils.composites import *
from designs.encode_Float32 import *
from designs.CSA import CSA_tree4
from fused_dot_product.numtypes.UQ import *
from fused_dot_product.numtypes.UQ import _uq_alloc
from fused_dot_product.numtypes.BFloat16 import *
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.Bool import *

import numpy as np


def _est_global_shift(E_max: Node, E_p: Node, s: int) -> Primitive:
    def spec(E_max: float, E_p: float, out: float):
        return (E_max - E_p) * 2**s == out
    
    def sign(E_max: UQT, E_p: UQT) -> UQT:
        return UQT(E_max.int_bits + s, 0)
    
    def impl(E_max: Node, E_p: Node) -> Node:
        # out = UQ(E_max.int_bits + s, E_max.frac_bits)
        out_int_bits = uq_add(uq_int_bits(E_max), Const(UQ.from_int(s)))
        out_frac_bits = uq_frac_bits(E_max)
        out = _uq_alloc(out_int_bits, out_frac_bits)
        
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


def _est_local_shift(E_p: Node, s: int) -> Primitive:
    def spec(x: float, out: float):
        return (2**s - 1) - (x % (2 ** s)) == out
    
    def sign(E_p: UQT) -> UQT:
        return UQT(s, 0)
    
    def impl(E_p: Node) -> Node:
        trailing_bits = uq_select(E_p, s-1, 0)
        out = basic_invert(x=trailing_bits, out=trailing_bits.copy())
        return out
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[E_p],
        name="_est_local_shift")

# xxx. -> xxx11.
def _prepend_ones(x: Node, s: int) -> Primitive:
    def spec(x: float, out: float):
        return x * 2**s + (2 ** s - 1) == out
    
    def sign(x: UQT) -> UQT:
        return UQT(x.int_bits + s, 0)
    
    def impl(x: Node) -> Node:
        # out = UQ(E_max.int_bits + s, E_max.frac_bits)
        out_int_bits = uq_add(uq_int_bits(x), Const(UQ.from_int(s)))
        out_frac_bits = uq_frac_bits(x)
        out = _uq_alloc(out_int_bits, out_frac_bits)
        
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
    
    def spec(a0: float, a1: float, a2: float, a3: float,
             b0: float, b1: float, b2: float, b3: float, out: float):
        res = 0
        res += a0 * b0
        res += a1 * b1
        res += a2 * b2
        res += a3 * b3
        return float(np.float32(res)) == out
    
    def sign(a0: BFloat16T, a1: BFloat16T, a2: BFloat16T, a3: BFloat16T,
             b0: BFloat16T, b1: BFloat16T, b2: BFloat16T, b3: BFloat16T) -> Float32T:
        return Float32T()
    
    def impl(a0: Node, a1: Node, a2: Node, a3: Node,
             b0: Node, b1: Node, b2: Node, b3: Node) -> Node:
        
        ############## INPUT ###############
        
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
        
        ############ CONSTANTS #############
        
        bf16_bias = Const(
            val=Q.from_int(BFloat16.exponent_bias),
            name="BFloat16.exponent_bias",
        )
        
        ############ EXPONENTS #############
        
        # Step 1. Exponents add. Each E_p is shifted by bias twice!
        E_p = [uq_add(E_a[i], E_b[i]) for i in range(N)]
        (
            [E_p[i].check(is_typeof(E_p[i], UQT(9, 0))) for i in range(N)],
            [E_p[i].check(uq_equal(E_p[i], uq_add(E_b[i], E_a[i]))) for i in range(N)]  # commutativity
        )
        
        # Step 2. Estimate local shifts
        L_shifts = [_est_local_shift(E_p[i], s) for i in range(N)]
        (
            [sh.check(is_typeof(sh, UQT(s, 0))) for sh in L_shifts]
        )
        
        # Step 3. Take leading {9-s} bits for max exponent and a global shift
        E_lead = [uq_select(E_p[i], 8, s) for i in range(N)]
        (
            [e.check(is_typeof(e, UQT(9-s, 0))) for e in E_lead]
        )
        
        # Step 4. Take max exponent
        E_m = OPTIMIZED_MAX_EXP4(*E_lead)
        (
            [E_m.check(is_typeof(E_m, UQT(9-s, 0)))],
            [E_m.check(uq_greater_or_equal(E_m, E_lead[i])) for i in range(N)]  # actually a max
        )
        
        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        G_shifts = [_est_global_shift(E_m, E_lead[i], s) for i in range(N)]
        (
            [sh.check(is_typeof(sh, UQT(9, 0))) for sh in G_shifts]
        )
        
        ############# MANTISSAS ############
        
        # Step 1. Convert mantissas to UQ1.7
        M_a = [mantissa_add_implicit_bit(M_a[i]) for i in range(N)]
        M_b = [mantissa_add_implicit_bit(M_b[i]) for i in range(N)]
        (
            [M_a[i].check(is_typeof(M_a[i], UQT(1, 7))) for i in range(N)],
            [M_b[i].check(is_typeof(M_b[i], UQT(1, 7))) for i in range(N)]
        )
        
        # Step 2. Multiply mantissas into UQ2.14
        M_p = [uq_mul(M_a[i], M_b[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, 14))) for i in range(N)]
        )
        
        # Step 3. Locally shift mantissas by the inverted last {s} bits of E_p
        # Make room for the right shift
        M_p = [uq_resize(M_p[i], 2, 14 + 2**s - 1) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, 14 + (2**s - 1)))) for i in range(N)]
        )
        
        M_p = [uq_rshift(M_p[i], L_shifts[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, 14 + (2**s - 1)))) for i in range(N)]
        )
        
        # Step 4. Globally shift mantissas by G_shifts[i] amount
        # Make room for the right shift
        M_p = [uq_resize(M_p[i], 2, Wf - 2 + 2**s - 1) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, Wf + (2**s - 1) - 2))) for i in range(N)]
        )
        
        M_p = [uq_rshift(M_p[i], G_shifts[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, Wf + (2**s - 1) - 2))) for i in range(N)]
        )
        
        # Step 5. Adjust signs using xor operation
        S_p = [sign_xor(S_a[i], S_b[i]) for i in range(N)]
        (
            [S_p[i].check(is_typeof(S_p[i], UQT(1, 0))) for i in range(N)]
        )
        
        M_p = [uq_to_q(M_p[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], QT(3, Wf + (2**s - 1) - 2))) for i in range(N)]
        )
        
        M_p = [q_add_sign(M_p[i], S_p[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], QT(3, Wf + (2**s - 1) - 2))) for i in range(N)]
        )
        
        # Step 6. Adder Tree
        M_sum = CSA_tree4(*M_p)
        (
            M_sum.check(is_typeof(M_sum, QT(6, Wf + (2**s - 1) - 2))),
            M_sum.check(
                q_equal(
                    M_sum, 
                    q_add(q_add(M_p[0], M_p[1]), q_add(M_p[2], M_p[3])),
                )
            )
        )
        
        ############# RESULT ###############
        # Append {s} 1s at the end of the max exponent for a normalization
        E_m = _prepend_ones(E_m, s)
        (
            E_m.check(is_typeof(E_m, UQT(9, 0)))
        )
        
        # Subtract bias since E_m is biased twice
        E_m = uq_to_q(E_m)
        (
            E_m.check(is_typeof(E_m, QT(10, 0)))
        )
        
        E_m = q_sub(E_m, bf16_bias)
        (
            E_m.check(is_typeof(E_m, QT(11, 0)))
        )
        
        root = encode_Float32(M_sum, E_m)
        (
            root.check(is_typeof(root, Float32T()))
        )
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
    
    # Test the design
    random_gen, exp_reshuffle = BFloat16.random_generator(seed=0, shared_exponent_bits=5)
    for _ in range(100):
        exp_reshuffle()
        for i in range(N):
            a[i].load_val(random_gen())
            b[i].load_val(random_gen())
        print(str(design.evaluate()))
