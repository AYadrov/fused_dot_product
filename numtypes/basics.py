from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.utils.utils import *
from fused_dot_product.ast.AST import *


def basic_adder(x: Node, y: Node) -> Op:
    def spec(x, y):
        return x + y
    
    def sign(x: StaticType, y: StaticType) -> StaticType:
        assert x == y, "input static types mismatch"
        return x
    
    def impl(x: RuntimeType, y: RuntimeType) -> RuntimeType:
        assert x.static_type() == y.static_type(), "input runtime types mismatch"
        val = x.val + y.val
        val = mask(val, x.total_bits())
        return x.copy(val=val)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="basic_adder")


def basic_subtracter(x: Node, y: Node) -> Op:
    def spec(x, y):
        return x - y
    
    def sign(x: StaticType, y: StaticType) -> StaticType:
        assert x == y, f"input static types mismatch"
        return x
    
    def impl(x: RuntimeType, y: RuntimeType) -> RuntimeType:
        assert x.static_type() == y.static_type(), "input runtime types mismatch"
        val = x.val - y.val
        val = mask(val, x.total_bits())
        return x.copy(val=val)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="basic_subtracter")


def basic_maxer(x: Node, y: Node) -> Op:
    def spec(x, y):
        return max(x, y)
    
    def sign(x: StaticType, y: StaticType) -> StaticType:
        assert x == y, "input static types mismatch"
        return x
    
    def impl(x: RuntimeType, y: RuntimeType) -> RuntimeType:
        assert x.static_type() == y.static_type(), "input runtime types mismatch"
        val = max(x.val, y.val)
        val = mask(val, x.total_bits())
        return x.copy(val=val)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="basic_maxer")


def basic_miner(x: Node, y: Node) -> Op:
    def spec(x, y):
        return min(x, y)
    
    def sign(x: StaticType, y: StaticType) -> StaticType:
        assert x == y, "input static types mismatch"
        return x
    
    def impl(x: RuntimeType, y: RuntimeType) -> RuntimeType:
        assert x.static_type() == y.static_type(), "input runtime types mismatch"
        val = min(x.val, y.val)
        val = mask(val, x.total_bits())
        return x.copy(val=val)
    
    return Op(
        spec=spec,
        impl=impl,
        signature=sign,
        args=[x, y],
        name="basic_miner")


