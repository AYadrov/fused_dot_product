from time import perf_counter

from egglog import *

from .rules import load_rules
from ..solver.report import build_proof_report, merge_rule_application_counts

####################### PRIVATE ############################


def _create_egraph(simplify=False) -> EGraph:
    egraph = EGraph()
    load_rules(egraph, simplify=simplify)
    return egraph


def _egglog_check_ctx(ctx: "SpecContext", iterations=6, simplify=False):
    egraph = _create_egraph(simplify=simplify)
    
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
    
    return equivalent, run_runtime_s, egraph, rule_application_counts, iterations_used


def _simplify_expr(expr: "SpecNode", egraph: EGraph):
    from ..spec.spec_utils import from_egglog
    return from_egglog(egraph.extract(expr.to_egglog()))


def _egglog_simplify_ctx(ctx: "SpecContext", egraph: EGraph):
    from ..spec.spec_ast import Eq, BoolEq
    
    def simplify_check(check: BoolEq | Eq):
        lhs = check.lhs.to_egglog()
        rhs = check.rhs.to_egglog()
        check_passed = egraph.check_bool(eq(lhs).to(rhs))
        if check_passed:
            return None
        return _simplify_expr(check, egraph)
    
    simplified_checks = []
    discharged_checks = []
    
    run_started_at = perf_counter()
    for check in ctx.checks:
        if not isinstance(check, Eq) and not isinstance(check, BoolEq):
            raise NotImplementedError(
                f"Only Eq and BoolEq checks are supported, got {type(check).__name__}"
            )
        simplified = simplify_check(check)
        if simplified is not None:
            simplified_checks.append(simplified)
        else:
            discharged_checks.append(check)
    run_runtime_s = perf_counter() - run_started_at

    simplified_ctx = ctx.copy(assumes=ctx.assumes + discharged_checks, checks=simplified_checks)
    equivalent = len(simplified_checks) == 0
    return equivalent, run_runtime_s, simplified_ctx


####################### PUBLIC #############################


def egglog_rewrite(ctx: "SpecContext", iterations: int):
    equivalent, egglog_runtime_s, egraph, rule_application_counts, iterations_used = _egglog_check_ctx(
        ctx=ctx,
        iterations=iterations,
        simplify=False,
    )
    equivalent, simplify_runtime_s, simplified_ctx = _egglog_simplify_ctx(
        ctx=ctx,
        egraph=egraph,
    )

    report = build_proof_report(
        ctx,
        simplified_ctx,
        tool="egglog_rewrite",
        runtime_s=egglog_runtime_s + simplify_runtime_s,
        equivalent=equivalent,
        rule_application_counts=rule_application_counts,
        iterations_used=iterations_used,
        egraph=egraph,
    )
    return equivalent, simplified_ctx, report


# TODO: MAYBE WE SHOULD NOT SIMPLIFY ASSUMES
def egglog_preprocess(ctx: "SpecContext", iterations: int):
    from ..spec.spec_ast import Eq, BoolEq

    # Preprocess checks
    equivalent, egglog_runtime_s, egraph, check_rule_application_counts, check_iterations_used = _egglog_check_ctx(
        ctx=ctx,
        iterations=iterations,
        simplify=True,
    )
    equivalent, simplify_runtime_s, simplified_ctx = _egglog_simplify_ctx(ctx=ctx, egraph=egraph)

    # Preprocess assumes
    egraph = _create_egraph(simplify=True)
    preprocessed_assumes = []
    preprocessed_checks = simplified_ctx.checks
    
    for assume in simplified_ctx.assumes:
        egraph.register(assume.to_egglog())

    run_started_at = perf_counter()
    assume_run_report = egraph.run(iterations)
    assume_runtime_s = perf_counter() - run_started_at

    assume_rule_application_counts = {
        str(rule): int(num_matches)
        for rule, num_matches in assume_run_report.num_matches_per_rule.items()
    }

    for assume in simplified_ctx.assumes:
        simplified = _simplify_expr(assume, egraph)
        if simplified == ctx.false():
            equivalent = False
        elif simplified != ctx.true():
            # zpreprocessed_assumes.append(assume)  # TODO: not fully sound, for full soundness we don't want to simplify assumes
            preprocessed_assumes.append(simplified)

    preprocessed_ctx = ctx.copy(
        assumes=preprocessed_assumes,
        checks=preprocessed_checks,
    )

    report = build_proof_report(
        ctx,
        preprocessed_ctx,
        tool="egglog_preprocess",
        runtime_s=egglog_runtime_s + simplify_runtime_s + assume_runtime_s,
        equivalent=equivalent,
        rule_application_counts=merge_rule_application_counts(
            check_rule_application_counts,
            assume_rule_application_counts,
        ),
        iterations_used=check_iterations_used + iterations,
        egraph=egraph,
    )
    return equivalent, preprocessed_ctx, report
