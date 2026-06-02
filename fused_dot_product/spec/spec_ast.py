from __future__ import annotations

from dataclasses import dataclass, fields, is_dataclass
from fractions import Fraction
import math
import sys
from typing import Any

from ..egglog import *

import z3
import dreal


class SpecNode:
    def to_egglog(self):
        raise NotImplementedError

    def to_z3(self):
        raise NotImplementedError

    def to_dreal(self):
        raise NotImplementedError

    def identical(self, other: object) -> bool:
        return identical_nodes(self, other)

    def constant_fold(self) -> "SpecNode":
        args = children(self)
        if args == ():
            return self

        folded_args = tuple(arg.constant_fold() for arg in args)
        
        # Try shortcut
        shortcut = _shortcut_fold(self, folded_args)
        if shortcut is not None:
            return shortcut
        
        # Else, general case
        output_type = _literal_type(self)
        fold = self.fold()
        if all(isinstance(arg, (RealLit, BoolLit)) for arg in folded_args):
            folded_value = fold(*(arg.value for arg in folded_args))
            if folded_value is not None and _can_constant_fold_literal(output_type, folded_value):
                # Successfully folded
                return output_type(folded_value)
            
        # Nothing got folded
        if all(old is new for old, new in zip(args, folded_args)):
            return self
        # Partially folded
        return type(self)(*folded_args)
        
    def fold(self):
        raise NotImplementedError


class RealExpr(SpecNode):
    @staticmethod
    def _coerce(value):
        if isinstance(value, RealExpr):
            return value
        raise TypeError(f"Expected RealExpr, got {type(value).__name__}")
    
    def __add__(self, other: "RealExpr") -> "RealExpr":
        return Add(self, self._coerce(other))

    def __iadd__(self, other: "RealExpr") -> "RealExpr":
        return self + other
    
    def __sub__(self, other: "RealExpr") -> "RealExpr":
        return Sub(self, self._coerce(other))

    def __isub__(self, other: "RealExpr") -> "RealExpr":
        return self - other
    
    def __mul__(self, other: "RealExpr") -> "RealExpr":
        return Mul(self, self._coerce(other))

    def __imul__(self, other: "RealExpr") -> "RealExpr":
        return self * other
    
    def __pow__(self, other: "RealExpr", modulo=None) -> "RealExpr":
        if modulo is not None:
            raise NotImplementedError("pow(..., modulo) is not supported for spec AST")
        return Pow(self, self._coerce(other))

    def __ipow__(self, other: "RealExpr") -> "RealExpr":
        return self ** other
    
    def __neg__(self) -> "RealExpr":
        return Neg(self)
    
    def __pos__(self) -> "RealExpr":
        return self  # maybe a copy needed
    
    def __abs__(self) -> "RealExpr":
        return Abs(self)
    
    def __lt__(self, other: "RealExpr") -> "BoolExpr":
        return Lt(self, self._coerce(other))
    
    def __le__(self, other: "RealExpr") -> "BoolExpr":
        return Le(self, self._coerce(other))
    
    def __gt__(self, other: "RealExpr") -> "BoolExpr":
        return Gt(self, self._coerce(other))
    
    def __ge__(self, other: "RealExpr") -> "BoolExpr":
        return Ge(self, self._coerce(other))
    
    def eq(self, other: "RealExpr") -> "BoolExpr":
        return Eq(self, self._coerce(other))
    
    def ne(self, other: "RealExpr") -> "BoolExpr":
        return NotEq(self, self._coerce(other))
    
    def max(self, other: "RealExpr") -> "RealExpr":
        return Max(self, self._coerce(other))
    
    def min(self, other: "RealExpr") -> "RealExpr":
        return Min(self, self._coerce(other))

class BoolExpr(SpecNode):
    @staticmethod
    def _coerce(value):
        if isinstance(value, BoolExpr):
            return value
        raise TypeError(f"Expected BoolExpr, got {type(value).__name__}")    
    
    def __bool__(self) -> bool:
        raise TypeError("Spec BoolExpr cannot be used as a Python bool")

    def __invert__(self) -> "BoolExpr":
        return Not(self)
        
    def eq(self, other: "BoolExpr") -> "BoolExpr":
        return BoolEq(self, self._coerce(other))
    
    def ne(self, other: "BoolExpr") -> "BoolExpr":
        raise NotImplementedError()

    def or_(self, other: "BoolExpr") -> "BoolExpr":
        return Or(self, self._coerce(other))

    def and_(self, other: "BoolExpr") -> "BoolExpr":
        return And(self, self._coerce(other))

@dataclass(frozen=True)
class RealVar(RealExpr):
    name: str
    
    def to_egglog(self):
        return Math.Var(self.name)
    
    def to_z3(self, env):
        key = ("real", self.name)
        if key not in env:
            env[key] = z3.Real(self.name)
        return env[key]

    def to_dreal(self, env):
        key = ("real", self.name)
        if key not in env:
            env[key] = dreal.Variable(self.name)
        return env[key]

    def __str__(self):
        return f"real({self.name})"


@dataclass(frozen=True)
class BoolVar(BoolExpr):
    name: str
    
    def to_egglog(self):
        return MathBool.Var(self.name)
    
    def to_z3(self, env):
        key = ("bool", self.name)
        if key not in env:
            env[key] = z3.Bool(self.name)
        return env[key]

    def to_dreal(self, env):
        key = ("bool", self.name)
        if key not in env:
            env[key] = dreal.Variable(self.name, dreal.Variable.Bool)
        return env[key]

    def __str__(self):
        return f"bool({self.name})"


@dataclass(frozen=True)
class RealLit(RealExpr):
    value: float | int

    def _as_fraction(self) -> Fraction:
        if isinstance(self.value, float):
            if not math.isfinite(self.value):
                raise ValueError("non-finite RealLit is not supported")
            return Fraction(self.value)
        return Fraction(self.value)
    
    def to_egglog(self):
        ratio = self._as_fraction()
        return _fraction_to_egglog(ratio)
            
    def to_z3(self, env):
        ratio = self._as_fraction()
        return z3.RealVal(f"{ratio.numerator}/{ratio.denominator}")

    def to_dreal(self, env):
        return dreal.Expression(self.value)

    def __str__(self):
        return str(self.value)


@dataclass(frozen=True)
class BoolLit(BoolExpr):
    value: bool
    
    def to_egglog(self):
        return MathBool.True_() if self.value else MathBool.False_()
    
    def to_z3(self, env):
        return z3.BoolVal(self.value)

    def to_dreal(self, env):
        return dreal.Formula.TRUE() if self.value else dreal.Formula.FALSE()

    def __str__(self):
        return "true" if self.value else "false"


@dataclass(frozen=True)
class Add(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) + self.rhs.to_z3(env=env)
    
    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) + self.rhs.to_dreal(env=env)
    
    def fold(self):
        return lambda lhs, rhs: lhs + rhs
    
    def __str__(self):
        return f"({self.lhs} + {self.rhs})"


@dataclass(frozen=True)
class Sub(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), Math.Neg(self.rhs.to_egglog()))
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) - self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) - self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs - rhs

    def __str__(self):
        return f"({self.lhs} - {self.rhs})"


@dataclass(frozen=True)
class Mul(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Mul(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) * self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) * self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs * rhs

    def __str__(self):
        return f"({self.lhs} * {self.rhs})"


@dataclass(frozen=True)
class Neg(RealExpr):
    value: RealExpr
    
    def to_egglog(self):
        return Math.Neg(self.value.to_egglog())
    
    def to_z3(self, env):
        return -self.value.to_z3(env=env)

    def to_dreal(self, env):
        return -self.value.to_dreal(env=env)

    def fold(self):
        return lambda value: -value

    def __str__(self):
        return f"(-{self.value})"


@dataclass(frozen=True)
class Abs(RealExpr):
    value: RealExpr
    
    def to_egglog(self):
        return Math.Abs(self.value.to_egglog())
    
    def to_z3(self, env):
        return z3.Abs(self.value.to_z3(env=env))

    def to_dreal(self, env):
        return abs(self.value.to_dreal(env=env))

    def fold(self):
        return lambda value: abs(value)

    def __str__(self):
        return f"abs({self.value})"


@dataclass(frozen=True)
class Pow(RealExpr):
    base: RealExpr
    exponent: RealExpr

    def to_egglog(self):
        return Math.Pow(self.base.to_egglog(), self.exponent.to_egglog())

    def to_z3(self, env):
        return self.base.to_z3(env=env) ** self.exponent.to_z3(env=env)


    def to_dreal(self, env):
        return self.base.to_dreal(env=env) ** self.exponent.to_dreal(env=env)

    def fold(self):
        return _folded_pow_value

    def __str__(self):
        return f"({self.base} ** {self.exponent})"


@dataclass(frozen=True)
class Max(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Max(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        lhs = self.lhs.to_z3(env=env)
        rhs = self.rhs.to_z3(env=env)
        return z3.If(lhs >= rhs, lhs, rhs)

    def to_dreal(self, env):
        return dreal.Max(self.lhs.to_dreal(env=env), self.rhs.to_dreal(env=env))

    def fold(self):
        return max

    def __str__(self):
        return f"max({self.lhs}, {self.rhs})"


@dataclass(frozen=True)
class Min(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Min(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        lhs = self.lhs.to_z3(env=env)
        rhs = self.rhs.to_z3(env=env)
        return z3.If(lhs <= rhs, lhs, rhs)

    def to_dreal(self, env):
        return dreal.Min(self.lhs.to_dreal(env=env), self.rhs.to_dreal(env=env))

    def fold(self):
        return min

    def __str__(self):
        return f"min({self.lhs}, {self.rhs})"


@dataclass(frozen=True)
class If(RealExpr):
    cond: BoolExpr
    on_true: RealExpr
    on_false: RealExpr
    
    def to_egglog(self):
        return Math.If(
            self.cond.to_egglog(),
            self.on_true.to_egglog(),
            self.on_false.to_egglog(),
        )
    
    def to_z3(self, env):
        return z3.If(
            self.cond.to_z3(env=env),
            self.on_true.to_z3(env=env),
            self.on_false.to_z3(env=env)
        )

    def to_dreal(self, env):
        return dreal.if_then_else(
            self.cond.to_dreal(env=env),
            self.on_true.to_dreal(env=env),
            self.on_false.to_dreal(env=env),
        )

    def fold(self):
        return lambda cond, on_true, on_false: on_true if cond else on_false

    def __str__(self):
        return f"(if {self.cond} then {self.on_true} else {self.on_false})"


@dataclass(frozen=True)
class Eq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Eq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) == self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) == self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs == rhs

    def __str__(self):
        return f"({self.lhs} == {self.rhs})"


@dataclass(frozen=True)
class NotEq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.NotEq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) != self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) != self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs != rhs

    def __str__(self):
        return f"({self.lhs} != {self.rhs})"


@dataclass(frozen=True)
class Lt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Lt(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) < self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) < self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs < rhs

    def __str__(self):
        return f"({self.lhs} < {self.rhs})"


@dataclass(frozen=True)
class Le(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Le(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) <= self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) <= self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs <= rhs

    def __str__(self):
        return f"({self.lhs} <= {self.rhs})"


@dataclass(frozen=True)
class Gt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Gt(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) > self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) > self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs > rhs

    def __str__(self):
        return f"({self.lhs} > {self.rhs})"


@dataclass(frozen=True)
class Ge(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Ge(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) >= self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        return self.lhs.to_dreal(env=env) >= self.rhs.to_dreal(env=env)

    def fold(self):
        return lambda lhs, rhs: lhs >= rhs

    def __str__(self):
        return f"({self.lhs} >= {self.rhs})"


@dataclass(frozen=True)
class BoolEq(BoolExpr):
    lhs: BoolExpr
    rhs: BoolExpr
    
    def to_egglog(self):
        return MathBool.Eq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return self.lhs.to_z3(env=env) == self.rhs.to_z3(env=env)

    def to_dreal(self, env):
        lhs = self.lhs.to_dreal(env=env)
        rhs = self.rhs.to_dreal(env=env)
        return dreal.And(dreal.Or(dreal.Not(lhs), rhs), dreal.Or(dreal.Not(rhs), lhs))

    def fold(self):
        return lambda lhs, rhs: lhs == rhs

    def __str__(self):
        return f"({self.lhs} == {self.rhs})"

    
@dataclass(frozen=True)
class Not(BoolExpr):
    value: BoolExpr
    
    def to_egglog(self):
        return MathBool.Not(self.value.to_egglog())
    
    def to_z3(self, env):
        return z3.Not(self.value.to_z3(env=env))

    def to_dreal(self, env):
        return dreal.Not(self.value.to_dreal(env=env))

    def fold(self):
        return lambda value: not value

    def __str__(self):
        return f"(not {self.value})"

    
@dataclass(frozen=True)
class Or(BoolExpr):
    lhs: BoolExpr
    rhs: BoolExpr
    
    def to_egglog(self):
        return MathBool.Or(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return z3.Or(self.lhs.to_z3(env=env), self.rhs.to_z3(env=env))

    def to_dreal(self, env):
        return dreal.Or(self.lhs.to_dreal(env=env), self.rhs.to_dreal(env=env))

    def fold(self):
        return lambda lhs, rhs: lhs or rhs

    def __str__(self):
        return f"({self.lhs} or {self.rhs})"


@dataclass(frozen=True)
class And(BoolExpr):
    lhs: BoolExpr
    rhs: BoolExpr
    
    def to_egglog(self):
        return MathBool.And(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self, env):
        return z3.And(self.lhs.to_z3(env=env), self.rhs.to_z3(env=env))

    def to_dreal(self, env):
        return dreal.And(self.lhs.to_dreal(env=env), self.rhs.to_dreal(env=env))

    def fold(self):
        return lambda lhs, rhs: lhs and rhs

    def __str__(self):
        return f"({self.lhs} and {self.rhs})"


def ite(
    cond: BoolExpr,
    on_true: RealExpr,
    on_false: RealExpr,
) -> RealExpr:
    return If(cond, RealExpr._coerce(on_true), RealExpr._coerce(on_false))


def _folded_pow_value(base: float | int, exponent: float | int):
    try:
        value = base ** exponent
    except (OverflowError, ValueError, ZeroDivisionError):
        return None
    if isinstance(value, complex):
        return None
    return value


_C_LONG_MIN = -sys.maxsize - 1
_C_LONG_MAX = sys.maxsize


def _fits_c_long(value: int) -> bool:
    return _C_LONG_MIN <= value <= _C_LONG_MAX


def _fraction_fits_c_long(value: Fraction) -> bool:
    return _fits_c_long(value.numerator) and _fits_c_long(value.denominator)


def _real_lit_fits_c_long(value: float | int) -> bool:
    try:
        ratio = Fraction(value)
    except (OverflowError, ValueError):
        return False
    return _fraction_fits_c_long(ratio)


def _math_num(numerator: int, denominator: int = 1):
    return Math.Num(BigRat(numerator, denominator))


def _remove_factor_of_two(value: int) -> tuple[int, int]:
    shift = 0
    while value != 0 and value % 2 == 0:
        value //= 2
        shift += 1
    return value, shift


def _fraction_to_egglog(value: Fraction):
    if _fraction_fits_c_long(value):
        return _math_num(value.numerator, value.denominator)

    sign = -1 if value.numerator < 0 else 1
    numerator_odd, numerator_shift = _remove_factor_of_two(abs(value.numerator))
    denominator_odd, denominator_shift = _remove_factor_of_two(value.denominator)
    coefficient = Fraction(sign * numerator_odd, denominator_odd)
    exponent = numerator_shift - denominator_shift

    if not _fraction_fits_c_long(coefficient) or not _fits_c_long(exponent):
        raise OverflowError(f"RealLit {value} cannot be represented with C-long-sized egglog literals")

    scale = Math.Pow(_math_num(2), _math_num(exponent))
    if coefficient == 1:
        return scale
    if coefficient == -1:
        return Math.Neg(scale)
    return Math.Mul(_math_num(coefficient.numerator, coefficient.denominator), scale)


def _can_constant_fold_literal(output_type, value: float | int | bool) -> bool:
    if output_type is RealLit:
        return _real_lit_fits_c_long(value)
    return True


# Substitute exact learned literal facts, then rebuild and constant-fold.
def substitute_literals(
    node: "SpecNode",
    replacements: dict[SpecNode, RealLit | BoolLit],
) -> "SpecNode":
    replacement = replacements.get(node)
    if replacement is not None:
        return replacement

    args = children(node)
    if args == ():
        return node

    substituted_args = tuple(substitute_literals(arg, replacements) for arg in args)
    rebuilt = (
        node
        if all(old is new for old, new in zip(args, substituted_args))
        else type(node)(*substituted_args)
    )
    return rebuilt.constant_fold()


def _shortcut_fold(
    node: SpecNode,
    folded_args: tuple[SpecNode, ...],
) -> SpecNode | None:
    if isinstance(node, Eq):
        lhs, rhs = folded_args
        folded = _fold_indicator_equality(lhs, rhs)
        if folded is not None:
            return folded
        folded = _fold_indicator_equality(rhs, lhs)
        if folded is not None:
            return folded
        return None

    if isinstance(node, If):
        cond, on_true, on_false = folded_args
        if isinstance(cond, BoolLit):
            return on_true if cond.value else on_false
        if identical_nodes(on_true, on_false):
            return on_true
        return None

    if isinstance(node, Mul):
        lhs, rhs = folded_args
        if isinstance(lhs, RealLit) and lhs.value == 0:
            return lhs
        if isinstance(rhs, RealLit) and rhs.value == 0:
            return rhs

        if isinstance(lhs, RealLit) and lhs.value == 1:
            return rhs
        if isinstance(rhs, RealLit) and rhs.value == 1:
            return lhs
        
        return None

    if isinstance(node, Add):
        lhs, rhs = folded_args
        if isinstance(lhs, RealLit) and lhs.value == 0:
            return rhs
        if isinstance(rhs, RealLit) and rhs.value == 0:
            return lhs
        return None

    if isinstance(node, Sub):
        lhs, rhs = folded_args
        if isinstance(rhs, RealLit) and rhs.value == 0:
            return lhs
        if isinstance(lhs, RealLit) and lhs.value == 0:
            return Neg(rhs)
        return None

    if isinstance(node, And):
        lhs, rhs = folded_args
        if isinstance(lhs, BoolLit):
            return rhs if lhs.value else BoolLit(False)
        if isinstance(rhs, BoolLit):
            return lhs if rhs.value else BoolLit(False)
        return None

    if isinstance(node, Or):
        lhs, rhs = folded_args
        if isinstance(lhs, BoolLit):
            return BoolLit(True) if lhs.value else rhs
        if isinstance(rhs, BoolLit):
            return BoolLit(True) if rhs.value else lhs
        return None

    return None


def _fold_indicator_equality(
    expr: SpecNode,
    target: SpecNode,
) -> BoolExpr | None:
    if not isinstance(expr, If) or not isinstance(target, RealLit):
        return None

    cond = expr.cond
    on_true = expr.on_true
    on_false = expr.on_false
    if not isinstance(on_true, RealLit) or not isinstance(on_false, RealLit):
        return None
    if on_true.value == on_false.value:
        return None

    if target.value == on_true.value:
        cond_value = True
    elif target.value == on_false.value:
        cond_value = False
    else:
        return BoolLit(False)

    if isinstance(cond, Not):
        value = cond.value
        if isinstance(value, BoolVar):
            return BoolEq(value, BoolLit(not cond_value))
    return BoolEq(cond, BoolLit(cond_value))


def _literal_type(node: SpecNode):
    if isinstance(node, BoolExpr):
        return BoolLit
    if isinstance(node, RealExpr):
        return RealLit
    raise TypeError(f"Unsupported node type: {type(node).__name__}")


def children(node: SpecNode) -> tuple[SpecNode, ...]:
    if isinstance(node, (RealVar, BoolVar, RealLit, BoolLit)):
        return ()
    if isinstance(node, (Neg, Abs, Not)):
        return (node.value,)
    if isinstance(node, Pow):
        return (node.base, node.exponent)
    if isinstance(node, If):
        return (node.cond, node.on_true, node.on_false)
    if isinstance(
        node,
        (
            Add,
            Sub,
            Mul,
            Max,
            Min,
            Eq,
            NotEq,
            Lt,
            Le,
            Gt,
            Ge,
            BoolEq,
            Or,
            And
        ),
    ):
        return (node.lhs, node.rhs)
    raise TypeError(f"Unsupported node type: {type(node).__name__}")


def variables(node: SpecNode) -> set[RealVar | BoolVar]:
    if isinstance(node, (RealVar, BoolVar)):
        return {node}
    vars_ = set()
    for child in children(node):
        vars_.update(variables(child))
    return vars_


def _identical_values(lhs: object, rhs: object) -> bool:
    if isinstance(lhs, SpecNode):
        return isinstance(rhs, SpecNode) and identical_nodes(lhs, rhs)
    if isinstance(lhs, tuple):
        return (
            isinstance(rhs, tuple)
            and len(lhs) == len(rhs)
            and all(_identical_values(l_item, r_item) for l_item, r_item in zip(lhs, rhs))
        )
    return lhs == rhs


def identical_nodes(lhs: SpecNode, rhs: object) -> bool:
    if type(lhs) is not type(rhs):
        return False
    if not is_dataclass(lhs):
        raise TypeError(f"Unsupported node type: {type(lhs).__name__}")
    return all(
        _identical_values(getattr(lhs, field.name), getattr(rhs, field.name))
        for field in fields(lhs)
    )
