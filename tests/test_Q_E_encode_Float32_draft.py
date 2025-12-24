import unittest
import random

from fused_dot_product.utils.composites import Q_E_encode_Float32_draft
from fused_dot_product.utils.operators import Q_E_encode_Float32
from fused_dot_product.ast.AST import Const
from fused_dot_product.numtypes.RuntimeTypes import Q


def q_from_signed(value: int, int_bits: int, frac_bits: int = 0) -> Q:
    """Helper to build a signed Q value from a Python int using two's complement."""
    total_bits = int_bits + frac_bits
    mask = (1 << total_bits) - 1
    return Q(value & mask, int_bits, frac_bits)


class TestQEncodeFloat32Draft(unittest.TestCase):
    def _encode(self, enc_fn, mantissa: Q, exponent: Q):
        node = enc_fn(Const(mantissa), Const(exponent))
        try:
            return node.evaluate()
        except Exception as err:  # pragma: no cover - helps surface draft failures clearly
            self.fail(f"{enc_fn.__name__} raised {err!r} for mantissa={mantissa}, exponent={exponent}")

    def _build_cases(self):
        cases = [
            ("zero", q_from_signed(0, 4, 3), q_from_signed(0, 5, 0)),
            ("zero_with_exponent", q_from_signed(0, 4, 3), q_from_signed(16, 5, 0)),
            ("small_normal", q_from_signed(0b10100, 3, 2), q_from_signed(4, 5, 0)),
            ("negative_mantissa", q_from_signed(0b10100, 3, 2), q_from_signed(4, 5, 0)),
            ("large_exponent_inf", q_from_signed(0b10100, 3, 2), q_from_signed(200, 9, 0)),
            ("subnormal_shift", q_from_signed(0b00100, 3, 2), q_from_signed(5, 6, 0)),
            ("rounding_carry", q_from_signed(0b111111, 3, 3), q_from_signed(2, 6, 0)),
        ]

        rng = random.Random(2025)
        while len(cases) < 80:
            int_bits = rng.randint(1, 6)
            frac_bits = rng.randint(0, 6)
            total_bits = int_bits + frac_bits
            # Allow negative mantissas; limit magnitude to avoid constant sign overflow.
            max_mag = (1 << (int_bits - 1)) - 1
            m_val = rng.randint(-max_mag, max_mag)
            if m_val == 0:
                m_val = rng.choice([1, -1])
            mantissa = q_from_signed(m_val, int_bits, frac_bits)

            exp_bits = rng.randint(5, 9)
            exp_max = (1 << (exp_bits - 1)) - 1
            exponent = q_from_signed(rng.randint(-exp_max, exp_max), exp_bits, 0)
            cases.append((f"rand_{len(cases)}", mantissa, exponent))
        return cases

    def test_draft_matches_reference(self):
        for name, mantissa, exponent in self._build_cases():
            with self.subTest(case=name, mantissa=mantissa, exponent=exponent):
                ref = self._encode(Q_E_encode_Float32, mantissa, exponent)
                draft = self._encode(Q_E_encode_Float32_draft, mantissa, exponent)
                self.assertEqual(draft.val, ref.val, "Float32 bit pattern mismatch")


if __name__ == "__main__":
    unittest.main()
