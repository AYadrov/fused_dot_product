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
            args=[x],
            name="_bf16_sign")

############## Public API ##############

def bf16_decode(x: Node) -> Primitive:
    def spec(x, ctx):
        sign = ctx.fresh_real(f"sign")
        mantissa = ctx.fresh_real(f"mantissa")
        exponent = ctx.fresh_real(f"exponent")
        
        mantissa_ = ctx.real_val(1) + (mantissa * (2 ** (-ctx.real_val(BFloat16.mantissa_bits))))
        exponent_ = exponent - ctx.real_val(BFloat16.exponent_bias)
        ctx.assume(x.eq(sign * (mantissa_ * (2 ** exponent_))))
        return (sign, mantissa, exponent)
    
    def sign(x: BFloat16T) -> TupleT:
        return TupleT(
            UQT(1, 0),
            UQT(7, 0),
            UQT(8, 0),
        )
    
    def impl(x: Node) -> Node:
        impl = make_Tuple(
            _bf16_sign(x),
            _bf16_mantissa(x),
            _bf16_exponent(x),
        )
        return impl
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="bf16_decode")
