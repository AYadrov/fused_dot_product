import unittest
import random
import inspect
import importlib
import argparse
import numpy as np

from designs.optimized import Optimized
from designs.conventional import Conventional
from fused_dot_product.ast.AST import *
from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.utils.utils import ulp_distance

DEFAULT_SEED = 0
DEFAULT_N_POINTS = 1000

def dot_product_spec(a_0, a_1, a_2, a_3, b_0, b_1, b_2, b_3):
        res = 0.0
        res += a_0.evaluate().to_spec() * b_0.evaluate().to_spec()
        res += a_1.evaluate().to_spec() * b_1.evaluate().to_spec()
        res += a_2.evaluate().to_spec() * b_2.evaluate().to_spec()
        res += a_3.evaluate().to_spec() * b_3.evaluate().to_spec()
        return float(np.float32(res))


class TestFusedDotProduct():
    def test_designs_difference_with_fp_spec(args):
        """Ensure the unfused, conventional and optimized dot products produce similar results."""
        SEED = args.seed
        N_POINTS = args.num_points
        
        print("Running test_designs_difference_with_fp_spec:")
        print("\tFuzzing conventional and optimized fused dot-product designs to detect deviations from the floating-point spec.")
        print(f"\tUsing random seed: {SEED}") 
        print("\tFloating-point spec (applies to both designs):")
        print("\t\tdef spec(BF16 a_0, BF16 a_1, BF16 a_2, BF16 a_3,\n\t\t\t BF16 b_0, BF16 b_1, BF16 b_2, BF16 b_3) -> FP64:")
        print("\t\t\tFP64 out  = FP64(a_0) * FP64(b_0)")
        print("\t\t\tFP64 out += FP64(a_1) * FP64(b_1)")
        print("\t\t\tFP64 out += FP64(a_2) * FP64(b_2)")
        print("\t\t\tFP64 out += FP64(a_3) * FP64(b_3)")
        print("\t\t\tFP64 out  = FP64(FP32(out))  // truncate to FP32, then cast back to FP64 (casting is exact)")
        print("\t\t\treturn out")
        print("\n\t\tNotes: Inputs (a_0...3, b_0...3) are generated in BF16 (8 exponent bits, 7 mantissa bits, 1 sign bit)")
        print("\t\t       and then cast to double precision; casting to FP64 is exact.")
        print("\t\t       The reference spec is evaluated in double precision because Python only supports this FP representation.")
        print("\t\t       A deviation is any FP64 ULP difference between the two designs.\n")
        
        # Compile designs
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
            random_gen, exp_reshuffle = BFloat16.random_generator(seed=SEED, shared_exponent_bits=shared_bits)
            print(f"\tRunning {N_POINTS} random points with {shared_bits} shared leading exponent bits for each generated input.")
            for _ in range(N_POINTS):
                exp_reshuffle()
                for i in range(N):
                    a[i].load_val(random_gen())
                    b[i].load_val(random_gen())
                
                con_res = conventional.evaluate().to_spec()
                opt_res = optimized.evaluate().to_spec()
                spec_res = dot_product_spec(*a, *b)
                msg = f"optimized impl={opt_res}, conventional impl={con_res}, double-precision spec={spec_res}"
                assert ulp_distance(opt_res, con_res) == 0 and ulp_distance(opt_res, spec_res) == 0, msg
                
        print("\tNo difference has been found, both designs match spec")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Unittests for fused dot product desings")
    parser.add_argument("-s", "--seed", help="Random seed", default=DEFAULT_SEED, type=int)
    parser.add_argument("-pt", "--num-points", help=f"Number of points to run per shared exponent", default=DEFAULT_N_POINTS, type=int)
    
    args = parser.parse_args()
    
    TestFusedDotProduct.test_designs_difference_with_fp_spec(args)
    
    
