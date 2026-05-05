from __future__ import annotations

from typing import Any

from ..spec import SpecContext, SpecNode
from ..egglog import egglog_rewrite, egglog_preprocess
from ..smt import z3_check_eq, dreal_check_eq


DEFAULT_REWRITE_ITERS = 6
DEFAULT_PREPROCESS_ITERS = 3
DEFAULT_Z3_TIMEOUT = 10000
DEFAULT_DREAL_PRECISION = 0.001


TOOL_FNS = {
    "egglog-preprocess": egglog_preprocess,
    "egglog-rewrite": egglog_rewrite,
    "z3": z3_check_eq,
    "dreal": dreal_check_eq,
}


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


def _normalize_schedule(
    schedule: list[str | dict[str, Any]],
) -> list[dict[str, Any]]:
    normalized = []
    for step in schedule:
        if not isinstance(step, dict):
            raise TypeError("Each schedule step must be a dict")

        if "tool" not in step:
            raise ValueError("Each schedule step must define a 'tool'")

        tool = step["tool"]
        if not isinstance(tool, str):
            raise TypeError("Schedule step 'tool' must be a string")

        if TOOL_FNS.get(tool) is None:
            raise ValueError(
                f"Unknown schedule tool {step['tool']}. Supported aliases: {list(TOOL_FNS.keys())}"
            )

        if tool == "egglog-preprocess":
            normalized.append(
                {"tool": tool, "iterations": int(step.get("iterations", DEFAULT_PREPROCESS_ITERS))}
            )
        elif tool == "egglog-rewrite":
            normalized.append(
                {"tool": tool, "iterations": int(step.get("iterations", DEFAULT_REWRITE_ITERS))}
            )
        elif tool == "z3":
            normalized.append(
                {"tool": tool, "timeout_ms": int(step.get("timeout_ms", DEFAULT_Z3_TIMEOUT))}
            )
        elif tool == "dreal":
            normalized.append(
                {"tool": tool, "precision": float(step.get("precision", DEFAULT_DREAL_PRECISION))}
            )

    return normalized


def _run_tool(ctx: SpecContext, step: dict[str, Any]):
    tool = step["tool"]
    tool_fn = TOOL_FNS[tool]
    kwargs = {key: value for key, value in step.items() if key != "tool"}
    return tool_fn(ctx, **kwargs)


def check_equivalence(
    query1: SpecNode | tuple,
    query2: SpecNode | tuple,
    ctx: SpecContext,
    schedule: list[str | dict[str, Any]] | None = None,
):
    _enqueue_equivalence(query1, query2, ctx=ctx)

    ctx_trace: list[SpecContext] = [ctx.copy()]
    proof_trace: list[dict[str, Any]] = []

    for step in _normalize_schedule(schedule=schedule):
        equivalent, new_ctx, report = _run_tool(ctx_trace[-1], step)
        proof_trace.append(report)
        ctx_trace.append(new_ctx)
        if equivalent:
            return True, proof_trace

    return False, proof_trace
