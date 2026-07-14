from __future__ import annotations

from collections import Counter
from typing import Any, Final, Literal, cast


ProofStatus = Literal["sat", "unsat", "unknown"]
VALID_PROOF_STATUSES: Final = frozenset({"sat", "unsat", "unknown"})


class ProofReport(dict[str, Any]):
    pass


def validate_proof_status(status: object) -> ProofStatus:
    if not isinstance(status, str) or status not in VALID_PROOF_STATUSES:
        raise ValueError(
            f"Proof report status must be one of {sorted(VALID_PROOF_STATUSES)}, "
            f"got {status!r}"
        )
    return cast(ProofStatus, status)


def _count_unchanged_items(before: list[str], after: list[str]) -> int:
    return sum((Counter(before) & Counter(after)).values())


def merge_rule_application_counts(*counts_dicts: dict[str, int]) -> dict[str, int]:
    merged: dict[str, int] = {}
    for counts in counts_dicts:
        for rule, count in counts.items():
            merged[rule] = merged.get(rule, 0) + int(count)
    return merged


def build_proof_report(
    old_ctx: "SpecContext",
    new_ctx: "SpecContext",
    tool: str,
    runtime_s: float,
    status: str,
    **extra: Any,
) -> ProofReport:
    assert old_ctx.name == new_ctx.name, "Trying to build proof report between two different designs"
    status = validate_proof_status(status)
    name = old_ctx.name

    assumes_before = len(old_ctx.assumes)
    assumes_after = len(new_ctx.assumes)
    checks_before = len(old_ctx.checks)
    checks_after = len(new_ctx.checks)

    added_assumes = max(0, assumes_after - assumes_before)
    added_checks = max(0, checks_after - checks_before)

    old_assumes = [str(assume) for assume in old_ctx.assumes]
    new_assumes = [str(assume) for assume in new_ctx.assumes]
    old_checks = [str(check) for check in old_ctx.checks]
    new_checks = [str(check) for check in new_ctx.checks]

    unchanged_assumes = _count_unchanged_items(old_assumes, new_assumes)
    unchanged_checks = _count_unchanged_items(old_checks, new_checks)

    discharged_checks = max(0, checks_before - checks_after)
    discharged_assumes = max(0, assumes_before - assumes_after)

    simplified_assumes = max(0, assumes_after - unchanged_assumes) - added_assumes
    simplified_checks = max(0, checks_after - unchanged_checks) - added_checks

    report = ProofReport(
        tool=tool,
        name=old_ctx.name if name is None else name,
        old_ctx=old_ctx,
        new_ctx=new_ctx,
        status=status,
        runtime_s=float(runtime_s),
        assumes_before=assumes_before,
        assumes_after=assumes_after,
        checks_before=checks_before,
        checks_after=checks_after,
        unchanged_assumes=unchanged_assumes,
        unchanged_checks=unchanged_checks,
        discharged_checks=discharged_checks,
        discharged_assumes=discharged_assumes,
        simplified_assumes=simplified_assumes,
        simplified_checks=simplified_checks,
        added_assumes=added_assumes,
        added_checks=added_checks,
    )
    assert unchanged_assumes + discharged_assumes + simplified_assumes == assumes_before
    assert unchanged_assumes + simplified_assumes + added_assumes == assumes_after

    assert unchanged_checks + discharged_checks + simplified_checks == checks_before
    assert unchanged_checks + simplified_checks + added_checks == checks_after
    report.update(extra)
    return report
