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
            Var(name="a_0", signature=BFloat16T()),
            Var(name="a_1", signature=BFloat16T()),
            Var(name="a_2", signature=BFloat16T()),
            Var(name="a_3", signature=BFloat16T()),
        ]
        
        b = [
            Var(name="b_0", signature=BFloat16T()),
            Var(name="b_1", signature=BFloat16T()),
            Var(name="b_2", signature=BFloat16T()),
            Var(name="b_3", signature=BFloat16T()),
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

                con_res_impl, con_res_spec = conventional.evaluate()
                opt_res_impl, opt_res_spec = optimized.evaluate()

                # --- ULP error checks
                ulp_err_conv = ulp_distance(con_res_spec, con_res_impl.to_spec())
                ulp_err_opt = ulp_distance(opt_res_spec, opt_res_impl.to_spec())

                msg_conv = (
                    f"conventional spec={con_res_spec}, conventional impl={con_res_impl}, "
                    f"ulp_err={ulp_err_conv}"
                )
                msg_opt = (
                    f"optimized spec={opt_res_spec}, optimized impl={opt_res_impl}, "
                    f"ulp_err={ulp_err_opt}"
                )
                msg_spec = f"optimized spec={opt_res_spec}, conventional spec={con_res_spec}"
                
                self.assertTrue(ulp_err_conv == 0, msg=msg_conv)
                self.assertTrue(ulp_err_opt == 0, msg=msg_opt)
                self.assertTrue(opt_res_spec == con_res_spec, msg=msg_spec)
    
if __name__ == "__main__":
    unittest.main()
