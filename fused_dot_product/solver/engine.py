from __future__ import annotations

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
):
    _enqueue_equivalence(query1, query2, ctx=ctx)
    
    egglog_equivalence, egglog_report = egglog_check_eq(ctx, iterations=egglog_iters)
    #print(ctx)
    #dreal_check_eq(ctx)
    if egglog_equivalence:
        return egglog_report
    else:
        ctx = egglog_simplify_ctx(ctx, egglog_report["egraph"])
        
        z3_equivalence, z3_report = z3_check_eq(ctx, timeout_ms=z3_timeout_ms)
        z3_report["previous"] = egglog_report
        return z3_report
