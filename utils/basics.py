# File defines basic operators for floating-point evaluations

from fused_dot_product.ast.AST import *
from fused_dot_product.ast.types import *

######### BASIC OPERATORS ##########
def Add(x, y) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = x.val + y.val
        width_ = max(x.width, y.width) + 1
        return Int(val_, width_)
       
    def spec(x: int, y: int) -> int:
        return x + y

    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Add")

def Sub(x, y) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = x.val - y.val
        width_ = max(x.width, y.width) + 1
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return x - y

    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Sub")

def Mul(x, y) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = x.val * y.val
        width_ = x.width + y.width
        return Int(val_, width_)

    def spec(x: int, y: int) -> int:
        return x * y

    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Mul")

def Max(x, y) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = max(x.val, y.val)
        
        if x.val > y.val:
            width_ = x.width
        elif x.val == y.val:
            width_ = max(x.width, y.width)
        else:
            width_ = y.width
            
        return Int(val_, width_)
        
    def spec(x: int, y: int) -> int:
        return max(x, y)
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Max")

def Min(x, y) -> Op:
    def impl(x: Int, y: Int) -> Int:
        val_ = min(x.val, y.val)
        
        if x.val < y.val:
            width_ = x.width
        elif x.val == y.val:
            width_ = max(x.width, y.width)
        else:
            width_ = y.width
            
        return Int(val_, width_)
    
    def spec(x: int, y: int) -> int:
        return min(x, y)
        
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Min")

def And(x, y) -> Op:
    def impl(a: Int, b: Int) -> Int:
        val_ = a.val & b.val
        width_ = max(a.width, b.width)
        return Int(val_, width_)

    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * ((a >> n) & 1) * ((b >> n) & 1)
                for n in range(0, max(1, m.bit_length()))])
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="And")

def Or(x, y) -> Op:
    def impl(a: Int, b: Int) -> Int:
        val_ = a.val | b.val
        width_ = max(a.width, b.width)
        return Int(val_, width_)

    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) + ((b >> n) & 1) - 
                 ((a >> n) & 1) * ((b >> n) & 1))
                    for n in range(0, max(1, m.bit_length()))])
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Or")

def Xor(x, y) -> Op:
    def impl(a: Int, b: Int) -> Int:
        val_ = a.val ^ b.val
        width_ = max(a.width, b.width)
        return Int(val_, width_)

    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) ^ ((b >> n) & 1))
                for n in range(0, max(1, m.bit_length()))])
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, y],
            name="Xor")

def Lshift(x, n) -> Op:
    def impl(x: Int, n: Int) -> Int:
        assert n.val >= 0, f"Shift amount should be non-negative, {n.val} is provided"
        val_ = x.val << n.val
        width_ = x.width + n.val
        return Int(val_, width_)

    def spec(x: int, n: int) -> int:
        return x * 2 ** n
    
    return Op(
            spec=spec,
            impl=impl,
            args=[x, n],
            name="Lshift")
            
def Rshift(x, n) -> Op:
    def impl(x: Int, n: Int) -> Int:
        assert n.val >= 0, f"Shift amount should be non-negative, {n.val} is provided"
        val_ = x.val >> n.val
        width_ = max(x.width - n.val, 1)
        return Int(val_, width_)

    # Right shift operates stricly over integers
    def spec(x: int, n: int) -> int:
        return int(x / 2 ** n)

    return Op(
            spec=spec,
            impl=impl,
            args=[x, n],
            name="Rshift")

