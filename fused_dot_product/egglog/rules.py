from __future__ import annotations

from egglog import *

from .datatypes import Math


def load_rules(egraph: EGraph) -> None:
    a, b, c, e1, e2, x = vars_("a b c e1 e2 x", Math)

    zero = Math.lit(0)
    one = Math.lit(1)
    two = Math.lit(2)

    egraph.register(
        # Associativity
        rewrite(a + (b + c)).to((a + b) + c),
        rewrite((a + b) + c).to(a + (b + c)),
        rewrite(a + (b + (- c))).to(a + b + (- c)),
        rewrite((a + (- b)) + c).to(a + (- (b + (- c)))),
        rewrite(a * (b * c)).to((a * b) * c),
        rewrite((a * b) * c).to(a * (b * c)),
        # Commutativity
        rewrite(a + b).to(b + a),
        rewrite(a * b).to(b * a),
        # Distributivity
        rewrite(a * (b + c)).to((a * b) + (a * c)),
        rewrite(a * (b + c)).to((b * a) + (c * a)),
        rewrite((a * b) + (a * c)).to(a * (b + c)),
        rewrite((b * a) + (c * a)).to(a * (b + c)),
        
        # rewrite(a ** zero).to(one),
        # rewrite(a ** one).to(a),
        # rewrite(c ** (e1 + e2)).to((c ** e1) * (c ** e2)),
        # rewrite((a ** x) * (a ** (- x))).to(one),
        # rewrite((a ** (- x)) * (a ** x)).to(one),
        rewrite(Math.exp2(zero)).to(one),
        rewrite(Math.exp2(one)).to(two),
        rewrite(Math.exp2(e1 + e2)).to(Math.exp2(e1) * Math.exp2(e2)),
        rewrite(Math.exp2(x) * Math.exp2(-x)).to(one),
        rewrite(Math.exp2(-x) * Math.exp2(x)).to(one),
        
        rewrite(-(a + b)).to((-a) + (-b)),
        rewrite((-a) + (-b)).to(-(a + b)),
        rewrite(-(a + (-b))).to((-a) + b),
        rewrite((-a) + b).to(-(a + (-b))),
        
        rewrite(Math.max(a, b)).to(Math.max(b, a)),
        rewrite(Math.max(Math.max(a, b), c)).to(Math.max(Math.max(a, c), b)),
        
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
