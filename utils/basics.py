# File defines basic operators for floating-point evaluations

from fused_dot_product.ast.AST import *

######### BASIC OPERATORS ##########
def Add(x, y) -> Op:
    return Op(
            spec=lambda a, b: a + b,
            impl=lambda a, b: a + b,
            args=[x, y],
            name="Add")

def Sub(x, y) -> Op:
    return Op(
            spec=lambda a, b: a - b,
            impl=lambda a, b: a - b,
            args=[x, y],
            name="Sub")   

def Mul(x, y) -> Op:
    return Op(
            spec=lambda a, b: a * b,
            impl=lambda a, b: a * b,
            args=[x, y],
            name="Mul")

def Max(x, y) -> Op:
    return Op(
            spec=lambda a, b: a if a >= b else b,
            impl=lambda a, b: max(a, b),
            args=[x, y],
            name="Max")

def Min(x, y) -> Op:
    return Op(
            spec=lambda a, b: a if a < b else b,
            impl=lambda a, b: min(a, b),
            args=[x, y],
            name="Min")

def And(x, y) -> Op:
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * ((a >> n) & 1) * ((b >> n) & 1)
                for n in range(0, max(1, m.bit_length()))])
    
    return Op(
            spec=spec,
            impl=lambda a, b: a & b,
            args=[x, y],
            name="And")

def Or(x, y) -> Op:
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) + ((b >> n) & 1) - 
                 ((a >> n) & 1) * ((b >> n) & 1))
                    for n in range(0, max(1, m.bit_length()))])
    
    return Op(
            spec=spec,
            impl=lambda a, b: a | b,
            args=[x, y],
            name="Or")

def Xor(x, y) -> Op:
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) ^ ((b >> n) & 1))
                for n in range(0, max(1, m.bit_length()))])
    
    return Op(
            spec=spec,
            impl=lambda a, b: a ^ b,
            args=[x, y],
            name="Xor")

def Lshift(x, n) -> Op:
    def spec(x: int, n: int) -> int:
        return x * 2 ** n
    return Op(
            spec=spec,
            impl=lambda x, n: x << n,
            args=[x, n],
            name="Lshift")
            
def Rshift(x, n) -> Op:
    # Right shift operates stricly over integers
    def spec(x: int, n: int) -> int:
        return int(x / 2 ** n)
    return Op(
            spec=spec,
            impl=lambda x, n: x >> n,
            args=[x, n],
            name="Rshift")
