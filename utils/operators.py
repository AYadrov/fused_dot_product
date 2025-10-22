# File defines custom user-defined Operators

from fused_dot_product.ast.AST import *
from fused_dot_product.utils.utils import *
from fused_dot_product.utils.basics import *
from fused_dot_product.config import *

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
            name="FXP_E2float")
    
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
            name="bf16_mantissa_to_FXP")

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
            name="Mul_fxp")
    
# Operator calculates a maximum exponent for {ep}s with length {n}
def OPTIMIZED_MAX_EXP(exponents, bit_width) -> Operator:
    def spec(exponents: list[int], bit_width: int) -> int:
        return max(exponents)
        
    def impl(exponents: list[int], bit_width: int) -> int:
        assert bit_width > 0
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
            args=[exponents, bit_width],
            name="OPTIMIZED_MAX_EXP")

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
            name="RIGHT_SHIFT_FXP")

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
            name="FXP_ADD_SIGN")
        
# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
def CSA_TREE4(FXP0, FXP1, FXP2, FXP3) -> Operator:
    def spec(FXP0: FixedPoint, 
             FXP1: FixedPoint, 
             FXP2: FixedPoint, 
             FXP3: FixedPoint) -> FixedPoint:
        return FXP0 + FXP1 + FXP2 + FXP3
    
    def impl(FXP0: FixedPoint, 
             FXP1: FixedPoint, 
             FXP2: FixedPoint, 
             FXP3: FixedPoint) -> FixedPoint:
        s1, c1 = CSA(FXP0, FXP1, FXP2)
        s2, c2 = CSA(resize(FXP3, FXP3.m+1, FXP3.n), resize(s1, s1.m+1, s1.n), c1)
        return s2 + c2
    
    return Operator(
            spec=spec,
            impl=impl,
            comp=lambda x: float(x),
            args=[FXP0, FXP1, FXP2, FXP3],
            name="CSA_TREE4")

# Take last {s} bits of number x
def take_last_s_bits(x, s) -> Operator:
    def spec(x: int, s: int) -> int:
        return x & (2 ** s - 1)
    def impl_constructor(x, s) -> int:
        return And(x, (Sub(Lshift(1, s), 1)))
    
    return Operator(
            spec=spec,
            impl=impl_constructor(x, s),
            comp=lambda x: x,
            args=[x, s],
            name="take_last_s_bits")

# Negate bits of {x}
# negate_bits(3, 2) -> 0, because '0b11' -> '0b00'
# negate_bits(0, 2) -> 3
def invert_bits(x, s) -> Operator:
    def spec(x: int, s: int) -> int:
        return (2**s - 1) - x
        
    def impl_constructor(x, s) -> Operator:
        return Sub(Sub(Lshift(1, s), 1), x)
    
    return Operator(
            spec=spec,
            impl=impl_constructor(x, s),
            comp=lambda x: x,
            args=[x, s],
            name="invert_bits")

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
            name="EXP_OVERFLOW_UNDERFLOW_HANDLING")
            
def exponents_adder(x, y):
    def spec(x: int, y: int) -> int:
        return x + y - (2**(BF16_EXPONENT_BITS-1) - 1)
    def impl_constructor(x, y) -> Operator:
        return Sub(Add(x, y), BF16_BIAS)
    
    return Operator(
            spec=spec,
            impl=impl_constructor(x, y),
            comp=lambda x: x,
            args=[x, y],
            name="exponents_adder")

