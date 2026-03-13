from __future__ import annotations

from ..spec import SpecContext, SpecNode
from ..egglog import egglog_check_eq, egglog_simplify_ctx
from ..smt import z3_check

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
):
    _enqueue_equivalence(query1, query2, ctx=ctx)
    
    certificate = {}
    egglog_equivalence, certificate["egglog"] = egglog_check_eq(ctx, iterations=6)
    # ctx = egglog_simplify_ctx(ctx, certificate["egglog"]["egraph"])
    
    z3_equivalence, certificate["z3"] = z3_check(ctx, timeout_ms=10000)
    return certificate
