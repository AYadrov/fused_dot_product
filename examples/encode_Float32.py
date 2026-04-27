import math

from fused_dot_product import *
from .common import *


# Round to Nearest, Ties to Even
def uq_RNE_IEEE(m: Node, bits_to_cut: int):
    assert bits_to_cut >= 0, "Cannot cut negative number of bits"
    assert bits_to_cut < m.node_type.total_bits(), "Cannot cut all the bits of a fixed point"
    
    @Primitive(name="uq_RNE_IEEE", spec=lambda x, ctx: tuple([x, ctx.real_val(0)]))
    def impl(m: Node) -> Node:
        m_frac_bits = m.node_type.frac_bits
        m_int_bits = m.node_type.int_bits
        m_total_bits = m_frac_bits + m_int_bits
        target_bits = m_total_bits - bits_to_cut
        
        target_int_bits = min(m_int_bits, target_bits)
        target_frac_bits = max(target_bits - target_int_bits, 0)
        
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
        
        m_truncated = uq_resize(m, target_int_bits, target_frac_bits)
        increment_to_add = basic_identity(increment, Const(UQ(0, target_int_bits, target_frac_bits)))

        # Overflow will happen?
        overflow_bit = basic_and(
            basic_and_reduce(m_truncated, Const(UQ(0, 1, 0))),
            increment,
            Const(UQ(0, 1, 0)),
        )
        m_incremented = uq_add(m_truncated, increment_to_add)

        # Address potential overflow
        m_resized = basic_rshift(m_incremented, overflow_bit, Const(UQ(0, target_int_bits, target_frac_bits)))
        return make_Tuple(m_resized, overflow_bit)
        
    return impl(m)


def round_mantissa_spec(m, e, ctx):
    m_ = ctx.fresh_real('rounded_m')
    e_ = ctx.fresh_real('rounded_e')
    ctx.assume((m * ctx.real_val(2) ** e).eq(m_ * ctx.real_val(2) ** e_))
    return m_, e_

def round_mantissa(m: Node, e: Node, target_bits: int = Float32.mantissa_bits, rounding_mode: str = "RNE") -> Primitive:
    assert target_bits > 0, "Cannot round fixed point to zero/negative number of bits"
    
    @Primitive(name="round_mantissa", spec=round_mantissa_spec)
    def impl(m_prerounded: Node, e_prerounded: Node) -> Node:
        ####################################################
        #  Constants
        m_frac_bits = m_prerounded.node_type.frac_bits
        m_int_bits = m_prerounded.node_type.int_bits
        m_total_bits = m_frac_bits + m_int_bits
        bits_to_cut = max(m_total_bits - target_bits, 0)
        
        ####################################################
        m_rounded = None
        overflow_bit = None
        if rounding_mode == "RNE":
            m_rounded, overflow_bit = uq_RNE_IEEE(m_prerounded, bits_to_cut=bits_to_cut)
        else:
            raise NotImplementedError()
        
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


def normalize_to_1_xxx_spec(m, e, ctx):
    m_ = ctx.fresh_real('normalized_m')
    e_ = ctx.fresh_real('normalized_e')
    ctx.assume((m * ctx.real_val(2) ** e).eq(m_ * ctx.real_val(2) ** e_))
    return m_, e_

@Primitive(name="normalize_to_1_xxx", spec=normalize_to_1_xxx_spec)
def normalize_to_1_xxx(m: Node, e: Node) -> Node:
    """Normalizes mantissa to 1.xxx with no lose in accuracy"""
    ####################################################
    #  Constants
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
    right_m_uq = uq_rshift_jam(m_resized, shift_magnitude_uq)  # Shift amount is negative
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


# Expects UQ<1, ...> as an input, returns UQ<0, ...>
@Primitive(name="drop_implicit_bit", spec=lambda x, ctx: x - ctx.real_val(1))
def drop_implicit_bit(x: Node):
    return uq_select(x, x.node_type.frac_bits - 1, 0)


def shift_if_subnormal_spec(m, e, ctx):
    m_ = ctx.fresh_real('classified_m')
    e_ = ctx.fresh_real('classified_e')
    ctx.assume((m * ctx.real_val(2) ** e).eq(m_ * ctx.real_val(2) ** e_))
    return m_, e_

@Primitive(name="shift_if_subnormal", spec=shift_if_subnormal_spec)
def shift_if_subnormal(normalized_m_uq: Node, normalized_e_q: Node):
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
    classified_m_uq = uq_rshift_jam(classified_m_uq, shift_amount)
    
    return make_Tuple(classified_m_uq, classified_e_uq)


def fp32_encodings_spec(m, e, ctx):
    return m * ctx.real_val(2) ** ctx.real_val(Float32.mantissa_bits), e

# TODO: this function should work for any input, or at least give an error
@Primitive(name="fp32_encodings", spec=fp32_encodings_spec)
def fp32_encodings(m_rounded_uq: Node, e_rounded_uq: Node):
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
    
    # Reinterpret the fractional significand bits as the raw IEEE mantissa field.
    final_m_uq = fraction_to_integer(final_m_uq)
    return make_Tuple(final_m_uq, final_e_uq)


# Assume that e is biased
def fp32_encode(s: Node, e: Node, m: Node, encode_nan: Node, encode_inf: Node) -> Primitive:
    assert e.node_type.frac_bits == 0
    
    def spec(s, e, m, encode_nan, encode_inf, ctx):
        ctx.check(encode_nan.eq(ctx.real_val(0)))
        ctx.check(encode_inf.eq(ctx.real_val(0)))
        return s * m * (ctx.real_val(2) ** (e - ctx.real_val(127)))
    
    @Composite(name="fp32_encode", spec=spec)
    def impl(s_uq: Node, e_q: Node, m_uq: Node, encode_nan: Node, encode_inf: Node) -> Node:
        encode_zero = uq_is_zero(m_uq)
        normalized_m_uq, normalized_e_q = normalize_to_1_xxx(m_uq, e_q)
        shifted_m_uq, shifted_e_uq = shift_if_subnormal(normalized_m_uq, normalized_e_q)
        shifted_m_uq = drop_implicit_bit(shifted_m_uq)
        m_rounded_uq, e_rounded_uq = round_mantissa(shifted_m_uq, shifted_e_uq)
        
        final_m_uq, final_e_uq = fp32_encodings(m_rounded_uq, e_rounded_uq)
        
        # Priority (lowest to highest): normal/subnormal -> zero -> inf -> nan 
        packed_fp32 = fp32_pack(s_uq, final_e_uq, final_m_uq)
        
        result = if_then_else(
            encode_zero,
            if_then_else(s_uq, Const(Float32.nZero()), Const(Float32.Zero())),
            packed_fp32,
        )
        result = if_then_else(
            encode_inf,
            if_then_else(s_uq, Const(Float32.nInf()), Const(Float32.Inf())),
            result,
        )
        result = if_then_else(encode_nan, Const(Float32.NaN()), result)
        return result
    
    return impl(s, e, m, encode_nan, encode_inf)


if __name__ == '__main__':
    from pprint import pprint
    m = Const(UQ.from_float(4.02923583984375, 5, 28)) 
    e = Const(Q.from_float(-25.0, 11, 0))
    s = Const(UQ(1, 1, 0))
    encode_nan = Const(UQ(0, 1, 0))
    encode_inf = Const(UQ(0, 1, 0))
    design = fp32_encode(s, e, m, encode_nan, encode_inf)
    design.print_tree(depth=1)
    pprint(design.check_spec(egglog_iters=6))
    print(design.evaluate())
