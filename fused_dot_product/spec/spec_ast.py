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
    def __reduce__(self):
        return type(self), tuple(getattr(self, field.name) for field in fields(self))

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
            return shortcut.constant_fold()
        
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
    def _coerce_real_expr(value):
        if isinstance(value, (RealExpr, SpecialExpr)):
            return value
        raise TypeError(f"Expected RealExpr or SpecialExpr, got {type(value).__name__}")
    
    def __add__(self, other: "RealExpr") -> "RealExpr":
        return Add(self, other)
    
    def __iadd__(self, other: "RealExpr") -> "RealExpr":
        return self + other
    
    def __sub__(self, other: "RealExpr") -> "RealExpr":
        return Sub(self, other)
    
    def __isub__(self, other: "RealExpr") -> "RealExpr":
        return self - other
    
    def __mul__(self, other: "RealExpr") -> "RealExpr":
        return Mul(self, other)
    
    def __imul__(self, other: "RealExpr") -> "RealExpr":
        return self * other
    
    def __pow__(self, other: "RealExpr", modulo=None) -> "RealExpr":
        if modulo is not None:
            raise NotImplementedError("pow(..., modulo) is not supported for spec AST")
        return Pow(self, other)
    
    def __ipow__(self, other: "RealExpr") -> "RealExpr":
        return self ** other
    
    def __neg__(self) -> "RealExpr":
        return Neg(self)
    
    def __pos__(self) -> "RealExpr":
        _reject_special_operation("unary plus", self)
        return self
    
    def __abs__(self) -> "RealExpr":
        return Abs(self)
    
    def __lt__(self, other: "RealExpr") -> "BoolExpr":
        return Lt(self, other)
        
    def __le__(self, other: "RealExpr") -> "BoolExpr":
        return Le(self, other)
    
    def __gt__(self, other: "RealExpr") -> "BoolExpr":
        return Gt(self, other)
    
    def __ge__(self, other: "RealExpr") -> "BoolExpr":
        return Ge(self, other)
    
    def eq(self, other: "RealExpr") -> "BoolExpr":
        return Eq(self, other)
    
    def ne(self, other: "RealExpr") -> "BoolExpr":
        return NotEq(self, other)
    
    def max(self, other: "RealExpr") -> "RealExpr":
        return Max(self, other)
    
    def min(self, other: "RealExpr") -> "RealExpr":
        return Min(self, other)


class SpecialExpr(RealExpr):
    pass


def contains_special(expr: SpecNode) -> bool:
    if isinstance(expr, SpecialExpr):
        return True
    return False
    # return any(
    #     contains_special(value)
    #     for field in fields(expr)
    #     if isinstance(value := getattr(expr, field.name), SpecNode)
    # )


def _reject_special_operation(operation: str, *operands: SpecNode) -> None:
    if any(contains_special(operand) for operand in operands):
        raise TypeError(
            f"{operation} cannot be applied to an expression containing SpecialExpr; use a finite expression"
        )


class BoolExpr(SpecNode):
    @staticmethod
    def _coerce_bool_expr(value):
        if isinstance(value, BoolExpr):
            return value
        raise TypeError(f"Expected BoolExpr, got {type(value).__name__}")

    
    def __bool__(self) -> bool:
        raise TypeError("Spec BoolExpr cannot be used as a Python bool")
    
    def __invert__(self) -> "BoolExpr":
        return Not(self)
    
    def __and__(self, other: "BoolExpr") -> "BoolExpr":
        return self.and_(other)
    
    def __rand__(self, other: "BoolExpr") -> "BoolExpr":
        return And(other, self)
    
    def __or__(self, other: "BoolExpr") -> "BoolExpr":
        return self.or_(other)
    
    def __ror__(self, other: "BoolExpr") -> "BoolExpr":
        return Or(other, self)
    
    def eq(self, other: "BoolExpr") -> "BoolExpr":
        return BoolEq(self, other)

    # this should be BoolNe
    def ne(self, other: "BoolExpr") -> "BoolExpr":
        return BoolEq(~self, other)
    
    def or_(self, other: "BoolExpr") -> "BoolExpr":
        return Or(self, other)
    
    def and_(self, other: "BoolExpr") -> "BoolExpr":
        return And(self, other)

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
class SpecNaN(SpecialExpr):
    def to_egglog(self):
        raise NotImplementedError("SpecNaN does not lower to egglog")
    
    def to_z3(self, env):
        raise NotImplementedError("SpecNaN does not lower to z3")
    
    def to_dreal(self, env):
        raise NotImplementedError("SpecNaN does not lower to dreal")
    
    def __str__(self):
        return "nan"


@dataclass(frozen=True)
class SpecInf(SpecialExpr):
    def to_egglog(self):
        raise NotImplementedError("SpecInf does not lower to egglog")
    
    def to_z3(self, env):
        raise NotImplementedError("SpecInf does not lower to z3")
    
    def to_dreal(self, env):
        raise NotImplementedError("SpecInf does not lower to dreal")
    
    def __str__(self):
        return "inf"


@dataclass(frozen=True)
class SpecNegInf(SpecialExpr):
    def to_egglog(self):
        raise NotImplementedError("SpecNegInf does not lower to egglog")

    def to_z3(self, env):
        raise NotImplementedError("SpecNegInf does not lower to z3")

    def to_dreal(self, env):
        raise NotImplementedError("SpecNegInf does not lower to dreal")

    def __str__(self):
        return "-inf"


@dataclass(frozen=True)
class Add(RealExpr):
    lhs: RealExpr
    rhs: RealExpr

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("addition", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("subtraction", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("multiplication", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.value)
        # _reject_special_operation("negation", self.value)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.value)
        # _reject_special_operation("absolute value", self.value)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.base)
        RealExpr._coerce_real_expr(self.exponent)
        # _reject_special_operation("exponentiation", self.base, self.exponent)

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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("maximum", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("minimum", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        BoolExpr._coerce_bool_expr(self.cond)
        RealExpr._coerce_real_expr(self.on_true)
        RealExpr._coerce_real_expr(self.on_false)
    
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

    def __new__(cls, lhs: RealExpr, rhs: RealExpr):
        RealExpr._coerce_real_expr(lhs)
        RealExpr._coerce_real_expr(rhs)
        # _reject_special_operation("equality comparison", lhs, rhs)
        return super().__new__(cls)

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
    
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

    def __new__(cls, lhs: RealExpr, rhs: RealExpr):
        RealExpr._coerce_real_expr(lhs)
        RealExpr._coerce_real_expr(rhs)
        # _reject_special_operation("inequality comparison", lhs, rhs)
        return super().__new__(cls)

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("less-than comparison", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("less-than-or-equal comparison", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("greater-than comparison", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        RealExpr._coerce_real_expr(self.lhs)
        RealExpr._coerce_real_expr(self.rhs)
        # _reject_special_operation("greater-than-or-equal comparison", self.lhs, self.rhs)
    
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

    def __post_init__(self):
        BoolExpr._coerce_bool_expr(self.lhs)
        BoolExpr._coerce_bool_expr(self.rhs)
    
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

    def __post_init__(self):
        BoolExpr._coerce_bool_expr(self.value)
        # _reject_special_operation("boolean not", self.value)
    
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

    def __post_init__(self):
        BoolExpr._coerce_bool_expr(self.lhs)
        BoolExpr._coerce_bool_expr(self.rhs)
        # _reject_special_operation("boolean not", self.lhs, self.rhs)
        
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

    def __post_init__(self):
        BoolExpr._coerce_bool_expr(self.lhs)
        BoolExpr._coerce_bool_expr(self.rhs)
        # _reject_special_operation("boolean not", self.lhs, self.rhs)
    
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
    return output_type is not RealLit or _real_lit_fits_c_long(value)


# Substitute exact learned facts, then rebuild and constant-fold.
def substitute_literals(
    node: "SpecNode",
    replacements: dict[SpecNode, SpecNode],
    _seen: set[SpecNode] | None = None,
) -> "SpecNode":
    if _seen is None:  # Avoid loops
        _seen = set()

    replacement = replacements.get(node)
    if replacement is not None:
        if node in _seen:
            return node
        return substitute_literals(replacement, replacements, _seen | {node})

    args = children(node)
    if args == ():
        return node

    substituted_args = tuple(
        substitute_literals(arg, replacements, _seen) for arg in args
    )
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
        # x == x -> True
        if (
            identical_nodes(lhs, rhs)
            and not _contains_special(lhs)
            and not _contains_special(rhs)
        ):
            return BoolLit(True)
        return None

    if isinstance(node, BoolEq):
        lhs, rhs = folded_args
        # x == x -> True
        if identical_nodes(lhs, rhs):
            return BoolLit(True)
        # ~x == x -> False
        if _are_complements(lhs, rhs):
            return BoolLit(False)
        # x == True -> x
        # x == False -> ~x
        if isinstance(lhs, BoolLit):
            return rhs if lhs.value else Not(rhs)
        # True == x -> x
        # False == x -> ~x
        if isinstance(rhs, BoolLit):
            return lhs if rhs.value else Not(lhs)
        return None

    if isinstance(node, NotEq):
        lhs, rhs = folded_args
        # x != x -> False
        if (
            identical_nodes(lhs, rhs)
            and not _contains_special(lhs)
            and not _contains_special(rhs)
        ):
            return BoolLit(False)
        return None

    if isinstance(node, Not):
        value, = folded_args
        # ~(~x) -> x
        if isinstance(value, Not):
            return value.value
        if isinstance(value, BoolLit):
            return BoolLit(not value.value)
        return None
    
    if isinstance(node, If):
        cond, on_true, on_false = folded_args
        # if True then x else y -> x
        # if False then x else y -> y
        if isinstance(cond, BoolLit):
            return on_true if cond.value else on_false
        # If x then y else y -> y
        if identical_nodes(on_true, on_false):
            return on_true
        return None

    # TODO: This can fire as 0*inf -> 0
    if isinstance(node, Mul):
        lhs, rhs = folded_args
        # if _contains_special(lhs) or _contains_special(rhs):
        #     return None
        # x * 0 -> 0
        if isinstance(lhs, RealLit) and lhs.value == 0:
            return lhs
        # 0 * x -> 0
        if isinstance(rhs, RealLit) and rhs.value == 0:
            return rhs
        # 1 * x -> x
        if isinstance(lhs, RealLit) and lhs.value == 1:
            return rhs
        # x * 1 -> x
        if isinstance(rhs, RealLit) and rhs.value == 1:
            return lhs
        return None

    if isinstance(node, Add):
        lhs, rhs = folded_args
        # if _contains_special(lhs) or _contains_special(rhs):
        #     return None
        # x + 0 -> x
        if isinstance(lhs, RealLit) and lhs.value == 0:
            return rhs
        # 0 + x -> x
        if isinstance(rhs, RealLit) and rhs.value == 0:
            return lhs
        return None

    if isinstance(node, Sub):
        lhs, rhs = folded_args
        # if _contains_special(lhs) or _contains_special(rhs):
        #     return None
        # x - 0 -> x
        if isinstance(rhs, RealLit) and rhs.value == 0:
            return lhs
        # 0 - x -> -x
        if isinstance(lhs, RealLit) and lhs.value == 0:
            return Neg(rhs).constant_fold()
        return None

    if isinstance(node, And):
        lhs, rhs = folded_args
        # x and x -> x
        if identical_nodes(lhs, rhs):
            return lhs
        # x and ~x -> False
        if _are_complements(lhs, rhs):
            return BoolLit(False)
        # x and True -> x
        # x and False -> False
        if isinstance(lhs, BoolLit):
            return rhs if lhs.value else BoolLit(False)
        # True and x -> x
        # False and x -> False
        if isinstance(rhs, BoolLit):
            return lhs if rhs.value else BoolLit(False)
        return None

    if isinstance(node, Or):
        lhs, rhs = folded_args
        # x or x -> x
        if identical_nodes(lhs, rhs):
            return lhs
        # x or ~x -> True
        if _are_complements(lhs, rhs):
            return BoolLit(True)
        # x or True -> True
        # x or False -> x
        if isinstance(lhs, BoolLit):
            return BoolLit(True) if lhs.value else rhs
        if isinstance(rhs, BoolLit):
            return BoolLit(True) if rhs.value else lhs
        # (common and x) or (common and y) -> common and (x or y)
        factored = _factor_common_conjunction(lhs, rhs)
        if factored is not None:
            return factored
        return None

    return None


def _are_complements(lhs: SpecNode, rhs: SpecNode) -> bool:
    return (
        isinstance(lhs, Not)
        and identical_nodes(lhs.value, rhs)
    ) or (
        isinstance(rhs, Not)
        and identical_nodes(rhs.value, lhs)
    )


def _factor_common_conjunction(lhs: BoolExpr, rhs: BoolExpr) -> BoolExpr | None:
    if not isinstance(lhs, And) or not isinstance(rhs, And):
        return None

    lhs_pairs = ((lhs.lhs, lhs.rhs), (lhs.rhs, lhs.lhs))
    rhs_pairs = ((rhs.lhs, rhs.rhs), (rhs.rhs, rhs.lhs))
    for lhs_common, lhs_rest in lhs_pairs:
        for rhs_common, rhs_rest in rhs_pairs:
            if identical_nodes(lhs_common, rhs_common):
                return And(lhs_common, Or(lhs_rest, rhs_rest))

    return None


def _negate_bool(expr: SpecNode) -> BoolExpr:
    if isinstance(expr, BoolLit):
        return BoolLit(not expr.value)
    if isinstance(expr, Not):
        return expr.value
    if isinstance(expr, BoolExpr):
        return Not(expr)
    raise TypeError(f"Expected BoolExpr, got {type(expr).__name__}")


def _contains_special(node: SpecNode) -> bool:
    if isinstance(node, SpecialExpr):
        return True
    return any(
        _contains_special(value)
        for field in fields(node)
        if isinstance(value := getattr(node, field.name), SpecNode)
    )


def _split_special_if(
    node: SpecNode,
) -> tuple[BoolExpr, SpecNode, SpecNode] | None:
    """Split a special-reaching If anywhere inside a spec expression."""
    if isinstance(node, If) and (
        _contains_special(node.on_true)
        or _contains_special(node.on_false)
    ):
        return node.cond, node.on_true, node.on_false

    node_fields = fields(node)
    field_values = [getattr(node, field.name) for field in node_fields]
    for index, value in enumerate(field_values):
        if not isinstance(value, SpecNode) or not _contains_special(value):
            continue
        split = _split_special_if(value)
        if split is None:
            continue

        cond, on_true, on_false = split
        true_values = list(field_values)
        false_values = list(field_values)
        true_values[index] = on_true
        false_values[index] = on_false
        return cond, type(node)(*true_values), type(node)(*false_values)

    return None


def _special_rank(node: RealExpr) -> int | None:
    if isinstance(node, SpecNegInf):
        return -1
    if isinstance(node, SpecInf):
        return 1
    if isinstance(node, SpecialExpr):
        return None
    return 0


def _lower_terminal_specials(node: SpecNode) -> SpecNode:
    """Remove unguarded special leaves after reachability was extracted."""
    args = children(node)
    if args == ():
        return node

    lowered_args = tuple(_lower_terminal_specials(arg) for arg in args)
    rebuilt = (
        node
        if all(old is new for old, new in zip(args, lowered_args))
        else type(node)(*lowered_args)
    )

    if isinstance(rebuilt, Eq):
        if _contains_special(rebuilt.lhs) or _contains_special(rebuilt.rhs):
            return BoolLit(
                isinstance(rebuilt.lhs, SpecialExpr)
                and isinstance(rebuilt.rhs, SpecialExpr)
                and identical_nodes(rebuilt.lhs, rebuilt.rhs)
            )

    if isinstance(rebuilt, NotEq):
        if _contains_special(rebuilt.lhs) or _contains_special(rebuilt.rhs):
            invalid = (
                _contains_special(rebuilt.lhs)
                and not isinstance(rebuilt.lhs, SpecialExpr)
            ) or (
                _contains_special(rebuilt.rhs)
                and not isinstance(rebuilt.rhs, SpecialExpr)
            )
            if invalid:
                return BoolLit(False)
            return BoolLit(
                not (
                    isinstance(rebuilt.lhs, SpecialExpr)
                    and isinstance(rebuilt.rhs, SpecialExpr)
                    and identical_nodes(rebuilt.lhs, rebuilt.rhs)
                )
            )

    if isinstance(rebuilt, (Lt, Le, Gt, Ge)) and (
        _contains_special(rebuilt.lhs) or _contains_special(rebuilt.rhs)
    ):
        if (
            _contains_special(rebuilt.lhs)
            and not isinstance(rebuilt.lhs, SpecialExpr)
        ) or (
            _contains_special(rebuilt.rhs)
            and not isinstance(rebuilt.rhs, SpecialExpr)
        ):
            return BoolLit(False)

        lhs_rank = _special_rank(rebuilt.lhs)
        rhs_rank = _special_rank(rebuilt.rhs)
        if lhs_rank is None or rhs_rank is None:
            return BoolLit(False)
        if isinstance(rebuilt, Lt):
            return BoolLit(lhs_rank < rhs_rank)
        if isinstance(rebuilt, Le):
            return BoolLit(lhs_rank <= rhs_rank)
        if isinstance(rebuilt, Gt):
            return BoolLit(lhs_rank > rhs_rank)
        return BoolLit(lhs_rank >= rhs_rank)

    return rebuilt


def lower_specials(node: BoolExpr) -> BoolExpr:
    """Remove specials by splitting within the smallest enclosing predicate."""
    memo: dict[SpecNode, SpecNode] = {}

    def lower_atom(expr: BoolExpr) -> BoolExpr:
        split = _split_special_if(expr)
        if split is None:
            lowered = _lower_terminal_specials(expr)
            if not isinstance(lowered, BoolExpr):
                raise TypeError(
                    f"Expected BoolExpr after lowering, got {type(lowered).__name__}"
                )
            return lowered

        cond, on_true, on_false = split
        if not isinstance(on_true, BoolExpr) or not isinstance(on_false, BoolExpr):
            raise TypeError("Boolean special lowering produced non-Boolean branches")
        lowered_cond = lower_node(cond)
        lowered_true = lower_node(on_true)
        lowered_false = lower_node(on_false)
        if not all(
            isinstance(value, BoolExpr)
            for value in (lowered_cond, lowered_true, lowered_false)
        ):
            raise TypeError("Boolean special lowering changed expression type")
        return (
            lowered_cond & lowered_true
        ) | (
            (~lowered_cond) & lowered_false
        )

    def lower_node(expr: SpecNode) -> SpecNode:
        cached = memo.get(expr)
        if cached is not None:
            return cached

        args = children(expr)
        lowered_args = tuple(lower_node(arg) for arg in args)
        rebuilt = (
            expr
            if all(old is new for old, new in zip(args, lowered_args))
            else type(expr)(*lowered_args)
        )
        if isinstance(rebuilt, BoolExpr) and ( # (Eq, NotEq, Lt, Le, Gt, Ge)) and (
            _contains_special(rebuilt)
        ):
            lowered = lower_atom(rebuilt)
        else:
            lowered = rebuilt

        memo[expr] = lowered
        return lowered

    lowered = lower_node(node)
    if not isinstance(lowered, BoolExpr):
        raise TypeError(
            f"Expected BoolExpr after lowering, got {type(lowered).__name__}"
        )
    return lowered


def _literal_type(node: SpecNode):
    if isinstance(node, BoolExpr):
        return BoolLit
    if isinstance(node, RealExpr):
        return RealLit
    raise TypeError(f"Unsupported node type: {type(node).__name__}")


def children(node: SpecNode) -> tuple[SpecNode, ...]:
    if not isinstance(node, SpecNode) or not is_dataclass(node):
        raise TypeError(f"Unsupported node type: {type(node).__name__}")
    return tuple(
        value
        for field in fields(node)
        if isinstance(value := getattr(node, field.name), SpecNode)
    )


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
