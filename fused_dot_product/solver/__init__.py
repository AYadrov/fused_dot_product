from __future__ import annotations

from typing import Any

from .report import ProofReport, build_proof_report, merge_rule_application_counts

__all__ = [
    "ProofReport",
    "build_proof_report",
    "check_equivalence",
    "merge_rule_application_counts",
]


def check_equivalence(*args: Any, **kwargs: Any):
    from .engine import check_equivalence as _check_equivalence
    return _check_equivalence(*args, **kwargs)
