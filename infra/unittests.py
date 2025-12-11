import unittest
import random
import inspect
import importlib
import tqdm

from ..designs.optimized import Optimized
from ..designs.conventional import Conventional
from ..ast.AST import *
from ..numtypes.RuntimeTypes import *
from ..utils.utils import ulp_distance

random.seed(0)


class TestFusedDotProduct(unittest.TestCase):
    def test_designs_difference(self):
        """Ensure the unfused, conventional and optimized dot products produce similar results."""
        # Compile design
        a = [
            Var(name="a_0", sign=BFloat16T()),
            Var(name="a_1", sign=BFloat16T()),
            Var(name="a_2", sign=BFloat16T()),
            Var(name="a_3", sign=BFloat16T()),
        ]
        
        b = [
            Var(name="b_0", sign=BFloat16T()),
            Var(name="b_1", sign=BFloat16T()),
            Var(name="b_2", sign=BFloat16T()),
            Var(name="b_3", sign=BFloat16T()),
        ]
    
        conventional = Conventional(*a, *b)
        optimized = Optimized(*a, *b)
        
        for shared_bits in range(5, BFloat16.exponent_bits+1):
            random_gen, exp_reshuffle = BFloat16.random_generator(seed=25, shared_exponent_bits=shared_bits)
            for _ in tqdm.tqdm(range(1000), desc=f"Testing designs with {shared_bits} bits of shared exponent"):
                exp_reshuffle()
                for i in range(N):
                    a[i].load_val(random_gen())
                    b[i].load_val(random_gen())

                con_res = conventional.evaluate()
                opt_res = optimized.evaluate()
                msg = f"optimized impl={opt_res}, conventional impl={con_res}"
                self.assertTrue(opt_res == con_res, msg=msg)
    
if __name__ == "__main__":
    unittest.main()
