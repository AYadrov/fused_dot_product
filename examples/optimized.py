from fused_dot_product import *
from .encode_Float32 import *
from .CSA import CSA_tree4
from .common import *
from .max_exponent import *

from cvc5.pythonic import FreshReal, FreshInt, Int2BV, Extract, BV2Int, IntVal, ToReal
import numpy as np

def _est_global_shift(E_max: Node, E_p: Node, s_: int) -> Primitive:
    def spec(prim, E_max, E_p, s):
        out = prim._spec_outputs(s)
        s.add((E_max - E_p) * 2**s_ == out)
        return out
    
    def sign(E_max: UQT, E_p: UQT) -> UQT:
        return UQT(E_max.int_bits + s_, 0)
    
    def impl(E_max: Node, E_p: Node) -> Node:
        # out = UQ(E_max.int_bits + s, E_max.frac_bits)
        out_int_bits = uq_add(uq_int_bits(E_max), Const(UQ.from_int(s_)))
        out_frac_bits = uq_frac_bits(E_max)
        out = uq_alloc(out_int_bits, out_frac_bits)
        
        return basic_concat(
            x=uq_sub(E_max, E_p),  # In theory produces UQ<7,0>, in practice UQ<8,0> (can be neglected)
            y=Const(UQ(0, s_, 0)),
            out=out,
        )
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[E_max, E_p],
        name="_est_global_shift")


def _est_local_shift(E_p: Node, s_: int) -> Primitive:
    def spec(prim, x, s):
        out = prim._spec_outputs(s)
        frac_bits = E_p.node_type.frac_bits
        total_bits = E_p.node_type.total_bits

        raw = FreshInt("raw")
        s.add(raw >= 0, raw <= (2**total_bits) - 1)
        s.add(x == ToReal(raw) / (2**frac_bits))
        s.add(out == ToReal(raw % 2**s_))
        return out
    
    def sign(E_p: UQT) -> UQT:
        return UQT(s_, 0)
    
    def impl(E_p: Node) -> Node:
        trailing_bits = uq_select(E_p, s_-1, 0)
        out = basic_invert(x=trailing_bits, out=trailing_bits.copy())
        return out
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[E_p],
        name="_est_local_shift")

# xxx. -> xxx11.
def _prepend_ones(x: Node, s_: int) -> Primitive:
    def spec(prim, x, s):
        out = prim._spec_outputs(s)
        s.add(x * 2**s_ + (2**s_ - 1) == out)
        return out
    
    def sign(x: UQT) -> UQT:
        return UQT(x.int_bits + s_, 0)
    
    def impl(x: Node) -> Node:
        # out = UQ(E_max.int_bits + s, E_max.frac_bits)
        out_int_bits = uq_add(uq_int_bits(x), Const(UQ.from_int(s_)))
        out_frac_bits = uq_frac_bits(x)
        out = uq_alloc(out_int_bits, out_frac_bits)
        
        return basic_concat(
            x=x,
            y=Const(UQ.from_int((1 << s_) - 1)),
            out=out,
        )
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="_prepend_ones")


def optimized_arithmetic_body(E_a: Node, E_b: Node, M_a: Node, M_b: Node) -> Composite:
    def spec(prim, E_a, E_b, M_a, M_b, s):
        M_p_q, E_m = prim._spec_outputs(s)
        n = len(E_a)
        
        E_p = [E_a[i] + E_b[i] for i in range(n)]
        
        E_m = E_p[0]
        for i in range(1, n):
            E_m = If(E_m >= E_p[i], E_m, E_p[i])
        E_m = ToInt(E_m) / 2**s_
        E_m = E_m * 2**s_ + 2**s_ - 1
        
        M_a = [(M_a[i] / (2 ** BFloat16.mantissa_bits)) + 1.0 for i in range(n)]
        M_b = [(M_b[i] / (2 ** BFloat16.mantissa_bits)) + 1.0 for i in range(n)]
        M_p = [M_a[i] * M_b[i] for i in range(n)]
        
        for i in range(n):
            s.add(M_p[i] == M_p_q[i] * 2 ** ToInt((E_m - E_p[i])))
        
        return (tuple(M_p_q), E_m)
    
    def impl(E_a: Node, E_b: Node, M_a: Node, M_b: Node) -> Node:
        ############ EXPONENTS #############
        
        # Step 1. Exponents add. Each E_p is shifted by bias twice!
        E_p = [uq_add(E_a[i], E_b[i]) for i in range(N)]
        (
            [E_p[i].check(is_typeof(E_p[i], UQT(9, 0))) for i in range(N)],
            [E_p[i].check(uq_equal(E_p[i], uq_add(E_b[i], E_a[i]))) for i in range(N)]  # commutativity
        )
        
        # Step 2. Estimate local shifts
        L_shifts = [_est_local_shift(E_p[i], s_) for i in range(N)]
        (
            [sh.check(is_typeof(sh, UQT(s_, 0))) for sh in L_shifts]
        )
        
        # Step 3. Take leading {9-s} bits for max exponent and a global shift
        E_lead = [uq_select(E_p[i], 8, s_) for i in range(N)]
        (
            [e.check(is_typeof(e, UQT(9-s_, 0))) for e in E_lead]
        )
        
        # Step 4. Take max exponent
        E_m = OPTIMIZED_MAX_EXP4(*E_lead)
        (
            [E_m.check(is_typeof(E_m, UQT(9-s_, 0)))],
            [E_m.check(uq_greater_or_equal(E_m, E_lead[i])) for i in range(N)]  # actually a max
        )
        
        # Step 5. Calculate global shifts as {(max_exp - exp) * 2**s}
        G_shifts = [_est_global_shift(E_m, E_lead[i], s_) for i in range(N)]
        (
            [sh.check(is_typeof(sh, UQT(9, 0))) for sh in G_shifts]
        )
        
        # Append {s} 1s at the end of the max exponent for a normalization
        E_m = _prepend_ones(E_m, s_)
        (
            E_m.check(is_typeof(E_m, UQT(9, 0)))
        )
        
        # Subtract bias since E_m is biased twice
        E_m = uq_to_q(E_m)
        (
            E_m.check(is_typeof(E_m, QT(10, 0)))
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
        M_p = [uq_resize(M_p[i], 2, 14 + 2**s_ - 1) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, 14 + (2**s_ - 1)))) for i in range(N)]
        )
        
        M_p = [uq_rshift(M_p[i], L_shifts[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, 14 + (2**s_ - 1)))) for i in range(N)]
        )
        
        # Step 4. Globally shift mantissas by G_shifts[i] amount
        # Make room for the right shift
        M_p = [uq_resize(M_p[i], 2, Wf - 2 + 2**s_ - 1) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, Wf + (2**s_ - 1) - 2))) for i in range(N)]
        )
        
        M_p = [uq_rshift(M_p[i], G_shifts[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], UQT(2, Wf + (2**s_ - 1) - 2))) for i in range(N)]
        )
        
        M_p = [uq_to_q(M_p[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], QT(3, Wf + (2**s_ - 1) - 2))) for i in range(N)]
        )
        
        return make_Tuple(make_Tuple(*M_p), E_m)
    
    def sign(E_a: TupleT, E_b: TupleT, M_a: TupleT, M_b: TupleT) -> TupleT:
        return TupleT(
            TupleT(QT(3, Wf + (2**s_ - 1) - 2), QT(3, Wf + (2**s_ - 1) - 2), QT(3, Wf + (2**s_ - 1) - 2), QT(3, Wf + (2**s_ - 1) - 2)), 
            QT(10, 0)
        )
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[E_a, E_b, M_a, M_b],
        name="optimized_arithmetic_body")


def Optimized(a0: Node, a1: Node, a2: Node, a3: Node,
              b0: Node, b1: Node, b2: Node, b3: Node) -> Composite:
    
    def spec(prim, a0, a1, a2, a3,
             b0, b1, b2, b3, s):
        out = prim._spec_outputs(s)
        res = 0
        res += a0 * b0
        res += a1 * b1
        res += a2 * b2
        res += a3 * b3
        s.add(res == out)
        return out
    
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
        
        M_p, E_m = optimized_arithmetic_body(
            make_Tuple(*E_a), 
            make_Tuple(*E_b), 
            make_Tuple(*M_a), 
            make_Tuple(*M_b),
        )
        
        # Step 5. Adjust signs using xor operation
        S_p = [sign_xor(S_a[i], S_b[i]) for i in range(N)]
        (
            [S_p[i].check(is_typeof(S_p[i], UQT(1, 0))) for i in range(N)]
        )
        
        M_p = [q_add_sign(M_p[i], S_p[i]) for i in range(N)]
        (
            [M_p[i].check(is_typeof(M_p[i], QT(3, Wf + (2**s_ - 1) - 2))) for i in range(N)]
        )
        
        # Step 6. Adder Tree
        M_sum = CSA_tree4(*M_p)
        (
            M_sum.check(is_typeof(M_sum, QT(6, Wf + (2**s_ - 1) - 2))),
            M_sum.check(
                q_equal(
                    M_sum, 
                    q_add(q_add(M_p[0], M_p[1]), q_add(M_p[2], M_p[3])),
                )
            )
        )
        
        ############# RESULT ###############
        
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
    design.run_spec()
    
    # Test the design
    random_gen, exp_reshuffle = BFloat16.random_generator(seed=0, shared_exponent_bits=5)
    for _ in range(100):
        exp_reshuffle()
        for i in range(N):
            a[i].load_val(random_gen())
            b[i].load_val(random_gen())
        print(str(design.evaluate()))
