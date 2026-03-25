from __future__ import annotations

from time import perf_counter

import z3


def _stats_to_dict(stats: z3.Statistics) -> dict[str, int | float]:
    return {key: stats.get_key_value(key) for key in stats.keys()}


def _first_stat(stats: dict, key: str):
    if key in stats:
        return stats[key]
    return None


def create_solver(timeout_ms):
    z3_ctx = z3.Context(proof=True)
    solver = z3.Solver(ctx=z3_ctx)
    solver.set(timeout=timeout_ms)
    
    return solver

def z3_check_eq(ctx: "SpecContext", timeout_ms: int = 10000):
    solver = create_solver(timeout_ms)
    program = ctx.to_z3().translate(solver.ctx)
    solver.add(program)
    # print(ctx)
    
    run_started_at = perf_counter()
    result = solver.check()
    runtime_s = perf_counter() - run_started_at
    
    #stats = _stats_to_dict(solver.statistics())
    equivalent = (result == z3.unsat)
    report = {
        "name": ctx.name,
        "equivalent": equivalent,
        "runtime_s": runtime_s,
        "status": str(result),
        "timeout_ms": timeout_ms,
        #"stats": stats,
        #"smt_query": solver.to_smt2(),
    }
    
    if result == z3.sat:
        report["supplementary_info"] = solver.model()
    if result == z3.unknown:
        report["supplementary_info"] = solver.reason_unknown()
    if result == z3.unsat:
        report["supplementary_info"] = solver.proof()
    
    return equivalent, report
