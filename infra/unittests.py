import unittest
import random
import inspect
import importlib
import tqdm

from ..designs.optimized import Optimized
from ..designs.conventional import Conventional
from ..ast.AST import *
from ..numtypes.numtypes import *
from ..utils.utils import ulp_distance

EPS = 1e-12  # to avoid divide-by-zero
ACCURACY_BITS = 6
ACC_TOL = 2 ** (-ACCURACY_BITS)

random.seed(0)


class TestFusedDotProduct(unittest.TestCase):
    def test_designs_difference(self):
        """Ensure the unfused, conventional and optimized dot products produce similar results."""
        # Compile design
        a = [Var("a_0"), Var("a_1"), Var("a_2"), Var("a_3")]
        b = [Var("b_0"), Var("b_1"), Var("b_2"), Var("b_3")]
        conventional = Conventional(*a, *b)
        optimized = Optimized(*a, *b)
        
        for shared_bits in range(5, BFloat16.exponent_bits+1):
            random_gen, exp_reshuffle = BFloat16.random_generator(seed=25, shared_exponent_bits=shared_bits)
            exp_reshuffle()
            for _ in tqdm.tqdm(range(100), desc=f"Testing designs with {shared_bits} bits of shared exponent"):
                for i in range(N):
                    a[i].load_val(random_gen())
                    b[i].load_val(random_gen())

                # --- Conventional path
                try:
                    con_res_impl, con_res_spec = conventional.evaluate()
                except Exception as e:
                    if "Overflow" in str(e) or "Underflow" in str(e):
                        continue
                    raise

                # --- Optimized path
                try:
                    opt_res_impl, opt_res_spec = optimized.evaluate()
                except Exception as e:
                    if "Overflow" in str(e) or "Underflow" in str(e):
                        continue
                    raise

                # --- Relative error checks
                rel_err_conv = abs(con_res_spec - con_res_impl.to_spec()) / max(
                    abs(con_res_spec), EPS
                )
                rel_err_opt = abs(opt_res_spec - opt_res_impl.to_spec()) / max(
                    abs(opt_res_spec), EPS
                )

                msg_conv = (
                    f"conventional spec={con_res_spec}, conventional impl={con_res_impl}, "
                    f"rel_err={rel_err_conv}"
                )
                msg_opt = (
                    f"optimized spec={opt_res_spec}, optimized impl={opt_res_impl}, "
                    f"rel_err={rel_err_opt}"
                )
                msg_spec = f"optimized spec={opt_res_spec}, conventional spec={con_res_spec}"
                self.assertTrue(rel_err_conv < ACC_TOL, msg=msg_conv)
                self.assertTrue(rel_err_opt < ACC_TOL, msg=msg_opt)
                self.assertTrue(opt_res_spec == con_res_spec, msg=msg_spec)
    
if __name__ == "__main__":
    unittest.main()
