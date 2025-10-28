import unittest
import random
import inspect
import importlib

from ..designs.optimized import Optimized
from ..designs.conventional import Conventional
from ..ast.AST import *
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
        
        for shared_bits in range(5, BF16_EXPONENT_BITS):
            for _ in range(100):
                a, b = generate_BF16_2x4x1(shared_bits)
                fp_a = [S_E_M2float(x[0], x[1], x[2]) for x in a]
                fp_b = [S_E_M2float(x[0], x[1], x[2]) for x in b]

                unfused_res = unfused_dot_product(fp_a, fp_b)

                # --- Conventional path
                try:
                    conventional_res = conventional(a, b)
                except Exception as e:
                    if "Overflow" in str(e) or "Underflow" in str(e):
                        continue
                    raise

                # --- Optimized path
                try:
                    optimized_res = optimized(a, b)
                except Exception as e:
                    if "Overflow" in str(e) or "Underflow" in str(e):
                        continue
                    raise

                # --- Relative error checks
                rel_err_conv = abs(unfused_res - conventional_res) / max(
                    abs(unfused_res), EPS
                )
                rel_err_opt = abs(unfused_res - optimized_res) / max(
                    abs(unfused_res), EPS
                )

                msg_conv = (
                    f"unfused_res={unfused_res}, conventional_res={conventional_res}, "
                    f"rel_err={rel_err_conv}"
                )
                msg_opt = (
                    f"unfused_res={unfused_res}, optimized_res={optimized_res}, "
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
            with self.subTest(operator=func.__name__):
                for _ in range(num_tests):
                    a, b = random.randint(0, 1000), random.randint(0, 1000)
                    op = func(a,b)
                    # print(op)
                    # print(op(a, b))
                    # print(op(a,b).spec(a,b))
                    
                    # Evaluate using spec and impl
                    spec_result = op.spec(a,b)
                    impl_result = op.impl(a,b)
                    
                    # Comparison through comparison function
                    comp_spec = op.comp(spec_result)
                    comp_impl = op.comp(impl_result)
                    
                    self.assertEqual(
                        comp_spec, comp_impl,
                        msg=f"{func.__name__} failed for inputs {a}, {b}: "
                            f"spec={comp_spec}, impl={comp_impl}"
                    )

                
if __name__ == "__main__":
    unittest.main()
