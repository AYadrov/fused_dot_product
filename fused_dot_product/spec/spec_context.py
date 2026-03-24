from __future__ import annotations

from .spec_ast import *
from ..egglog import *
from egglog import rewrite, vars_

import copy
import z3


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
    
    def to_z3(self):
        def assert_not_empty(terms):
            return terms + [z3.BoolVal(True)]
        assume_terms = assert_not_empty([assume.to_z3() for assume in self.assumes])
        check_terms = assert_not_empty([check.to_z3() for check in self.checks])
        
        return z3.And(z3.And(*assume_terms), z3.Not(z3.And(*check_terms)))
    
    def to_egglog(self, egraph):
        for assume in self.assumes:
            if isinstance(assume, Eq):
                egraph.register(
                    union(assume.lhs.to_egglog()).with_(assume.rhs.to_egglog())
                )
            else:
                raise NotImplementedError(
                    f"Only Eq assumptions are supported, got {type(assume).__name__}"
                )
        
        to_check = []
        for check in self.checks:
            if not isinstance(check, Eq):
                raise NotImplementedError(
                    f"Only Eq checks are supported, got {type(check).__name__}"
                )
            lhs = check.lhs.to_egglog()
            rhs = check.rhs.to_egglog()
            egraph.register(lhs)
            egraph.register(rhs)
            to_check.append(eq(lhs).to(rhs))
        return to_check
    
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


