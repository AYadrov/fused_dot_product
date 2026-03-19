from __future__ import annotations

from contextlib import contextmanager
from contextvars import ContextVar


class SpecRecorder:
    def __init__(self, ctx: SpecContext, spec_cache: dict):
        self.ctx = ctx
        self.spec_cache = spec_cache

_current_recorder: ContextVar[ProofRecorder | None] = ContextVar(
    "current_spec_recorder", default=None
)
_current_stage_name: ContextVar[str | None] = ContextVar(
    "current_spec_stage_name", default=None
)


@contextmanager
def record_specs(recorder: SpecRecorder):
    recorder_token = _current_recorder.set(recorder)
    stage_token = _current_stage_name.set(None)
    try:
        yield
    finally:
        _current_stage_name.reset(stage_token)
        _current_recorder.reset(recorder_token)


@contextmanager
def spec(name: str):
    recorder = _current_recorder.get()
    if recorder is None:
        raise RuntimeError(f"Spec block {name} is not located inside Composite")
    
    if _current_stage_name.get() is not None:
        raise RuntimeError(f"Nested spec blocks are not supported, {name} block is nested inside {_current_stage_name.get()} block")
    
    stage_token = _current_stage_name.set(name)
    try:
        yield lambda node: node._evaluate_spec(recorder.ctx, recorder.spec_cache), recorder.ctx
    finally:
        _current_stage_name.reset(stage_token)
