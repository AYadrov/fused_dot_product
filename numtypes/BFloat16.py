import time
import random
import math

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Tuple import *
from fused_dot_product.ast.AST import *

########### Private Helpers ############

def _bf16_mantissa(x: Node) -> Op:
    def impl(x: BFloat16) -> UQ:
        return UQ(x.mantissa, 7, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(7, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x],
            name="_bf16_mantissa")

def _bf16_exponent(x: Node) -> Op:
    def impl(x: BFloat16) -> UQ:
        return UQ(x.exponent, 8, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(8, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x],
            name="_bf16_exponent")

def _bf16_sign(x: Node) -> Op:
    def impl(x: BFloat16) -> UQ:
        return UQ(x.sign, 1, 0)
    
    def sign(x: BFloat16T) -> UQT:
        return UQT(1, 0)
    
    return Op(
            impl=impl,
            sign=sign,
            args=[x],
            name="_bf16_sign")

############## Public API ##############

def bf16_decode(x: Node) -> Primitive:
    def spec(x: float, out: float) -> tuple[float]:
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
        
        return sign(x) == out[0] and mantissa(x) == out[1] and exponent(x) == out[2]
    
    def sign(x: BFloat16T) -> TupleT:
        return TupleT(
            UQT(1, 0),
            UQT(7, 0),
            UQT(8, 0),
        )
    
    def impl(x: Node) -> Node:
        impl = make_Tuple(
            _bf16_sign(x),
            _bf16_mantissa(x),
            _bf16_exponent(x),
        )
        return impl
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x],
        name="bf16_decode")





