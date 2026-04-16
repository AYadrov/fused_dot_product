#pragma once
#include <cstdint>
#include <array>

static inline uint_fast8_t fp32_is_normal(uint_fast32_t arg_0) {  // fp32_is_normal
    const uint_fast8_t tmp = uint_fast8_t((((arg_0 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_1 = uint_fast8_t(((tmp != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_2 = uint_fast8_t(((tmp == 255)) & 1);  // basic_and_reduce
    const uint_fast8_t tmp_3 = uint_fast8_t((((~tmp_2) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_4 = uint_fast8_t(((tmp_1 & tmp_3)) & 1);  // basic_and
    return tmp_4;
}
static inline uint_fast8_t fp32_is_subnormal(uint_fast32_t arg_0) {  // fp32_is_subnormal
    const uint_fast8_t tmp_6 = uint_fast8_t((((arg_0 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_7 = uint_fast8_t(((tmp_6 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_8 = uint_fast8_t((((~tmp_7) & 1)) & 1);  // basic_invert
    const uint_fast32_t tmp_9 = uint_fast32_t(((arg_0 & ((1 << 23) - 1))) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_10 = uint_fast8_t(((tmp_9 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_11 = uint_fast8_t(((tmp_8 & tmp_10)) & 1);  // basic_and
    return tmp_11;
}
static inline uint_fast8_t fp32_is_zero(uint_fast32_t arg_0) {  // fp32_is_zero
    const uint_fast8_t tmp_13 = uint_fast8_t((((arg_0 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_14 = uint_fast8_t(((tmp_13 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_15 = uint_fast8_t((((~tmp_14) & 1)) & 1);  // basic_invert
    const uint_fast32_t tmp_16 = uint_fast32_t(((arg_0 & ((1 << 23) - 1))) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_17 = uint_fast8_t(((tmp_16 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_18 = uint_fast8_t((((~tmp_17) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_19 = uint_fast8_t(((tmp_15 & tmp_18)) & 1);  // basic_and
    return tmp_19;
}
static inline uint_fast8_t fp32_is_inf(uint_fast32_t arg_0) {  // fp32_is_inf
    const uint_fast8_t tmp_21 = uint_fast8_t((((arg_0 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_22 = uint_fast8_t(((tmp_21 == 255)) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_23 = uint_fast32_t(((arg_0 & ((1 << 23) - 1))) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_24 = uint_fast8_t(((tmp_23 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_25 = uint_fast8_t((((~tmp_24) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_26 = uint_fast8_t(((tmp_22 & tmp_25)) & 1);  // basic_and
    return tmp_26;
}
static inline uint_fast8_t fp32_is_nan(uint_fast32_t arg_0) {  // fp32_is_nan
    const uint_fast8_t tmp_28 = uint_fast8_t((((arg_0 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_29 = uint_fast8_t(((tmp_28 == 255)) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_30 = uint_fast32_t(((arg_0 & ((1 << 23) - 1))) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_31 = uint_fast8_t(((tmp_30 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_32 = uint_fast8_t(((tmp_29 & tmp_31)) & 1);  // basic_and
    return tmp_32;
}
static inline uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_59 = uint_fast32_t((((uint_fast32_t(uint_fast8_t((1) & 1)) << 23) | arg_0)) & 16777215);  // basic_concat
    return tmp_59;
}
static inline uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_61 = uint_fast32_t((arg_0) & 16777215);  // basic_identity
    return tmp_61;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_64 = uint_fast32_t(((uint_fast8_t((3) & 3) >= 27 ? 0 : (uint_fast32_t(arg_0) << uint_fast8_t((3) & 3)))) & 134217727);  // basic_lshift
    return tmp_64;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const std::array<uint_fast64_t, 2> tmp_72 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(arg_1)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_73 = uint_fast8_t((tmp_72[0]) & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_74 = uint_fast8_t((tmp_72[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_75 = uint_fast8_t(((tmp_73 > tmp_74 ? tmp_73 : tmp_74)) & 255);  // basic_max
    return tmp_75;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_77 = uint_fast16_t((arg_0) & 511);  // basic_identity
    const uint_fast16_t tmp_78 = uint_fast16_t((arg_1) & 511);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_79 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_77), static_cast<uint_fast64_t>(tmp_78)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_80 = uint_fast16_t((tmp_79[0]) & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_81 = uint_fast16_t((tmp_79[1]) & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_82 = uint_fast16_t(((uint_fast16_t(tmp_80) - uint_fast16_t(tmp_81))) & 511);  // basic_sub
    return tmp_82;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_84 = uint_fast32_t(((arg_1 >= 27 ? 0 : (arg_0 >> arg_1))) & 134217727);  // basic_rshift
    return tmp_84;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_86 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_87 = uint_fast8_t((((~tmp_86) & 1)) & 1);  // basic_invert
    return tmp_87;
}
static inline uint_fast8_t uq_ge(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_89 = uint_fast16_t((arg_1) & 511);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_90 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_89)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_91 = uint_fast16_t((tmp_90[0]) & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_92 = uint_fast16_t((tmp_90[1]) & 511);  // _basic_get_item_1
    const uint_fast8_t tmp_93 = uint_fast8_t(((tmp_91 >= tmp_92)) & 1);  // basic_greater_or_equal
    return tmp_93;
}
static inline uint_fast16_t uq_sub_1(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_95 = uint_fast16_t((arg_0) & 1023);  // basic_identity
    const uint_fast16_t tmp_96 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_97 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_95), static_cast<uint_fast64_t>(tmp_96)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_98 = uint_fast16_t((tmp_97[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_99 = uint_fast16_t((tmp_97[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_100 = uint_fast16_t(((uint_fast16_t(tmp_98) - uint_fast16_t(tmp_99))) & 1023);  // basic_sub
    return tmp_100;
}
static inline uint_fast32_t uq_rshift_jam(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift_jam
    const uint_fast32_t tmp_85 = uq_rshift(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_88 = uq_is_zero(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_94 = uq_ge(arg_1, uint_fast8_t((27) & 31));  // uq_ge
    const uint_fast16_t tmp_101 = uq_sub_1(uint_fast8_t((27) & 31), arg_1);  // uq_sub
    const uint_fast32_t tmp_102 = uint_fast32_t(((tmp_101 >= 27 ? 0 : (uint_fast32_t(arg_0) << tmp_101))) & 134217727);  // basic_lshift
    const uint_fast8_t tmp_103 = uint_fast8_t(((tmp_102 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_104 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_105 = uint_fast8_t(((tmp_94 != 0 ? tmp_104 : tmp_103)) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_106 = uint_fast8_t(((tmp_88 != 0 ? uint_fast8_t((0) & 1) : tmp_105)) & 1);  // basic_mux_2_1
    const uint_fast32_t tmp_107 = uint_fast32_t(((tmp_85 | tmp_106)) & 134217727);  // basic_or
    return tmp_107;
}
static inline uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_109 = uint_fast8_t((arg_0) & 3);  // basic_identity
    const uint_fast8_t tmp_110 = uint_fast8_t((arg_1) & 3);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_111 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_109), static_cast<uint_fast64_t>(tmp_110)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_112 = uint_fast8_t((tmp_111[0]) & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_113 = uint_fast8_t((tmp_111[1]) & 3);  // _basic_get_item_1
    const uint_fast8_t tmp_114 = uint_fast8_t(((uint_fast8_t(tmp_112) + uint_fast8_t(tmp_113))) & 3);  // basic_add
    return tmp_114;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_115 = uq_add(uint_fast8_t((1) & 1), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast32_t tmp_116 = uint_fast32_t((0) & 268435455);  // q_alloc
    const uint_fast32_t tmp_117 = uint_fast32_t((arg_0) & 268435455);  // basic_identity
    return tmp_117;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_119 = uint_fast8_t(((arg_0 == 134217728)) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_120 = uint_fast32_t((((~arg_0) & 268435455)) & 268435455);  // basic_invert
    const uint_fast32_t tmp_121 = uint_fast32_t(((uint_fast32_t(tmp_120) + uint_fast32_t(uint_fast8_t((1) & 1)))) & 268435455);  // basic_add
    const uint_fast32_t tmp_122 = uint_fast32_t(((arg_0 ^ arg_0)) & 268435455);  // basic_xor
    const uint_fast32_t tmp_123 = uint_fast32_t((((~tmp_122) & 268435455)) & 268435455);  // basic_invert
    const uint_fast32_t tmp_124 = uint_fast32_t(((tmp_119 != 0 ? tmp_123 : tmp_121)) & 268435455);  // basic_mux_2_1
    return tmp_124;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_125 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_126 = uint_fast32_t(((arg_1 != 0 ? tmp_125 : arg_0)) & 268435455);  // basic_mux_2_1
    return tmp_126;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_140 = uint_fast8_t((((arg_0 >> 27) & 1)) & 1);  // basic_select
    return tmp_140;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_141 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_142 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? 0 : (uint_fast8_t(tmp_141) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_143 = uint_fast8_t(((uint_fast8_t(tmp_142) - uint_fast8_t(tmp_141))) & 1);  // basic_sub
    const uint_fast32_t tmp_144 = uint_fast32_t((0) & 536870911);  // q_alloc
    const uint_fast32_t tmp_145 = uint_fast32_t((((uint_fast32_t(tmp_143) << 28) | arg_0)) & 536870911);  // basic_concat
    return tmp_145;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_139 = uint_fast32_t(((uint_fast8_t((0) & 1) >= 28 ? 0 : (uint_fast32_t(arg_0) << uint_fast8_t((0) & 1)))) & 268435455);  // basic_lshift
    const uint_fast32_t tmp_146 = q_sign_extend(tmp_139);  // q_sign_extend
    const uint_fast32_t tmp_147 = uint_fast32_t(((uint_fast8_t((0) & 1) >= 28 ? 0 : (uint_fast32_t(arg_1) << uint_fast8_t((0) & 1)))) & 268435455);  // basic_lshift
    const uint_fast32_t tmp_148 = q_sign_extend(tmp_147);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_149 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_146), static_cast<uint_fast64_t>(tmp_148)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_150 = uint_fast32_t((tmp_149[0]) & 536870911);  // _basic_get_item_0
    const uint_fast32_t tmp_151 = uint_fast32_t((tmp_149[1]) & 536870911);  // _basic_get_item_1
    const uint_fast32_t tmp_152 = uint_fast32_t(((uint_fast32_t(tmp_150) + uint_fast32_t(tmp_151))) & 536870911);  // basic_add
    return tmp_152;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_154 = uint_fast8_t((((arg_0 >> 28) & 1)) & 1);  // basic_select
    return tmp_154;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_157 = uint_fast8_t((arg_0) & 31);  // basic_identity
    const uint_fast8_t tmp_158 = uint_fast8_t((arg_1) & 31);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_159 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_157), static_cast<uint_fast64_t>(tmp_158)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_160 = uint_fast8_t((tmp_159[0]) & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_161 = uint_fast8_t((tmp_159[1]) & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_162 = uint_fast8_t(((uint_fast8_t(tmp_160) + uint_fast8_t(tmp_161))) & 31);  // basic_add
    return tmp_162;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_163 = uq_add_1(uint_fast8_t((8) & 15), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast16_t tmp_164 = uint_fast16_t((0) & 511);  // q_alloc
    const uint_fast16_t tmp_165 = uint_fast16_t((arg_0) & 511);  // basic_identity
    return tmp_165;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_168 = uint_fast8_t(((arg_0 == 268435456)) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_169 = uint_fast32_t((((~arg_0) & 536870911)) & 536870911);  // basic_invert
    const uint_fast32_t tmp_170 = uint_fast32_t(((uint_fast32_t(tmp_169) + uint_fast32_t(uint_fast8_t((1) & 1)))) & 536870911);  // basic_add
    const uint_fast32_t tmp_171 = uint_fast32_t(((arg_0 ^ arg_0)) & 536870911);  // basic_xor
    const uint_fast32_t tmp_172 = uint_fast32_t((((~tmp_171) & 536870911)) & 536870911);  // basic_invert
    const uint_fast32_t tmp_173 = uint_fast32_t(((tmp_168 != 0 ? tmp_172 : tmp_170)) & 536870911);  // basic_mux_2_1
    return tmp_173;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_174 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_175 = uint_fast32_t(((arg_1 != 0 ? tmp_174 : arg_0)) & 536870911);  // basic_mux_2_1
    return tmp_175;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_167 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_176 = q_add_sign_1(arg_0, tmp_167);  // q_add_sign
    return tmp_176;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_178 = uint_fast32_t((arg_0) & 268435455);  // basic_identity
    return tmp_178;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_193 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_194 = uint_fast8_t((((~tmp_193) & 1)) & 1);  // basic_invert
    return tmp_194;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_197 = uint_fast8_t((((arg_0 >> 27) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_198 = uint_fast8_t((((~tmp_197) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_199 = uint_fast8_t(((uint_fast8_t((1) & 1) & tmp_198)) & 1);  // basic_and
    const uint_fast8_t tmp_200 = uint_fast8_t(((uint_fast8_t(uint_fast8_t((0) & 31)) + uint_fast8_t(tmp_199))) & 31);  // basic_add
    const uint_fast8_t tmp_201 = uint_fast8_t((((arg_0 >> 26) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_202 = uint_fast8_t((((~tmp_201) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_203 = uint_fast8_t(((tmp_199 & tmp_202)) & 1);  // basic_and
    const uint_fast8_t tmp_204 = uint_fast8_t(((uint_fast8_t(tmp_200) + uint_fast8_t(tmp_203))) & 31);  // basic_add
    const uint_fast8_t tmp_205 = uint_fast8_t((((arg_0 >> 25) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_206 = uint_fast8_t((((~tmp_205) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_207 = uint_fast8_t(((tmp_203 & tmp_206)) & 1);  // basic_and
    const uint_fast8_t tmp_208 = uint_fast8_t(((uint_fast8_t(tmp_204) + uint_fast8_t(tmp_207))) & 31);  // basic_add
    const uint_fast8_t tmp_209 = uint_fast8_t((((arg_0 >> 24) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_210 = uint_fast8_t((((~tmp_209) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_211 = uint_fast8_t(((tmp_207 & tmp_210)) & 1);  // basic_and
    const uint_fast8_t tmp_212 = uint_fast8_t(((uint_fast8_t(tmp_208) + uint_fast8_t(tmp_211))) & 31);  // basic_add
    const uint_fast8_t tmp_213 = uint_fast8_t((((arg_0 >> 23) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_214 = uint_fast8_t((((~tmp_213) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_215 = uint_fast8_t(((tmp_211 & tmp_214)) & 1);  // basic_and
    const uint_fast8_t tmp_216 = uint_fast8_t(((uint_fast8_t(tmp_212) + uint_fast8_t(tmp_215))) & 31);  // basic_add
    const uint_fast8_t tmp_217 = uint_fast8_t((((arg_0 >> 22) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_218 = uint_fast8_t((((~tmp_217) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_219 = uint_fast8_t(((tmp_215 & tmp_218)) & 1);  // basic_and
    const uint_fast8_t tmp_220 = uint_fast8_t(((uint_fast8_t(tmp_216) + uint_fast8_t(tmp_219))) & 31);  // basic_add
    const uint_fast8_t tmp_221 = uint_fast8_t((((arg_0 >> 21) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_222 = uint_fast8_t((((~tmp_221) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_223 = uint_fast8_t(((tmp_219 & tmp_222)) & 1);  // basic_and
    const uint_fast8_t tmp_224 = uint_fast8_t(((uint_fast8_t(tmp_220) + uint_fast8_t(tmp_223))) & 31);  // basic_add
    const uint_fast8_t tmp_225 = uint_fast8_t((((arg_0 >> 20) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_226 = uint_fast8_t((((~tmp_225) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_227 = uint_fast8_t(((tmp_223 & tmp_226)) & 1);  // basic_and
    const uint_fast8_t tmp_228 = uint_fast8_t(((uint_fast8_t(tmp_224) + uint_fast8_t(tmp_227))) & 31);  // basic_add
    const uint_fast8_t tmp_229 = uint_fast8_t((((arg_0 >> 19) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_230 = uint_fast8_t((((~tmp_229) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_231 = uint_fast8_t(((tmp_227 & tmp_230)) & 1);  // basic_and
    const uint_fast8_t tmp_232 = uint_fast8_t(((uint_fast8_t(tmp_228) + uint_fast8_t(tmp_231))) & 31);  // basic_add
    const uint_fast8_t tmp_233 = uint_fast8_t((((arg_0 >> 18) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_234 = uint_fast8_t((((~tmp_233) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_235 = uint_fast8_t(((tmp_231 & tmp_234)) & 1);  // basic_and
    const uint_fast8_t tmp_236 = uint_fast8_t(((uint_fast8_t(tmp_232) + uint_fast8_t(tmp_235))) & 31);  // basic_add
    const uint_fast8_t tmp_237 = uint_fast8_t((((arg_0 >> 17) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_238 = uint_fast8_t((((~tmp_237) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_239 = uint_fast8_t(((tmp_235 & tmp_238)) & 1);  // basic_and
    const uint_fast8_t tmp_240 = uint_fast8_t(((uint_fast8_t(tmp_236) + uint_fast8_t(tmp_239))) & 31);  // basic_add
    const uint_fast8_t tmp_241 = uint_fast8_t((((arg_0 >> 16) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_242 = uint_fast8_t((((~tmp_241) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_243 = uint_fast8_t(((tmp_239 & tmp_242)) & 1);  // basic_and
    const uint_fast8_t tmp_244 = uint_fast8_t(((uint_fast8_t(tmp_240) + uint_fast8_t(tmp_243))) & 31);  // basic_add
    const uint_fast8_t tmp_245 = uint_fast8_t((((arg_0 >> 15) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_246 = uint_fast8_t((((~tmp_245) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_247 = uint_fast8_t(((tmp_243 & tmp_246)) & 1);  // basic_and
    const uint_fast8_t tmp_248 = uint_fast8_t(((uint_fast8_t(tmp_244) + uint_fast8_t(tmp_247))) & 31);  // basic_add
    const uint_fast8_t tmp_249 = uint_fast8_t((((arg_0 >> 14) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_250 = uint_fast8_t((((~tmp_249) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_251 = uint_fast8_t(((tmp_247 & tmp_250)) & 1);  // basic_and
    const uint_fast8_t tmp_252 = uint_fast8_t(((uint_fast8_t(tmp_248) + uint_fast8_t(tmp_251))) & 31);  // basic_add
    const uint_fast8_t tmp_253 = uint_fast8_t((((arg_0 >> 13) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_254 = uint_fast8_t((((~tmp_253) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_255 = uint_fast8_t(((tmp_251 & tmp_254)) & 1);  // basic_and
    const uint_fast8_t tmp_256 = uint_fast8_t(((uint_fast8_t(tmp_252) + uint_fast8_t(tmp_255))) & 31);  // basic_add
    const uint_fast8_t tmp_257 = uint_fast8_t((((arg_0 >> 12) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_258 = uint_fast8_t((((~tmp_257) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_259 = uint_fast8_t(((tmp_255 & tmp_258)) & 1);  // basic_and
    const uint_fast8_t tmp_260 = uint_fast8_t(((uint_fast8_t(tmp_256) + uint_fast8_t(tmp_259))) & 31);  // basic_add
    const uint_fast8_t tmp_261 = uint_fast8_t((((arg_0 >> 11) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_262 = uint_fast8_t((((~tmp_261) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_263 = uint_fast8_t(((tmp_259 & tmp_262)) & 1);  // basic_and
    const uint_fast8_t tmp_264 = uint_fast8_t(((uint_fast8_t(tmp_260) + uint_fast8_t(tmp_263))) & 31);  // basic_add
    const uint_fast8_t tmp_265 = uint_fast8_t((((arg_0 >> 10) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_266 = uint_fast8_t((((~tmp_265) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_267 = uint_fast8_t(((tmp_263 & tmp_266)) & 1);  // basic_and
    const uint_fast8_t tmp_268 = uint_fast8_t(((uint_fast8_t(tmp_264) + uint_fast8_t(tmp_267))) & 31);  // basic_add
    const uint_fast8_t tmp_269 = uint_fast8_t((((arg_0 >> 9) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_270 = uint_fast8_t((((~tmp_269) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_271 = uint_fast8_t(((tmp_267 & tmp_270)) & 1);  // basic_and
    const uint_fast8_t tmp_272 = uint_fast8_t(((uint_fast8_t(tmp_268) + uint_fast8_t(tmp_271))) & 31);  // basic_add
    const uint_fast8_t tmp_273 = uint_fast8_t((((arg_0 >> 8) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_274 = uint_fast8_t((((~tmp_273) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_275 = uint_fast8_t(((tmp_271 & tmp_274)) & 1);  // basic_and
    const uint_fast8_t tmp_276 = uint_fast8_t(((uint_fast8_t(tmp_272) + uint_fast8_t(tmp_275))) & 31);  // basic_add
    const uint_fast8_t tmp_277 = uint_fast8_t((((arg_0 >> 7) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_278 = uint_fast8_t((((~tmp_277) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_279 = uint_fast8_t(((tmp_275 & tmp_278)) & 1);  // basic_and
    const uint_fast8_t tmp_280 = uint_fast8_t(((uint_fast8_t(tmp_276) + uint_fast8_t(tmp_279))) & 31);  // basic_add
    const uint_fast8_t tmp_281 = uint_fast8_t((((arg_0 >> 6) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_282 = uint_fast8_t((((~tmp_281) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_283 = uint_fast8_t(((tmp_279 & tmp_282)) & 1);  // basic_and
    const uint_fast8_t tmp_284 = uint_fast8_t(((uint_fast8_t(tmp_280) + uint_fast8_t(tmp_283))) & 31);  // basic_add
    const uint_fast8_t tmp_285 = uint_fast8_t((((arg_0 >> 5) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_286 = uint_fast8_t((((~tmp_285) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_287 = uint_fast8_t(((tmp_283 & tmp_286)) & 1);  // basic_and
    const uint_fast8_t tmp_288 = uint_fast8_t(((uint_fast8_t(tmp_284) + uint_fast8_t(tmp_287))) & 31);  // basic_add
    const uint_fast8_t tmp_289 = uint_fast8_t((((arg_0 >> 4) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_290 = uint_fast8_t((((~tmp_289) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_291 = uint_fast8_t(((tmp_287 & tmp_290)) & 1);  // basic_and
    const uint_fast8_t tmp_292 = uint_fast8_t(((uint_fast8_t(tmp_288) + uint_fast8_t(tmp_291))) & 31);  // basic_add
    const uint_fast8_t tmp_293 = uint_fast8_t((((arg_0 >> 3) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_294 = uint_fast8_t((((~tmp_293) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_295 = uint_fast8_t(((tmp_291 & tmp_294)) & 1);  // basic_and
    const uint_fast8_t tmp_296 = uint_fast8_t(((uint_fast8_t(tmp_292) + uint_fast8_t(tmp_295))) & 31);  // basic_add
    const uint_fast8_t tmp_297 = uint_fast8_t((((arg_0 >> 2) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_298 = uint_fast8_t((((~tmp_297) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_299 = uint_fast8_t(((tmp_295 & tmp_298)) & 1);  // basic_and
    const uint_fast8_t tmp_300 = uint_fast8_t(((uint_fast8_t(tmp_296) + uint_fast8_t(tmp_299))) & 31);  // basic_add
    const uint_fast8_t tmp_301 = uint_fast8_t((((arg_0 >> 1) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_302 = uint_fast8_t((((~tmp_301) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_303 = uint_fast8_t(((tmp_299 & tmp_302)) & 1);  // basic_and
    const uint_fast8_t tmp_304 = uint_fast8_t(((uint_fast8_t(tmp_300) + uint_fast8_t(tmp_303))) & 31);  // basic_add
    const uint_fast8_t tmp_305 = uint_fast8_t((((arg_0 >> 0) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_306 = uint_fast8_t((((~tmp_305) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_307 = uint_fast8_t(((tmp_303 & tmp_306)) & 1);  // basic_and
    const uint_fast8_t tmp_308 = uint_fast8_t(((uint_fast8_t(tmp_304) + uint_fast8_t(tmp_307))) & 31);  // basic_add
    return tmp_308;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_310 = uint_fast8_t((arg_0) & 15);  // basic_identity
    const uint_fast8_t tmp_311 = uint_fast8_t((arg_1) & 15);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_312 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_310), static_cast<uint_fast64_t>(tmp_311)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_313 = uint_fast8_t((tmp_312[0]) & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_314 = uint_fast8_t((tmp_312[1]) & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_315 = uint_fast8_t(((uint_fast8_t(tmp_313) + uint_fast8_t(tmp_314))) & 15);  // basic_add
    return tmp_315;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_316 = uq_add_2(uint_fast8_t((5) & 7), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast8_t tmp_317 = uint_fast8_t((0) & 63);  // q_alloc
    const uint_fast8_t tmp_318 = uint_fast8_t((arg_0) & 63);  // basic_identity
    return tmp_318;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_320 = uint_fast8_t((arg_0) & 7);  // basic_identity
    const uint_fast8_t tmp_321 = uint_fast8_t((arg_1) & 7);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_322 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_320), static_cast<uint_fast64_t>(tmp_321)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_323 = uint_fast8_t((tmp_322[0]) & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_324 = uint_fast8_t((tmp_322[1]) & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_325 = uint_fast8_t(((uint_fast8_t(tmp_323) + uint_fast8_t(tmp_324))) & 7);  // basic_add
    return tmp_325;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_326 = uq_add_3(uint_fast8_t((2) & 3), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast8_t tmp_327 = uint_fast8_t((0) & 7);  // q_alloc
    const uint_fast8_t tmp_328 = uint_fast8_t((arg_0) & 7);  // basic_identity
    return tmp_328;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_331 = uint_fast8_t((((arg_0 >> 5) & 1)) & 1);  // basic_select
    return tmp_331;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_332 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_333 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? 0 : (uint_fast8_t(tmp_332) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_334 = uint_fast8_t(((uint_fast8_t(tmp_333) - uint_fast8_t(tmp_332))) & 1);  // basic_sub
    const uint_fast8_t tmp_335 = uint_fast8_t((0) & 127);  // q_alloc
    const uint_fast8_t tmp_336 = uint_fast8_t((((uint_fast8_t(tmp_334) << 6) | arg_0)) & 127);  // basic_concat
    return tmp_336;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_339 = uint_fast8_t((((arg_0 >> 2) & 1)) & 1);  // basic_select
    return tmp_339;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_340 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_341 = uint_fast8_t(((uint_fast8_t((4) & 7) >= 5 ? 0 : (uint_fast8_t(tmp_340) << uint_fast8_t((4) & 7)))) & 31);  // basic_lshift
    const uint_fast8_t tmp_342 = uint_fast8_t(((uint_fast8_t(tmp_341) - uint_fast8_t(tmp_340))) & 15);  // basic_sub
    const uint_fast8_t tmp_343 = uint_fast8_t((0) & 127);  // q_alloc
    const uint_fast8_t tmp_344 = uint_fast8_t((((uint_fast8_t(tmp_342) << 3) | arg_0)) & 127);  // basic_concat
    return tmp_344;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_330 = uint_fast8_t(((uint_fast8_t((0) & 1) >= 6 ? 0 : (uint_fast8_t(arg_0) << uint_fast8_t((0) & 1)))) & 63);  // basic_lshift
    const uint_fast8_t tmp_337 = q_sign_extend_1(tmp_330);  // q_sign_extend
    const uint_fast8_t tmp_338 = uint_fast8_t(((uint_fast8_t((0) & 1) >= 3 ? 0 : (uint_fast8_t(arg_1) << uint_fast8_t((0) & 1)))) & 7);  // basic_lshift
    const uint_fast8_t tmp_345 = q_sign_extend_2(tmp_338);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_346 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_337), static_cast<uint_fast64_t>(tmp_345)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_347 = uint_fast8_t((tmp_346[0]) & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_348 = uint_fast8_t((tmp_346[1]) & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_349 = uint_fast8_t(((uint_fast8_t(tmp_347) - uint_fast8_t(tmp_348))) & 127);  // basic_sub
    return tmp_349;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_352 = uint_fast8_t((((arg_0 >> 6) & 1)) & 1);  // basic_select
    return tmp_352;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_353 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_354 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? 0 : (uint_fast8_t(tmp_353) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_355 = uint_fast8_t(((uint_fast8_t(tmp_354) - uint_fast8_t(tmp_353))) & 1);  // basic_sub
    const uint_fast8_t tmp_356 = uint_fast8_t((0) & 255);  // q_alloc
    const uint_fast8_t tmp_357 = uint_fast8_t((((uint_fast8_t(tmp_355) << 7) | arg_0)) & 255);  // basic_concat
    return tmp_357;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_360 = uint_fast8_t((((arg_0 >> 1) & 1)) & 1);  // basic_select
    return tmp_360;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_361 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_362 = uint_fast8_t(((uint_fast8_t((6) & 7) >= 7 ? 0 : (uint_fast8_t(tmp_361) << uint_fast8_t((6) & 7)))) & 127);  // basic_lshift
    const uint_fast8_t tmp_363 = uint_fast8_t(((uint_fast8_t(tmp_362) - uint_fast8_t(tmp_361))) & 63);  // basic_sub
    const uint_fast8_t tmp_364 = uint_fast8_t((0) & 255);  // q_alloc
    const uint_fast8_t tmp_365 = uint_fast8_t((((uint_fast8_t(tmp_363) << 2) | arg_0)) & 255);  // basic_concat
    return tmp_365;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_351 = uint_fast8_t(((uint_fast8_t((0) & 1) >= 7 ? 0 : (uint_fast8_t(arg_0) << uint_fast8_t((0) & 1)))) & 127);  // basic_lshift
    const uint_fast8_t tmp_358 = q_sign_extend_3(tmp_351);  // q_sign_extend
    const uint_fast8_t tmp_359 = uint_fast8_t(((uint_fast8_t((0) & 1) >= 2 ? 0 : (uint_fast8_t(arg_1) << uint_fast8_t((0) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_366 = q_sign_extend_4(tmp_359);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_367 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_358), static_cast<uint_fast64_t>(tmp_366)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_368 = uint_fast8_t((tmp_367[0]) & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_369 = uint_fast8_t((tmp_367[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_370 = uint_fast8_t(((uint_fast8_t(tmp_368) + uint_fast8_t(tmp_369))) & 255);  // basic_add
    return tmp_370;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_372 = uint_fast8_t((((arg_0 >> 7) & 1)) & 1);  // basic_select
    return tmp_372;
}
static inline uint_fast32_t uq_resize_2(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_374 = uint_fast32_t(((uint_fast8_t((1) & 1) >= 29 ? 0 : (uint_fast32_t(arg_0) << uint_fast8_t((1) & 1)))) & 536870911);  // basic_lshift
    return tmp_374;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_377 = uint_fast8_t(((arg_0 == 128)) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_378 = uint_fast8_t((((~arg_0) & 255)) & 255);  // basic_invert
    const uint_fast8_t tmp_379 = uint_fast8_t(((uint_fast8_t(tmp_378) + uint_fast8_t(uint_fast8_t((1) & 1)))) & 255);  // basic_add
    const uint_fast8_t tmp_380 = uint_fast8_t(((arg_0 ^ arg_0)) & 255);  // basic_xor
    const uint_fast8_t tmp_381 = uint_fast8_t((((~tmp_380) & 255)) & 255);  // basic_invert
    const uint_fast8_t tmp_382 = uint_fast8_t(((tmp_377 != 0 ? tmp_381 : tmp_379)) & 255);  // basic_mux_2_1
    return tmp_382;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_383 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_384 = uint_fast8_t(((arg_1 != 0 ? tmp_383 : arg_0)) & 255);  // basic_mux_2_1
    return tmp_384;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_376 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_385 = q_add_sign_2(arg_0, tmp_376);  // q_add_sign
    return tmp_385;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_387 = uint_fast8_t((arg_0) & 127);  // basic_identity
    return tmp_387;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_389 = uint_fast32_t(((arg_1 >= 29 ? 0 : (uint_fast32_t(arg_0) << arg_1))) & 536870911);  // basic_lshift
    return tmp_389;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_391 = uint_fast32_t(((arg_1 >= 29 ? 0 : (arg_0 >> arg_1))) & 536870911);  // basic_rshift
    return tmp_391;
}
static inline uint_fast8_t uq_is_zero_2(uint_fast8_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_393 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_394 = uint_fast8_t((((~tmp_393) & 1)) & 1);  // basic_invert
    return tmp_394;
}
static inline uint_fast8_t uq_ge_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_396 = uint_fast8_t((arg_1) & 127);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_397 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_396)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_398 = uint_fast8_t((tmp_397[0]) & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_399 = uint_fast8_t((tmp_397[1]) & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_400 = uint_fast8_t(((tmp_398 >= tmp_399)) & 1);  // basic_greater_or_equal
    return tmp_400;
}
static inline uint_fast8_t uq_sub_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_402 = uint_fast8_t((arg_0) & 255);  // basic_identity
    const uint_fast8_t tmp_403 = uint_fast8_t((arg_1) & 255);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_404 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_402), static_cast<uint_fast64_t>(tmp_403)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_405 = uint_fast8_t((tmp_404[0]) & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_406 = uint_fast8_t((tmp_404[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_407 = uint_fast8_t(((uint_fast8_t(tmp_405) - uint_fast8_t(tmp_406))) & 255);  // basic_sub
    return tmp_407;
}
static inline uint_fast32_t uq_rshift_jam_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift_jam
    const uint_fast32_t tmp_392 = uq_rshift_1(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_395 = uq_is_zero_2(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_401 = uq_ge_1(arg_1, uint_fast8_t((29) & 31));  // uq_ge
    const uint_fast8_t tmp_408 = uq_sub_2(uint_fast8_t((29) & 31), arg_1);  // uq_sub
    const uint_fast32_t tmp_409 = uint_fast32_t(((tmp_408 >= 29 ? 0 : (uint_fast32_t(arg_0) << tmp_408))) & 536870911);  // basic_lshift
    const uint_fast8_t tmp_410 = uint_fast8_t(((tmp_409 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_411 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_412 = uint_fast8_t(((tmp_401 != 0 ? tmp_411 : tmp_410)) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_413 = uint_fast8_t(((tmp_395 != 0 ? uint_fast8_t((0) & 1) : tmp_412)) & 1);  // basic_mux_2_1
    const uint_fast32_t tmp_414 = uint_fast32_t(((tmp_392 | tmp_413)) & 536870911);  // basic_or
    return tmp_414;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_418 = uint_fast8_t((((arg_0 >> 8) & 1)) & 1);  // basic_select
    return tmp_418;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_419 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_420 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? 0 : (uint_fast8_t(tmp_419) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_421 = uint_fast8_t(((uint_fast8_t(tmp_420) - uint_fast8_t(tmp_419))) & 1);  // basic_sub
    const uint_fast16_t tmp_422 = uint_fast16_t((0) & 1023);  // q_alloc
    const uint_fast16_t tmp_423 = uint_fast16_t((((uint_fast16_t(tmp_421) << 9) | arg_0)) & 1023);  // basic_concat
    return tmp_423;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_426 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_427 = uint_fast8_t(((uint_fast8_t((2) & 3) >= 3 ? 0 : (uint_fast8_t(tmp_426) << uint_fast8_t((2) & 3)))) & 7);  // basic_lshift
    const uint_fast8_t tmp_428 = uint_fast8_t(((uint_fast8_t(tmp_427) - uint_fast8_t(tmp_426))) & 3);  // basic_sub
    const uint_fast16_t tmp_429 = uint_fast16_t((0) & 1023);  // q_alloc
    const uint_fast16_t tmp_430 = uint_fast16_t((((uint_fast16_t(tmp_428) << 8) | arg_0)) & 1023);  // basic_concat
    return tmp_430;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_417 = uint_fast16_t(((uint_fast8_t((0) & 1) >= 9 ? 0 : (uint_fast16_t(arg_0) << uint_fast8_t((0) & 1)))) & 511);  // basic_lshift
    const uint_fast16_t tmp_424 = q_sign_extend_5(tmp_417);  // q_sign_extend
    const uint_fast8_t tmp_425 = uint_fast8_t(((uint_fast8_t((0) & 1) >= 8 ? 0 : (uint_fast8_t(arg_1) << uint_fast8_t((0) & 1)))) & 255);  // basic_lshift
    const uint_fast16_t tmp_431 = q_sign_extend_6(tmp_425);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_432 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_424), static_cast<uint_fast64_t>(tmp_431)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_433 = uint_fast16_t((tmp_432[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_434 = uint_fast16_t((tmp_432[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_435 = uint_fast16_t(((uint_fast16_t(tmp_433) - uint_fast16_t(tmp_434))) & 1023);  // basic_sub
    return tmp_435;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_437 = uint_fast16_t(((uint_fast8_t((0) & 1) >= 9 ? 0 : (uint_fast16_t(arg_0) << uint_fast8_t((0) & 1)))) & 511);  // basic_lshift
    const uint_fast16_t tmp_438 = q_sign_extend_5(tmp_437);  // q_sign_extend
    const uint_fast8_t tmp_439 = uint_fast8_t(((uint_fast8_t((0) & 1) >= 8 ? 0 : (uint_fast8_t(arg_1) << uint_fast8_t((0) & 1)))) & 255);  // basic_lshift
    const uint_fast16_t tmp_440 = q_sign_extend_6(tmp_439);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_441 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_438), static_cast<uint_fast64_t>(tmp_440)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_442 = uint_fast16_t((tmp_441[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_443 = uint_fast16_t((tmp_441[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_444 = uint_fast16_t(((uint_fast16_t(tmp_442) + uint_fast16_t(tmp_443))) & 1023);  // basic_add
    return tmp_444;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_451 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_452 = uint_fast8_t((((~tmp_451) & 1)) & 1);  // basic_invert
    return tmp_452;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_454 = uint_fast8_t((((arg_0 >> 9) & 1)) & 1);  // basic_select
    return tmp_454;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_458 = uint_fast8_t(((arg_0 == 512)) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_459 = uint_fast16_t((((~arg_0) & 1023)) & 1023);  // basic_invert
    const uint_fast16_t tmp_460 = uint_fast16_t(((uint_fast16_t(tmp_459) + uint_fast16_t(uint_fast8_t((1) & 1)))) & 1023);  // basic_add
    const uint_fast16_t tmp_461 = uint_fast16_t(((arg_0 ^ arg_0)) & 1023);  // basic_xor
    const uint_fast16_t tmp_462 = uint_fast16_t((((~tmp_461) & 1023)) & 1023);  // basic_invert
    const uint_fast16_t tmp_463 = uint_fast16_t(((tmp_458 != 0 ? tmp_462 : tmp_460)) & 1023);  // basic_mux_2_1
    return tmp_463;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_464 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_465 = uint_fast16_t(((arg_1 != 0 ? tmp_464 : arg_0)) & 1023);  // basic_mux_2_1
    return tmp_465;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_457 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_466 = q_add_sign_3(arg_0, tmp_457);  // q_add_sign
    return tmp_466;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_468 = uint_fast16_t((arg_0) & 511);  // basic_identity
    return tmp_468;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_470 = uint_fast16_t((arg_0) & 1023);  // basic_identity
    const uint_fast16_t tmp_471 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_472 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_470), static_cast<uint_fast64_t>(tmp_471)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_473 = uint_fast16_t((tmp_472[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_474 = uint_fast16_t((tmp_472[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_475 = uint_fast16_t(((uint_fast16_t(tmp_473) + uint_fast16_t(tmp_474))) & 1023);  // basic_add
    return tmp_475;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_478 = uint_fast64_t(((arg_1 >= 38 ? 0 : (arg_0 >> arg_1))) & 274877906943);  // basic_rshift
    return tmp_478;
}
static inline uint_fast8_t uq_is_zero_3(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_480 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_481 = uint_fast8_t((((~tmp_480) & 1)) & 1);  // basic_invert
    return tmp_481;
}
static inline uint_fast8_t uq_ge_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_483 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_484 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_483)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_485 = uint_fast16_t((tmp_484[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_486 = uint_fast16_t((tmp_484[1]) & 1023);  // _basic_get_item_1
    const uint_fast8_t tmp_487 = uint_fast8_t(((tmp_485 >= tmp_486)) & 1);  // basic_greater_or_equal
    return tmp_487;
}
static inline uint_fast16_t uq_sub_3(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_489 = uint_fast16_t((arg_0) & 2047);  // basic_identity
    const uint_fast16_t tmp_490 = uint_fast16_t((arg_1) & 2047);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_491 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_489), static_cast<uint_fast64_t>(tmp_490)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_492 = uint_fast16_t((tmp_491[0]) & 2047);  // _basic_get_item_0
    const uint_fast16_t tmp_493 = uint_fast16_t((tmp_491[1]) & 2047);  // _basic_get_item_1
    const uint_fast16_t tmp_494 = uint_fast16_t(((uint_fast16_t(tmp_492) - uint_fast16_t(tmp_493))) & 2047);  // basic_sub
    return tmp_494;
}
static inline uint_fast64_t uq_rshift_jam_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift_jam
    const uint_fast64_t tmp_479 = uq_rshift_2(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_482 = uq_is_zero_3(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_488 = uq_ge_2(arg_1, uint_fast8_t((38) & 63));  // uq_ge
    const uint_fast16_t tmp_495 = uq_sub_3(uint_fast8_t((38) & 63), arg_1);  // uq_sub
    const uint_fast64_t tmp_496 = uint_fast64_t(((tmp_495 >= 38 ? 0 : (uint_fast64_t(arg_0) << tmp_495))) & 274877906943);  // basic_lshift
    const uint_fast8_t tmp_497 = uint_fast8_t(((tmp_496 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_498 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_499 = uint_fast8_t(((tmp_488 != 0 ? tmp_498 : tmp_497)) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_500 = uint_fast8_t(((tmp_482 != 0 ? uint_fast8_t((0) & 1) : tmp_499)) & 1);  // basic_mux_2_1
    const uint_fast64_t tmp_501 = uint_fast64_t(((tmp_479 | tmp_500)) & 274877906943);  // basic_or
    return tmp_501;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_506 = uint_fast64_t((((arg_0 >> 0) & 137438953471)) & 137438953471);  // basic_select
    return tmp_506;
}
static inline uint_fast32_t uq_resize_3(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_510 = uint_fast32_t(((uint_fast8_t((14) & 15) >= 37 ? 0 : (arg_0 >> uint_fast8_t((14) & 15)))) & 8388607);  // basic_rshift
    return tmp_510;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_521 = uint_fast32_t((arg_0) & 16777215);  // basic_identity
    const uint_fast32_t tmp_522 = uint_fast32_t((arg_1) & 16777215);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_523 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_521), static_cast<uint_fast64_t>(tmp_522)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_524 = uint_fast32_t((tmp_523[0]) & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_525 = uint_fast32_t((tmp_523[1]) & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_526 = uint_fast32_t(((uint_fast32_t(tmp_524) + uint_fast32_t(tmp_525))) & 16777215);  // basic_add
    return tmp_526;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_533 = uint_fast16_t((arg_0) & 1023);  // basic_identity
    const uint_fast16_t tmp_534 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_535 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_533), static_cast<uint_fast64_t>(tmp_534)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_536 = uint_fast16_t((tmp_535[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_537 = uint_fast16_t((tmp_535[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_538 = uint_fast16_t(((uint_fast16_t(tmp_536) + uint_fast16_t(tmp_537))) & 1023);  // basic_add
    return tmp_538;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_547 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_548 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_547)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_549 = uint_fast16_t((tmp_548[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_550 = uint_fast16_t((tmp_548[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_551 = uint_fast16_t(((tmp_549 < tmp_550 ? tmp_549 : tmp_550)) & 1023);  // basic_min
    return tmp_551;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_560 = uint_fast32_t((((arg_0 << 31) | (arg_1 << 23) | arg_2)) & 4294967295);  // float32_alloc
    return tmp_560;
}
static inline uint_fast32_t fp32_encode(uint_fast8_t arg_0, uint_fast16_t arg_1, uint_fast32_t arg_2, uint_fast8_t arg_3, uint_fast8_t arg_4) {  // fp32_encode
    const uint_fast32_t tmp_192 = uint_fast32_t(((arg_0 != 0 ? uint_fast32_t((4286578688) & 4294967295) : uint_fast32_t((2139095040) & 4294967295))) & 4294967295);  // basic_mux_2_1
    const uint_fast8_t tmp_195 = uq_is_zero_1(arg_2);  // uq_is_zero
    const uint_fast32_t tmp_196 = uint_fast32_t(((arg_0 != 0 ? uint_fast32_t((2147483648) & 4294967295) : uint_fast32_t((0) & 4294967295))) & 4294967295);  // basic_mux_2_1
    // begin inline primitive normalize_to_1_xxx
    const uint_fast8_t tmp_309 = lzc(arg_2);  // lzc
    const uint_fast8_t tmp_319 = uq_to_q_2(tmp_309);  // uq_to_q
    const uint_fast8_t tmp_329 = uq_to_q_3(uint_fast8_t((2) & 3));  // uq_to_q
    const uint_fast8_t tmp_350 = q_sub(tmp_319, tmp_329);  // q_sub
    const uint_fast8_t tmp_371 = q_add_1(tmp_350, uint_fast8_t((1) & 3));  // q_add
    const uint_fast8_t tmp_373 = q_sign_bit_6(tmp_371);  // q_sign_bit
    const uint_fast32_t tmp_375 = uq_resize_2(arg_2);  // uq_resize
    const uint_fast8_t tmp_386 = q_abs_1(tmp_371);  // q_abs
    const uint_fast8_t tmp_388 = q_to_uq_1(tmp_386);  // q_to_uq
    const uint_fast32_t tmp_390 = uq_lshift(tmp_375, tmp_388);  // uq_lshift
    const uint_fast32_t tmp_415 = uq_rshift_jam_1(tmp_375, tmp_388);  // uq_rshift_jam
    const uint_fast32_t tmp_416 = uint_fast32_t(((tmp_373 != 0 ? tmp_415 : tmp_390)) & 268435455);  // basic_mux_2_1
    const uint_fast16_t tmp_436 = q_sub_1(arg_1, tmp_386);  // q_sub
    const uint_fast16_t tmp_445 = q_add_2(arg_1, tmp_386);  // q_add
    const uint_fast16_t tmp_446 = uint_fast16_t(((tmp_373 != 0 ? tmp_445 : tmp_436)) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_447 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_416), static_cast<uint_fast64_t>(tmp_446)};  // basic_tuple_maker_2
    // end inline primitive normalize_to_1_xxx
    const uint_fast32_t tmp_448 = uint_fast32_t((tmp_447[0]) & 268435455);  // _basic_get_item_0
    const uint_fast16_t tmp_449 = uint_fast16_t((tmp_447[1]) & 1023);  // _basic_get_item_1
    // begin inline primitive shift_if_subnormal
    const uint_fast64_t tmp_450 = uint_fast64_t(((uint_fast8_t((10) & 15) >= 38 ? 0 : (uint_fast64_t(tmp_448) << uint_fast8_t((10) & 15)))) & 274877906943);  // basic_lshift
    const uint_fast8_t tmp_453 = q_is_zero(tmp_449);  // q_is_zero
    const uint_fast8_t tmp_455 = q_sign_bit_8(tmp_449);  // q_sign_bit
    const uint_fast8_t tmp_456 = uint_fast8_t(((tmp_453 | tmp_455)) & 1);  // basic_or
    const uint_fast16_t tmp_467 = q_abs_2(tmp_449);  // q_abs
    const uint_fast16_t tmp_469 = q_to_uq_2(tmp_467);  // q_to_uq
    const uint_fast16_t tmp_476 = uq_add_4(uint_fast8_t((1) & 1), tmp_469);  // uq_add
    const uint_fast16_t tmp_477 = uint_fast16_t(((tmp_456 != 0 ? tmp_476 : uint_fast8_t((0) & 1))) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_502 = uq_rshift_jam_2(tmp_450, tmp_477);  // uq_rshift_jam
    const uint_fast16_t tmp_503 = uint_fast16_t(((tmp_456 != 0 ? uint_fast8_t((0) & 1) : tmp_469)) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_504 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_502), static_cast<uint_fast64_t>(tmp_503)};  // basic_tuple_maker_2
    // end inline primitive shift_if_subnormal
    const uint_fast64_t tmp_505 = uint_fast64_t((tmp_504[0]) & 274877906943);  // _basic_get_item_0
    const uint_fast64_t tmp_507 = drop_implicit_bit(tmp_505);  // drop_implicit_bit
    const uint_fast16_t tmp_508 = uint_fast16_t((tmp_504[1]) & 511);  // _basic_get_item_1
    // begin inline primitive round_mantissa
    const uint_fast8_t tmp_509 = uq_is_zero(tmp_508);  // uq_is_zero
    // begin inline primitive uq_RNE_IEEE
    const uint_fast32_t tmp_511 = uq_resize_3(tmp_507);  // uq_resize
    const uint_fast8_t tmp_512 = uint_fast8_t((((tmp_507 >> 13) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_513 = uint_fast8_t((((tmp_507 >> 12) & 1)) & 1);  // basic_select
    const uint_fast16_t tmp_514 = uint_fast16_t((((tmp_507 >> 0) & 4095)) & 4095);  // basic_select
    const uint_fast8_t tmp_515 = uint_fast8_t(((tmp_514 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_516 = uint_fast8_t(((tmp_513 | tmp_515)) & 1);  // basic_or
    const uint_fast8_t tmp_517 = uint_fast8_t((((tmp_507 >> 14) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_518 = uint_fast8_t(((tmp_516 | tmp_517)) & 1);  // basic_or
    const uint_fast8_t tmp_519 = uint_fast8_t(((tmp_512 & tmp_518)) & 1);  // basic_and
    const uint_fast32_t tmp_520 = uint_fast32_t((tmp_519) & 8388607);  // basic_identity
    const uint_fast32_t tmp_527 = uq_add_5(tmp_511, tmp_520);  // uq_add
    const uint_fast8_t tmp_528 = uint_fast8_t(((tmp_511 == 8388607)) & 1);  // basic_and_reduce
    const uint_fast8_t tmp_529 = uint_fast8_t(((tmp_528 & tmp_519)) & 1);  // basic_and
    const uint_fast32_t tmp_530 = uint_fast32_t(((tmp_529 >= 24 ? 0 : (tmp_527 >> tmp_529))) & 8388607);  // basic_rshift
    const std::array<uint_fast64_t, 2> tmp_531 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_530), static_cast<uint_fast64_t>(tmp_529)};  // basic_tuple_maker_2
    // end inline primitive uq_RNE_IEEE
    const uint_fast8_t tmp_532 = uint_fast8_t((tmp_531[1]) & 1);  // _basic_get_item_1
    const uint_fast16_t tmp_539 = uq_add_6(tmp_508, tmp_532);  // uq_add
    const uint_fast8_t tmp_540 = uint_fast8_t(((tmp_539 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_541 = uint_fast8_t(((tmp_509 & tmp_540)) & 1);  // basic_and
    const uint_fast32_t tmp_542 = uint_fast32_t((tmp_531[0]) & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_543 = uint_fast32_t(((tmp_541 != 0 ? uint_fast8_t((0) & 1) : tmp_542)) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_544 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_543), static_cast<uint_fast64_t>(tmp_539)};  // basic_tuple_maker_2
    // end inline primitive round_mantissa
    const uint_fast32_t tmp_545 = uint_fast32_t((tmp_544[0]) & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_546 = uint_fast16_t((tmp_544[1]) & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_552 = uq_min(tmp_546, uint_fast8_t((255) & 255));  // uq_min
    const uint_fast8_t tmp_553 = uint_fast8_t((tmp_552) & 255);  // basic_identity
    const uint_fast8_t tmp_554 = uint_fast8_t(((tmp_553 == 255)) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_555 = uint_fast32_t(((tmp_554 != 0 ? uint_fast8_t((0) & 1) : tmp_545)) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_556 = uint_fast32_t((tmp_555) & 8388607);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_557 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_556), static_cast<uint_fast64_t>(tmp_553)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_558 = uint_fast8_t((tmp_557[1]) & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_559 = uint_fast32_t((tmp_557[0]) & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_561 = fp32_pack(arg_0, tmp_558, tmp_559);  // fp32_pack
    const uint_fast32_t tmp_562 = uint_fast32_t(((tmp_195 != 0 ? tmp_196 : tmp_561)) & 4294967295);  // basic_mux_2_1
    const uint_fast32_t tmp_563 = uint_fast32_t(((arg_4 != 0 ? tmp_192 : tmp_562)) & 4294967295);  // basic_mux_2_1
    const uint_fast32_t tmp_564 = uint_fast32_t(((arg_3 != 0 ? uint_fast32_t((2139095041) & 4294967295) : tmp_563)) & 4294967295);  // basic_mux_2_1
    return tmp_564;
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
    const uint_fast8_t tmp_35 = uint_fast8_t((tmp_34[2]) & 1);  // _basic_get_item_2
    // begin inline composite fp32_classify
    const uint_fast8_t tmp_36 = fp32_is_normal(arg_1);  // fp32_is_normal
    const uint_fast8_t tmp_37 = fp32_is_subnormal(arg_1);  // fp32_is_subnormal
    const uint_fast8_t tmp_38 = fp32_is_zero(arg_1);  // fp32_is_zero
    const uint_fast8_t tmp_39 = fp32_is_inf(arg_1);  // fp32_is_inf
    const uint_fast8_t tmp_40 = fp32_is_nan(arg_1);  // fp32_is_nan
    const std::array<uint_fast64_t, 5> tmp_41 = std::array<uint_fast64_t, 5>{static_cast<uint_fast64_t>(tmp_36), static_cast<uint_fast64_t>(tmp_37), static_cast<uint_fast64_t>(tmp_38), static_cast<uint_fast64_t>(tmp_39), static_cast<uint_fast64_t>(tmp_40)};  // basic_tuple_maker_5
    // end inline composite fp32_classify
    const uint_fast8_t tmp_42 = uint_fast8_t((tmp_41[2]) & 1);  // _basic_get_item_2
    const uint_fast8_t tmp_43 = uint_fast8_t(((tmp_35 & tmp_42)) & 1);  // basic_and
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_44 = uint_fast8_t((((arg_0 >> 31) & 1)) & 1);  // _fp32_sign
    const uint_fast8_t tmp_45 = uint_fast8_t((((arg_0 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_46 = uint_fast32_t(((arg_0 & ((1 << 23) - 1))) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_47 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_44), static_cast<uint_fast64_t>(tmp_45), static_cast<uint_fast64_t>(tmp_46)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_48 = uint_fast8_t((tmp_47[0]) & 1);  // _basic_get_item_0
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_49 = uint_fast8_t((((arg_1 >> 31) & 1)) & 1);  // _fp32_sign
    const uint_fast8_t tmp_50 = uint_fast8_t((((arg_1 >> 23) & ((1 << 8) - 1))) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_51 = uint_fast32_t(((arg_1 & ((1 << 23) - 1))) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_52 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_49), static_cast<uint_fast64_t>(tmp_50), static_cast<uint_fast64_t>(tmp_51)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_53 = uint_fast8_t((tmp_52[0]) & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_54 = uint_fast8_t(((tmp_48 & tmp_53)) & 1);  // basic_and
    const uint_fast8_t tmp_55 = uint_fast8_t(((tmp_43 & tmp_54)) & 1);  // basic_and
    const uint_fast8_t tmp_56 = uint_fast8_t((tmp_34[0]) & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_57 = uint_fast32_t((tmp_47[2]) & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_58 = uint_fast32_t((tmp_57) & 8388607);  // basic_identity
    const uint_fast32_t tmp_60 = add_implicit_bit(tmp_58);  // add_implicit_bit
    const uint_fast32_t tmp_62 = uq_resize(tmp_58);  // uq_resize
    const uint_fast32_t tmp_63 = uint_fast32_t(((tmp_56 != 0 ? tmp_60 : tmp_62)) & 16777215);  // basic_mux_2_1
    const uint_fast32_t tmp_65 = uq_resize_1(tmp_63);  // uq_resize
    const uint_fast8_t tmp_66 = uint_fast8_t((tmp_34[1]) & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_67 = uint_fast8_t((tmp_47[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_68 = uint_fast8_t(((tmp_66 != 0 ? uint_fast8_t((1) & 255) : tmp_67)) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_69 = uint_fast8_t((tmp_41[1]) & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_70 = uint_fast8_t((tmp_52[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_71 = uint_fast8_t(((tmp_69 != 0 ? uint_fast8_t((1) & 255) : tmp_70)) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_76 = uq_max(tmp_68, tmp_71);  // uq_max
    const uint_fast16_t tmp_83 = uq_sub(tmp_76, tmp_68);  // uq_sub
    const uint_fast32_t tmp_108 = uq_rshift_jam(tmp_65, tmp_83);  // uq_rshift_jam
    const uint_fast32_t tmp_118 = uq_to_q(tmp_108);  // uq_to_q
    const uint_fast32_t tmp_127 = q_add_sign(tmp_118, tmp_48);  // q_add_sign
    const uint_fast8_t tmp_128 = uint_fast8_t((tmp_41[0]) & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_129 = uint_fast32_t((tmp_52[2]) & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_130 = uint_fast32_t((tmp_129) & 8388607);  // basic_identity
    const uint_fast32_t tmp_131 = add_implicit_bit(tmp_130);  // add_implicit_bit
    const uint_fast32_t tmp_132 = uq_resize(tmp_130);  // uq_resize
    const uint_fast32_t tmp_133 = uint_fast32_t(((tmp_128 != 0 ? tmp_131 : tmp_132)) & 16777215);  // basic_mux_2_1
    const uint_fast32_t tmp_134 = uq_resize_1(tmp_133);  // uq_resize
    const uint_fast16_t tmp_135 = uq_sub(tmp_76, tmp_71);  // uq_sub
    const uint_fast32_t tmp_136 = uq_rshift_jam(tmp_134, tmp_135);  // uq_rshift_jam
    const uint_fast32_t tmp_137 = uq_to_q(tmp_136);  // uq_to_q
    const uint_fast32_t tmp_138 = q_add_sign(tmp_137, tmp_53);  // q_add_sign
    const uint_fast32_t tmp_153 = q_add(tmp_127, tmp_138);  // q_add
    const uint_fast8_t tmp_155 = q_sign_bit_1(tmp_153);  // q_sign_bit
    const uint_fast8_t tmp_156 = uint_fast8_t(((tmp_55 != 0 ? uint_fast8_t((1) & 1) : tmp_155)) & 1);  // basic_mux_2_1
    const uint_fast16_t tmp_166 = uq_to_q_1(tmp_76);  // uq_to_q
    const uint_fast32_t tmp_177 = q_abs(tmp_153);  // q_abs
    const uint_fast32_t tmp_179 = q_to_uq(tmp_177);  // q_to_uq
    const uint_fast8_t tmp_180 = uint_fast8_t((tmp_34[3]) & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_181 = uint_fast8_t((tmp_41[3]) & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_182 = uint_fast8_t(((tmp_180 & tmp_181)) & 1);  // basic_and
    const uint_fast8_t tmp_183 = uint_fast8_t(((tmp_48 ^ tmp_53)) & 1);  // basic_xor
    const uint_fast8_t tmp_184 = uint_fast8_t(((tmp_182 & tmp_183)) & 1);  // basic_and
    const uint_fast8_t tmp_185 = uint_fast8_t((tmp_34[4]) & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_186 = uint_fast8_t((tmp_41[4]) & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_187 = uint_fast8_t(((tmp_185 | tmp_186)) & 1);  // basic_or
    const uint_fast8_t tmp_188 = uint_fast8_t(((tmp_184 | tmp_187)) & 1);  // basic_or
    const uint_fast8_t tmp_189 = uint_fast8_t((((~tmp_188) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_190 = uint_fast8_t(((tmp_180 | tmp_181)) & 1);  // basic_or
    const uint_fast8_t tmp_191 = uint_fast8_t(((tmp_189 & tmp_190)) & 1);  // basic_and
    const uint_fast32_t tmp_565 = fp32_encode(tmp_156, tmp_166, tmp_179, tmp_188, tmp_191);  // fp32_encode
    return tmp_565;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}