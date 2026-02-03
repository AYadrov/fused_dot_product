import time
import random
import math
from cvc5.pythonic import FreshReal, Solver, Or, And, ToInt, If, FreshInt, ToReal

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
    def spec(x, s):
        sign = FreshInt('sign')
        mantissa = FreshInt('mantissa')
        exponent = FreshInt('exponent')
        
        s.add(Or(sign == 0, sign == 1))
        s.add(And(mantissa >= 0, mantissa <= 2**BFloat16.mantissa_bits - 1))
        s.add(And(exponent >= 0, exponent <= 2**BFloat16.exponent_bits - 1))
        
        sign = ToReal(sign)
        mantissa = ToReal(mantissa)
        exponent = ToReal(exponent)
        
        sign_ = If(sign == 0, 1.0, -1.0)
        mantissa_ = 1.0 + (mantissa / 2 ** BFloat16.mantissa_bits)
        exponent_ = exponent - BFloat16.exponent_bias
        
        s.add(x == sign_ * mantissa_ * 2 ** (exponent_))
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

