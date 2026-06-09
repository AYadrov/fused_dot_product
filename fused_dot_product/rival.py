from __future__ import annotations

from collections import deque
from dataclasses import dataclass
from fractions import Fraction
from itertools import product
import math
from time import perf_counter
import sys
from typing import Any, Iterable, Sequence

from .spec.spec_ast import (
    Abs,
    Add,
    And,
    BoolEq,
    BoolExpr,
    BoolLit,
    BoolVar,
    Eq,
    Ge,
    Gt,
    If,
    Le,
    Lt,
    Max,
    Min,
    Mul,
    Neg,
    Not,
    NotEq,
    Or,
    Pow,
    RealLit,
    RealVar,
    SpecNode,
    Sub,
    children,
)

RivalIR = dict[str, Any]

__all__ = [
    "rival_feasibility_check",
]


@dataclass(frozen=True)
class RivalAnalysis:
    status: tuple[bool, bool]
    hints: Any
    converged: bool

    @property
    def is_error(self) -> bool:
        return self.status[0]

    @property
    def maybe_error(self) -> bool:
        return self.status[1]


class RivalMachine:
    def __init__(self, raw_machine: Any):
        self._raw_machine = raw_machine

    def apply_with_hints(
        self,
        rect: Sequence[tuple[float, float]],
        hints: Any | None = None,
    ) -> RivalAnalysis:
        status, next_hints, converged = self._raw_machine.apply_with_hints(rect, hints)
        return RivalAnalysis(
            status=(bool(status[0]), bool(status[1])),
            hints=next_hints,
            converged=bool(converged),
        )


def build_machine(
    exprs: Sequence[SpecNode],
    free_vars: Sequence[str],
) -> RivalMachine:
    expr_list = list(exprs)
    var_list = _validate_free_vars(free_vars)
    _validate_referenced_vars(expr_list, var_list)
    native = _load_native_module()
    translated_exprs = [
        _append_assert(_and_exprs(to_rival_ir(expr) for expr in expr_list))
    ]
    raw_machine = native.build_machine(translated_exprs, var_list)
    return RivalMachine(raw_machine)


def collect_free_vars(exprs: Iterable[SpecNode]) -> list[str]:
    found: set[str] = set()

    def visit(node: SpecNode) -> None:
        if isinstance(node, (RealVar, BoolVar)):
            found.add(node.name)
        for child in children(node):
            visit(child)

    for expr in exprs:
        if not isinstance(expr, SpecNode):
            raise TypeError(f"Expected SpecNode, got {type(expr).__name__}")
        visit(expr)
    return sorted(found)


def get_rival_rects(
    assumes: Sequence[BoolExpr],
    free_vars: Sequence[str],
) -> list[list[tuple[float, float]]]:
    var_indexes = {name: index for index, name in enumerate(free_vars)}
    rects = [_rival_unbounded_rect(len(free_vars))]
    for assume in assumes:
        alternatives = _rival_rect_alternatives(
            assume,
            var_indexes,
            len(free_vars),
        )
        if alternatives is None:
            continue
        rects = _intersect_rival_rect_sets(rects, alternatives)
        if not rects:
            break
    return rects


def rival_feasibility_check(
    ctx: "SpecContext",
    max_depth: int = 1,
):
    from .solver.report import build_proof_report

    max_depth = int(max_depth)
    run_started_at = perf_counter()
    exprs = ctx.assumes + ctx.checks
    free_vars = collect_free_vars(exprs)
    machine = build_machine(exprs, free_vars)

    work_queue = deque(
        (rect, None, 0)
        for rect in get_rival_rects(ctx.assumes, free_vars)
    )

    sat_flag = True

    while work_queue:
        rect, hints, depth = work_queue.popleft()
        analysis = machine.apply_with_hints(rect, hints)
        status = analysis.status

        if status == (True, True):
            sat_flag = sat_flag and True
            continue

        if status == (False, False):
            return build_proof_report(
                ctx,
                ctx.copy(),
                tool="rival_check_solution_exists",
                runtime_s=perf_counter() - run_started_at,
                status="unsat",
                max_depth=max_depth,
                supplementary_info=rect,
            )

        if status == (False, True) and depth < max_depth:
            children = _subdivide_rival_rect(rect)
            if children:
                for child in children:
                    work_queue.append((child, analysis.hints, depth + 1))
        sat_flag = False

    return build_proof_report(
        ctx,
        ctx.copy(),
        tool="rival_check_solution_exists",
        runtime_s=perf_counter() - run_started_at,
        status="sat" if sat_flag else "unknown",
        max_depth=max_depth,
    )

def _subdivide_rival_rect(
    rect: Sequence[tuple[float, float]],
) -> list[list[tuple[float, float]]]:
    dimension_options: list[list[tuple[float, float]]] = []
    split_any_dimension = False
    for interval in rect:
        split = _split_rival_interval(interval)
        if split is None:
            dimension_options.append([interval])
        else:
            split_any_dimension = True
            dimension_options.append(split)

    if not split_any_dimension:
        return []

    return [list(child) for child in product(*dimension_options)]


def _split_rival_interval(
    interval: tuple[float, float],
) -> list[tuple[float, float]] | None:
    lower, upper = interval
    if lower > upper:
        return None

    effective_lower = -sys.float_info.max if lower == -math.inf else lower
    effective_upper = sys.float_info.max if upper == math.inf else upper
    midpoint = (effective_lower / 2.0) + (effective_upper / 2.0)
    right_lower = math.nextafter(midpoint, math.inf)

    left = (lower, midpoint)
    right = (right_lower, upper)
    if (
        lower <= midpoint
        and right_lower <= upper
        and left != interval
        and right != interval
    ):
        return [left, right]
    return None


def _rival_unbounded_rect(dimensions: int) -> list[tuple[float, float]]:
    return [(-math.inf, math.inf) for _ in range(dimensions)]


def _rival_rect_alternatives(
    expr: BoolExpr,
    var_indexes: dict[str, int],
    dimensions: int,
) -> list[list[tuple[float, float]]] | None:
    if isinstance(expr, And):
        lhs = _rival_rect_alternatives(expr.lhs, var_indexes, dimensions)
        rhs = _rival_rect_alternatives(expr.rhs, var_indexes, dimensions)
        if lhs == [] or rhs == []:
            return []
        if lhs is None:
            return rhs
        if rhs is None:
            return lhs
        return _intersect_rival_rect_sets(lhs, rhs)

    if isinstance(expr, Or):
        lhs = _rival_rect_alternatives(expr.lhs, var_indexes, dimensions)
        rhs = _rival_rect_alternatives(expr.rhs, var_indexes, dimensions)
        if lhs is None or rhs is None:
            return None
        return lhs + rhs

    return _rival_comparison_rect(expr, var_indexes, dimensions)


def _rival_comparison_rect(
    expr: BoolExpr,
    var_indexes: dict[str, int],
    dimensions: int,
) -> list[list[tuple[float, float]]] | None:
    if not isinstance(expr, (Eq, Lt, Le, Gt, Ge)):
        return None

    var: RealVar
    literal: RealLit
    var_on_lhs: bool
    if isinstance(expr.lhs, RealVar) and isinstance(expr.rhs, RealLit):
        var = expr.lhs
        literal = expr.rhs
        var_on_lhs = True
    elif isinstance(expr.lhs, RealLit) and isinstance(expr.rhs, RealVar):
        var = expr.rhs
        literal = expr.lhs
        var_on_lhs = False
    else:
        return None

    value = _rival_literal_value(literal)
    if value is None:
        return None

    var_index = var_indexes.get(var.name)
    if var_index is None:
        return [_rival_unbounded_rect(dimensions)]

    lower = -math.inf
    upper = math.inf
    if isinstance(expr, Eq):
        lower = value
        upper = value
    elif isinstance(expr, Gt):
        if var_on_lhs:
            lower = math.nextafter(value, math.inf)
        else:
            upper = math.nextafter(value, -math.inf)
    elif isinstance(expr, Ge):
        if var_on_lhs:
            lower = value
        else:
            upper = value
    elif isinstance(expr, Lt):
        if var_on_lhs:
            upper = math.nextafter(value, -math.inf)
        else:
            lower = math.nextafter(value, math.inf)
    elif isinstance(expr, Le):
        if var_on_lhs:
            upper = value
        else:
            lower = value

    rect = _rival_unbounded_rect(dimensions)
    rect[var_index] = (lower, upper)
    return [] if lower > upper else [rect]


def _rival_literal_value(literal: RealLit) -> float | None:
    try:
        value = float(literal.value)
    except (OverflowError, TypeError, ValueError):
        return None
    if not math.isfinite(value):
        return None
    return value


def _intersect_rival_rect_sets(
    lhs_rects: list[list[tuple[float, float]]],
    rhs_rects: list[list[tuple[float, float]]],
) -> list[list[tuple[float, float]]]:
    intersections: list[list[tuple[float, float]]] = []
    for lhs in lhs_rects:
        for rhs in rhs_rects:
            intersection = _intersect_rival_rects(lhs, rhs)
            if intersection is not None:
                intersections.append(intersection)
    return intersections


def _intersect_rival_rects(
    lhs: list[tuple[float, float]],
    rhs: list[tuple[float, float]],
) -> list[tuple[float, float]] | None:
    rect: list[tuple[float, float]] = []
    for (lhs_lower, lhs_upper), (rhs_lower, rhs_upper) in zip(lhs, rhs):
        lower = max(lhs_lower, rhs_lower)
        upper = min(lhs_upper, rhs_upper)
        if lower > upper:
            return None
        rect.append((lower, upper))
    return rect


def to_rival_ir(node: SpecNode) -> RivalIR:
    if isinstance(node, (RealVar, BoolVar)):
        return {"op": "var", "name": node.name}
    if isinstance(node, RealLit):
        ratio = _real_literal_ratio(node.value)
        return {
            "op": "real_lit",
            "num": str(ratio.numerator),
            "den": str(ratio.denominator),
        }
    if isinstance(node, BoolLit):
        return {"op": "bool_lit", "value": bool(node.value)}

    if isinstance(node, Add):
        return _binary("add", node.lhs, node.rhs)
    if isinstance(node, Sub):
        return _binary("sub", node.lhs, node.rhs)
    if isinstance(node, Mul):
        return _binary("mul", node.lhs, node.rhs)
    if isinstance(node, Neg):
        return _unary("neg", node.value)
    if isinstance(node, Abs):
        return _unary("abs", node.value)
    if isinstance(node, Pow):
        return _binary("pow", node.base, node.exponent)
    if isinstance(node, Max):
        return _binary("max", node.lhs, node.rhs)
    if isinstance(node, Min):
        return _binary("min", node.lhs, node.rhs)
    if isinstance(node, If):
        return {
            "op": "if",
            "cond": to_rival_ir(node.cond),
            "on_true": to_rival_ir(node.on_true),
            "on_false": to_rival_ir(node.on_false),
        }

    if isinstance(node, Eq):
        return _binary("eq", node.lhs, node.rhs)
    if isinstance(node, NotEq):
        return _binary("ne", node.lhs, node.rhs)
    if isinstance(node, Lt):
        return _binary("lt", node.lhs, node.rhs)
    if isinstance(node, Le):
        return _binary("le", node.lhs, node.rhs)
    if isinstance(node, Gt):
        return _binary("gt", node.lhs, node.rhs)
    if isinstance(node, Ge):
        return _binary("ge", node.lhs, node.rhs)
    if isinstance(node, BoolEq):
        return _binary("bool_eq", node.lhs, node.rhs)
    if isinstance(node, Not):
        return _unary("not", node.value)
    if isinstance(node, Or):
        return _binary("or", node.lhs, node.rhs)
    if isinstance(node, And):
        return _binary("and", node.lhs, node.rhs)

    raise TypeError(f"Unsupported SpecNode for Rival translation: {type(node).__name__}")


def _binary(op: str, lhs: SpecNode, rhs: SpecNode) -> RivalIR:
    return {"op": op, "lhs": to_rival_ir(lhs), "rhs": to_rival_ir(rhs)}


def _unary(op: str, arg: SpecNode) -> RivalIR:
    return {"op": op, "arg": to_rival_ir(arg)}


def _and_exprs(exprs: Iterable[RivalIR]) -> RivalIR:
    expr_iter = iter(exprs)
    result = next(expr_iter)
    for expr in expr_iter:
        result = {"op": "and", "lhs": result, "rhs": expr}
    return result


def _append_assert(expr: RivalIR) -> RivalIR:
    return {"op": "assert", "arg": expr}


def _real_literal_ratio(value: int | float) -> Fraction:
    if isinstance(value, float) and not math.isfinite(value):
        raise ValueError("Rival translation does not support non-finite RealLit values")
    return Fraction(value)


def _validate_free_vars(free_vars: Sequence[str]) -> list[str]:
    result = list(free_vars)
    if any(not isinstance(var, str) for var in result):
        raise TypeError("free_vars must contain only strings")
    if len(set(result)) != len(result):
        raise ValueError("free_vars must be unique")
    return result


def _validate_referenced_vars(exprs: Sequence[SpecNode], free_vars: Sequence[str]) -> None:
    if not exprs:
        raise ValueError("exprs must be non-empty")
    missing = sorted(set(collect_free_vars(exprs)) - set(free_vars))
    if missing:
        raise ValueError(f"free_vars is missing referenced variables: {missing}")


def _load_native_module():
    try:
        from . import _rival3
    except ImportError:
        try:
            import _rival3  # type: ignore[no-redef]
        except ImportError as exc:
            raise RuntimeError(
                "Rival3 native bridge is not built. Build it with "
                "`maturin develop -m crates/rival_bridge/Cargo.toml` or an equivalent "
                "PyO3 build command."
            ) from exc
    return _rival3
