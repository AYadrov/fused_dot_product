#include <cstdint>

#include "fp32_adder_ref.hpp"

extern "C" std::uint32_t fp32_adder_ref_dpi(std::uint32_t lhs_bits, std::uint32_t rhs_bits) {
    return fp32_adder_ref::reference_fp32_ieee_adder_bits(lhs_bits, rhs_bits);
}
