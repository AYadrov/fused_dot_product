from __future__ import annotations

from typing import Any

from ..spec import SpecContext, SpecNode
from ..egglog import egglog_rewrite, egglog_preprocess
from ..smt import z3_check_eq, dreal_check_eq


DEFAULT_REWRITE_ITERS = 6
DEFAULT_PREPROCESS_ITERS = 3
DEFAULT_Z3_TIMEOUT = 10000
DEFAULT_DREAL_PRECISION = 0.001


TOOL_ALIASES = {
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
    schedule: list[str | dict[str, Any]] | None,
) -> list[dict[str, Any]]:
    if schedule is None:
        return [
            {"tool": "egglog-preprocess", "iters": DEFAULT_PREPROCESS_ITERS},
            {"tool": "egglog-rewrite", "iters": DEFAULT_REWRITE_ITERS},
            {"tool": "z3", "timeout_ms": DEFAULT_Z3_TIMEOUT},
            {"tool": "dreal", "precision": DEFAULT_DREAL_PRECISION},
        ]

    normalized = []
    for step in schedule:
        if not isinstance(step, dict):
            raise TypeError("Each schedule step must be a dict or a string alias")

        if "tool" not in step:
            raise ValueError("Each schedule step must define a 'tool'")

        tool = step["tool"]
        if not isinstance(tool, str):
            raise TypeError("Schedule step 'tool' must be a string")

        if TOOL_ALIASES.get(tool) is None:
            raise ValueError(
                f"Unknown schedule tool {step['tool']}. Supported aliases: {list(TOOL_ALIASES)}"
            )

        if tool == "egglog-preprocess":
            normalized.append(
                {"tool": canonical_tool, "iters": int(step.get("iters", DEFAULT_PREPROCESS_ITERS))}
            )
        elif tool == "egglog-rewrite":
            normalized.append(
                {"tool": canonical_tool, "iters": int(step.get("iters", DEFAULT_REWRITE_ITERS))}
            )
        elif tool == "z3":
            normalized.append(
                {"tool": canonical_tool, "timeout_ms": int(step.get("timeout_ms", DEFAULT_Z3_TIMEOUT))}
            )
        elif tool == "dreal":
            normalized.append(
                {"tool": canonical_tool, "precision": float(step.get("precision", DEFAULT_DREAL_PRECISION))}
            )

    return normalized


def _run_tool(ctx: SpecContext, step: dict[str, Any]):
    tool = step["tool"]
    tool_fn = TOOL_ALIASES[tool]
    kwargs = {key: value for key, value in step.items() if key != "tool"}
    return tool_fn(ctx, **kwargs)


def check_equivalence(
    query1: SpecNode | tuple,
    query2: SpecNode | tuple,
    ctx: SpecContext,
    schedule: list[str | dict[str, Any]] | None = None,
):
    _enqueue_equivalence(query1, query2, ctx=ctx)

    current_ctx = ctx.copy()
    proof_trace: list[dict[str, Any]] = []

    for step in _normalize_schedule(schedule=schedule):
        equivalent, new_ctx, report = _run_tool(current_ctx, step)
        proof_trace.append(report)
        if equivalent:
            return True, proof_trace
        current_ctx = new_ctx

    return False, proof_trace
