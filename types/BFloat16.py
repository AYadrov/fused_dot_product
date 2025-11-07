import time
import random
import math

from fused_dot_product.types.types import *
from fused_dot_product.types.Int import *
from fused_dot_product.ast.AST import *

def BF16_mantissa_to_UQ(mantissa: Node) -> Composite:
    def spec(mantissa: int) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
    
    mantissa_ = Or(mantissa, Lshift(Const(Int(1)), Const(Int(7), "BF16_MANTISSA_BITS")))
    impl = Int_to_UQ(mantissa_, Const(Int(1)), Const(Int(7)))
    
    return Composite(spec, impl, [mantissa], "bf16_mantissa_to_UQ")

def BF16_mantissa(x: Node) -> Op:
    def spec(x: int) -> int:
        if x == 0.0:
            return 0
        exp = math.floor(math.log2(abs(x)))
        frac = abs(x) / (2 ** exp) - 1.0
        return int(frac * (2 ** BFloat16.mantissa_bits))
    
    def impl(x: BFloat16) -> Int:
        return Int(x.mantissa, BFloat16.mantissa_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="BF16_mantissa")

def BF16_exponent(x: Node) -> Op:
    """Returns biased exponent of BFloat16."""
    def spec(x: float) -> float:
        if x == 0:
            return 0
        else:
            return math.floor(math.log2(abs(x))) + BFloat16.exponent_bias
    
    def impl(x: BFloat16) -> Int:
        return Int(x.exponent, BFloat16.exponent_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="BF16_unbaised_exponent")

def BF16_sign(x: Node) -> Op:
    def spec(x: float) -> float:
        if x < 0:
            return 1
        else:
            return 0
    
    def impl(x: BFloat16) -> Int:
        return Int(x.sign)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="BF16_sign")
