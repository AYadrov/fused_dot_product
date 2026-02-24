from __future__ import annotations

from egglog import *

from .datatypes import Math


def load_rules(egraph: EGraph) -> None:
    a, b, c, e1, e2, x = vars_("a b c e1 e2 x", Math)

    zero = Math.lit(0)
    one = Math.lit(1)
    two = Math.lit(2)

    max_ab = Math.if_(a >= b, a, b)
    max_cb = Math.if_(c >= b, c, b)

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
        # Normalize negation on sums so exp2 rules can fire.
        rewrite(-(a + b)).to((-a) + (-b)),
        rewrite(-(a + (-b))).to((-a) + b),
        # Cancel the exponent-alignment max term in conventional spec.
        rewrite(Math.exp2(-(a + (-b))) * Math.exp2(a + c)).to(Math.exp2(b + c)),
        
        rewrite(Math.exp2(a + c) * Math.exp2(-(a + (-b)))).to(Math.exp2(b + c)),
        
        rewrite(Math.if_(c >= max_ab, c, max_ab)).to(Math.if_(a >= max_cb, a, max_cb)),
        rewrite(max_ab).to(Math.if_(b >= a, b, a)),
        
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
