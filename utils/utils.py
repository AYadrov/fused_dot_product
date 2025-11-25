import struct
import math
import numpy as np
import inspect

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
        
    elif isinstance(x, tuple) and isinstance(y, tuple):
        return max([ulp_distance(x_, y_) for x_, y_ in zip(x, y)])
    
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
    
def mask(x, n):
    return x & ((1 << n) - 1)
    
def make_fixed_arguments(f, default_type, N):

    # Desired signature parameters
    params = [
        inspect.Parameter(
            f"arg{i}",
            inspect.Parameter.POSITIONAL_ONLY,
            annotation=default_type,
        )
        for i in range(N)
    ]

    ret_ann = f.__annotations__.get("return", inspect._empty)

    sig = inspect.Signature(
        parameters=params,
        return_annotation=ret_ann,
    )

    # ---- wrapper that enforces strict arity ----
    def wrapper(*args):
        if len(args) != N:
            raise TypeError(f"{f.__name__} expects {N} arguments, got {len(args)}")
        return f(*args)  # f expects N args too

    # Apply signature + metadata
    wrapper.__signature__ = sig
    wrapper.__annotations__ = {
        **{f"arg{i}": default_type for i in range(N)},
        "return": ret_ann,
    }
    wrapper.__name__ = f.__name__
    wrapper.__qualname__ = f.__qualname__
    wrapper.__doc__ = f.__doc__

    return wrapper

