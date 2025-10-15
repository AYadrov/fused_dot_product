from config import *
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

# Function encodes floating-point given a fix-point mantissa and exponent
def FXP_E2float(fxp: FixedPoint, e: int) -> float:
    return float(fxp) * 2 ** (e - BF16_BIAS)

# Function is given mantissa bits of BFfloat16 format as integers
#   Mantissas are casted to Q1.7 as 0b1[7 mantissa bits] binary representation
#   Then, fixpoint mantissas are multiplied using internal functions
def MxM2FXP(m_1: int, m_2: int) -> FixedPoint:
    assert m_1.bit_length() <= BF16_MANTISSA_BITS
    assert m_2.bit_length() <= BF16_MANTISSA_BITS
    assert m_1 >= 0 and m_2 >= 0

    # FXP_1, FXP_2: UQ1.7
    # Decimal mantissa 1.01...01 converts to FXP as '0b101...01'
    FXP_1 = FixedPoint(f"0b1{m_1:0{BF16_MANTISSA_BITS}b}", signed=0, m=1, n=BF16_MANTISSA_BITS, str_base=2)
    FXP_2 = FixedPoint(f"0b1{m_2:0{BF16_MANTISSA_BITS}b}", signed=0, m=1, n=BF16_MANTISSA_BITS, str_base=2)

    # No rounding error at conversion
    fp_m_1 = 1.0 + m_1 / (2 ** BF16_MANTISSA_BITS)
    fp_m_2 = 1.0 + m_2 / (2 ** BF16_MANTISSA_BITS)
    assert abs(fp_m_1 - float(FXP_1)) == 0.0
    assert abs(fp_m_2 - float(FXP_2)) == 0.0

    # FXP_out: UQ2.14
    # Multiplication is done in full-precision - no accuracy lose
    FXP_out = FXP_1 * FXP_2
   
    # No rounding error after multiplication
    assert fp_m_1 * fp_m_2 == float(FXP_out)
    # Output size does match expectations
    assert FXP_out.m == 2 # product of two [1, 2) numbers give an output with 2 integer bits
    assert FXP_out.n == BF16_MANTISSA_BITS * 2

    return FXP_out

def unfused_dot_product(FP_xs: list[float], FP_ys: list[float]) -> list[float]:
    assert len(FP_xs) == len(FP_ys)

    out = 0
    for i in range(len(FP_xs)):
        out += FP_xs[i] * FP_ys[i]
    return out
    
def OR_tree(bits: list[int]) -> int:
    return int(any(bits))

# Function calculates a maximum exponent for {ep}s with length {n}
def OPTIMIZED_MAX_EXP(exponents: list[int], bit_width: int) -> int:
    assert bit_width > 0, "Bit width must be positive"
    num_elements = len(exponents)

    # Binary representations of exponents
    # extra element for convenience
    ep_bits = [
        [0] + list(map(int, f'{e:0{bit_width}b}'))
        for e in exponents
    ]
   
    smaller = [[0] * (bit_width + 1) for _ in range(num_elements)] # extra element for convenience
    maxexp = [0] * (bit_width + 1)

    # Process bits from MSB to LSB
    for i in range(1, bit_width + 1):
        data_for_or_tree = []
        for j in range(num_elements):
            res = not ((maxexp[i-1] and (not ep_bits[j][i-1])) or smaller[j][i-1])
            smaller[j][i] = not res
            data_for_or_tree.append(ep_bits[j][i] and res)
        maxexp[i] = OR_tree(data_for_or_tree)

    return int(''.join(map(str, map(int, maxexp))), 2)
    
# Take last {s} bits of number x
def take_last_bits(x: int, s: int) -> int:
    return x & (2**s - 1)

# Negate bits of {x}
# negate_bits(3, 2) -> 0, because '0b11' -> '0b00'
# negate_bits(0, 2) -> 3
def invert_bits(x: int, s: int) -> int:
    return (2**s - 1) - x

# acc_req is required bit length after the shift (accuracy requirement)
def RIGHT_SHIFT(FXP: FixedPoint, sh: int, acc_req: int) -> FixedPoint:
    FXP_resized = resize(FXP, FXP.m, acc_req - FXP.m)
    return FXP_resized >> sh

def LEFT_SHIFT(FXP: FixedPoint, sh: int) -> FixedPoint:
    FXP_resized = resize(FXP, FXP.m + sh, FXP.n)
    return FXP_resized << sh

def FXP_ADD_SIGN(FXP: FixedPoint, sign: int) -> FixedPoint:
    assert sign in (0, 1)
    m_ = FXP.m + 1
    with FXP(m=m_, signed=1):
        return -FixedPoint(FXP) if sign else FixedPoint(FXP)

# Carry save add for a general case
# For a fixed number of inputs you may not need to shift carry every time after CSA
def CSA(a: FixedPoint, b: FixedPoint, c: FixedPoint):
    sum_  = a ^ b ^ c
    carry = (a & b) | (a & c) | (b & c)
    return sum_, LEFT_SHIFT(carry, 1)

# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
def CARRY_SAVE_ADDER_TREE(FXPs: list[FixedPoint]) -> FixedPoint:
    assert len(FXPs) == 4
    s1, c1 = CSA(FXPs[0], FXPs[1], FXPs[2])
    s2, c2 = CSA(resize(FXPs[3], FXPs[3].m+1, FXPs[3].n), resize(s1, s1.m+1, s1.n), c1)
    return s2 + c2
