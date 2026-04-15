#pragma once
#include <array>
#include <cstdint>

static inline uint_fast8_t fp32_is_normal(uint_fast32_t arg_0) {  // fp32_is_normal
    const uint_fast8_t tmp = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_1 = uint_fast8_t((tmp != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_2 = uint_fast8_t((tmp == 255) & 1);  // basic_and_reduce
    const uint_fast8_t tmp_3 = uint_fast8_t(((~tmp_2) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_4 = uint_fast8_t((tmp_1 & tmp_3) & 1);  // basic_and
    return tmp_4;
}
static inline uint_fast8_t fp32_is_subnormal(uint_fast32_t arg_0) {  // fp32_is_subnormal
    const uint_fast8_t tmp_6 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_7 = uint_fast8_t((tmp_6 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_8 = uint_fast8_t(((~tmp_7) & 1) & 1);  // basic_invert
    const uint_fast32_t tmp_9 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_10 = uint_fast8_t((tmp_9 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_11 = uint_fast8_t((tmp_8 & tmp_10) & 1);  // basic_and
    return tmp_11;
}
static inline uint_fast8_t fp32_is_zero(uint_fast32_t arg_0) {  // fp32_is_zero
    const uint_fast8_t tmp_13 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_14 = uint_fast8_t((tmp_13 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_15 = uint_fast8_t(((~tmp_14) & 1) & 1);  // basic_invert
    const uint_fast32_t tmp_16 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_17 = uint_fast8_t((tmp_16 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_18 = uint_fast8_t(((~tmp_17) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_19 = uint_fast8_t((tmp_15 & tmp_18) & 1);  // basic_and
    return tmp_19;
}
static inline uint_fast8_t fp32_is_inf(uint_fast32_t arg_0) {  // fp32_is_inf
    const uint_fast8_t tmp_21 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_22 = uint_fast8_t((tmp_21 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_23 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_24 = uint_fast8_t((tmp_23 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_25 = uint_fast8_t(((~tmp_24) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_26 = uint_fast8_t((tmp_22 & tmp_25) & 1);  // basic_and
    return tmp_26;
}
static inline uint_fast8_t fp32_is_nan(uint_fast32_t arg_0) {  // fp32_is_nan
    const uint_fast8_t tmp_28 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_29 = uint_fast8_t((tmp_28 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_30 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_31 = uint_fast8_t((tmp_30 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_32 = uint_fast8_t((tmp_29 & tmp_31) & 1);  // basic_and
    return tmp_32;
}
static inline uint_fast8_t bit_and(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // bit_and
    const uint_fast8_t tmp_43 = uint_fast8_t((arg_0 & arg_1) & 1);  // basic_and
    return tmp_43;
}
static inline uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_60 = uint_fast32_t(((uint_fast64_t(uint_fast8_t(1 & 1)) << 23) | arg_0) & 16777215);  // basic_concat
    return tmp_60;
}
static inline uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_62 = uint_fast32_t(arg_0 & 16777215);  // basic_identity
    return tmp_62;
}
static inline uint_fast32_t if_then_else(uint_fast8_t arg_0, uint_fast32_t arg_1, uint_fast32_t arg_2) {  // if_then_else
    const uint_fast32_t tmp_64 = uint_fast32_t((arg_0 == 1 ? arg_1 : arg_2) & 16777215);  // basic_mux_2_1
    return tmp_64;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_66 = uint_fast32_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(3 & 3))) & 134217727);  // basic_lshift
    return tmp_66;
}
static inline uint_fast8_t if_then_else_1(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast8_t arg_2) {  // if_then_else
    const uint_fast8_t tmp_70 = uint_fast8_t((arg_0 == 1 ? arg_1 : arg_2) & 255);  // basic_mux_2_1
    return tmp_70;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_75 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast8_t tmp_76 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_77 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_75), static_cast<uint_fast64_t>(tmp_76)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_78 = uint_fast8_t(tmp_77[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_79 = uint_fast8_t(tmp_77[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_80 = uint_fast8_t((tmp_78 > tmp_79 ? tmp_78 : tmp_79) & 255);  // basic_max
    return tmp_80;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_82 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_83 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_84 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_82), static_cast<uint_fast64_t>(tmp_83)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_85 = uint_fast16_t(tmp_84[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_86 = uint_fast16_t(tmp_84[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_87 = uint_fast16_t((tmp_85 - tmp_86) & 511);  // basic_sub
    return tmp_87;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_89 = uint_fast32_t((arg_1 >= 27 ? 0 : (arg_0 >> arg_1)) & 134217727);  // basic_rshift
    return tmp_89;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_91 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_92 = uint_fast8_t(((~tmp_91) & 1) & 1);  // basic_invert
    return tmp_92;
}
static inline uint_fast8_t uq_ge(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_94 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_95 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_96 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_94), static_cast<uint_fast64_t>(tmp_95)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_97 = uint_fast16_t(tmp_96[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_98 = uint_fast16_t(tmp_96[1] & 511);  // _basic_get_item_1
    const uint_fast8_t tmp_99 = uint_fast8_t((tmp_97 >= tmp_98) & 1);  // basic_greater_or_equal
    return tmp_99;
}
static inline uint_fast16_t uq_sub_1(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_101 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_102 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_103 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_101), static_cast<uint_fast64_t>(tmp_102)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_104 = uint_fast16_t(tmp_103[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_105 = uint_fast16_t(tmp_103[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_106 = uint_fast16_t((tmp_104 - tmp_105) & 1023);  // basic_sub
    return tmp_106;
}
static inline uint_fast32_t uq_rshift_jam(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift_jam
    const uint_fast32_t tmp_90 = uq_rshift(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_93 = uq_is_zero(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_100 = uq_ge(arg_1, uint_fast8_t(27 & 31));  // uq_ge
    const uint_fast16_t tmp_107 = uq_sub_1(uint_fast8_t(27 & 31), arg_1);  // uq_sub
    const uint_fast32_t tmp_108 = uint_fast32_t((tmp_107 >= 64 ? 0 : (uint_fast64_t(arg_0) << tmp_107)) & 134217727);  // basic_lshift
    const uint_fast8_t tmp_109 = uint_fast8_t((tmp_108 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_110 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_111 = uint_fast8_t((tmp_100 == 1 ? tmp_110 : tmp_109) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_112 = uint_fast8_t((tmp_93 == 1 ? uint_fast8_t(0 & 1) : tmp_111) & 1);  // basic_mux_2_1
    const uint_fast32_t tmp_113 = uint_fast32_t((tmp_90 | tmp_112) & 134217727);  // basic_or
    return tmp_113;
}
static inline uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_115 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_116 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_117 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_115), static_cast<uint_fast64_t>(tmp_116)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_118 = uint_fast8_t(tmp_117[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_119 = uint_fast8_t(tmp_117[1] & 3);  // _basic_get_item_1
    const uint_fast8_t tmp_120 = uint_fast8_t((tmp_118 + tmp_119) & 3);  // basic_add
    return tmp_120;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_121 = uq_add(uint_fast8_t(1 & 1), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast32_t tmp_122 = uint_fast32_t(0 & 268435455);  // q_alloc
    const uint_fast32_t tmp_123 = uint_fast32_t(arg_0 & 268435455);  // basic_identity
    return tmp_123;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_125 = uint_fast8_t((arg_0 == 134217728) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_126 = uint_fast32_t(((~arg_0) & 268435455) & 268435455);  // basic_invert
    const uint_fast32_t tmp_127 = uint_fast32_t((tmp_126 + uint_fast8_t(1 & 1)) & 268435455);  // basic_add
    const uint_fast32_t tmp_128 = uint_fast32_t((arg_0 ^ arg_0) & 268435455);  // basic_xor
    const uint_fast32_t tmp_129 = uint_fast32_t(((~tmp_128) & 268435455) & 268435455);  // basic_invert
    const uint_fast32_t tmp_130 = uint_fast32_t((tmp_125 == 1 ? tmp_129 : tmp_127) & 268435455);  // basic_mux_2_1
    return tmp_130;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_131 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_132 = uint_fast32_t((arg_1 == 1 ? tmp_131 : arg_0) & 268435455);  // basic_mux_2_1
    return tmp_132;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_146 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    return tmp_146;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_147 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_148 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_147) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_149 = uint_fast8_t((tmp_148 - tmp_147) & 1);  // basic_sub
    const uint_fast32_t tmp_150 = uint_fast32_t(0 & 536870911);  // q_alloc
    const uint_fast32_t tmp_151 = uint_fast32_t(((uint_fast64_t(tmp_149) << 28) | arg_0) & 536870911);  // basic_concat
    return tmp_151;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_145 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 268435455);  // basic_lshift
    const uint_fast32_t tmp_152 = q_sign_extend(tmp_145);  // q_sign_extend
    const uint_fast32_t tmp_153 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 268435455);  // basic_lshift
    const uint_fast32_t tmp_154 = q_sign_extend(tmp_153);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_155 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_152), static_cast<uint_fast64_t>(tmp_154)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_156 = uint_fast32_t(tmp_155[0] & 536870911);  // _basic_get_item_0
    const uint_fast32_t tmp_157 = uint_fast32_t(tmp_155[1] & 536870911);  // _basic_get_item_1
    const uint_fast32_t tmp_158 = uint_fast32_t((tmp_156 + tmp_157) & 536870911);  // basic_add
    return tmp_158;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_160 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    return tmp_160;
}
static inline uint_fast8_t if_then_else_2(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast8_t arg_2) {  // if_then_else
    const uint_fast8_t tmp_162 = uint_fast8_t((arg_0 == 1 ? arg_1 : arg_2) & 1);  // basic_mux_2_1
    return tmp_162;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_164 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_165 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_166 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_164), static_cast<uint_fast64_t>(tmp_165)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_167 = uint_fast8_t(tmp_166[0] & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_168 = uint_fast8_t(tmp_166[1] & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_169 = uint_fast8_t((tmp_167 + tmp_168) & 31);  // basic_add
    return tmp_169;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_170 = uq_add_1(uint_fast8_t(8 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_171 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_172 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_172;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_175 = uint_fast8_t((arg_0 == 268435456) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_176 = uint_fast32_t(((~arg_0) & 536870911) & 536870911);  // basic_invert
    const uint_fast32_t tmp_177 = uint_fast32_t((tmp_176 + uint_fast8_t(1 & 1)) & 536870911);  // basic_add
    const uint_fast32_t tmp_178 = uint_fast32_t((arg_0 ^ arg_0) & 536870911);  // basic_xor
    const uint_fast32_t tmp_179 = uint_fast32_t(((~tmp_178) & 536870911) & 536870911);  // basic_invert
    const uint_fast32_t tmp_180 = uint_fast32_t((tmp_175 == 1 ? tmp_179 : tmp_177) & 536870911);  // basic_mux_2_1
    return tmp_180;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_181 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_182 = uint_fast32_t((arg_1 == 1 ? tmp_181 : arg_0) & 536870911);  // basic_mux_2_1
    return tmp_182;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_174 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_183 = q_add_sign_1(arg_0, tmp_174);  // q_add_sign
    return tmp_183;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_185 = uint_fast32_t(arg_0 & 268435455);  // basic_identity
    return tmp_185;
}
static inline uint_fast8_t bit_xor(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // bit_xor
    const uint_fast8_t tmp_190 = uint_fast8_t((arg_0 ^ arg_1) & 1);  // basic_xor
    return tmp_190;
}
static inline uint_fast8_t bit_or(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // bit_or
    const uint_fast8_t tmp_195 = uint_fast8_t((arg_0 | arg_1) & 1);  // basic_or
    return tmp_195;
}
static inline uint_fast8_t bit_neg(uint_fast8_t arg_0) {  // bit_neg
    const uint_fast8_t tmp_198 = uint_fast8_t(((~arg_0) & 1) & 1);  // basic_invert
    return tmp_198;
}
static inline uint_fast32_t if_then_else_3(uint_fast8_t arg_0, uint_fast32_t arg_1, uint_fast32_t arg_2) {  // if_then_else
    const uint_fast32_t tmp_202 = uint_fast32_t((arg_0 == 1 ? arg_1 : arg_2) & 4294967295);  // basic_mux_2_1
    return tmp_202;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_204 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_205 = uint_fast8_t(((~tmp_204) & 1) & 1);  // basic_invert
    return tmp_205;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_208 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_209 = uint_fast8_t(((~tmp_208) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_210 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_209) & 1);  // basic_and
    const uint_fast8_t tmp_211 = uint_fast8_t((uint_fast8_t(0 & 31) + tmp_210) & 31);  // basic_add
    const uint_fast8_t tmp_212 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_213 = uint_fast8_t(((~tmp_212) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_214 = uint_fast8_t((tmp_210 & tmp_213) & 1);  // basic_and
    const uint_fast8_t tmp_215 = uint_fast8_t((tmp_211 + tmp_214) & 31);  // basic_add
    const uint_fast8_t tmp_216 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_217 = uint_fast8_t(((~tmp_216) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_218 = uint_fast8_t((tmp_214 & tmp_217) & 1);  // basic_and
    const uint_fast8_t tmp_219 = uint_fast8_t((tmp_215 + tmp_218) & 31);  // basic_add
    const uint_fast8_t tmp_220 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_221 = uint_fast8_t(((~tmp_220) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_222 = uint_fast8_t((tmp_218 & tmp_221) & 1);  // basic_and
    const uint_fast8_t tmp_223 = uint_fast8_t((tmp_219 + tmp_222) & 31);  // basic_add
    const uint_fast8_t tmp_224 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_225 = uint_fast8_t(((~tmp_224) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_226 = uint_fast8_t((tmp_222 & tmp_225) & 1);  // basic_and
    const uint_fast8_t tmp_227 = uint_fast8_t((tmp_223 + tmp_226) & 31);  // basic_add
    const uint_fast8_t tmp_228 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_229 = uint_fast8_t(((~tmp_228) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_230 = uint_fast8_t((tmp_226 & tmp_229) & 1);  // basic_and
    const uint_fast8_t tmp_231 = uint_fast8_t((tmp_227 + tmp_230) & 31);  // basic_add
    const uint_fast8_t tmp_232 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_233 = uint_fast8_t(((~tmp_232) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_234 = uint_fast8_t((tmp_230 & tmp_233) & 1);  // basic_and
    const uint_fast8_t tmp_235 = uint_fast8_t((tmp_231 + tmp_234) & 31);  // basic_add
    const uint_fast8_t tmp_236 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_237 = uint_fast8_t(((~tmp_236) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_238 = uint_fast8_t((tmp_234 & tmp_237) & 1);  // basic_and
    const uint_fast8_t tmp_239 = uint_fast8_t((tmp_235 + tmp_238) & 31);  // basic_add
    const uint_fast8_t tmp_240 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_241 = uint_fast8_t(((~tmp_240) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_242 = uint_fast8_t((tmp_238 & tmp_241) & 1);  // basic_and
    const uint_fast8_t tmp_243 = uint_fast8_t((tmp_239 + tmp_242) & 31);  // basic_add
    const uint_fast8_t tmp_244 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_245 = uint_fast8_t(((~tmp_244) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_246 = uint_fast8_t((tmp_242 & tmp_245) & 1);  // basic_and
    const uint_fast8_t tmp_247 = uint_fast8_t((tmp_243 + tmp_246) & 31);  // basic_add
    const uint_fast8_t tmp_248 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_249 = uint_fast8_t(((~tmp_248) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_250 = uint_fast8_t((tmp_246 & tmp_249) & 1);  // basic_and
    const uint_fast8_t tmp_251 = uint_fast8_t((tmp_247 + tmp_250) & 31);  // basic_add
    const uint_fast8_t tmp_252 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_253 = uint_fast8_t(((~tmp_252) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_254 = uint_fast8_t((tmp_250 & tmp_253) & 1);  // basic_and
    const uint_fast8_t tmp_255 = uint_fast8_t((tmp_251 + tmp_254) & 31);  // basic_add
    const uint_fast8_t tmp_256 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_257 = uint_fast8_t(((~tmp_256) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_258 = uint_fast8_t((tmp_254 & tmp_257) & 1);  // basic_and
    const uint_fast8_t tmp_259 = uint_fast8_t((tmp_255 + tmp_258) & 31);  // basic_add
    const uint_fast8_t tmp_260 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_261 = uint_fast8_t(((~tmp_260) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_262 = uint_fast8_t((tmp_258 & tmp_261) & 1);  // basic_and
    const uint_fast8_t tmp_263 = uint_fast8_t((tmp_259 + tmp_262) & 31);  // basic_add
    const uint_fast8_t tmp_264 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_265 = uint_fast8_t(((~tmp_264) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_266 = uint_fast8_t((tmp_262 & tmp_265) & 1);  // basic_and
    const uint_fast8_t tmp_267 = uint_fast8_t((tmp_263 + tmp_266) & 31);  // basic_add
    const uint_fast8_t tmp_268 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_269 = uint_fast8_t(((~tmp_268) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_270 = uint_fast8_t((tmp_266 & tmp_269) & 1);  // basic_and
    const uint_fast8_t tmp_271 = uint_fast8_t((tmp_267 + tmp_270) & 31);  // basic_add
    const uint_fast8_t tmp_272 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_273 = uint_fast8_t(((~tmp_272) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_274 = uint_fast8_t((tmp_270 & tmp_273) & 1);  // basic_and
    const uint_fast8_t tmp_275 = uint_fast8_t((tmp_271 + tmp_274) & 31);  // basic_add
    const uint_fast8_t tmp_276 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_277 = uint_fast8_t(((~tmp_276) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_278 = uint_fast8_t((tmp_274 & tmp_277) & 1);  // basic_and
    const uint_fast8_t tmp_279 = uint_fast8_t((tmp_275 + tmp_278) & 31);  // basic_add
    const uint_fast8_t tmp_280 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_281 = uint_fast8_t(((~tmp_280) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_282 = uint_fast8_t((tmp_278 & tmp_281) & 1);  // basic_and
    const uint_fast8_t tmp_283 = uint_fast8_t((tmp_279 + tmp_282) & 31);  // basic_add
    const uint_fast8_t tmp_284 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_285 = uint_fast8_t(((~tmp_284) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_286 = uint_fast8_t((tmp_282 & tmp_285) & 1);  // basic_and
    const uint_fast8_t tmp_287 = uint_fast8_t((tmp_283 + tmp_286) & 31);  // basic_add
    const uint_fast8_t tmp_288 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_289 = uint_fast8_t(((~tmp_288) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_290 = uint_fast8_t((tmp_286 & tmp_289) & 1);  // basic_and
    const uint_fast8_t tmp_291 = uint_fast8_t((tmp_287 + tmp_290) & 31);  // basic_add
    const uint_fast8_t tmp_292 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_293 = uint_fast8_t(((~tmp_292) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_294 = uint_fast8_t((tmp_290 & tmp_293) & 1);  // basic_and
    const uint_fast8_t tmp_295 = uint_fast8_t((tmp_291 + tmp_294) & 31);  // basic_add
    const uint_fast8_t tmp_296 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_297 = uint_fast8_t(((~tmp_296) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_298 = uint_fast8_t((tmp_294 & tmp_297) & 1);  // basic_and
    const uint_fast8_t tmp_299 = uint_fast8_t((tmp_295 + tmp_298) & 31);  // basic_add
    const uint_fast8_t tmp_300 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_301 = uint_fast8_t(((~tmp_300) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_302 = uint_fast8_t((tmp_298 & tmp_301) & 1);  // basic_and
    const uint_fast8_t tmp_303 = uint_fast8_t((tmp_299 + tmp_302) & 31);  // basic_add
    const uint_fast8_t tmp_304 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_305 = uint_fast8_t(((~tmp_304) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_306 = uint_fast8_t((tmp_302 & tmp_305) & 1);  // basic_and
    const uint_fast8_t tmp_307 = uint_fast8_t((tmp_303 + tmp_306) & 31);  // basic_add
    const uint_fast8_t tmp_308 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_309 = uint_fast8_t(((~tmp_308) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_310 = uint_fast8_t((tmp_306 & tmp_309) & 1);  // basic_and
    const uint_fast8_t tmp_311 = uint_fast8_t((tmp_307 + tmp_310) & 31);  // basic_add
    const uint_fast8_t tmp_312 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_313 = uint_fast8_t(((~tmp_312) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_314 = uint_fast8_t((tmp_310 & tmp_313) & 1);  // basic_and
    const uint_fast8_t tmp_315 = uint_fast8_t((tmp_311 + tmp_314) & 31);  // basic_add
    const uint_fast8_t tmp_316 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_317 = uint_fast8_t(((~tmp_316) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_318 = uint_fast8_t((tmp_314 & tmp_317) & 1);  // basic_and
    const uint_fast8_t tmp_319 = uint_fast8_t((tmp_315 + tmp_318) & 31);  // basic_add
    return tmp_319;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_321 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_322 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_323 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_321), static_cast<uint_fast64_t>(tmp_322)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_324 = uint_fast8_t(tmp_323[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_325 = uint_fast8_t(tmp_323[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_326 = uint_fast8_t((tmp_324 + tmp_325) & 15);  // basic_add
    return tmp_326;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_327 = uq_add_2(uint_fast8_t(5 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_328 = uint_fast8_t(0 & 63);  // q_alloc
    const uint_fast8_t tmp_329 = uint_fast8_t(arg_0 & 63);  // basic_identity
    return tmp_329;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_331 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_332 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_333 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_331), static_cast<uint_fast64_t>(tmp_332)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_334 = uint_fast8_t(tmp_333[0] & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_335 = uint_fast8_t(tmp_333[1] & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_336 = uint_fast8_t((tmp_334 + tmp_335) & 7);  // basic_add
    return tmp_336;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_337 = uq_add_3(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_338 = uint_fast8_t(0 & 7);  // q_alloc
    const uint_fast8_t tmp_339 = uint_fast8_t(arg_0 & 7);  // basic_identity
    return tmp_339;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_342 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    return tmp_342;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_343 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_344 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_343) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_345 = uint_fast8_t((tmp_344 - tmp_343) & 1);  // basic_sub
    const uint_fast8_t tmp_346 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_347 = uint_fast8_t(((uint_fast64_t(tmp_345) << 6) | arg_0) & 127);  // basic_concat
    return tmp_347;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_350 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    return tmp_350;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_351 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_352 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_351) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_353 = uint_fast8_t((tmp_352 - tmp_351) & 15);  // basic_sub
    const uint_fast8_t tmp_354 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_355 = uint_fast8_t(((uint_fast64_t(tmp_353) << 3) | arg_0) & 127);  // basic_concat
    return tmp_355;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_341 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast8_t tmp_348 = q_sign_extend_1(tmp_341);  // q_sign_extend
    const uint_fast8_t tmp_349 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_356 = q_sign_extend_2(tmp_349);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_357 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_348), static_cast<uint_fast64_t>(tmp_356)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_358 = uint_fast8_t(tmp_357[0] & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_359 = uint_fast8_t(tmp_357[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_360 = uint_fast8_t((tmp_358 - tmp_359) & 127);  // basic_sub
    return tmp_360;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_363 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_363;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_364 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_365 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_364) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_366 = uint_fast8_t((tmp_365 - tmp_364) & 1);  // basic_sub
    const uint_fast8_t tmp_367 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_368 = uint_fast8_t(((uint_fast64_t(tmp_366) << 7) | arg_0) & 255);  // basic_concat
    return tmp_368;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_371 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_371;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_372 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_373 = uint_fast8_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_372) << uint_fast8_t(6 & 7))) & 127);  // basic_lshift
    const uint_fast8_t tmp_374 = uint_fast8_t((tmp_373 - tmp_372) & 63);  // basic_sub
    const uint_fast8_t tmp_375 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_376 = uint_fast8_t(((uint_fast64_t(tmp_374) << 2) | arg_0) & 255);  // basic_concat
    return tmp_376;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_362 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_369 = q_sign_extend_3(tmp_362);  // q_sign_extend
    const uint_fast8_t tmp_370 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_377 = q_sign_extend_4(tmp_370);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_378 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_369), static_cast<uint_fast64_t>(tmp_377)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_379 = uint_fast8_t(tmp_378[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_380 = uint_fast8_t(tmp_378[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_381 = uint_fast8_t((tmp_379 + tmp_380) & 255);  // basic_add
    return tmp_381;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_383 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_383;
}
static inline uint_fast32_t uq_resize_2(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_385 = uint_fast32_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(1 & 1))) & 536870911);  // basic_lshift
    return tmp_385;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_388 = uint_fast8_t((arg_0 == 128) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_389 = uint_fast8_t(((~arg_0) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_390 = uint_fast8_t((tmp_389 + uint_fast8_t(1 & 1)) & 255);  // basic_add
    const uint_fast8_t tmp_391 = uint_fast8_t((arg_0 ^ arg_0) & 255);  // basic_xor
    const uint_fast8_t tmp_392 = uint_fast8_t(((~tmp_391) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_393 = uint_fast8_t((tmp_388 == 1 ? tmp_392 : tmp_390) & 255);  // basic_mux_2_1
    return tmp_393;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_394 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_395 = uint_fast8_t((arg_1 == 1 ? tmp_394 : arg_0) & 255);  // basic_mux_2_1
    return tmp_395;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_387 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_396 = q_add_sign_2(arg_0, tmp_387);  // q_add_sign
    return tmp_396;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_398 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_398;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_400 = uint_fast32_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 536870911);  // basic_lshift
    return tmp_400;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_402 = uint_fast32_t((arg_1 >= 29 ? 0 : (arg_0 >> arg_1)) & 536870911);  // basic_rshift
    return tmp_402;
}
static inline uint_fast8_t uq_is_zero_2(uint_fast8_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_404 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_405 = uint_fast8_t(((~tmp_404) & 1) & 1);  // basic_invert
    return tmp_405;
}
static inline uint_fast8_t uq_ge_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_407 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_408 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_409 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_407), static_cast<uint_fast64_t>(tmp_408)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_410 = uint_fast8_t(tmp_409[0] & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_411 = uint_fast8_t(tmp_409[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_412 = uint_fast8_t((tmp_410 >= tmp_411) & 1);  // basic_greater_or_equal
    return tmp_412;
}
static inline uint_fast8_t uq_sub_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_414 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast8_t tmp_415 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_416 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_414), static_cast<uint_fast64_t>(tmp_415)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_417 = uint_fast8_t(tmp_416[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_418 = uint_fast8_t(tmp_416[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_419 = uint_fast8_t((tmp_417 - tmp_418) & 255);  // basic_sub
    return tmp_419;
}
static inline uint_fast32_t uq_rshift_jam_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift_jam
    const uint_fast32_t tmp_403 = uq_rshift_1(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_406 = uq_is_zero_2(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_413 = uq_ge_1(arg_1, uint_fast8_t(29 & 31));  // uq_ge
    const uint_fast8_t tmp_420 = uq_sub_2(uint_fast8_t(29 & 31), arg_1);  // uq_sub
    const uint_fast32_t tmp_421 = uint_fast32_t((tmp_420 >= 64 ? 0 : (uint_fast64_t(arg_0) << tmp_420)) & 536870911);  // basic_lshift
    const uint_fast8_t tmp_422 = uint_fast8_t((tmp_421 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_423 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_424 = uint_fast8_t((tmp_413 == 1 ? tmp_423 : tmp_422) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_425 = uint_fast8_t((tmp_406 == 1 ? uint_fast8_t(0 & 1) : tmp_424) & 1);  // basic_mux_2_1
    const uint_fast32_t tmp_426 = uint_fast32_t((tmp_403 | tmp_425) & 536870911);  // basic_or
    return tmp_426;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_430 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_430;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_431 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_432 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_431) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_433 = uint_fast8_t((tmp_432 - tmp_431) & 1);  // basic_sub
    const uint_fast16_t tmp_434 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_435 = uint_fast16_t(((uint_fast64_t(tmp_433) << 9) | arg_0) & 1023);  // basic_concat
    return tmp_435;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_438 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_439 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_438) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_440 = uint_fast8_t((tmp_439 - tmp_438) & 3);  // basic_sub
    const uint_fast16_t tmp_441 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_442 = uint_fast16_t(((uint_fast64_t(tmp_440) << 8) | arg_0) & 1023);  // basic_concat
    return tmp_442;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_429 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_436 = q_sign_extend_5(tmp_429);  // q_sign_extend
    const uint_fast8_t tmp_437 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_443 = q_sign_extend_6(tmp_437);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_444 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_436), static_cast<uint_fast64_t>(tmp_443)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_445 = uint_fast16_t(tmp_444[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_446 = uint_fast16_t(tmp_444[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_447 = uint_fast16_t((tmp_445 - tmp_446) & 1023);  // basic_sub
    return tmp_447;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_449 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_450 = q_sign_extend_5(tmp_449);  // q_sign_extend
    const uint_fast8_t tmp_451 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_452 = q_sign_extend_6(tmp_451);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_453 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_450), static_cast<uint_fast64_t>(tmp_452)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_454 = uint_fast16_t(tmp_453[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_455 = uint_fast16_t(tmp_453[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_456 = uint_fast16_t((tmp_454 + tmp_455) & 1023);  // basic_add
    return tmp_456;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_463 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_464 = uint_fast8_t(((~tmp_463) & 1) & 1);  // basic_invert
    return tmp_464;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_466 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_466;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_470 = uint_fast8_t((arg_0 == 512) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_471 = uint_fast16_t(((~arg_0) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_472 = uint_fast16_t((tmp_471 + uint_fast8_t(1 & 1)) & 1023);  // basic_add
    const uint_fast16_t tmp_473 = uint_fast16_t((arg_0 ^ arg_0) & 1023);  // basic_xor
    const uint_fast16_t tmp_474 = uint_fast16_t(((~tmp_473) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_475 = uint_fast16_t((tmp_470 == 1 ? tmp_474 : tmp_472) & 1023);  // basic_mux_2_1
    return tmp_475;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_476 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_477 = uint_fast16_t((arg_1 == 1 ? tmp_476 : arg_0) & 1023);  // basic_mux_2_1
    return tmp_477;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_469 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_478 = q_add_sign_3(arg_0, tmp_469);  // q_add_sign
    return tmp_478;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_480 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_480;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_482 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_483 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_484 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_482), static_cast<uint_fast64_t>(tmp_483)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_485 = uint_fast16_t(tmp_484[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_486 = uint_fast16_t(tmp_484[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_487 = uint_fast16_t((tmp_485 + tmp_486) & 1023);  // basic_add
    return tmp_487;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_490 = uint_fast64_t((arg_1 >= 38 ? 0 : (arg_0 >> arg_1)) & 274877906943);  // basic_rshift
    return tmp_490;
}
static inline uint_fast8_t uq_is_zero_3(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_492 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_493 = uint_fast8_t(((~tmp_492) & 1) & 1);  // basic_invert
    return tmp_493;
}
static inline uint_fast8_t uq_ge_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_495 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_496 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_497 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_495), static_cast<uint_fast64_t>(tmp_496)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_498 = uint_fast16_t(tmp_497[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_499 = uint_fast16_t(tmp_497[1] & 1023);  // _basic_get_item_1
    const uint_fast8_t tmp_500 = uint_fast8_t((tmp_498 >= tmp_499) & 1);  // basic_greater_or_equal
    return tmp_500;
}
static inline uint_fast16_t uq_sub_3(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_502 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const uint_fast16_t tmp_503 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_504 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_502), static_cast<uint_fast64_t>(tmp_503)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_505 = uint_fast16_t(tmp_504[0] & 2047);  // _basic_get_item_0
    const uint_fast16_t tmp_506 = uint_fast16_t(tmp_504[1] & 2047);  // _basic_get_item_1
    const uint_fast16_t tmp_507 = uint_fast16_t((tmp_505 - tmp_506) & 2047);  // basic_sub
    return tmp_507;
}
static inline uint_fast64_t uq_rshift_jam_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift_jam
    const uint_fast64_t tmp_491 = uq_rshift_2(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_494 = uq_is_zero_3(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_501 = uq_ge_2(arg_1, uint_fast8_t(38 & 63));  // uq_ge
    const uint_fast16_t tmp_508 = uq_sub_3(uint_fast8_t(38 & 63), arg_1);  // uq_sub
    const uint_fast64_t tmp_509 = uint_fast64_t((tmp_508 >= 64 ? 0 : (uint_fast64_t(arg_0) << tmp_508)) & 274877906943);  // basic_lshift
    const uint_fast8_t tmp_510 = uint_fast8_t((tmp_509 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_511 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_512 = uint_fast8_t((tmp_501 == 1 ? tmp_511 : tmp_510) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_513 = uint_fast8_t((tmp_494 == 1 ? uint_fast8_t(0 & 1) : tmp_512) & 1);  // basic_mux_2_1
    const uint_fast64_t tmp_514 = uint_fast64_t((tmp_491 | tmp_513) & 274877906943);  // basic_or
    return tmp_514;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_519 = uint_fast64_t(((arg_0 >> 0) & 137438953471) & 137438953471);  // basic_select
    return tmp_519;
}
static inline uint_fast32_t uq_resize_3(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_523 = uint_fast32_t((uint_fast8_t(14 & 15) >= 37 ? 0 : (arg_0 >> uint_fast8_t(14 & 15))) & 8388607);  // basic_rshift
    return tmp_523;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_534 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_535 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_536 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_534), static_cast<uint_fast64_t>(tmp_535)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_537 = uint_fast32_t(tmp_536[0] & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_538 = uint_fast32_t(tmp_536[1] & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_539 = uint_fast32_t((tmp_537 + tmp_538) & 16777215);  // basic_add
    return tmp_539;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_546 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_547 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_548 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_546), static_cast<uint_fast64_t>(tmp_547)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_549 = uint_fast16_t(tmp_548[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_550 = uint_fast16_t(tmp_548[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_551 = uint_fast16_t((tmp_549 + tmp_550) & 1023);  // basic_add
    return tmp_551;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_560 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_561 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_562 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_560), static_cast<uint_fast64_t>(tmp_561)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_563 = uint_fast16_t(tmp_562[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_564 = uint_fast16_t(tmp_562[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_565 = uint_fast16_t((tmp_563 < tmp_564 ? tmp_563 : tmp_564) & 1023);  // basic_min
    return tmp_565;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_574 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_574;
}
static inline uint_fast32_t fp32_encode(uint_fast8_t arg_0, uint_fast16_t arg_1, uint_fast32_t arg_2, uint_fast8_t arg_3, uint_fast8_t arg_4) {  // fp32_encode
    const uint_fast32_t tmp_203 = if_then_else_3(arg_0, uint_fast32_t(4286578688 & 4294967295), uint_fast32_t(2139095040 & 4294967295));  // if_then_else
    const uint_fast8_t tmp_206 = uq_is_zero_1(arg_2);  // uq_is_zero
    const uint_fast32_t tmp_207 = if_then_else_3(arg_0, uint_fast32_t(2147483648 & 4294967295), uint_fast32_t(0 & 4294967295));  // if_then_else
    // begin inline primitive normalize_to_1_xxx
    const uint_fast8_t tmp_320 = lzc(arg_2);  // lzc
    const uint_fast8_t tmp_330 = uq_to_q_2(tmp_320);  // uq_to_q
    const uint_fast8_t tmp_340 = uq_to_q_3(uint_fast8_t(2 & 3));  // uq_to_q
    const uint_fast8_t tmp_361 = q_sub(tmp_330, tmp_340);  // q_sub
    const uint_fast8_t tmp_382 = q_add_1(tmp_361, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_384 = q_sign_bit_6(tmp_382);  // q_sign_bit
    const uint_fast32_t tmp_386 = uq_resize_2(arg_2);  // uq_resize
    const uint_fast8_t tmp_397 = q_abs_1(tmp_382);  // q_abs
    const uint_fast8_t tmp_399 = q_to_uq_1(tmp_397);  // q_to_uq
    const uint_fast32_t tmp_401 = uq_lshift(tmp_386, tmp_399);  // uq_lshift
    const uint_fast32_t tmp_427 = uq_rshift_jam_1(tmp_386, tmp_399);  // uq_rshift_jam
    const uint_fast32_t tmp_428 = uint_fast32_t((tmp_384 == 1 ? tmp_427 : tmp_401) & 268435455);  // basic_mux_2_1
    const uint_fast16_t tmp_448 = q_sub_1(arg_1, tmp_397);  // q_sub
    const uint_fast16_t tmp_457 = q_add_2(arg_1, tmp_397);  // q_add
    const uint_fast16_t tmp_458 = uint_fast16_t((tmp_384 == 1 ? tmp_457 : tmp_448) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_459 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_428), static_cast<uint_fast64_t>(tmp_458)};  // basic_tuple_maker_2
    // end inline primitive normalize_to_1_xxx
    const uint_fast32_t tmp_460 = uint_fast32_t(tmp_459[0] & 268435455);  // _basic_get_item_0
    const uint_fast16_t tmp_461 = uint_fast16_t(tmp_459[1] & 1023);  // _basic_get_item_1
    // begin inline primitive shift_if_subnormal
    const uint_fast64_t tmp_462 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_460) << uint_fast8_t(10 & 15))) & 274877906943);  // basic_lshift
    const uint_fast8_t tmp_465 = q_is_zero(tmp_461);  // q_is_zero
    const uint_fast8_t tmp_467 = q_sign_bit_8(tmp_461);  // q_sign_bit
    const uint_fast8_t tmp_468 = uint_fast8_t((tmp_465 | tmp_467) & 1);  // basic_or
    const uint_fast16_t tmp_479 = q_abs_2(tmp_461);  // q_abs
    const uint_fast16_t tmp_481 = q_to_uq_2(tmp_479);  // q_to_uq
    const uint_fast16_t tmp_488 = uq_add_4(uint_fast8_t(1 & 1), tmp_481);  // uq_add
    const uint_fast16_t tmp_489 = uint_fast16_t((tmp_468 == 1 ? tmp_488 : uint_fast8_t(0 & 1)) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_515 = uq_rshift_jam_2(tmp_462, tmp_489);  // uq_rshift_jam
    const uint_fast16_t tmp_516 = uint_fast16_t((tmp_468 == 1 ? uint_fast8_t(0 & 1) : tmp_481) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_517 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_515), static_cast<uint_fast64_t>(tmp_516)};  // basic_tuple_maker_2
    // end inline primitive shift_if_subnormal
    const uint_fast64_t tmp_518 = uint_fast64_t(tmp_517[0] & 274877906943);  // _basic_get_item_0
    const uint_fast64_t tmp_520 = drop_implicit_bit(tmp_518);  // drop_implicit_bit
    const uint_fast16_t tmp_521 = uint_fast16_t(tmp_517[1] & 511);  // _basic_get_item_1
    // begin inline primitive round_mantissa
    const uint_fast8_t tmp_522 = uq_is_zero(tmp_521);  // uq_is_zero
    // begin inline primitive uq_RNE_IEEE
    const uint_fast32_t tmp_524 = uq_resize_3(tmp_520);  // uq_resize
    const uint_fast8_t tmp_525 = uint_fast8_t(((tmp_520 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_526 = uint_fast8_t(((tmp_520 >> 12) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_527 = uint_fast16_t(((tmp_520 >> 0) & 4095) & 4095);  // basic_select
    const uint_fast8_t tmp_528 = uint_fast8_t((tmp_527 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_529 = uint_fast8_t((tmp_526 | tmp_528) & 1);  // basic_or
    const uint_fast8_t tmp_530 = uint_fast8_t(((tmp_520 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_531 = uint_fast8_t((tmp_529 | tmp_530) & 1);  // basic_or
    const uint_fast8_t tmp_532 = uint_fast8_t((tmp_525 & tmp_531) & 1);  // basic_and
    const uint_fast32_t tmp_533 = uint_fast32_t(tmp_532 & 8388607);  // basic_identity
    const uint_fast32_t tmp_540 = uq_add_5(tmp_524, tmp_533);  // uq_add
    const uint_fast8_t tmp_541 = uint_fast8_t((tmp_524 == 8388607) & 1);  // basic_and_reduce
    const uint_fast8_t tmp_542 = uint_fast8_t((tmp_541 & tmp_532) & 1);  // basic_and
    const uint_fast32_t tmp_543 = uint_fast32_t((tmp_542 >= 24 ? 0 : (tmp_540 >> tmp_542)) & 8388607);  // basic_rshift
    const std::array<uint_fast64_t, 2> tmp_544 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_543), static_cast<uint_fast64_t>(tmp_542)};  // basic_tuple_maker_2
    // end inline primitive uq_RNE_IEEE
    const uint_fast8_t tmp_545 = uint_fast8_t(tmp_544[1] & 1);  // _basic_get_item_1
    const uint_fast16_t tmp_552 = uq_add_6(tmp_521, tmp_545);  // uq_add
    const uint_fast8_t tmp_553 = uint_fast8_t((tmp_552 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_554 = uint_fast8_t((tmp_522 & tmp_553) & 1);  // basic_and
    const uint_fast32_t tmp_555 = uint_fast32_t(tmp_544[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_556 = uint_fast32_t((tmp_554 == 1 ? uint_fast8_t(0 & 1) : tmp_555) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_557 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_556), static_cast<uint_fast64_t>(tmp_552)};  // basic_tuple_maker_2
    // end inline primitive round_mantissa
    const uint_fast32_t tmp_558 = uint_fast32_t(tmp_557[0] & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_559 = uint_fast16_t(tmp_557[1] & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_566 = uq_min(tmp_559, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_567 = uint_fast8_t(tmp_566 & 255);  // basic_identity
    const uint_fast8_t tmp_568 = uint_fast8_t((tmp_567 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_569 = uint_fast32_t((tmp_568 == 1 ? uint_fast8_t(0 & 1) : tmp_558) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_570 = uint_fast32_t(tmp_569 & 8388607);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_571 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_570), static_cast<uint_fast64_t>(tmp_567)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_572 = uint_fast8_t(tmp_571[1] & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_573 = uint_fast32_t(tmp_571[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_575 = fp32_pack(arg_0, tmp_572, tmp_573);  // fp32_pack
    const uint_fast32_t tmp_576 = if_then_else_3(tmp_206, tmp_207, tmp_575);  // if_then_else
    const uint_fast32_t tmp_577 = if_then_else_3(arg_4, tmp_203, tmp_576);  // if_then_else
    const uint_fast32_t tmp_578 = if_then_else_3(arg_3, uint_fast32_t(2139095041 & 4294967295), tmp_577);  // if_then_else
    return tmp_578;
}
static inline uint_fast32_t FP32_IEEE_adder_impl(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // FP32_IEEE_adder
    // begin inline composite fp32_classify
    const uint_fast8_t tmp_5 = fp32_is_normal(arg_0);  // fp32_is_normal
    const uint_fast8_t tmp_12 = fp32_is_subnormal(arg_0);  // fp32_is_subnormal
    const uint_fast8_t tmp_20 = fp32_is_zero(arg_0);  // fp32_is_zero
    const uint_fast8_t tmp_27 = fp32_is_inf(arg_0);  // fp32_is_inf
    const uint_fast8_t tmp_33 = fp32_is_nan(arg_0);  // fp32_is_nan
    const std::array<uint_fast64_t, 5> tmp_34 = std::array<uint_fast64_t, 5>{static_cast<uint_fast64_t>(tmp_5), static_cast<uint_fast64_t>(tmp_12), static_cast<uint_fast64_t>(tmp_20), static_cast<uint_fast64_t>(tmp_27), static_cast<uint_fast64_t>(tmp_33)};  // basic_tuple_maker_5
    // end inline composite fp32_classify
    const uint_fast8_t tmp_35 = uint_fast8_t(tmp_34[2] & 1);  // _basic_get_item_2
    // begin inline composite fp32_classify
    const uint_fast8_t tmp_36 = fp32_is_normal(arg_1);  // fp32_is_normal
    const uint_fast8_t tmp_37 = fp32_is_subnormal(arg_1);  // fp32_is_subnormal
    const uint_fast8_t tmp_38 = fp32_is_zero(arg_1);  // fp32_is_zero
    const uint_fast8_t tmp_39 = fp32_is_inf(arg_1);  // fp32_is_inf
    const uint_fast8_t tmp_40 = fp32_is_nan(arg_1);  // fp32_is_nan
    const std::array<uint_fast64_t, 5> tmp_41 = std::array<uint_fast64_t, 5>{static_cast<uint_fast64_t>(tmp_36), static_cast<uint_fast64_t>(tmp_37), static_cast<uint_fast64_t>(tmp_38), static_cast<uint_fast64_t>(tmp_39), static_cast<uint_fast64_t>(tmp_40)};  // basic_tuple_maker_5
    // end inline composite fp32_classify
    const uint_fast8_t tmp_42 = uint_fast8_t(tmp_41[2] & 1);  // _basic_get_item_2
    const uint_fast8_t tmp_44 = bit_and(tmp_35, tmp_42);  // bit_and
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_45 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_46 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_47 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_48 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_45), static_cast<uint_fast64_t>(tmp_46), static_cast<uint_fast64_t>(tmp_47)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_49 = uint_fast8_t(tmp_48[0] & 1);  // _basic_get_item_0
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_50 = uint_fast8_t(((arg_1 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_51 = uint_fast8_t(((arg_1 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_52 = uint_fast32_t(((arg_1 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_53 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_50), static_cast<uint_fast64_t>(tmp_51), static_cast<uint_fast64_t>(tmp_52)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_54 = uint_fast8_t(tmp_53[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_55 = bit_and(tmp_49, tmp_54);  // bit_and
    const uint_fast8_t tmp_56 = bit_and(tmp_44, tmp_55);  // bit_and
    const uint_fast8_t tmp_57 = uint_fast8_t(tmp_34[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_58 = uint_fast32_t(tmp_48[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_59 = uint_fast32_t(tmp_58 & 8388607);  // basic_identity
    const uint_fast32_t tmp_61 = add_implicit_bit(tmp_59);  // add_implicit_bit
    const uint_fast32_t tmp_63 = uq_resize(tmp_59);  // uq_resize
    const uint_fast32_t tmp_65 = if_then_else(tmp_57, tmp_61, tmp_63);  // if_then_else
    const uint_fast32_t tmp_67 = uq_resize_1(tmp_65);  // uq_resize
    const uint_fast8_t tmp_68 = uint_fast8_t(tmp_34[1] & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_69 = uint_fast8_t(tmp_48[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_71 = if_then_else_1(tmp_68, uint_fast8_t(1 & 255), tmp_69);  // if_then_else
    const uint_fast8_t tmp_72 = uint_fast8_t(tmp_41[1] & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_73 = uint_fast8_t(tmp_53[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_74 = if_then_else_1(tmp_72, uint_fast8_t(1 & 255), tmp_73);  // if_then_else
    const uint_fast8_t tmp_81 = uq_max(tmp_71, tmp_74);  // uq_max
    const uint_fast16_t tmp_88 = uq_sub(tmp_81, tmp_71);  // uq_sub
    const uint_fast32_t tmp_114 = uq_rshift_jam(tmp_67, tmp_88);  // uq_rshift_jam
    const uint_fast32_t tmp_124 = uq_to_q(tmp_114);  // uq_to_q
    const uint_fast32_t tmp_133 = q_add_sign(tmp_124, tmp_49);  // q_add_sign
    const uint_fast8_t tmp_134 = uint_fast8_t(tmp_41[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_135 = uint_fast32_t(tmp_53[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_136 = uint_fast32_t(tmp_135 & 8388607);  // basic_identity
    const uint_fast32_t tmp_137 = add_implicit_bit(tmp_136);  // add_implicit_bit
    const uint_fast32_t tmp_138 = uq_resize(tmp_136);  // uq_resize
    const uint_fast32_t tmp_139 = if_then_else(tmp_134, tmp_137, tmp_138);  // if_then_else
    const uint_fast32_t tmp_140 = uq_resize_1(tmp_139);  // uq_resize
    const uint_fast16_t tmp_141 = uq_sub(tmp_81, tmp_74);  // uq_sub
    const uint_fast32_t tmp_142 = uq_rshift_jam(tmp_140, tmp_141);  // uq_rshift_jam
    const uint_fast32_t tmp_143 = uq_to_q(tmp_142);  // uq_to_q
    const uint_fast32_t tmp_144 = q_add_sign(tmp_143, tmp_54);  // q_add_sign
    const uint_fast32_t tmp_159 = q_add(tmp_133, tmp_144);  // q_add
    const uint_fast8_t tmp_161 = q_sign_bit_1(tmp_159);  // q_sign_bit
    const uint_fast8_t tmp_163 = if_then_else_2(tmp_56, uint_fast8_t(1 & 1), tmp_161);  // if_then_else
    const uint_fast16_t tmp_173 = uq_to_q_1(tmp_81);  // uq_to_q
    const uint_fast32_t tmp_184 = q_abs(tmp_159);  // q_abs
    const uint_fast32_t tmp_186 = q_to_uq(tmp_184);  // q_to_uq
    const uint_fast8_t tmp_187 = uint_fast8_t(tmp_34[3] & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_188 = uint_fast8_t(tmp_41[3] & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_189 = bit_and(tmp_187, tmp_188);  // bit_and
    const uint_fast8_t tmp_191 = bit_xor(tmp_49, tmp_54);  // bit_xor
    const uint_fast8_t tmp_192 = bit_and(tmp_189, tmp_191);  // bit_and
    const uint_fast8_t tmp_193 = uint_fast8_t(tmp_34[4] & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_194 = uint_fast8_t(tmp_41[4] & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_196 = bit_or(tmp_193, tmp_194);  // bit_or
    const uint_fast8_t tmp_197 = bit_or(tmp_192, tmp_196);  // bit_or
    const uint_fast8_t tmp_199 = bit_neg(tmp_197);  // bit_neg
    const uint_fast8_t tmp_200 = bit_or(tmp_187, tmp_188);  // bit_or
    const uint_fast8_t tmp_201 = bit_and(tmp_199, tmp_200);  // bit_and
    const uint_fast32_t tmp_579 = fp32_encode(tmp_163, tmp_173, tmp_186, tmp_197, tmp_201);  // fp32_encode
    return tmp_579;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}