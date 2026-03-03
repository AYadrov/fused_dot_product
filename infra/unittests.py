import random
import argparse
import time
import unittest
import json
import sys
import numpy as np
from pprint import pprint, pformat
from pathlib import Path

from fused_dot_product import *
from examples.optimized import Optimized
from examples.conventional import Conventional
from examples.CSA import CSA_tree4

DEFAULT_SEED = 0
DEFAULT_N_POINTS = 1000

def dot_product_spec(a_0, a_1, a_2, a_3, b_0, b_1, b_2, b_3):
        res = 0.0
        res += a_0.evaluate().to_val() * b_0.evaluate().to_val()
        res += a_1.evaluate().to_val() * b_1.evaluate().to_val()
        res += a_2.evaluate().to_val() * b_2.evaluate().to_val()
        res += a_3.evaluate().to_val() * b_3.evaluate().to_val()
        return float(np.float32(res))

def run_spec_with_metrics(design: Node):
    return design.check_spec()

def merge_spec_reports(reports: list[dict]):
    merged_rule_application_counts = {}
    
    runtime_s_by_design = {}
    equivalent_by_design = {}
    
    total_runtime_s = 0.0
    all_equivalent = True
    
    for report in reports:
        design_name = report['name']
        runtime_s = float(report.get("runtime_s", 0.0))
        equivalent = bool(report.get("equivalent", False))
        
        runtime_s_by_design[design_name] = runtime_s
        equivalent_by_design[design_name] = equivalent
        total_runtime_s += runtime_s
        all_equivalent = all_equivalent and equivalent
        
        for rule, count in report.get("rule_application_counts", {}).items():
            merged_rule_application_counts[rule] = (
                merged_rule_application_counts.get(rule, 0) + int(count)
            )
    
    return {
        "equivalent": all_equivalent,
        "runtime_s_total": total_runtime_s,
        "runtime_s_by_design": runtime_s_by_design,
        "equivalent_by_design": equivalent_by_design,
        "rule_application_counts": dict(sorted(merged_rule_application_counts.items())),
    }


class TestFusedDotProduct(unittest.TestCase):
    SEED = DEFAULT_SEED
    N_POINTS = DEFAULT_N_POINTS
    SPEC_REPORT = None
    IMPL_REPORT = None

    def test_run_spec_verification_and_timing(self):
        print("\nRunning test_run_spec_verification_and_timing:")
        print("\tConstructing CSA_tree4, Conventional, and Optimized composites.")
        print("\tRunning run_spec() for each design and reporting verification runtime.\n")
        
        csa_args = [
            Var(name="csa_0", sign=QT(3, 4)),
            Var(name="csa_1", sign=QT(8, 3)),
            Var(name="csa_2", sign=QT(5, 0)),
            Var(name="csa_3", sign=QT(1, 5)),
        ]
        csa_tree4 = CSA_tree4(*csa_args)
        
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
        
        report1 = run_spec_with_metrics(csa_tree4)
        report2 = run_spec_with_metrics(conventional)
        report3 = run_spec_with_metrics(optimized)
        
        overall_report = merge_spec_reports([report1, report2, report3])
        TestFusedDotProduct.SPEC_REPORT = overall_report
        
        pprint(overall_report)
        self.assertTrue(overall_report["equivalent"], pformat(overall_report))
    
    def test_designs_difference_with_fp_spec(self):
        SEED = self.SEED
        N_POINTS = self.N_POINTS
        TOTAL_POINTS = 0
        conventional_runtime_s = 0.0
        optimized_runtime_s = 0.0
        
        print("\nRunning test_designs_difference_with_fp_spec:")
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
            TOTAL_POINTS += N_POINTS
            
            random_gen, exp_reshuffle = BFloat16.random_generator(seed=SEED, shared_exponent_bits=shared_bits)
            print(f"\tRunning {N_POINTS} random points with {shared_bits} shared leading exponent bits for each generated input.")
            
            for _ in range(N_POINTS):
                exp_reshuffle()
                for i in range(N):
                    a[i].load_val(random_gen())
                    b[i].load_val(random_gen())
                
                t0 = time.perf_counter()
                con_res = conventional.evaluate().to_val()
                conventional_runtime_s += time.perf_counter() - t0

                t0 = time.perf_counter()
                opt_res = optimized.evaluate().to_val()
                optimized_runtime_s += time.perf_counter() - t0

                spec_res = dot_product_spec(*a, *b)
                msg = (
                    f"Mismatch at pt:\nf{[x.val.to_val() for x in a + b]}",
                    f"optimized impl={opt_res}, conventional impl={con_res}, double-precision spec={spec_res}"
                )
                if ulp_distance(opt_res, con_res) != 0 or ulp_distance(opt_res, spec_res) != 0:
                    self.fail(str(msg))
                    
        TestFusedDotProduct.IMPL_REPORT = {
            "seed": SEED,
            "total_num_points": TOTAL_POINTS,
            "conventional_runtime_per_point": conventional_runtime_s/TOTAL_POINTS,
            "optimized_runtime_per_point": optimized_runtime_s/TOTAL_POINTS,
            "conventional_runtime_s_total": conventional_runtime_s,
            "optimized_runtime_s_total": optimized_runtime_s,
        }

        pprint(TestFusedDotProduct.IMPL_REPORT)


def build_unittest_report(seed: int, spec_report: dict, impl_report: dict):
    return {
        "seed": seed,
        "run_spec_report": spec_report,
        "impl_report": impl_report,
    }


def write_unittest_report(path: str, report: dict):
    report_path = Path(path)
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(report, indent=2, sort_keys=True) + "\n", encoding="utf-8")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Unittests for fused dot product desings")
    parser.add_argument("-s", "--seed", help="Random seed", default=DEFAULT_SEED, type=int)
    parser.add_argument("-pt", "--num-points", help=f"Number of points to run per shared exponent", default=DEFAULT_N_POINTS, type=int)
    parser.add_argument("--json-report", help="Write unittest summary report to this JSON file", default=None)
    
    args, unittest_args = parser.parse_known_args()

    TestFusedDotProduct.SEED = args.seed
    TestFusedDotProduct.N_POINTS = args.num_points
    
    program = unittest.main(argv=[__file__, *unittest_args], exit=False)
    
    if args.json_report:
        report = build_unittest_report(
            seed=args.seed,
            spec_report=TestFusedDotProduct.SPEC_REPORT,
            impl_report=TestFusedDotProduct.IMPL_REPORT,
        )
        write_unittest_report(args.json_report, report)

    exit_code = 0 if program.result.wasSuccessful() else 1
    sys.exit(exit_code)
