from __future__ import annotations

from itertools import count

from .spec_ast import BoolExpr, BoolLit, BoolVar, Eq, RealLit, RealVar
from ..egglog import *

class SpecContext:
    """Builder API for creating spec programs over the spec AST."""

    def __init__(self):
        self.assumes: list[BoolExpr] = []
        self.checks: list[BoolExpr] = []
        self._sym_counter = count()
    
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
    
    def real_val(self, value: int | float):
        return RealLit(value=value)
    
    def real(self, name: str) -> RealVar:
        return RealVar(name=name)
    
    def fresh_real(self, base: str) -> RealVar:
        return RealVar(name=f"{base}_{next(self._sym_counter)}")
    
    def bool(self, name: str) -> BoolVar:
        return BoolVar(name=name)
    
    def fresh_bool(self, base: str) -> BoolVar:
        return BoolVar(name=f"{base}_{next(self._sym_counter)}")
    
    def bool_val(self, value: bool):
        return BoolLit(value=value)
    
    def true(self) -> BoolLit:
        return BoolLit(value=True)
    
    def false(self) -> BoolLit:
        return BoolLit(value=False)
    
    def reset(self) -> None:
        self.assumes.clear()
        self.checks.clear()
        self._sym_counter = count()

__all__ = ["SpecContext"]
