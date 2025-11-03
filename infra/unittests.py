import unittest
import random
import inspect
import importlib

from ..designs.optimized import Optimized
from ..designs.conventional import Conventional
from ..ast.AST import *
from ..ast.types import *
from ..utils.utils import *
from ..utils.basics import *

EPS = 1e-12  # to avoid divide-by-zero
ACCURACY_BITS = 6
ACC_TOL = 2 ** (-ACCURACY_BITS)

random.seed(0)


class TestFusedDotProduct(unittest.TestCase):
    def test_designs_difference(self):
        """Ensure the unfused, conventional and optimized dot products produce similar results."""
        conventional = Conventional()
        optimized = Optimized()
        
        for shared_bits in range(4, BF16_EXPONENT_BITS):
            for _ in range(100):
                a, b = generate_BF16_2x4x1(shared_bits)
                fp_a = [S_E_M2float(x[0], x[1], x[2]) for x in a]
                fp_b = [S_E_M2float(x[0], x[1], x[2]) for x in b]

                unfused_res = unfused_dot_product(fp_a, fp_b)

                # --- Conventional path
                try:
                    con_res_impl, con_res_spec = conventional(a, b)
                except Exception as e:
                    if "Overflow" in str(e) or "Underflow" in str(e):
                        continue
                    raise

                # --- Optimized path
                try:
                    opt_res_impl, opt_res_spec = optimized(a, b)
                except Exception as e:
                    if "Overflow" in str(e) or "Underflow" in str(e):
                        continue
                    raise

                # --- Relative error checks
                rel_err_conv = abs(unfused_res - con_res_impl) / max(
                    abs(unfused_res), EPS
                )
                rel_err_opt = abs(unfused_res - opt_res_impl) / max(
                    abs(unfused_res), EPS
                )

                msg_conv = (
                    f"unfused_res={unfused_res}, conventional_res={con_res_impl}, "
                    f"rel_err={rel_err_conv}"
                )
                msg_opt = (
                    f"unfused_res={unfused_res}, optimized_res={opt_res_impl}, "
                    f"rel_err={rel_err_opt}"
                )

                self.assertTrue(rel_err_conv < ACC_TOL, msg=msg_conv)
                self.assertTrue(rel_err_opt < ACC_TOL, msg=msg_opt)
   
    def test_basic_operators(self):
        """Check implementation and specification execution of basic functions."""
        # Dynamically import module
        basics = importlib.import_module("fused_dot_product.utils.basics")

        # Get all callables
        basic_operators = [
            func for name, func in inspect.getmembers(basics, inspect.isfunction)
        ]
        
        num_tests = 100
        for func in basic_operators:
            N_inputs = len(inspect.signature(func).parameters)
            with self.subTest(operator=func.__name__):
                for _ in range(num_tests):
                    args = []
                    for i in range(N_inputs):
                        args.append(Int(random.randint(0, 1000)))
                    op = func(*args)
                    
                    # Evaluate using spec and impl
                    spec_result = op.spec(*[x.val for x in args])
                    impl_result = op.impl(*args)
                    
                    self.assertEqual(
                        spec_result, impl_result.val,
                        msg=f"{func.__name__} failed for inputs {args}: "
                            f"spec={spec_result}, impl={impl_result}"
                    )


if __name__ == "__main__":
    unittest.main()
