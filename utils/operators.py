# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *
from fused_dot_product.config import *

import math
from fixedpoint import FixedPoint, resize

########## CUSTOM OPERATORS ########

# Operator encodes floating-point given a fix-point mantissa and exponent
def FXP_E2float(fxp, e) -> Operator:
    def spec(m: FixedPoint, e: int):
        return float(m) * 2**(e - BF16_BIAS)
    def impl(m: FixedPoint, e: int):
        return float(m) * 2**(e - BF16_BIAS)
        
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[fxp, e],
        name="FXP_E2float"
    )
    
def bf16_mantissa_to_FXP(m) -> Operator:
    def spec(m: int):
        return FixedPoint(1.0 + m / (2 ** BF16_MANTISSA_BITS))
    def impl(m: int):
        assert m.bit_length() <= BF16_MANTISSA_BITS
        assert m >= 0
        return FixedPoint(f"0b1{m:0{BF16_MANTISSA_BITS}b}", signed=0, m=1, n=BF16_MANTISSA_BITS, str_base=2)
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: float(x),
        args=[m],
        name="bf16_mantissa_to_FXP"
    )

def bf16_mantissa_to_FXP_NEW(m) -> Operator:
    return Or(m, Lshift(1, BF16_MANTISSA_BITS))

# Function extends mantissa length by one
def to_twos_complement(mantissa, sign, bit_width) -> Operator:
    full_width = Add(bit_width, 1)
    two_pow = Lshift(1, full_width)
    # Compute both candidates
    neg = Sub(two_pow, mantissa)  # 2^(bit_width+1) - mantissa
    pos = mantissa
    # Select one using sign mask: result = pos*(1-sign) + neg*sign
    return Add(Mul(Sub(1, sign), pos), Mul(sign, neg))

def extract_sign_bit(mantissa, bit_width) -> Operator:
    return Rshift(
        mantissa, Sub(bit_width, 1)
    )
    
def from_twos_complement(mantissa, bit_width) -> Operator:
    return Sub(
        mantissa,
        Lshift(extract_sign_bit(mantissa, bit_width), bit_width)
    )
    
def extend_twos_complement(mantissa, bit_width, extend_bits) -> Operator:
    sign = extract_sign_bit(mantissa, bit_width)
    upper_bits = Sub(Lshift(sign, extend_bits), sign)
    return Or(mantissa, Lshift(upper_bits, bit_width))
            
def TO_FXP(m, signed, integer_bits, fractional_bits):
    return Operator(
        spec=lambda m, signed, integer_bits, fractional_bits: FixedPoint(float(m) / (2 ** fractional_bits), signed=signed, m=integer_bits, n=fractional_bits),
        impl=lambda m, signed, integer_bits, fractional_bits: FixedPoint(float(m) / (2 ** fractional_bits), signed=signed, m=integer_bits, n=fractional_bits),
        comp=lambda x: x,
        args=[m, signed, integer_bits, fractional_bits],
        name="TO_FXP"
    )

def Mul_fxp(FXP_1, FXP_2) -> Operator:
    def spec(FXP_1: FixedPoint, FXP_2: FixedPoint) -> float:
        return float(FXP_1) * float(FXP_2)
        
    # Multiplication is done in full-precision - no accuracy lose 
    def impl(FXP_1: FixedPoint, FXP_2: FixedPoint) -> FixedPoint:
        FXP_out = FXP_1 * FXP_2
        
        assert FXP_out.m == FXP_1.m + FXP_2.m
        assert FXP_out.n == FXP_1.n + FXP_2.n
    
        return FXP_out
        
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: float(x),
        args=[FXP_1, FXP_2],
        name="Mul_fxp"
    )

# acc_req is the required bit length after the shift (accuracy requirement)
def RIGHT_SHIFT_FXP(FXP, sh, acc_req) -> Operator:
    def spec(FXP: FixedPoint, sh: int, acc_req: int) -> float:
        return float(FXP)/2**sh
        
    def impl(FXP: FixedPoint, sh: int, acc_req: int) -> FixedPoint:
        FXP_resized = resize(FXP, FXP.m, acc_req - FXP.m)
        return FXP_resized >> sh
        
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: float(x),
        args=[FXP, sh, acc_req],
        name="RIGHT_SHIFT_FXP"
    )

def FXP_ADD_SIGN(FXP, sign) -> Operator:
    def spec(FXP: FixedPoint, sign: int) -> FixedPoint:
        return FXP * (-1) ** sign
    
    def impl(FXP: FixedPoint, sign: int) -> FixedPoint:
        assert sign in (0, 1)
        m_ = FXP.m + 1
        with FXP(m=m_, signed=1):
            return -FixedPoint(FXP) if sign else FixedPoint(FXP)
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: float(x),
        args=[FXP, sign],
        name="FXP_ADD_SIGN"
    )
 
def conventional_max_exponent(e0, e1, e2, e3):
    return Max(Max(e0, e1), Max(e2, e3))

def conventional_adder_tree(FXP0, FXP1, FXP2, FXP3) -> Operator:
    def spec(FXP0: FixedPoint,
             FXP1: FixedPoint,
             FXP2: FixedPoint,
             FXP3: FixedPoint) -> FixedPoint:
        return FXP0 + FXP1 + FXP2 + FXP3
    
    def impl(FXP0: FixedPoint,
             FXP1: FixedPoint,
             FXP2: FixedPoint,
             FXP3: FixedPoint) -> FixedPoint:
         return (FXP0 + FXP1) + (FXP2 + FXP3)
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: float(x),
        args=[FXP0, FXP1, FXP2, FXP3],
        name="conventional_adder_tree"
    )

# Operator calculates a maximum exponent for {ep}s with length {n}
def OPTIMIZED_MAX_EXP(e0, e1, e2, e3, bit_width) -> Operator:
    def spec(e0: int, e1: int, e2: int, e3: int, bit_width: int) -> int:
        return max(max(e0, e1), max(e2, e3))
    
    def impl(e0: int, e1: int, e2: int, e3: int, bit_width: int) -> int:
        assert bit_width > 0
        exponents = [e0, e1, e2, e3]
        num_elements = len(exponents)
        
        # Binary representations of exponents, extra element {0} for convenience
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
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[e0, e1, e2, e3, bit_width],
        name="OPTIMIZED_MAX_EXP"
    )

# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
# The result's length is bit_width+3
def CSA_TREE4(m0, m1, m2, m3, bit_width) -> Operator:
    s1, c1 = CSA(m0, m1, m2)
    m3_ = extend_twos_complement(m3, bit_width, 1)
    s1_ = extend_twos_complement(s1, bit_width, 1)
    s2, c2 = CSA(m3_, s1_, c1)
    return Add(from_twos_complement(s2, Add(bit_width, 1)), from_twos_complement(c2, Add(bit_width, 2)))

# Carry save add for a general case
# For a fixed number of inputs you may not need to shift carry every time after CSA
def CSA(a: FixedPoint, b: FixedPoint, c: FixedPoint):
    sum_  = Xor(Xor(a, b), c)
    carry = Or(Or(And(a, b), And(a, c)), And(b, c))
    return sum_, Lshift(carry, 1)

# Take last {s} bits of number x
def take_last_n_bits(x, n) -> Operator:
    return And(x, (Sub(Lshift(1, n), 1)))

# This function is wrong when x < 0
def drop_last_n_bits(x, n) -> Operator:
    def spec(x: int, n: int) -> int:
        return math.floor(x / (2**n))
    
    def impl(x: int, n: int) -> int:
        return x >> n
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[x, n],
        name="drop_last_n_bits"
    )

# Negate bits of {x}
# negate_bits(3, 2) -> 0, because '0b11' -> '0b00'
# negate_bits(0, 2) -> 3
def invert_bits(x, s) -> Operator:
    return Sub(Sub(Lshift(1, s), 1), x)

def EXP_OVERFLOW_UNDERFLOW_HANDLING(e) -> Operator:
    def spec(e: int) -> int:
        return min(max(e, 0), 255)
    def impl(e: int) -> int:
        if e <= 0:
            raise Exception("Underflow")
        elif e >= 255:
            raise Exception("Overflow")
        return min(max(e, 0), 255)
    
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[e],
        name="EXP_OVERFLOW_UNDERFLOW_HANDLING"
    )

def exponents_adder(x, y) -> Operator:
    return Sub(Add(x, y), BF16_BIAS)

