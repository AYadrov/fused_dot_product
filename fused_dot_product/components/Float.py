from ..types import *
from ..ast import *
from ..spec import If
from .Tuple import make_Tuple
from .basics import *


########### Private Helpers ############

def _fp32_mantissa(x: Node) -> Op:
    def impl(x: Float32) -> UQ:
        return UQ(x.mantissa, Float32.mantissa_bits, 0)
    
    def sign(x: Float32T) -> UQT:
        return UQT(Float32.mantissa_bits, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            c_lowering=lambda lowered_args, jittable: f"({lowered_args[0]} & 8388607)",
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
            c_lowering=lambda lowered_args, jittable: f"(({lowered_args[0]} >> 23) & 255)",
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
            c_lowering=lambda lowered_args, jittable: f"(({lowered_args[0]} >> 31) & 1)",
            args=[x],
            name="_fp32_sign")

def _fp32_alloc(sign_bit: Node,
                  exponent: Node,
                  mantissa: Node) -> Op:
    def sign(sign_bit: StaticType, exponent: StaticType, mantissa: StaticType) -> Float32T:
        return Float32T()
    
    def impl(sign_bit: RuntimeType, exponent: RuntimeType, mantissa: RuntimeType) -> Float32:
        return Float32.from_fields(sign_bit.val, exponent.val, mantissa.val)
    
    return Op(
        sign=sign,
        impl=impl,
        c_lowering=lambda lowered_args, jittable: (
            f"(({Float32T().to_cpp_type(jittable=jittable)}({lowered_args[0]}) << 31) | "
            f"({Float32T().to_cpp_type(jittable=jittable)}({lowered_args[1]}) << 23) | "
            f"{Float32T().to_cpp_type(jittable=jittable)}({lowered_args[2]}))"
        ),
        args=[sign_bit, exponent, mantissa],
        name="_fp32_alloc")

############## Public API ##############

# Does not track nan/infs/subnormals yet
def fp32_pack_spec(s, e, m, ctx):
    ctx.assume(s.eq(ctx.real_val(1)) | s.eq(ctx.real_val(0)))
    mantissa = ctx.real_val(1) + m * ctx.real_val(2) ** (-ctx.real_val(Float32.mantissa_bits))
    exponent = e - ctx.real_val(Float32.exponent_bias)
    value = ctx.real_val(-1) ** s * mantissa * ctx.real_val(2) ** exponent
    return (value, ctx.real_val(1), ctx.real_val(0), ctx.real_val(0), ctx.real_val(0), ctx.real_val(0))

@Primitive(name="fp32_pack", spec=fp32_pack_spec)
def fp32_pack(sign: Node, exponent: Node, mantissa: Node) -> Node:
    return _fp32_alloc(sign, exponent, mantissa)

@Primitive(name="fp32_decode", spec=lambda x, ctx: x[1:])
def fp32_decode(x: Node) -> Node:
    sign = _fp32_sign(x)
    exponent = _fp32_exponent(x)
    mantissa = _fp32_mantissa(x)
    
    mantissa_is_nonzero = basic_or_reduce(mantissa, out=Const(UQ(0, 1, 0)))
    mantissa_is_zero = basic_invert(mantissa_is_nonzero, out=Const(UQ(0, 1, 0)))
    
    exponent_is_all_ones = basic_and_reduce(exponent, out=Const(UQ(0, 1, 0)))
    exponent_is_not_all_ones = basic_invert(exponent_is_all_ones, out=Const(UQ(0, 1, 0)))
    exponent_is_nonzero = basic_or_reduce(exponent, out=Const(UQ(0, 1, 0)))
    exponent_is_zero = basic_invert(exponent_is_nonzero, out=Const(UQ(0, 1, 0)))
    
    is_normal = basic_and(exponent_is_nonzero, exponent_is_not_all_ones, Const(UQ(0, 1, 0)),)
    is_subnormal = basic_and(exponent_is_zero, mantissa_is_nonzero, Const(UQ(0, 1, 0)))
    is_zero = basic_and(exponent_is_zero, mantissa_is_zero, Const(UQ(0, 1, 0)))
    is_inf = basic_and(exponent_is_all_ones, mantissa_is_zero, Const(UQ(0, 1, 0)))
    is_nan = basic_and(exponent_is_all_ones, mantissa_is_nonzero, Const(UQ(0, 1, 0)))
    return make_Tuple(sign, exponent, mantissa, is_normal, is_subnormal, is_zero, is_inf, is_nan)
