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
            raise NotImplementedError("Only power base 2 is supported")
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


@dataclass(frozen=True)
class RealVar(RealExpr):
    name: str
    
    def to_egglog(self):
        return Math.Var(self.name)
    
    def to_z3(self):
        return z3.Real(self.name)

    def __str__(self):
        return self.name


@dataclass(frozen=True)
class BoolVar(BoolExpr):
    name: str
    
    def to_egglog(self):
        return MathBool.Var(self.name)
    
    def to_z3(self):
        return z3.Bool(self.name)

    def __str__(self):
        return self.name


@dataclass(frozen=True)
class RealLit(RealExpr):
    value: float | int
    
    def to_egglog(self):
        if float(self.value) != float(int(self.value)):
            raise ValueError("only integers are working rn in egglog")
        return Math.Num(BigRat(int(self.value), 1))
    
    def to_z3(self):
        return z3.RealVal(str(self.value))

    def __str__(self):
        return str(self.value)


@dataclass(frozen=True)
class BoolLit(BoolExpr):
    value: bool
    
    def to_egglog(self):
        return MathBool.True_() if self.value else MathBool.False_()
    
    def to_z3(self):
        return z3.BoolVal(self.value)

    def __str__(self):
        return "true" if self.value else "false"


@dataclass(frozen=True)
class Add(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() + self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} + {self.rhs})"


@dataclass(frozen=True)
class Sub(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), Math.Neg(self.rhs.to_egglog()))
    
    def to_z3(self):
        return self.lhs.to_z3() - self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} - {self.rhs})"


@dataclass(frozen=True)
class Mul(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Mul(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() * self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} * {self.rhs})"


@dataclass(frozen=True)
class Neg(RealExpr):
    value: RealExpr
    
    def to_egglog(self):
        return Math.Neg(self.value.to_egglog())
    
    def to_z3(self):
        return -self.value.to_z3()

    def __str__(self):
        return f"(-{self.value})"


@dataclass(frozen=True)
class Abs(RealExpr):
    value: RealExpr
    
    def to_egglog(self):
        return Math.Abs(self.value.to_egglog())
    
    def to_z3(self):
        return z3.Abs(self.value.to_z3())

    def __str__(self):
        return f"abs({self.value})"


@dataclass(frozen=True)
class Exp2(RealExpr):
    exponent: RealExpr
    
    def to_egglog(self):
        return Math.Exp2(self.exponent.to_egglog())
    
    def to_z3(self):
        return z3.RealVal(str(2)) ** self.exponent.to_z3()

    def __str__(self):
        return f"(2 ** {self.exponent})"


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

    def __str__(self):
        return f"max({self.lhs}, {self.rhs})"


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
    
    def to_z3(self):
        return z3.If(self.cond.to_z3(), self.on_true.to_z3(), self.on_false.to_z3())

    def __str__(self):
        return f"(if {self.cond} then {self.on_true} else {self.on_false})"


@dataclass(frozen=True)
class Eq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Eq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() == self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} == {self.rhs})"


@dataclass(frozen=True)
class NotEq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.NotEq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() != self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} != {self.rhs})"


@dataclass(frozen=True)
class Lt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Lt(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() < self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} < {self.rhs})"


@dataclass(frozen=True)
class Le(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Le(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() <= self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} <= {self.rhs})"


@dataclass(frozen=True)
class Gt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Gt(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() > self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} > {self.rhs})"


@dataclass(frozen=True)
class Ge(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    
    def to_egglog(self):
        return Math.Ge(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() >= self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} >= {self.rhs})"


@dataclass(frozen=True)
class BoolEq(BoolExpr):
    lhs: BoolExpr
    rhs: BoolExpr
    
    def to_egglog(self):
        return MathBool.Eq(self.lhs.to_egglog(), self.rhs.to_egglog())
    
    def to_z3(self):
        return self.lhs.to_z3() == self.rhs.to_z3()

    def __str__(self):
        return f"({self.lhs} == {self.rhs})"

    
@dataclass(frozen=True)
class Not(BoolExpr):
    value: BoolExpr
    
    def to_egglog(self):
        return MathBool.Not(self.value.to_egglog())
    
    def to_z3(self):
        return z3.Not(self.value.to_z3())

    def __str__(self):
        return f"(not {self.value})"


def ite(
    cond: BoolExpr,
    on_true: RealExpr,
    on_false: RealExpr,
) -> RealExpr:
    return If(cond, RealExpr._coerce(on_true), RealExpr._coerce(on_false))


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
            BoolEq
        ),
    ):
        return (node.lhs, node.rhs)
    raise TypeError(f"Unsupported node type: {type(node).__name__}")
