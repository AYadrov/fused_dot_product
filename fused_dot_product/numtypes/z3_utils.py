from fractions import Fraction
from z3 import If, RealVal, Function, RealSort, ForAll, Real

pow2 = Function("pow2", RealSort(), RealSort())
x = Real('x')
y = Real('y')
pow2_props = [pow2(RealVal(0)) == RealVal(1), pow2(RealVal(1)) == RealVal(2), ForAll([x, y], pow2(x + y) == pow2(x) * pow2(y))]

def pow_int_2(exp):
    return pow2(exp)

def pow2_int(exp, min_exp: int, max_exp: int):
    if min_exp > max_exp:
        raise ValueError("min_exp must be <= max_exp")

    def const_pow2(k: int):
        if k >= 0:
            return RealVal(1 << k)
        frac = Fraction(1, 1 << (-k))
        return RealVal(f"{frac.numerator}/{frac.denominator}")

    expr = const_pow2(max_exp)
    for k in range(max_exp - 1, min_exp - 1, -1):
        expr = If(exp == k, const_pow2(k), expr)
    return expr
