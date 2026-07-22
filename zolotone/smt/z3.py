from __future__ import annotations

from time import perf_counter

import z3

from ..solver.report import build_proof_report

####################### PRIVATE ############################

def _stats_to_dict(stats: z3.Statistics) -> dict[str, int | float]:
    return {key: stats.get_key_value(key) for key in stats.keys()}


def _first_stat(stats: dict, key: str):
    if key in stats:
        return stats[key]
    return None


def _create_solver(timeout_ms, proof=True):
    z3_ctx = z3.Context(proof=proof)
    solver = z3.Solver(ctx=z3_ctx)
    solver.set(timeout=timeout_ms)
    
    return solver


def _check_solver(ctx: "SpecContext", timeout_ms: int, proof: bool):
    solver = _create_solver(timeout_ms, proof=proof)
    program = ctx.to_z3().translate(solver.ctx)
    solver.add(program)

    run_started_at = perf_counter()
    result = solver.check()
    runtime_s = perf_counter() - run_started_at

    return solver, result, runtime_s

####################### PUBLIC #############################

def z3_check_eq(ctx: "SpecContext", timeout_ms: int):
    solver, result, runtime_s = _check_solver(ctx, timeout_ms=timeout_ms, proof=True)
    proof_retry_reason = None
    if result == z3.unknown and "proof production" in solver.reason_unknown():
        proof_retry_reason = solver.reason_unknown()
        solver, result, retry_runtime_s = _check_solver(ctx, timeout_ms=timeout_ms, proof=False)
        runtime_s += retry_runtime_s
    
    #stats = _stats_to_dict(solver.statistics())
    status = str(result)
    new_ctx = ctx.copy()
    report = build_proof_report(
        ctx,
        new_ctx,
        tool="z3",
        runtime_s=runtime_s,
        status=status,
        timeout_ms=timeout_ms,
        #stats=stats,
        #smt_query=solver.to_smt2(),
    )
    
    if result == z3.sat:
        report["supplementary_info"] = str(solver.model())
    if result == z3.unknown:
        report["supplementary_info"] = solver.reason_unknown()
    if result == z3.unsat:
        if proof_retry_reason is None:
            report["supplementary_info"] = str(solver.proof())
        else:
            report["supplementary_info"] = {
                "proof_retry_reason": proof_retry_reason,
                "proof": None,
            }
    
    return report
