from __future__ import annotations

from contextlib import contextmanager
from contextvars import ContextVar


class SpecRecorder:
    def __init__(self, ctx: SpecContext):
        self.ctx = ctx

_current_recorder: ContextVar[SpecRecorder | None] = ContextVar(
    "current_spec_recorder", default=None
)
_current_stage: ContextVar[bool | None] = ContextVar(
    "current_spec_stage", default=None
)


@contextmanager
def record_specs(recorder: SpecRecorder):
    recorder_token = _current_recorder.set(recorder)
    stage_token = _current_stage.set(None)
    try:
        yield
    finally:
        _current_stage.reset(stage_token)
        _current_recorder.reset(recorder_token)


@contextmanager
def context():
    recorder = _current_recorder.get()
    if recorder is None:
        raise RuntimeError(f"Spec block is not located inside Composite")
    
    if _current_stage.get() is not None:
        raise RuntimeError(f"Nested spec blocks are not supported")
    
    stage_token = _current_stage.set(True)
    try:
        yield recorder.ctx
    finally:
        _current_stage.reset(stage_token)
