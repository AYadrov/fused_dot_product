import math

from fused_dot_product.ast.AST import *
from fused_dot_product.config import *

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.StaticTypes import TupleT
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.Tuple import make_Tuple
from fused_dot_product.numtypes.UQ import *
from fused_dot_product.numtypes.UQ import _uq_alloc, _uq_int_bits, _uq_frac_bits
from fused_dot_product.utils.utils import mask, round_to_the_nearest_even


def round_to_the_nearest_even_draft(x: Node, e: Node, target_bits: int) -> Primitive:
    """Round unsigned fixed-point x to target_bits with IEEE ties-to-even; adjust exponent on carry."""
    x_total_bits = x.node_type.frac_bits + x.node_type.int_bits
    bits_diff = x_total_bits - target_bits
    
    sign_int_bits = min(x.node_type.int_bits, target_bits)
    sign_frac_bits = max(target_bits - x.node_type.int_bits, 0)

    def sign(x_t: UQT, e: UQT) -> TupleT:
        return TupleT(UQT(sign_int_bits, sign_frac_bits), e)

    def impl(x: Node, e: Node) -> Node:
        # Nothing to truncate, just forward mantissa and exponent.
        if bits_diff <= 0:
            mantissa = basic_identity(x=x, out=Const(UQ(0, sign_int_bits, sign_frac_bits)))
            return make_Tuple(mantissa, e.copy())
        
        shift_amount = Const(UQ.from_int(bits_diff))
        truncated = basic_rshift(
            x=x,
            amount=shift_amount,
            out=Const(UQ(0, sign_int_bits, sign_frac_bits)),
        )
        
        guard_bit = basic_select(x, bits_diff-1, bits_diff-1, Const(UQ(0, 1, 0)))
        round_bit = Const(UQ(0, 1, 0))
        sticky_bit = Const(UQ(0, 1, 0))
        if bits_diff >= 2:
            round_bit = basic_select(x, bits_diff-2, bits_diff-2, round_bit.copy())
            if bits_diff > 2:
                sticky_slice = uq_select(x, bits_diff-3, 0)
                sticky_bit = basic_or_reduce(x=sticky_slice, out=sticky_bit.copy())

        lsb_bit = basic_select(truncated, 0, 0, Const(UQ(0, 1, 0)))

        tail = basic_or(round_bit, sticky_bit, out=Const(UQ(0, 1, 0)))
        tail = basic_or(tail, lsb_bit, out=tail.copy())
        increment = basic_and(guard_bit, tail, out=Const(UQ(0, 1, 0)))
        
        rounded_wide = uq_add(truncated, increment)
        
        total_target_bits = sign_int_bits + sign_frac_bits
        top_index = rounded_wide.node_type.int_bits + rounded_wide.node_type.frac_bits - 1
        carry_index = total_target_bits
        overflow_bit = Const(UQ(0, 1, 0))
        if carry_index <= top_index:
            overflow_bit = basic_select(rounded_wide, carry_index, carry_index, overflow_bit.copy())
        
        shifted = basic_rshift(  # Is it rshift or just select???
            x=rounded_wide,
            amount=Const(UQ.from_int(1)),
            out=rounded_wide.copy(),
        )
        rounded = basic_mux_2_1(
            sel=overflow_bit,
            in0=rounded_wide,
            in1=shifted,
            out=Const(UQ(0, sign_int_bits, sign_frac_bits)),  # Silent overflow
        )
        
        e_inc = uq_add(e, overflow_bit)
        e_out = basic_mux_2_1(sel=overflow_bit, in0=e, in1=e_inc, out=e.copy())  # Assuming that e can not overflow (weak assumption)

        return make_Tuple(rounded, e_out)

    return Primitive(
        spec=None,
        impl=impl,
        sign=sign,
        args=[x, e],
        name=f"round_to_the_nearest_even_draft",
    )


def mantissa_add_implicit_bit(x: Node) -> Primitive:
    def spec(mantissa: float) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
    
    def sign(mantissa: UQT) -> UQT:
        assert mantissa.frac_bits == 0
        return UQT(1, mantissa.int_bits)
    
    def impl(x: Node) -> Node:
        return basic_concat(
            x=Const(UQ(1, 1, 0)),  # 1.
            y=x,  # xxxxxxx.
            out=Const(UQ(0, 1, 7)),
        )
    
    return Composite(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x],
        name="mantissa_add_implicit_bit")


def sign_xor(x: Node, y: Node) -> Primitive:
    def spec(x, y):
        return 0.0 if x == y else 1.0
    
    def sign(x: UQT, y: UQT) -> UQT:
        return UQT(1, 0)
    
    def impl(x: UQ, y: UQ) -> UQ:
        return basic_xor(
            x=x,
            y=y,
            out=Const(UQ(0, 1, 0)),  # 0.
        )
    
    return Primitive(
        spec=spec,
        sign=sign,
        impl=impl,
        args=[x, y],
        name="sign_xor")


def lzc(x: Node) -> Primitive:
    """Leading zero count for an unsigned fixed-point value."""
    width = x.node_type.int_bits + x.node_type.frac_bits
    frac_bits = x.node_type.frac_bits
    count_bits = max(1, math.ceil(math.log2(width + 1)))

    def spec(x_val: float) -> float:
        raw = int(round(x_val * (2 ** frac_bits)))
        bits = f"{raw:0{width}b}"
        lz = len(bits) - len(bits.lstrip("0"))
        return float(lz)
    
    def impl(x: Node) -> Node:
        count = Const(UQ(0, count_bits, 0))
        still_zero = Const(UQ(1, 1, 0))
        for pos in range(width - 1, -1, -1):
            bit = uq_select(x, pos, pos)
            is_zero = basic_invert(x=bit, out=bit.copy())
            still_zero = basic_and(x=still_zero, y=is_zero, out=still_zero.copy())
            # Keep the accumulator width stable by zero-extending the predicate.
            count = basic_add(x=count, y=still_zero, out=count.copy())
        return count
    
    def sign(x: UQT) -> UQT:
        return UQT(count_bits, 0)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="lzc")


def normalize_to_1_xxx_draft(m: Node, e: Node) -> Primitive:
    def sign(m: UQT, e: QT) -> TupleT:
        width = m.int_bits + m.frac_bits
        lzc_q_width = max(1, math.ceil(math.log2(width + 1))) + 1
        
        int_bits_q_width = m.int_bits.bit_length() + 1
        shift_magnitude_width = max(lzc_q_width, int_bits_q_width) + 2
        e_width = max(e.int_bits, shift_magnitude_width) + 1
        
        return TupleT(UQT(m.int_bits, m.frac_bits), QT(e_width, e.frac_bits))
    
    # Q<a,b>, UQ<c,d>
    def impl(m: Node, e: Node) -> Node:
        lzc_uq = lzc(m)  # UQ<ceil(log2(a + b)), 0>
        lzc_q = uq_to_q(lzc_uq)  # UQ<ceil(log2(a + b)) + 1, 0>
        
        # Shift amount = LZC - int_bits + 1
        int_bits_q = uq_to_q(_uq_int_bits(m))
        shift_amount_q = q_add(q_sub(lzc_q, int_bits_q), Const(Q.from_int(1)))  # UQ<max(m.int_bits, lzc_width) + 2, 0>
        
        shift_sign_uq = q_sign_bit(shift_amount_q)
        shift_magnitude_q = q_abs(shift_amount_q)
        shift_magnitude_uq = q_to_uq(shift_magnitude_q)
        
        # Loss of accuracy here
        left_m_uq = uq_lshift(m, shift_magnitude_uq)
        right_m_uq = uq_rshift(m, shift_magnitude_uq)
        norm_m_uq = basic_mux_2_1(
            sel=shift_sign_uq,
            in0=left_m_uq,
            in1=right_m_uq,
            out=m.copy(),
        )
        
        left_e_q = q_sub(e, shift_magnitude_q)
        right_e_q = q_add(e, shift_magnitude_q)
        norm_e_q = basic_mux_2_1(
            sel=shift_sign_uq,
            in0=left_e_q,
            in1=right_e_q,
            out=right_e_q.copy(),
        )
        
        return make_Tuple(norm_m_uq, norm_e_q)
    
    return Primitive(
        spec=None,  # Do not check spec for now, it should be m*e == m_*e_
        impl=impl,
        sign=sign,
        args=[m, e],
        name="normalize_to_1_xxx_draft",
    )


# Alias used by tests; keeps the draft normalizer accessible without exposing internals.
def _normalize_to_1_xxx_draft(m: Node, e: Node) -> Primitive:
    return normalize_to_1_xxx_draft(m, e)


# TODO: loss of accuracy, NaNs
def Q_E_encode_Float32_draft(m: Node, e: Node) -> Composite:
    def sign(m: QT, e: QT) -> Float32T:
        return Float32T()

    def impl(m: Node, e: Node) -> Node:
        sign_bit = q_sign_bit(m)
        m_uq = q_to_uq(q_abs(m))
        
        m_uq, e = normalize_to_1_xxx_draft(m_uq, e)
        
        e_sign_uq = q_sign_bit(e)
        e_magnitude_uq = q_to_uq(q_abs(e))
        
        # if exponent is negative - it is subnormal
        shift_if_negative = uq_add(Const(UQ.from_int(1, 1, 0)), e_magnitude_uq)
        subnormal_shift_amount = basic_mux_2_1(
            sel=e_sign_uq,
            in0=Const(UQ.from_int(0, 1, 0)),
            in1=shift_if_negative,
            out=shift_if_negative.copy(),
        )
        
        normalized_exponent_uq = basic_mux_2_1(
            sel=e_sign_uq,
            in0=e_magnitude_uq,
            in1=Const(UQ.from_int(1, 1, 0)),
            out=e_magnitude_uq.copy(),
        )
        # Loss of accuracy
        normalized_m_uq = uq_rshift(m_uq, subnormal_shift_amount)
        
        
        m_is_zero = Const(UQ.from_int(0, 1, 0))
        m_is_zero = basic_invert(
            x=basic_or_reduce(
                x=m_uq,
                out=m_is_zero.copy(),
            ),
            out=m_is_zero.copy(),
        )
        
        
        # TODO: incorporate m_is_zero into a mux to force Zero/nZero if desired.
        return #Q_E_encode_Float32(normalized_m_q, normalized_e_q)
    
    return Composite(
        spec=None,
        impl=impl,
        sign=sign,
        args=[m, e],
        name="Q_E_encode_Float32_draft",
    )



def OPTIMIZED_MAX_EXP4(e0: Node,
                       e1: Node,
                       e2: Node,
                       e3: Node) -> Primitive:
    def spec(e0, e1, e2, e3):
        return max(max(e0, e1), max(e2, e3))
    
    def sign(e0: UQT, e1: UQT, e2: UQT, e3: UQT) -> UQT:
        int_bits = max(max(e0.int_bits, e1.int_bits), max(e2.int_bits, e3.int_bits))
        frac_bits = max(max(e0.frac_bits, e1.frac_bits), max(e2.frac_bits, e3.frac_bits))
        assert frac_bits == 0, "Not expected fractional bits"
        return UQT(int_bits, frac_bits)
    
    def impl(e0: Node, e1: Node, e2: Node, e3: Node) -> Node:
        def bit_not(x: Node) -> Node:
            return basic_invert(x=x, out=x.copy())
        
        def bit_and(x: Node, y: Node) -> Node:
            return basic_and(x=x, y=y, out=x.copy())
        
        def bit_or(x: Node, y: Node) -> Node:
            return basic_or(x=x, y=y, out=x.copy())
        
        def or_tree(bits: list[Node]) -> Node:
            acc = bits[0]
            for b in bits[1:]:
                acc = bit_or(acc, b)
            return acc
        
        def concat(high: Node, low: Node) -> Node:
            int_bits = uq_add(_uq_int_bits(high), _uq_int_bits(low))
            out = _uq_alloc(int_bits, Const(UQ.from_int(0)))
            return basic_concat(x=high, y=low, out=out)
        
        inputs = [e0, e1, e2, e3]
        
        # That's a bad move, it steps away from AST to pure integers
        int_bits = max(x.node_type.int_bits for x in inputs)
        frac_bits = max(x.node_type.frac_bits for x in inputs)
        bit_width = int_bits + frac_bits
        
        zero_bit = Const(UQ(0, 1, 0))
        
        ep_bits = []
        for exp in inputs:
            bits = [zero_bit]
            for pos in range(bit_width-1, -1, -1):
                bits.append(uq_select(exp, pos, pos))
            ep_bits.append(bits)
        
        smaller = [[zero_bit] for _ in range(len(inputs))]
        maxexp = [zero_bit]
        
        for i in range(1, bit_width+1):
            data_for_or = []
            max_prev = maxexp[i-1]
            for j in range(len(inputs)):
                prev_bit = ep_bits[j][i-1]
                curr_bit = ep_bits[j][i]
                prev_is_smaller = smaller[j][i-1]
                
                curr_is_smaller = bit_or(bit_and(max_prev, bit_not(prev_bit)), prev_is_smaller)
                res = bit_not(curr_is_smaller)
                
                smaller[j].append(curr_is_smaller)
                
                candidate = bit_and(curr_bit, res)
                data_for_or.append(candidate)
            
            maxexp.append(or_tree(data_for_or))
        
        bits = maxexp[1:]  # drop the leading 0, keep MSB→LSB
        out = bits[0]
        for b in bits[1:]:
            out = concat(out, b)
        return out
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[e0, e1, e2, e3],
        name="OPTIMIZED_MAX_EXP4"
    )

if __name__ == '__main__':
    inputs = [Var(f"arg_{i}", sign=UQT(7,0)) for i in range(4)]
    design = OPTIMIZED_MAX_EXP4(*inputs)
    design.print_tree(depth=1)
    
