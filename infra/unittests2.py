import unittest
import contextlib
import os
from unittest.mock import patch

import dreal
import math
import z3
from egglog import EGraph

from fused_dot_product import *
from fused_dot_product.ast import nodes as ast_nodes
from fused_dot_product.egglog.rules import load_rules
from fused_dot_product.smt import dreal_check_eq, z3_check_eq
from fused_dot_product.solver import engine as solver_engine
from fused_dot_product.solver.report import build_proof_report
from fused_dot_product.spec.spec_context import simplify_ctx
from fused_dot_product.spec.spec_utils import from_egglog
import examples.FP32_IEEE_adder as fp32_adder_module
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
    def test_if_constant_fold_prunes_nonliteral_branch(self):
        x = RealVar("x")
        y = RealVar("y")

        self.assertEqual(
            If(BoolLit(False), x + RealLit(1), y + RealLit(2)).constant_fold(),
            Add(y, RealLit(2)),
        )
        self.assertEqual(
            If(BoolLit(True), x + RealLit(1), y + RealLit(2)).constant_fold(),
            Add(x, RealLit(1)),
        )

    def test_boolean_constant_fold_short_circuits_nonliteral_operands(self):
        p = BoolVar("p")

        self.assertEqual(
            And(BoolLit(False), p).constant_fold(),
            BoolLit(False),
        )
        self.assertEqual(
            And(BoolLit(True), p).constant_fold(),
            p,
        )
        self.assertEqual(
            Or(BoolLit(True), p).constant_fold(),
            BoolLit(True),
        )
        self.assertEqual(
            Or(BoolLit(False), p).constant_fold(),
            p,
        )

    def test_mul_by_zero_shortcuts_nonliteral_operand(self):
        x = RealVar("x")

        self.assertEqual(
            Mul(RealLit(0), x + RealLit(1)).constant_fold(),
            RealLit(0),
        )
        self.assertEqual(
            Mul(x + RealLit(1), RealLit(0)).constant_fold(),
            RealLit(0),
        )

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
    def test_minus_one_symbolic_power_lowers_as_plain_power(self):
        s = RealVar("s")
        expr = RealLit(-1) ** s

        z3_expr = expr.to_z3({})
        dreal_expr = expr.to_dreal({})

        self.assertNotEqual(z3_expr.decl().kind(), z3.Z3_OP_ITE)
        self.assertEqual(str(z3_expr), "-1**s")
        self.assertEqual(str(dreal_expr), "pow(-1, s)")
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

    def test_context_simplify_uses_if_branch_pruning(self):
        ctx = SpecContext("if-pruning")
        x = ctx.real("x")

        ctx.check(If(BoolLit(False), x + RealLit(1), RealLit(3)).eq(RealLit(3)))

        simplified = ctx.simplify()
        self.assertEqual(simplified.checks, [BoolLit(True)])

    def test_context_simplify_uses_mul_by_zero_shortcut(self):
        ctx = SpecContext("mul-zero")
        x = ctx.real("x")

        ctx.check((RealLit(0) * (x + RealLit(5))).eq(RealLit(0)))

        simplified = ctx.simplify()
        self.assertEqual(simplified.checks, [BoolLit(True)])


class TestSpecContextLearning(unittest.TestCase):
    def test_learned_literals_reads_real_var_equalities(self):
        ctx = SpecContext("learn-real")
        x = ctx.real("x")
        y = ctx.real("y")

        ctx.assume(x.eq(ctx.real_val(1)))
        ctx.assume(ctx.real_val(2).eq(y))

        learned = ctx.learned_literals()
        self.assertEqual(len(learned), 2)
        self.assertEqual(learned[x], RealLit(1))
        self.assertEqual(learned[y], RealLit(2))

    def test_learned_literals_reads_foldable_real_equalities(self):
        ctx = SpecContext("learn-real-foldable")
        x = ctx.real("x")
        y = ctx.real("y")

        ctx.assume(x.eq(ctx.real_val(2) + ctx.real_val(3)))
        ctx.assume((ctx.real_val(10) - ctx.real_val(4)).eq(y))

        learned = ctx.learned_literals()
        self.assertEqual(len(learned), 2)
        self.assertEqual(learned[x], RealLit(5))
        self.assertEqual(learned[y], RealLit(6))

    def test_learned_literals_reads_bool_var_equalities(self):
        ctx = SpecContext("learn-bool")
        p = ctx.bool("p")
        q = ctx.bool("q")

        ctx.assume(p.eq(ctx.true()))
        ctx.assume(ctx.false().eq(q))

        learned = ctx.learned_literals()
        self.assertEqual(len(learned), 2)
        self.assertEqual(learned[p], BoolLit(True))
        self.assertEqual(learned[q], BoolLit(False))

    def test_learned_literals_reads_foldable_bool_equalities(self):
        ctx = SpecContext("learn-bool-foldable")
        p = ctx.bool("p")
        q = ctx.bool("q")

        ctx.assume(p.eq(ctx.real_val(2).eq(ctx.real_val(2))))
        ctx.assume((ctx.real_val(2).eq(ctx.real_val(3))).eq(q))

        learned = ctx.learned_literals()
        self.assertEqual(len(learned), 2)
        self.assertEqual(learned[p], BoolLit(True))
        self.assertEqual(learned[q], BoolLit(False))

    def test_learned_literals_ignores_non_literal_equalities(self):
        ctx = SpecContext("learn-ignore")
        x = ctx.real("x")
        y = ctx.real("y")
        p = ctx.bool("p")
        q = ctx.bool("q")

        ctx.assume(x.eq(y))
        ctx.assume(p.eq(q))

        self.assertEqual(ctx.learned_literals(), {})

    def test_learned_literals_raises_on_conflicting_bindings(self):
        ctx = SpecContext("learn-conflict")
        x = ctx.real("x")
        p = ctx.bool("p")

        ctx.assume(x.eq(ctx.real_val(0)))
        ctx.assume(p.eq(ctx.true()))
        ctx.assume(x.eq(ctx.real_val(1)))

        with self.assertRaises(ValueError):
            ctx.learned_literals()

    def test_conflicting_assumptions_are_deferred_until_simplification(self):
        ctx = SpecContext("assume-deferred-conflict")
        x = ctx.real("x")
        y = ctx.real("y")

        ctx.assume(x.eq(ctx.real_val(0)))
        before = ctx.copy()
        ctx.assume(x.eq(ctx.real_val(1)))

        self.assertEqual(
            ctx.assumes,
            before.assumes + [Eq(x, RealLit(1))],
        )
        self.assertEqual(ctx.checks, before.checks)

        ctx.assume(y.eq(x))
        with self.assertRaises(ValueError):
            ctx.simplify()

        self.assertEqual(
            ctx.assumes,
            [Eq(x, RealLit(0)), Eq(x, RealLit(1)), Eq(y, x)],
        )

    def test_context_fixpoint_simplifies_assumptions_from_learned_literals(self):
        ctx = SpecContext("simplify-assumes")
        and_res = ctx.real("and_res")
        x = ctx.real("x")
        y = ctx.real("y")

        ctx.assume(and_res.eq(x * y))
        ctx.assume(x.eq(ctx.real_val(0)))
        ctx.assume(y.eq(ctx.real_val(0)))

        simplified = ctx.simplify()

        self.assertEqual(
            ctx.assumes,
            [
                Eq(and_res, x * y),
                Eq(x, RealLit(0)),
                Eq(y, RealLit(0)),
            ],
        )
        self.assertEqual(
            simplified.assumes,
            [
                Eq(and_res, RealLit(0)),
                Eq(x, RealLit(0)),
                Eq(y, RealLit(0)),
            ],
        )

    def test_context_fixpoint_retains_canonical_learned_assumptions(self):
        ctx = SpecContext("canonical-assumes")
        x = ctx.real("x")
        p = ctx.bool("p")

        ctx.assume(x.eq(ctx.real_val(1) + ctx.real_val(2)))
        ctx.assume(ctx.real_val(4).eq(x + ctx.real_val(1)))
        ctx.assume(p.eq(ctx.real_val(2).eq(ctx.real_val(2))))

        simplified = ctx.simplify()

        self.assertEqual(
            simplified.assumes,
            [
                Eq(x, RealLit(3)),
                BoolLit(True),
                BoolEq(p, BoolLit(True)),
            ],
        )
        self.assertEqual(
            simplified.learned_literals(),
            {x: RealLit(3), p: BoolLit(True)},
        )

    def test_context_fixpoint_propagates_through_multiple_rounds(self):
        ctx = SpecContext("simplify-multi-round")
        x = ctx.real("x")
        y = ctx.real("y")
        z = ctx.real("z")

        ctx.assume(x.eq(y + ctx.real_val(1)))
        ctx.assume(y.eq(z + ctx.real_val(1)))
        ctx.assume(z.eq(ctx.real_val(0)))

        simplified = ctx.simplify()

        self.assertEqual(
            simplified.assumes,
            [
                Eq(x, RealLit(2)),
                Eq(y, RealLit(1)),
                Eq(z, RealLit(0)),
            ],
        )
        self.assertEqual(
            simplified.learned_literals(),
            {x: RealLit(2), y: RealLit(1), z: RealLit(0)},
        )

    def test_context_fixpoint_simplifies_checks_from_learned_literals(self):
        ctx = SpecContext("simplify-checks")
        x = ctx.real("x")

        ctx.assume(x.eq(ctx.real_val(1)))
        ctx.check((x + ctx.real_val(2)).eq(ctx.real_val(3)))

        simplified = ctx.simplify()

        self.assertEqual(ctx.checks, [Eq(x + RealLit(2), RealLit(3))])
        self.assertEqual(simplified.checks, [BoolLit(True)])

    def test_context_fixpoint_simplifies_bool_assumptions_and_checks(self):
        ctx = SpecContext("simplify-bool")
        p = ctx.bool("p")
        q = ctx.bool("q")

        ctx.assume(p.eq(ctx.true()))
        ctx.assume(q.eq(p))
        ctx.check(q.eq(ctx.true()))

        simplified = ctx.simplify()

        self.assertEqual(ctx.assumes, [BoolEq(p, BoolLit(True)), BoolEq(q, p)])
        self.assertEqual(
            simplified.assumes,
            [BoolEq(p, BoolLit(True)), BoolEq(q, BoolLit(True))],
        )
        self.assertEqual(simplified.checks, [BoolLit(True)])
        self.assertEqual(
            simplified.learned_literals(),
            {p: BoolLit(True), q: BoolLit(True)},
        )

    def test_context_fixpoint_accepts_duplicate_equivalent_bindings(self):
        ctx = SpecContext("simplify-duplicate")
        x = ctx.real("x")
        p = ctx.bool("p")

        ctx.assume(x.eq(ctx.real_val(1)))
        ctx.assume((ctx.real_val(2) - ctx.real_val(1)).eq(x))
        ctx.assume(p.eq(ctx.true()))
        ctx.assume(ctx.real_val(3).eq(ctx.real_val(3)).eq(p))

        simplified = ctx.simplify()

        self.assertEqual(
            simplified.assumes,
            [
                Eq(x, RealLit(1)),
                Eq(x, RealLit(1)),
                BoolEq(p, BoolLit(True)),
                BoolEq(p, BoolLit(True)),
            ],
        )
        self.assertEqual(
            simplified.learned_literals(),
            {x: RealLit(1), p: BoolLit(True)},
        )

    def test_context_fixpoint_raises_on_conflicting_bindings(self):
        ctx = SpecContext("simplify-conflict")
        x = ctx.real("x")

        ctx.assume(x.eq(ctx.real_val(0)))
        ctx.assume(x.eq(ctx.real_val(1)))

        with self.assertRaises(ValueError):
            ctx.simplify()

    def test_simplify_returns_new_simplified_context(self):
        ctx = SpecContext("simplify-output")
        x = ctx.real("x")
        y = ctx.real("y")

        ctx.assume(x.eq(y + ctx.real_val(1)))
        ctx.assume(y.eq(ctx.real_val(2)))
        ctx.check(x.eq(ctx.real_val(3)))

        simplified = ctx.simplify()

        self.assertIsNot(simplified, ctx)
        self.assertEqual(ctx.assumes, [Eq(x, Add(y, RealLit(1))), Eq(y, RealLit(2))])
        self.assertEqual(ctx.checks, [Eq(x, RealLit(3))])
        self.assertEqual(
            simplified.assumes,
            [Eq(x, RealLit(3)), Eq(y, RealLit(2))],
        )
        self.assertEqual(simplified.checks, [BoolLit(True)])

    def test_simplify_leaves_original_context_unchanged_on_conflict(self):
        ctx = SpecContext("simplify-conflict-output")
        x = ctx.real("x")

        ctx.assume(x.eq(ctx.real_val(0)))
        ctx.assume(x.eq(ctx.real_val(1)))

        with self.assertRaises(ValueError):
            ctx.simplify()

        self.assertEqual(ctx.assumes, [Eq(x, RealLit(0)), Eq(x, RealLit(1))])


class TestEgglogFloatLiterals(unittest.TestCase):
    def test_real_lit_round_trips_exact_finite_float_values(self):
        values = [
            0.1,
            0.2,
            0.3,
            1.25,
            -2.5,
            1e-6,
            2.0 ** -20,
        ]

        for value in values:
            with self.subTest(value=value):
                round_tripped = from_egglog(RealLit(value).to_egglog())

                self.assertIsInstance(round_tripped, RealLit)
                self.assertEqual(round_tripped.value.hex(), value.hex())

    def test_fractional_literals_constant_fold_in_egglog_without_losing_float_bits(self):
        expr = RealLit(0.1) + RealLit(0.2)

        egraph = EGraph()
        load_rules(egraph)
        lowered = expr.to_egglog()

        egraph.register(lowered)
        egraph.run(1)

        folded = from_egglog(egraph.extract(lowered))
        self.assertEqual(folded, RealLit(0.1 + 0.2))
        self.assertEqual(folded.value.hex(), (0.1 + 0.2).hex())

    def test_fractional_pow_round_trips_through_egglog(self):
        expr = Pow(RealLit(2.5), RealLit(0.5))

        self.assertEqual(from_egglog(expr.to_egglog()), expr)

    def test_non_finite_real_lits_are_rejected_by_egglog_lowering(self):
        for value in (math.inf, -math.inf, math.nan):
            with self.subTest(value=value):
                with self.assertRaises(ValueError):
                    RealLit(value).to_egglog()


class TestSpecAstConstantFolding(unittest.TestCase):
    def test_constant_fold_method_folds_literal_tree(self):
        expr = (RealLit(2) + RealLit(3)) * RealLit(4)

        self.assertEqual(expr.constant_fold(), RealLit(20))

    def test_constant_fold_collapses_literal_subtrees(self):
        expr = ((RealLit(2) + RealLit(3)) * RealLit(4)).eq(RealLit(20))

        self.assertEqual(expr.constant_fold(), BoolLit(True))

    def test_constant_fold_can_produce_false(self):
        expr = (RealLit(2) + RealLit(3)).eq(RealLit(6))

        self.assertEqual(expr.constant_fold(), BoolLit(False))

    def test_constant_fold_keeps_symbolic_if_shape(self):
        expr = If(BoolLit(True), RealVar("x"), RealVar("y"))

        self.assertEqual(expr.constant_fold(), RealVar("x"))

    def test_constant_fold_partially_rebuilds_symbolic_real_expr(self):
        x = RealVar("x")
        expr = x + (RealLit(2) + RealLit(3))

        self.assertEqual(expr.constant_fold(), Add(x, RealLit(5)))

    def test_constant_fold_partially_rebuilds_symbolic_bool_expr(self):
        p = BoolVar("p")
        expr = p.or_(RealLit(2).eq(RealLit(2)))

        self.assertEqual(expr.constant_fold(), BoolLit(True))

    def test_constant_fold_folds_boolean_operator_trees(self):
        expr = RealLit(2).eq(RealLit(2)).and_(~BoolLit(False))

        self.assertEqual(expr.constant_fold(), BoolLit(True))

    def test_constant_fold_leaves_unsupported_literal_pow_unchanged(self):
        expr = Pow(RealLit(-2), RealLit(0.5))

        self.assertEqual(expr.constant_fold(), expr)

class TestSolverApis(unittest.TestCase):
    def test_fp32_adder_check_spec_splits_all_input_class_pairs(self):
        adder = FP32_IEEE_adder(
            Var(name="a", sign=Float32T()),
            Var(name="b", sign=Float32T()),
        )
        seen_names = []

        def fake_check_equivalence(query1, query2, ctx, schedule):
            del query1, query2, schedule
            seen_names.append(ctx.name)
            return True, []

        with patch.object(ast_nodes, "check_equivalence", side_effect=fake_check_equivalence):
            proof_trace = adder.check_spec(schedule=[{"tool": "z3", "timeout_ms": 1}])

        expected_names = {
            f"FP32_IEEE_adder[x={x_case},y={y_case},inner_out={inner_case},outer_out={outer_case}]"
            for x_case in fp32_adder_module._FP32_INPUT_CLASS_CASES
            for y_case in fp32_adder_module._FP32_INPUT_CLASS_CASES
            for inner_case in fp32_adder_module._FP32_OUTPUT_CLASS_CASES
            for outer_case in fp32_adder_module._FP32_OUTPUT_CLASS_CASES
        }
        self.assertEqual(proof_trace, [[] for _ in expected_names])
        self.assertEqual(len(seen_names), len(expected_names))
        self.assertEqual(set(seen_names), expected_names)

    def test_check_equivalence_with_simplify_schedule_short_circuits(self):
        ctx = SpecContext("simplify-schedule")

        equivalent, proof_trace = solver_engine.check_equivalence(
            RealLit(1) + RealLit(2),
            RealLit(3),
            ctx=ctx,
            schedule=[{"tool": "simplify"}],
        )

        self.assertTrue(equivalent)
        self.assertEqual(len(proof_trace), 1)
        self.assertEqual(proof_trace[0]["tool"], "simplify")

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

    def test_fp32_adder_norm_norm_proves_with_egglog(self):
        adder = FP32_IEEE_adder(
            Var(name="a", sign=Float32T()),
            Var(name="b", sign=Float32T()),
        )

        with open(os.devnull, "w") as devnull, contextlib.redirect_stdout(devnull):
            proof_traces = adder.check_spec(
                schedule=[
                    {"tool": "simplify"},
                    {
                        "tool": "egglog-rewrite",
                        "iterations": 6,
                        "scheduler": {"match_limit": 500_000, "ban_length": 1},
                    },
                ]
            )

        self.assertEqual(len(proof_traces), 1)
        self.assertTrue(
            any(
                report["tool"] == "egglog_rewrite" and report["equivalent"]
                for report in proof_traces[0]
            ),
            proof_traces[0],
        )

    def test_z3_check_eq_returns_single_report(self):
        ctx = SpecContext("z3-api")
        ctx.check(RealLit(1).eq(RealLit(1)))

        report = z3_check_eq(ctx, timeout_ms=1000)

        self.assertIsInstance(report, dict)
        self.assertEqual(report["tool"], "z3")
        self.assertTrue(report["equivalent"])

    def test_dreal_check_eq_returns_single_report(self):
        ctx = SpecContext("dreal-api")
        ctx.check(RealLit(1).eq(RealLit(1)))

        report = dreal_check_eq(ctx, precision=0.001)

        self.assertIsInstance(report, dict)
        self.assertEqual(report["tool"], "dreal")
        self.assertTrue(report["equivalent"])


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
                ctx.check(spec.eq(ctx.real_val(expected)))
                report = z3_check_eq(ctx.simplify(), timeout_ms=1000)

                self.assertEqual(str(spec), "real(xored_signs_2)")
                self.assertTrue(report["equivalent"], report)


if __name__ == "__main__":
    unittest.main()
