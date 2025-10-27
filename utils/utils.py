from fused_dot_product.config import *
from fused_dot_product.ast import *

from random import getrandbits


def generate_BF16_2x4x1(shared_exponent_bits: int):
    unshared_exponent_bits = BF16_EXPONENT_BITS - shared_exponent_bits
    assert shared_exponent_bits < (1 << BF16_EXPONENT_BITS)
    assert shared_exponent_bits >= 0

    # Generating input data of type: 
    #   List[(sign, exponent, mantissa)]
    shared_exp = getrandbits(shared_exponent_bits) << unshared_exponent_bits
    a = [(getrandbits(1), shared_exp + getrandbits(unshared_exponent_bits), getrandbits(BF16_MANTISSA_BITS)) for _ in range(1, N+1)]
    b = [(getrandbits(1), shared_exp + getrandbits(unshared_exponent_bits), getrandbits(BF16_MANTISSA_BITS)) for _ in range(1, N+1)]
    return a, b

# Function encodes floating-point given sign, exponent and mantissa
def S_E_M2float(s: int,  e: int, m: int) -> float:
    assert e.bit_length() <= BF16_EXPONENT_BITS
    assert m.bit_length() <= BF16_MANTISSA_BITS
    assert s == 0 or s == 1

    m_ = 1.0 + m / (2 ** BF16_MANTISSA_BITS)
    return (-1) ** s * m_ * 2 ** (e - BF16_BIAS)

def unfused_dot_product(FP_xs: list[float], FP_ys: list[float]) -> list[float]:
    assert len(FP_xs) == len(FP_ys)

    out = 0
    for i in range(len(FP_xs)):
        out += FP_xs[i] * FP_ys[i]
    return out

def OR_tree(bits: list[int]) -> int:
    return int(any(bits))
