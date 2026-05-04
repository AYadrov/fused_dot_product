from .runtime import RuntimeType
from .static import StaticType

def _fingerprint_value(self, value):
    if isinstance(value, RuntimeType):
        return value._fingerprint()
    if isinstance(value, StaticType):
        return value._fingerprint()
    if isinstance(value, tuple):
        return tuple(self._fingerprint_value(item) for item in value)
    if isinstance(value, list):
        return tuple(self._fingerprint_value(item) for item in value)
    if isinstance(value, dict):
        return tuple(
            sorted(
                (self._fingerprint_value(key), self._fingerprint_value(val))
                for key, val in value.items()
            )
        )
    return value
