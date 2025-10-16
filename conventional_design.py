from AST import CTree, Node
from utils import *
import math


class Conventional(CTree):
    def __init__(self):
        super().__init__()

        # Nodes for exponents
        self.exponents_adder = Node(spec=lambda x, y: x + y - (2**(BF16_EXPONENT_BITS-1) - 1), 
                                    impl=lambda x, y: x + y - BF16_BIAS)
        self.max_exp = Node(spec=lambda x: max(x), 
                            impl=lambda x: max(x))
        self.estimate_global_shift = Node(spec=lambda x, y: x - y, 
                                          impl=lambda x, y: x - y)
        
        # Nodes for mantissas
        self.mantissa2FXP = Node(spec=lambda m: FixedPoint(1.0 + m / (2 ** BF16_MANTISSA_BITS)),
                                 impl=bf16_mantissa_to_FXP,
                                 comp=float)
        self.mantissas_mul = Node(spec=lambda x, y: float(x) * float(y),
                                  impl=lambda x, y: x * y,
                                  comp=float)
        self.right_shift = Node(spec=lambda x, sh, Wf: float(x)/2**sh,
                                impl=RIGHT_SHIFT,
                                comp=float)
        self.calculate_sign = Node(spec=lambda x, y: 0 if x == y else 1,
                                   impl=lambda x, y: x ^ y)
        self.add_sign_to_FXP = Node(spec=lambda val, sign: val * (-1) ** sign,
                                    impl=FXP_ADD_SIGN,
                                    comp=float)
        self.adder_tree = Node(spec=sum,
                               impl=lambda ls: (ls[0] + ls[1]) + (ls[2] + ls[3]),
                               comp=float)
        
        # Converting back to float
        self.to_float = Node(spec=lambda m, e: float(m) * 2**(e - BF16_BIAS),
                             impl=FXP_E2float)

    def __call__(self, a, b):
        ########## EXPONENTS ###############
        # Step 1. Exponents add
        E_p = [self.exponents_adder(a[i][1], b[i][1]) for i in range(N)]

        # UNDERFLOW/OVERFLOW
        E_p = [EXP_OVERFLOW_UNDERFLOW_HANDLING(e) for e in E_p]

        # Step 2. Calculate maximum exponent
        E_m = self.max_exp(E_p)

        # Step 3. Calculate global shifts
        sh = [self.estimate_global_shift(E_m, E_p[i]) for i in range(N)]

        ########## MANTISSAS ###############
        # Step 1. Convert mantissas to FixedPoint
        M_a = [self.mantissa2FXP(x[2]) for x in a]
        M_b = [self.mantissa2FXP(x[2]) for x in b]

        # Step 2. Multiply mantissas using FixedPoint
        M_p = [self.mantissas_mul(x, y) for x, y in zip(M_a, M_b)]
        
        for m in M_p:
            assert m.n == 2 * BF16_MANTISSA_BITS and m.m == 2

        # Step 3. Shift mantissas
        M_p = [self.right_shift(x, shift, Wf) for x, shift in zip(M_p, sh)]
        
        for m in M_p:
            assert m.n == Wf - 2 and m.m == 2

        # Step 4. Adjust sign for mantissas using xor operation
        # As a result of adding a sign, integer bits of fixedpoint gets increased by 1 to avoid overflow during conversion
        S_p = [self.calculate_sign(x[0], y[0]) for x, y in zip(a, b)]
        M_p = [self.add_sign_to_FXP(x, s) for x, s in zip(M_p, S_p)]
        
        for m in M_p:
            assert m.n == Wf - 2
            assert m.m == 3

        ########## ADDER TREE ############## 
        
        fx_sum = self.adder_tree(M_p)

        # Unfortunately, we are off by 1 bits from the design with the sign logic
        assert fx_sum.n + fx_sum.m == Wf + math.ceil(math.log2(N)) + 1
    
        ########## RESULT ##################

        res = self.to_float(fx_sum, E_m)
        return res
