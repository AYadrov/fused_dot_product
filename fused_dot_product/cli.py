import argparse
import random
import time

from fused_dot_product import *
from examples.conventional import Conventional
from examples.optimized import Optimized


def main(argv=None):
    parser = argparse.ArgumentParser(description="Fused dot product, Kaul et al. (2019)")
    parser.add_argument(
        "-s",
        "--seed",
        help="RANDOM SEED",
        default=int(time.time()),
        type=int,
    )
    parser.add_argument(
        "-sh",
        "--shared-exponent",
        help=f"shared exponent bits (less than {BFloat16.exponent_bits})",
        default=SHARED_EXPONENT_BITS,
        type=int,
    )

    args = parser.parse_args(argv)
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
    random_gen, _ = BFloat16.random_generator(
        seed=args.seed,
        shared_exponent_bits=args.shared_exponent,
    )
    for i in range(N):
        a[i].load_val(random_gen())
        b[i].load_val(random_gen())

    con_res = conv.evaluate()
    opt_res = opt.evaluate()

    msg = f"optimized impl={opt_res}, conventional impl={con_res}"
    assert opt_res == con_res, msg
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
