import unittest
import random

from fused_dot_product.utils.composites import normalize_to_1_xxx_draft
from fused_dot_product.ast.AST import Const
from fused_dot_product.numtypes.RuntimeTypes import Q, UQ


class TestNormalizeTo1Draft(unittest.TestCase):
    """Sanity checks for the AST normalizer that should force mantissas to 1.xxxxx."""

    def _normalize(self, mantissa, exponent):
        node = normalize_to_1_xxx_draft(Const(mantissa), Const(exponent))
        try:
            result = node.evaluate()
        except AssertionError as err:
            self.fail(f"Normalization failed for mantissa={mantissa}, exponent={exponent}: {err}")
        return result.args

    def test_shifts_left_when_mantissa_too_small(self):
        # 0.75 -> shift left by 1, exponent decremented.
        m = UQ(3, 3, 2)  # 0b00011 == 0.75 with 2 fractional bits
        e = Q(4, 4, 0)  # exponent = 4
        norm_m, norm_e = self._normalize(m, e)
        self.assertAlmostEqual(norm_m.to_spec(), 1.5)
        self.assertAlmostEqual(norm_e.to_spec(), 3.0)
        self.assertAlmostEqual(norm_m.to_spec() * (2 ** norm_e.to_spec()), m.to_spec() * (2 ** e.to_spec()))

    def test_shifts_right_when_mantissa_too_large(self):
        # 3.0 -> shift right by 1, exponent incremented.
        m = UQ(6, 3, 1)  # 0b0110 == 3.0 with one fractional bit
        e = Q(4, 4, 0)  # exponent = 4
        norm_m, norm_e = self._normalize(m, e)
        self.assertAlmostEqual(norm_m.to_spec(), 1.5)
        self.assertAlmostEqual(norm_e.to_spec(), 5.0)
        self.assertAlmostEqual(norm_m.to_spec() * (2 ** norm_e.to_spec()), m.to_spec() * (2 ** e.to_spec()))

    def test_no_shift_when_already_normalized(self):
        # 1.0 stays as-is.
        m = UQ(5, 2, 2)  # 0b0101 == 1.25 with two fractional bits
        e = Q(6, 4, 0)  # exponent = 6
        norm_m, norm_e = self._normalize(m, e)
        self.assertAlmostEqual(norm_m.to_spec(), 1.25)
        self.assertAlmostEqual(norm_e.to_spec(), 6.0)
        self.assertAlmostEqual(norm_m.to_spec() * (2 ** norm_e.to_spec()), m.to_spec() * (2 ** e.to_spec()))

    def test_many_randomized_cases(self):
        """Broader sweep across bit-widths/values to catch edge cases."""
        def lzc(val: int, width: int) -> int:
            bits = f"{val:0{width}b}"
            return len(bits) - len(bits.lstrip("0"))
        
        def ref_normalize(m: UQ, e: Q) -> tuple[float, float]:
            width = m.int_bits + m.frac_bits
            lz = lzc(m.val, width)
            shift_amount = lz - m.int_bits + 1
            mag = abs(shift_amount)
            mask = (1 << width) - 1
            if shift_amount >= 0:
                new_m_val = (m.val << mag) & mask
                new_e_val = e.to_spec() - mag
            else:
                new_m_val = (m.val >> mag) & mask
                new_e_val = e.to_spec() + mag
            return float(new_m_val) / (2 ** m.frac_bits), float(new_e_val)
        
        rng = random.Random(1234)
        cases = []
        for _ in range(50):
            int_bits = rng.randint(1, 4)
            frac_bits = rng.randint(0, 4)
            width = int_bits + frac_bits
            max_val = (1 << width) - 1
            val = rng.randint(0, max_val)
            m = UQ(val, int_bits, frac_bits)
            # Keep exponents small and positive to avoid signed wraparound.
            e_val = rng.randint(0, (1 << 5) - 1)
            e = Q(e_val, 6, 0)
            cases.append((m, e))
        
        for m, e in cases:
            with self.subTest(m=m, e=e):
                norm_m, norm_e = self._normalize(m, e)
                exp_m, exp_e = ref_normalize(m, e)
                self.assertAlmostEqual(norm_m.to_spec(), exp_m)
                self.assertAlmostEqual(norm_e.to_spec(), exp_e)
                # If mantissa is non-zero, it should have exactly int_bits-1 leading zeros.
                width = m.int_bits + m.frac_bits
                if norm_m.val != 0:
                    self.assertEqual(lzc(norm_m.val, width), norm_m.int_bits - 1)
                else:
                    self.assertEqual(norm_m.to_spec(), 0.0)


if __name__ == "__main__":
    unittest.main()
