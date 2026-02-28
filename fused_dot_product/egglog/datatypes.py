from __future__ import annotations

from fractions import Fraction
from typing import TypeAlias

from random import randint
from itertools import count

from egglog import *

_sym_counter = count()

class MathBool(Expr):
    @method(egg_fn="BoolNeg")
    @classmethod
    def not_(cls, value: MathBool) -> MathBool: ...
    
    @method(egg_fn="BoolVar")
    @classmethod
    def var(cls, name: StringLike) -> MathBool: ...
    
    @method(egg_fn="BoolVal")
    @classmethod
    def val(cls, name: BoolLike) -> MathBool: ...

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
    
    @method(egg_fn="Abs")
    def __abs__(self) -> Math: ...
    
    @method(egg_fn="Max")
    @classmethod
    def max(cls, expr1: Math, expr2: Math) -> Math: ...
    
    @method(egg_fn="Min")
    @classmethod
    def min(cls, expr1: Math, expr2: Math) -> Math: ...
    
    ######## BOOLEAN LOGIC THAT IS NOT CURRENTLY USED ######
    @method(egg_fn="Lt")
    def __lt__(self, other: Math) -> MathBool: ...
    
    @method(egg_fn="Le")
    def __le__(self, other: Math) -> MathBool: ...
    
    @method(egg_fn="Gt")
    def __gt__(self, other: Math) -> MathBool: ...
    
    @method(egg_fn="Ge")
    def __ge__(self, other: Math) -> MathBool: ...
    
    @method(egg_fn="NotEq")
    def __ne__(self, other: Math) -> MathBool: ...
    
    @method(egg_fn="Eq")
    def __eq__(self, other: Math) -> MathBool: ...
    
    @method(egg_fn="If")
    @classmethod
    def if_(cls, cnd: MathBool, tru: Math, fls: Math) -> Math: ...


def _lit(cls, value) -> Math:
    assert float(value) == float(int(value))
    return cls.num(BigRat(int(value), 1))

def _math_fresh_var(cls, base: str) -> Math:
    return cls.var(f"{base}_{next(_sym_counter)}")
    
def _mathbool_fresh_var(cls, base: str) -> MathBool:
    return cls.var(f"{base}_{next(_sym_counter)}")

Math.fresh_var = classmethod(_math_fresh_var)
MathBool.fresh_var = classmethod(_mathbool_fresh_var)
Math.lit = classmethod(_lit)
