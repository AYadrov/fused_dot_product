import unittest
import random
import time
import argparse


from ..designs.optimized import Optimized
from ..designs.conventional import Conventional
from ..utils.utils import *



class TestFusedDotProduct(unittest.TestCase):
    def test_designs_difference(self):
        """Ensure the unfused, conventional and optimized dot products produce similar results."""
        random.seed(0)
        conventional = Conventional()
        optimized = Optimized()

        EPS = 1e-12  # to avoid divide-by-zero
        ACCURACY_BITS = 6
        ACC_TOL = 2 ** (-ACCURACY_BITS)
        for shared_bits in range(5, BF16_EXPONENT_BITS):
            for _ in range(1000):
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
                
if __name__ == "__main__":
    unittest.main()
