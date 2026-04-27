from __future__ import annotations

from dataclasses import dataclass
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
    
    @staticmethod
    def _is_two(value: "RealExpr") -> bool:
        if isinstance(value, RealLit):
            return value.value == 2 or value.value == 2.0
        else:
            return False

    def __pow__(self, other: "RealExpr", modulo=None) -> "RealExpr":
        if modulo is not None:
            raise NotImplementedError("pow(..., modulo) is not supported for spec AST")
        if not self._is_two(self):
            if self._is_two(other):
                return Square(self)
            raise NotImplementedError("Only power base 2 or exponent 2 is supported")
        return Exp2(self._coerce(other))

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
    
    def to_egglog(self):
        if float(self.value) != float(int(self.value)):
            raise ValueError("only integers are working rn in egglog")
        return Math.Num(BigRat(int(self.value), 1))
    
    def to_z3(self, env):
        return z3.RealVal(str(self.value))

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

    def __str__(self):
        return f"abs({self.value})"


@dataclass(frozen=True)
class Exp2(RealExpr):
    exponent: RealExpr
    
    def to_egglog(self):
        return Math.Exp2(self.exponent.to_egglog())
    
    def to_z3(self, env):
        return z3.RealVal(str(2)) ** self.exponent.to_z3(env=env)

    def to_dreal(self, env):
        return dreal.Expression(2) ** self.exponent.to_dreal(env=env)

    def __str__(self):
        return f"(2 ** {self.exponent})"


@dataclass(frozen=True)
class Square(RealExpr):
    value: RealExpr

    def to_egglog(self):
        return Math.Square(self.value.to_egglog())

    def to_z3(self, env):
        value = self.value.to_z3(env=env)
        return value * value

    def to_dreal(self, env):
        value = self.value.to_dreal(env=env)
        return value * value

    def __str__(self):
        return f"({self.value} ** 2)"


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

    def __str__(self):
        return f"({self.lhs} and {self.rhs})"


def ite(
    cond: BoolExpr,
    on_true: RealExpr,
    on_false: RealExpr,
) -> RealExpr:
    return If(cond, RealExpr._coerce(on_true), RealExpr._coerce(on_false))


def children(node: SpecNode) -> tuple[SpecNode, ...]:
    if isinstance(node, (RealVar, BoolVar, RealLit, BoolLit)):
        return ()
    if isinstance(node, (Neg, Abs, Square, Not)):
        return (node.value,)
    if isinstance(node, (Exp2)):
        return (node.exponent,)
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
