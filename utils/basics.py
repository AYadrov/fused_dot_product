# File defines basic operators for floating-point evaluations

from fused_dot_product.ast.AST import *

######### SPEC HELPERS #############
def bit_width(x):
    return max(1, x.bit_length())

######### BASIC OPERATORS ##########
def Add(x, y):
    return Operator(
            spec=lambda a, b: a + b,
            impl=lambda a, b: a + b,
            comp=lambda a: a,
            args=[x, y],
            name="Add")

def Sub(x, y):
    return Operator(
            spec=lambda a, b: a - b,
            impl=lambda a, b: a - b,
            comp=lambda a: a,
            args=[x, y],
            name="Sub")

def Max(x, y):
    return Operator(
            spec=lambda a, b: a if a >= b else b,
            impl=max,
            comp=lambda a: a,
            args=[x, y],
            name="Max")

def Min(x, y):
    return Operator(
            spec=lambda a, b: a if a < b else b,
            impl=min,
            comp=lambda a: a,
            args=[x, y],
            name="Min")

def And(x, y):
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * ((a >> n) & 1) * ((b >> n) & 1)
                for n in range(0, bit_width(m))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a & b,
            comp=int,
            args=[x, y],
            name="And")

def Or(x, y):
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) + ((b >> n) & 1) - 
                 ((a >> n) & 1) * ((b >> n) & 1))
                    for n in range(0, bit_width(m))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a | b,
            comp=int,
            args=[x, y],
            name="Or")

def Xor(x, y):
    def spec(a: int, b: int) -> int:
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) ^ ((b >> n) & 1))
                for n in range(0, bit_width(m))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a ^ b,
            comp=int,
            args=[x, y],
            name="Xor")
            
def Lshift(x, n):
    def spec(x: int, n: int) -> int:
        return x * 2 ** n
    return Operator(
            spec=spec,
            impl=lambda x, n: x << n,
            comp=int,
            args=[x, n],
            name="Lshift")

# Some basic tests
# Checks whether spec evaluation and impl evaluation results are equal
if __name__ == '__main__':
    from random import randint
    num_tests = 1000
    
    basic_operations = [Xor, Or, And, Min, Max, Sub, Add, Lshift]
    for f in basic_operations:
        for i in range(num_tests):
            f(randint(0, 10000), randint(0, 10000)).evaluate()
