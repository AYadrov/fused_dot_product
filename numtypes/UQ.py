from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *


def UQ_to_Q(x: Node) -> Op:
    def spec(x: float) -> float:
        return x
    
    def impl(x: UQ) -> Q:
        return Q(x.val, x.int_bits + 1, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x],
            name="UQ_to_Q")

def UQ_Mul(x: Node, y: Node) -> Op:
    def spec(x: float, y: float) -> float:
        return x * y
    
    def impl(x: UQ, y: UQ) -> UQ:
        val_ = x.val * y.val
        int_bits_ = x.int_bits + y.int_bits
        frac_bits_ = x.frac_bits + y.frac_bits
        return UQ(val_, int_bits_, frac_bits_)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="UQ_Mul")

def UQ_Resize(x: Node, new_int_bits: Node, new_frac_bits: Node) -> Op:
    def spec(x: float, new_int_bits: int, new_frac_bits: int) -> float:
        return x
    
    def impl(x: UQ, new_int_bits: Int, new_frac_bits: Int) -> UQ:
        assert new_int_bits.val >= x.int_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        assert new_frac_bits.val >= x.frac_bits, "USER TRIES TO TRUNCATE! NOT IMPLEMENTED YET"
        
        return UQ(x.val << (new_frac_bits.val - x.frac_bits), new_int_bits.val, new_frac_bits.val)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, new_int_bits, new_frac_bits],
            name="UQ_Resize")

# TODO: spec does not match impl (I guess as it should)
def UQ_Rshift(x: Node, amount: Node) -> Op:
    def spec(x: float, amount: int) -> float:
        return x / (2 ** amount)
        
    def impl(x: UQ, amount: Int) -> UQ:
        return UQ(x.val >> amount.val, x.int_bits, x.frac_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, amount],
            name="UQ_Rshift")
 
