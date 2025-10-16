import argparse
import time
import random

from config import *
from utils import unfused_dot_product, generate_BF16_1x4, S_E_M2float
from optimized import optimized_dot_product
from conventional import conventional_dot_product
from conventional_design import Conventional

def main():
    parser = argparse.ArgumentParser(description="Fused dot product, Kaul et al. (2019)")
    parser.add_argument("-s", "--seed", help="RANDOM SEED", default=int(time.time()))
    parser.add_argument("-v", "--verbose", help="0 (no verbose) or 1 (yes verbose)", default=0)
    parser.add_argument("-sh", "--shared-exponent", help=f"shared exponent bits (less than {BF16_EXPONENT_BITS})", default=SHARED_EXPONENT_BITS, type=int)
    
    args = parser.parse_args()
    print(args)

    ######### GENERATING DATA ##########
    
    random.seed(args.seed)
    a = generate_BF16_1x4(args.shared_exponent)
    b = generate_BF16_1x4(args.shared_exponent) 

    ########### GROUND TRUTH ###########
    
    # Unfused dot-product
    fp_a = [S_E_M2float(x[0], x[1], x[2]) for x in a]
    fp_b = [S_E_M2float(x[0], x[1], x[2]) for x in b]
    unfused_res = unfused_dot_product(fp_a, fp_b)

    if args.verbose:
        print("x =", fp_a)
        print("y =", fp_b)

    ########## CONV+OPTIMIZED ##########

    print("Unfused result of dot-product:\n\t", unfused_res)

    conventional_res = conventional_dot_product(a, b)
    print("Absolute difference between conventional/unfused:\n\t", abs(unfused_res-conventional_res))

    conventional_res2 = Conventional()(a,b)
    print("Absolute difference between conventional/unfused 2:\n\t", abs(unfused_res-conventional_res2))
 
    optimized_res = optimized_dot_product(a, b)
    print("Absolute difference between optimized/unfused:\n\t", abs(unfused_res-optimized_res))
    return 0
  
if __name__ == "__main__":
    main()
