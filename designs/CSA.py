from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.Q import *
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.numtypes.Bool import *

from z3 import Real, Solver

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
    def spec(x, y, z, s):
        sum_ = Real('sum')
        carry = Real('carry')
        s.add(sum_ + carry == x + y + z)
        return tuple(sum_, carry)
    
    def sign(x: QT, y: QT, z: QT) -> TupleT:
        frac_bits = max(max(x.frac_bits, y.frac_bits), z.frac_bits)
        int_bits = max(max(x.int_bits, y.int_bits), z.int_bits)
        return TupleT(QT(int_bits, frac_bits), QT(int_bits + 1, frac_bits))
    
    def impl(x: Node, y: Node, z: Node) -> Node:
        sum_  = exact_xor(exact_xor(x, y), z)
        carry = exact_or(exact_or(exact_and(x, y), exact_and(x, z)), exact_and(y, z))
        one = Const(UQ.from_int(1))
        carry = q_sign_extend(carry, 1)
        carry = q_lshift(carry, one)
        
        carry.check(
            q_equal(
                q_add(q_add(x, y), z),
                q_add(sum_, carry),
            )
        )
        
        return make_Tuple(sum_, carry)
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[x, y, z],
        name="CSA")


def CSA_tree4(m0: Node, m1: Node, m2: Node, m3: Node) -> Composite:
    def spec(m0, m1, m2, m3, s):
        out = Real('out')
        s.add(out == m0 + m1 + m2 + m3)
        return out
    
    def sign(m0: QT, m1: QT, m2: QT, m3: QT) -> QT:
        frac_bits = max(max(m0.frac_bits, m1.frac_bits), max(m2.frac_bits, m3.frac_bits))
        int_bits = max(max(m0.int_bits, m1.int_bits), max(m2.int_bits, m3.int_bits)) + 3
        return QT(int_bits, frac_bits)
    
    def impl(m0: Node, m1: Node, m2: Node, m3: Node) -> Node:   
        s1, c1 = CSA(m0, m1, m2)
        
        ############# Asserts ##############
        s1.check(
            is_typeof(
                s1, 
                QT(
                    max(max(m0.node_type.int_bits, m1.node_type.int_bits), m2.node_type.int_bits),
                    max(max(m0.node_type.frac_bits, m1.node_type.frac_bits), m2.node_type.frac_bits)
                )
            )
        )
        c1.check(
            is_typeof(
                c1, 
                QT(
                    max(max(m0.node_type.int_bits, m1.node_type.int_bits), m2.node_type.int_bits) + 1,
                    max(max(m0.node_type.frac_bits, m1.node_type.frac_bits), m2.node_type.frac_bits)
                )
            )
        )
        ####################################
        
        s2, c2 = CSA(m3, s1, c1)
        
        ############# Asserts ##############
        s2.check(
            is_typeof(
                s2,
                QT(
                    max(c1.node_type.int_bits, m3.node_type.int_bits),
                    max(c1.node_type.frac_bits, m3.node_type.frac_bits),
                )
            )
        )
        c2.check(
            is_typeof(
                c2,
                QT(
                    max(c1.node_type.int_bits, m3.node_type.int_bits) + 1,
                    max(c1.node_type.frac_bits, m3.node_type.frac_bits),
                )
            )
        )
        ####################################
        
        impl = q_add(s2, c2)
        
        ############# Asserts ##############
        impl.check(
            is_typeof(
                impl,
                QT(c2.node_type.int_bits + 1, c2.node_type.frac_bits),
            )
        )
        impl.check(
            q_equal(
                impl,
                q_add(q_add(m0, m1), q_add(m2, m3)),
            )
        )
        ####################################
        
        return impl
    
    return Composite(spec=spec,
                     impl=impl,
                     sign=sign,
                     args=[m0, m1, m2, m3],
                     name="CSA_tree4")

if __name__ == '__main__':
    # Compile design
    args = [
        Var(name="a_0", sign=QT(3, 4)),
        Var(name="a_1", sign=QT(8, 3)),
        Var(name="a_2", sign=QT(5, 0)),
        Var(name="a_3", sign=QT(1, 5)),
    ]
    
    design = CSA_tree4(*args)
    design.print_tree(depth=1)


