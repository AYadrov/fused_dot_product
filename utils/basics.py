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
            args=[x, y])

def Sub(x, y):
    return Operator(
            spec=lambda a, b: a - b,
            impl=lambda a, b: a - b,
            comp=lambda a: a,
            args=[x, y])

def Max(x, y):
    return Operator(
            spec=lambda a, b: a if a >= b else b,
            impl=max,
            comp=lambda a: a,
            args=[x, y])

def Min(x, y):
    return Operator(
            spec=lambda a, b: a if a < b else b,
            impl=min,
            comp=lambda a: a,
            args=[x, y])

def And(x, y):
    def spec(a, b):
        m = max(a, b)
        return sum([(1 << n) * ((a >> n) & 1) * ((b >> n) & 1)
                for n in range(0, bit_width(m))])
    
    return Operator(
            spec=spec,
            impl=lambda a, b: a & b,
            comp=int,
            args=[x, y])

def Or(x, y):
    def spec(a, b):
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) + ((b >> n) & 1) - 
                 ((a >> n) & 1) * ((b >> n) & 1))
                    for n in range(0, bit_width(m))])

    return Operator(
            spec=spec,
            impl=lambda a, b: a | b,
            comp=int,
            args=[x, y])

def Xor(x: int, y: int):
    def spec(a, b):
        m = max(a, b)
        return sum([(1 << n) * (((a >> n) & 1) ^ ((b >> n) & 1))
                for n in range(0, bit_width(m))])
 
    return Operator(
            spec=spec,
            impl=lambda a, b: a ^ b,
            comp=int,
            args=[x, y])

# Some basic tests
# Checks whether spec evaluation and impl evaluation results are equal
if __name__ == '__main__':
    from random import randint
    num_tests = 1000
   
    basic_operations = [Xor, Or, And, Min, Max, Sub, Add]
    for f in basic_operations:
        for i in range(num_tests):
            f(randint(0, 10000), randint(0, 10000)).evaluate()
