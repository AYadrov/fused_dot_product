from __future__ import annotations

from .spec_ast import *
from ..egglog import *
from egglog import rewrite, vars_
from ..solver.report import build_proof_report

import copy
import dreal
from time import perf_counter
import z3
import warnings


class SpecContext:
    """Builder API for creating spec programs over the spec AST."""
    
    def __init__(self, name: str):
        self.assumes: list[BoolExpr] = []
        self.checks: list[BoolExpr] = []
        self._sym_counter = 0
        self.name = name
        self.spec_cache = {}
    
    def assume(self, condition: BoolExpr) -> None:
        if not isinstance(condition, BoolExpr):
            raise TypeError(
                f"SpecContext.assume expects BoolExpr, got {type(condition).__name__}"
            )
        self.assumes.append(condition)
    
    def check(self, condition: BoolExpr) -> None:
        if not isinstance(condition, BoolExpr):
            raise TypeError(
                f"SpecContext.check expects BoolExpr, got {type(condition).__name__}"
            )
        self.checks.append(condition)

    def _context_not_empty(self):
        if len(self.checks) == 0:
            raise RuntimeError("Context does not statements to check")
    
    def to_z3(self):
        self._context_not_empty()
        env = {}
        assume_terms = [assume.to_z3(env=env) for assume in self.assumes] + [z3.BoolVal(True)]  # make sure it is not empty
        check_terms = [check.to_z3(env=env) for check in self.checks]
        
        return z3.And(z3.And(*assume_terms), z3.Not(z3.And(*check_terms)))
    
    def to_dreal(self):
        self._context_not_empty()
        env: dict[tuple[str, str], dreal.Variable] = {}
        assume_terms = [assume.to_dreal(env) for assume in self.assumes] + [dreal.Formula.TRUE()]  # make sure it is not empty
        check_terms = [check.to_dreal(env) for check in self.checks]
        
        return dreal.And(dreal.And(*assume_terms), dreal.Not(dreal.And(*check_terms)))
    
    def to_egglog(self, egraph):
        self._context_not_empty()
        for assume in self.assumes:
            if isinstance(assume, Eq) or isinstance(assume, BoolEq):
                egraph.register(
                    union(assume.lhs.to_egglog()).with_(assume.rhs.to_egglog())
                )
            else:
                egraph.register(
                    union(assume.to_egglog()).with_(MathBool.True_())
                )
        
        to_check = []
        for check in self.checks:
            if isinstance(check, Eq) or isinstance(check, BoolEq):
                lhs = check.lhs.to_egglog()
                rhs = check.rhs.to_egglog()
                egraph.register(lhs)
                egraph.register(rhs)
                to_check.append(eq(lhs).to(rhs))
            elif isinstance(check, BoolExpr):
                expr = check.to_egglog()
                egraph.register(expr)
                to_check.append(eq(expr).to(MathBool.True_()))
            else:
                raise NotImplementedError(
                    f"Only BoolExpr checks are supported, got {type(check).__name__}"
                )
        return to_check

    # Try to learn literal facts from assumes only. Conflicting facts are errors.
    def learned_literals(self) -> dict[SpecNode, RealLit | BoolLit]:
        candidates: dict[SpecNode, RealLit | BoolLit] = {}
        
        def record(
            expr: SpecNode,
            lit: RealLit | BoolLit,
        ) -> None:
            existing = candidates.get(expr)
            if existing is None:
                candidates[expr] = lit
            elif not identical_nodes(existing, lit):
                raise ValueError(
                    f"Conflicting learned literals for {expr}: {existing} vs {lit}"
                )

        for assume in self.assumes:
            learned = self._canonical_learned_assumption(assume)
            if learned is None:
                continue
            record(*learned)
        
        return candidates
    
    # LOCAL LEARNING FACTS FROM AN ASSUME
    def _canonical_learned_assumption(
        self,
        assume: BoolExpr,
    ) -> tuple[SpecNode, RealLit | BoolLit] | None:
        folded_assume = assume.constant_fold()
        if not identical_nodes(folded_assume, assume):
            if not isinstance(folded_assume, BoolExpr):
                raise TypeError(
                    "BoolExpr.constant_fold() must return BoolExpr, "
                    f"got {type(folded_assume).__name__}"
                )
            return self._canonical_learned_assumption(folded_assume)

        if isinstance(assume, Eq):
            rhs_folded = assume.rhs.constant_fold()
            lhs_folded = assume.lhs.constant_fold()
            if (
                isinstance(lhs_folded, RealExpr)
                and not isinstance(lhs_folded, RealLit)
                and isinstance(rhs_folded, RealLit)
            ):
                return lhs_folded, rhs_folded
            if (
                isinstance(rhs_folded, RealExpr)
                and not isinstance(rhs_folded, RealLit)
                and isinstance(lhs_folded, RealLit)
            ):
                return rhs_folded, lhs_folded

        elif isinstance(assume, BoolEq):
            rhs_folded = assume.rhs.constant_fold()
            lhs_folded = assume.lhs.constant_fold()
            if (
                isinstance(lhs_folded, BoolExpr)
                and not isinstance(lhs_folded, BoolLit)
                and isinstance(rhs_folded, BoolLit)
            ):
                return lhs_folded, rhs_folded
            if (
                isinstance(rhs_folded, BoolExpr)
                and not isinstance(rhs_folded, BoolLit)
                and isinstance(lhs_folded, BoolLit)
            ):
                return rhs_folded, lhs_folded
        return None
    
    def _normalize_assume(
        self,
        assume: BoolExpr,
        replacements: dict[SpecNode, RealLit | BoolLit],
    ) -> BoolExpr:
        learned = self._canonical_learned_assumption(assume)
        if learned is None:
            return assume
        expr, lit = learned
        if not isinstance(expr, (RealVar, BoolVar)):
            local_replacements = dict(replacements)
            local_replacements.pop(expr, None)
            expr = substitute_literals(expr, local_replacements)
        if isinstance(expr, RealExpr):
            return Eq(expr, lit).constant_fold()
        return BoolEq(expr, lit).constant_fold()

    def _simplify_assume(
        self,
        assume: BoolExpr,
        replacements: dict[SpecNode, RealLit | BoolLit],
    ) -> BoolExpr:
        if self._canonical_learned_assumption(assume) is not None:
            return self._normalize_assume(assume, replacements)
        return substitute_literals(assume, replacements)
    
    # LEARNS FROM ASSUMES - APPLIES EVERYWHERE
    def simplify(self) -> "SpecContext":
        simplified = self.copy()
        max_iterations = len(simplified.assumes) + len(simplified.checks) + 1
        for _ in range(max_iterations):
            replacements = simplified.learned_literals()
            new_assumes = [
                simplified._simplify_assume(assume, replacements)
                for assume in simplified.assumes
            ]
            new_checks = [
                substitute_literals(check, replacements)
                for check in simplified.checks
            ]
            if new_assumes == simplified.assumes and new_checks == simplified.checks:
                break
            simplified.assumes = new_assumes
            simplified.checks = new_checks
        return simplified
    
    def spec_of(self, node: Node):
        return node._evaluate_spec(ctx=self, cache=self.spec_cache)
    
    def real_val(self, value: int | float):
        return RealLit(value=value)
    
    def real(self, name: str) -> RealVar:
        return RealVar(name=name)
    
    def fresh_real(self, base: str) -> RealVar:
        name = RealVar(name=f"{base}_{self._sym_counter}")
        self._sym_counter += 1
        return name
    
    def bool(self, name: str) -> BoolVar:
        return BoolVar(name=name)
    
    def fresh_bool(self, base: str) -> BoolVar:
        name = BoolVar(name=f"{base}_{self._sym_counter}")
        self._sym_counter += 1
        return name

    def fresh_float(self, base: str):
        from .spec_values import fresh_float
        return fresh_float(base, self)

    def encode_fp32(self, **kwargs):
        from .spec_values import encode_fp32
        return encode_fp32(self, **kwargs)

    def bool_val(self, value: bool):
        return BoolLit(value=value)
    
    def true(self) -> BoolLit:
        return BoolLit(value=True)
    
    def false(self) -> BoolLit:
        return BoolLit(value=False)
    
    def reset(self) -> None:
        self.assumes.clear()
        self.checks.clear()
        self._sym_counter = 0
        self.spec_cache.clear()

    def snapshot(self):
        return {
            "name": self.name,
            "assume_count": len(self.assumes),
            "check_count": len(self.checks),
            "assumes": [str(assume) for assume in self.assumes],
            "checks": [str(check) for check in self.checks],
            "context": str(self),
        }

    def __str__(self) -> str:
        def format_section(title: str, items: list[BoolExpr]) -> list[str]:
            if not items:
                return [f"{title}:", "  <none>"]
            return [f"{title}:"] + [f"  {item}" for item in items]

        lines = [f"SpecContext({self.name})"]
        lines.extend(format_section("Assumes", self.assumes))
        lines.extend(format_section("Checks", self.checks))
        return "\n".join(lines)
    
    def copy(self, assumes=None, checks=None):
        if assumes is None:
            assumes = copy.deepcopy(self.assumes)
        if checks is None:
            checks = copy.deepcopy(self.checks)

        new_ctx = SpecContext(self.name)
        new_ctx.assumes = assumes
        new_ctx.checks = checks
        new_ctx._sym_counter = self._sym_counter
        new_ctx.spec_cache = dict(self.spec_cache)
        return new_ctx

def simplify_ctx(ctx: SpecContext):
    run_started_at = perf_counter()
    
    simplified_ctx = ctx.simplify()
    
    new_assumes = []
    for assume in simplified_ctx.assumes:
        if identical_nodes(assume, BoolLit(True)):
            continue
        if identical_nodes(assume, BoolLit(False)):
            raise ValueError("assumption folds to False")
        new_assumes.append(assume)
    
    new_checks = []
    for check in simplified_ctx.checks:
        if identical_nodes(check, BoolLit(True)):
            continue
        if identical_nodes(check, BoolLit(False)):
            raise ValueError("check folds to False")
        new_checks.append(check)
    
    trimmed_ctx = ctx.copy(assumes=new_assumes, checks=new_checks)
    return build_proof_report(
        ctx,
        trimmed_ctx,
        tool="simplify",
        runtime_s=perf_counter() - run_started_at,
        equivalent=len(new_checks) == 0,
    )
