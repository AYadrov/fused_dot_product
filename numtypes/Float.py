from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.ast.AST import *

def _float32_alloc(sign_bit: Node,
                   mantissa: Node,
                   exponent: Node) -> Op:
    def sign(sign_bit: StaticType, mantissa: StaticType, exponent: StaticType) -> Float32T:
        return Float32T()
    
    def impl(sign_bit: RuntimeType, mantissa: RuntimeType, exponent: RuntimeType) -> Float32:
        return Float32(sign_bit.val, mantissa.val, exponent.val)
    
    return Op(
        sign=sign,
        impl=impl,
        args=[sign_bit, mantissa, exponent],
        name="_float32_alloc")
