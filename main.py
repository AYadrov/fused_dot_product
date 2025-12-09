import argparse
import time
import random

from fused_dot_product.config import *
from fused_dot_product.designs.optimized import Optimized
from fused_dot_product.designs.conventional import Conventional
from fused_dot_product.numtypes.StaticTypes import *
from fused_dot_product.numtypes.RuntimeTypes import *
from fused_dot_product.ast.AST import *


def main():
    parser = argparse.ArgumentParser(description="Fused dot product, Kaul et al. (2019)")
    parser.add_argument("-s", "--seed", help="RANDOM SEED", default=int(time.time()), type=int)
    parser.add_argument("-sh", "--shared-exponent", help=f"shared exponent bits (less than {BFloat16.exponent_bits})", default=SHARED_EXPONENT_BITS, type=int)
    
    args = parser.parse_args()
    print(args)

    random.seed(args.seed)
    
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
    
    
    conv = Conventional(*a, *b)
    opt = Optimized(*a, *b)

    # Test the design
    random_gen, _ = BFloat16.random_generator(seed=args.seed, shared_exponent_bits=args.shared_exponent)
    for i in range(N):
        a[i].load_val(random_gen())
        b[i].load_val(random_gen())
    
    con_res_impl, con_res_spec = conv.evaluate()
    opt_res_impl, opt_res_spec = opt.evaluate()

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
    
    assert ulp_err_conv == 0, msg_conv
    assert ulp_err_opt == 0, msg_opt
    assert opt_res_spec == con_res_spec, msg_spec
    return 0

if __name__ == "__main__":
    main()
