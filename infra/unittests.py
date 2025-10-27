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
        for shared_bits in range(1, BF16_EXPONENT_BITS):
            for _ in range(1000):
                a, b = generate_BF16_2x4x1(shared_bits)
                fp_a = [S_E_M2float(x[0], x[1], x[2]) for x in a]
                fp_b = [S_E_M2float(x[0], x[1], x[2]) for x in b]
                
                overflow=False
                underflow=False
                
                unfused_res = unfused_dot_product(fp_a, fp_b)
                
                try:
                    conventional_res = conventional(a, b)
                except Exception as e:
                    if "Overflow" in str(e):
                        overflow=True
                    elif "Underflow" in str(e):
                        underflow=True
                try:
                    optimized_res = optimized(a, b)
                except Exception as e:
                    if "Overflow" in str(e) and overflow:
                        continue
                    elif "Underflow" in str(e) and underflow:
                        continue

                # They should be numerically close
                self.assertAlmostEqual(unfused_res, conventional_res, places=3)
                self.assertAlmostEqual(unfused_res, optimized_res, places=3)

if __name__ == "__main__":
    unittest.main()
