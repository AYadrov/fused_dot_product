from __future__ import annotations

from dataclasses import dataclass

from ..types import Float32
from .spec_ast import BoolExpr, BoolLit, If, RealExpr, RealLit


def _implies(lhs: BoolExpr, rhs: BoolExpr) -> BoolExpr:
    return (~lhs) | rhs


def sign_multiplier(ctx, sign: RealExpr) -> RealExpr:
    one = ctx.real_val(1)
    return If(sign.eq(one), ctx.real_val(-1), one)


@dataclass(frozen=True)
class Float32Spec:
    """A decoded FP32 value represented entirely with real and Boolean terms.

    ``value`` is meaningful only when one of ``is_norm``, ``is_sub``, or
    ``is_zero`` holds. NaN and infinity are represented by classification
    flags, with the sign field distinguishing the two infinities.
    """

    value: RealExpr
    sign: RealExpr
    exponent: RealExpr
    mantissa: RealExpr
    is_norm: BoolExpr
    is_sub: BoolExpr
    is_zero: BoolExpr
    is_inf: BoolExpr
    is_nan: BoolExpr

    def as_tuple(self) -> tuple[RealExpr | BoolExpr, ...]:
        """Return the observable semantic fields used for equivalence.

        The finite value carries the sign of normal and subnormal values.
        Infinity and signed zero need an explicit sign comparison. NaN sign
        and payload are intentionally not observable here.
        """

        zero = RealLit(0)
        finite_value = If(self.is_norm | self.is_sub, self.value, zero)
        observable_sign = If(self.is_inf | self.is_zero, self.sign, zero)
        return (
            finite_value,
            observable_sign,
            self.is_norm,
            self.is_sub,
            self.is_zero,
            self.is_inf,
            self.is_nan,
        )

    def as_fields_tuple(
        self,
    ) -> tuple[
        RealExpr,
        RealExpr,
        RealExpr,
        RealExpr,
        BoolExpr,
        BoolExpr,
        BoolExpr,
        BoolExpr,
        BoolExpr,
    ]:
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

    def classification_flags(self) -> dict[str, BoolExpr]:
        return {
            "norm": self.is_norm,
            "sub": self.is_sub,
            "zero": self.is_zero,
            "inf": self.is_inf,
            "nan": self.is_nan,
        }

    @property
    def is_ninf(self) -> BoolExpr:
        return self.is_inf & self.sign.eq(RealLit(1))

    @property
    def is_pinf(self) -> BoolExpr:
        return self.is_inf & self.sign.eq(RealLit(0))


def _assume_exclusive_classification(ctx, flags: tuple[BoolExpr, ...]) -> None:
    ctx.assume(flags[0] | flags[1] | flags[2] | flags[3] | flags[4])
    for i, lhs in enumerate(flags):
        for rhs in flags[i + 1:]:
            ctx.assume((~lhs) | (~rhs))


def fresh_float(name: str, ctx) -> Float32Spec:
    """Create an unconstrained FP32 input with explicit classification."""

    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")

    value = ctx.fresh_real(f"{name}_value")
    sign = ctx.fresh_real(f"{name}_sign")
    exponent = ctx.fresh_real(f"{name}_exponent")
    mantissa = ctx.fresh_real(f"{name}_mantissa")

    zero = ctx.real_val(0)
    one = ctx.real_val(1)
    two = ctx.real_val(2)
    mantissa_bits = ctx.real_val(Float32.mantissa_bits)
    exponent_bias = ctx.real_val(Float32.exponent_bias)
    max_exponent = ctx.real_val((1 << Float32.exponent_bits) - 1)
    max_mantissa = ctx.real_val((1 << Float32.mantissa_bits) - 1)

    ctx.assume(sign.eq(zero) | sign.eq(one))
    ctx.assume((exponent >= zero) & (exponent <= max_exponent))
    ctx.assume((mantissa >= zero) & (mantissa <= max_mantissa))

    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    _assume_exclusive_classification(ctx, flags)

    ctx.assume(_implies(is_norm, exponent >= one))
    ctx.assume(_implies(is_norm, exponent <= max_exponent - one))
    ctx.assume(_implies(is_sub | is_zero, exponent.eq(zero)))
    ctx.assume(_implies(is_zero | is_inf, mantissa.eq(zero)))
    ctx.assume(_implies(is_inf | is_nan, exponent.eq(max_exponent)))
    ctx.assume(_implies(is_sub | is_nan, mantissa >= one))

    sign_value = sign_multiplier(ctx, sign)
    norm_value = (
        sign_value
        * (one + mantissa * (two ** (-mantissa_bits)))
        * (two ** (exponent - exponent_bias))
    )
    sub_value = (
        sign_value
        * mantissa
        * (two ** (-mantissa_bits))
        * (two ** (one - exponent_bias))
    )

    ctx.assume(_implies(is_norm, value.eq(norm_value)))
    ctx.assume(_implies(is_sub, value.eq(sub_value)))
    ctx.assume(_implies(is_zero, value.eq(zero)))

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


def encode_fp32(
    ctx,
    value: RealExpr,
    *,
    nan: BoolExpr | None = None,
    inf: BoolExpr | None = None,
    inf_sign: RealExpr | None = None,
) -> Float32Spec:
    """Encode a finite candidate plus explicit non-finite result conditions.

    NaN has priority over infinity. ``inf_sign`` is required whenever ``inf``
    may hold; finite overflow derives its sign directly from ``value``.
    """

    if not isinstance(value, RealExpr):
        raise TypeError(f"encode_fp32 value must be RealExpr, got {type(value).__name__}")

    nan = ctx.false() if nan is None else nan
    inf_was_supplied = inf is not None
    inf = ctx.false() if inf is None else inf
    if not isinstance(nan, BoolExpr):
        raise TypeError(f"encode_fp32 nan must be BoolExpr, got {type(nan).__name__}")
    if not isinstance(inf, BoolExpr):
        raise TypeError(f"encode_fp32 inf must be BoolExpr, got {type(inf).__name__}")

    zero = ctx.real_val(0)
    one = ctx.real_val(1)
    two = ctx.real_val(2)
    if inf_sign is None:
        if inf_was_supplied and inf.constant_fold() != BoolLit(False):
            raise ValueError("encode_fp32 requires inf_sign when inf may be true")
        inf_sign = zero
    if not isinstance(inf_sign, RealExpr):
        raise TypeError(
            f"encode_fp32 inf_sign must be RealExpr, got {type(inf_sign).__name__}"
        )

    forced_nan = nan
    forced_inf = (~forced_nan) & inf
    candidate_is_finite = (~forced_nan) & (~forced_inf)

    max_exponent = ctx.real_val((1 << Float32.exponent_bits) - 1)
    max_mantissa = ctx.real_val((1 << Float32.mantissa_bits) - 1)
    mantissa_bits = ctx.real_val(Float32.mantissa_bits)
    exponent_bits = ctx.real_val(Float32.exponent_bits)
    exponent_bias = ctx.real_val(Float32.exponent_bias)

    smallest_normal = two ** (one - exponent_bias)
    greatest_normal = (
        (two - two ** (-mantissa_bits))
        * two ** (two ** exponent_bits - two - exponent_bias)
    )
    smallest_subnormal = two ** (one - exponent_bias - mantissa_bits)

    name = "encoded_fp32"
    sign = ctx.fresh_real(f"{name}_sign")
    exponent = ctx.fresh_real(f"{name}_exponent")
    mantissa = ctx.fresh_real(f"{name}_mantissa")
    output_value = ctx.fresh_real(f"{name}_value")

    ctx.assume(sign.eq(zero) | sign.eq(one))
    ctx.assume(_implies(candidate_is_finite, sign.eq(If(value < zero, one, zero))))
    ctx.assume(_implies(forced_inf, inf_sign.eq(zero) | inf_sign.eq(one)))
    ctx.assume(_implies(forced_inf, sign.eq(inf_sign)))
    ctx.assume((exponent >= zero) & (exponent <= max_exponent))
    ctx.assume((mantissa >= zero) & (mantissa <= max_mantissa))

    magnitude = ctx.fresh_real(f"{name}_magnitude")
    ctx.assume(_implies(candidate_is_finite, magnitude.eq(abs(value))))

    is_norm = ctx.fresh_bool(f"{name}_is_norm")
    is_sub = ctx.fresh_bool(f"{name}_is_sub")
    is_zero = ctx.fresh_bool(f"{name}_is_zero")
    is_inf = ctx.fresh_bool(f"{name}_is_inf")
    is_nan = ctx.fresh_bool(f"{name}_is_nan")

    ctx.assume(
        is_zero.eq(candidate_is_finite & (magnitude < smallest_subnormal))
    )
    ctx.assume(
        is_sub.eq(
            candidate_is_finite
            & (magnitude < smallest_normal)
            & (magnitude >= smallest_subnormal)
        )
    )
    ctx.assume(
        is_norm.eq(
            candidate_is_finite
            & (magnitude >= smallest_normal)
            & (magnitude <= greatest_normal)
        )
    )
    ctx.assume(
        is_inf.eq(
            (candidate_is_finite & (magnitude > greatest_normal)) | forced_inf
        )
    )
    ctx.assume(is_nan.eq(forced_nan))

    flags = (is_norm, is_sub, is_zero, is_inf, is_nan)
    _assume_exclusive_classification(ctx, flags)

    ctx.assume(_implies(is_norm, exponent >= one))
    ctx.assume(_implies(is_norm, exponent <= max_exponent - one))
    ctx.assume(_implies(is_sub | is_zero, exponent.eq(zero)))
    ctx.assume(_implies(is_zero | is_inf, mantissa.eq(zero)))
    ctx.assume(_implies(is_inf | is_nan, exponent.eq(max_exponent)))
    ctx.assume(_implies(is_sub | is_nan, mantissa >= one))

    sign_value = sign_multiplier(ctx, sign)
    norm_value = (
        sign_value
        * (one + mantissa * (two ** (-mantissa_bits)))
        * (two ** (exponent - exponent_bias))
    )
    sub_value = (
        sign_value
        * mantissa
        * (two ** (-mantissa_bits))
        * (two ** (one - exponent_bias))
    )

    ctx.assume(_implies(is_norm, value.eq(norm_value)))
    ctx.assume(_implies(is_sub, value.eq(sub_value)))
    ctx.assume(_implies(is_norm, output_value.eq(norm_value)))
    ctx.assume(_implies(is_sub, output_value.eq(sub_value)))
    ctx.assume(_implies(is_zero, output_value.eq(zero)))

    return Float32Spec(
        value=output_value,
        sign=sign,
        exponent=exponent,
        mantissa=mantissa,
        is_norm=is_norm,
        is_sub=is_sub,
        is_zero=is_zero,
        is_inf=is_inf,
        is_nan=is_nan,
    )
