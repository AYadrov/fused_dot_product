import struct
import math
import numpy as np

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

