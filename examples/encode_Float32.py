import math
import numpy as np

from fused_dot_product import *

from cvc5.pythonic import FreshReal

# TODO: edge case when input is subnormal that after rounding becomes normal
def round_to_the_nearest_even(m: Node, e: Node, target_bits: int) -> Primitive:
    m_frac_bits = m.node_type.frac_bits
    m_total_bits = m_frac_bits + m.node_type.int_bits
    bits_diff = m_total_bits - target_bits
    
    sign_int_bits = min(m.node_type.int_bits, target_bits)
    sign_frac_bits = max(target_bits - m.node_type.int_bits, 0)
    
    def spec(m: float, e: float, out: tuple):
        if bits_diff <= 0:
            return m * 2 ** e == out[0] * 2 ** out[1]
        
        # Reconstruct raw bits of the incoming mantissa.
        raw = int(round(m * (2 ** m_frac_bits)))
        
        truncated = raw >> bits_diff
        guard = (raw >> (bits_diff - 1)) & 1
        round_bit = (raw >> (bits_diff - 2)) & 1 if bits_diff >= 2 else 0
        sticky_mask = (1 << (bits_diff - 2)) - 1 if bits_diff > 2 else 0
        sticky = 1 if (raw & sticky_mask) else 0
        lsb = truncated & 1
        
        increment = guard and (round_bit or sticky or lsb)
        rounded = truncated + (1 if increment else 0)
        
        overflow = rounded >> target_bits
        if overflow:
            rounded >>= 1
        e_out = e + overflow
        
        mantissa_out = rounded / (2 ** sign_frac_bits)
        return mantissa_out == out[0] and e_out == out[1]
    
    
    def sign(m: UQT, e: UQT) -> TupleT:
        assert e.frac_bits == 0
        return TupleT(UQT(sign_int_bits, sign_frac_bits), UQT(e.int_bits + 1, 0))
    
    def impl(m: Node, e: Node) -> Node:
        e_ext = uq_zero_extend(e, 1)
        # Nothing to truncate, just forward mantissa and exponent.
        if bits_diff < 0:
            # Extend mantissa with additional frac_bits
            m = basic_concat(
                x=m,
                y=Const(UQ(0, abs(bits_diff), 0)),
                out=Const(UQ(0, sign_int_bits, sign_frac_bits)),
            )
            return make_Tuple(m, e_ext)
        elif bits_diff == 0:
            return make_Tuple(m, e_ext)
        
        # Truncation
        shift_amount = Const(UQ.from_int(bits_diff))
        truncated = basic_rshift(
            x=m,
            amount=shift_amount,
            out=Const(UQ(0, sign_int_bits, sign_frac_bits)),
        )
        
        # Guard/round/sticky/lsb bits
        guard_bit = uq_select(m, bits_diff-1, bits_diff-1)
        round_bit = Const(UQ(0, 1, 0))
        sticky_bit = Const(UQ(0, 1, 0))
        if bits_diff >= 2:
            round_bit = uq_select(m, bits_diff-2, bits_diff-2)
            if bits_diff > 2:
                sticky_slice = uq_select(m, bits_diff-3, 0)
                sticky_bit = basic_or_reduce(x=sticky_slice, out=sticky_bit.copy())
        
        lsb_bit = uq_select(truncated, 0, 0)
        
        # Add increment?
        tail = basic_or(round_bit, sticky_bit, out=Const(UQ(0, 1, 0)))
        tail = basic_or(tail, lsb_bit, out=tail.copy())
        increment = basic_and(guard_bit, tail, out=Const(UQ(0, 1, 0)))
        
        # rounded_wide possibly can be overflown
        rounded_wide = basic_add(
            x=truncated,
            y=increment,
            out=Const(UQ(0, sign_int_bits+1, sign_frac_bits))
        )
        
        # Check whether rounded_wide is overflown
        carry_index = sign_int_bits + sign_frac_bits
        overflow_bit = basic_select(rounded_wide, carry_index, carry_index, e.copy())  # UQ<x.0>
        
        # Handling overflow
        shifted = basic_rshift(
            x=rounded_wide,
            amount=Const(UQ.from_int(1)),
            out=Const(UQ(0, sign_int_bits, sign_frac_bits)),
        )
        rounded = basic_mux_2_1(
            sel=overflow_bit,
            in0=rounded_wide,
            in1=shifted,
            out=Const(UQ(0, sign_int_bits, sign_frac_bits)),  # Silent truncation of 1 rightmost bit
        )
        
        e_inc = uq_add(e, overflow_bit)
        e_out = basic_mux_2_1(sel=overflow_bit, in0=e_ext, in1=e_inc, out=e_ext.copy())
        
        return make_Tuple(rounded, e_out)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[m, e],
        name=f"round_to_the_nearest_even",
    )

def lzc(x: Node) -> Primitive:
    """Leading zero count for an unsigned fixed-point value."""
    width = x.node_type.int_bits + x.node_type.frac_bits
    frac_bits = x.node_type.frac_bits
    count_bits = max(1, math.ceil(math.log2(width + 1)))
    
    def spec(x_val: float, out: float):
        raw = int(round(x_val * (2 ** frac_bits)))
        bits = f"{raw:0{width}b}"
        lz = len(bits) - len(bits.lstrip("0"))
        return float(lz) == out
    
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


# Assume that e is biased
def normalize_to_1_xxx(m: Node, e: Node) -> Primitive:
    # mantissa is going to be normalized to 1.xxxxxx
    # this precision will make sure that we do not lose accuracy
    m_int_target_bits = 1
    m_frac_target_bits = max(m.node_type.int_bits - 1, 0) + m.node_type.frac_bits
    
    def sign(m: UQT, e: QT) -> TupleT:
        width = m.int_bits + m.frac_bits
        lzc_q_width = max(1, math.ceil(math.log2(width + 1))) + 1
        
        int_bits_q_width = m.int_bits.bit_length() + 1
        shift_magnitude_width = max(lzc_q_width, int_bits_q_width) + 2
        e_width = max(e.int_bits, shift_magnitude_width) + 1
        
        return TupleT(UQT(m_int_target_bits, m_frac_target_bits), QT(e_width, e.frac_bits))
    
    def spec(m: float, e: float, out: tuple):
        return m * 2 ** (e - 127) == out[0] * 2 ** (out[1] - 127)
    
    def impl(m: Node, e: Node) -> Node:
        lzc_uq = lzc(m)  # UQ<ceil(log2(a + b)), 0>
        lzc_q = uq_to_q(lzc_uq)  # UQ<ceil(log2(a + b)) + 1, 0>
        
        # Shift amount = LZC - int_bits + 1
        int_bits_q = uq_to_q(uq_int_bits(m))
        shift_amount_q = q_add(q_sub(lzc_q, int_bits_q), Const(Q.from_int(1)))  # UQ<max(m.int_bits, lzc_width) + 2, 0>
        
        shift_sign_uq = q_sign_bit(shift_amount_q)
        shift_magnitude_q = q_abs(shift_amount_q)
        shift_magnitude_uq = q_to_uq(shift_magnitude_q)
        
        # This resize operation will make sure that no loss of accuracy happens
        # This precision is union for left or right shift case
        m = uq_resize(m, max(m_int_target_bits, m.node_type.int_bits), m_frac_target_bits)
        
        left_m_uq = uq_lshift(m, shift_magnitude_uq)
        right_m_uq = uq_rshift(m, shift_magnitude_uq)
        norm_m_uq = basic_mux_2_1(
            sel=shift_sign_uq,
            in0=left_m_uq,
            in1=right_m_uq,
            out=Const(UQ(0, m_int_target_bits, m_frac_target_bits)),  
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
        spec=spec,
        impl=impl,
        sign=sign,
        args=[m, e],
        name="normalize_to_1_xxx",
    )


# Assume that e is biased
# TODO: loss of accuracy, NaNs
# subnormal_extra_bits is extra bits that will be used when truncating mantissa to a subnormal format
def encode_Float32(m: Node, e: Node, subnormal_extra_bits = 10) -> Primitive:
    assert e.node_type.frac_bits == 0
    def sign(m: QT, e: QT) -> Float32T:
        return Float32T()
    
    def spec(prim, m, e, s):
        out = prim._spec_outputs(s)
        s.add(out == m * 2 ** (e - Float32.exponent_bias))
        return out

    def impl(m: Node, e: Node) -> Node:
        sign_bit = q_sign_bit(m)
        m_uq = q_to_uq(q_abs(m))
        m_is_zero = basic_invert(
            basic_or_reduce(m_uq, Const(UQ(0, 1, 0))),
            Const(UQ(0, 1, 0)),
        )
        
        ######### NORMALIZING ##########
        
        normalized_m_uq, normalized_e_q = normalize_to_1_xxx(m_uq, e)
        (
            normalized_m_uq.check(uq_less(normalized_m_uq, Const(UQ.from_int(2)))),
            normalized_m_uq.check(uq_greater_or_equal(normalized_m_uq, Const(UQ.from_int(0)))),  # it can be a zero
        )
        
        ###### SUBNORMAL HANDLING ######
        
        e_sign_uq = q_sign_bit(normalized_e_q)
        e_magnitude_uq = q_to_uq(q_abs(normalized_e_q))
        
        # if exponent is less than one - it is subnormal
        e_is_zero = basic_invert(basic_or_reduce(e_magnitude_uq, Const(UQ(0, 1, 0))), Const(UQ(0, 1, 0)))
        is_subnormal = basic_or(e_is_zero, e_sign_uq, Const(UQ(0, 1, 0)))
        
        # make sure that the shift makes exponent to be 1 if subnormal
        shift_if_subnormal = uq_add(Const(UQ(1, 1, 0)), e_magnitude_uq)
        subnormal_shift_amount = basic_mux_2_1(
            sel=is_subnormal,
            in0=Const(UQ(0, 1, 0)),
            in1=shift_if_subnormal,
            out=shift_if_subnormal.copy(),
        )
        
        # Normalize mantissa from 1.xxx to 0.0xxx when subnormal
        int_bits = normalized_m_uq.node_type.int_bits
        frac_bits = normalized_m_uq.node_type.frac_bits + subnormal_extra_bits
        normalized_m_uq = basic_lshift(
                                x=normalized_m_uq,
                                amount=Const(UQ.from_int(subnormal_extra_bits)),
                                out=Const(UQ(0, int_bits, frac_bits)))
        normalized_m_uq = uq_rshift(normalized_m_uq, subnormal_shift_amount)
        
        normalized_e_uq = basic_mux_2_1(
            sel=is_subnormal,
            in0=e_magnitude_uq,
            in1=Const(UQ(0, 1, 0)),  # Subnormals encode exponent as 0
            out=e_magnitude_uq.copy(),
        )
        
        ######### IMPLICIT BIT #########
        
        # Drop implicit bit from ?.xxx to .xxx
        frac_bits = normalized_m_uq.node_type.frac_bits
        if frac_bits > 0:
            normalized_m_uq = uq_select(normalized_m_uq, frac_bits - 1, 0)
        else:
            normalized_m_uq = Const(UQ(0, 0, 1))  # Edge case .0 as fractional bits
        
        (
            normalized_m_uq.check(uq_less(normalized_m_uq, Const(UQ.from_int(1)))),
            normalized_m_uq.check(uq_greater_or_equal(normalized_m_uq, Const(UQ.from_int(0))))
        )
        
        ##### ROUND TO THE NEAREST #####
        
        target_width = Float32.mantissa_bits
        m_rounded_uq, e_rounded_uq = round_to_the_nearest_even(normalized_m_uq, normalized_e_uq, target_bits=target_width)
        (
            m_rounded_uq.check(uq_less(m_rounded_uq, Const(UQ.from_int(1)))),
            m_rounded_uq.check(uq_greater_or_equal(m_rounded_uq, Const(UQ.from_int(0))))
        )
        
        ######### INF HANDLING #########
        
        # if exponent is consecutive 1s - it is infinity
        final_e_uq_wide = uq_min(e_rounded_uq, Const(UQ.from_int(Float32.inf_code)))
        final_e_uq = basic_identity(
            x=final_e_uq_wide,
            out=Const(UQ.from_int(Float32.inf_code)),
        )
        is_inf = basic_and_reduce(final_e_uq, out=Const(UQ(0, 1, 0)))
        final_m_uq = basic_mux_2_1(
            sel=is_inf,
            in0=m_rounded_uq,
            in1=Const(UQ(0, 1, 0)),
            out=m_rounded_uq.copy())
        
        (
            final_e_uq.check(uq_less_or_equal(final_e_uq, Const(UQ.from_int(Float32.inf_code)))),
            final_e_uq.check(uq_greater_or_equal(final_e_uq, Const(UQ.from_int(0)))),
            final_m_uq.check(uq_less(final_m_uq, Const(UQ.from_int(1))))
        )
        
        ######### ZERO HANDLING #########
        final_m_uq = basic_mux_2_1(
            sel=m_is_zero,
            in0=final_m_uq,
            in1=Const(UQ(0, 1, 0)),
            out=final_m_uq.copy(),
        )
        final_e_uq = basic_mux_2_1(
            sel=m_is_zero,
            in0=final_e_uq,
            in1=Const(UQ(0, 1, 0)),
            out=final_e_uq.copy(),
        )

        return float32_alloc(sign_bit, final_m_uq, final_e_uq)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[m, e],
        name="encode_Float32",
    )


if __name__ == '__main__':
    m = -4.02923583984375
    e = -25.0
    print(encode_Float32(Const(Q.from_float(m, 5, 28)), Const(Q.from_float(e, 11, 0))).evaluate())
