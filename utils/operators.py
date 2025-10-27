# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *
from fused_dot_product.config import *

import math

########## CUSTOM OPERATORS ########
    
# Operator encodes floating-point given a fix-point mantissa and exponent
def UQ_E2float(fxp, fraction_bits, e) -> Operator:
    def spec(m: int, fraction_bits: int, e: int):
        return float(m) / 2**fraction_bits * 2**(e - BF16_BIAS)
    def impl(m: int, fraction_bits: int, e: int):
        return float(m) / 2**fraction_bits * 2**(e - BF16_BIAS)
        
    return Operator(
        spec=spec,
        impl=impl,
        comp=lambda x: x,
        args=[fxp, fraction_bits, e],
        name="FXP_E2float"
    )
    
def bf16_mantissa_to_UQ(m) -> Operator:
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

def twos_complement_sign_bit(mantissa, bit_width) -> Operator:
    return Rshift(
        mantissa, Sub(bit_width, 1)
    )
    
def from_twos_complement(mantissa, bit_width) -> Operator:
    return Sub(
        mantissa,
        Lshift(twos_complement_sign_bit(mantissa, bit_width), bit_width)
    )
    
def extend_twos_complement(mantissa, bit_width, bit_width_new) -> Operator:
    extend_bits = Sub(bit_width_new, bit_width)
    sign = twos_complement_sign_bit(mantissa, bit_width)
    upper_bits = Sub(Lshift(sign, extend_bits), sign)
    return Or(mantissa, Lshift(upper_bits, bit_width))
 
def conventional_max_exponent(e0, e1, e2, e3):
    return Max(Max(e0, e1), Max(e2, e3))

def conventional_adder_tree(x0, x1, x2, x3, bit_width) -> Operator:
    res1 = Add_twos_complement(x0, bit_width, x1, bit_width)
    res2 = Add_twos_complement(x2, bit_width, x3, bit_width) 
    bit_width_ = Add(1, bit_width)
    return Add_twos_complement(res1, bit_width_, res2, bit_width_)

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

def Add_twos_complement(x, x_bits, y, y_bits) -> Operator:
    output_len = Add(Max(x_bits, y_bits), 1)
    x_ = extend_twos_complement(x, x_bits, output_len)
    y_ = extend_twos_complement(y, y_bits, output_len)
    mask = Sub(Lshift(1, output_len), 1)
    return And(Add(x_, y_), mask)

# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
# The result's length is bit_width+3
def CSA_TREE4(m0, m1, m2, m3, bit_width) -> Operator:
    s1, c1 = CSA(m0, m1, m2)
    m3_ = extend_twos_complement(m3, bit_width, Add(1, bit_width))
    s1_ = extend_twos_complement(s1, bit_width, Add(1, bit_width))
    s2, c2 = CSA(m3_, s1_, c1)
    return Add_twos_complement(s2, Add(1, bit_width), c2, Add(2, bit_width))

# Carry save add for a general case
# Depending on a task, you may not need to shift carry every time after CSA
def CSA(a, b, c):
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

