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
        if int_bits.runtime_val and frac_bits.runtime_val:
            return UQT(int_bits.runtime_val.val, frac_bits.runtime_val.val)
        else:
            raise TypeError("Int_to_UQ depends on a variable. Impossible to typecheck")
    
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
            return IntT(max(x.total_bits - y.runtime_val.val, 1))
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, n],
            name="Rshift")

def Select(x: Node, start: Node, end: Node) -> Op:
    def impl(x: Int, start: Int, end: Int) -> Int:
        assert start.val >= 0 and end.val >= 0, "Indexing at Select can not be negative"
        assert start.val < x.width, f"Indexing is out of range! Given: [{start.val}:{end.val}], width: {x.width}"
        if start.val >= end.val:
            val = (x.val >> end.val) & ((1 << (start.val - end.val + 1)) - 1)
            width = start.val - end.val + 1
            return Int(val, width)
        else:
            raise ValueError(f"Start index ({start.val}) is less that end index ({end.val})")
    
    def sign(x: IntT, start: IntT, end: IntT) -> IntT:
        if start.runtime_val and end.runtime_val:
            return IntT(start.runtime_val.val - end.runtime_val.val + 1)
        else:
            raise TypeError("Select's indexing depends on a variable. Impossible to typecheck")
    
    def spec(x: int, start: int, end: int) -> int:
        return (x >> end) & ((1 << (start - end + 1)) - 1)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, start, end],
            name="Select")

def Invert(x: Node, s: Node) -> Op:
    def spec(x: int, s: int) -> int:
        return (2**s - 1) - x
    
    def impl(x: Int, s: Int) -> Int:
        assert s.val == x.width, "Oops, s can not be greater than x.width in this implementation"
        val = ((1 << x.width) - 1) - x.val
        width = x.width
        return Int(val, width)
    
    def sign(x: IntT, s: IntT) -> IntT:
        return IntT(x.total_bits)
    
    return Op(
            spec=spec,
            impl=impl,
            signature=sign,
            args=[x, s],
            name="Invert")


if __name__ == '__main__':
    assert Add(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(8)
    assert Sub(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(8)
    assert Mul(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(10)
    assert Max(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(7)
    assert Min(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(7)
    assert And(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(3)
    assert Or(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(7)
    assert Xor(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(7)
    assert Lshift(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(103)
    assert Rshift(Const(Int(val=2, width=3)), Const(Int(val=100, width=7))).static_typecheck() == IntT(1)
    assert Int_to_UQ(Var(name='x', signature=IntT(10)), Const(Int(val=2, width=3)), Const(Int(val=2, width=3))).static_typecheck() == UQT(2, 2)

