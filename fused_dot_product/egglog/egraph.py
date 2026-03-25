from time import perf_counter

from egglog import *

from .rules import load_rules


def create_egraph() -> EGraph:
    egraph = EGraph()
    load_rules(egraph)
    return egraph

def egglog_check_eq(ctx: "SpecContext", iterations=6):
    egraph = create_egraph()
    
    to_check = ctx.to_egglog(egraph)
    
    run_started_at = perf_counter()
    
    rule_application_counts: dict[str, int] = {}
    iterations_used = 0
    equivalent = egraph.check_bool(*to_check)
    
    for _ in range(iterations):
        if equivalent:
            break
        run_report = egraph.run(1)
        iterations_used += 1
        for rule, num_matches in run_report.num_matches_per_rule.items():
            rule_name = str(rule)
            rule_application_counts[rule_name] = (
                rule_application_counts.get(rule_name, 0) + int(num_matches)
            )
        equivalent = egraph.check_bool(*to_check)
    
    run_runtime_s = perf_counter() - run_started_at
    
    report = {
        "name": ctx.name,
        "equivalent": equivalent,
        "runtime_s": run_runtime_s,
        "rule_application_counts": rule_application_counts,
        "iterations_used": iterations_used,
        "egraph": egraph,
    }
    
    return equivalent, report
    

def egglog_simplify_ctx(ctx: "SpecContext", egraph: EGraph):
    from ..spec.spec_utils import from_egglog
    from ..spec.spec_ast import Eq, BoolEq
    from pprint import pprint
    
    def simplify(expr: "SpecNode", egraph: EGraph):
        return from_egglog(egraph.extract(expr.to_egglog()))
    
    simplified_checks = []

    for check in ctx.checks:
        if not isinstance(check, Eq) and not isinstance(check, BoolEq):
            raise NotImplementedError(
                f"Only Eq and BoolEq checks are supported, got {type(check).__name__}"
            )
        lhs = check.lhs.to_egglog()
        rhs = check.rhs.to_egglog()
        check_passed = egraph.check_bool(eq(lhs).to(rhs))
        if not check_passed:
            simplified = simplify(check, egraph)
            # print(f"\t{check}\n\t{simplified}\n\n")
            simplified_checks.append(simplified)
    
    
    # Assumes must not be simplified, otherwise properties like:
    # x == (-1)**s * 1.m * 2**(e-bias)
    # with egglog simply gets simplified into x == x
    # which is not useful information anymore for other solvers
    # While checks can be simplified, they do not carry any useful information
    
    new_ctx = ctx.copy(assumes=ctx.assumes, checks=simplified_checks)
    return new_ctx
