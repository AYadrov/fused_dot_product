from __future__ import annotations

from dataclasses import dataclass

from ..types import Float32
from .spec_ast import BoolExpr, If, RealExpr, RealLit


def _implies(lhs: BoolExpr, rhs: BoolExpr) -> BoolExpr:
    return (~lhs).or_(rhs)


def _flag_as_real(flag: BoolExpr) -> RealExpr:
    return If(flag, RealLit(1), RealLit(0))


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
    minus_one = ctx.real_val(-1)
    max_exponent = ctx.real_val((1 << Float32.exponent_bits) - 1)
    max_mantissa = ctx.real_val((1 << Float32.mantissa_bits) - 1)
    min_normal_exponent = ctx.real_val(1)
    max_normal_exponent = ctx.real_val(Float32.inf_code - 1)
    subnormal_exponent = ctx.real_val(1 - Float32.exponent_bias)

    signed = minus_one ** sign
    
    norm_mantissa = one + mantissa * (two ** ctx.real_val(-Float32.mantissa_bits))
    norm_exponent = exponent - ctx.real_val(Float32.exponent_bias)
    norm_value = signed * norm_mantissa * (two ** norm_exponent)

    sub_mantissa = mantissa * (two ** ctx.real_val(-Float32.mantissa_bits))
    sub_value = signed * sub_mantissa * (two ** subnormal_exponent)
    
    zero_value = zero

    value_case = If(
        is_norm,
        norm_value,
        If(
            is_sub,
            sub_value,
            If(
                is_zero,
                zero_value,
                If(
                    is_inf,
                    zero,
                    zero), # is_nan case
            ),
        ),
    )

    ctx.assume(sign.eq(zero).or_(sign.eq(one)))
    ctx.assume((exponent >= zero).and_(exponent <= max_exponent))
    ctx.assume((mantissa >= zero).and_(mantissa <= max_mantissa))

    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    ctx.assume(is_norm.or_(is_sub).or_(is_zero).or_(is_inf).or_(is_nan))
    # Only one flag at a time can be true
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1 :]:
            ctx.assume((~lhs).or_(~rhs))  

    ctx.assume(
        _implies(
            is_norm,
            (exponent >= min_normal_exponent)
            .and_(exponent <= max_normal_exponent),
        )
    )
    ctx.assume(_implies(is_sub, exponent.eq(zero).and_(mantissa > zero)))
    ctx.assume(_implies(is_zero, exponent.eq(zero).and_(mantissa.eq(zero))))
    ctx.assume(_implies(is_inf, exponent.eq(max_exponent).and_(mantissa.eq(zero))))
    ctx.assume(_implies(is_nan, exponent.eq(max_exponent).and_(mantissa >= one)))

    return Float32Spec(
        value=value_case,
        sign=sign,
        exponent=exponent,
        mantissa=mantissa,
        is_norm=is_norm,
        is_sub=is_sub,
        is_zero=is_zero,
        is_inf=is_inf,
        is_nan=is_nan,
    )
