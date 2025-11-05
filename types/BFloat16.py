import time
import random

from fused_dot_product.types.types import *
from fused_dot_product.types.Int import *
from fused_dot_product.ast.AST import *
from fused_dot_product.config import *


def BF16_mantissa_to_UQ(mantissa: Node) -> Composite:
    def spec(mantissa: int) -> float:
        return (float(mantissa) / (2 ** BF16_MANTISSA_BITS)) + 1.0
        
    mantissa_ = Or(mantissa, Lshift(Const(Int(1)), Const(Int(BF16_MANTISSA_BITS), "BF16_MANTISSA_BITS")))
    impl = Int_to_UQ(mantissa_, Const(Int(1)), Const(Int(7)))
    
    return Composite(spec, impl, [mantissa], "bf16_mantissa_to_UQ")
