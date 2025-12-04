import time
import random
import math

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Tuple import *
from fused_dot_product.ast.AST import *

def BF16_decode(x: Node) -> Composite:
    def spec(x: float) -> tuple[float]:
        def sign(x):
            return 1.0 if x < 0 else 0.0
        
        def mantissa(x):
            if x == 0.0:
                return 0.0
            exp = math.floor(math.log2(abs(x)))
            frac = abs(x) / (2 ** exp) - 1.0
            return float(int(frac * (2 ** 7)))
        
        def exponent(x):
            return 0.0 if x == 0 else float(math.floor(math.log2(abs(x))) + 127)
        
        return sign(x), mantissa(x), exponent(x)
    
    def signature(x: BFloat16T) -> TupleT:
        return TupleT(
            UQT(1, 0),
            UQT(7, 0),
            UQT(8, 0),
        )
    
    def impl(x: Node) -> Node:
        impl = make_Tuple(
            BF16_sign(x),
            BF16_mantissa(x),
            BF16_exponent(x),
        )
        return impl
    
    return Composite(
        spec=spec,
        impl=impl,
        sign=signature,
        args=[x],
        name="BF16_decode")

def BF16_mantissa(x: Node) -> Op:
    def spec(x: float) -> float:
        if x == 0.0:
            return 0.0
        exp = math.floor(math.log2(abs(x)))
        frac = abs(x) / (2 ** exp) - 1.0
        return float(int(frac * (2 ** 7)))
    
    def impl(x: BFloat16) -> UQ:
        return UQ(x.mantissa, 7, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(7, 0)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="BF16_mantissa")

def BF16_exponent(x: Node) -> Op:
    def spec(x: float) -> float:
        if x == 0:
            return 1.0
        else:
            return float(math.floor(math.log2(abs(x))) + 127)
    
    def impl(x: BFloat16) -> UQ:
        return UQ(x.exponent, 8, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(8, 0)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="BF16_exponent")

def BF16_sign(x: Node) -> Op:
    def spec(x: float) -> float:
        if x < 0:
            return 1.0
        else:
            return 0.0
    
    def impl(x: BFloat16) -> UQ:
        return UQ(x.sign, 1, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(1, 0)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="BF16_sign")

