import time
import random
import math

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Tuple import *
from fused_dot_product.ast.AST import *
from fused_dot_product.egglog import *

from random import randint

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
    def spec(x, egraph):
        rnd = str(randint(0, 10000))
        sign = egraph.let("sign" + rnd, Math.var("sign" + rnd))
        mantissa = egraph.let("mantissa" + rnd, Math.var("mantissa" + rnd))
        exponent = egraph.let("exponent" + rnd, Math.var("exponent" + rnd))
    
        sign_ = (- Math.lit(1)) ** sign
        mantissa_ = Math.lit(1) + (mantissa * Math.exp2(- Math.lit(BFloat16.mantissa_bits)))
        exponent_ = exponent + (- Math.lit(BFloat16.exponent_bias))
        egraph.register(
            union(x).with_(sign_ * mantissa_ * Math.exp2(exponent_)))
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




