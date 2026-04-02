import math

from fused_dot_product import *
from .common import *

# Round to Nearest, Ties to Even
def uq_RNE_IEEE(m: Node, bits_to_cut: int):
    assert bits_to_cut >= 0, "Cannot cut negative number of bits"
    assert bits_to_cut < m.node_type.total_bits(), "Cannot cut all the bits of a fixed point"
    @Primitive(name="uq_RNE_IEEE", spec=lambda x, ctx: x)
    def impl(m: Node) -> Node:
        m_frac_bits = m.node_type.frac_bits
        m_int_bits = m.node_type.int_bits
        m_total_bits = m_frac_bits + m_int_bits
        target_bits = m_total_bits - bits_to_cut
        
        increment_int_bits = min(m_int_bits, target_bits)
        increment_frac_bits = max(target_bits - increment_int_bits, 0)
        
        # Guard/round/sticky/lsb bits
        guard_bit = Const(UQ(0, 1, 0))
        round_bit = Const(UQ(0, 1, 0))
        sticky_bit = Const(UQ(0, 1, 0))
        
        if bits_to_cut > 0:
            guard_bit = uq_select(m, bits_to_cut-1, bits_to_cut-1)
            round_bit = Const(UQ(0, 1, 0))
            sticky_bit = Const(UQ(0, 1, 0))
            if bits_to_cut >= 2:
                round_bit = uq_select(m, bits_to_cut-2, bits_to_cut-2)
                if bits_to_cut > 2:
                    sticky_slice = uq_select(m, bits_to_cut-3, 0)
                    sticky_bit = basic_or_reduce(x=sticky_slice, out=sticky_bit.copy())
        
        lsb_bit = uq_select(m, bits_to_cut, bits_to_cut)
        
        # Add increment?
        tail = basic_or(round_bit, sticky_bit, out=Const(UQ(0, 1, 0)))
        tail = basic_or(tail, lsb_bit, out=Const(UQ(0, 1, 0)))
        increment = basic_and(guard_bit, tail, out=Const(UQ(0, 1, 0)))
        return basic_identity(increment, Const(UQ(0, increment_int_bits, increment_frac_bits)))
    return impl(m)


def round_spec(m, e, ctx):
    return m, e

def fp32_round(m: Node, e: Node, target_bits: int = Float32.mantissa_bits, rounding_mode: str = "RNE") -> Primitive:
    assert target_bits > 0, "Cannot round fixed point to zero/negative number of bits"
    
    @Primitive(name="fp32_round", spec=round_spec)
    def impl(m_prerounded: Node, e_prerounded: Node) -> Node:
        ####################################################
        #  Some constants
        m_frac_bits = m_prerounded.node_type.frac_bits
        m_int_bits = m_prerounded.node_type.int_bits
        m_total_bits = m_frac_bits + m_int_bits
        bits_to_cut = max(m_total_bits - target_bits, 0)

        sign_int_bits = min(m_int_bits, target_bits)
        sign_frac_bits = max(target_bits - m_int_bits, 0)
        
        ####################################################
        increment = None
        if rounding_mode == "RNE":
            increment = uq_RNE_IEEE(m_prerounded, bits_to_cut=bits_to_cut)
        else:
            raise NotImplementedError()
        
        m_truncated = uq_resize(m_prerounded, sign_int_bits, sign_frac_bits)
        
        m_rounded_wide = uq_add(m_truncated, increment)

        ####################################################
        # "m_rounded_wide gets overflown from adding increment" handling
        carry_index = sign_int_bits + sign_frac_bits
        overflow_bit = basic_select(m_rounded_wide, carry_index, carry_index, Const(UQ(0, 1, 0)))  # UQ<x.0>
        
        # Carry-out means the rounded significand became 1.xxx and must be renormalized to 0.1xxx
        m_shifted = basic_rshift(
            x=m_rounded_wide,
            amount=Const(UQ.from_int(1)),
            out=Const(UQ(0, sign_int_bits, sign_frac_bits)),
        )
        m_rounded = basic_mux_2_1(
            sel=overflow_bit,
            in0=m_rounded_wide,
            in1=m_shifted,
            out=m_shifted.copy(),
        )
        
        e_incremented = uq_add(e_prerounded, overflow_bit)

        ####################################################
        # "subnormal became normal" handling
        prerounded_was_subnormal = uq_is_zero(e_prerounded)
        prerounded_subnormal_became_normal = basic_and(
            prerounded_was_subnormal,
            basic_or_reduce(e_incremented, Const(UQ(0, 1, 0))),
            out=Const(UQ(0, 1, 0)),
        )
        m_after_subnormal_fixup = basic_mux_2_1(
            sel=prerounded_subnormal_became_normal,
            in0=m_rounded,
            in1=Const(UQ(0, 1, 0)),
            out=m_rounded.copy(),
        )
        ####################################################
        
        return make_Tuple(m_after_subnormal_fixup, e_incremented)
    return impl(m, e)


def lzc_spec(x, ctx):
    raise NotImplementedError

@Primitive(name="lzc", spec=lzc_spec)
def lzc(x: Node) -> Node:
    width = x.node_type.int_bits + x.node_type.frac_bits
    frac_bits = x.node_type.frac_bits
    count_bits = max(1, math.ceil(math.log2(width + 1)))
    
    count = Const(UQ(0, count_bits, 0))
    still_zero = Const(UQ(1, 1, 0))
    for pos in range(width - 1, -1, -1):
        bit = uq_select(x, pos, pos)
        is_zero = basic_invert(x=bit, out=bit.copy())
        still_zero = basic_and(x=still_zero, y=is_zero, out=still_zero.copy())
        # Keep the accumulator width stable by zero-extending the predicate.
        count = basic_add(x=count, y=still_zero, out=count.copy())
    return count


def normalize_spec(m, e, ctx):
    return m, e

@Primitive(name="fp32_normalize", spec=normalize_spec)
def fp32_normalize(m: Node, e: Node) -> Node:
    """Normalizes mantissa to 1.xxx with no lose in accuracy"""
    ####################################################
    #  Some constants
    m_int_target_bits = 1
    m_frac_target_bits = max(m.node_type.int_bits - 1, 0) + m.node_type.frac_bits
    ####################################################
    # Calculating shift amount
    lzc_q = uq_to_q(lzc(m))
    
    # Shift amount = LZC - int_bits + 1
    int_bits_q = uq_to_q(uq_int_bits(m))
    shift_amount_q = q_add(q_sub(lzc_q, int_bits_q), Const(Q.from_int(1)))
    ####################################################
    # Shifting mantissa
    shift_sign_uq = q_sign_bit(shift_amount_q)
    shift_magnitude_q = q_abs(shift_amount_q)
    shift_magnitude_uq = q_to_uq(shift_magnitude_q)
    
    # This resize operation will make sure that no loss of accuracy happens
    m_resized = uq_resize(m, max(m_int_target_bits, m.node_type.int_bits), m_frac_target_bits)
    
    left_m_uq = uq_lshift(m_resized, shift_magnitude_uq)  # Shift amount is positive
    right_m_uq = uq_rshift(m_resized, shift_magnitude_uq)  # Shift amount is negative
    norm_m_uq = basic_mux_2_1(
        sel=shift_sign_uq,
        in0=left_m_uq,
        in1=right_m_uq,
        out=Const(UQ(0, m_int_target_bits, m_frac_target_bits)),  
    )
    ####################################################
    # Correcting exponent
    left_e_q = q_sub(e, shift_magnitude_q)
    right_e_q = q_add(e, shift_magnitude_q)
    norm_e_q = basic_mux_2_1(
        sel=shift_sign_uq,
        in0=left_e_q,
        in1=right_e_q,
        out=right_e_q.copy(),
    )
    
    return make_Tuple(norm_m_uq, norm_e_q)


def classify_fp32_spec(m, e, ctx):
    return m, e
     
@Primitive(name="fp32_classify", spec=classify_fp32_spec)
def fp32_classify(normalized_m_uq: Node, normalized_e_q: Node):
    # Classifying exponent and shifting mantissa
    ####################################################
    # Constants
    subnormal_extra_bits = 10  # Customizable
    int_bits = normalized_m_uq.node_type.int_bits
    frac_bits = normalized_m_uq.node_type.frac_bits + subnormal_extra_bits
    ####################################################
    # Classify exponent
    e_sign_uq = q_sign_bit(normalized_e_q)
    e_is_zero = q_is_zero(normalized_e_q)
    is_subnormal = basic_or(e_is_zero, e_sign_uq, Const(UQ(0, 1, 0)))
    ####################################################
    # Clamp exponent
    e_magnitude_uq = q_to_uq(q_abs(normalized_e_q))
    classified_e_uq = basic_mux_2_1(
        sel=is_subnormal,
        in0=e_magnitude_uq,
        in1=Const(UQ(0, 1, 0)),
        out=e_magnitude_uq.copy(),
    )
    ####################################################
    # Shift mantissa
    shift_if_subnormal = uq_add(Const(UQ(1, 1, 0)), e_magnitude_uq)
    shift_amount = basic_mux_2_1(
        sel=is_subnormal,
        in0=Const(UQ(0, 1, 0)),
        in1=shift_if_subnormal,
        out=shift_if_subnormal.copy(),
    )
    
    classified_m_uq = basic_lshift(
        x=normalized_m_uq,
        amount=Const(UQ.from_int(subnormal_extra_bits)),
        out=Const(UQ(0, int_bits, frac_bits)),
    )
    classified_m_uq = uq_rshift(classified_m_uq, shift_amount)
    
    return make_Tuple(classified_m_uq, classified_e_uq)


def fp32_encodings_spec(m, e, m_pre, ctx):
    return m * ctx.real_val(2) ** ctx.real_val(Float32.mantissa_bits), e

# TODO: this function should work for any input, or at least give an error
@Primitive(name="fp32_encodings", spec=fp32_encodings_spec)
def fp32_encodings(m_rounded_uq: Node, e_rounded_uq: Node, m_prerounded_uq: Node):
    # Inf handling
    final_e_uq_wide = uq_min(e_rounded_uq, Const(UQ.from_int(Float32.inf_code)))
    final_e_uq = basic_identity(x=final_e_uq_wide, out=Const(UQ.from_int(Float32.inf_code)))
    is_inf = basic_and_reduce(final_e_uq, out=Const(UQ(0, 1, 0)))
    final_m_uq = basic_mux_2_1(
        sel=is_inf,
        in0=m_rounded_uq,
        in1=Const(UQ(0, 1, 0)),
        out=m_rounded_uq.copy(),
    )
    
    # Zero handling
    m_is_zero = uq_is_zero(m_prerounded_uq)
    final_e_uq = basic_mux_2_1(
        sel=m_is_zero,
        in0=final_e_uq,
        in1=Const(UQ(0, 1, 0)),
        out=final_e_uq.copy(),
    )
    # Reinterpret the fractional significand bits as the raw IEEE mantissa field.
    final_m_uq = fraction_to_integer(final_m_uq)
    return make_Tuple(final_m_uq, final_e_uq)


# Assume that e is biased
# TODO: NaNs
def encode_Float32(m: Node, e: Node) -> Primitive:
    assert e.node_type.frac_bits == 0
    
    def spec(m, e, ctx):
        return m * (ctx.real_val(2) ** (e - ctx.real_val(127)))
    
    @Composite(name="encode_Float32", spec=spec)
    def impl(m_q: Node, e_q: Node) -> Node:
        sign_bit = q_sign_bit(m_q)
        m_uq = q_to_uq(q_abs(m_q))
        
        normalized_m_uq, normalized_e_q = fp32_normalize(m_uq, e_q)
        classified_m_uq, classified_e_uq = fp32_classify(normalized_m_uq, normalized_e_q)
        classified_m_uq = drop_implicit_bit(classified_m_uq)
        m_rounded_uq, e_rounded_uq = fp32_round(classified_m_uq, classified_e_uq)
        final_m_uq, final_e_uq = fp32_encodings(m_rounded_uq, e_rounded_uq, m_uq)
        return fp32_pack(sign_bit, final_e_uq, final_m_uq)
    
    return impl(m, e)


if __name__ == '__main__':
    from pprint import pprint
    m = -4.02923583984375
    e = -25.0
    design = encode_Float32(Const(Q.from_float(m, 5, 28)), Const(Q.from_float(e, 11, 0)))
    design.print_tree(depth=1)
    pprint(design.check_spec(egglog_iters=6))
    print(design.evaluate())
