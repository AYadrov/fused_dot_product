import time
import random
import math

from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Int import *
from fused_dot_product.ast.AST import *

def BF16_mantissa_to_UQ(mantissa: Node) -> Composite:
    def spec(mantissa: int) -> float:
        return (float(mantissa) / (2 ** 7)) + 1.0
        
    def sign(mantissa: IntT) -> UQT:
        return UQT(1, 7)
    
    mantissa_ = Or(mantissa, Lshift(Const(Int(1)), Const(Int(BFloat16.mantissa_bits), "BF16_MANTISSA_BITS")))
    impl = Int_to_UQ(mantissa_, Const(Int(1)), Const(Int(BFloat16.mantissa_bits), "BF16_MANTISSA_BITS"))
    
    return Composite(spec=spec, 
                     impl=impl, 
                     sign=sign,
                     args=[mantissa], 
                     name="BF16_mantissa_to_UQ")

def BF16_decode(x: Node) -> Op:
    def spec(x: int) -> Tuple[int, int, int]:
        def sign(x):
            if x < 0:
                return 1
            else:
                return 0

        def mantissa(x):
            if x == 0.0:
                return 0
            exp = math.floor(math.log2(abs(x)))
            frac = abs(x) / (2 ** exp) - 1.0
            return int(frac * (2 ** 7))

        def exponent(x):
            if x == 0:
                return 0
            else:
                return math.floor(math.log2(abs(x))) + 127
        return (
            sign(x),
            mantissa(x),
            exponent(x),
        )

    def impl(x: BFloat16) -> Tuple:
        return Tuple(
            Int(x.sign, 1),
            Int(x.mantissa, 7),
            Int(x.exponent, 8),
        )

    def signature(x: BFloat16T) -> TupleT:
        return TupleT(
            IntT(1),
            IntT(7),
            IntT(8),
        )

    return Op(
        spec=spec,
        impl=impl,
        signature=signature,
        args=[x],
        name="BF16_decode")

def BF16_mantissa(x: Node) -> Op:
    def spec(x: int) -> int:
        if x == 0.0:
            return 0
        exp = math.floor(math.log2(abs(x)))
        frac = abs(x) / (2 ** exp) - 1.0
        return int(frac * (2 ** 7))
    
    def impl(x: BFloat16) -> Int:
        return Int(x.mantissa, 7)
    
    def sign(x: BFloat16T) -> IntT:
        return IntT(7)

    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="BF16_mantissa")

def BF16_exponent(x: Node) -> Op:
    """Returns biased exponent of BFloat16."""
    def spec(x: float) -> float:
        if x == 0:
            return 0
        else:
            return math.floor(math.log2(abs(x))) + 127
    
    def impl(x: BFloat16) -> Int:
        return Int(x.exponent, 8)
    
    def sign(x: BFloat16T) -> IntT:
        return IntT(8)

    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="BF16_exponent")

def BF16_sign(x: Node) -> Op:
    def spec(x: float) -> float:
        if x < 0:
            return 1
        else:
            return 0
    
    def impl(x: BFloat16) -> Int:
        return Int(x.sign, 1)
    
    def sign(x: BFloat16T) -> IntT:
        return IntT(1)

    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x],
            name="BF16_sign")

