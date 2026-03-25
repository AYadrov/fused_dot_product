from __future__ import annotations
from pprint import pprint

from egglog import *

from .datatypes import Math, MathBool

def rewrite_rules():
    from ..spec.spec_ast import RealLit, RealVar, BoolLit, BoolVar
    
    a = RealVar("a")
    b = RealVar("b")
    c = RealVar("c")
    x = RealVar("x")
    
    bool_var = BoolVar("a")
    
    zero = RealLit(0)
    one = RealLit(1)
    two = RealLit(2)
    
    true = BoolLit(True)
    
    return [
        # Associativity
        ("assoc_1", (a + (b + c)).eq((a + b) + c)),
        ("assoc_2", ((a + b) + c).eq(a + (b + c))),
        ("assoc_3", (a * (b * c)).eq((a * b) * c)),
        ("assoc_4", ((a * b) * c).eq(a * (b * c))),
        
        # Commutativity
        ("comm_1", (a + b).eq(b + a)),
        ("comm_2", (a * b).eq(b * a)),
        
        ("dist_1", ((a * b) + (a * c)).eq(a * (b + c))),
        ("dist_2", ((b * a) + (c * a)).eq(a * (b + c))),
        ("dist_3", (a * (b + c)).eq((a * b) + (a * c))),
        ("dist_4", (a * (b + c)).eq((b * a) + (c * a))),
        
        # Rules with exp2
        ("exp2_1", (two ** zero).eq(one)),
        ("exp2_2", one.eq(two ** zero)),
        
        ("exp2_3", (two ** one).eq(two)),
        ("exp2_4", two.eq(two ** one)),
        ("exp2_5", (two ** (a + b)).eq((two ** a) * (two ** b))),
        ("exp2_6", ((two ** a) * (two ** b)).eq(two ** (a + b))),
        ("exp2_7", ((two ** x) * (two ** (-x))).eq(one)),
        
         # Rules with negation of addition
        ("neg_1", (-(a + b)).eq((-a) + (-b))),
        ("neg_2", ((-a) + (-b)).eq(-(a + b))),
        ("neg_3", (-(a + (-b))).eq((-a) + b)),
        ("neg_4", ((-a) + b).eq(-(a + (-b)))),
        
        # Rules with negation of multiplication
        ("neg_mul_1", (-(a * b)).eq((-a) * b)),
        ("neg_mul_2", (-(a * b)).eq(a * (-b))),
        ("neg_mul_3", ((-a) * (-b)).eq(a * b)),
        ("neg_mul_4", (-(a * (-b))).eq(a * b)),
        
        # Rules with max operations
        ("max_1", a.max(b).eq(b.max(a))),
        ("max_2", (a.max(b).max(c)).eq(a.max(c).max(b))),
        ("max_3", (a.max(a)).eq(a)),
        
        # Negation/constants
        ("const_1", (-(-x)).eq(x)),
        ("const_2", (x + (-x)).eq(zero)),
        ("const_3", ((-x) + x).eq(zero)),
        ("const_4", (x * one).eq(x)),
        ("const_5", (one * x).eq(x)),
        ("const_6", (x * zero).eq(zero)),
        ("const_7", (zero * x).eq(zero)),
        ("const_8", (x + zero).eq(x)),
        ("const_9", (zero + x).eq(x)),
        
        # Equality
        ("eq_1", (a.eq(a)).eq(true)),
        ("eq_2", (bool_var.eq(bool_var)).eq(true)),
    ]

def constant_rules():
    m, n = vars_("m n", BigRat)
    return [
        rewrite(Math.Add(Math.Num(m), Math.Num(n))).to(Math.Num(m + n)),
        rewrite(Math.Neg(Math.Num(m))).to(Math.Num(-m)),
        rewrite(Math.Exp2(Math.Num(m))).to(Math.Num(BigRat(2, 1) ** m), eq(m.denom).to(1)),  # power works only with integers in egglog
        rewrite(Math.Mul(Math.Num(m), Math.Num(n))).to(Math.Num(m * n)),
    ]


def _lower_expr(node: SpecNode) -> Expr:
    from ..spec.spec_ast import (
        Abs,
        Add,
        BoolEq,
        BoolLit,
        BoolVar,
        Eq,
        Exp2,
        Ge,
        Gt,
        If,
        Le,
        Lt,
        Max,
        Min,
        Mul,
        Neg,
        Not,
        NotEq,
        RealLit,
        RealVar,
        Sub,
    )
    
    if isinstance(node, RealVar):
        return var(node.name, Math)
    if isinstance(node, RealLit):
        return node.to_egglog()
    if isinstance(node, Add):
        return Math.Add(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Sub):
        return Math.Add(_lower_expr(node.lhs), Math.Neg(_lower_expr(node.rhs)))
    if isinstance(node, Mul):
        return Math.Mul(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Neg):
        return Math.Neg(_lower_expr(node.value))
    if isinstance(node, Abs):
        return Math.Abs(_lower_expr(node.value))
    if isinstance(node, Exp2):
        return Math.Exp2(_lower_expr(node.exponent))
    if isinstance(node, Max):
        return Math.Max(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Min):
        return Math.Min(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, If):
        return Math.If(
            _lower_expr(node.cond),
            _lower_expr(node.on_true),
            _lower_expr(node.on_false),
        )
    if isinstance(node, BoolLit):
        return node.to_egglog()
    if isinstance(node, BoolVar):
        return var(node.name, MathBool)
    if isinstance(node, Eq):
        return Math.Eq(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, NotEq):
        return Math.NotEq(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Lt):
        return Math.Lt(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Le):
        return Math.Le(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Gt):
        return Math.Gt(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Ge):
        return Math.Ge(_lower_expr(node.lhs), _lower_expr(node.rhs))
    if isinstance(node, Not):
        return MathBool.Not(_lower_expr(node.value))
    if isinstance(node, BoolEq):
        return MathBool.Eq(_lower_expr(node.lhs), _lower_expr(node.rhs))
    raise TypeError(f"Unsupported expression node: {type(node).__name__}")


def lower_rule(rule: Eq):
    from ..spec.spec_ast import Eq, RealExpr, children
    
    lhs, rhs = children(rule)
    lowered_lhs = _lower_expr(lhs)
    lowered_rhs = _lower_expr(rhs)
    return rewrite(lowered_lhs).to(lowered_rhs)


def lower_rules(rules):
    from ..spec.spec_ast import Eq, BoolEq
    
    lowered_rules = []
    for name, rule in rules:
        if not isinstance(rule, Eq) and not isinstance(rule, BoolEq):
            raise TypeError(f"Expected Eq or BoolEq rule for {name}, got {type(rule).__name__}")
        lowered_rules.append(lower_rule(rule))
    return lowered_rules


def check_rules(rules, skip=["exp2_5", "exp2_6", "exp2_7"], z3_timeout_ms: int = 10000):
    from ..spec.spec_ast import Eq, BoolEq, children
    from ..spec.spec_context import SpecContext
    from ..smt import z3_check_eq
    
    results = {}
    for name, rule in rules:
        if name in skip:
            continue
        if not isinstance(rule, Eq) and not isinstance(rule, BoolEq):
            raise TypeError(f"Expected Eq or BoolEq rule for {name}, got {type(rule).__name__}")
        lhs, rhs = children(rule)
        ctx = SpecContext(name)
        ctx.check(lhs.eq(rhs))
        equivalent, report = z3_check_eq(ctx, timeout_ms=z3_timeout_ms)
        results[name] = equivalent or report['status']
    return results


def load_rules(egraph: EGraph) -> None:
    rules_ = rewrite_rules()
    
    # Constant rules are not checked with z3 for now
    res = check_rules(rules_)
    # pprint(res)
    
    rules = constant_rules() + lower_rules(rules_)
    egraph.register(*rules)

    
