import unittest
import random

from fused_dot_product.utils.composites import round_to_the_nearest_even_draft
from fused_dot_product.utils.utils import round_to_the_nearest_even
from fused_dot_product.ast.AST import Const
from fused_dot_product.numtypes.RuntimeTypes import UQ, Q


class TestRoundToNearestEvenDraft(unittest.TestCase):
    def _round(self, mantissa: UQ, exponent: Q, target_bits: int) -> tuple[UQ, Q]:
        node = round_to_the_nearest_even_draft(Const(mantissa), Const(exponent), target_bits)
        try:
            result = node.evaluate()
        except AssertionError as err:
            self.fail(
                f"round_to_the_nearest_even_draft failed for mantissa={mantissa}, "
                f"exponent={exponent}, target_bits={target_bits}: {err}"
            )
        return result.args

    def _ref_round(self, mantissa: UQ, exponent: Q, target_bits: int) -> tuple[UQ, Q]:
        total_bits = mantissa.total_bits()
        bits_diff = total_bits - target_bits

        sign_int_bits = min(mantissa.int_bits, target_bits)
        sign_frac_bits = max(target_bits - mantissa.int_bits, 0)

        overflow = 0
        if bits_diff <= 0:
            rounded_val = mantissa.val
        else:
            rounded_val = round_to_the_nearest_even(mantissa.val, total_bits, target_bits)
            if rounded_val >= (1 << target_bits):
                overflow = 1
                rounded_val >>= 1

        rounded_val &= (1 << target_bits) - 1
        expected_m = UQ(rounded_val, sign_int_bits, sign_frac_bits)

        def to_signed(val: int, bits: int) -> int:
            sign = 1 << (bits - 1)
            return val - (1 << bits) if val & sign else val

        e_total_bits = exponent.total_bits() + 1
        e_mask = (1 << e_total_bits) - 1
        e_signed = to_signed(exponent.val, exponent.total_bits())
        expected_e = Q(
            (e_signed + overflow) & e_mask,
            exponent.int_bits + 1,
            exponent.frac_bits,
        )
        return expected_m, expected_e

    def _build_cases(self) -> list[tuple[str, UQ, Q, int]]:
        cases = [
            ("no_truncation", UQ(0b1011, 2, 2), Q(3, 4, 0), 4),
            ("guard_1_lsb_0", UQ(0b1001, 2, 2), Q(1, 3, 0), 3),
            ("guard_1_lsb_1", UQ(0b1011, 2, 2), Q(2, 3, 0), 3),
            ("guard_round_1", UQ(0b0111, 2, 2), Q(0, 2, 0), 2),
            ("tie_down_even", UQ(0b1010, 2, 2), Q(4, 4, 0), 2),
            ("tie_up_overflow", UQ(0b1110, 2, 2), Q(7, 3, 0), 2),
            ("sticky_set", UQ(0b101101, 3, 3), Q(2, 4, 0), 3),
            ("guard_zero_rounds_down", UQ(0b110011, 3, 3), Q(5, 4, 0), 3),
            ("zero_mantissa", UQ(0, 3, 3), Q(1, 3, 0), 3),
            ("max_mantissa", UQ(0b11111, 2, 3), Q(0, 3, 0), 3),
            ("drop_integer_bits", UQ(0b11011, 4, 1), Q(1, 4, 0), 3),
            ("integer_only", UQ(0b10111, 5, 0), Q(2, 3, 0), 3),
            ("fraction_only", UQ(0b10111, 0, 5), Q(0, 3, 0), 3),
            ("target_bits_one", UQ(0b111, 1, 2), Q(0, 2, 0), 1),
            ("guard_zero", UQ(0b1100, 2, 2), Q(6, 3, 0), 3),
            ("all_ones_round_up", UQ(0b111111, 3, 3), Q(3, 4, 0), 3),
            ("all_ones_round_down", UQ(0b111111, 3, 3), Q(3, 4, 0), 5),
            ("lsb_even_no_inc", UQ(0b100100, 3, 3), Q(2, 4, 0), 3),
            ("lsb_odd_inc", UQ(0b100110, 3, 3), Q(2, 4, 0), 3),
            ("round_bit_only", UQ(0b101000, 3, 3), Q(1, 3, 0), 3),
            ("sticky_only", UQ(0b100001, 3, 3), Q(1, 3, 0), 3),
            ("guard_round_sticky", UQ(0b111011, 3, 3), Q(1, 3, 0), 3),
            ("guard_only", UQ(0b100100, 2, 4), Q(1, 3, 0), 2),
            ("tiny_frac_round", UQ(0b11, 0, 2), Q(0, 2, 0), 1),
            ("tiny_int_round", UQ(0b11, 2, 0), Q(0, 2, 0), 1),
            ("carry_exact", UQ(0b1111, 2, 2), Q(2, 3, 0), 2),
            ("carry_large", UQ(0b111111, 3, 3), Q(2, 3, 0), 2),
            ("no_carry_round_up", UQ(0b101111, 3, 3), Q(2, 3, 0), 3),
            ("no_carry_round_down", UQ(0b101000, 3, 3), Q(2, 3, 0), 3),
            ("max_target_bits", UQ(0b10101, 2, 3), Q(1, 3, 0), 5),
            ("min_target_bits", UQ(0b10101, 2, 3), Q(1, 3, 0), 1),
            ("drop_all_frac", UQ(0b100101, 3, 3), Q(2, 3, 0), 3),
            ("keep_only_frac", UQ(0b100101, 3, 3), Q(2, 3, 0), 2),
            ("wide_int_narrow_target", UQ(0b1010101, 6, 1), Q(0, 4, 0), 3),
            ("wide_frac_narrow_target", UQ(0b1010101, 1, 6), Q(0, 4, 0), 3),
            ("power_of_two_exact", UQ(0b100000, 3, 3), Q(4, 4, 0), 3),
            ("half_ulp_tie_even", UQ(0b100100, 2, 4), Q(0, 3, 0), 2),
            ("half_ulp_tie_odd", UQ(0b100110, 2, 4), Q(0, 3, 0), 2),
            ("sticky_high_bit", UQ(0b101001, 3, 3), Q(0, 3, 0), 3),
            ("sticky_low_bit", UQ(0b1010001, 3, 4), Q(0, 3, 0), 3),
            ("guard_only_increment", UQ(0b101100, 3, 3), Q(0, 3, 0), 3),
            ("guard_only_no_increment", UQ(0b101000, 3, 3), Q(0, 3, 0), 3),
            ("bits_diff_1_guard0", UQ(0b1100, 2, 2), Q(1, 3, 0), 3),
            ("bits_diff_1_guard1_even", UQ(0b1110, 2, 2), Q(1, 3, 0), 3),
            ("bits_diff_1_guard1_odd", UQ(0b1111, 2, 2), Q(1, 3, 0), 3),
            ("bits_diff_2_round0", UQ(0b110000, 3, 3), Q(2, 3, 0), 4),
            ("bits_diff_2_round1", UQ(0b110100, 3, 3), Q(2, 3, 0), 4),
            ("bits_diff_2_tie_even", UQ(0b101000, 3, 3), Q(0, 3, 0), 4),
            ("bits_diff_2_tie_odd", UQ(0b101100, 3, 3), Q(0, 3, 0), 4),
            ("bits_diff_3_sticky0", UQ(0b1100000, 3, 4), Q(1, 3, 0), 4),
            ("bits_diff_3_sticky1", UQ(0b1100011, 3, 4), Q(1, 3, 0), 4),
            ("bits_diff_3_carry", UQ(0b1111111, 3, 4), Q(1, 3, 0), 4),
        ]

        rng = random.Random(2024)
        while len(cases) < 90:
            int_bits = rng.randint(0, 5)
            frac_bits = rng.randint(0, 5)
            if int_bits == 0 and frac_bits == 0:
                continue
            total_bits = int_bits + frac_bits
            target_bits = rng.randint(1, total_bits)
            val = rng.randint(0, (1 << total_bits) - 1)
            exp_int_bits = rng.randint(2, 6)
            exp_val = rng.randint(0, (1 << exp_int_bits) - 1)
            cases.append(
                (f"rand_{len(cases)}", UQ(val, int_bits, frac_bits), Q(exp_val, exp_int_bits, 0), target_bits)
            )
        return cases

    def test_rounding_matches_reference(self):
        cases = self._build_cases()
        self.assertEqual(len(cases), 90)
        for name, mantissa, exponent, target_bits in cases:
            with self.subTest(case=name, mantissa=mantissa, exponent=exponent, target_bits=target_bits):
                out_m, out_e = self._round(mantissa, exponent, target_bits)
                exp_m, exp_e = self._ref_round(mantissa, exponent, target_bits)
                self.assertEqual(out_m, exp_m)
                self.assertEqual(out_e.val, exp_e.val)


if __name__ == "__main__":
    unittest.main()
