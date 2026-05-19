import unittest
from unittest.mock import patch

import dreal
from egglog import EGraph

from fused_dot_product import *
from fused_dot_product.egglog.rules import load_rules
from fused_dot_product.smt import z3_check_eq
from fused_dot_product.solver import engine as solver_engine
from fused_dot_product.solver.report import build_proof_report
from fused_dot_product.spec.spec_utils import from_egglog
from examples.FP32_IEEE_adder import FP32_IEEE_adder
from examples.FP32_IEEE_mult import FP32_IEEE_mult
from examples.conventional import Conventional
from examples.optimized import Optimized

from infra.compile_cpp import jit_compile, nonjit_compile


class TestConstantFolding(unittest.TestCase):
    def assert_folded_value(self, node, runtime_type, expected_val):
        self.assertIsNotNone(node.node_type.runtime_val)
        self.assertIsInstance(node.node_type.runtime_val, runtime_type)
        self.assertEqual(node.node_type.runtime_val.val, expected_val)

        evaluated = node.evaluate()
        self.assertIsInstance(evaluated, runtime_type)
        self.assertEqual(evaluated.val, expected_val)

    def test_float32_nan_default_is_quiet(self):
        self.assertEqual(Float32.NaN().val, 0x7FC00000)
        self.assertEqual(Float32.NaN(1).val, 0x7F800001)
        
    def test_cpp_lowering_widening_add_sub(self):
        add_x = Var(name="add_x", sign=UQT(32, 0))
        add_y = Var(name="add_y", sign=UQT(32, 0))
        add_design = uq_add(add_x, add_y)

        sub_x = Var(name="sub_x", sign=UQT(32, 0))
        sub_y = Var(name="sub_y", sign=UQT(32, 0))
        sub_design = uq_sub(sub_x, sub_y)

        add_tempdir_jit, add_fn_jit = jit_compile(add_design)
        add_tempdir_no_jit, add_fn_no_jit = nonjit_compile(add_design)
        sub_tempdir_jit, sub_fn_jit = jit_compile(sub_design)
        sub_tempdir_no_jit, sub_fn_no_jit = nonjit_compile(sub_design)

        add_cases = [
            (0xFFFF_FFFF, 0x0000_0001, 0x1_0000_0000),
            (0x8000_0000, 0x8000_0000, 0x1_0000_0000),
        ]
        sub_cases = [
            (0x0000_0000, 0x0000_0001, 0x1_FFFF_FFFF),
            (0x8000_0000, 0x0000_0001, 0x07FFF_FFFF),
        ]

        try:
            for lhs_bits, rhs_bits, expected in add_cases:
                add_x.load_val(UQ(lhs_bits, 32, 0))
                add_y.load_val(UQ(rhs_bits, 32, 0))
                with self.subTest(op="uq_add", lhs=hex(lhs_bits), rhs=hex(rhs_bits)):
                    self.assertEqual(add_design.evaluate().val, expected)
                    self.assertEqual(add_fn_jit(lhs_bits, rhs_bits), expected)
                    self.assertEqual(add_fn_no_jit(lhs_bits, rhs_bits), expected)

            for lhs_bits, rhs_bits, expected in sub_cases:
                sub_x.load_val(UQ(lhs_bits, 32, 0))
                sub_y.load_val(UQ(rhs_bits, 32, 0))
                with self.subTest(op="uq_sub", lhs=hex(lhs_bits), rhs=hex(rhs_bits)):
                    self.assertEqual(sub_design.evaluate().val, expected)
                    self.assertEqual(sub_fn_jit(lhs_bits, rhs_bits), expected)
                    self.assertEqual(sub_fn_no_jit(lhs_bits, rhs_bits), expected)
        finally:
            add_tempdir_jit.cleanup()
            add_tempdir_no_jit.cleanup()
            sub_tempdir_jit.cleanup()
            sub_tempdir_no_jit.cleanup()


    def test_fp32_multiplier_special_cases(self):
        x = Var(name="x", sign=Float32T())
        y = Var(name="y", sign=Float32T())
        design = FP32_IEEE_mult(x, y)

        tempdir_jit, fn_jit = jit_compile(design)
        tempdir_no_jit, fn_no_jit = nonjit_compile(design)

        cases = [
            (Float32.Inf().val, Float32.Zero().val, Float32.NaN().val),
            (Float32.nInf().val, Float32.Zero().val, Float32.NaN().val),
            (Float32.Inf().val, Float32.from_fields(0, 128, 0).val, Float32.Inf().val),
            (Float32.nInf().val, Float32.from_fields(0, 128, 0).val, Float32.nInf().val),
            (Float32.nZero().val, Float32.from_fields(0, 128, 1 << 22).val, Float32.nZero().val),
            (Float32.nZero().val, Float32.from_fields(1, 128, 1 << 22).val, Float32.Zero().val),
            (Float32.NaN().val, Float32.from_fields(0, 128, 0).val, Float32.NaN().val),
        ]

        try:
            for lhs_bits, rhs_bits, expected_bits in cases:
                x.load_val(Float32(lhs_bits))
                y.load_val(Float32(rhs_bits))
                with self.subTest(lhs=hex(lhs_bits), rhs=hex(rhs_bits)):
                    self.assertEqual(design.evaluate().val, expected_bits)
                    self.assertEqual(fn_jit(lhs_bits, rhs_bits), expected_bits)
                    self.assertEqual(fn_no_jit(lhs_bits, rhs_bits), expected_bits)
        finally:
            tempdir_jit.cleanup()
            tempdir_no_jit.cleanup()

    def test_basic_add_folds_for_float_bit_types(self):
        cases = [
            ("float32", Float32),
            ("bfloat16", BFloat16),
        ]

        for name, runtime_type in cases:
            with self.subTest(runtime_type=name):
                folded = basic_add(
                    Const(runtime_type(1)),
                    Const(runtime_type(2)),
                    out=Const(runtime_type(0)),
                )

                self.assert_folded_value(folded, runtime_type, 3)

    def test_basic_add_masks_to_output_width(self):
        folded = basic_add(
            Const(UQ(7, 3, 0)),
            Const(UQ(3, 3, 0)),
            out=Const(UQ(0, 3, 0)),
        )

        self.assert_folded_value(folded, UQ, 2)

    def test_comparison_folds_to_bool(self):
        folded = basic_less(
            Const(UQ(1, 2, 0)),
            Const(UQ(2, 2, 0)),
            out=Const(Bool(0)),
        )

        self.assert_folded_value(folded, Bool, 1)

    def test_tuple_get_item_is_constant_folded(self):
        folded = make_Tuple(
            Const(UQ(5, 3, 0)),
            Const(Bool(1)),
        )[0]

        self.assert_folded_value(folded, UQ, 5)

    def test_if_then_else_is_constant_folded(self):
        folded = if_then_else(
            Const(Bool(1)),
            Const(UQ(5, 3, 0)),
            Const(UQ(2, 3, 0)),
        )

        self.assert_folded_value(folded, UQ, 5)

    def test_non_constant_inputs_do_not_fold(self):
        x = Var("x", sign=UQT(3, 0))
        node = basic_add(
            x,
            Const(UQ(1, 3, 0)),
            out=Const(UQ(0, 3, 0)),
        )

        self.assertIsNone(node.node_type.runtime_val)

        x.load_val(UQ(6, 3, 0))
        self.assertEqual(node.evaluate().val, 7)
        self.assertIsNone(node.node_type.runtime_val)

    def test_uq_rshift_jam_sets_sticky_when_shifted_out_bits_are_nonzero(self):
        cases = [
            (8, 1, 4),
            (9, 1, 5),
        ]

        for x_val, amount_val, expected in cases:
            with self.subTest(x=x_val, amount=amount_val):
                folded = uq_rshift_jam(
                    Const(UQ(x_val, 4, 0)),
                    Const(UQ.from_int(amount_val)),
                )
                self.assert_folded_value(folded, UQ, expected)

    def test_conventional_and_optimized_match_on_cancellation_regression(self):
        vals = [43160, 10458, 11062, 10989, 10589, 10469, 11020, 11013]
        a = [Var(name=f"a_{i}", sign=BFloat16T()) for i in range(4)]
        b = [Var(name=f"b_{i}", sign=BFloat16T()) for i in range(4)]

        for i, bits in enumerate(vals[:4]):
            a[i].load_val(BFloat16(bits))
        for i, bits in enumerate(vals[4:]):
            b[i].load_val(BFloat16(bits))

        conventional = Conventional(*a, *b).evaluate()
        optimized = Optimized(*a, *b).evaluate()

        self.assertEqual(conventional.val, 388040612)
        self.assertEqual(conventional, optimized)


class TestFingerprint(unittest.TestCase):
    def test_runtime_type_fingerprint_depends_on_structure_and_value(self):
        self.assertEqual(UQ(3, 3, 0)._fingerprint(), UQ(3, 3, 0)._fingerprint())
        self.assertNotEqual(UQ(3, 3, 0)._fingerprint(), UQ(4, 3, 0)._fingerprint())
        self.assertNotEqual(UQ(3, 3, 0)._fingerprint(), UQ(3, 4, 0)._fingerprint())

        lhs = Tuple(UQ(5, 3, 0), Bool(1))
        rhs = Tuple(UQ(5, 3, 0), Bool(1))
        different = Tuple(UQ(5, 3, 0), Bool(0))
        self.assertEqual(lhs._fingerprint(), rhs._fingerprint())
        self.assertNotEqual(lhs._fingerprint(), different._fingerprint())

    def test_static_type_fingerprint_includes_runtime_val(self):
        plain = UQT(3, 0)
        same = UQT(3, 0)
        self.assertEqual(plain._fingerprint(), same._fingerprint())

        with_runtime = UQT(3, 0)
        with_runtime.runtime_val = UQ(1, 3, 0)
        same_runtime = UQT(3, 0)
        same_runtime.runtime_val = UQ(1, 3, 0)
        different_runtime = UQT(3, 0)
        different_runtime.runtime_val = UQ(2, 3, 0)

        self.assertEqual(with_runtime._fingerprint(), same_runtime._fingerprint())
        self.assertNotEqual(plain._fingerprint(), with_runtime._fingerprint())
        self.assertNotEqual(with_runtime._fingerprint(), different_runtime._fingerprint())

    def test_equivalent_graphs_have_equal_fingerprints(self):
        x1 = Var("x", sign=UQT(3, 0))
        y1 = Var("y", sign=UQT(3, 0))
        x2 = Var("x", sign=UQT(3, 0))
        y2 = Var("y", sign=UQT(3, 0))

        lhs = basic_add(x1, y1, Const(UQ(0, 3, 0)))
        rhs = basic_add(x2, y2, Const(UQ(0, 3, 0)))

        self.assertEqual(lhs._fingerprint(), rhs._fingerprint())

    def test_graph_fingerprint_changes_with_operation_and_constants(self):
        x = Var("x", sign=UQT(3, 0))
        y = Var("y", sign=UQT(3, 0))

        add_node = basic_add(x, y, Const(UQ(0, 3, 0)))
        sub_node = basic_sub(x, y, Const(UQ(0, 3, 0)))
        different_const = basic_add(x, y, Const(UQ(1, 3, 0)))

        self.assertNotEqual(add_node._fingerprint(), sub_node._fingerprint())
        self.assertNotEqual(add_node._fingerprint(), different_const._fingerprint())

    def test_fingerprint_depends_on_jittable_lowering_when_codegen_differs(self):
        node = make_Tuple(Const(UQ(1, 3, 0)), Const(UQ(2, 3, 0)))

        self.assertNotEqual(node._fingerprint(jittable=True), node._fingerprint(jittable=False))

    def test_fingerprint_is_stable_across_runtime_variable_bindings(self):
        x = Var("x", sign=UQT(3, 0))
        y = Var("y", sign=UQT(3, 0))
        node = basic_add(x, y, Const(UQ(0, 3, 0)))

        before = node._fingerprint()

        x.load_val(UQ(6, 3, 0))
        y.load_val(UQ(1, 3, 0))
        self.assertEqual(node.evaluate().val, 7)

        after = node._fingerprint()
        self.assertEqual(before, after)


class TestPowSpecOp(unittest.TestCase):
    def test_pow_python_sugar_uses_negative_one_base(self):
        self.assertEqual(
            RealLit(-1) ** RealLit(3),
            Pow(RealLit(-1), RealLit(3)),
        )

    def test_pow_python_sugar_keeps_supported_base2_and_square_forms(self):
        self.assertEqual(
            RealLit(2) ** RealLit(3),
            Pow(RealLit(2), RealLit(3)),
        )
        self.assertEqual(
            RealLit(3) ** RealLit(2),
            Pow(RealLit(3), RealLit(2)),
        )

    def test_pow_round_trips_from_egglog(self):
        exprs = [
            Pow(RealLit(-1), RealLit(2)),
            Pow(RealLit(2), RealLit(3)),
            Pow(RealLit(3), RealLit(2)),
        ]

        for expr in exprs:
            with self.subTest(expr=str(expr)):
                self.assertEqual(from_egglog(expr.to_egglog()), expr)

    def test_pow_constant_folds_in_egglog(self):
        cases = [
            (Pow(RealLit(-1), RealLit(3)), RealLit(-1)),
            (Pow(RealLit(2), RealLit(3)), RealLit(8)),
            (Pow(RealLit(3), RealLit(2)), RealLit(9)),
        ]

        for expr, expected in cases:
            with self.subTest(expr=str(expr)):
                egraph = EGraph()
                load_rules(egraph)
                lowered = expr.to_egglog()

                egraph.register(lowered)
                egraph.run(1)

                self.assertEqual(from_egglog(egraph.extract(lowered)), expected)

    def test_minus_one_symbolic_power_is_solver_friendly_for_dreal(self):
        ctx = SpecContext("minus-one-dreal")
        s = RealVar("s")
        x = RealVar("x")
        ctx.assume(s.eq(RealLit(0)).or_(s.eq(RealLit(1))))
        ctx.assume(x.eq((RealLit(-1) ** s) * abs(x)))

        env = {}
        result = dreal.CheckSatisfiability(
            dreal.And(*[assume.to_dreal(env) for assume in ctx.assumes]),
            0.001,
        )

        self.assertIsNotNone(result)

    def test_numeric_equality_constant_folds_in_egglog(self):
        cases = [
            (RealLit(3).eq(RealLit(3)), BoolLit(True)),
            (RealLit(3).ne(RealLit(4)), BoolLit(True)),
        ]

        for expr, expected in cases:
            with self.subTest(expr=str(expr)):
                egraph = EGraph()
                load_rules(egraph)
                lowered = expr.to_egglog()

                egraph.register(lowered)
                egraph.run(1)

                self.assertEqual(from_egglog(egraph.extract(lowered)), expected)

    def test_numeric_equality_constant_folds_in_simplify_mode(self):
        cases = [
            (RealLit(5).eq(RealLit(5)), BoolLit(True)),
            (RealLit(5).ne(RealLit(6)), BoolLit(True)),
        ]

        for expr, expected in cases:
            with self.subTest(expr=str(expr)):
                egraph = EGraph()
                load_rules(egraph, simplify=True)
                lowered = expr.to_egglog()

                egraph.register(lowered)
                egraph.run(1)

                self.assertEqual(from_egglog(egraph.extract(lowered)), expected)


class TestSolverApis(unittest.TestCase):
    def test_check_equivalence_returns_flat_proof_trace(self):
        ctx = SpecContext("flat-trace")
        report1 = build_proof_report(ctx, ctx.copy(), tool="branch-a", runtime_s=0.0, equivalent=False)
        report2 = build_proof_report(ctx, ctx.copy(), tool="branch-b", runtime_s=0.0, equivalent=True)

        with patch.dict(solver_engine.TOOL_FNS, {"z3": lambda _ctx, timeout_ms: [report1, report2]}):
            equivalent, proof_trace = solver_engine.check_equivalence(
                RealLit(1),
                RealLit(1),
                ctx=ctx,
                schedule=[{"tool": "z3", "timeout_ms": 1}],
            )

        self.assertTrue(equivalent)
        self.assertIsInstance(proof_trace, list)
        self.assertEqual(len(proof_trace), 1)
        self.assertIsInstance(proof_trace[0], dict)
        self.assertEqual(proof_trace[0]["tool"], "branch-b")

    def test_check_equivalence_splits_tuple_queries_into_independent_contexts(self):
        base_ctx = SpecContext("tuple-split")
        base_ctx.assume(RealLit(5).eq(RealLit(5)))
        seen_checks: list[list[str]] = []

        def fake_z3(ctx, timeout_ms):
            seen_checks.append([str(check) for check in ctx.checks])
            return build_proof_report(
                ctx,
                ctx.copy(),
                tool="z3",
                runtime_s=0.0,
                equivalent=True,
                timeout_ms=timeout_ms,
            )

        with patch.dict(solver_engine.TOOL_FNS, {"z3": fake_z3}):
            equivalent, proof_trace = solver_engine.check_equivalence(
                (RealLit(1), RealLit(2)),
                (RealLit(1), RealLit(2)),
                ctx=base_ctx,
                schedule=[{"tool": "z3", "timeout_ms": 1}],
            )

        self.assertTrue(equivalent)
        self.assertEqual(
            seen_checks,
            [
                ["(1 == 1)"],
                ["(2 == 2)"],
            ],
        )
        self.assertEqual(len(proof_trace), 2)
        self.assertTrue(all(report["equivalent"] for report in proof_trace))
        self.assertEqual(base_ctx.checks, [])

    def test_check_equivalence_stops_at_first_failing_split_problem(self):
        seen_checks: list[list[str]] = []

        def fake_z3(ctx, timeout_ms):
            check_strs = [str(check) for check in ctx.checks]
            seen_checks.append(check_strs)
            equivalent = check_strs == ["(1 == 1)"]
            return build_proof_report(
                ctx,
                ctx.copy(),
                tool="z3",
                runtime_s=0.0,
                equivalent=equivalent,
                timeout_ms=timeout_ms,
            )

        with patch.dict(solver_engine.TOOL_FNS, {"z3": fake_z3}):
            equivalent, proof_trace = solver_engine.check_equivalence(
                (RealLit(1), RealLit(2), RealLit(3)),
                (RealLit(1), RealLit(4), RealLit(3)),
                ctx=SpecContext("tuple-stop"),
                schedule=[{"tool": "z3", "timeout_ms": 1}],
            )

        self.assertFalse(equivalent)
        self.assertEqual(
            seen_checks,
            [
                ["(1 == 1)"],
                ["(2 == 4)"],
            ],
        )
        self.assertEqual(len(proof_trace), 2)
        self.assertTrue(proof_trace[0]["equivalent"])
        self.assertFalse(proof_trace[1]["equivalent"])

    def test_z3_check_eq_returns_single_report(self):
        ctx = SpecContext("z3-api")
        ctx.check(RealLit(1).eq(RealLit(1)))

        report = z3_check_eq(ctx, timeout_ms=1000)

        self.assertIsInstance(report, dict)
        self.assertEqual(report["tool"], "z3")
        self.assertTrue(report["equivalent"])

    def test_fp32_adder_wrong_high_level_spec_is_not_proved_by_dreal(self):
        adder = FP32_IEEE_adder(
            Var(name="a", sign=Float32T()),
            Var(name="b", sign=Float32T()),
        )

        trace = adder.check_spec(schedule=[{"tool": "dreal", "precision": 0.001}])

        self.assertEqual(len(trace), 1)
        self.assertEqual(trace[0]["tool"], "dreal")
        self.assertFalse(trace[0]["equivalent"])


class TestSignSpecs(unittest.TestCase):
    def test_q_signs_xor_spec_matches_constant_sign_combinations(self):
        cases = [
            (-1, -1, 0),
            (-1, 1, 1),
            (1, -1, 1),
            (1, 1, 0),
        ]

        for lhs, rhs, expected in cases:
            with self.subTest(lhs=lhs, rhs=rhs):
                node = q_signs_xor(Const(Q.from_int(lhs)), Const(Q.from_int(rhs)))
                self.assertEqual(node.evaluate().val, expected)

                ctx = SpecContext("q_signs_xor")
                spec = ctx.spec_of(node)

                self.assertEqual(str(spec), "real(xored_signs_2)")
                self.assertEqual(
                    [str(assume) for assume in ctx.assumes],
                    [
                        "((real(x_sign_0) == 1) or (real(x_sign_0) == 0))",
                        "((real(y_sign_1) == 1) or (real(y_sign_1) == 0))",
                        "((real(xored_signs_2) == 1) or (real(xored_signs_2) == 0))",
                        f"({float(lhs)} == ((-1 ** real(x_sign_0)) * abs({float(lhs)})))",
                        f"({float(rhs)} == ((-1 ** real(y_sign_1)) * abs({float(rhs)})))",
                        "((-1 ** real(xored_signs_2)) == ((-1 ** real(x_sign_0)) * (-1 ** real(y_sign_1))))",
                    ],
                )


if __name__ == "__main__":
    unittest.main()
