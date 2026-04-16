from ..types import *
from .Tuple import make_Tuple
from ..ast import *
from ..spec import *

########### Private Helpers ############

def _bf16_mantissa(x: Node) -> Op:
    def impl(x: BFloat16) -> UQ:
        return UQ(x.mantissa, 7, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(7, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            c_lowering=lambda lowered_args, jittable: f"({lowered_args[0]} & {(1 << 7) - 1})",
            args=[x],
            name="_bf16_mantissa")

def _bf16_exponent(x: Node) -> Op:
    def impl(x: BFloat16) -> UQ:
        return UQ(x.exponent, 8, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(8, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            c_lowering=lambda lowered_args, jittable: f"(({lowered_args[0]} >> 7) & {(1 << 8) - 1})",
            args=[x],
            name="_bf16_exponent")

def _bf16_sign(x: Node) -> Op:
    def impl(x: BFloat16) -> UQ:
        return UQ(x.sign, 1, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(1, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            c_lowering=lambda lowered_args, jittable: f"(({lowered_args[0]} >> 15) & 1)",
            args=[x],
            name="_bf16_sign")

############## Public API ##############

def bf16_decode_spec(x, ctx):
    sign = ctx.fresh_real("sign")
    mantissa = ctx.fresh_real("mantissa")
    exponent = ctx.fresh_real("exponent")

    two = ctx.real_val(2)
    one = ctx.real_val(1)
    m_bits = ctx.real_val(BFloat16.mantissa_bits)
    e_bits = ctx.real_val(BFloat16.exponent_bias)

    mantissa_ = one + mantissa * two ** (-m_bits)
    exponent_ = exponent - e_bits
    ctx.assume(x.eq(sign * (mantissa_ * (two ** exponent_))))
    ctx.assume(sign.eq(ctx.real_val(1)).or_(sign.eq(ctx.real_val(-1))))
    ctx.assume((exponent >= ctx.real_val(0)).and_(exponent < ctx.real_val(1 << BFloat16.exponent_bits)))
    ctx.assume((mantissa >= ctx.real_val(0)).and_(mantissa < ctx.real_val(1 << BFloat16.mantissa_bits)))
    return (sign, mantissa, exponent)


@Primitive(name="bf16_decode", spec=bf16_decode_spec)
def bf16_decode(x: Node) -> Node:
    return make_Tuple(
        _bf16_sign(x),
        _bf16_mantissa(x),
        _bf16_exponent(x),
    )
