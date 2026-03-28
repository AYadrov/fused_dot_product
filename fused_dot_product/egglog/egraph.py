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
        "tool": "egglog_rewrite",
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
    from ..spec.spec_ast import Eq, BoolEq, variables
    
    def simplify_expr(expr: "SpecNode", egraph: EGraph):
        return from_egglog(egraph.extract(expr.to_egglog()))

    def simplify_check(check: BoolEq | Eq):
        lhs = check.lhs.to_egglog()
        rhs = check.rhs.to_egglog()
        check_passed = egraph.check_bool(eq(lhs).to(rhs))
        if check_passed:
            return None
        return simplify_expr(check, egraph)
    
    simplified_checks = []
    
    run_started_at = perf_counter()
    for check in ctx.checks:
        if not isinstance(check, Eq) and not isinstance(check, BoolEq):
            raise NotImplementedError(
                f"Only Eq and BoolEq checks are supported, got {type(check).__name__}"
            )
        simplified = simplify_check(check)
        if simplified is not None:
            simplified_checks.append(simplified)
    run_runtime_s = perf_counter() - run_started_at

    simplified_ctx = ctx.copy(checks=simplified_checks)
    checks_before = [str(check) for check in ctx.checks]
    checks_after = [str(check) for check in simplified_ctx.checks]
    
    equivalent = len(simplified_checks) == 0
    report = {
        "tool": "egglog_simplify",
        "equivalent": equivalent,
        "discharged_checks": len(ctx.checks) - len(simplified_checks),
        "checks_before": len(checks_before),
        "checks_after": len(checks_after),
        "runtime_s": run_runtime_s,
        # "input_context": ctx.snapshot(),
        # "output_context": simplified_ctx.snapshot(),
    }
    return equivalent, simplified_ctx, report
