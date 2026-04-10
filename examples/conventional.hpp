#pragma once
#include <array>
#include <cstdint>

static inline uint_fast8_t add_implicit_bit(uint_fast8_t arg_0) {  // add_implicit_bit
    const uint_fast8_t tmp_5 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(1 & 1)) << 7) | arg_0) & 255);  // basic_concat
    return tmp_5;
}
static inline uint_fast16_t uq_mul(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_mul
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_13 = uint_fast16_t((uint_fast8_t(7 & 7) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(7 & 7))) & 65535);  // basic_lshift
    const uint_fast16_t tmp_14 = uint_fast16_t((uint_fast8_t(7 & 7) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(7 & 7))) & 65535);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_15 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_13), static_cast<uint_fast64_t>(tmp_14)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_16 = uint_fast16_t(tmp_15[0] & 65535);  // _basic_get_item_0
    const uint_fast16_t tmp_17 = uint_fast16_t((arg_0 * arg_1) & 65535);  // basic_mul
    return tmp_17;
}
static inline uint_fast32_t uq_resize(uint_fast16_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_19 = uint_fast32_t((uint_fast8_t(14 & 15) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(14 & 15))) & 1073741823);  // basic_lshift
    return tmp_19;
}
static inline uint_fast16_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_23 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_24 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_25 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_23), static_cast<uint_fast64_t>(tmp_24)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_26 = uint_fast16_t(tmp_25[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_27 = uint_fast16_t(tmp_25[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_28 = uint_fast16_t((tmp_26 + tmp_27) & 511);  // basic_add
    return tmp_28;
}
static inline uint_fast16_t uq_max(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_41 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_42 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_43 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_41), static_cast<uint_fast64_t>(tmp_42)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_44 = uint_fast16_t(tmp_43[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_45 = uint_fast16_t(tmp_43[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_46 = uint_fast16_t((tmp_44 > tmp_45 ? tmp_44 : tmp_45) & 511);  // basic_max
    return tmp_46;
}
static inline uint_fast16_t uq_sub(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_72 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_73 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_74 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_72), static_cast<uint_fast64_t>(tmp_73)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_75 = uint_fast16_t(tmp_74[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_76 = uint_fast16_t(tmp_74[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_77 = uint_fast16_t((tmp_75 - tmp_76) & 1023);  // basic_sub
    return tmp_77;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_79 = uint_fast32_t((arg_1 >= 30 ? 0 : (arg_0 >> arg_1)) & 1073741823);  // basic_rshift
    return tmp_79;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_81 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_82 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_83 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_81), static_cast<uint_fast64_t>(tmp_82)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_84 = uint_fast8_t(tmp_83[0] & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_85 = uint_fast8_t(tmp_83[1] & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_86 = uint_fast8_t((tmp_84 + tmp_85) & 7);  // basic_add
    return tmp_86;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_87 = uq_add_1(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast32_t tmp_88 = uint_fast32_t(0 & 2147483647);  // q_alloc
    const uint_fast32_t tmp_89 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_89;
}
static inline uint_fast8_t sign_xor(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // sign_xor
    const uint_fast8_t tmp_93 = uint_fast8_t((arg_0 ^ arg_1) & 1);  // basic_xor
    return tmp_93;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_95 = uint_fast8_t((arg_0 == 1073741824) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_96 = uint_fast32_t(((~arg_0) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_97 = uint_fast32_t((tmp_96 + uint_fast8_t(1 & 1)) & 2147483647);  // basic_add
    const uint_fast32_t tmp_98 = uint_fast32_t((arg_0 ^ arg_0) & 2147483647);  // basic_xor
    const uint_fast32_t tmp_99 = uint_fast32_t(((~tmp_98) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_100 = uint_fast32_t((tmp_95 == 1 ? tmp_99 : tmp_97) & 2147483647);  // basic_mux_2_1
    return tmp_100;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_101 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_102 = uint_fast32_t((arg_1 == 1 ? tmp_101 : arg_0) & 2147483647);  // basic_mux_2_1
    return tmp_102;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_118 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    return tmp_118;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_119 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_120 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_119) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_121 = uint_fast8_t((tmp_120 - tmp_119) & 1);  // basic_sub
    const uint_fast32_t tmp_122 = uint_fast32_t(0 & 4294967295);  // q_alloc
    const uint_fast32_t tmp_123 = uint_fast32_t(((uint_fast64_t(tmp_121) << 31) | arg_0) & 4294967295);  // basic_concat
    return tmp_123;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_117 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_124 = q_sign_extend(tmp_117);  // q_sign_extend
    const uint_fast32_t tmp_125 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_126 = q_sign_extend(tmp_125);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_127 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_124), static_cast<uint_fast64_t>(tmp_126)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_128 = uint_fast32_t(tmp_127[0] & 4294967295);  // _basic_get_item_0
    const uint_fast32_t tmp_129 = uint_fast32_t(tmp_127[1] & 4294967295);  // _basic_get_item_1
    const uint_fast32_t tmp_130 = uint_fast32_t((tmp_128 + tmp_129) & 4294967295);  // basic_add
    return tmp_130;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_160 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    return tmp_160;
}
static inline uint_fast64_t q_sign_extend_1(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_161 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_162 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_161) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_163 = uint_fast8_t((tmp_162 - tmp_161) & 1);  // basic_sub
    const uint_fast64_t tmp_164 = uint_fast64_t(0 & 8589934591);  // q_alloc
    const uint_fast64_t tmp_165 = uint_fast64_t(((uint_fast64_t(tmp_163) << 32) | arg_0) & 8589934591);  // basic_concat
    return tmp_165;
}
static inline uint_fast64_t q_add_1(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_159 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4294967295);  // basic_lshift
    const uint_fast64_t tmp_166 = q_sign_extend_1(tmp_159);  // q_sign_extend
    const uint_fast32_t tmp_167 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4294967295);  // basic_lshift
    const uint_fast64_t tmp_168 = q_sign_extend_1(tmp_167);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_169 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_166), static_cast<uint_fast64_t>(tmp_168)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_170 = uint_fast64_t(tmp_169[0] & 8589934591);  // _basic_get_item_0
    const uint_fast64_t tmp_171 = uint_fast64_t(tmp_169[1] & 8589934591);  // _basic_get_item_1
    const uint_fast64_t tmp_172 = uint_fast64_t((tmp_170 + tmp_171) & 8589934591);  // basic_add
    return tmp_172;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_174 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_175 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_176 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_174), static_cast<uint_fast64_t>(tmp_175)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_177 = uint_fast8_t(tmp_176[0] & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_178 = uint_fast8_t(tmp_176[1] & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_177 + tmp_178) & 31);  // basic_add
    return tmp_179;
}
static inline uint_fast16_t uq_to_q_1(uint_fast16_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_180 = uq_add_2(uint_fast8_t(9 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_181 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_182 = uint_fast16_t(arg_0 & 1023);  // basic_identity
    return tmp_182;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_185 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_185;
}
static inline uint_fast16_t q_sign_extend_2(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_186 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_187 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_186) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_188 = uint_fast8_t((tmp_187 - tmp_186) & 1);  // basic_sub
    const uint_fast16_t tmp_189 = uint_fast16_t(0 & 2047);  // q_alloc
    const uint_fast16_t tmp_190 = uint_fast16_t(((uint_fast64_t(tmp_188) << 10) | arg_0) & 2047);  // basic_concat
    return tmp_190;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_193 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_193;
}
static inline uint_fast16_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_194 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_195 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_194) << uint_fast8_t(3 & 3))) & 15);  // basic_lshift
    const uint_fast8_t tmp_196 = uint_fast8_t((tmp_195 - tmp_194) & 7);  // basic_sub
    const uint_fast16_t tmp_197 = uint_fast16_t(0 & 2047);  // q_alloc
    const uint_fast16_t tmp_198 = uint_fast16_t(((uint_fast64_t(tmp_196) << 8) | arg_0) & 2047);  // basic_concat
    return tmp_198;
}
static inline uint_fast16_t q_sub(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_184 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_191 = q_sign_extend_2(tmp_184);  // q_sign_extend
    const uint_fast8_t tmp_192 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_199 = q_sign_extend_3(tmp_192);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_200 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_191), static_cast<uint_fast64_t>(tmp_199)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_201 = uint_fast16_t(tmp_200[0] & 2047);  // _basic_get_item_0
    const uint_fast16_t tmp_202 = uint_fast16_t(tmp_200[1] & 2047);  // _basic_get_item_1
    const uint_fast16_t tmp_203 = uint_fast16_t((tmp_201 - tmp_202) & 2047);  // basic_sub
    return tmp_203;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast64_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_205 = uint_fast8_t(((arg_0 >> 32) & 1) & 1);  // basic_select
    return tmp_205;
}
static inline uint_fast64_t q_neg_1(uint_fast64_t arg_0) {  // q_neg
    const uint_fast8_t tmp_208 = uint_fast8_t((arg_0 == 4294967296) & 1);  // _q_is_min_val
    const uint_fast64_t tmp_209 = uint_fast64_t(((~arg_0) & 8589934591) & 8589934591);  // basic_invert
    const uint_fast64_t tmp_210 = uint_fast64_t((tmp_209 + uint_fast8_t(1 & 1)) & 8589934591);  // basic_add
    const uint_fast64_t tmp_211 = uint_fast64_t((arg_0 ^ arg_0) & 8589934591);  // basic_xor
    const uint_fast64_t tmp_212 = uint_fast64_t(((~tmp_211) & 8589934591) & 8589934591);  // basic_invert
    const uint_fast64_t tmp_213 = uint_fast64_t((tmp_208 == 1 ? tmp_212 : tmp_210) & 8589934591);  // basic_mux_2_1
    return tmp_213;
}
static inline uint_fast64_t q_add_sign_1(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast64_t tmp_214 = q_neg_1(arg_0);  // q_neg
    const uint_fast64_t tmp_215 = uint_fast64_t((arg_1 == 1 ? tmp_214 : arg_0) & 8589934591);  // basic_mux_2_1
    return tmp_215;
}
static inline uint_fast64_t q_abs(uint_fast64_t arg_0) {  // q_abs
    const uint_fast8_t tmp_207 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast64_t tmp_216 = q_add_sign_1(arg_0, tmp_207);  // q_add_sign
    return tmp_216;
}
static inline uint_fast32_t q_to_uq(uint_fast64_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_218 = uint_fast32_t(arg_0 & 4294967295);  // basic_identity
    return tmp_218;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_220 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_221 = uint_fast8_t(((~tmp_220) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_222 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_221) & 1);  // basic_and
    const uint_fast8_t tmp_223 = uint_fast8_t((uint_fast8_t(0 & 63) + tmp_222) & 63);  // basic_add
    const uint_fast8_t tmp_224 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_225 = uint_fast8_t(((~tmp_224) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_226 = uint_fast8_t((tmp_222 & tmp_225) & 1);  // basic_and
    const uint_fast8_t tmp_227 = uint_fast8_t((tmp_223 + tmp_226) & 63);  // basic_add
    const uint_fast8_t tmp_228 = uint_fast8_t(((arg_0 >> 29) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_229 = uint_fast8_t(((~tmp_228) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_230 = uint_fast8_t((tmp_226 & tmp_229) & 1);  // basic_and
    const uint_fast8_t tmp_231 = uint_fast8_t((tmp_227 + tmp_230) & 63);  // basic_add
    const uint_fast8_t tmp_232 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_233 = uint_fast8_t(((~tmp_232) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_234 = uint_fast8_t((tmp_230 & tmp_233) & 1);  // basic_and
    const uint_fast8_t tmp_235 = uint_fast8_t((tmp_231 + tmp_234) & 63);  // basic_add
    const uint_fast8_t tmp_236 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_237 = uint_fast8_t(((~tmp_236) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_238 = uint_fast8_t((tmp_234 & tmp_237) & 1);  // basic_and
    const uint_fast8_t tmp_239 = uint_fast8_t((tmp_235 + tmp_238) & 63);  // basic_add
    const uint_fast8_t tmp_240 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_241 = uint_fast8_t(((~tmp_240) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_242 = uint_fast8_t((tmp_238 & tmp_241) & 1);  // basic_and
    const uint_fast8_t tmp_243 = uint_fast8_t((tmp_239 + tmp_242) & 63);  // basic_add
    const uint_fast8_t tmp_244 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_245 = uint_fast8_t(((~tmp_244) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_246 = uint_fast8_t((tmp_242 & tmp_245) & 1);  // basic_and
    const uint_fast8_t tmp_247 = uint_fast8_t((tmp_243 + tmp_246) & 63);  // basic_add
    const uint_fast8_t tmp_248 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_249 = uint_fast8_t(((~tmp_248) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_250 = uint_fast8_t((tmp_246 & tmp_249) & 1);  // basic_and
    const uint_fast8_t tmp_251 = uint_fast8_t((tmp_247 + tmp_250) & 63);  // basic_add
    const uint_fast8_t tmp_252 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_253 = uint_fast8_t(((~tmp_252) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_254 = uint_fast8_t((tmp_250 & tmp_253) & 1);  // basic_and
    const uint_fast8_t tmp_255 = uint_fast8_t((tmp_251 + tmp_254) & 63);  // basic_add
    const uint_fast8_t tmp_256 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_257 = uint_fast8_t(((~tmp_256) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_258 = uint_fast8_t((tmp_254 & tmp_257) & 1);  // basic_and
    const uint_fast8_t tmp_259 = uint_fast8_t((tmp_255 + tmp_258) & 63);  // basic_add
    const uint_fast8_t tmp_260 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_261 = uint_fast8_t(((~tmp_260) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_262 = uint_fast8_t((tmp_258 & tmp_261) & 1);  // basic_and
    const uint_fast8_t tmp_263 = uint_fast8_t((tmp_259 + tmp_262) & 63);  // basic_add
    const uint_fast8_t tmp_264 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_265 = uint_fast8_t(((~tmp_264) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_266 = uint_fast8_t((tmp_262 & tmp_265) & 1);  // basic_and
    const uint_fast8_t tmp_267 = uint_fast8_t((tmp_263 + tmp_266) & 63);  // basic_add
    const uint_fast8_t tmp_268 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_269 = uint_fast8_t(((~tmp_268) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_270 = uint_fast8_t((tmp_266 & tmp_269) & 1);  // basic_and
    const uint_fast8_t tmp_271 = uint_fast8_t((tmp_267 + tmp_270) & 63);  // basic_add
    const uint_fast8_t tmp_272 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_273 = uint_fast8_t(((~tmp_272) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_274 = uint_fast8_t((tmp_270 & tmp_273) & 1);  // basic_and
    const uint_fast8_t tmp_275 = uint_fast8_t((tmp_271 + tmp_274) & 63);  // basic_add
    const uint_fast8_t tmp_276 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_277 = uint_fast8_t(((~tmp_276) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_278 = uint_fast8_t((tmp_274 & tmp_277) & 1);  // basic_and
    const uint_fast8_t tmp_279 = uint_fast8_t((tmp_275 + tmp_278) & 63);  // basic_add
    const uint_fast8_t tmp_280 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_281 = uint_fast8_t(((~tmp_280) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_282 = uint_fast8_t((tmp_278 & tmp_281) & 1);  // basic_and
    const uint_fast8_t tmp_283 = uint_fast8_t((tmp_279 + tmp_282) & 63);  // basic_add
    const uint_fast8_t tmp_284 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_285 = uint_fast8_t(((~tmp_284) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_286 = uint_fast8_t((tmp_282 & tmp_285) & 1);  // basic_and
    const uint_fast8_t tmp_287 = uint_fast8_t((tmp_283 + tmp_286) & 63);  // basic_add
    const uint_fast8_t tmp_288 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_289 = uint_fast8_t(((~tmp_288) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_290 = uint_fast8_t((tmp_286 & tmp_289) & 1);  // basic_and
    const uint_fast8_t tmp_291 = uint_fast8_t((tmp_287 + tmp_290) & 63);  // basic_add
    const uint_fast8_t tmp_292 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_293 = uint_fast8_t(((~tmp_292) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_294 = uint_fast8_t((tmp_290 & tmp_293) & 1);  // basic_and
    const uint_fast8_t tmp_295 = uint_fast8_t((tmp_291 + tmp_294) & 63);  // basic_add
    const uint_fast8_t tmp_296 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_297 = uint_fast8_t(((~tmp_296) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_298 = uint_fast8_t((tmp_294 & tmp_297) & 1);  // basic_and
    const uint_fast8_t tmp_299 = uint_fast8_t((tmp_295 + tmp_298) & 63);  // basic_add
    const uint_fast8_t tmp_300 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_301 = uint_fast8_t(((~tmp_300) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_302 = uint_fast8_t((tmp_298 & tmp_301) & 1);  // basic_and
    const uint_fast8_t tmp_303 = uint_fast8_t((tmp_299 + tmp_302) & 63);  // basic_add
    const uint_fast8_t tmp_304 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_305 = uint_fast8_t(((~tmp_304) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_306 = uint_fast8_t((tmp_302 & tmp_305) & 1);  // basic_and
    const uint_fast8_t tmp_307 = uint_fast8_t((tmp_303 + tmp_306) & 63);  // basic_add
    const uint_fast8_t tmp_308 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_309 = uint_fast8_t(((~tmp_308) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_310 = uint_fast8_t((tmp_306 & tmp_309) & 1);  // basic_and
    const uint_fast8_t tmp_311 = uint_fast8_t((tmp_307 + tmp_310) & 63);  // basic_add
    const uint_fast8_t tmp_312 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_313 = uint_fast8_t(((~tmp_312) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_314 = uint_fast8_t((tmp_310 & tmp_313) & 1);  // basic_and
    const uint_fast8_t tmp_315 = uint_fast8_t((tmp_311 + tmp_314) & 63);  // basic_add
    const uint_fast8_t tmp_316 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_317 = uint_fast8_t(((~tmp_316) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_318 = uint_fast8_t((tmp_314 & tmp_317) & 1);  // basic_and
    const uint_fast8_t tmp_319 = uint_fast8_t((tmp_315 + tmp_318) & 63);  // basic_add
    const uint_fast8_t tmp_320 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_321 = uint_fast8_t(((~tmp_320) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_322 = uint_fast8_t((tmp_318 & tmp_321) & 1);  // basic_and
    const uint_fast8_t tmp_323 = uint_fast8_t((tmp_319 + tmp_322) & 63);  // basic_add
    const uint_fast8_t tmp_324 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_325 = uint_fast8_t(((~tmp_324) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_326 = uint_fast8_t((tmp_322 & tmp_325) & 1);  // basic_and
    const uint_fast8_t tmp_327 = uint_fast8_t((tmp_323 + tmp_326) & 63);  // basic_add
    const uint_fast8_t tmp_328 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_329 = uint_fast8_t(((~tmp_328) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_330 = uint_fast8_t((tmp_326 & tmp_329) & 1);  // basic_and
    const uint_fast8_t tmp_331 = uint_fast8_t((tmp_327 + tmp_330) & 63);  // basic_add
    const uint_fast8_t tmp_332 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_333 = uint_fast8_t(((~tmp_332) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_334 = uint_fast8_t((tmp_330 & tmp_333) & 1);  // basic_and
    const uint_fast8_t tmp_335 = uint_fast8_t((tmp_331 + tmp_334) & 63);  // basic_add
    const uint_fast8_t tmp_336 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_337 = uint_fast8_t(((~tmp_336) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_338 = uint_fast8_t((tmp_334 & tmp_337) & 1);  // basic_and
    const uint_fast8_t tmp_339 = uint_fast8_t((tmp_335 + tmp_338) & 63);  // basic_add
    const uint_fast8_t tmp_340 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_341 = uint_fast8_t(((~tmp_340) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_342 = uint_fast8_t((tmp_338 & tmp_341) & 1);  // basic_and
    const uint_fast8_t tmp_343 = uint_fast8_t((tmp_339 + tmp_342) & 63);  // basic_add
    const uint_fast8_t tmp_344 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_345 = uint_fast8_t(((~tmp_344) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_346 = uint_fast8_t((tmp_342 & tmp_345) & 1);  // basic_and
    const uint_fast8_t tmp_347 = uint_fast8_t((tmp_343 + tmp_346) & 63);  // basic_add
    return tmp_347;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_349 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_350 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_351 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_349), static_cast<uint_fast64_t>(tmp_350)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_352 = uint_fast8_t(tmp_351[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_353 = uint_fast8_t(tmp_351[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_354 = uint_fast8_t((tmp_352 + tmp_353) & 15);  // basic_add
    return tmp_354;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_355 = uq_add_3(uint_fast8_t(6 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_356 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_357 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_357;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_359 = uq_add_1(uint_fast8_t(3 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_360 = uint_fast8_t(0 & 15);  // q_alloc
    const uint_fast8_t tmp_361 = uint_fast8_t(arg_0 & 15);  // basic_identity
    return tmp_361;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_364 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_364;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_365 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_366 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_365) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_367 = uint_fast8_t((tmp_366 - tmp_365) & 1);  // basic_sub
    const uint_fast8_t tmp_368 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_369 = uint_fast8_t(((uint_fast64_t(tmp_367) << 7) | arg_0) & 255);  // basic_concat
    return tmp_369;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_372 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    return tmp_372;
}
static inline uint_fast8_t q_sign_extend_5(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_373 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_374 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_373) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_375 = uint_fast8_t((tmp_374 - tmp_373) & 15);  // basic_sub
    const uint_fast8_t tmp_376 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_377 = uint_fast8_t(((uint_fast64_t(tmp_375) << 4) | arg_0) & 255);  // basic_concat
    return tmp_377;
}
static inline uint_fast8_t q_sub_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_363 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_370 = q_sign_extend_4(tmp_363);  // q_sign_extend
    const uint_fast8_t tmp_371 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_378 = q_sign_extend_5(tmp_371);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_379 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_370), static_cast<uint_fast64_t>(tmp_378)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_380 = uint_fast8_t(tmp_379[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_381 = uint_fast8_t(tmp_379[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_382 = uint_fast8_t((tmp_380 - tmp_381) & 255);  // basic_sub
    return tmp_382;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_385 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_386 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_385) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_387 = uint_fast8_t((tmp_386 - tmp_385) & 1);  // basic_sub
    const uint_fast16_t tmp_388 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_389 = uint_fast16_t(((uint_fast64_t(tmp_387) << 8) | arg_0) & 511);  // basic_concat
    return tmp_389;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_392 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_392;
}
static inline uint_fast16_t q_sign_extend_7(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_393 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_394 = uint_fast8_t((uint_fast8_t(7 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_393) << uint_fast8_t(7 & 7))) & 255);  // basic_lshift
    const uint_fast8_t tmp_395 = uint_fast8_t((tmp_394 - tmp_393) & 127);  // basic_sub
    const uint_fast16_t tmp_396 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_397 = uint_fast16_t(((uint_fast64_t(tmp_395) << 2) | arg_0) & 511);  // basic_concat
    return tmp_397;
}
static inline uint_fast16_t q_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_384 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_390 = q_sign_extend_6(tmp_384);  // q_sign_extend
    const uint_fast8_t tmp_391 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast16_t tmp_398 = q_sign_extend_7(tmp_391);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_399 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_390), static_cast<uint_fast64_t>(tmp_398)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_400 = uint_fast16_t(tmp_399[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_401 = uint_fast16_t(tmp_399[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_402 = uint_fast16_t((tmp_400 + tmp_401) & 511);  // basic_add
    return tmp_402;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_404 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_404;
}
static inline uint_fast64_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast64_t tmp_406 = uint_fast64_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(3 & 3))) & 34359738367);  // basic_lshift
    return tmp_406;
}
static inline uint_fast16_t q_neg_2(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_409 = uint_fast8_t((arg_0 == 256) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_410 = uint_fast16_t(((~arg_0) & 511) & 511);  // basic_invert
    const uint_fast16_t tmp_411 = uint_fast16_t((tmp_410 + uint_fast8_t(1 & 1)) & 511);  // basic_add
    const uint_fast16_t tmp_412 = uint_fast16_t((arg_0 ^ arg_0) & 511);  // basic_xor
    const uint_fast16_t tmp_413 = uint_fast16_t(((~tmp_412) & 511) & 511);  // basic_invert
    const uint_fast16_t tmp_414 = uint_fast16_t((tmp_409 == 1 ? tmp_413 : tmp_411) & 511);  // basic_mux_2_1
    return tmp_414;
}
static inline uint_fast16_t q_add_sign_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_415 = q_neg_2(arg_0);  // q_neg
    const uint_fast16_t tmp_416 = uint_fast16_t((arg_1 == 1 ? tmp_415 : arg_0) & 511);  // basic_mux_2_1
    return tmp_416;
}
static inline uint_fast16_t q_abs_1(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_408 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_417 = q_add_sign_2(arg_0, tmp_408);  // q_add_sign
    return tmp_417;
}
static inline uint_fast8_t q_to_uq_1(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_419 = uint_fast8_t(arg_0 & 255);  // basic_identity
    return tmp_419;
}
static inline uint_fast64_t uq_lshift(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast64_t tmp_421 = uint_fast64_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 34359738367);  // basic_lshift
    return tmp_421;
}
static inline uint_fast64_t uq_rshift_1(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_423 = uint_fast64_t((arg_1 >= 35 ? 0 : (arg_0 >> arg_1)) & 34359738367);  // basic_rshift
    return tmp_423;
}
static inline uint_fast8_t q_sign_bit_9(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_427 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    return tmp_427;
}
static inline uint_fast16_t q_sign_extend_8(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_428 = q_sign_bit_9(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_429 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_428) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_430 = uint_fast8_t((tmp_429 - tmp_428) & 1);  // basic_sub
    const uint_fast16_t tmp_431 = uint_fast16_t(0 & 4095);  // q_alloc
    const uint_fast16_t tmp_432 = uint_fast16_t(((uint_fast64_t(tmp_430) << 11) | arg_0) & 4095);  // basic_concat
    return tmp_432;
}
static inline uint_fast16_t q_sign_extend_9(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_435 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_436 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_435) << uint_fast8_t(3 & 3))) & 15);  // basic_lshift
    const uint_fast8_t tmp_437 = uint_fast8_t((tmp_436 - tmp_435) & 7);  // basic_sub
    const uint_fast16_t tmp_438 = uint_fast16_t(0 & 4095);  // q_alloc
    const uint_fast16_t tmp_439 = uint_fast16_t(((uint_fast64_t(tmp_437) << 9) | arg_0) & 4095);  // basic_concat
    return tmp_439;
}
static inline uint_fast16_t q_sub_2(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_426 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const uint_fast16_t tmp_433 = q_sign_extend_8(tmp_426);  // q_sign_extend
    const uint_fast16_t tmp_434 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_440 = q_sign_extend_9(tmp_434);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_441 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_433), static_cast<uint_fast64_t>(tmp_440)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_442 = uint_fast16_t(tmp_441[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_443 = uint_fast16_t(tmp_441[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_444 = uint_fast16_t((tmp_442 - tmp_443) & 4095);  // basic_sub
    return tmp_444;
}
static inline uint_fast16_t q_add_3(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_446 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const uint_fast16_t tmp_447 = q_sign_extend_8(tmp_446);  // q_sign_extend
    const uint_fast16_t tmp_448 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_449 = q_sign_extend_9(tmp_448);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_450 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_447), static_cast<uint_fast64_t>(tmp_449)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_451 = uint_fast16_t(tmp_450[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_452 = uint_fast16_t(tmp_450[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_453 = uint_fast16_t((tmp_451 + tmp_452) & 4095);  // basic_add
    return tmp_453;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_460 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_461 = uint_fast8_t(((~tmp_460) & 1) & 1);  // basic_invert
    return tmp_461;
}
static inline uint_fast8_t q_sign_bit_10(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_463 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    return tmp_463;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_467 = uint_fast8_t((arg_0 == 2048) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_468 = uint_fast16_t(((~arg_0) & 4095) & 4095);  // basic_invert
    const uint_fast16_t tmp_469 = uint_fast16_t((tmp_468 + uint_fast8_t(1 & 1)) & 4095);  // basic_add
    const uint_fast16_t tmp_470 = uint_fast16_t((arg_0 ^ arg_0) & 4095);  // basic_xor
    const uint_fast16_t tmp_471 = uint_fast16_t(((~tmp_470) & 4095) & 4095);  // basic_invert
    const uint_fast16_t tmp_472 = uint_fast16_t((tmp_467 == 1 ? tmp_471 : tmp_469) & 4095);  // basic_mux_2_1
    return tmp_472;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_473 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_474 = uint_fast16_t((arg_1 == 1 ? tmp_473 : arg_0) & 4095);  // basic_mux_2_1
    return tmp_474;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_466 = q_sign_bit_10(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_475 = q_add_sign_3(arg_0, tmp_466);  // q_add_sign
    return tmp_475;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_477 = uint_fast16_t(arg_0 & 2047);  // basic_identity
    return tmp_477;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_479 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_480 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_481 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_479), static_cast<uint_fast64_t>(tmp_480)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_482 = uint_fast16_t(tmp_481[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_483 = uint_fast16_t(tmp_481[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_484 = uint_fast16_t((tmp_482 + tmp_483) & 4095);  // basic_add
    return tmp_484;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_487 = uint_fast64_t((arg_1 >= 42 ? 0 : (arg_0 >> arg_1)) & 4398046511103);  // basic_rshift
    return tmp_487;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_492 = uint_fast64_t(((arg_0 >> 0) & 2199023255551) & 2199023255551);  // basic_select
    return tmp_492;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_495 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_496 = uint_fast8_t(((~tmp_495) & 1) & 1);  // basic_invert
    return tmp_496;
}
static inline uint_fast32_t uq_resize_2(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_498 = uint_fast32_t((uint_fast8_t(18 & 31) >= 41 ? 0 : (arg_0 >> uint_fast8_t(18 & 31))) & 8388607);  // basic_rshift
    return tmp_498;
}
static inline uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_500 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_501 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_502 = uint_fast16_t(((arg_0 >> 0) & 65535) & 65535);  // basic_select
    const uint_fast8_t tmp_503 = uint_fast8_t((tmp_502 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_504 = uint_fast8_t((tmp_501 | tmp_503) & 1);  // basic_or
    const uint_fast8_t tmp_505 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_506 = uint_fast8_t((tmp_504 | tmp_505) & 1);  // basic_or
    const uint_fast8_t tmp_507 = uint_fast8_t((tmp_500 & tmp_506) & 1);  // basic_and
    const uint_fast32_t tmp_508 = uint_fast32_t(tmp_507 & 8388607);  // basic_identity
    return tmp_508;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_510 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_511 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_512 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_510), static_cast<uint_fast64_t>(tmp_511)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_513 = uint_fast32_t(tmp_512[0] & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_514 = uint_fast32_t(tmp_512[1] & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_515 = uint_fast32_t((tmp_513 + tmp_514) & 16777215);  // basic_add
    return tmp_515;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_518 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_519 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_520 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_518), static_cast<uint_fast64_t>(tmp_519)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_521 = uint_fast16_t(tmp_520[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_522 = uint_fast16_t(tmp_520[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_523 = uint_fast16_t((tmp_521 + tmp_522) & 4095);  // basic_add
    return tmp_523;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_533 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_534 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_535 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_533), static_cast<uint_fast64_t>(tmp_534)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_536 = uint_fast16_t(tmp_535[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_537 = uint_fast16_t(tmp_535[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_538 = uint_fast16_t((tmp_536 < tmp_537 ? tmp_536 : tmp_537) & 4095);  // basic_min
    return tmp_538;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_545 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_546 = uint_fast8_t(((~tmp_545) & 1) & 1);  // basic_invert
    return tmp_546;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_553 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_553;
}
static inline uint_fast32_t encode_Float32(uint_fast64_t arg_0, uint_fast16_t arg_1, uint_fast8_t arg_2) {  // encode_Float32
    const uint_fast8_t tmp_206 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast64_t tmp_217 = q_abs(arg_0);  // q_abs
    const uint_fast32_t tmp_219 = q_to_uq(tmp_217);  // q_to_uq
    // begin inline primitive fp32_normalize
    const uint_fast8_t tmp_348 = lzc(tmp_219);  // lzc
    const uint_fast8_t tmp_358 = uq_to_q_2(tmp_348);  // uq_to_q
    const uint_fast8_t tmp_362 = uq_to_q_3(uint_fast8_t(4 & 7));  // uq_to_q
    const uint_fast8_t tmp_383 = q_sub_1(tmp_358, tmp_362);  // q_sub
    const uint_fast16_t tmp_403 = q_add_2(tmp_383, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_405 = q_sign_bit_8(tmp_403);  // q_sign_bit
    const uint_fast64_t tmp_407 = uq_resize_1(tmp_219);  // uq_resize
    const uint_fast16_t tmp_418 = q_abs_1(tmp_403);  // q_abs
    const uint_fast8_t tmp_420 = q_to_uq_1(tmp_418);  // q_to_uq
    const uint_fast64_t tmp_422 = uq_lshift(tmp_407, tmp_420);  // uq_lshift
    const uint_fast64_t tmp_424 = uq_rshift_1(tmp_407, tmp_420);  // uq_rshift
    const uint_fast32_t tmp_425 = uint_fast32_t((tmp_405 == 1 ? tmp_424 : tmp_422) & 4294967295);  // basic_mux_2_1
    const uint_fast16_t tmp_445 = q_sub_2(arg_1, tmp_418);  // q_sub
    const uint_fast16_t tmp_454 = q_add_3(arg_1, tmp_418);  // q_add
    const uint_fast16_t tmp_455 = uint_fast16_t((tmp_405 == 1 ? tmp_454 : tmp_445) & 4095);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_456 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_425), static_cast<uint_fast64_t>(tmp_455)};  // basic_tuple_maker_2
    // end inline primitive fp32_normalize
    const uint_fast32_t tmp_457 = uint_fast32_t(tmp_456[0] & 4294967295);  // _basic_get_item_0
    const uint_fast16_t tmp_458 = uint_fast16_t(tmp_456[1] & 4095);  // _basic_get_item_1
    // begin inline primitive fp32_classify
    const uint_fast64_t tmp_459 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_457) << uint_fast8_t(10 & 15))) & 4398046511103);  // basic_lshift
    const uint_fast8_t tmp_462 = q_is_zero(tmp_458);  // q_is_zero
    const uint_fast8_t tmp_464 = q_sign_bit_10(tmp_458);  // q_sign_bit
    const uint_fast8_t tmp_465 = uint_fast8_t((tmp_462 | tmp_464) & 1);  // basic_or
    const uint_fast16_t tmp_476 = q_abs_2(tmp_458);  // q_abs
    const uint_fast16_t tmp_478 = q_to_uq_2(tmp_476);  // q_to_uq
    const uint_fast16_t tmp_485 = uq_add_4(uint_fast8_t(1 & 1), tmp_478);  // uq_add
    const uint_fast16_t tmp_486 = uint_fast16_t((tmp_465 == 1 ? tmp_485 : uint_fast8_t(0 & 1)) & 4095);  // basic_mux_2_1
    const uint_fast64_t tmp_488 = uq_rshift_2(tmp_459, tmp_486);  // uq_rshift
    const uint_fast16_t tmp_489 = uint_fast16_t((tmp_465 == 1 ? uint_fast8_t(0 & 1) : tmp_478) & 2047);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_490 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_488), static_cast<uint_fast64_t>(tmp_489)};  // basic_tuple_maker_2
    // end inline primitive fp32_classify
    const uint_fast64_t tmp_491 = uint_fast64_t(tmp_490[0] & 4398046511103);  // _basic_get_item_0
    const uint_fast64_t tmp_493 = drop_implicit_bit(tmp_491);  // drop_implicit_bit
    const uint_fast16_t tmp_494 = uint_fast16_t(tmp_490[1] & 2047);  // _basic_get_item_1
    // begin inline primitive fp32_round
    const uint_fast8_t tmp_497 = uq_is_zero(tmp_494);  // uq_is_zero
    const uint_fast32_t tmp_499 = uq_resize_2(tmp_493);  // uq_resize
    const uint_fast32_t tmp_509 = uq_RNE_IEEE(tmp_493);  // uq_RNE_IEEE
    const uint_fast32_t tmp_516 = uq_add_5(tmp_499, tmp_509);  // uq_add
    const uint_fast8_t tmp_517 = uint_fast8_t(((tmp_516 >> 23) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_524 = uq_add_6(tmp_494, tmp_517);  // uq_add
    const uint_fast8_t tmp_525 = uint_fast8_t((tmp_524 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_526 = uint_fast8_t((tmp_497 & tmp_525) & 1);  // basic_and
    const uint_fast32_t tmp_527 = uint_fast32_t((uint_fast8_t(1 & 1) >= 24 ? 0 : (tmp_516 >> uint_fast8_t(1 & 1))) & 8388607);  // basic_rshift
    const uint_fast32_t tmp_528 = uint_fast32_t((tmp_517 == 1 ? tmp_527 : tmp_516) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_529 = uint_fast32_t((tmp_526 == 1 ? uint_fast8_t(0 & 1) : tmp_528) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_530 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_529), static_cast<uint_fast64_t>(tmp_524)};  // basic_tuple_maker_2
    // end inline primitive fp32_round
    const uint_fast32_t tmp_531 = uint_fast32_t(tmp_530[0] & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_532 = uint_fast16_t(tmp_530[1] & 4095);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_539 = uq_min(tmp_532, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_540 = uint_fast8_t(tmp_539 & 255);  // basic_identity
    const uint_fast8_t tmp_541 = uint_fast8_t((tmp_540 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_542 = uint_fast32_t((tmp_541 == 1 ? uint_fast8_t(0 & 1) : tmp_531) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_543 = uint_fast32_t((arg_2 == 1 ? uint_fast8_t(1 & 1) : tmp_542) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_544 = uint_fast32_t(tmp_543 & 8388607);  // basic_identity
    const uint_fast8_t tmp_547 = uq_is_zero_1(tmp_219);  // uq_is_zero
    const uint_fast8_t tmp_548 = uint_fast8_t((tmp_547 == 1 ? uint_fast8_t(0 & 1) : tmp_540) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_549 = uint_fast8_t((arg_2 == 1 ? uint_fast8_t(255 & 255) : tmp_548) & 255);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_550 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_544), static_cast<uint_fast64_t>(tmp_549)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_551 = uint_fast8_t(tmp_550[1] & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_552 = uint_fast32_t(tmp_550[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_554 = fp32_pack(tmp_206, tmp_551, tmp_552);  // fp32_pack
    return tmp_554;
}
static inline uint_fast32_t Conventional_impl(uint_fast16_t arg_0, uint_fast16_t arg_1, uint_fast16_t arg_2, uint_fast16_t arg_3, uint_fast16_t arg_4, uint_fast16_t arg_5, uint_fast16_t arg_6, uint_fast16_t arg_7) {  // Conventional
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_1 = uint_fast8_t(((arg_0 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_2 = uint_fast8_t(((arg_0 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_3 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp), static_cast<uint_fast64_t>(tmp_1), static_cast<uint_fast64_t>(tmp_2)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_4 = uint_fast8_t(tmp_3[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_6 = add_implicit_bit(tmp_4);  // add_implicit_bit
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_7 = uint_fast8_t(((arg_4 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_8 = uint_fast8_t(((arg_4 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_9 = uint_fast8_t(((arg_4 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_10 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_7), static_cast<uint_fast64_t>(tmp_8), static_cast<uint_fast64_t>(tmp_9)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_11 = uint_fast8_t(tmp_10[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_12 = add_implicit_bit(tmp_11);  // add_implicit_bit
    const uint_fast16_t tmp_18 = uq_mul(tmp_6, tmp_12);  // uq_mul
    const uint_fast32_t tmp_20 = uq_resize(tmp_18);  // uq_resize
    const uint_fast8_t tmp_21 = uint_fast8_t(tmp_3[2] & 255);  // _basic_get_item_2
    const uint_fast8_t tmp_22 = uint_fast8_t(tmp_10[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_29 = uq_add(tmp_21, tmp_22);  // uq_add
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_30 = uint_fast8_t(((arg_1 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_31 = uint_fast8_t(((arg_1 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_32 = uint_fast8_t(((arg_1 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_33 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_30), static_cast<uint_fast64_t>(tmp_31), static_cast<uint_fast64_t>(tmp_32)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_34 = uint_fast8_t(tmp_33[2] & 255);  // _basic_get_item_2
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_35 = uint_fast8_t(((arg_5 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_36 = uint_fast8_t(((arg_5 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_37 = uint_fast8_t(((arg_5 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_38 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_35), static_cast<uint_fast64_t>(tmp_36), static_cast<uint_fast64_t>(tmp_37)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_39 = uint_fast8_t(tmp_38[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_40 = uq_add(tmp_34, tmp_39);  // uq_add
    const uint_fast16_t tmp_47 = uq_max(tmp_29, tmp_40);  // uq_max
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_48 = uint_fast8_t(((arg_2 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_49 = uint_fast8_t(((arg_2 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_50 = uint_fast8_t(((arg_2 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_51 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_48), static_cast<uint_fast64_t>(tmp_49), static_cast<uint_fast64_t>(tmp_50)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_52 = uint_fast8_t(tmp_51[2] & 255);  // _basic_get_item_2
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_53 = uint_fast8_t(((arg_6 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_54 = uint_fast8_t(((arg_6 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_55 = uint_fast8_t(((arg_6 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_56 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_53), static_cast<uint_fast64_t>(tmp_54), static_cast<uint_fast64_t>(tmp_55)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_57 = uint_fast8_t(tmp_56[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_58 = uq_add(tmp_52, tmp_57);  // uq_add
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_59 = uint_fast8_t(((arg_3 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_60 = uint_fast8_t(((arg_3 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_61 = uint_fast8_t(((arg_3 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_62 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_59), static_cast<uint_fast64_t>(tmp_60), static_cast<uint_fast64_t>(tmp_61)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_63 = uint_fast8_t(tmp_62[2] & 255);  // _basic_get_item_2
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_64 = uint_fast8_t(((arg_7 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_65 = uint_fast8_t(((arg_7 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_66 = uint_fast8_t(((arg_7 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_67 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_64), static_cast<uint_fast64_t>(tmp_65), static_cast<uint_fast64_t>(tmp_66)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_68 = uint_fast8_t(tmp_67[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_69 = uq_add(tmp_63, tmp_68);  // uq_add
    const uint_fast16_t tmp_70 = uq_max(tmp_58, tmp_69);  // uq_max
    const uint_fast16_t tmp_71 = uq_max(tmp_47, tmp_70);  // uq_max
    const uint_fast16_t tmp_78 = uq_sub(tmp_71, tmp_29);  // uq_sub
    const uint_fast32_t tmp_80 = uq_rshift(tmp_20, tmp_78);  // uq_rshift
    const uint_fast32_t tmp_90 = uq_to_q(tmp_80);  // uq_to_q
    const uint_fast8_t tmp_91 = uint_fast8_t(tmp_3[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_92 = uint_fast8_t(tmp_10[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_94 = sign_xor(tmp_91, tmp_92);  // sign_xor
    const uint_fast32_t tmp_103 = q_add_sign(tmp_90, tmp_94);  // q_add_sign
    const uint_fast8_t tmp_104 = uint_fast8_t(tmp_33[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_105 = add_implicit_bit(tmp_104);  // add_implicit_bit
    const uint_fast8_t tmp_106 = uint_fast8_t(tmp_38[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_107 = add_implicit_bit(tmp_106);  // add_implicit_bit
    const uint_fast16_t tmp_108 = uq_mul(tmp_105, tmp_107);  // uq_mul
    const uint_fast32_t tmp_109 = uq_resize(tmp_108);  // uq_resize
    const uint_fast16_t tmp_110 = uq_sub(tmp_71, tmp_40);  // uq_sub
    const uint_fast32_t tmp_111 = uq_rshift(tmp_109, tmp_110);  // uq_rshift
    const uint_fast32_t tmp_112 = uq_to_q(tmp_111);  // uq_to_q
    const uint_fast8_t tmp_113 = uint_fast8_t(tmp_33[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_114 = uint_fast8_t(tmp_38[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_115 = sign_xor(tmp_113, tmp_114);  // sign_xor
    const uint_fast32_t tmp_116 = q_add_sign(tmp_112, tmp_115);  // q_add_sign
    const uint_fast32_t tmp_131 = q_add(tmp_103, tmp_116);  // q_add
    const uint_fast8_t tmp_132 = uint_fast8_t(tmp_51[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_133 = add_implicit_bit(tmp_132);  // add_implicit_bit
    const uint_fast8_t tmp_134 = uint_fast8_t(tmp_56[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_135 = add_implicit_bit(tmp_134);  // add_implicit_bit
    const uint_fast16_t tmp_136 = uq_mul(tmp_133, tmp_135);  // uq_mul
    const uint_fast32_t tmp_137 = uq_resize(tmp_136);  // uq_resize
    const uint_fast16_t tmp_138 = uq_sub(tmp_71, tmp_58);  // uq_sub
    const uint_fast32_t tmp_139 = uq_rshift(tmp_137, tmp_138);  // uq_rshift
    const uint_fast32_t tmp_140 = uq_to_q(tmp_139);  // uq_to_q
    const uint_fast8_t tmp_141 = uint_fast8_t(tmp_51[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_142 = uint_fast8_t(tmp_56[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_143 = sign_xor(tmp_141, tmp_142);  // sign_xor
    const uint_fast32_t tmp_144 = q_add_sign(tmp_140, tmp_143);  // q_add_sign
    const uint_fast8_t tmp_145 = uint_fast8_t(tmp_62[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_146 = add_implicit_bit(tmp_145);  // add_implicit_bit
    const uint_fast8_t tmp_147 = uint_fast8_t(tmp_67[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_148 = add_implicit_bit(tmp_147);  // add_implicit_bit
    const uint_fast16_t tmp_149 = uq_mul(tmp_146, tmp_148);  // uq_mul
    const uint_fast32_t tmp_150 = uq_resize(tmp_149);  // uq_resize
    const uint_fast16_t tmp_151 = uq_sub(tmp_71, tmp_69);  // uq_sub
    const uint_fast32_t tmp_152 = uq_rshift(tmp_150, tmp_151);  // uq_rshift
    const uint_fast32_t tmp_153 = uq_to_q(tmp_152);  // uq_to_q
    const uint_fast8_t tmp_154 = uint_fast8_t(tmp_62[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_155 = uint_fast8_t(tmp_67[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_156 = sign_xor(tmp_154, tmp_155);  // sign_xor
    const uint_fast32_t tmp_157 = q_add_sign(tmp_153, tmp_156);  // q_add_sign
    const uint_fast32_t tmp_158 = q_add(tmp_144, tmp_157);  // q_add
    const uint_fast64_t tmp_173 = q_add_1(tmp_131, tmp_158);  // q_add
    const uint_fast16_t tmp_183 = uq_to_q_1(tmp_71);  // uq_to_q
    const uint_fast16_t tmp_204 = q_sub(tmp_183, uint_fast8_t(127 & 255));  // q_sub
    const uint_fast32_t tmp_555 = encode_Float32(tmp_173, tmp_204, uint_fast8_t(0 & 1));  // encode_Float32
    return tmp_555;
}
extern "C" inline uint_fast32_t Conventional(uint_fast16_t arg_0, uint_fast16_t arg_1, uint_fast16_t arg_2, uint_fast16_t arg_3, uint_fast16_t arg_4, uint_fast16_t arg_5, uint_fast16_t arg_6, uint_fast16_t arg_7) {
    return Conventional_impl((arg_0 & 65535), (arg_1 & 65535), (arg_2 & 65535), (arg_3 & 65535), (arg_4 & 65535), (arg_5 & 65535), (arg_6 & 65535), (arg_7 & 65535));
}