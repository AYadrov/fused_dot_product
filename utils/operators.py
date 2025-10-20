from ..ast import *
from .utils import *

# Function encodes floating-point given a fix-point mantissa and exponent
@operator(
    spec=lambda m, e: float(m) * 2**(e - BF16_BIAS))
def FXP_E2float(fxp: FixedPoint, e: int) -> float:
    return float(fxp) * 2 ** (e - BF16_BIAS)
    
@operator(
    spec=lambda m: FixedPoint(1.0 + m / (2 ** BF16_MANTISSA_BITS)),
    comp=float)
def bf16_mantissa_to_FXP(m: int):
    assert m.bit_length() <= BF16_MANTISSA_BITS
    assert m >= 0
    return FixedPoint(f"0b1{m:0{BF16_MANTISSA_BITS}b}", signed=0, m=1, n=BF16_MANTISSA_BITS, str_base=2)

@operator(
    spec=lambda x, y: float(x) * float(y),
    comp=float)
def MxM2FXP(FXP_1: FixedPoint, FXP_2: FixedPoint) -> FixedPoint:

    # Multiplication is done in full-precision - no accuracy lose
    FXP_out = FXP_1 * FXP_2
   
    assert FXP_out.m == FXP_1.m + FXP_2.m
    assert FXP_out.n == FXP_1.n + FXP_2.n

    return FXP_out
    
# Function calculates a maximum exponent for {ep}s with length {n}
@operator(
    spec=lambda exponents, bit_width: max(exponents))
def OPTIMIZED_MAX_EXP(exponents: list[int], bit_width: int) -> int:
    assert bit_width > 0, "Bit width must be positive"
    num_elements = len(exponents)

    # Binary representations of exponents
    # extra element {0} for convenience
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
    
# acc_req is the required bit length after the shift (accuracy requirement)
@operator(
    spec=lambda FXP, sh, acc_req: float(FXP)/2**sh,
    comp=float)
def RIGHT_SHIFT(FXP: FixedPoint, sh: int, acc_req: int) -> FixedPoint:
    FXP_resized = resize(FXP, FXP.m, acc_req - FXP.m)
    return FXP_resized >> sh
    
@operator(
    spec=lambda FXP, sign: FXP * (-1) ** sign,
    comp=float)
def FXP_ADD_SIGN(FXP: FixedPoint, sign: int) -> FixedPoint:
    assert sign in (0, 1)
    m_ = FXP.m + 1
    with FXP(m=m_, signed=1):
        return -FixedPoint(FXP) if sign else FixedPoint(FXP)
        
# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
@operator(
    spec=sum,
    comp=float)
def CARRY_SAVE_ADDER_TREE(FXPs: list[FixedPoint]) -> FixedPoint:
    assert len(FXPs) == 4
    s1, c1 = CSA(FXPs[0], FXPs[1], FXPs[2])
    s2, c2 = CSA(resize(FXPs[3], FXPs[3].m+1, FXPs[3].n), resize(s1, s1.m+1, s1.n), c1)
    return s2 + c2

