from fused_dot_product.config import *
from fused_dot_product.ast import *

from fixedpoint import FixedPoint, resize
from random import getrandbits


def generate_BF16_1x4(shared_exponent_bits: int):
    unshared_exponent_bits = BF16_EXPONENT_BITS - shared_exponent_bits
    assert shared_exponent_bits <= BF16_EXPONENT_BITS
    assert shared_exponent_bits >= 0
    assert Wf > 2 # At least two bits are required for integer part of a fixed point

    # Generating input data of type: 
    #   List[(sign, exponent, mantissa)]
    shared_exp = getrandbits(shared_exponent_bits) * 2 ** unshared_exponent_bits
    a = [(getrandbits(1), shared_exp + getrandbits(unshared_exponent_bits), getrandbits(BF16_MANTISSA_BITS)) for _ in range(1, N+1)]
    return a

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

def LEFT_FXP_SHIFT(FXP: FixedPoint, sh: int) -> FixedPoint:
    FXP_resized = resize(FXP, FXP.m + sh, FXP.n)
    return FXP_resized << sh

# Carry save add for a general case
# For a fixed number of inputs you may not need to shift carry every time after CSA
def CSA(a: FixedPoint, b: FixedPoint, c: FixedPoint):
    sum_  = a ^ b ^ c
    carry = (a & b) | (a & c) | (b & c)
    return sum_, LEFT_SHIFT(carry, 1)
