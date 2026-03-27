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
        assume_terms = [assume.to_z3() for assume in self.assumes] + [z3.BoolVal(True)]  # make sure it is not empty
        check_terms = [check.to_z3() for check in self.checks]
        
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
                warnings.warn(f"Skipped assume for egglog: {str(assume)}")
        
        to_check = []
        for check in self.checks:
            if not isinstance(check, Eq) and not isinstance(check, BoolEq):
                raise NotImplementedError(
                    f"Only Eq and BoolEq checks are supported, got {type(check).__name__}"
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

    # TODO: stuff like this: assume(x == y * y); check(x == abs(x)) won't work
    # TODO: assume(x == 0); assume(x == 1); check(0 == 1) - should not pass
    # TODO: assume(x == 1);  assume(y == 0); assume(y == 1); check(x == 2) - should not pass
    # TODO: assume(x == z*y); assume(y==0); check(x == 0) - should pass
    # def simplify_assumes(self):
    #     live_vars = set()
    #     for check in self.checks:
    #         live_vars.update(variables(check))

    #     if not live_vars:  # checks do not have vars, assumptions are useless
    #         self.assumes = []
    #         return self

    #     assume_vars = [variables(assume) for assume in self.assumes]
    #     var_occurrences = {}
    #     for vars_ in assume_vars:
    #         for var in vars_:
    #             var_occurrences[var] = var_occurrences.get(var, 0) + 1

    #     kept_indices = set()
    #     changed = True
    #     while changed:
    #         changed = False
    #         for idx, (assume, vars_) in enumerate(zip(self.assumes, assume_vars)):
    #             if idx in kept_indices:
    #                 continue
    #             if not vars_:  # assumption does not have vars
    #                 kept_indices.add(idx)
    #                 changed = True
    #                 continue
    #             if not (vars_ & live_vars):  # assumption and checks do not have common vars - drop statement
    #                 continue
    #             if all(var in live_vars or var_occurrences[var] > 1 for var in vars_):  # all of assume's vars are either in live_vars or they are at least somewhere else as well
    #                 kept_indices.add(idx)
    #                 live_vars.update(vars_)
    #                 changed = True

    #     new_assumes = [assume for idx, assume in enumerate(self.assumes) if idx in kept_indices]
    #     self.assumes = new_assumes
    #     return self

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
