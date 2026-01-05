from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.numtypes.RuntimeTypes import *


############## HELPERS #################
def exact_xor(a: Node, b: Node):
    a_, b_ = q_aligner(
        x=a,
        y=b,
        int_aggr=lambda x, y: max(x, y),
        frac_aggr=lambda x, y: max(x, y),
    )
    return basic_xor(
        x=a_,
        y=b_,
        out=a_.copy(),
    )

def exact_and(a: Node, b: Node):
    a_, b_ = q_aligner(
        x=a,
        y=b,
        int_aggr=lambda x, y: max(x, y),
        frac_aggr=lambda x, y: max(x, y),
    )
    return basic_and(
        x=a_,
        y=b_,
        out=a_.copy(),
    )

def exact_or(a: Node, b: Node):
    a_, b_ = q_aligner(
        x=a,
        y=b,
        int_aggr=lambda x, y: max(x, y),
        frac_aggr=lambda x, y: max(x, y),
    )
    return basic_or(
        x=a_,
        y=b_,
        out=a_.copy(),
    )

############## DESIGN ##################
# It is important to call CSA only on fixed points with equal lengths!
# This is due to signed fixed points that we use
# A lose of sign can happen if the lengths of inputs to CSA are not equal
def CSA(x: Node, y: Node, z: Node) -> Primitive:
    def spec(x: float, y: float, z: float, out: tuple) -> bool:
        return x + y + z == out[0] + out[1]
    
    def sign(x: QT, y: QT, z: QT) -> TupleT:
        frac_bits = max(max(x.frac_bits, y.frac_bits), z.frac_bits)
        int_bits = max(max(x.int_bits, y.int_bits), z.int_bits)
        return TupleT(QT(int_bits, frac_bits), QT(int_bits + 1, frac_bits))
    
    def impl(x: Node, y: Node, z: Node) -> Node:
        sum_  = exact_xor(exact_xor(x, y), z)
        carry = exact_or(exact_or(exact_and(x, y), exact_and(x, z)), exact_and(y, z))
        one = Const(UQ.from_int(1))
        carry = q_sign_extend(carry, 1)
        return make_Tuple(sum_, q_lshift(carry, one))
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y, z],
        name="CSA")


def CSA_tree4(m0: Node, m1: Node, m2: Node, m3: Node) -> Composite:
    def spec(m0: float, m1: float, m2: float, m3: float, out: float) -> float:
        return m0 + m1 + m2 + m3 == out
    
    def sign(m0: QT, m1: QT, m2: QT, m3: QT) -> QT:
        frac_bits = max(max(m0.frac_bits, m1.frac_bits), max(m2.frac_bits, m3.frac_bits))
        int_bits = max(max(m0.int_bits, m1.int_bits), max(m2.int_bits, m3.int_bits)) + 3
        return QT(int_bits, frac_bits)
    
    def impl(m0: Node, m1: Node, m2: Node, m3: Node) -> Node:   
        s1, c1 = CSA(m0, m1, m2)
        s2, c2 = CSA(m3, s1, c1)
        impl = q_add(s2, c2)
        return impl
    
    return Composite(spec=spec,
                     impl=impl,
                     sign=sign,
                     args=[m0, m1, m2, m3],
                     name="CSA_tree4")

