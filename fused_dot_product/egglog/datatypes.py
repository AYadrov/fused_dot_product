from __future__ import annotations

from fractions import Fraction
from typing import TypeAlias

from random import randint
from itertools import count

from egglog import *

"""
(datatype Math
  (Num BigRat)
  (Var String)
  // (Sign String)
  (Add Math Math)
  // (Sub Math Math)
  (Mul Math Math)
  // (Div Math Math)
  (Pow Math Math)
  (Exp2 Math)
  (If Math Math Math)
  (Ge Math Math)
  (Neg Math))
"""

_sym_counter = count()


class Math(Expr):
    @method(egg_fn="Num")
    @classmethod
    def num(cls, value: BigRatLike) -> Math: ...
    
    @method(egg_fn="Var")
    @classmethod
    def var(cls, name: StringLike) -> Math: ...
    
    # @method(egg_fn="Sign")
    # @classmethod
    # def sign(cls, name: StringLike) -> Math: ...

    @method(egg_fn="Add")
    def __add__(self, other: Math) -> Math: ...

    @method(egg_fn="Mul")
    def __mul__(self, other: Math) -> Math: ...
    
    @method(egg_fn="Exp2")
    @classmethod
    def exp2(cls, exponent: Math) -> Math: ...

    @method(egg_fn="Neg")
    def __neg__(self) -> Math: ...

    @method(egg_fn="Max")
    @classmethod
    def max(cls, expr1: Math, expr2: Math) -> Math: ...

    @classmethod
    def lit(cls, value: i64Like) -> Math:
        return cls.num(BigRat(value, 1))


def _fresh_var(cls, base: str) -> Math:
    return cls.var(f"{base}_{next(_sym_counter)}")

Math.fresh_var = classmethod(_fresh_var)


