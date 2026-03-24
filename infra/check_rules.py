import argparse
from pprint import pprint

from fused_dot_product.egglog.rules import check_rules


def main() -> None:
    parser = argparse.ArgumentParser(description="Validate algebraic rules with Z3")
    parser.add_argument(
        "--timeout-ms",
        type=int,
        default=10000,
        help="Z3 timeout per rule in milliseconds",
    )
    args = parser.parse_args()

    res = check_rules(z3_timeout_ms=args.timeout_ms)
    pprint(res)


if __name__ == "__main__":
    main()
