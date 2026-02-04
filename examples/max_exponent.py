from fused_dot_product import *
from cvc5.pythonic import FreshReal, If

def OPTIMIZED_MAX_EXP4(e0: Node,
                       e1: Node,
                       e2: Node,
                       e3: Node) -> Primitive:
    def spec(e0, e1, e2, e3, s):
        out = FreshReal('out')
        res1 = If(e0 >= e1, e0, e1)
        res2 = If(e2 >= e3, e2, e3)
        res3 = If(res1 >= res2, res1, res2)
        s.add(out == res3)
        return out
    
    def sign(e0: UQT, e1: UQT, e2: UQT, e3: UQT) -> UQT:
        int_bits = max(max(e0.int_bits, e1.int_bits), max(e2.int_bits, e3.int_bits))
        frac_bits = max(max(e0.frac_bits, e1.frac_bits), max(e2.frac_bits, e3.frac_bits))
        assert frac_bits == 0, "Not expected fractional bits"
        return UQT(int_bits, frac_bits)
    
    def impl(e0: Node, e1: Node, e2: Node, e3: Node) -> Node:
        def bit_not(x: Node) -> Node:
            return basic_invert(x=x, out=x.copy())
        
        def bit_and(x: Node, y: Node) -> Node:
            return basic_and(x=x, y=y, out=x.copy())
        
        def bit_or(x: Node, y: Node) -> Node:
            return basic_or(x=x, y=y, out=x.copy())
        
        def or_tree(bits: list[Node]) -> Node:
            acc = bits[0]
            for b in bits[1:]:
                acc = bit_or(acc, b)
            return acc
        
        def concat(high: Node, low: Node) -> Node:
            int_bits = uq_add(uq_int_bits(high), uq_int_bits(low))
            out = uq_alloc(int_bits, Const(UQ.from_int(0)))
            return basic_concat(x=high, y=low, out=out)
        
        inputs = [e0, e1, e2, e3]
        
        # That's a bad move, it steps away from AST to pure integers
        int_bits = max(x.node_type.int_bits for x in inputs)
        frac_bits = max(x.node_type.frac_bits for x in inputs)
        bit_width = int_bits + frac_bits
        
        zero_bit = Const(UQ(0, 1, 0))
        
        ep_bits = []
        for exp in inputs:
            bits = [zero_bit]
            for pos in range(bit_width-1, -1, -1):
                bits.append(uq_select(exp, pos, pos))
            ep_bits.append(bits)
        
        smaller = [[zero_bit] for _ in range(len(inputs))]
        maxexp = [zero_bit]
        
        for i in range(1, bit_width+1):
            data_for_or = []
            max_prev = maxexp[i-1]
            for j in range(len(inputs)):
                prev_bit = ep_bits[j][i-1]
                curr_bit = ep_bits[j][i]
                prev_is_smaller = smaller[j][i-1]
                
                curr_is_smaller = bit_or(bit_and(max_prev, bit_not(prev_bit)), prev_is_smaller)
                res = bit_not(curr_is_smaller)
                
                smaller[j].append(curr_is_smaller)
                
                candidate = bit_and(curr_bit, res)
                data_for_or.append(candidate)
            
            maxexp.append(or_tree(data_for_or))
        
        bits = maxexp[1:]  # drop the leading 0, keep MSB→LSB
        out = bits[0]
        for b in bits[1:]:
            out = concat(out, b)
        return out
    
    return Primitive(
        spec=spec,
        impl=impl,
        sign=sign,
        args=[e0, e1, e2, e3],
        name="OPTIMIZED_MAX_EXP4"
    )

if __name__ == '__main__':
    inputs = [Var(f"arg_{i}", sign=UQT(7,0)) for i in range(4)]
    design = OPTIMIZED_MAX_EXP4(*inputs)
    design.print_tree(depth=1)
    
