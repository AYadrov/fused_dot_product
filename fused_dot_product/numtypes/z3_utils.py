from fractions import Fraction
from cvc5.pythonic import Function, RealSort, RealVal

# Keep pow2 axioms bounded to avoid quantifiers in the solver.
POW2_MIN_EXP = -512
POW2_MAX_EXP = 512

pow2 = Function("pow2", RealSort(), RealSort())

def _pow2_const(exp: int):
    if exp >= 0:
        return RealVal(2 ** exp)
    return RealVal(Fraction(1, 2 ** (-exp)))

pow2_props = [
    pow2(RealVal(exp)) == _pow2_const(exp)
    for exp in range(POW2_MIN_EXP, POW2_MAX_EXP + 1)
]

def pow2_real(exp):
    return pow2(exp)
