from __future__ import annotations

from egglog import *

from .datatypes import Math


def load_rules(egraph: EGraph) -> None:
    a, b, c, x = vars_("a b c x", Math)
    m, n = vars_("m n", BigRat)
    
    zero = Math.lit(0)
    one = Math.lit(1)
    two = Math.lit(2)

    egraph.register(
        # Constant folding
        rewrite(Math.num(m) + Math.num(n)).to(Math.num(m + n)),
        rewrite(-Math.num(m)).to(Math.num(-m)),
        rewrite(Math.exp2(Math.num(m))).to(Math.num(BigRat(2, 1) ** m), eq(m.denom).to(1)),
        rewrite(Math.num(m) * Math.num(n)).to(Math.num(m * n)),
        
        # Associativity
        rewrite(a + (b + c)).to((a + b) + c),
        rewrite((a + b) + c).to(a + (b + c)),
        rewrite(a * (b * c)).to((a * b) * c),
        rewrite((a * b) * c).to(a * (b * c)),
        
        # Commutativity
        rewrite(a + b).to(b + a),
        rewrite(a * b).to(b * a),
        
        # Distributivity
        rewrite((a * b) + (a * c)).to(a * (b + c)),
        rewrite((b * a) + (c * a)).to(a * (b + c)),
        
        rewrite(a * (b + c)).to((a * b) + (a * c)),
        rewrite(a * (b + c)).to((b * a) + (c * a)),
        
        # Rules with exp2
        rewrite(Math.exp2(zero)).to(one),
        rewrite(one).to(Math.exp2(zero)),
        
        rewrite(Math.exp2(one)).to(two),
        rewrite(two).to(Math.exp2(one)),
        
        rewrite(Math.exp2(a + b)).to(Math.exp2(a) * Math.exp2(b)),
        rewrite(Math.exp2(a) * Math.exp2(b)).to(Math.exp2(a + b)),
        
        rewrite(Math.exp2(x) * Math.exp2(-x)).to(one),
        
        # Rules with negation of addition
        rewrite(-(a + b)).to((-a) + (-b)),
        rewrite((-a) + (-b)).to(-(a + b)),
        
        rewrite(-(a + (-b))).to((-a) + b),
        rewrite((-a) + b).to(-(a + (-b))),
        
        # Rules with negation of multiplication
        rewrite(-(a * b)).to((-a) * b),
        rewrite(-(a * b)).to(a * (-b)),
        rewrite((-a) * (-b)).to(a * b),
        rewrite(-(a * (-b))).to(a * b),
        
        # Rules with max operations
        rewrite(Math.max(a, b)).to(Math.max(b, a)),
        rewrite(Math.max(Math.max(a, b), c)).to(Math.max(Math.max(a, c), b)),
        rewrite(Math.max(a, a)).to(a),
        
        # Negation/constants
        rewrite(- (-x)).to(x),
        rewrite(x + (-x)).to(zero),
        rewrite((-x) + x).to(zero),
        rewrite(x * one).to(x),
        rewrite(one * x).to(x),
        rewrite(x * zero).to(zero),
        rewrite(zero * x).to(zero),
        rewrite(x + zero).to(x),
        rewrite(zero + x).to(x),
    )
