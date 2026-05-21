from __future__ import annotations

from .spec_ast import *
from ..egglog import *
from egglog import rewrite, vars_

import copy
import dreal
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
        # self.assumes.append(condition.constant_fold())
    
    def check(self, condition: BoolExpr) -> None:
        if not isinstance(condition, BoolExpr):
            raise TypeError(
                f"SpecContext.check expects BoolExpr, got {type(condition).__name__}"
            )
        self.checks.append(condition)
        # self.checks.append(condition.constant_fold())

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
    
    def _fold_spec(self, spec):
        if isinstance(spec, SpecNode):
            return spec.constant_fold()
        if isinstance(spec, tuple):
            return tuple(self._fold_spec(item) for item in spec)
        return spec

    def learned_literals(self) -> dict[RealVar | BoolVar, RealLit | BoolLit]:
        candidates: dict[RealVar | BoolVar, RealLit | BoolLit] = {}

        def record(
            var: RealVar | BoolVar,
            lit: RealLit | BoolLit,
        ) -> None:
            existing = candidates.get(var)
            if existing is None:
                candidates[var] = lit
                return
            if not identical_nodes(existing, lit):
                raise ValueError(
                    f"Conflicting learned literals for {var}: {existing} vs {lit}"
                )

        for assume in self.assumes:
            if isinstance(assume, Eq):
                rhs_folded = assume.rhs.constant_fold()
                lhs_folded = assume.lhs.constant_fold()
                if isinstance(lhs_folded, RealVar) and isinstance(rhs_folded, RealLit):
                    record(lhs_folded, rhs_folded)
                elif isinstance(rhs_folded, RealVar) and isinstance(lhs_folded, RealLit):
                    record(rhs_folded, lhs_folded)
            elif isinstance(assume, BoolEq):
                rhs_folded = assume.rhs.constant_fold()
                lhs_folded = assume.lhs.constant_fold()
                if isinstance(lhs_folded, BoolVar) and isinstance(rhs_folded, BoolLit):
                    record(lhs_folded, rhs_folded)
                elif isinstance(rhs_folded, BoolVar) and isinstance(lhs_folded, BoolLit):
                    record(rhs_folded, lhs_folded)

        return candidates

    def spec_of(self, node: Node):
        return node._evaluate_spec(ctx=self, cache=self.spec_cache)
        # spec = node._evaluate_spec(ctx=self, cache=self.spec_cache)
        # folded = self._fold_spec(spec)
        # self.spec_cache[node] = folded
        # return folded
    
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
