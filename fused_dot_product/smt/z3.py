from __future__ import annotations

from time import perf_counter

import z3


z3_exp2 = z3.Function("exp2", z3.RealSort(), z3.RealSort())


def _ctx_exp2(ctx: z3.Context) -> z3.FuncDeclRef:
    return z3_exp2.translate(ctx)

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
    exp2 = _ctx_exp2(z3_ctx)
    
    x = z3.FreshConst(z3.RealSort(ctx=z3_ctx))
    y = z3.FreshConst(z3.RealSort(ctx=z3_ctx))

    solver.add(exp2(z3.RealVal(0, ctx=z3_ctx)) == z3.RealVal(1, ctx=z3_ctx))
    solver.add(exp2(z3.RealVal(1, ctx=z3_ctx)) == z3.RealVal(2, ctx=z3_ctx))
    solver.add(z3.ForAll([x, y], exp2(x + y) == exp2(x) * exp2(y)))
    solver.add(z3.ForAll([x, y], exp2(x - y) == exp2(x) * exp2(-y)))
    
    return solver


def z3_check_eq(ctx: "SpecContext", timeout_ms: int = 10000):
    solver = create_solver(timeout_ms)
    program = ctx.to_z3().translate(solver.ctx)
    print(program)
    solver.add(program)
    
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
