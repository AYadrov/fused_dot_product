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
static inline uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_42 = uint_fast32_t(((uint_fast64_t(uint_fast8_t(1 & 1)) << 23) | arg_0) & 16777215);  // basic_concat
    return tmp_42;
}
static inline uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_44 = uint_fast32_t(arg_0 & 16777215);  // basic_identity
    return tmp_44;
}
static inline uint_fast32_t if_then_else(uint_fast8_t arg_0, uint_fast32_t arg_1, uint_fast32_t arg_2) {  // if_then_else
    const uint_fast32_t tmp_46 = uint_fast32_t((arg_0 == 1 ? arg_1 : arg_2) & 16777215);  // basic_mux_2_1
    return tmp_46;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_48 = uint_fast32_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(6 & 7))) & 1073741823);  // basic_lshift
    return tmp_48;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_56 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast8_t tmp_57 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_58 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_56), static_cast<uint_fast64_t>(tmp_57)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_59 = uint_fast8_t(tmp_58[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_60 = uint_fast8_t(tmp_58[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_61 = uint_fast8_t((tmp_59 > tmp_60 ? tmp_59 : tmp_60) & 255);  // basic_max
    return tmp_61;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_63 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_64 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_65 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_63), static_cast<uint_fast64_t>(tmp_64)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_66 = uint_fast16_t(tmp_65[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_67 = uint_fast16_t(tmp_65[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_68 = uint_fast16_t((tmp_66 - tmp_67) & 511);  // basic_sub
    return tmp_68;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_70 = uint_fast32_t((arg_1 >= 30 ? 0 : (arg_0 >> arg_1)) & 1073741823);  // basic_rshift
    return tmp_70;
}
static inline uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_72 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_73 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_74 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_72), static_cast<uint_fast64_t>(tmp_73)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_75 = uint_fast8_t(tmp_74[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_76 = uint_fast8_t(tmp_74[1] & 3);  // _basic_get_item_1
    const uint_fast8_t tmp_77 = uint_fast8_t((tmp_75 + tmp_76) & 3);  // basic_add
    return tmp_77;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_78 = uq_add(uint_fast8_t(1 & 1), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast32_t tmp_79 = uint_fast32_t(0 & 2147483647);  // q_alloc
    const uint_fast32_t tmp_80 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_80;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_83 = uint_fast8_t((arg_0 == 1073741824) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_84 = uint_fast32_t(((~arg_0) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_85 = uint_fast32_t((tmp_84 + uint_fast8_t(1 & 1)) & 2147483647);  // basic_add
    const uint_fast32_t tmp_86 = uint_fast32_t((arg_0 ^ arg_0) & 2147483647);  // basic_xor
    const uint_fast32_t tmp_87 = uint_fast32_t(((~tmp_86) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_88 = uint_fast32_t((tmp_83 == 1 ? tmp_87 : tmp_85) & 2147483647);  // basic_mux_2_1
    return tmp_88;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_89 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_90 = uint_fast32_t((arg_1 == 1 ? tmp_89 : arg_0) & 2147483647);  // basic_mux_2_1
    return tmp_90;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_111 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    return tmp_111;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_112 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_113 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_112) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_114 = uint_fast8_t((tmp_113 - tmp_112) & 1);  // basic_sub
    const uint_fast32_t tmp_115 = uint_fast32_t(0 & 4294967295);  // q_alloc
    const uint_fast32_t tmp_116 = uint_fast32_t(((uint_fast64_t(tmp_114) << 31) | arg_0) & 4294967295);  // basic_concat
    return tmp_116;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_110 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_117 = q_sign_extend(tmp_110);  // q_sign_extend
    const uint_fast32_t tmp_118 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_119 = q_sign_extend(tmp_118);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_120 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_117), static_cast<uint_fast64_t>(tmp_119)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_121 = uint_fast32_t(tmp_120[0] & 4294967295);  // _basic_get_item_0
    const uint_fast32_t tmp_122 = uint_fast32_t(tmp_120[1] & 4294967295);  // _basic_get_item_1
    const uint_fast32_t tmp_123 = uint_fast32_t((tmp_121 + tmp_122) & 4294967295);  // basic_add
    return tmp_123;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_125 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    return tmp_125;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_127 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_128 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_129 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_127), static_cast<uint_fast64_t>(tmp_128)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_130 = uint_fast8_t(tmp_129[0] & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_131 = uint_fast8_t(tmp_129[1] & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_132 = uint_fast8_t((tmp_130 + tmp_131) & 31);  // basic_add
    return tmp_132;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_133 = uq_add_1(uint_fast8_t(8 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_134 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_135 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_135;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_138 = uint_fast8_t((arg_0 == 2147483648) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_139 = uint_fast32_t(((~arg_0) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_140 = uint_fast32_t((tmp_139 + uint_fast8_t(1 & 1)) & 4294967295);  // basic_add
    const uint_fast32_t tmp_141 = uint_fast32_t((arg_0 ^ arg_0) & 4294967295);  // basic_xor
    const uint_fast32_t tmp_142 = uint_fast32_t(((~tmp_141) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_143 = uint_fast32_t((tmp_138 == 1 ? tmp_142 : tmp_140) & 4294967295);  // basic_mux_2_1
    return tmp_143;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_144 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_145 = uint_fast32_t((arg_1 == 1 ? tmp_144 : arg_0) & 4294967295);  // basic_mux_2_1
    return tmp_145;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_137 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_146 = q_add_sign_1(arg_0, tmp_137);  // q_add_sign
    return tmp_146;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_148 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_148;
}
static inline uint_fast8_t bit_and(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // bit_and
    const uint_fast8_t tmp_152 = uint_fast8_t((arg_0 & arg_1) & 1);  // basic_and
    return tmp_152;
}
static inline uint_fast8_t bit_xor(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // bit_xor
    const uint_fast8_t tmp_154 = uint_fast8_t((arg_0 ^ arg_1) & 1);  // basic_xor
    return tmp_154;
}
static inline uint_fast8_t bit_or(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // bit_or
    const uint_fast8_t tmp_159 = uint_fast8_t((arg_0 | arg_1) & 1);  // basic_or
    return tmp_159;
}
static inline uint_fast8_t bit_neg(uint_fast8_t arg_0) {  // bit_neg
    const uint_fast8_t tmp_162 = uint_fast8_t(((~arg_0) & 1) & 1);  // basic_invert
    return tmp_162;
}
static inline uint_fast8_t q_is_zero(uint_fast32_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_166 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_167 = uint_fast8_t(((~tmp_166) & 1) & 1);  // basic_invert
    return tmp_167;
}
static inline uint_fast32_t if_then_else_1(uint_fast8_t arg_0, uint_fast32_t arg_1, uint_fast32_t arg_2) {  // if_then_else
    const uint_fast32_t tmp_169 = uint_fast32_t((arg_0 == 1 ? arg_1 : arg_2) & 4294967295);  // basic_mux_2_1
    return tmp_169;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_172 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_173 = uint_fast8_t(((~tmp_172) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_174 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_173) & 1);  // basic_and
    const uint_fast8_t tmp_175 = uint_fast8_t((uint_fast8_t(0 & 31) + tmp_174) & 31);  // basic_add
    const uint_fast8_t tmp_176 = uint_fast8_t(((arg_0 >> 29) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_177 = uint_fast8_t(((~tmp_176) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_174 & tmp_177) & 1);  // basic_and
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_175 + tmp_178) & 31);  // basic_add
    const uint_fast8_t tmp_180 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_181 = uint_fast8_t(((~tmp_180) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_182 = uint_fast8_t((tmp_178 & tmp_181) & 1);  // basic_and
    const uint_fast8_t tmp_183 = uint_fast8_t((tmp_179 + tmp_182) & 31);  // basic_add
    const uint_fast8_t tmp_184 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_185 = uint_fast8_t(((~tmp_184) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_186 = uint_fast8_t((tmp_182 & tmp_185) & 1);  // basic_and
    const uint_fast8_t tmp_187 = uint_fast8_t((tmp_183 + tmp_186) & 31);  // basic_add
    const uint_fast8_t tmp_188 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_189 = uint_fast8_t(((~tmp_188) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_190 = uint_fast8_t((tmp_186 & tmp_189) & 1);  // basic_and
    const uint_fast8_t tmp_191 = uint_fast8_t((tmp_187 + tmp_190) & 31);  // basic_add
    const uint_fast8_t tmp_192 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_193 = uint_fast8_t(((~tmp_192) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_194 = uint_fast8_t((tmp_190 & tmp_193) & 1);  // basic_and
    const uint_fast8_t tmp_195 = uint_fast8_t((tmp_191 + tmp_194) & 31);  // basic_add
    const uint_fast8_t tmp_196 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_197 = uint_fast8_t(((~tmp_196) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_198 = uint_fast8_t((tmp_194 & tmp_197) & 1);  // basic_and
    const uint_fast8_t tmp_199 = uint_fast8_t((tmp_195 + tmp_198) & 31);  // basic_add
    const uint_fast8_t tmp_200 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_201 = uint_fast8_t(((~tmp_200) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_202 = uint_fast8_t((tmp_198 & tmp_201) & 1);  // basic_and
    const uint_fast8_t tmp_203 = uint_fast8_t((tmp_199 + tmp_202) & 31);  // basic_add
    const uint_fast8_t tmp_204 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_205 = uint_fast8_t(((~tmp_204) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_206 = uint_fast8_t((tmp_202 & tmp_205) & 1);  // basic_and
    const uint_fast8_t tmp_207 = uint_fast8_t((tmp_203 + tmp_206) & 31);  // basic_add
    const uint_fast8_t tmp_208 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_209 = uint_fast8_t(((~tmp_208) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_210 = uint_fast8_t((tmp_206 & tmp_209) & 1);  // basic_and
    const uint_fast8_t tmp_211 = uint_fast8_t((tmp_207 + tmp_210) & 31);  // basic_add
    const uint_fast8_t tmp_212 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_213 = uint_fast8_t(((~tmp_212) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_214 = uint_fast8_t((tmp_210 & tmp_213) & 1);  // basic_and
    const uint_fast8_t tmp_215 = uint_fast8_t((tmp_211 + tmp_214) & 31);  // basic_add
    const uint_fast8_t tmp_216 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_217 = uint_fast8_t(((~tmp_216) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_218 = uint_fast8_t((tmp_214 & tmp_217) & 1);  // basic_and
    const uint_fast8_t tmp_219 = uint_fast8_t((tmp_215 + tmp_218) & 31);  // basic_add
    const uint_fast8_t tmp_220 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_221 = uint_fast8_t(((~tmp_220) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_222 = uint_fast8_t((tmp_218 & tmp_221) & 1);  // basic_and
    const uint_fast8_t tmp_223 = uint_fast8_t((tmp_219 + tmp_222) & 31);  // basic_add
    const uint_fast8_t tmp_224 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_225 = uint_fast8_t(((~tmp_224) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_226 = uint_fast8_t((tmp_222 & tmp_225) & 1);  // basic_and
    const uint_fast8_t tmp_227 = uint_fast8_t((tmp_223 + tmp_226) & 31);  // basic_add
    const uint_fast8_t tmp_228 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_229 = uint_fast8_t(((~tmp_228) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_230 = uint_fast8_t((tmp_226 & tmp_229) & 1);  // basic_and
    const uint_fast8_t tmp_231 = uint_fast8_t((tmp_227 + tmp_230) & 31);  // basic_add
    const uint_fast8_t tmp_232 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_233 = uint_fast8_t(((~tmp_232) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_234 = uint_fast8_t((tmp_230 & tmp_233) & 1);  // basic_and
    const uint_fast8_t tmp_235 = uint_fast8_t((tmp_231 + tmp_234) & 31);  // basic_add
    const uint_fast8_t tmp_236 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_237 = uint_fast8_t(((~tmp_236) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_238 = uint_fast8_t((tmp_234 & tmp_237) & 1);  // basic_and
    const uint_fast8_t tmp_239 = uint_fast8_t((tmp_235 + tmp_238) & 31);  // basic_add
    const uint_fast8_t tmp_240 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_241 = uint_fast8_t(((~tmp_240) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_242 = uint_fast8_t((tmp_238 & tmp_241) & 1);  // basic_and
    const uint_fast8_t tmp_243 = uint_fast8_t((tmp_239 + tmp_242) & 31);  // basic_add
    const uint_fast8_t tmp_244 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_245 = uint_fast8_t(((~tmp_244) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_246 = uint_fast8_t((tmp_242 & tmp_245) & 1);  // basic_and
    const uint_fast8_t tmp_247 = uint_fast8_t((tmp_243 + tmp_246) & 31);  // basic_add
    const uint_fast8_t tmp_248 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_249 = uint_fast8_t(((~tmp_248) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_250 = uint_fast8_t((tmp_246 & tmp_249) & 1);  // basic_and
    const uint_fast8_t tmp_251 = uint_fast8_t((tmp_247 + tmp_250) & 31);  // basic_add
    const uint_fast8_t tmp_252 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_253 = uint_fast8_t(((~tmp_252) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_254 = uint_fast8_t((tmp_250 & tmp_253) & 1);  // basic_and
    const uint_fast8_t tmp_255 = uint_fast8_t((tmp_251 + tmp_254) & 31);  // basic_add
    const uint_fast8_t tmp_256 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_257 = uint_fast8_t(((~tmp_256) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_258 = uint_fast8_t((tmp_254 & tmp_257) & 1);  // basic_and
    const uint_fast8_t tmp_259 = uint_fast8_t((tmp_255 + tmp_258) & 31);  // basic_add
    const uint_fast8_t tmp_260 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_261 = uint_fast8_t(((~tmp_260) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_262 = uint_fast8_t((tmp_258 & tmp_261) & 1);  // basic_and
    const uint_fast8_t tmp_263 = uint_fast8_t((tmp_259 + tmp_262) & 31);  // basic_add
    const uint_fast8_t tmp_264 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_265 = uint_fast8_t(((~tmp_264) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_266 = uint_fast8_t((tmp_262 & tmp_265) & 1);  // basic_and
    const uint_fast8_t tmp_267 = uint_fast8_t((tmp_263 + tmp_266) & 31);  // basic_add
    const uint_fast8_t tmp_268 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_269 = uint_fast8_t(((~tmp_268) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_270 = uint_fast8_t((tmp_266 & tmp_269) & 1);  // basic_and
    const uint_fast8_t tmp_271 = uint_fast8_t((tmp_267 + tmp_270) & 31);  // basic_add
    const uint_fast8_t tmp_272 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_273 = uint_fast8_t(((~tmp_272) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_274 = uint_fast8_t((tmp_270 & tmp_273) & 1);  // basic_and
    const uint_fast8_t tmp_275 = uint_fast8_t((tmp_271 + tmp_274) & 31);  // basic_add
    const uint_fast8_t tmp_276 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_277 = uint_fast8_t(((~tmp_276) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_278 = uint_fast8_t((tmp_274 & tmp_277) & 1);  // basic_and
    const uint_fast8_t tmp_279 = uint_fast8_t((tmp_275 + tmp_278) & 31);  // basic_add
    const uint_fast8_t tmp_280 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_281 = uint_fast8_t(((~tmp_280) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_282 = uint_fast8_t((tmp_278 & tmp_281) & 1);  // basic_and
    const uint_fast8_t tmp_283 = uint_fast8_t((tmp_279 + tmp_282) & 31);  // basic_add
    const uint_fast8_t tmp_284 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_285 = uint_fast8_t(((~tmp_284) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_286 = uint_fast8_t((tmp_282 & tmp_285) & 1);  // basic_and
    const uint_fast8_t tmp_287 = uint_fast8_t((tmp_283 + tmp_286) & 31);  // basic_add
    const uint_fast8_t tmp_288 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_289 = uint_fast8_t(((~tmp_288) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_290 = uint_fast8_t((tmp_286 & tmp_289) & 1);  // basic_and
    const uint_fast8_t tmp_291 = uint_fast8_t((tmp_287 + tmp_290) & 31);  // basic_add
    const uint_fast8_t tmp_292 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_293 = uint_fast8_t(((~tmp_292) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_294 = uint_fast8_t((tmp_290 & tmp_293) & 1);  // basic_and
    const uint_fast8_t tmp_295 = uint_fast8_t((tmp_291 + tmp_294) & 31);  // basic_add
    return tmp_295;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_297 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_298 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_299 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_297), static_cast<uint_fast64_t>(tmp_298)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_300 = uint_fast8_t(tmp_299[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_301 = uint_fast8_t(tmp_299[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_302 = uint_fast8_t((tmp_300 + tmp_301) & 15);  // basic_add
    return tmp_302;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_303 = uq_add_2(uint_fast8_t(5 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_304 = uint_fast8_t(0 & 63);  // q_alloc
    const uint_fast8_t tmp_305 = uint_fast8_t(arg_0 & 63);  // basic_identity
    return tmp_305;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_307 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_308 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_309 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_307), static_cast<uint_fast64_t>(tmp_308)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_310 = uint_fast8_t(tmp_309[0] & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_311 = uint_fast8_t(tmp_309[1] & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_312 = uint_fast8_t((tmp_310 + tmp_311) & 7);  // basic_add
    return tmp_312;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_313 = uq_add_3(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_314 = uint_fast8_t(0 & 7);  // q_alloc
    const uint_fast8_t tmp_315 = uint_fast8_t(arg_0 & 7);  // basic_identity
    return tmp_315;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_318 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    return tmp_318;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_319 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_320 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_319) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_321 = uint_fast8_t((tmp_320 - tmp_319) & 1);  // basic_sub
    const uint_fast8_t tmp_322 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_323 = uint_fast8_t(((uint_fast64_t(tmp_321) << 6) | arg_0) & 127);  // basic_concat
    return tmp_323;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_326 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    return tmp_326;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_327 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_328 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_327) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_329 = uint_fast8_t((tmp_328 - tmp_327) & 15);  // basic_sub
    const uint_fast8_t tmp_330 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_331 = uint_fast8_t(((uint_fast64_t(tmp_329) << 3) | arg_0) & 127);  // basic_concat
    return tmp_331;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_317 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast8_t tmp_324 = q_sign_extend_1(tmp_317);  // q_sign_extend
    const uint_fast8_t tmp_325 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_332 = q_sign_extend_2(tmp_325);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_333 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_324), static_cast<uint_fast64_t>(tmp_332)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_334 = uint_fast8_t(tmp_333[0] & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_335 = uint_fast8_t(tmp_333[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_336 = uint_fast8_t((tmp_334 - tmp_335) & 127);  // basic_sub
    return tmp_336;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_339 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_339;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_340 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_341 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_340) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_342 = uint_fast8_t((tmp_341 - tmp_340) & 1);  // basic_sub
    const uint_fast8_t tmp_343 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_344 = uint_fast8_t(((uint_fast64_t(tmp_342) << 7) | arg_0) & 255);  // basic_concat
    return tmp_344;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_347 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_347;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_348 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_349 = uint_fast8_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_348) << uint_fast8_t(6 & 7))) & 127);  // basic_lshift
    const uint_fast8_t tmp_350 = uint_fast8_t((tmp_349 - tmp_348) & 63);  // basic_sub
    const uint_fast8_t tmp_351 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_352 = uint_fast8_t(((uint_fast64_t(tmp_350) << 2) | arg_0) & 255);  // basic_concat
    return tmp_352;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_338 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_345 = q_sign_extend_3(tmp_338);  // q_sign_extend
    const uint_fast8_t tmp_346 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_353 = q_sign_extend_4(tmp_346);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_354 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_345), static_cast<uint_fast64_t>(tmp_353)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_355 = uint_fast8_t(tmp_354[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_356 = uint_fast8_t(tmp_354[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_357 = uint_fast8_t((tmp_355 + tmp_356) & 255);  // basic_add
    return tmp_357;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_359 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_359;
}
static inline uint_fast32_t uq_resize_2(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_361 = uint_fast32_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(1 & 1))) & 4294967295);  // basic_lshift
    return tmp_361;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_364 = uint_fast8_t((arg_0 == 128) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_365 = uint_fast8_t(((~arg_0) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_366 = uint_fast8_t((tmp_365 + uint_fast8_t(1 & 1)) & 255);  // basic_add
    const uint_fast8_t tmp_367 = uint_fast8_t((arg_0 ^ arg_0) & 255);  // basic_xor
    const uint_fast8_t tmp_368 = uint_fast8_t(((~tmp_367) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_369 = uint_fast8_t((tmp_364 == 1 ? tmp_368 : tmp_366) & 255);  // basic_mux_2_1
    return tmp_369;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_370 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_371 = uint_fast8_t((arg_1 == 1 ? tmp_370 : arg_0) & 255);  // basic_mux_2_1
    return tmp_371;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_363 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_372 = q_add_sign_2(arg_0, tmp_363);  // q_add_sign
    return tmp_372;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_374 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_374;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_376 = uint_fast32_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 4294967295);  // basic_lshift
    return tmp_376;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_378 = uint_fast32_t((arg_1 >= 32 ? 0 : (arg_0 >> arg_1)) & 4294967295);  // basic_rshift
    return tmp_378;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_382 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_382;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_383 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_384 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_383) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_385 = uint_fast8_t((tmp_384 - tmp_383) & 1);  // basic_sub
    const uint_fast16_t tmp_386 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_387 = uint_fast16_t(((uint_fast64_t(tmp_385) << 9) | arg_0) & 1023);  // basic_concat
    return tmp_387;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_390 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_391 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_390) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_392 = uint_fast8_t((tmp_391 - tmp_390) & 3);  // basic_sub
    const uint_fast16_t tmp_393 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_394 = uint_fast16_t(((uint_fast64_t(tmp_392) << 8) | arg_0) & 1023);  // basic_concat
    return tmp_394;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_381 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_388 = q_sign_extend_5(tmp_381);  // q_sign_extend
    const uint_fast8_t tmp_389 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_395 = q_sign_extend_6(tmp_389);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_396 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_388), static_cast<uint_fast64_t>(tmp_395)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_397 = uint_fast16_t(tmp_396[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_398 = uint_fast16_t(tmp_396[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_399 = uint_fast16_t((tmp_397 - tmp_398) & 1023);  // basic_sub
    return tmp_399;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_401 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_402 = q_sign_extend_5(tmp_401);  // q_sign_extend
    const uint_fast8_t tmp_403 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_404 = q_sign_extend_6(tmp_403);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_405 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_402), static_cast<uint_fast64_t>(tmp_404)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_406 = uint_fast16_t(tmp_405[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_407 = uint_fast16_t(tmp_405[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_408 = uint_fast16_t((tmp_406 + tmp_407) & 1023);  // basic_add
    return tmp_408;
}
static inline uint_fast8_t q_is_zero_1(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_415 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_416 = uint_fast8_t(((~tmp_415) & 1) & 1);  // basic_invert
    return tmp_416;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_418 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_418;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_422 = uint_fast8_t((arg_0 == 512) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_423 = uint_fast16_t(((~arg_0) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_424 = uint_fast16_t((tmp_423 + uint_fast8_t(1 & 1)) & 1023);  // basic_add
    const uint_fast16_t tmp_425 = uint_fast16_t((arg_0 ^ arg_0) & 1023);  // basic_xor
    const uint_fast16_t tmp_426 = uint_fast16_t(((~tmp_425) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_427 = uint_fast16_t((tmp_422 == 1 ? tmp_426 : tmp_424) & 1023);  // basic_mux_2_1
    return tmp_427;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_428 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_429 = uint_fast16_t((arg_1 == 1 ? tmp_428 : arg_0) & 1023);  // basic_mux_2_1
    return tmp_429;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_421 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_430 = q_add_sign_3(arg_0, tmp_421);  // q_add_sign
    return tmp_430;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_432 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_432;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_434 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_435 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_436 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_434), static_cast<uint_fast64_t>(tmp_435)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_437 = uint_fast16_t(tmp_436[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_438 = uint_fast16_t(tmp_436[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_439 = uint_fast16_t((tmp_437 + tmp_438) & 1023);  // basic_add
    return tmp_439;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_442 = uint_fast64_t((arg_1 >= 41 ? 0 : (arg_0 >> arg_1)) & 2199023255551);  // basic_rshift
    return tmp_442;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_447 = uint_fast64_t(((arg_0 >> 0) & 1099511627775) & 1099511627775);  // basic_select
    return tmp_447;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_450 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_451 = uint_fast8_t(((~tmp_450) & 1) & 1);  // basic_invert
    return tmp_451;
}
static inline uint_fast32_t uq_resize_3(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_453 = uint_fast32_t((uint_fast8_t(17 & 31) >= 40 ? 0 : (arg_0 >> uint_fast8_t(17 & 31))) & 8388607);  // basic_rshift
    return tmp_453;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_464 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_465 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_466 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_464), static_cast<uint_fast64_t>(tmp_465)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_467 = uint_fast32_t(tmp_466[0] & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_468 = uint_fast32_t(tmp_466[1] & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_469 = uint_fast32_t((tmp_467 + tmp_468) & 16777215);  // basic_add
    return tmp_469;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_476 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_477 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_478 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_476), static_cast<uint_fast64_t>(tmp_477)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_479 = uint_fast16_t(tmp_478[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_480 = uint_fast16_t(tmp_478[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_481 = uint_fast16_t((tmp_479 + tmp_480) & 1023);  // basic_add
    return tmp_481;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_490 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_491 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_492 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_490), static_cast<uint_fast64_t>(tmp_491)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_493 = uint_fast16_t(tmp_492[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_494 = uint_fast16_t(tmp_492[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_495 = uint_fast16_t((tmp_493 < tmp_494 ? tmp_493 : tmp_494) & 1023);  // basic_min
    return tmp_495;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_504 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_504;
}
static inline uint_fast32_t fp32_encode(uint_fast8_t arg_0, uint_fast16_t arg_1, uint_fast32_t arg_2, uint_fast8_t arg_3, uint_fast8_t arg_4, uint_fast8_t arg_5) {  // fp32_encode
    const uint_fast32_t tmp_170 = if_then_else_1(arg_0, uint_fast32_t(2147483648 & 4294967295), uint_fast32_t(0 & 4294967295));  // if_then_else
    const uint_fast32_t tmp_171 = if_then_else_1(arg_0, uint_fast32_t(4286578688 & 4294967295), uint_fast32_t(2139095040 & 4294967295));  // if_then_else
    // begin inline primitive normalize_to_1_xxx
    const uint_fast8_t tmp_296 = lzc(arg_2);  // lzc
    const uint_fast8_t tmp_306 = uq_to_q_2(tmp_296);  // uq_to_q
    const uint_fast8_t tmp_316 = uq_to_q_3(uint_fast8_t(2 & 3));  // uq_to_q
    const uint_fast8_t tmp_337 = q_sub(tmp_306, tmp_316);  // q_sub
    const uint_fast8_t tmp_358 = q_add_1(tmp_337, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_360 = q_sign_bit_6(tmp_358);  // q_sign_bit
    const uint_fast32_t tmp_362 = uq_resize_2(arg_2);  // uq_resize
    const uint_fast8_t tmp_373 = q_abs_1(tmp_358);  // q_abs
    const uint_fast8_t tmp_375 = q_to_uq_1(tmp_373);  // q_to_uq
    const uint_fast32_t tmp_377 = uq_lshift(tmp_362, tmp_375);  // uq_lshift
    const uint_fast32_t tmp_379 = uq_rshift_1(tmp_362, tmp_375);  // uq_rshift
    const uint_fast32_t tmp_380 = uint_fast32_t((tmp_360 == 1 ? tmp_379 : tmp_377) & 2147483647);  // basic_mux_2_1
    const uint_fast16_t tmp_400 = q_sub_1(arg_1, tmp_373);  // q_sub
    const uint_fast16_t tmp_409 = q_add_2(arg_1, tmp_373);  // q_add
    const uint_fast16_t tmp_410 = uint_fast16_t((tmp_360 == 1 ? tmp_409 : tmp_400) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_411 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_380), static_cast<uint_fast64_t>(tmp_410)};  // basic_tuple_maker_2
    // end inline primitive normalize_to_1_xxx
    const uint_fast32_t tmp_412 = uint_fast32_t(tmp_411[0] & 2147483647);  // _basic_get_item_0
    const uint_fast16_t tmp_413 = uint_fast16_t(tmp_411[1] & 1023);  // _basic_get_item_1
    // begin inline primitive shift_if_subnormal
    const uint_fast64_t tmp_414 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_412) << uint_fast8_t(10 & 15))) & 2199023255551);  // basic_lshift
    const uint_fast8_t tmp_417 = q_is_zero_1(tmp_413);  // q_is_zero
    const uint_fast8_t tmp_419 = q_sign_bit_8(tmp_413);  // q_sign_bit
    const uint_fast8_t tmp_420 = uint_fast8_t((tmp_417 | tmp_419) & 1);  // basic_or
    const uint_fast16_t tmp_431 = q_abs_2(tmp_413);  // q_abs
    const uint_fast16_t tmp_433 = q_to_uq_2(tmp_431);  // q_to_uq
    const uint_fast16_t tmp_440 = uq_add_4(uint_fast8_t(1 & 1), tmp_433);  // uq_add
    const uint_fast16_t tmp_441 = uint_fast16_t((tmp_420 == 1 ? tmp_440 : uint_fast8_t(0 & 1)) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_443 = uq_rshift_2(tmp_414, tmp_441);  // uq_rshift
    const uint_fast16_t tmp_444 = uint_fast16_t((tmp_420 == 1 ? uint_fast8_t(0 & 1) : tmp_433) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_445 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_443), static_cast<uint_fast64_t>(tmp_444)};  // basic_tuple_maker_2
    // end inline primitive shift_if_subnormal
    const uint_fast64_t tmp_446 = uint_fast64_t(tmp_445[0] & 2199023255551);  // _basic_get_item_0
    const uint_fast64_t tmp_448 = drop_implicit_bit(tmp_446);  // drop_implicit_bit
    const uint_fast16_t tmp_449 = uint_fast16_t(tmp_445[1] & 511);  // _basic_get_item_1
    // begin inline primitive round_mantissa
    const uint_fast8_t tmp_452 = uq_is_zero(tmp_449);  // uq_is_zero
    // begin inline primitive uq_RNE_IEEE
    const uint_fast32_t tmp_454 = uq_resize_3(tmp_448);  // uq_resize
    const uint_fast8_t tmp_455 = uint_fast8_t(((tmp_448 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_456 = uint_fast8_t(((tmp_448 >> 15) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_457 = uint_fast16_t(((tmp_448 >> 0) & 32767) & 32767);  // basic_select
    const uint_fast8_t tmp_458 = uint_fast8_t((tmp_457 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_459 = uint_fast8_t((tmp_456 | tmp_458) & 1);  // basic_or
    const uint_fast8_t tmp_460 = uint_fast8_t(((tmp_448 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_461 = uint_fast8_t((tmp_459 | tmp_460) & 1);  // basic_or
    const uint_fast8_t tmp_462 = uint_fast8_t((tmp_455 & tmp_461) & 1);  // basic_and
    const uint_fast32_t tmp_463 = uint_fast32_t(tmp_462 & 8388607);  // basic_identity
    const uint_fast32_t tmp_470 = uq_add_5(tmp_454, tmp_463);  // uq_add
    const uint_fast8_t tmp_471 = uint_fast8_t((tmp_454 == 8388607) & 1);  // basic_and_reduce
    const uint_fast8_t tmp_472 = uint_fast8_t((tmp_471 & tmp_462) & 1);  // basic_and
    const uint_fast32_t tmp_473 = uint_fast32_t((tmp_472 >= 24 ? 0 : (tmp_470 >> tmp_472)) & 8388607);  // basic_rshift
    const std::array<uint_fast64_t, 2> tmp_474 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_473), static_cast<uint_fast64_t>(tmp_472)};  // basic_tuple_maker_2
    // end inline primitive uq_RNE_IEEE
    const uint_fast8_t tmp_475 = uint_fast8_t(tmp_474[1] & 1);  // _basic_get_item_1
    const uint_fast16_t tmp_482 = uq_add_6(tmp_449, tmp_475);  // uq_add
    const uint_fast8_t tmp_483 = uint_fast8_t((tmp_482 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_484 = uint_fast8_t((tmp_452 & tmp_483) & 1);  // basic_and
    const uint_fast32_t tmp_485 = uint_fast32_t(tmp_474[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_486 = uint_fast32_t((tmp_484 == 1 ? uint_fast8_t(0 & 1) : tmp_485) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_487 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_486), static_cast<uint_fast64_t>(tmp_482)};  // basic_tuple_maker_2
    // end inline primitive round_mantissa
    const uint_fast32_t tmp_488 = uint_fast32_t(tmp_487[0] & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_489 = uint_fast16_t(tmp_487[1] & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_496 = uq_min(tmp_489, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_497 = uint_fast8_t(tmp_496 & 255);  // basic_identity
    const uint_fast8_t tmp_498 = uint_fast8_t((tmp_497 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_499 = uint_fast32_t((tmp_498 == 1 ? uint_fast8_t(0 & 1) : tmp_488) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_500 = uint_fast32_t(tmp_499 & 8388607);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_501 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_500), static_cast<uint_fast64_t>(tmp_497)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_502 = uint_fast8_t(tmp_501[1] & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_503 = uint_fast32_t(tmp_501[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_505 = fp32_pack(arg_0, tmp_502, tmp_503);  // fp32_pack
    const uint_fast32_t tmp_506 = if_then_else_1(arg_3, uint_fast32_t(2139095041 & 4294967295), tmp_505);  // if_then_else
    const uint_fast32_t tmp_507 = if_then_else_1(arg_4, tmp_171, tmp_506);  // if_then_else
    const uint_fast32_t tmp_508 = if_then_else_1(arg_5, tmp_170, tmp_507);  // if_then_else
    return tmp_508;
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
    const uint_fast8_t tmp_35 = uint_fast8_t(tmp_34[0] & 1);  // _basic_get_item_0
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_36 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_37 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_38 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_39 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_36), static_cast<uint_fast64_t>(tmp_37), static_cast<uint_fast64_t>(tmp_38)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast32_t tmp_40 = uint_fast32_t(tmp_39[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_41 = uint_fast32_t(tmp_40 & 8388607);  // basic_identity
    const uint_fast32_t tmp_43 = add_implicit_bit(tmp_41);  // add_implicit_bit
    const uint_fast32_t tmp_45 = uq_resize(tmp_41);  // uq_resize
    const uint_fast32_t tmp_47 = if_then_else(tmp_35, tmp_43, tmp_45);  // if_then_else
    const uint_fast32_t tmp_49 = uq_resize_1(tmp_47);  // uq_resize
    const uint_fast8_t tmp_50 = uint_fast8_t(tmp_39[1] & 255);  // _basic_get_item_1
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_51 = uint_fast8_t(((arg_1 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_52 = uint_fast8_t(((arg_1 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_53 = uint_fast32_t(((arg_1 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_54 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_51), static_cast<uint_fast64_t>(tmp_52), static_cast<uint_fast64_t>(tmp_53)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_55 = uint_fast8_t(tmp_54[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_62 = uq_max(tmp_50, tmp_55);  // uq_max
    const uint_fast16_t tmp_69 = uq_sub(tmp_62, tmp_50);  // uq_sub
    const uint_fast32_t tmp_71 = uq_rshift(tmp_49, tmp_69);  // uq_rshift
    const uint_fast32_t tmp_81 = uq_to_q(tmp_71);  // uq_to_q
    const uint_fast8_t tmp_82 = uint_fast8_t(tmp_39[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_91 = q_add_sign(tmp_81, tmp_82);  // q_add_sign
    // begin inline composite fp32_classify
    const uint_fast8_t tmp_92 = fp32_is_normal(arg_1);  // fp32_is_normal
    const uint_fast8_t tmp_93 = fp32_is_subnormal(arg_1);  // fp32_is_subnormal
    const uint_fast8_t tmp_94 = fp32_is_zero(arg_1);  // fp32_is_zero
    const uint_fast8_t tmp_95 = fp32_is_inf(arg_1);  // fp32_is_inf
    const uint_fast8_t tmp_96 = fp32_is_nan(arg_1);  // fp32_is_nan
    const std::array<uint_fast64_t, 5> tmp_97 = std::array<uint_fast64_t, 5>{static_cast<uint_fast64_t>(tmp_92), static_cast<uint_fast64_t>(tmp_93), static_cast<uint_fast64_t>(tmp_94), static_cast<uint_fast64_t>(tmp_95), static_cast<uint_fast64_t>(tmp_96)};  // basic_tuple_maker_5
    // end inline composite fp32_classify
    const uint_fast8_t tmp_98 = uint_fast8_t(tmp_97[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_99 = uint_fast32_t(tmp_54[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_100 = uint_fast32_t(tmp_99 & 8388607);  // basic_identity
    const uint_fast32_t tmp_101 = add_implicit_bit(tmp_100);  // add_implicit_bit
    const uint_fast32_t tmp_102 = uq_resize(tmp_100);  // uq_resize
    const uint_fast32_t tmp_103 = if_then_else(tmp_98, tmp_101, tmp_102);  // if_then_else
    const uint_fast32_t tmp_104 = uq_resize_1(tmp_103);  // uq_resize
    const uint_fast16_t tmp_105 = uq_sub(tmp_62, tmp_55);  // uq_sub
    const uint_fast32_t tmp_106 = uq_rshift(tmp_104, tmp_105);  // uq_rshift
    const uint_fast32_t tmp_107 = uq_to_q(tmp_106);  // uq_to_q
    const uint_fast8_t tmp_108 = uint_fast8_t(tmp_54[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_109 = q_add_sign(tmp_107, tmp_108);  // q_add_sign
    const uint_fast32_t tmp_124 = q_add(tmp_91, tmp_109);  // q_add
    const uint_fast8_t tmp_126 = q_sign_bit_1(tmp_124);  // q_sign_bit
    const uint_fast16_t tmp_136 = uq_to_q_1(tmp_62);  // uq_to_q
    const uint_fast32_t tmp_147 = q_abs(tmp_124);  // q_abs
    const uint_fast32_t tmp_149 = q_to_uq(tmp_147);  // q_to_uq
    const uint_fast8_t tmp_150 = uint_fast8_t(tmp_34[3] & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_151 = uint_fast8_t(tmp_97[3] & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_153 = bit_and(tmp_150, tmp_151);  // bit_and
    const uint_fast8_t tmp_155 = bit_xor(tmp_82, tmp_108);  // bit_xor
    const uint_fast8_t tmp_156 = bit_and(tmp_153, tmp_155);  // bit_and
    const uint_fast8_t tmp_157 = uint_fast8_t(tmp_34[4] & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_158 = uint_fast8_t(tmp_97[4] & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_160 = bit_or(tmp_157, tmp_158);  // bit_or
    const uint_fast8_t tmp_161 = bit_or(tmp_156, tmp_160);  // bit_or
    const uint_fast8_t tmp_163 = bit_neg(tmp_161);  // bit_neg
    const uint_fast8_t tmp_164 = bit_or(tmp_150, tmp_151);  // bit_or
    const uint_fast8_t tmp_165 = bit_and(tmp_163, tmp_164);  // bit_and
    const uint_fast8_t tmp_168 = q_is_zero(tmp_124);  // q_is_zero
    const uint_fast32_t tmp_509 = fp32_encode(tmp_126, tmp_136, tmp_149, tmp_161, tmp_165, tmp_168);  // fp32_encode
    return tmp_509;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}