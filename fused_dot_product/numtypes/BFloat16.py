import time
import random
import math
from z3 import FreshReal, Solver, Or, And, ToInt, If

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Tuple import *
from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.z3_utils import pow2_int

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
    def spec(x, s):
        sign = FreshReal('sign')
        mantissa = FreshReal('mantissa')
        exponent = FreshReal('exponent')
        
        s.add(sign == ToInt(sign))
        s.add(mantissa == ToInt(mantissa))
        s.add(exponent == ToInt(exponent))
        
        s.add(Or(sign == 0, sign == 1))
        s.add(And(mantissa >= 0, ToInt(mantissa) <= 2**BFloat16.mantissa_bits - 1))
        s.add(And(exponent >= 0, ToInt(exponent) <= 2**BFloat16.exponent_bits - 1))
        
        sign_ = If(sign == 0, 1.0, -1.0)
        mantissa_ = 1.0 + (ToInt(mantissa) / 2 ** BFloat16.mantissa_bits)
        exponent_ = ToInt(exponent) - BFloat16.exponent_bias
        min_exp = -BFloat16.exponent_bias
        max_exp = (2**BFloat16.exponent_bits - 1) - BFloat16.exponent_bias
        s.add(exponent_ >= min_exp)
        s.add(exponent_ <= max_exp)
       
        s.add(x == sign_ * mantissa_ * pow2_int(exponent_))
        return tuple([sign, mantissa, exponent])
    
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

    
