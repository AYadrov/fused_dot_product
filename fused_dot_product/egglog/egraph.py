from time import perf_counter

from egglog import *

from .datatypes import MathBool
from .rules import load_rules
from ..solver.report import build_proof_report, merge_rule_application_counts

####################### PRIVATE ############################


def _create_egraph(simplify=False) -> EGraph:
    egraph = EGraph()
    load_rules(egraph, simplify=simplify)
    return egraph


def _make_run_schedule(scheduler: dict[str, int | None] | None):
    if scheduler is None:
        return 1
    return run(
        scheduler=back_off(
            match_limit=scheduler.get("match_limit"),
            ban_length=scheduler.get("ban_length"),
        )
    )


def _egglog_check_ctx(ctx: "SpecContext", iterations=6, simplify=False, scheduler=None):
    egraph = _create_egraph(simplify=simplify)
    
    to_check = ctx.to_egglog(egraph)
    run_schedule = _make_run_schedule(scheduler)
    
    run_started_at = perf_counter()
    
    rule_application_counts: dict[str, int] = {}
    iterations_used = 0
    proved = egraph.check_bool(*to_check)
    
    for _ in range(iterations):
        if proved:
            break
        run_report = egraph.run(run_schedule)
        iterations_used += 1
        for rule, num_matches in run_report.num_matches_per_rule.items():
            rule_name = str(rule)
            rule_application_counts[rule_name] = (
                rule_application_counts.get(rule_name, 0) + int(num_matches)
            )
        proved = egraph.check_bool(*to_check)
        
    run_runtime_s = perf_counter() - run_started_at
    
    return proved, run_runtime_s, egraph, rule_application_counts, iterations_used


def _simplify_expr(expr: "SpecNode", egraph: EGraph):
    from ..spec.spec_utils import from_egglog
    return from_egglog(egraph.extract(expr.to_egglog()))


def _egglog_simplify_ctx(ctx: "SpecContext", egraph: EGraph):
    from ..spec.spec_ast import Eq, BoolEq, BoolExpr
    
    def simplify_check(check: BoolExpr):
        if isinstance(check, Eq) or isinstance(check, BoolEq):
            lhs = check.lhs.to_egglog()
            rhs = check.rhs.to_egglog()
            check_passed = egraph.check_bool(eq(lhs).to(rhs))
        else:
            expr = check.to_egglog()
            check_passed = egraph.check_bool(eq(expr).to(MathBool.True_()))
        if check_passed:
            return None
        return _simplify_expr(check, egraph)
    
    simplified_checks = []
    discharged_checks = []
    
    run_started_at = perf_counter()
    for check in ctx.checks:
        if not isinstance(check, BoolExpr):
            raise NotImplementedError(
                f"Only BoolExpr checks are supported, got {type(check).__name__}"
            )
        simplified = simplify_check(check)
        if simplified is not None:
            simplified_checks.append(simplified)
        else:
            discharged_checks.append(check)
    run_runtime_s = perf_counter() - run_started_at

    simplified_ctx = ctx.copy(assumes=ctx.assumes + discharged_checks, checks=simplified_checks)
    status = "unsat" if len(simplified_checks) == 0 else "unknown"
    return status, run_runtime_s, simplified_ctx


####################### PUBLIC #############################


def egglog_rewrite(ctx: "SpecContext", iterations: int, scheduler=None):
    proved, egglog_runtime_s, egraph, rule_application_counts, iterations_used = _egglog_check_ctx(
        ctx=ctx,
        iterations=iterations,
        simplify=False,
        scheduler=scheduler,
    )
    status, simplify_runtime_s, simplified_ctx = _egglog_simplify_ctx(
        ctx=ctx,
        egraph=egraph,
    )

    report = build_proof_report(
        ctx,
        simplified_ctx,
        tool="egglog-rewrite",
        runtime_s=egglog_runtime_s + simplify_runtime_s,
        status=status,
        rule_application_counts=rule_application_counts,
        iterations_used=iterations_used,
        egraph=egraph,
        egraph_size=sum(sz for _, sz in egraph.all_function_sizes()),
    )
    return report


# TODO: MAYBE WE SHOULD NOT SIMPLIFY ASSUMES
def egglog_preprocess(ctx: "SpecContext", iterations: int, scheduler=None):
    from ..spec.spec_ast import Eq, BoolEq

    # Preprocess checks
    proved, egglog_runtime_s, egraph, check_rule_application_counts, check_iterations_used = _egglog_check_ctx(
        ctx=ctx,
        iterations=iterations,
        simplify=True,
        scheduler=scheduler,
    )
    status, simplify_runtime_s, simplified_ctx = _egglog_simplify_ctx(ctx=ctx, egraph=egraph)

    simplified_checks_report = build_proof_report(
        ctx,
        simplified_ctx,
        tool="egglog-preprocess",
        runtime_s=egglog_runtime_s + simplify_runtime_s,
        status=status,
        rule_application_counts=check_rule_application_counts,
        iterations_used=check_iterations_used,
        egraph=egraph,
        egraph_size=sum(sz for _, sz in egraph.all_function_sizes()),
    )

    if status == "unsat":
        return simplified_checks_report

    # Preprocess assumes
    egraph = _create_egraph(simplify=True)
    preprocessed_assumes = []
    preprocessed_checks = simplified_ctx.checks
    false_assumes = []
    
    for assume in simplified_ctx.assumes:
        egraph.register(assume.to_egglog())

    run_started_at = perf_counter()
    assume_run_report = egraph.run(_make_run_schedule(scheduler) * iterations)
    assume_runtime_s = perf_counter() - run_started_at

    assume_rule_application_counts = {
        str(rule): int(num_matches)
        for rule, num_matches in assume_run_report.num_matches_per_rule.items()
    }

    for assume in simplified_ctx.assumes:
        simplified = _simplify_expr(assume, egraph)
        if simplified == ctx.false():
            false_assumes.append(str(assume))
            preprocessed_assumes.append(simplified)
        elif simplified != ctx.true():
            preprocessed_assumes.append(simplified) # TODO: not fully sound, for full soundness we don't want to simplify assumes

    preprocessed_ctx = ctx.copy(
        assumes=preprocessed_assumes,
        checks=preprocessed_checks,
    )
    extra = {}
    if false_assumes:
        extra["false_assumes"] = false_assumes

    simplified_assumes_report = build_proof_report(
        ctx,
        preprocessed_ctx,
        tool="egglog-preprocess",
        runtime_s=egglog_runtime_s + simplify_runtime_s + assume_runtime_s,
        status="unknown",
        rule_application_counts=merge_rule_application_counts(
            check_rule_application_counts,
            assume_rule_application_counts,
        ),
        iterations_used=check_iterations_used + iterations,
        egraph=egraph,
        **extra,
    )

    dummy_report = build_proof_report(ctx, ctx.copy(), tool="copy", runtime_s=0.0, status="unknown")
    
    return [simplified_assumes_report, simplified_checks_report, dummy_report]
