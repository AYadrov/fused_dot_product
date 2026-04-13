from __future__ import annotations

from typing import Any

from ..spec import SpecContext, SpecNode
from ..egglog import egglog_check_eq, egglog_simplify_ctx
from ..smt import z3_check_eq, dreal_check_eq


# Unrolls tuples
def _enqueue_equivalence(
    lhs: SpecNode | tuple,
    rhs: SpecNode | tuple,
    ctx: SpecContext
):
    lhs_is_tuple = isinstance(lhs, tuple)
    rhs_is_tuple = isinstance(rhs, tuple)
    if lhs_is_tuple or rhs_is_tuple:
        if not (lhs_is_tuple and rhs_is_tuple):
            raise TypeError(
                "Spec shape mismatch: one side is a tuple and the other is not"
            )
        if len(lhs) != len(rhs):
            raise TypeError(
                f"Spec tuple arity mismatch: {len(lhs)} != {len(rhs)}"
            )
        for lhs_item, rhs_item in zip(lhs, rhs):
            _enqueue_equivalence(lhs_item, rhs_item, ctx=ctx)
        return
    ctx.check(lhs.eq(rhs))


def check_equivalence(
    query1: SpecNode | tuple,
    query2: SpecNode | tuple,
    ctx: SpecContext,
    egglog_iters: int = 6,
    z3_timeout_ms: int = 10000,
    dreal_precision: float = 0.001,
):
    _enqueue_equivalence(query1, query2, ctx=ctx)
 
    original_ctx = ctx.copy()
    proof_trace: list[dict[str, Any]] = []

    # warm up context
    egglog_equivalence, egglog_report = egglog_check_eq(original_ctx, iterations=2, simplify=True)
    proof_trace.append(egglog_report)
    if egglog_equivalence:
        return True, proof_trace

    
    simplified_equivalence, simplified_ctx, simplified_report = egglog_simplify_ctx(original_ctx, egglog_report["egraph"])
    proof_trace.append(simplified_report)
    if simplified_equivalence:
        return True, proof_trace  # never should be the case

    print(simplified_ctx)


    egglog_equivalence, egglog_report = egglog_check_eq(simplified_ctx, iterations=egglog_iters)
    proof_trace.append(egglog_report)
    if egglog_equivalence:
        return True, proof_trace

    
    z3_equivalence, z3_report = z3_check_eq(simplified_ctx, timeout_ms=z3_timeout_ms)
    proof_trace.append(z3_report)
    if z3_equivalence:
        return True, proof_trace

    dreal_equivalence, dreal_report = dreal_check_eq(simplified_ctx, precision=dreal_precision)
    proof_trace.append(dreal_report)

    return dreal_equivalence, proof_trace
