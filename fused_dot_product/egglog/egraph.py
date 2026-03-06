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
    run_report = egraph.run(iterations)
    run_runtime_s = perf_counter() - run_started_at
    
    rule_application_counts = {
        str(rule): int(num_matches)
        for rule, num_matches in run_report.num_matches_per_rule.items()
    }
    
    equivalent = False
    try:
        for check in to_check:
            egraph.check(check)
        equivalent = True
    except EggSmolError:
        equivalent = False
    
    report = {
        "name": ctx.name,
        "equivalent": equivalent,
        "runtime_s": run_runtime_s,
        "rule_application_counts": rule_application_counts,
        "egraph": egraph,
    }
    
    return equivalent, report

def egglog_simplify_ctx(ctx: "SpecContext", egraph: EGraph):
    def simplify(expr: "SpecNode", egraph: EGraph):
        return from_egglog(egraph.extract(expr.to_egglog()))
    
    simplified_assumes = []
    for assume in ctx.assumes:
        simplified_assumes.append(simplify(assume, egraph))
    
    simplified_checks = []
    for check in ctx.checks:
        simplified_checks.append(simplify(check, egraph))
    
    new_ctx = ctx.copy(assumes=simplified_assumes, checks=simplified_checks)
    return new_ctx
