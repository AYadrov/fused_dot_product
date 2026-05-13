from __future__ import annotations

from time import perf_counter

import dreal

from ..solver.report import build_proof_report


def dreal_check_eq(ctx: "SpecContext", precision: float):
    program = ctx.to_dreal()

    run_started_at = perf_counter()
    result = dreal.CheckSatisfiability(program, precision)
    runtime_s = perf_counter() - run_started_at
    
    equivalent = result is None
    status = "unsat" if equivalent else "delta-sat"
    new_ctx = ctx.copy()
    report = build_proof_report(
        ctx,
        new_ctx,
        tool="dreal",
        runtime_s=runtime_s,
        equivalent=equivalent,
        status=status,
        precision=precision,
    )
    
    if result is not None:
        report["supplementary_info"] = str(result)
      
    return report
