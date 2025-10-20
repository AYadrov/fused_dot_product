from fused_dot_product.ast.AST import *

######### SPEC HELPERS #############
def bit_width(x):
    return max(1, x.bit_length())

######### BASIC OPERATORS ##########
def Add(x, y):
    return Operator(
            spec=lambda x, y: x + y,
            impl=lambda x, y: x + y,
            comp=lambda x: x,
            args=[x, y])

def Sub(x, y):
    return Operator(
            spec=lambda x, y: x - y,
            impl=lambda x, y: x - y,
            comp=lambda x: x,
            args=[x, y])

def Max(x, y):
    return Operator(
            spec=lambda x, y: x if x >= y else y,
            impl=max,
            comp=lambda x: x,
            args=[x, y])

def Min(x, y):
    return Operator(
            spec=lambda x, y: x if x < y else y,
            impl=min,
            comp=lambda x: x,
            args=[x,y])

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
    # makes sure than x >= y
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

