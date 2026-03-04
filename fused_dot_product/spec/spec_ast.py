from __future__ import annotations

from dataclasses import dataclass
from fractions import Fraction
from typing import Iterator

from ..egglog import *


class SpecNode:
    def to_egglog(self):
        raise NotImplementedError
    
    def to_z3(self):
        raise NotImplementedError
    
    def to_cvc5(self):
        raise NotImplementedError

class RealExpr(SpecNode):
    pass

class BoolExpr(SpecNode):
    pass


@dataclass(frozen=True)
class RealVar(RealExpr):
    name: str
    def to_egglog(self):
        return Math.Var(self.name)


@dataclass(frozen=True)
class BoolVar(BoolExpr):
    name: str
    def to_egglog(self):
        return MathBool.Var(self.name)


@dataclass(frozen=True)
class RealLit(RealExpr):
    value: float | int
    def to_egglog(self):
        assert float(self.value) == float(int(self.value)), "only integers are working rn in egglog"
        return Math.Num(BigRat(int(self.value), 1))


@dataclass(frozen=True)
class BoolLit(BoolExpr):
    value: bool
    def to_egglog(self):
        return MathBool.True_() if self.value else MathBool.False_()


@dataclass(frozen=True)
class Add(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Sub(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Add(self.lhs.to_egglog(), Math.Neg(self.rhs.to_egglog()))

@dataclass(frozen=True)
class Mul(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Mul(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Neg(RealExpr):
    value: RealExpr
    def to_egglog(self):
        return Math.Neg(self.value.to_egglog())

@dataclass(frozen=True)
class Abs(RealExpr):
    value: RealExpr
    def to_egglog(self):
        return Math.Abs(self.value.to_egglog())

@dataclass(frozen=True)
class Exp2(RealExpr):
    exponent: RealExpr
    def to_egglog(self):
        return Math.Exp2(self.exponent.to_egglog())

@dataclass(frozen=True)
class Max(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Max(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Min(RealExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Min(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class If(RealExpr):
    cond: BoolExpr
    on_true: RealExpr
    on_false: RealExpr
    def to_egglog(self):
        return Math.If(self.cond.to_egglog(), self.on_true.to_egglog(), self.on_false.to_egglog())

@dataclass(frozen=True)
class Eq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Eq(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class NotEq(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.NotEq(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Lt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Lt(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Le(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Le(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Gt(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Gt(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Ge(BoolExpr):
    lhs: RealExpr
    rhs: RealExpr
    def to_egglog(self):
        return Math.Ge(self.lhs.to_egglog(), self.rhs.to_egglog())

@dataclass(frozen=True)
class Not(BoolExpr):
    value: BoolExpr
    def to_egglog(self):
        return MathBool.Not(self.value.to_egglog())

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

if __name__ == '__main__':
    print(Neg(RealVar("allo")).to_egglog())
