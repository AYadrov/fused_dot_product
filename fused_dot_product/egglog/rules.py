from __future__ import annotations

from egglog import *

from .datatypes import Math


def load_rules(egraph: EGraph) -> None:
    a, b, c, x = vars_("a b c x", Math)
    m, n = vars_("m n", BigRat)
    
    zero = Math.Num(BigRat(0, 1))
    one = Math.Num(BigRat(1, 1))
    two = Math.Num(BigRat(2, 1))

    egraph.register(
        # Constant folding
        rewrite(Math.Add(Math.Num(m), Math.Num(n))).to(Math.Num(m + n)),
        rewrite(Math.Neg(Math.Num(m))).to(Math.Num(-m)),
        rewrite(Math.Exp2(Math.Num(m))).to(Math.Num(BigRat(2, 1) ** m), eq(m.denom).to(1)),
        rewrite(Math.Mul(Math.Num(m), Math.Num(n))).to(Math.Num(m * n)),
        
        # Associativity
        rewrite(Math.Add(a, Math.Add(b, c))).to(Math.Add(Math.Add(a, b), c)),
        rewrite(Math.Add(Math.Add(a, b), c)).to(Math.Add(a, Math.Add(b, c))),
        rewrite(Math.Mul(a, Math.Mul(b, c))).to(Math.Mul(Math.Mul(a, b), c)),
        rewrite(Math.Mul(Math.Mul(a, b), c)).to(Math.Mul(a, Math.Mul(b, c))),
        
        # Commutativity
        rewrite(Math.Add(a, b)).to(Math.Add(b, a)),
        rewrite(Math.Mul(a, b)).to(Math.Mul(b, a)),
        
        # Distributivity
        rewrite(Math.Add(Math.Mul(a, b), Math.Mul(a, c))).to(Math.Mul(a, Math.Add(b, c))),
        rewrite(Math.Add(Math.Mul(b, a), Math.Mul(c, a))).to(Math.Mul(a, Math.Add(b, c))),
        
        rewrite(Math.Mul(a, Math.Add(b, c))).to(Math.Add(Math.Mul(a, b), Math.Mul(a, c))),
        rewrite(Math.Mul(a, Math.Add(b, c))).to(Math.Add(Math.Mul(b, a), Math.Mul(c, a))),
        
        # Rules with exp2
        rewrite(Math.Exp2(zero)).to(one),
        rewrite(one).to(Math.Exp2(zero)),
        
        rewrite(Math.Exp2(one)).to(two),
        rewrite(two).to(Math.Exp2(one)),
        
        rewrite(Math.Exp2(Math.Add(a, b))).to(Math.Mul(Math.Exp2(a), Math.Exp2(b))),
        rewrite(Math.Mul(Math.Exp2(a), Math.Exp2(b))).to(Math.Exp2(Math.Add(a, b))),
        
        rewrite(Math.Mul(Math.Exp2(x), Math.Exp2(Math.Neg(x)))).to(one),
        
        # Rules with negation of addition
        rewrite(Math.Neg(Math.Add(a, b))).to(Math.Add(Math.Neg(a), Math.Neg(b))),
        rewrite(Math.Add(Math.Neg(a), Math.Neg(b))).to(Math.Neg(Math.Add(a, b))),
        
        rewrite(Math.Neg(Math.Add(a, Math.Neg(b)))).to(Math.Add(Math.Neg(a), b)),
        rewrite(Math.Add(Math.Neg(a), b)).to(Math.Neg(Math.Add(a, Math.Neg(b)))),
        
        # Rules with negation of multiplication
        rewrite(Math.Neg(Math.Mul(a, b))).to(Math.Mul(Math.Neg(a), b)),
        rewrite(Math.Neg(Math.Mul(a, b))).to(Math.Mul(a, Math.Neg(b))),
        rewrite(Math.Mul(Math.Neg(a), Math.Neg(b))).to(Math.Mul(a, b)),
        rewrite(Math.Neg(Math.Mul(a, Math.Neg(b)))).to(Math.Mul(a, b)),
        
        # Rules with max operations
        rewrite(Math.Max(a, b)).to(Math.Max(b, a)),
        rewrite(Math.Max(Math.Max(a, b), c)).to(Math.Max(Math.Max(a, c), b)),
        rewrite(Math.Max(a, a)).to(a),
        
        # Negation/constants
        rewrite(Math.Neg(Math.Neg(x))).to(x),
        rewrite(Math.Add(x, Math.Neg(x))).to(zero),
        rewrite(Math.Add(Math.Neg(x), x)).to(zero),
        rewrite(Math.Mul(x, one)).to(x),
        rewrite(Math.Mul(one, x)).to(x),
        rewrite(Math.Mul(x, zero)).to(zero),
        rewrite(Math.Mul(zero, x)).to(zero),
        rewrite(Math.Add(x, zero)).to(x),
        rewrite(Math.Add(zero, x)).to(x),
    )
