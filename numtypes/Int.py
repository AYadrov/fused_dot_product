from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *
        
# TODO: loss of accuracy can happen here
def Int_to_UQ(x: Node, int_bits: Node, frac_bits: Node) -> Op:
    def spec(x: int, int_bits: int, frac_bits: int) -> float:
        return x / 2 ** frac_bits

    def impl(x: Int, int_bits: Int, frac_bits: Int) -> UQ:
        total_bits = int_bits.val + frac_bits.val
        assert total_bits >= x.width
        return UQ(x.val, int_bits.val, frac_bits.val)
        
    def sign(x: IntT, int_bits: IntT, frac_bits: IntT) -> UQT:
        return UQT(int_bits, frac_bits)

    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, int_bits, frac_bits],
            name="Int_to_UQ")

def Add(x: Node, y: Node) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = x.val + y.val
        width_ = max(x.width, y.width) + 1
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return x + y
        
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(max(x.total_bits, y.total_bits) + 1)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Add")

def Sub(x: Node, y: Node) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = x.val - y.val
        width_ = max(x.width, y.width) + 1
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return x - y
        
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(max(x.total_bits, y.total_bits) + 1)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Sub")

def Mul(x: Node, y: Node) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = x.val * y.val
        width_ = x.width + y.width
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return x * y
        
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(x.total_bits + y.total_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Mul")

def Max(x: Node, y: Node) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = max(x.val, y.val)
        width_ = max(x.width, y.width)
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return max(x, y)
    
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(max(x.total_bits, y.total_bits))
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Max")

def Min(x: Node, y: Node) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = min(x.val, y.val)
        width_ = max(x.width, y.width)
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return min(x, y)
        
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(max(x.total_bits, y.total_bits))
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Min")

def And(x: Node, y: Node) -> Op:
    def impl(a: Int, b: Int) -> Int:
        val_ = a.val & b.val
        width_ = min(a.width, b.width)
        return Int(val_, width_)

    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * ((a >> n) & 1) * ((b >> n) & 1)
                for n in range(0, max(1, m.bit_length()))])
                
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(min(x.total_bits, y.total_bits))
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="And")

def Or(x: Node, y: Node) -> Op:
    def impl(a: Int, b: Int) -> Int:
        val_ = a.val | b.val
        width_ = max(a.width, b.width)
        return Int(val_, width_)
    
    def spec(a: int, b: int) -> int:
        return sum([(1 << n) * (((a >> n) & 1) + ((b >> n) & 1) - 
                 ((a >> n) & 1) * ((b >> n) & 1))
                    for n in range(0, max(1, max(a, b).bit_length()))])
         
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(max(x.total_bits, y.total_bits)) 
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Or")

def Xor(x: Node, y: Node) -> Op:
    def impl(a: Int, b: Int) -> Int:
        val_ = a.val ^ b.val
        width_ = max(a.width, b.width)
        return Int(val_, width_)
    
    def spec(a: int, b: int) -> int:
        return sum([(2**n) * (((a // 2**n) + (b // 2**n)) % 2)
                for n in range(0, max(1, max(a, b).bit_length()))])
    
    def sign(x: IntT, y: IntT) -> IntT:
        return IntT(max(x.total_bits, y.total_bits)) 
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, y],
            name="Xor")

def Lshift(x: Node, n: Node) -> Op:
    def impl(x: Int, n: Int) -> Int:
        assert n.val >= 0, f"Shift amount should be non-negative, {n.val} is provided"
        val_ = x.val << n.val
        width_ = x.width + n.val
        return Int(val_, width_)

    def spec(x: int, n: int) -> int:
        return x * 2 ** n
    
    def sign(x: IntT, y: IntT) -> IntT:
        if y.runtime_val is None:
            raise TypeError("Amount of Lshift depends on a variable. Impossible to typecheck")
        else:
            return IntT(x.total_bits + y.runtime_val.val)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, n],
            name="Lshift")
            
def Rshift(x: Node, n: Node) -> Op:
    def impl(x: Int, n: Int) -> Int:
        assert n.val >= 0, f"Shift amount should be non-negative, {n.val} is provided"
        val_ = x.val >> n.val
        width_ = max(x.width - n.val, 1)
        return Int(val_, width_)

    # Right shift operates stricly over integers
    def spec(x: int, n: int) -> int:
        return int(x / 2 ** n)
        
    def sign(x: IntT, y: IntT) -> IntT:
        if y.runtime_val is None:
            raise TypeError("Amount of Rshift depends on a variable. Impossible to typecheck")
        else:
            return IntT(x.total_bits - y.runtime_val.val, 1)

    return Op(
            spec=spec,
            impl=impl,
            args=[x, n],
            name="Rshift")
