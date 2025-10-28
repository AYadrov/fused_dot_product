# File defines basic operators for floating-point evaluations

from fused_dot_product.ast.AST import *

######### BASIC OPERATORS ##########
def Add(x, y) -> Operator:
    return Operator(
            spec=lambda a, b: a + b,
            impl=lambda a, b: a + b,
            comp=lambda a: a,
            args=[x, y],
            name="Add")

def Sub(x, y) -> Operator:
    return Operator(
            spec=lambda a, b: a - b,
            impl=lambda a, b: a - b,
            comp=lambda a: a,
            args=[x, y],
            name="Sub")   

def Mul(x, y) -> Operator:
    return Operator(
            spec=lambda a, b: a * b,
            impl=lambda a, b: a * b,
            comp=lambda a: a,
            args=[x, y],
            name="Mul")

def Max(x, y) -> Operator:
    return Operator(
            spec=lambda a, b: a if a >= b else b,
            impl=lambda a, b: max(a, b),
            comp=lambda a: a,
            args=[x, y],
            name="Max")

def Min(x, y) -> Operator:
    return Operator(
            spec=lambda a, b: a if a < b else b,
            impl=lambda a, b: min(a, b),
            comp=lambda a: a,
            args=[x, y],
            name="Min")

def And(x, y) -> Operator:
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * ((a >> n) & 1) * ((b >> n) & 1)
                for n in range(0, max(1, m.bit_length()))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a & b,
            comp=lambda x: int(x),
            args=[x, y],
            name="And")

def Or(x, y) -> Operator:
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) + ((b >> n) & 1) - 
                 ((a >> n) & 1) * ((b >> n) & 1))
                    for n in range(0, max(1, m.bit_length()))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a | b,
            comp=lambda x: int(x),
            args=[x, y],
            name="Or")

def Xor(x, y) -> Operator:
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) ^ ((b >> n) & 1))
                for n in range(0, max(1, m.bit_length()))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a ^ b,
            comp=lambda x: int(x),
            args=[x, y],
            name="Xor")

def Lshift(x, n) -> Operator:
    def spec(x: int, n: int) -> int:
        return x * 2 ** n
    return Operator(
            spec=spec,
            impl=lambda x, n: x << n,
            comp=lambda x: int(x),
            args=[x, n],
            name="Lshift")
            
def Rshift(x, n) -> Operator:
    # Right shift operates stricly over integers
    def spec(x: int, n: int) -> int:
        return int(x / 2 ** n)
    return Operator(
            spec=spec,
            impl=lambda x, n: x >> n,
            comp=lambda x: int(x),
            args=[x, n],
            name="Rshift")
