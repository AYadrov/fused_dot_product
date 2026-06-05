from __future__ import annotations

from dataclasses import dataclass
from fractions import Fraction
import math
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
    "RivalAnalysis",
    "RivalMachine",
    "build_machine",
    "collect_free_vars",
    "to_rival_ir",
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
    translated_exprs = [_append_assert(to_rival_ir(expr)) for expr in expr_list]
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
