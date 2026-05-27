from __future__ import annotations

from dataclasses import dataclass

from ..types import Float32
from .spec_ast import BoolExpr, If, RealExpr, RealLit


def _implies(lhs: BoolExpr, rhs: BoolExpr) -> BoolExpr:
    return (~lhs).or_(rhs)


def _flag_as_real(flag: BoolExpr) -> RealExpr:
    return If(flag, RealLit(1), RealLit(0))


@dataclass(frozen=True)
class Float32Spec():
    name: str
    value: RealExpr
    sign: RealExpr
    exponent: RealExpr
    mantissa: RealExpr
    is_norm: BoolExpr
    is_sub: BoolExpr
    is_zero: BoolExpr
    is_inf: BoolExpr
    is_nan: BoolExpr
    
    def __iter__(self):
        yield self.value
        yield self.sign
        yield self.exponent
        yield self.mantissa
        yield self.is_norm
        yield self.is_sub
        yield self.is_zero
        yield self.is_inf
        yield self.is_nan

    def flags(self):
        return ['norm', 'sub', 'zero', 'inf', 'nan']


# General case
def fresh_float32(name: str, flag: str = None, ctx) -> Float32Spec:
    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")
    
    if flag is not None:
        if flag == "norm":
            ctx.assume(is_norm.eq(ctx.bool_val(True)))
        elif flag == "sub":
            ctx.assume(is_sub.eq(ctx.bool_val(True)))
        elif flag == "zero":
            ctx.assume(is_zero.eq(ctx.bool_val(True)))
        elif flag == "inf":
            ctx.assume(is_inf.eq(ctx.bool_val(True)))
        elif flag == "nan":
            ctx.assume(is_nan.eq(ctx.bool_val(True)))
        else:
            raise ValueError(f"Unknown flag {flag}, norm/sub/zero/inf/nan are allowed")
    
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
    
    value_case = If(
        is_norm,
        norm_value,
        If(
            is_sub,
            sub_value,
            zero  # zero/inf/nan
        )
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
        is_norm=_flag_as_real(is_norm),  # TODO: boolean flags
        is_sub=_flag_as_real(is_sub),
        is_zero=_flag_as_real(is_zero),
        is_inf=_flag_as_real(is_inf),
        is_nan=_flag_as_real(is_nan),
    )
