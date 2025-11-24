import struct
import math
import numpy as np
import inspect
from typing import Callable, Tuple, Any, Union, get_origin

def float_to_bits32(f):
    # pack float32 → 4 bytes, then unpack to unsigned int
    [bits] = struct.unpack('>I', struct.pack('>f', np.float32(f)))
    # Convert to lexicographically ordered integer space
    return bits ^ ((bits >> 31) & 0x7FFFFFFF)

def ulp_distance(x, y):
    if isinstance(x, float) and isinstance(y, float):
        if math.isnan(x) or math.isnan(y):
            return float('nan')
        if math.isinf(x) or math.isinf(y):
            return float('inf') if x != y else 0
        return abs(float_to_bits32(x) - float_to_bits32(y))
    elif isinstance(x, int) and isinstance(y, int):
        return abs(x - y)
    else:
        raise TypeError(f"Arguments are expected to have the same type, given {x} and {y}")
        
def round_to_the_nearest_even(x: int, x_len: int, target_len: int) -> int:
    bits_to_truncate = max(0, x_len - target_len)
            
    if bits_to_truncate > 0:
        # Bit positions relative to x
        guard_pos = bits_to_truncate - 1
        guard_bit = (x >> guard_pos) & 1
        
        round_pos = bits_to_truncate - 2
        round_bit = (x >> round_pos) & 1 if bits_to_truncate >= 2 else 0
        
        sticky_mask = (1 << max(0, bits_to_truncate - 2)) - 1
        sticky_bit = (x & sticky_mask) != 0
        
        x >>= bits_to_truncate
        
        # IEEE-754 round-to-nearest-even
        lsb = x & 1
        if guard_bit and (round_bit or sticky_bit or lsb):
            x += 1
    return x

def wrap_return_tuple(f: Callable[..., Union[Any, Tuple[Any, ...]]]) -> Callable[..., Tuple[Any, ...]]:
    orig_ret = f.__annotations__.get("return", inspect.Signature.empty)
    origin = get_origin(orig_ret)

    # --- check if the return annotation is already a Tuple ---
    if origin is tuple or origin is Tuple \
        or orig_ret is tuple \
        or orig_ret is Tuple:
        return f
    
    def wrapped(*args) -> Tuple[Any, ...]:
        out = f(*args)
        if isinstance(out, tuple):
            return out
        return (out,)

    wrapped.__annotations__ = dict(f.__annotations__)
    ret = wrapped.__annotations__.get("return", Any)
    wrapped.__annotations__["return"] = Tuple[ret, ...]

    sig = inspect.signature(f)
    params = list(sig.parameters.values())
    # New signature with updated return annotation
    wrapped.__signature__ = sig.replace(
        return_annotation=Tuple[sig.return_annotation, ...])

    # Mirror metadata
    wrapped.__name__ = f.__name__
    wrapped.__doc__ = f.__doc__
    wrapped.__qualname__ = f.__qualname__

    return wrapped
    
def flatten(lst: list[tuple[Any, ...]]) -> list[Any]:
    return [x for t in lst for x in t]
    
def mask(x, n):
    return x & ((1 << n) - 1)

