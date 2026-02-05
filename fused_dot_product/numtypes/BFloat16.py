import time
import random
import math
from cvc5.pythonic import FreshReal, Solver, Or, And, ToInt, If, FreshInt, ToReal, IntVal

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Tuple import *
from fused_dot_product.ast.AST import *

########### Private Helpers ############

def _scale_by_pow2_shift(base, shift_int, max_abs_shift: int):
    # Encode base * 2**shift_int without symbolic POW.
    bit_count = max_abs_shift.bit_length()
    pos_shift = If(shift_int >= 0, shift_int, IntVal(0))
    neg_shift = If(shift_int < 0, -shift_int, IntVal(0))

    scaled = base
    for bit in range(bit_count):
        factor = ToReal(IntVal(1 << (1 << bit)))
        pos_bit = (pos_shift / (2**bit)) % 2
        neg_bit = (neg_shift / (2**bit)) % 2
        scaled = If(pos_bit == 1, scaled * factor, scaled)
        scaled = If(neg_bit == 1, scaled / factor, scaled)
    return scaled

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
    def spec(prim, x, s):
        sign, mantissa, exponent = prim._spec_outputs(s)
        
        

        
        sign_ = If(sign == 0, 1.0, -1.0)
        mantissa_ = 1.0 + (mantissa / 2 ** BFloat16.mantissa_bits)
        exponent_int = ToInt(exponent) - BFloat16.exponent_bias
        # s.add(x == sign_ * mantissa_ * 2 ** (exponent_))
        
        s.add(exponent_int >= -BFloat16.exponent_bias)
        s.add(exponent_int <= (2 ** BFloat16.exponent_bits - 1) - BFloat16.exponent_bias)

        s.add(x == _scale_by_pow2_shift(sign_ * mantissa_, exponent_int, BFloat16.exponent_bias + 1))
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
