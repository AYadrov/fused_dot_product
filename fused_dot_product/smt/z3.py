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


def _create_solver(timeout_ms):
    z3_ctx = z3.Context(proof=True)
    solver = z3.Solver(ctx=z3_ctx)
    solver.set(timeout=timeout_ms)
    
    return solver

####################### PUBLIC #############################

def z3_check_eq(ctx: "SpecContext", timeout_ms: int):
    solver = _create_solver(timeout_ms)
    program = ctx.to_z3().translate(solver.ctx)
    solver.add(program)
    
    run_started_at = perf_counter()
    result = solver.check()
    runtime_s = perf_counter() - run_started_at
    
    #stats = _stats_to_dict(solver.statistics())
    equivalent = (result == z3.unsat)
    new_ctx = ctx.copy()
    report = build_proof_report(
        ctx,
        new_ctx,
        tool="z3",
        runtime_s=runtime_s,
        equivalent=equivalent,
        status=str(result),
        timeout_ms=timeout_ms,
        #stats=stats,
        #smt_query=solver.to_smt2(),
    )
    
    if result == z3.sat:
        report["supplementary_info"] = solver.model()
    if result == z3.unknown:
        report["supplementary_info"] = solver.reason_unknown()
    if result == z3.unsat:
        report["supplementary_info"] = solver.proof()
    
    return equivalent, new_ctx, report
