from __future__ import annotations

from dataclasses import dataclass

from ..egglog import *

import z3


class SpecNode:
    def to_egglog(self):
        raise NotImplementedError

    def to_z3(self):
        raise NotImplementedError


class RealExpr(SpecNode):
    @staticmethod
    def _coerce(value: "RealExpr | int | float") -> "RealExpr":
        if isinstance(value, RealExpr):
            return value
        if isinstance(value, (int, float)):
            return RealLit(value)
        raise TypeError(
            f"Expected RealExpr | int | float, got {type(value).__name__}"
        )
    
    def __add__(self, other: "RealExpr | int | float") -> "RealExpr":
        return Add(self, self._coerce(other))
    
    def __radd__(self, other: "RealExpr | int | float") -> "RealExpr":
        return Add(self._coerce(other), self)

    def __iadd__(self, other: "RealExpr | int | float") -> "RealExpr":
        return self + other
    
    def __sub__(self, other: "RealExpr | int | float") -> "RealExpr":
        return Sub(self, self._coerce(other))
    
    def __rsub__(self, other: "RealExpr | int | float") -> "RealExpr":
        return Sub(self._coerce(other), self)

    def __isub__(self, other: "RealExpr | int | float") -> "RealExpr":
        return self - other
    
    def __mul__(self, other: "RealExpr | int | float") -> "RealExpr":
        return Mul(self, self._coerce(other))
    
    def __rmul__(self, other: "RealExpr | int | float") -> "RealExpr":
        return Mul(self._coerce(other), self)

    def __imul__(self, other: "RealExpr | int | float") -> "RealExpr":
        return self * other
    
    @staticmethod
    def _is_two(value: "RealExpr | int | float") -> bool:
        if isinstance(value, RealLit):
            return value.value == 2 or value.value == 2.0
        return value == 2 or value == 2.0

    def __pow__(self, other: "RealExpr | int | float", modulo=None) -> "RealExpr":
        if modulo is not None:
            raise NotImplementedError("pow(..., modulo) is not supported for spec AST")
        if not self._is_two(self):
            raise NotImplementedError("Only power base 2 is supported")
        return Exp2(self._coerce(other))
    
    def __rpow__(self, other: "RealExpr | int | float", modulo=None) -> "RealExpr":
        if modulo is not None:
            raise NotImplementedError("pow(..., modulo) is not supported for spec AST")
        if not self._is_two(other):
            raise NotImplementedError("Only power base 2 is supported")
        return Exp2(self)

    def __ipow__(self, other: "RealExpr | int | float") -> "RealExpr":
        return self ** other
    
    def __neg__(self) -> "RealExpr":
        return Neg(self)
    
    def __pos__(self) -> "RealExpr":
        return self  # maybe a copy needed
    
    def __abs__(self) -> "RealExpr":
        return Abs(self)
    
    def __lt__(self, other: "RealExpr | int | float") -> "BoolExpr":
        return Lt(self, self._coerce(other))
    
    def __le__(self, other: "RealExpr | int | float") -> "BoolExpr":
        return Le(self, self._coerce(other))
    
    def __gt__(self, other: "RealExpr | int | float") -> "BoolExpr":
        return Gt(self, self._coerce(other))
    
    def __ge__(self, other: "RealExpr | int | float") -> "BoolExpr":
        return Ge(self, self._coerce(other))
    
    def eq(self, other: "RealExpr | int | float") -> "BoolExpr":
        return Eq(self, self._coerce(other))
    
    def ne(self, other: "RealExpr | int | float") -> "BoolExpr":
        return NotEq(self, self._coerce(other))


class BoolExpr(SpecNode):
    def __bool__(self) -> bool:
        raise TypeError("Spec BoolExpr cannot be used as a Python bool")

    def __invert__(self) -> "BoolExpr":
        return Not(self)


@dataclass(frozen=True)
class RealVar(RealExpr):
    name: str
    
    def to_egglog(self):
        return Math.Var(self.name)
    
    def to_z3(self):
        return z3.Real(self.name)


@dataclass(frozen=True)
class BoolVar(BoolExpr):
    name: str
    
    def to_egglog(self):
        return MathBool.Var(self.name)
    
    def to_z3(self):
        return z3.Bool(self.name)


@dataclass(frozen=True)
class RealLit(RealExpr):
    value: float | int
    
    def to_egglog(self):
        assert float(self.value) == float(int(self.value)), "only integers are working rn in egglog"
        return Math.Num(BigRat(int(self.value), 1))
    
    def to_z3(self):
        return z3.RealVal(str(self.value))


@dataclass(frozen=True)
class BoolLit(BoolExpr):
    value: bool
    
    def to_egglog(self):
        return MathBool.True_() if self.value else MathBool.False_()
    
    def to_z3(self):
        return z3.BoolVal(self.value)


@dataclass(frozen=True)
class Add(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() + self.rhs.to_z3()


@dataclass(frozen=True)
class Sub(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), Math.Neg(self.rhs.to_egglog()))
    
    def to_z3(self):
        return self.lhs.to_z3() - self.rhs.to_z3()


@dataclass(frozen=True)
class Mul(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Mul(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() * self.rhs.to_z3()


@dataclass(frozen=True)
class Neg(RealExpr):
    value: RealExpr
    
    def to_egglog(self):
        return Math.Neg(self.value.to_egglog())
    
    def to_z3(self):
        return -self.value.to_z3()


@dataclass(frozen=True)
class Abs(RealExpr):
    value: RealExpr
    
    def to_egglog(self):
        return Math.Abs(self.value.to_egglog())
    
    def to_z3(self):
        return z3.Abs(self.value.to_z3())


@dataclass(frozen=True)
class Exp2(RealExpr):
    exponent: RealExpr
    
    def to_egglog(self):
        return Math.Exp2(self.exponent.to_egglog())
    
    def to_z3(self):
        return z3.RealVal(2) ** self.exponent.to_z3()


@dataclass(frozen=True)
class Max(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Max(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        lhs = self.lhs.to_z3()
        rhs = self.rhs.to_z3()
        return z3.If(lhs >= rhs, lhs, rhs)


@dataclass(frozen=True)
class Min(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Min(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        lhs = self.lhs.to_z3()
        rhs = self.rhs.to_z3()
        return z3.If(lhs <= rhs, lhs, rhs)


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
    
    def to_z3(self):
        return z3.If(self.cond.to_z3(), self.on_true.to_z3(), self.on_false.to_z3())


@dataclass(frozen=True)
class Eq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Eq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() == self.rhs.to_z3()


@dataclass(frozen=True)
class NotEq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.NotEq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() != self.rhs.to_z3()


@dataclass(frozen=True)
class Lt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Lt(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() < self.rhs.to_z3()


@dataclass(frozen=True)
class Le(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Le(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() <= self.rhs.to_z3()


@dataclass(frozen=True)
class Gt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Gt(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() > self.rhs.to_z3()


@dataclass(frozen=True)
class Ge(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Ge(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() >= self.rhs.to_z3()


@dataclass(frozen=True)
class Not(BoolExpr):
    value: BoolExpr
    
    def to_egglog(self):
        return MathBool.Not(self.value.to_egglog())
    
    def to_z3(self):
        return z3.Not(self.value.to_z3())


def ite(
    cond: BoolExpr,
    on_true: "RealExpr | int | float",
    on_false: "RealExpr | int | float",
) -> RealExpr:
    return If(cond, RealExpr._coerce(on_true), RealExpr._coerce(on_false))


def smax(lhs: "RealExpr | int | float", rhs: "RealExpr | int | float") -> RealExpr:
    return Max(RealExpr._coerce(lhs), RealExpr._coerce(rhs))


def smin(lhs: "RealExpr | int | float", rhs: "RealExpr | int | float") -> RealExpr:
    return Min(RealExpr._coerce(lhs), RealExpr._coerce(rhs))


def children(node: SpecNode) -> tuple[SpecNode, ...]:
    if isinstance(node, (RealVar, BoolVar, RealLit, BoolLit)):
        return ()
    if isinstance(node, (Neg, Abs, Exp2, Not)):
        return (node.value,)
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
        ),
    ):
        return (node.lhs, node.rhs)
    raise TypeError(f"Unsupported node type: {type(node).__name__}")
