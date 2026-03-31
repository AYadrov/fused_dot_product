from __future__ import annotations

from time import perf_counter

import dreal


def dreal_check_eq(ctx: "SpecContext", precision: float = 0.001):
    program = ctx.to_dreal()
    
    run_started_at = perf_counter()
    result = dreal.CheckSatisfiability(program, precision)
    runtime_s = perf_counter() - run_started_at
    
    equivalent = result is None
    status = "unsat" if equivalent else "delta-sat"
    report = {
        "tool": "dreal",
        "name": ctx.name,
        "equivalent": equivalent,
        "runtime_s": runtime_s,
        "status": status,
        "precision": precision,
    }
    
    if result is not None:
        report["supplementary_info"] = str(result)
      
    return equivalent, report
