import argparse
import time
import random

from fused_dot_product.config import *
from fused_dot_product.designs.optimized import Optimized
from fused_dot_product.designs.conventional import Conventional
from fused_dot_product.numtypes.numtypes import *
from fused_dot_product.ast.AST import *


def main():
    parser = argparse.ArgumentParser(description="Fused dot product, Kaul et al. (2019)")
    parser.add_argument("-s", "--seed", help="RANDOM SEED", default=int(time.time()), type=int)
    parser.add_argument("-v", "--verbose", help="0 (no verbose) or 1 (yes verbose)", default=0)
    parser.add_argument("-sh", "--shared-exponent", help=f"shared exponent bits (less than {BFloat16.exponent_bits})", default=SHARED_EXPONENT_BITS, type=int)
    
    args = parser.parse_args()
    print(args)

    random.seed(args.seed)
    
    # Compile designs
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
    
    
    conv = Conventional(*a, *b)
    opt = Optimized(*a, *b)

    # Test the design
    random_gen, _ = BFloat16.random_generator(seed=args.seed, shared_exponent_bits=args.shared_exponent)
    for i in range(N):
        a[i].load_val(random_gen())
        b[i].load_val(random_gen())
    
    if args.verbose:
        print("x =", a)
        print("y =", b)
    
    conv_res_impl, conv_res_spec = conv.evaluate()
    opt_res_impl, opt_res_spec = opt.evaluate()

    print("Result of conventional fused dot-product:")
    print("\tImpl:", conv_res_impl)
    print("\tSpec:", conv_res_spec)
    
    print("Result of optimized fused dot-product:")
    print("\tImpl:", opt_res_impl)
    print("\tSpec:", opt_res_spec)
    
    print("Absolute difference between optimized/conventional:\n\t", abs(conv_res_impl.to_spec() - opt_res_impl.to_spec()))
    return 0

if __name__ == "__main__":
    main()
