from fractions import Fraction
from z3 import If, RealVal, Function, RealSort, ForAll, Real

pow2 = Function("pow2", RealSort(), RealSort())
x = Real('x')
y = Real('y')
pow2_props = [
    pow2(RealVal(0)) == RealVal(1), 
    pow2(RealVal(1)) == RealVal(2), 
    ForAll([x, y], pow2(x + y) == pow2(x) * pow2(y)), 
    ForAll([x, y], pow2(x - y) == pow2(x) / pow2(y))
]

def pow2_int(exp):
    return pow2(exp)

