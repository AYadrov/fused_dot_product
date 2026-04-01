from ..types import *
from ..ast import *
from .Tuple import make_Tuple

########### Private Helpers ############

def _fp32_mantissa(x: Node) -> Op:
    def impl(x: Float32) -> UQ:
        return UQ(x.mantissa, Float32.mantissa_bits, 0)
    
    def sign(x: Float32T) -> UQT:
        return UQT(Float32.mantissa_bits, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x],
            name="_fp32_mantissa")

def _fp32_exponent(x: Node) -> Op:
    def impl(x: Float32) -> UQ:
        return UQ(x.exponent, Float32.exponent_bits, 0)
    
    def sign(x: Float32T) -> UQT:
        return UQT(Float32.exponent_bits, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x],
            name="_fp32_exponent")

def _fp32_sign(x: Node) -> Op:
    def impl(x: Float32) -> UQ:
        return UQ(x.sign, 1, 0)
    
    def sign(x: Float32T) -> UQT:
        return UQT(1, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x],
            name="_fp32_sign")

############## Public API ##############

def float32_alloc(sign_bit: Node,
                   mantissa: Node,
                   exponent: Node) -> Op:
    def sign(sign_bit: StaticType, mantissa: StaticType, exponent: StaticType) -> Float32T:
        return Float32T()
    
    def impl(sign_bit: RuntimeType, mantissa: RuntimeType, exponent: RuntimeType) -> Float32:
        return Float32(sign_bit.val, mantissa.val, exponent.val)
    
    return Op(
        sign=sign,
        impl=impl,
        args=[sign_bit, mantissa, exponent],
        name="float32_alloc")

def fp32_decode_spec(x, ctx):
    sign = ctx.fresh_real("sign")
    mantissa = ctx.fresh_real("mantissa")
    exponent = ctx.fresh_real("exponent")

    two = ctx.real_val(2)
    one = ctx.real_val(1)
    m_bits = ctx.real_val(Float32.mantissa_bits)
    e_bits = ctx.real_val(Float32.exponent_bias)

    mantissa_ = one + mantissa * two ** (-m_bits)
    exponent_ = exponent - e_bits
    ctx.assume(x.eq(sign * (mantissa_ * (two ** exponent_))))
    ctx.assume(sign.eq(ctx.real_val(1)).or_(sign.eq(ctx.real_val(-1))))
    ctx.assume((exponent >= ctx.real_val(0)).and_(exponent < ctx.real_val(1 << Float32.exponent_bits)))
    ctx.assume((mantissa >= ctx.real_val(0)).and_(mantissa < ctx.real_val(1 << Float32.mantissa_bits)))
    return (sign, mantissa, exponent)


@Primitive(name="fp32_decode", spec=fp32_decode_spec)
def fp32_decode(x: Node) -> Node:
    return make_Tuple(
        _fp32_sign(x),
        _fp32_mantissa(x),
        _fp32_exponent(x),
    )
