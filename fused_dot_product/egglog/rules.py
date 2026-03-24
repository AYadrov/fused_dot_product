from __future__ import annotations
from pprint import pprint

from egglog import *

from .datatypes import Math


def rewrite_rules():
    from ..spec.spec_ast import RealLit, RealVar

    a = RealVar("a")
    b = RealVar("b")
    c = RealVar("c")
    x = RealVar("x")

    zero = RealLit(0)
    one = RealLit(1)
    two = RealLit(2)

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
        ("const_2", (x + (-x)).eq(zero)),
        ("const_4", (x * one).eq(x)),
        ("const_5", (one * x).eq(x)),
        ("const_6", (x * zero).eq(zero)),
        ("const_9", (zero + x).eq(x)),
    ]

def constant_rules():
    m, n = vars_("m n", BigRat)
    return [
        rewrite(Math.Add(Math.Num(m), Math.Num(n))).to(Math.Num(m + n)),
        rewrite(Math.Neg(Math.Num(m))).to(Math.Num(-m)),
        rewrite(Math.Exp2(Math.Num(m))).to(Math.Num(BigRat(2, 1) ** m), eq(m.denom).to(1)),
        rewrite(Math.Mul(Math.Num(m), Math.Num(n))).to(Math.Num(m * n)),
    ]


def _collect_real_var_names(node: SpecNode) -> set[str]:
    from ..spec.spec_ast import (
        Abs,
        Add,
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
        return {node.name}
    if isinstance(node, (RealLit, BoolLit, BoolVar)):
        return set()
    if isinstance(node, (Neg, Abs)):
        return _collect_real_var_names(node.value)
    if isinstance(node, Exp2):
        return _collect_real_var_names(node.exponent)
    if isinstance(node, Not):
        return _collect_real_var_names(node.value)
    if isinstance(
        node,
        (
            Add,
            Sub,
            Mul,
            Max,
            Min,
            Eq,
            NotEq,
            Lt,
            Le,
            Gt,
            Ge,
        ),
    ):
        return _collect_real_var_names(node.lhs) | _collect_real_var_names(node.rhs)
    if isinstance(node, If):
        return (
            _collect_real_var_names(node.cond)
            | _collect_real_var_names(node.on_true)
            | _collect_real_var_names(node.on_false)
        )
    raise TypeError(f"Unsupported node in variable collection: {type(node).__name__}")


def _lower_expr(node: SpecNode, vars_env: dict[str, Expr]) -> Expr:
    from ..spec.spec_ast import (
        Abs,
        Add,
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
        return vars_env[node.name]
    if isinstance(node, RealLit):
        return node.to_egglog()
    if isinstance(node, Add):
        return Math.Add(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Sub):
        return Math.Add(_lower_expr(node.lhs, vars_env), Math.Neg(_lower_expr(node.rhs, vars_env)))
    if isinstance(node, Mul):
        return Math.Mul(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Neg):
        return Math.Neg(_lower_expr(node.value, vars_env))
    if isinstance(node, Abs):
        return Math.Abs(_lower_expr(node.value, vars_env))
    if isinstance(node, Exp2):
        return Math.Exp2(_lower_expr(node.exponent, vars_env))
    if isinstance(node, Max):
        return Math.Max(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Min):
        return Math.Min(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, If):
        return Math.If(
            _lower_expr(node.cond, vars_env),
            _lower_expr(node.on_true, vars_env),
            _lower_expr(node.on_false, vars_env),
        )
    if isinstance(node, BoolLit):
        return node.to_egglog()
    if isinstance(node, BoolVar):
        raise NotImplementedError("BoolVar lowering to egglog rewrite is not supported")
    if isinstance(node, Eq):
        return Math.Eq(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, NotEq):
        return Math.NotEq(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Lt):
        return Math.Lt(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Le):
        return Math.Le(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Gt):
        return Math.Gt(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Ge):
        return Math.Ge(_lower_expr(node.lhs, vars_env), _lower_expr(node.rhs, vars_env))
    if isinstance(node, Not):
        return MathBool.Not(_lower_expr(node.value, vars_env))
    raise TypeError(f"Unsupported expression node: {type(node).__name__}")


def lower_rule(rule: Eq):
    from ..spec.spec_ast import Eq, RealExpr, children

    lhs, rhs = children(rule)
    if not isinstance(lhs, RealExpr) or not isinstance(rhs, RealExpr):
        raise TypeError("Only real equalities can be lowered into egglog rewrites")

    var_names = sorted(_collect_real_var_names(rule))
    vars_env: dict[str, Math] = {}
    if var_names:
        lowered_vars = tuple(vars_(" ".join(var_names), Math))
        vars_env = {name: var for name, var in zip(var_names, lowered_vars)}

    lowered_lhs = _lower_expr(lhs, vars_env)
    lowered_rhs = _lower_expr(rhs, vars_env)
    return rewrite(lowered_lhs).to(lowered_rhs)


def lower_rules(rules):
    from ..spec.spec_ast import Eq

    lowered_rules = []
    for name, rule in rules:
        if not isinstance(rule, Eq):
            raise TypeError(f"Expected Eq rule for {name}, got {type(rule).__name__}")
        lowered_rules.append(lower_rule(rule))
    return lowered_rules


def check_rules(rules, z3_timeout_ms: int = 10000):
    from ..spec.spec_ast import Eq, children
    from ..spec.spec_context import SpecContext
    from ..smt import z3_check_eq

    results = {}
    for name, rule in rules:
        if not isinstance(rule, Eq):
            raise TypeError(f"Expected Eq rule for {name}, got {type(rule).__name__}")
        lhs, rhs = children(rule)
        ctx = SpecContext(name)
        ctx.check(lhs.eq(rhs))
        equivalent, _ = z3_check_eq(ctx, timeout_ms=z3_timeout_ms)
        results[name] = equivalent
    return results


def load_rules(egraph: EGraph) -> None:
    rules_ = rewrite_rules()
    
    res = check_rules(rules_)
    pprint(res)
    
    # Constant rules are not checked with z3 for now
    rules = constant_rules() + lower_rules(rules_)
    egraph.register(*rules)

    
