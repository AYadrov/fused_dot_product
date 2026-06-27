from __future__ import annotations

from dataclasses import dataclass

from ..types import Float32
from .spec_ast import BoolExpr, If, RealExpr, RealLit


def _implies(lhs: BoolExpr, rhs: BoolExpr) -> BoolExpr:
    return (~lhs) | rhs


def _flag_as_real(flag: BoolExpr) -> RealExpr:
    return If(flag, RealLit(1), RealLit(0))


def sign_multiplier(ctx, sign: RealExpr) -> RealExpr:
    one = ctx.real_val(1)
    return If(sign.eq(one), ctx.real_val(-1), one)


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
            self.is_norm,
            self.is_sub,
            self.is_zero,
            self.is_inf,
            self.is_nan,
        )

    def as_fields_tuple(self) -> tuple[RealExpr, RealExpr, RealExpr, RealExpr, BoolExpr, BoolExpr, BoolExpr, BoolExpr, BoolExpr]:
        return (
            self.value,
            self.sign,
            self.exponent,
            self.mantissa,
            self.is_norm,
            self.is_sub,
            self.is_zero,
            self.is_inf,
            self.is_nan,
        )

    def __iter__(self):
        yield from self.as_fields_tuple()

    def __len__(self):
        return len(self.as_fields_tuple())

    def __getitem__(self, idx: int):
        return self.as_fields_tuple()[idx]

    def special_flags(self):
        return {
            "norm": self.is_norm,
            "sub": self.is_sub,
            "zero": self.is_zero,
            "inf": self.is_inf,
            "nan": self.is_nan,
        }


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

    ctx.assume(sign.eq(zero) | sign.eq(one))
    ctx.assume((exponent >= zero) & (exponent <= max_exponent))
    ctx.assume((mantissa >= zero) & (mantissa <= max_mantissa))

    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    ctx.assume(is_norm | is_sub | is_zero | is_inf | is_nan)
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1:]:
            ctx.assume((~lhs) | (~rhs))
        
    ctx.assume(_implies(is_norm, exponent >= one))
    ctx.assume(_implies(is_norm, exponent <= (max_exponent - one)))
    ctx.assume(_implies(is_sub | is_zero, exponent.eq(zero)))
    ctx.assume(_implies(is_zero | is_inf, mantissa.eq(zero)))
    ctx.assume(_implies(is_inf | is_nan, exponent.eq(max_exponent)))
    ctx.assume(_implies(is_sub | is_nan, mantissa >= one))

    sign_value = sign_multiplier(ctx, sign)
    norm_value = sign_value * (one + mantissa * (two ** (-m_bits))) * (two ** (exponent - bias))
    sub_value = sign_value * mantissa * (two ** (-m_bits)) * (two ** (one - bias))

    value = If(
        is_norm,
        norm_value,
        If(
            is_sub,
            sub_value,
            If(
                is_zero,
                zero,
                If(
                    is_nan,
                    ctx.nan(),
                    ctx.inf(),
                ),
            ),
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


def encode_fp32_real(
    ctx,
    value: RealExpr,
    inf: BoolExpr,
    nan: BoolExpr,
    rounding: str,
) -> Float32Spec:
    name = f"encoded_fp32_{rounding}"

    ########## Special value? ##########
    
    forced_nan = nan
    forced_inf = (~nan) & inf
    is_finite = (~forced_nan) & (~forced_inf)
    
    ############# Constants #############
    zero = ctx.real_val(0)
    one = ctx.real_val(1)
    two = ctx.real_val(2)
    max_exponent = ctx.real_val((1 << Float32.exponent_bits) - 1)
    max_mantissa = ctx.real_val((1 << Float32.mantissa_bits) - 1)
    
    mantissa_bits = ctx.real_val(Float32.mantissa_bits)
    exponent_bits = ctx.real_val(Float32.exponent_bits)
    exponent_bias = ctx.real_val(Float32.exponent_bias)
    
    smallest_normal = two ** (one - exponent_bias)
    # Greatest_normal cannot fit in egglog if folded
    greatest_normal = (two - two ** (-mantissa_bits)) * two ** (two ** exponent_bits - two - exponent_bias)
    smallest_subnormal = two ** (one - exponent_bias - mantissa_bits)

    ####################################

    ########### Components #############

    sign = ctx.fresh_real(f"{name}_sign")
    exponent = ctx.fresh_real(f"{name}_exponent")
    mantissa = ctx.fresh_real(f"{name}_mantissa")

    ctx.assume(sign.eq(zero) | sign.eq(one))
    # Statements like this can exist only if value is finite
    ctx.assume(
        _implies(
            is_finite,
            _implies(value < zero, sign.eq(one)),
        ),
    )
    ctx.assume(
        _implies(
            is_finite,
            _implies(value >= zero, sign.eq(zero)),
        ),
    )
    ctx.assume((exponent >= zero) & (exponent <= max_exponent))
    ctx.assume((mantissa >= zero) & (mantissa <= max_mantissa))
    
    ####################################
    
    ############## Flags ###############
    
    magnitude = abs(value)
    
    is_subnormal_range = is_finite & (magnitude < smallest_normal)
    
    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")
    
    ctx.assume(is_zero.eq(is_finite & (magnitude < smallest_subnormal)))
    ctx.assume(is_sub.eq(is_finite & (magnitude < smallest_normal) & (magnitude >= smallest_subnormal)))
    ctx.assume(is_norm.eq(is_finite & (magnitude >= smallest_normal) & (magnitude <= greatest_normal)))
    ctx.assume(is_inf.eq((is_finite & (magnitude > greatest_normal)) | forced_inf))
    ctx.assume(is_nan.eq(forced_nan))
    
    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    ctx.assume(is_norm | is_sub | is_zero | is_inf | is_nan)
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1:]:
            ctx.assume((~lhs) | (~rhs))
    
    ####################################
    
    ###### Components Constraints ######
    
    ctx.assume(_implies(is_norm, exponent >= one))
    ctx.assume(_implies(is_norm, exponent <= (max_exponent - one)))
    ctx.assume(_implies(is_sub | is_zero, exponent.eq(zero)))
    ctx.assume(_implies(is_zero | is_inf, mantissa.eq(zero)))
    ctx.assume(_implies(is_inf | is_nan, exponent.eq(max_exponent)))
    ctx.assume(_implies(is_sub | is_nan, mantissa >= one))
    
    sign_value = sign_multiplier(ctx, sign)
    norm_value = sign_value * (one + mantissa * (two ** (-mantissa_bits))) * (two ** (exponent - exponent_bias))
    sub_value = sign_value * mantissa * (two ** (-mantissa_bits)) * (two ** (one - exponent_bias))
    
    value_from_components = If(
        is_norm,
        norm_value,
        If(
            is_sub,
            sub_value,
            If(
                is_zero,
                zero,
                If(
                    is_nan,
                    ctx.nan(),
                    ctx.inf(),
                ),
            ),
        ),
    )
    
    ctx.assume(_implies(is_norm, value.eq(value_from_components)))
    ctx.assume(_implies(is_sub, value.eq(value_from_components)))
    
    ####################################
    
    return Float32Spec(
        value=value_from_components,
        sign=sign,
        exponent=exponent,
        mantissa=mantissa,
        is_norm=is_norm,
        is_sub=is_sub,
        is_zero=is_zero,
        is_inf=is_inf,
        is_nan=is_nan,
    )


# Priority for flags: NaN -> Inf
# sign is assumed to be {0, 1}
# encode_inf is assumed to be {0, 1}
# encode_nan is assumed to be {0, 1}
def encode_fp32_components(
    ctx,
    sign: RealExpr,
    exponent: RealExpr,
    mantissa: RealExpr,
    inf: BoolExpr,
    nan: BoolExpr,
) -> Float32Spec:
    name = "encoded_fp32_components"
    
    forced_nan = nan
    forced_inf = (~forced_nan) & inf

    is_finite = (~forced_nan) & (~forced_inf)

    zero = ctx.real_val(0)
    one = ctx.real_val(1)
    two = ctx.real_val(2)
    sign_value = sign_multiplier(ctx, sign)

    ctx.assume(sign.eq(zero) | sign.eq(one))
    ctx.assume(encode_inf.eq(zero) | encode_inf.eq(one))
    ctx.assume(encode_nan.eq(zero) | encode_nan.eq(one))

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

    is_subnormal_range = is_finite & (normal_magnitude < smallest_normal)

    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")

    ctx.assume(is_zero.eq(is_subnormal_range & (subnormal_magnitude < smallest_subnormal)))
    ctx.assume(is_sub.eq(is_subnormal_range & (~is_zero)))
    ctx.assume(is_norm.eq(is_finite & (normal_magnitude >= smallest_normal) & (normal_magnitude <= greatest_normal)))
    ctx.assume(is_inf.eq((is_finite & (normal_magnitude > greatest_normal)) | forced_inf))
    ctx.assume(is_nan.eq(forced_nan))

    # Some constant encodings, such as inf/nan.
    out_exponent = If(
        is_nan | is_inf,
        max_exponent,
        If(is_zero | is_sub, zero, ctx.fresh_real(f"{name}_exponent")),
    )
    out_mantissa = If(
        is_nan,
        one,
        If(is_inf | is_zero, zero, ctx.fresh_real(f"{name}_mantissa")),
    )
    ctx.assume(_implies(is_sub | is_norm, (out_mantissa >= zero) & (out_mantissa <= max_mantissa)))
    ctx.assume(_implies(is_norm, (out_exponent >= one) & (out_exponent <= max_exponent - one)))

    out_subnormal_magnitude = out_mantissa * two ** (-mantissa_bits) * two ** (one - exponent_bias)
    out_normal_magnitude = (one + out_mantissa * two ** (-mantissa_bits)) * two ** (out_exponent - exponent_bias)

    ctx.assume(_implies(is_norm, out_normal_magnitude.eq(normal_magnitude)))
    ctx.assume(_implies(is_sub, out_subnormal_magnitude.eq(subnormal_magnitude)))

    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    ctx.assume(is_norm | is_sub | is_zero | is_inf | is_nan)
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1:]:
            ctx.assume((~lhs) | (~rhs))

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
