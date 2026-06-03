from __future__ import annotations

from dataclasses import dataclass

from ..types import Float32
from .spec_ast import BoolExpr, If, RealExpr, RealLit


def _implies(lhs: BoolExpr, rhs: BoolExpr) -> BoolExpr:
    return (~lhs).or_(rhs)


def _flag_as_real(flag: BoolExpr) -> RealExpr:
    return If(flag, RealLit(1), RealLit(0))


def _sign_factor(sign: RealExpr) -> RealExpr:
    return If(sign.eq(RealLit(1)), RealLit(-1), RealLit(1))


@dataclass(frozen=True)
class Float32Spec:
    value: RealExpr
    sign: RealExpr
    exponent: RealExpr
    mantissa: RealExpr
    is_norm: BoolExpr
    is_sub: BoolExpr
    is_zero: BoolExpr
    is_inf: BoolExpr
    is_nan: BoolExpr

    def as_tuple(self) -> tuple[RealExpr, RealExpr, RealExpr, RealExpr, RealExpr, RealExpr]:
        return (
            self.value,
            _flag_as_real(self.is_norm),
            _flag_as_real(self.is_sub),
            _flag_as_real(self.is_zero),
            _flag_as_real(self.is_inf),
            _flag_as_real(self.is_nan),
        )

    def as_fields_tuple(self) -> tuple[RealExpr, RealExpr, RealExpr, RealExpr, BoolExpr, BoolExpr, BoolExpr, BoolExpr, BoolExpr]:
        return (
            self.value,
            self.sign,
            self.exponent,
            self.mantissa,
            _flag_as_real(self.is_norm),
            _flag_as_real(self.is_sub),
            _flag_as_real(self.is_zero),
            _flag_as_real(self.is_inf),
            _flag_as_real(self.is_nan),
        )

    def __iter__(self):
        yield from self.as_fields_tuple()


# General case for FP32
def fresh_float(name: str, ctx) -> Float32Spec:
    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")
    
    sign = ctx.fresh_real(f"{name}_sign")
    exponent = ctx.fresh_real(f"{name}_exponent")
    mantissa = ctx.fresh_real(f"{name}_mantissa")

    zero = ctx.real_val(0)
    one = ctx.real_val(1)
    two = ctx.real_val(2)
    m_bits = ctx.real_val(Float32.mantissa_bits)
    bias = ctx.real_val(Float32.exponent_bias)
    max_exponent = ctx.real_val((1 << Float32.exponent_bits) - 1)
    max_mantissa = ctx.real_val((1 << Float32.mantissa_bits) - 1)
    
    ctx.assume(sign.eq(zero).or_(sign.eq(one)))
    ctx.assume((exponent >= zero).and_(exponent <= max_exponent))
    ctx.assume((mantissa >= zero).and_(mantissa <= max_mantissa))
    
    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    ctx.assume(is_norm.or_(is_sub).or_(is_zero).or_(is_inf).or_(is_nan))
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1:]:
            ctx.assume((~lhs).or_(~rhs))

    ctx.assume(_implies(is_norm, exponent > zero))
    ctx.assume(_implies(is_norm, exponent <= (max_exponent - one)))
    ctx.assume(_implies(is_sub.or_(is_zero), exponent.eq(zero)))
    ctx.assume(_implies(is_zero.or_(is_inf), mantissa.eq(zero)))
    ctx.assume(_implies(is_inf.or_(is_nan), exponent.eq(max_exponent)))
    ctx.assume(_implies(is_sub.or_(is_nan), mantissa > zero))


    sign_value = _sign_factor(sign)
    norm_value = sign_value * (one + mantissa * (two ** (-m_bits))) * (two ** (exponent - bias))
    sub_value = sign_value * mantissa * (two ** (-m_bits)) * (two ** (one - bias))

    value = If(
        is_norm,
        norm_value,
        If(
            is_sub,
            sub_value,
            zero,
        ),
    )
    
    return Float32Spec(
        value=value,
        sign=sign,
        exponent=exponent,
        mantissa=mantissa,
        is_norm=is_norm,
        is_sub=is_sub,
        is_zero=is_zero,
        is_inf=is_inf,
        is_nan=is_nan,
    )


def _encode_from_value(
    ctx,
    name: str,
    value: RealExpr,
    encode_inf: RealExpr,
    encode_nan: RealExpr,
) -> Float32Spec:
    sign_expr = ctx.fresh_real(f"{name}_sign")
    exponent_expr = ctx.fresh_real(f"{name}_exponent")
    mantissa_expr = ctx.fresh_real(f"{name}_mantissa")

    res = _encode_from_components(
        ctx=ctx,
        name=name,
        sign=sign_expr,
        exponent=exponent_expr,
        mantissa=mantissa_expr,
        encode_inf=encode_inf,
        encode_nan=encode_nan,
    )
    ctx.assume(res.value.eq(value))
    return res


# Priority for flags: NaN -> Inf
# sign is assumed to be {0, 1}
# encode_inf is assumed to be {0, 1}
# encode_nan is assumed to be {0, 1}
def _encode_from_components(
    ctx,
    name: str,
    sign: RealExpr,
    exponent: RealExpr,
    mantissa: RealExpr,
    encode_inf: RealExpr,
    encode_nan: RealExpr,
) -> Float32Spec:
    forced_nan = encode_nan.eq(ctx.real_val(1))
    forced_inf = (~forced_nan).and_(encode_inf.eq(ctx.real_val(1)))
    
    is_finite = (~forced_nan).and_(~forced_inf)
    
    zero = ctx.real_val(0)
    one = ctx.real_val(1)
    two = ctx.real_val(2)
    sign_value = _sign_factor(sign)

    ctx.assume(sign.eq(zero).or_(sign.eq(one)))
    ctx.assume(encode_inf.eq(zero).or_(encode_inf.eq(one)))
    ctx.assume(encode_nan.eq(zero).or_(encode_nan.eq(one)))
    
    mantissa_bits = ctx.real_val(Float32.mantissa_bits)
    exponent_bits = ctx.real_val(Float32.exponent_bits)
    exponent_bias = ctx.real_val(Float32.exponent_bias)
    
    max_mantissa = ctx.real_val((1 << Float32.mantissa_bits) - 1)
    max_exponent = ctx.real_val((1 << Float32.exponent_bits) - 1)
    
    smallest_normal = two ** (one - exponent_bias)
    # Greatest_normal cannot fit in egglog if folded
    greatest_normal = (two - two ** (-mantissa_bits)) * two ** (two ** exponent_bits - two - exponent_bias)
    smallest_subnormal = two ** (one - exponent_bias - mantissa_bits)
    
    normal_magnitude = (one + mantissa * two ** (-mantissa_bits)) * two ** (exponent - exponent_bias)
    subnormal_magnitude = mantissa * two ** (-mantissa_bits) * two ** (one - exponent_bias)
    
    is_subnormal_range = is_finite.and_(normal_magnitude < smallest_normal)

    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")
    
    ctx.assume(is_zero.eq(is_subnormal_range.and_(subnormal_magnitude < smallest_subnormal)))
    ctx.assume(is_sub.eq(is_subnormal_range.and_(~is_zero)))
    ctx.assume(is_norm.eq(is_finite.and_(normal_magnitude >= smallest_normal).and_(normal_magnitude <= greatest_normal)))
    ctx.assume(is_inf.eq(is_finite.and_(~is_norm).and_(~is_subnormal_range).or_(forced_inf)))
    ctx.assume(is_nan.eq(forced_nan))
    
    # Some constant encodings, such as inf/nan.
    out_exponent = If(
        is_nan.or_(is_inf),
        max_exponent,
        If(is_zero.or_(is_sub), zero, ctx.fresh_real(f"{name}_exponent")),
    )
    out_mantissa = If(
        is_nan,
        one,
        If(is_inf.or_(is_zero), zero, ctx.fresh_real(f"{name}_mantissa")),
    )
    ctx.assume(_implies(is_sub.or_(is_norm), (out_mantissa >= zero).and_(out_mantissa <= max_mantissa)))
    ctx.assume(_implies(is_norm, (out_exponent >= one).and_(out_exponent <= max_exponent - one)))
    
    out_subnormal_magnitude = out_mantissa * two ** (-mantissa_bits) * two ** (one - exponent_bias)
    out_normal_magnitude = (one + out_mantissa * two ** (-mantissa_bits)) * two ** (out_exponent - exponent_bias)
    
    ctx.assume(_implies(is_norm, out_normal_magnitude.eq(normal_magnitude)))
    ctx.assume(_implies(is_sub, out_subnormal_magnitude.eq(subnormal_magnitude)))
    
    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    ctx.assume(is_norm.or_(is_sub).or_(is_zero).or_(is_inf).or_(is_nan))
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1:]:
            ctx.assume((~lhs).or_(~rhs))
    
    subnormal_val = sign_value * out_subnormal_magnitude
    normal_val = sign_value * out_normal_magnitude
    
    value = If(
        is_norm,
        normal_val,
        If(
            is_sub,
            subnormal_val,
            zero,
        ),
    )
    
    return Float32Spec(
        value=value,
        sign=sign,
        exponent=out_exponent,
        mantissa=out_mantissa,
        is_norm=is_norm,
        is_sub=is_sub,
        is_zero=is_zero,
        is_inf=is_inf,
        is_nan=is_nan,
    )


def encode_fp32(
    ctx,
    encode_inf: RealExpr,
    encode_nan: RealExpr,
    value: RealExpr | None = None,
    sign: RealExpr | None = None,
    exponent: RealExpr | None = None,
    mantissa: RealExpr | None = None,
) -> Float32Spec:
    name = "encoded_fp32"
    if value is not None:
        return _encode_from_value(
            ctx,
            name=name,
            value=value,
            encode_nan=encode_nan,
            encode_inf=encode_inf,
        )

    if sign is None or exponent is None or mantissa is None:
        raise TypeError("encode_fp32 requires either value=... or sign/exponent/mantissa components")
    if encode_inf is None or encode_nan is None:
        raise TypeError("component-based encode_fp32 requires encode_inf and encode_nan")

    return _encode_from_components(
        ctx,
        name=name,
        sign=sign,
        exponent=exponent,
        mantissa=mantissa,
        encode_inf=encode_inf,
        encode_nan=encode_nan,
    )


def fresh_float32(name: str, ctx) -> Float32Spec:
    return fresh_float(name, ctx)
