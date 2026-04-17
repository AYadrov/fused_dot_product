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
    const uint_fast32_t tmp_64 = uint_fast32_t(((uint_fast8_t((3) & 3) >= 27 ? uint_fast32_t(0) : (uint_fast32_t(arg_0) << uint_fast8_t((3) & 3)))) & 134217727);  // basic_lshift
    return tmp_64;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const std::array<uint_fast64_t, 2> tmp_72 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(arg_1)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_73 = uint_fast8_t((tmp_72[0]) & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_74 = uint_fast8_t((tmp_72[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_75 = uint_fast8_t(((tmp_73 > tmp_74 ? uint_fast8_t(tmp_73) : uint_fast8_t(tmp_74))) & 255);  // basic_max
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
    const uint_fast32_t tmp_84 = uint_fast32_t(((arg_1 >= 27 ? uint_fast32_t(0) : (arg_0 >> arg_1))) & 134217727);  // basic_rshift
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
    const uint_fast32_t tmp_102 = uint_fast32_t(((tmp_101 >= 27 ? uint_fast32_t(0) : (uint_fast32_t(arg_0) << tmp_101))) & 134217727);  // basic_lshift
    const uint_fast8_t tmp_103 = uint_fast8_t(((tmp_102 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_104 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_105 = uint_fast8_t(((tmp_94 != 0 ? uint_fast8_t(tmp_104) : uint_fast8_t(tmp_103))) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_106 = uint_fast8_t(((tmp_88 != 0 ? uint_fast8_t(uint_fast8_t((0) & 1)) : uint_fast8_t(tmp_105))) & 1);  // basic_mux_2_1
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
    const uint_fast32_t tmp_124 = uint_fast32_t(((tmp_119 != 0 ? uint_fast32_t(tmp_123) : uint_fast32_t(tmp_121))) & 268435455);  // basic_mux_2_1
    return tmp_124;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_125 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_126 = uint_fast32_t(((arg_1 != 0 ? uint_fast32_t(tmp_125) : uint_fast32_t(arg_0))) & 268435455);  // basic_mux_2_1
    return tmp_126;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_139 = uint_fast8_t((((arg_0 >> 27) & 1)) & 1);  // basic_select
    return tmp_139;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_140 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_141 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? uint_fast8_t(0) : (uint_fast8_t(tmp_140) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_142 = uint_fast8_t(((uint_fast8_t(tmp_141) - uint_fast8_t(tmp_140))) & 1);  // basic_sub
    const uint_fast32_t tmp_143 = uint_fast32_t((0) & 536870911);  // q_alloc
    const uint_fast32_t tmp_144 = uint_fast32_t((((uint_fast32_t(tmp_142) << 28) | arg_0)) & 536870911);  // basic_concat
    return tmp_144;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_145 = q_sign_extend(arg_0);  // q_sign_extend
    const uint_fast32_t tmp_146 = q_sign_extend(arg_1);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_147 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_145), static_cast<uint_fast64_t>(tmp_146)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_148 = uint_fast32_t((tmp_147[0]) & 536870911);  // _basic_get_item_0
    const uint_fast32_t tmp_149 = uint_fast32_t((tmp_147[1]) & 536870911);  // _basic_get_item_1
    const uint_fast32_t tmp_150 = uint_fast32_t(((uint_fast32_t(tmp_148) + uint_fast32_t(tmp_149))) & 536870911);  // basic_add
    return tmp_150;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_152 = uint_fast8_t((((arg_0 >> 28) & 1)) & 1);  // basic_select
    return tmp_152;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_155 = uint_fast8_t((arg_0) & 31);  // basic_identity
    const uint_fast8_t tmp_156 = uint_fast8_t((arg_1) & 31);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_157 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_155), static_cast<uint_fast64_t>(tmp_156)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_158 = uint_fast8_t((tmp_157[0]) & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_159 = uint_fast8_t((tmp_157[1]) & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_160 = uint_fast8_t(((uint_fast8_t(tmp_158) + uint_fast8_t(tmp_159))) & 31);  // basic_add
    return tmp_160;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_161 = uq_add_1(uint_fast8_t((8) & 15), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast16_t tmp_162 = uint_fast16_t((0) & 511);  // q_alloc
    const uint_fast16_t tmp_163 = uint_fast16_t((arg_0) & 511);  // basic_identity
    return tmp_163;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_166 = uint_fast8_t(((arg_0 == 268435456)) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_167 = uint_fast32_t((((~arg_0) & 536870911)) & 536870911);  // basic_invert
    const uint_fast32_t tmp_168 = uint_fast32_t(((uint_fast32_t(tmp_167) + uint_fast32_t(uint_fast8_t((1) & 1)))) & 536870911);  // basic_add
    const uint_fast32_t tmp_169 = uint_fast32_t(((arg_0 ^ arg_0)) & 536870911);  // basic_xor
    const uint_fast32_t tmp_170 = uint_fast32_t((((~tmp_169) & 536870911)) & 536870911);  // basic_invert
    const uint_fast32_t tmp_171 = uint_fast32_t(((tmp_166 != 0 ? uint_fast32_t(tmp_170) : uint_fast32_t(tmp_168))) & 536870911);  // basic_mux_2_1
    return tmp_171;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_172 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_173 = uint_fast32_t(((arg_1 != 0 ? uint_fast32_t(tmp_172) : uint_fast32_t(arg_0))) & 536870911);  // basic_mux_2_1
    return tmp_173;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_165 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_174 = q_add_sign_1(arg_0, tmp_165);  // q_add_sign
    return tmp_174;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_176 = uint_fast32_t((arg_0) & 268435455);  // basic_identity
    return tmp_176;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_191 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_192 = uint_fast8_t((((~tmp_191) & 1)) & 1);  // basic_invert
    return tmp_192;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_195 = uint_fast8_t((((arg_0 >> 27) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_196 = uint_fast8_t((((~tmp_195) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_197 = uint_fast8_t(((uint_fast8_t((1) & 1) & tmp_196)) & 1);  // basic_and
    const uint_fast8_t tmp_198 = uint_fast8_t(((uint_fast8_t(uint_fast8_t((0) & 31)) + uint_fast8_t(tmp_197))) & 31);  // basic_add
    const uint_fast8_t tmp_199 = uint_fast8_t((((arg_0 >> 26) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_200 = uint_fast8_t((((~tmp_199) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_201 = uint_fast8_t(((tmp_197 & tmp_200)) & 1);  // basic_and
    const uint_fast8_t tmp_202 = uint_fast8_t(((uint_fast8_t(tmp_198) + uint_fast8_t(tmp_201))) & 31);  // basic_add
    const uint_fast8_t tmp_203 = uint_fast8_t((((arg_0 >> 25) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_204 = uint_fast8_t((((~tmp_203) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_205 = uint_fast8_t(((tmp_201 & tmp_204)) & 1);  // basic_and
    const uint_fast8_t tmp_206 = uint_fast8_t(((uint_fast8_t(tmp_202) + uint_fast8_t(tmp_205))) & 31);  // basic_add
    const uint_fast8_t tmp_207 = uint_fast8_t((((arg_0 >> 24) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_208 = uint_fast8_t((((~tmp_207) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_209 = uint_fast8_t(((tmp_205 & tmp_208)) & 1);  // basic_and
    const uint_fast8_t tmp_210 = uint_fast8_t(((uint_fast8_t(tmp_206) + uint_fast8_t(tmp_209))) & 31);  // basic_add
    const uint_fast8_t tmp_211 = uint_fast8_t((((arg_0 >> 23) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_212 = uint_fast8_t((((~tmp_211) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_213 = uint_fast8_t(((tmp_209 & tmp_212)) & 1);  // basic_and
    const uint_fast8_t tmp_214 = uint_fast8_t(((uint_fast8_t(tmp_210) + uint_fast8_t(tmp_213))) & 31);  // basic_add
    const uint_fast8_t tmp_215 = uint_fast8_t((((arg_0 >> 22) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_216 = uint_fast8_t((((~tmp_215) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_217 = uint_fast8_t(((tmp_213 & tmp_216)) & 1);  // basic_and
    const uint_fast8_t tmp_218 = uint_fast8_t(((uint_fast8_t(tmp_214) + uint_fast8_t(tmp_217))) & 31);  // basic_add
    const uint_fast8_t tmp_219 = uint_fast8_t((((arg_0 >> 21) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_220 = uint_fast8_t((((~tmp_219) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_221 = uint_fast8_t(((tmp_217 & tmp_220)) & 1);  // basic_and
    const uint_fast8_t tmp_222 = uint_fast8_t(((uint_fast8_t(tmp_218) + uint_fast8_t(tmp_221))) & 31);  // basic_add
    const uint_fast8_t tmp_223 = uint_fast8_t((((arg_0 >> 20) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_224 = uint_fast8_t((((~tmp_223) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_225 = uint_fast8_t(((tmp_221 & tmp_224)) & 1);  // basic_and
    const uint_fast8_t tmp_226 = uint_fast8_t(((uint_fast8_t(tmp_222) + uint_fast8_t(tmp_225))) & 31);  // basic_add
    const uint_fast8_t tmp_227 = uint_fast8_t((((arg_0 >> 19) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_228 = uint_fast8_t((((~tmp_227) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_229 = uint_fast8_t(((tmp_225 & tmp_228)) & 1);  // basic_and
    const uint_fast8_t tmp_230 = uint_fast8_t(((uint_fast8_t(tmp_226) + uint_fast8_t(tmp_229))) & 31);  // basic_add
    const uint_fast8_t tmp_231 = uint_fast8_t((((arg_0 >> 18) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_232 = uint_fast8_t((((~tmp_231) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_233 = uint_fast8_t(((tmp_229 & tmp_232)) & 1);  // basic_and
    const uint_fast8_t tmp_234 = uint_fast8_t(((uint_fast8_t(tmp_230) + uint_fast8_t(tmp_233))) & 31);  // basic_add
    const uint_fast8_t tmp_235 = uint_fast8_t((((arg_0 >> 17) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_236 = uint_fast8_t((((~tmp_235) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_237 = uint_fast8_t(((tmp_233 & tmp_236)) & 1);  // basic_and
    const uint_fast8_t tmp_238 = uint_fast8_t(((uint_fast8_t(tmp_234) + uint_fast8_t(tmp_237))) & 31);  // basic_add
    const uint_fast8_t tmp_239 = uint_fast8_t((((arg_0 >> 16) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_240 = uint_fast8_t((((~tmp_239) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_241 = uint_fast8_t(((tmp_237 & tmp_240)) & 1);  // basic_and
    const uint_fast8_t tmp_242 = uint_fast8_t(((uint_fast8_t(tmp_238) + uint_fast8_t(tmp_241))) & 31);  // basic_add
    const uint_fast8_t tmp_243 = uint_fast8_t((((arg_0 >> 15) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_244 = uint_fast8_t((((~tmp_243) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_245 = uint_fast8_t(((tmp_241 & tmp_244)) & 1);  // basic_and
    const uint_fast8_t tmp_246 = uint_fast8_t(((uint_fast8_t(tmp_242) + uint_fast8_t(tmp_245))) & 31);  // basic_add
    const uint_fast8_t tmp_247 = uint_fast8_t((((arg_0 >> 14) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_248 = uint_fast8_t((((~tmp_247) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_249 = uint_fast8_t(((tmp_245 & tmp_248)) & 1);  // basic_and
    const uint_fast8_t tmp_250 = uint_fast8_t(((uint_fast8_t(tmp_246) + uint_fast8_t(tmp_249))) & 31);  // basic_add
    const uint_fast8_t tmp_251 = uint_fast8_t((((arg_0 >> 13) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_252 = uint_fast8_t((((~tmp_251) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_253 = uint_fast8_t(((tmp_249 & tmp_252)) & 1);  // basic_and
    const uint_fast8_t tmp_254 = uint_fast8_t(((uint_fast8_t(tmp_250) + uint_fast8_t(tmp_253))) & 31);  // basic_add
    const uint_fast8_t tmp_255 = uint_fast8_t((((arg_0 >> 12) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_256 = uint_fast8_t((((~tmp_255) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_257 = uint_fast8_t(((tmp_253 & tmp_256)) & 1);  // basic_and
    const uint_fast8_t tmp_258 = uint_fast8_t(((uint_fast8_t(tmp_254) + uint_fast8_t(tmp_257))) & 31);  // basic_add
    const uint_fast8_t tmp_259 = uint_fast8_t((((arg_0 >> 11) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_260 = uint_fast8_t((((~tmp_259) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_261 = uint_fast8_t(((tmp_257 & tmp_260)) & 1);  // basic_and
    const uint_fast8_t tmp_262 = uint_fast8_t(((uint_fast8_t(tmp_258) + uint_fast8_t(tmp_261))) & 31);  // basic_add
    const uint_fast8_t tmp_263 = uint_fast8_t((((arg_0 >> 10) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_264 = uint_fast8_t((((~tmp_263) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_265 = uint_fast8_t(((tmp_261 & tmp_264)) & 1);  // basic_and
    const uint_fast8_t tmp_266 = uint_fast8_t(((uint_fast8_t(tmp_262) + uint_fast8_t(tmp_265))) & 31);  // basic_add
    const uint_fast8_t tmp_267 = uint_fast8_t((((arg_0 >> 9) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_268 = uint_fast8_t((((~tmp_267) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_269 = uint_fast8_t(((tmp_265 & tmp_268)) & 1);  // basic_and
    const uint_fast8_t tmp_270 = uint_fast8_t(((uint_fast8_t(tmp_266) + uint_fast8_t(tmp_269))) & 31);  // basic_add
    const uint_fast8_t tmp_271 = uint_fast8_t((((arg_0 >> 8) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_272 = uint_fast8_t((((~tmp_271) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_273 = uint_fast8_t(((tmp_269 & tmp_272)) & 1);  // basic_and
    const uint_fast8_t tmp_274 = uint_fast8_t(((uint_fast8_t(tmp_270) + uint_fast8_t(tmp_273))) & 31);  // basic_add
    const uint_fast8_t tmp_275 = uint_fast8_t((((arg_0 >> 7) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_276 = uint_fast8_t((((~tmp_275) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_277 = uint_fast8_t(((tmp_273 & tmp_276)) & 1);  // basic_and
    const uint_fast8_t tmp_278 = uint_fast8_t(((uint_fast8_t(tmp_274) + uint_fast8_t(tmp_277))) & 31);  // basic_add
    const uint_fast8_t tmp_279 = uint_fast8_t((((arg_0 >> 6) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_280 = uint_fast8_t((((~tmp_279) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_281 = uint_fast8_t(((tmp_277 & tmp_280)) & 1);  // basic_and
    const uint_fast8_t tmp_282 = uint_fast8_t(((uint_fast8_t(tmp_278) + uint_fast8_t(tmp_281))) & 31);  // basic_add
    const uint_fast8_t tmp_283 = uint_fast8_t((((arg_0 >> 5) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_284 = uint_fast8_t((((~tmp_283) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_285 = uint_fast8_t(((tmp_281 & tmp_284)) & 1);  // basic_and
    const uint_fast8_t tmp_286 = uint_fast8_t(((uint_fast8_t(tmp_282) + uint_fast8_t(tmp_285))) & 31);  // basic_add
    const uint_fast8_t tmp_287 = uint_fast8_t((((arg_0 >> 4) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_288 = uint_fast8_t((((~tmp_287) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_289 = uint_fast8_t(((tmp_285 & tmp_288)) & 1);  // basic_and
    const uint_fast8_t tmp_290 = uint_fast8_t(((uint_fast8_t(tmp_286) + uint_fast8_t(tmp_289))) & 31);  // basic_add
    const uint_fast8_t tmp_291 = uint_fast8_t((((arg_0 >> 3) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_292 = uint_fast8_t((((~tmp_291) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_293 = uint_fast8_t(((tmp_289 & tmp_292)) & 1);  // basic_and
    const uint_fast8_t tmp_294 = uint_fast8_t(((uint_fast8_t(tmp_290) + uint_fast8_t(tmp_293))) & 31);  // basic_add
    const uint_fast8_t tmp_295 = uint_fast8_t((((arg_0 >> 2) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_296 = uint_fast8_t((((~tmp_295) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_297 = uint_fast8_t(((tmp_293 & tmp_296)) & 1);  // basic_and
    const uint_fast8_t tmp_298 = uint_fast8_t(((uint_fast8_t(tmp_294) + uint_fast8_t(tmp_297))) & 31);  // basic_add
    const uint_fast8_t tmp_299 = uint_fast8_t((((arg_0 >> 1) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_300 = uint_fast8_t((((~tmp_299) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_301 = uint_fast8_t(((tmp_297 & tmp_300)) & 1);  // basic_and
    const uint_fast8_t tmp_302 = uint_fast8_t(((uint_fast8_t(tmp_298) + uint_fast8_t(tmp_301))) & 31);  // basic_add
    const uint_fast8_t tmp_303 = uint_fast8_t((((arg_0 >> 0) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_304 = uint_fast8_t((((~tmp_303) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_305 = uint_fast8_t(((tmp_301 & tmp_304)) & 1);  // basic_and
    const uint_fast8_t tmp_306 = uint_fast8_t(((uint_fast8_t(tmp_302) + uint_fast8_t(tmp_305))) & 31);  // basic_add
    return tmp_306;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_308 = uint_fast8_t((arg_0) & 15);  // basic_identity
    const uint_fast8_t tmp_309 = uint_fast8_t((arg_1) & 15);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_310 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_308), static_cast<uint_fast64_t>(tmp_309)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_311 = uint_fast8_t((tmp_310[0]) & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_312 = uint_fast8_t((tmp_310[1]) & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_313 = uint_fast8_t(((uint_fast8_t(tmp_311) + uint_fast8_t(tmp_312))) & 15);  // basic_add
    return tmp_313;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_314 = uq_add_2(uint_fast8_t((5) & 7), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast8_t tmp_315 = uint_fast8_t((0) & 63);  // q_alloc
    const uint_fast8_t tmp_316 = uint_fast8_t((arg_0) & 63);  // basic_identity
    return tmp_316;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_318 = uint_fast8_t((arg_0) & 7);  // basic_identity
    const uint_fast8_t tmp_319 = uint_fast8_t((arg_1) & 7);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_320 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_318), static_cast<uint_fast64_t>(tmp_319)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_321 = uint_fast8_t((tmp_320[0]) & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_322 = uint_fast8_t((tmp_320[1]) & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_323 = uint_fast8_t(((uint_fast8_t(tmp_321) + uint_fast8_t(tmp_322))) & 7);  // basic_add
    return tmp_323;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_324 = uq_add_3(uint_fast8_t((2) & 3), uint_fast8_t((1) & 1));  // uq_add
    const uint_fast8_t tmp_325 = uint_fast8_t((0) & 7);  // q_alloc
    const uint_fast8_t tmp_326 = uint_fast8_t((arg_0) & 7);  // basic_identity
    return tmp_326;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_328 = uint_fast8_t((((arg_0 >> 5) & 1)) & 1);  // basic_select
    return tmp_328;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_329 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_330 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? uint_fast8_t(0) : (uint_fast8_t(tmp_329) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_331 = uint_fast8_t(((uint_fast8_t(tmp_330) - uint_fast8_t(tmp_329))) & 1);  // basic_sub
    const uint_fast8_t tmp_332 = uint_fast8_t((0) & 127);  // q_alloc
    const uint_fast8_t tmp_333 = uint_fast8_t((((uint_fast8_t(tmp_331) << 6) | arg_0)) & 127);  // basic_concat
    return tmp_333;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_335 = uint_fast8_t((((arg_0 >> 2) & 1)) & 1);  // basic_select
    return tmp_335;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_336 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_337 = uint_fast8_t(((uint_fast8_t((4) & 7) >= 5 ? uint_fast8_t(0) : (uint_fast8_t(tmp_336) << uint_fast8_t((4) & 7)))) & 31);  // basic_lshift
    const uint_fast8_t tmp_338 = uint_fast8_t(((uint_fast8_t(tmp_337) - uint_fast8_t(tmp_336))) & 15);  // basic_sub
    const uint_fast8_t tmp_339 = uint_fast8_t((0) & 127);  // q_alloc
    const uint_fast8_t tmp_340 = uint_fast8_t((((uint_fast8_t(tmp_338) << 3) | arg_0)) & 127);  // basic_concat
    return tmp_340;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_334 = q_sign_extend_1(arg_0);  // q_sign_extend
    const uint_fast8_t tmp_341 = q_sign_extend_2(arg_1);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_342 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_334), static_cast<uint_fast64_t>(tmp_341)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_343 = uint_fast8_t((tmp_342[0]) & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_344 = uint_fast8_t((tmp_342[1]) & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_345 = uint_fast8_t(((uint_fast8_t(tmp_343) - uint_fast8_t(tmp_344))) & 127);  // basic_sub
    return tmp_345;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_347 = uint_fast8_t((((arg_0 >> 6) & 1)) & 1);  // basic_select
    return tmp_347;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_348 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_349 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? uint_fast8_t(0) : (uint_fast8_t(tmp_348) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_350 = uint_fast8_t(((uint_fast8_t(tmp_349) - uint_fast8_t(tmp_348))) & 1);  // basic_sub
    const uint_fast8_t tmp_351 = uint_fast8_t((0) & 255);  // q_alloc
    const uint_fast8_t tmp_352 = uint_fast8_t((((uint_fast8_t(tmp_350) << 7) | arg_0)) & 255);  // basic_concat
    return tmp_352;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_354 = uint_fast8_t((((arg_0 >> 1) & 1)) & 1);  // basic_select
    return tmp_354;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_355 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_356 = uint_fast8_t(((uint_fast8_t((6) & 7) >= 7 ? uint_fast8_t(0) : (uint_fast8_t(tmp_355) << uint_fast8_t((6) & 7)))) & 127);  // basic_lshift
    const uint_fast8_t tmp_357 = uint_fast8_t(((uint_fast8_t(tmp_356) - uint_fast8_t(tmp_355))) & 63);  // basic_sub
    const uint_fast8_t tmp_358 = uint_fast8_t((0) & 255);  // q_alloc
    const uint_fast8_t tmp_359 = uint_fast8_t((((uint_fast8_t(tmp_357) << 2) | arg_0)) & 255);  // basic_concat
    return tmp_359;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_353 = q_sign_extend_3(arg_0);  // q_sign_extend
    const uint_fast8_t tmp_360 = q_sign_extend_4(arg_1);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_361 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_353), static_cast<uint_fast64_t>(tmp_360)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_362 = uint_fast8_t((tmp_361[0]) & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_363 = uint_fast8_t((tmp_361[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_364 = uint_fast8_t(((uint_fast8_t(tmp_362) + uint_fast8_t(tmp_363))) & 255);  // basic_add
    return tmp_364;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_366 = uint_fast8_t((((arg_0 >> 7) & 1)) & 1);  // basic_select
    return tmp_366;
}
static inline uint_fast32_t uq_resize_2(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_368 = uint_fast32_t(((uint_fast8_t((1) & 1) >= 29 ? uint_fast32_t(0) : (uint_fast32_t(arg_0) << uint_fast8_t((1) & 1)))) & 536870911);  // basic_lshift
    return tmp_368;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_371 = uint_fast8_t(((arg_0 == 128)) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_372 = uint_fast8_t((((~arg_0) & 255)) & 255);  // basic_invert
    const uint_fast8_t tmp_373 = uint_fast8_t(((uint_fast8_t(tmp_372) + uint_fast8_t(uint_fast8_t((1) & 1)))) & 255);  // basic_add
    const uint_fast8_t tmp_374 = uint_fast8_t(((arg_0 ^ arg_0)) & 255);  // basic_xor
    const uint_fast8_t tmp_375 = uint_fast8_t((((~tmp_374) & 255)) & 255);  // basic_invert
    const uint_fast8_t tmp_376 = uint_fast8_t(((tmp_371 != 0 ? uint_fast8_t(tmp_375) : uint_fast8_t(tmp_373))) & 255);  // basic_mux_2_1
    return tmp_376;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_377 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_378 = uint_fast8_t(((arg_1 != 0 ? uint_fast8_t(tmp_377) : uint_fast8_t(arg_0))) & 255);  // basic_mux_2_1
    return tmp_378;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_370 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_379 = q_add_sign_2(arg_0, tmp_370);  // q_add_sign
    return tmp_379;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_381 = uint_fast8_t((arg_0) & 127);  // basic_identity
    return tmp_381;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_383 = uint_fast32_t(((arg_1 >= 29 ? uint_fast32_t(0) : (uint_fast32_t(arg_0) << arg_1))) & 536870911);  // basic_lshift
    return tmp_383;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_385 = uint_fast32_t(((arg_1 >= 29 ? uint_fast32_t(0) : (arg_0 >> arg_1))) & 536870911);  // basic_rshift
    return tmp_385;
}
static inline uint_fast8_t uq_is_zero_2(uint_fast8_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_387 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_388 = uint_fast8_t((((~tmp_387) & 1)) & 1);  // basic_invert
    return tmp_388;
}
static inline uint_fast8_t uq_ge_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_390 = uint_fast8_t((arg_1) & 127);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_391 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_390)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_392 = uint_fast8_t((tmp_391[0]) & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_393 = uint_fast8_t((tmp_391[1]) & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_394 = uint_fast8_t(((tmp_392 >= tmp_393)) & 1);  // basic_greater_or_equal
    return tmp_394;
}
static inline uint_fast8_t uq_sub_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_396 = uint_fast8_t((arg_0) & 255);  // basic_identity
    const uint_fast8_t tmp_397 = uint_fast8_t((arg_1) & 255);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_398 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_396), static_cast<uint_fast64_t>(tmp_397)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_399 = uint_fast8_t((tmp_398[0]) & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_400 = uint_fast8_t((tmp_398[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_401 = uint_fast8_t(((uint_fast8_t(tmp_399) - uint_fast8_t(tmp_400))) & 255);  // basic_sub
    return tmp_401;
}
static inline uint_fast32_t uq_rshift_jam_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift_jam
    const uint_fast32_t tmp_386 = uq_rshift_1(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_389 = uq_is_zero_2(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_395 = uq_ge_1(arg_1, uint_fast8_t((29) & 31));  // uq_ge
    const uint_fast8_t tmp_402 = uq_sub_2(uint_fast8_t((29) & 31), arg_1);  // uq_sub
    const uint_fast32_t tmp_403 = uint_fast32_t(((tmp_402 >= 29 ? uint_fast32_t(0) : (uint_fast32_t(arg_0) << tmp_402))) & 536870911);  // basic_lshift
    const uint_fast8_t tmp_404 = uint_fast8_t(((tmp_403 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_405 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_406 = uint_fast8_t(((tmp_395 != 0 ? uint_fast8_t(tmp_405) : uint_fast8_t(tmp_404))) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_407 = uint_fast8_t(((tmp_389 != 0 ? uint_fast8_t(uint_fast8_t((0) & 1)) : uint_fast8_t(tmp_406))) & 1);  // basic_mux_2_1
    const uint_fast32_t tmp_408 = uint_fast32_t(((tmp_386 | tmp_407)) & 536870911);  // basic_or
    return tmp_408;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_411 = uint_fast8_t((((arg_0 >> 8) & 1)) & 1);  // basic_select
    return tmp_411;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_412 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_413 = uint_fast8_t(((uint_fast8_t((1) & 1) >= 2 ? uint_fast8_t(0) : (uint_fast8_t(tmp_412) << uint_fast8_t((1) & 1)))) & 3);  // basic_lshift
    const uint_fast8_t tmp_414 = uint_fast8_t(((uint_fast8_t(tmp_413) - uint_fast8_t(tmp_412))) & 1);  // basic_sub
    const uint_fast16_t tmp_415 = uint_fast16_t((0) & 1023);  // q_alloc
    const uint_fast16_t tmp_416 = uint_fast16_t((((uint_fast16_t(tmp_414) << 9) | arg_0)) & 1023);  // basic_concat
    return tmp_416;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_418 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_419 = uint_fast8_t(((uint_fast8_t((2) & 3) >= 3 ? uint_fast8_t(0) : (uint_fast8_t(tmp_418) << uint_fast8_t((2) & 3)))) & 7);  // basic_lshift
    const uint_fast8_t tmp_420 = uint_fast8_t(((uint_fast8_t(tmp_419) - uint_fast8_t(tmp_418))) & 3);  // basic_sub
    const uint_fast16_t tmp_421 = uint_fast16_t((0) & 1023);  // q_alloc
    const uint_fast16_t tmp_422 = uint_fast16_t((((uint_fast16_t(tmp_420) << 8) | arg_0)) & 1023);  // basic_concat
    return tmp_422;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_417 = q_sign_extend_5(arg_0);  // q_sign_extend
    const uint_fast16_t tmp_423 = q_sign_extend_6(arg_1);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_424 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_417), static_cast<uint_fast64_t>(tmp_423)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_425 = uint_fast16_t((tmp_424[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_426 = uint_fast16_t((tmp_424[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_427 = uint_fast16_t(((uint_fast16_t(tmp_425) - uint_fast16_t(tmp_426))) & 1023);  // basic_sub
    return tmp_427;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_429 = q_sign_extend_5(arg_0);  // q_sign_extend
    const uint_fast16_t tmp_430 = q_sign_extend_6(arg_1);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_431 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_429), static_cast<uint_fast64_t>(tmp_430)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_432 = uint_fast16_t((tmp_431[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_433 = uint_fast16_t((tmp_431[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_434 = uint_fast16_t(((uint_fast16_t(tmp_432) + uint_fast16_t(tmp_433))) & 1023);  // basic_add
    return tmp_434;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_441 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_442 = uint_fast8_t((((~tmp_441) & 1)) & 1);  // basic_invert
    return tmp_442;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_444 = uint_fast8_t((((arg_0 >> 9) & 1)) & 1);  // basic_select
    return tmp_444;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_448 = uint_fast8_t(((arg_0 == 512)) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_449 = uint_fast16_t((((~arg_0) & 1023)) & 1023);  // basic_invert
    const uint_fast16_t tmp_450 = uint_fast16_t(((uint_fast16_t(tmp_449) + uint_fast16_t(uint_fast8_t((1) & 1)))) & 1023);  // basic_add
    const uint_fast16_t tmp_451 = uint_fast16_t(((arg_0 ^ arg_0)) & 1023);  // basic_xor
    const uint_fast16_t tmp_452 = uint_fast16_t((((~tmp_451) & 1023)) & 1023);  // basic_invert
    const uint_fast16_t tmp_453 = uint_fast16_t(((tmp_448 != 0 ? uint_fast16_t(tmp_452) : uint_fast16_t(tmp_450))) & 1023);  // basic_mux_2_1
    return tmp_453;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_454 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_455 = uint_fast16_t(((arg_1 != 0 ? uint_fast16_t(tmp_454) : uint_fast16_t(arg_0))) & 1023);  // basic_mux_2_1
    return tmp_455;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_447 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_456 = q_add_sign_3(arg_0, tmp_447);  // q_add_sign
    return tmp_456;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_458 = uint_fast16_t((arg_0) & 511);  // basic_identity
    return tmp_458;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_460 = uint_fast16_t((arg_0) & 1023);  // basic_identity
    const uint_fast16_t tmp_461 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_462 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_460), static_cast<uint_fast64_t>(tmp_461)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_463 = uint_fast16_t((tmp_462[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_464 = uint_fast16_t((tmp_462[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_465 = uint_fast16_t(((uint_fast16_t(tmp_463) + uint_fast16_t(tmp_464))) & 1023);  // basic_add
    return tmp_465;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_468 = uint_fast64_t(((arg_1 >= 38 ? uint_fast64_t(0) : (arg_0 >> arg_1))) & 274877906943);  // basic_rshift
    return tmp_468;
}
static inline uint_fast8_t uq_is_zero_3(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_470 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_471 = uint_fast8_t((((~tmp_470) & 1)) & 1);  // basic_invert
    return tmp_471;
}
static inline uint_fast8_t uq_ge_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_473 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_474 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_473)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_475 = uint_fast16_t((tmp_474[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_476 = uint_fast16_t((tmp_474[1]) & 1023);  // _basic_get_item_1
    const uint_fast8_t tmp_477 = uint_fast8_t(((tmp_475 >= tmp_476)) & 1);  // basic_greater_or_equal
    return tmp_477;
}
static inline uint_fast16_t uq_sub_3(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_479 = uint_fast16_t((arg_0) & 2047);  // basic_identity
    const uint_fast16_t tmp_480 = uint_fast16_t((arg_1) & 2047);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_481 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_479), static_cast<uint_fast64_t>(tmp_480)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_482 = uint_fast16_t((tmp_481[0]) & 2047);  // _basic_get_item_0
    const uint_fast16_t tmp_483 = uint_fast16_t((tmp_481[1]) & 2047);  // _basic_get_item_1
    const uint_fast16_t tmp_484 = uint_fast16_t(((uint_fast16_t(tmp_482) - uint_fast16_t(tmp_483))) & 2047);  // basic_sub
    return tmp_484;
}
static inline uint_fast64_t uq_rshift_jam_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift_jam
    const uint_fast64_t tmp_469 = uq_rshift_2(arg_0, arg_1);  // uq_rshift
    const uint_fast8_t tmp_472 = uq_is_zero_3(arg_1);  // uq_is_zero
    const uint_fast8_t tmp_478 = uq_ge_2(arg_1, uint_fast8_t((38) & 63));  // uq_ge
    const uint_fast16_t tmp_485 = uq_sub_3(uint_fast8_t((38) & 63), arg_1);  // uq_sub
    const uint_fast64_t tmp_486 = uint_fast64_t(((tmp_485 >= 38 ? uint_fast64_t(0) : (uint_fast64_t(arg_0) << tmp_485))) & 274877906943);  // basic_lshift
    const uint_fast8_t tmp_487 = uint_fast8_t(((tmp_486 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_488 = uint_fast8_t(((arg_0 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_489 = uint_fast8_t(((tmp_478 != 0 ? uint_fast8_t(tmp_488) : uint_fast8_t(tmp_487))) & 1);  // basic_mux_2_1
    const uint_fast8_t tmp_490 = uint_fast8_t(((tmp_472 != 0 ? uint_fast8_t(uint_fast8_t((0) & 1)) : uint_fast8_t(tmp_489))) & 1);  // basic_mux_2_1
    const uint_fast64_t tmp_491 = uint_fast64_t(((tmp_469 | tmp_490)) & 274877906943);  // basic_or
    return tmp_491;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_496 = uint_fast64_t((((arg_0 >> 0) & 137438953471)) & 137438953471);  // basic_select
    return tmp_496;
}
static inline uint_fast32_t uq_resize_3(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_500 = uint_fast32_t(((uint_fast8_t((14) & 15) >= 37 ? uint_fast64_t(0) : (arg_0 >> uint_fast8_t((14) & 15)))) & 8388607);  // basic_rshift
    return tmp_500;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_511 = uint_fast32_t((arg_0) & 16777215);  // basic_identity
    const uint_fast32_t tmp_512 = uint_fast32_t((arg_1) & 16777215);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_513 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_511), static_cast<uint_fast64_t>(tmp_512)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_514 = uint_fast32_t((tmp_513[0]) & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_515 = uint_fast32_t((tmp_513[1]) & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_516 = uint_fast32_t(((uint_fast32_t(tmp_514) + uint_fast32_t(tmp_515))) & 16777215);  // basic_add
    return tmp_516;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_523 = uint_fast16_t((arg_0) & 1023);  // basic_identity
    const uint_fast16_t tmp_524 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_525 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_523), static_cast<uint_fast64_t>(tmp_524)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_526 = uint_fast16_t((tmp_525[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_527 = uint_fast16_t((tmp_525[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_528 = uint_fast16_t(((uint_fast16_t(tmp_526) + uint_fast16_t(tmp_527))) & 1023);  // basic_add
    return tmp_528;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_537 = uint_fast16_t((arg_1) & 1023);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_538 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(arg_0), static_cast<uint_fast64_t>(tmp_537)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_539 = uint_fast16_t((tmp_538[0]) & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_540 = uint_fast16_t((tmp_538[1]) & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_541 = uint_fast16_t(((tmp_539 < tmp_540 ? uint_fast16_t(tmp_539) : uint_fast16_t(tmp_540))) & 1023);  // basic_min
    return tmp_541;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_550 = uint_fast32_t((((uint_fast32_t(arg_0) << 31) | (uint_fast32_t(arg_1) << 23) | uint_fast32_t(arg_2))) & 4294967295);  // float32_alloc
    return tmp_550;
}
static inline uint_fast32_t fp32_encode(uint_fast8_t arg_0, uint_fast16_t arg_1, uint_fast32_t arg_2, uint_fast8_t arg_3, uint_fast8_t arg_4) {  // fp32_encode
    const uint_fast32_t tmp_190 = uint_fast32_t(((arg_0 != 0 ? uint_fast32_t(uint_fast32_t((4286578688) & 4294967295)) : uint_fast32_t(uint_fast32_t((2139095040) & 4294967295)))) & 4294967295);  // basic_mux_2_1
    const uint_fast8_t tmp_193 = uq_is_zero_1(arg_2);  // uq_is_zero
    const uint_fast32_t tmp_194 = uint_fast32_t(((arg_0 != 0 ? uint_fast32_t(uint_fast32_t((2147483648) & 4294967295)) : uint_fast32_t(uint_fast32_t((0) & 4294967295)))) & 4294967295);  // basic_mux_2_1
    // begin inline primitive normalize_to_1_xxx
    const uint_fast8_t tmp_307 = lzc(arg_2);  // lzc
    const uint_fast8_t tmp_317 = uq_to_q_2(tmp_307);  // uq_to_q
    const uint_fast8_t tmp_327 = uq_to_q_3(uint_fast8_t((2) & 3));  // uq_to_q
    const uint_fast8_t tmp_346 = q_sub(tmp_317, tmp_327);  // q_sub
    const uint_fast8_t tmp_365 = q_add_1(tmp_346, uint_fast8_t((1) & 3));  // q_add
    const uint_fast8_t tmp_367 = q_sign_bit_6(tmp_365);  // q_sign_bit
    const uint_fast32_t tmp_369 = uq_resize_2(arg_2);  // uq_resize
    const uint_fast8_t tmp_380 = q_abs_1(tmp_365);  // q_abs
    const uint_fast8_t tmp_382 = q_to_uq_1(tmp_380);  // q_to_uq
    const uint_fast32_t tmp_384 = uq_lshift(tmp_369, tmp_382);  // uq_lshift
    const uint_fast32_t tmp_409 = uq_rshift_jam_1(tmp_369, tmp_382);  // uq_rshift_jam
    const uint_fast32_t tmp_410 = uint_fast32_t(((tmp_367 != 0 ? uint_fast32_t(tmp_409) : uint_fast32_t(tmp_384))) & 268435455);  // basic_mux_2_1
    const uint_fast16_t tmp_428 = q_sub_1(arg_1, tmp_380);  // q_sub
    const uint_fast16_t tmp_435 = q_add_2(arg_1, tmp_380);  // q_add
    const uint_fast16_t tmp_436 = uint_fast16_t(((tmp_367 != 0 ? uint_fast16_t(tmp_435) : uint_fast16_t(tmp_428))) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_437 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_410), static_cast<uint_fast64_t>(tmp_436)};  // basic_tuple_maker_2
    // end inline primitive normalize_to_1_xxx
    const uint_fast32_t tmp_438 = uint_fast32_t((tmp_437[0]) & 268435455);  // _basic_get_item_0
    const uint_fast16_t tmp_439 = uint_fast16_t((tmp_437[1]) & 1023);  // _basic_get_item_1
    // begin inline primitive shift_if_subnormal
    const uint_fast64_t tmp_440 = uint_fast64_t(((uint_fast8_t((10) & 15) >= 38 ? uint_fast64_t(0) : (uint_fast64_t(tmp_438) << uint_fast8_t((10) & 15)))) & 274877906943);  // basic_lshift
    const uint_fast8_t tmp_443 = q_is_zero(tmp_439);  // q_is_zero
    const uint_fast8_t tmp_445 = q_sign_bit_8(tmp_439);  // q_sign_bit
    const uint_fast8_t tmp_446 = uint_fast8_t(((tmp_443 | tmp_445)) & 1);  // basic_or
    const uint_fast16_t tmp_457 = q_abs_2(tmp_439);  // q_abs
    const uint_fast16_t tmp_459 = q_to_uq_2(tmp_457);  // q_to_uq
    const uint_fast16_t tmp_466 = uq_add_4(uint_fast8_t((1) & 1), tmp_459);  // uq_add
    const uint_fast16_t tmp_467 = uint_fast16_t(((tmp_446 != 0 ? uint_fast16_t(tmp_466) : uint_fast16_t(uint_fast8_t((0) & 1)))) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_492 = uq_rshift_jam_2(tmp_440, tmp_467);  // uq_rshift_jam
    const uint_fast16_t tmp_493 = uint_fast16_t(((tmp_446 != 0 ? uint_fast16_t(uint_fast8_t((0) & 1)) : uint_fast16_t(tmp_459))) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_494 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_492), static_cast<uint_fast64_t>(tmp_493)};  // basic_tuple_maker_2
    // end inline primitive shift_if_subnormal
    const uint_fast64_t tmp_495 = uint_fast64_t((tmp_494[0]) & 274877906943);  // _basic_get_item_0
    const uint_fast64_t tmp_497 = drop_implicit_bit(tmp_495);  // drop_implicit_bit
    const uint_fast16_t tmp_498 = uint_fast16_t((tmp_494[1]) & 511);  // _basic_get_item_1
    // begin inline primitive round_mantissa
    const uint_fast8_t tmp_499 = uq_is_zero(tmp_498);  // uq_is_zero
    // begin inline primitive uq_RNE_IEEE
    const uint_fast32_t tmp_501 = uq_resize_3(tmp_497);  // uq_resize
    const uint_fast8_t tmp_502 = uint_fast8_t((((tmp_497 >> 13) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_503 = uint_fast8_t((((tmp_497 >> 12) & 1)) & 1);  // basic_select
    const uint_fast16_t tmp_504 = uint_fast16_t((((tmp_497 >> 0) & 4095)) & 4095);  // basic_select
    const uint_fast8_t tmp_505 = uint_fast8_t(((tmp_504 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_506 = uint_fast8_t(((tmp_503 | tmp_505)) & 1);  // basic_or
    const uint_fast8_t tmp_507 = uint_fast8_t((((tmp_497 >> 14) & 1)) & 1);  // basic_select
    const uint_fast8_t tmp_508 = uint_fast8_t(((tmp_506 | tmp_507)) & 1);  // basic_or
    const uint_fast8_t tmp_509 = uint_fast8_t(((tmp_502 & tmp_508)) & 1);  // basic_and
    const uint_fast32_t tmp_510 = uint_fast32_t((tmp_509) & 8388607);  // basic_identity
    const uint_fast32_t tmp_517 = uq_add_5(tmp_501, tmp_510);  // uq_add
    const uint_fast8_t tmp_518 = uint_fast8_t(((tmp_501 == 8388607)) & 1);  // basic_and_reduce
    const uint_fast8_t tmp_519 = uint_fast8_t(((tmp_518 & tmp_509)) & 1);  // basic_and
    const uint_fast32_t tmp_520 = uint_fast32_t(((tmp_519 >= 24 ? uint_fast32_t(0) : (tmp_517 >> tmp_519))) & 8388607);  // basic_rshift
    const std::array<uint_fast64_t, 2> tmp_521 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_520), static_cast<uint_fast64_t>(tmp_519)};  // basic_tuple_maker_2
    // end inline primitive uq_RNE_IEEE
    const uint_fast8_t tmp_522 = uint_fast8_t((tmp_521[1]) & 1);  // _basic_get_item_1
    const uint_fast16_t tmp_529 = uq_add_6(tmp_498, tmp_522);  // uq_add
    const uint_fast8_t tmp_530 = uint_fast8_t(((tmp_529 != 0)) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_531 = uint_fast8_t(((tmp_499 & tmp_530)) & 1);  // basic_and
    const uint_fast32_t tmp_532 = uint_fast32_t((tmp_521[0]) & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_533 = uint_fast32_t(((tmp_531 != 0 ? uint_fast32_t(uint_fast8_t((0) & 1)) : uint_fast32_t(tmp_532))) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_534 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_533), static_cast<uint_fast64_t>(tmp_529)};  // basic_tuple_maker_2
    // end inline primitive round_mantissa
    const uint_fast32_t tmp_535 = uint_fast32_t((tmp_534[0]) & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_536 = uint_fast16_t((tmp_534[1]) & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_542 = uq_min(tmp_536, uint_fast8_t((255) & 255));  // uq_min
    const uint_fast8_t tmp_543 = uint_fast8_t((tmp_542) & 255);  // basic_identity
    const uint_fast8_t tmp_544 = uint_fast8_t(((tmp_543 == 255)) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_545 = uint_fast32_t(((tmp_544 != 0 ? uint_fast32_t(uint_fast8_t((0) & 1)) : uint_fast32_t(tmp_535))) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_546 = uint_fast32_t((tmp_545) & 8388607);  // basic_identity
    const std::array<uint_fast64_t, 2> tmp_547 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_546), static_cast<uint_fast64_t>(tmp_543)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_548 = uint_fast8_t((tmp_547[1]) & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_549 = uint_fast32_t((tmp_547[0]) & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_551 = fp32_pack(arg_0, tmp_548, tmp_549);  // fp32_pack
    const uint_fast32_t tmp_552 = uint_fast32_t(((tmp_193 != 0 ? uint_fast32_t(tmp_194) : uint_fast32_t(tmp_551))) & 4294967295);  // basic_mux_2_1
    const uint_fast32_t tmp_553 = uint_fast32_t(((arg_4 != 0 ? uint_fast32_t(tmp_190) : uint_fast32_t(tmp_552))) & 4294967295);  // basic_mux_2_1
    const uint_fast32_t tmp_554 = uint_fast32_t(((arg_3 != 0 ? uint_fast32_t(uint_fast32_t((2139095041) & 4294967295)) : uint_fast32_t(tmp_553))) & 4294967295);  // basic_mux_2_1
    return tmp_554;
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
    const uint_fast32_t tmp_63 = uint_fast32_t(((tmp_56 != 0 ? uint_fast32_t(tmp_60) : uint_fast32_t(tmp_62))) & 16777215);  // basic_mux_2_1
    const uint_fast32_t tmp_65 = uq_resize_1(tmp_63);  // uq_resize
    const uint_fast8_t tmp_66 = uint_fast8_t((tmp_34[1]) & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_67 = uint_fast8_t((tmp_47[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_68 = uint_fast8_t(((tmp_66 != 0 ? uint_fast8_t(uint_fast8_t((1) & 255)) : uint_fast8_t(tmp_67))) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_69 = uint_fast8_t((tmp_41[1]) & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_70 = uint_fast8_t((tmp_52[1]) & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_71 = uint_fast8_t(((tmp_69 != 0 ? uint_fast8_t(uint_fast8_t((1) & 255)) : uint_fast8_t(tmp_70))) & 255);  // basic_mux_2_1
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
    const uint_fast32_t tmp_133 = uint_fast32_t(((tmp_128 != 0 ? uint_fast32_t(tmp_131) : uint_fast32_t(tmp_132))) & 16777215);  // basic_mux_2_1
    const uint_fast32_t tmp_134 = uq_resize_1(tmp_133);  // uq_resize
    const uint_fast16_t tmp_135 = uq_sub(tmp_76, tmp_71);  // uq_sub
    const uint_fast32_t tmp_136 = uq_rshift_jam(tmp_134, tmp_135);  // uq_rshift_jam
    const uint_fast32_t tmp_137 = uq_to_q(tmp_136);  // uq_to_q
    const uint_fast32_t tmp_138 = q_add_sign(tmp_137, tmp_53);  // q_add_sign
    const uint_fast32_t tmp_151 = q_add(tmp_127, tmp_138);  // q_add
    const uint_fast8_t tmp_153 = q_sign_bit_1(tmp_151);  // q_sign_bit
    const uint_fast8_t tmp_154 = uint_fast8_t(((tmp_55 != 0 ? uint_fast8_t(uint_fast8_t((1) & 1)) : uint_fast8_t(tmp_153))) & 1);  // basic_mux_2_1
    const uint_fast16_t tmp_164 = uq_to_q_1(tmp_76);  // uq_to_q
    const uint_fast32_t tmp_175 = q_abs(tmp_151);  // q_abs
    const uint_fast32_t tmp_177 = q_to_uq(tmp_175);  // q_to_uq
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_34[3]) & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_41[3]) & 1);  // _basic_get_item_3
    const uint_fast8_t tmp_180 = uint_fast8_t(((tmp_178 & tmp_179)) & 1);  // basic_and
    const uint_fast8_t tmp_181 = uint_fast8_t(((tmp_48 ^ tmp_53)) & 1);  // basic_xor
    const uint_fast8_t tmp_182 = uint_fast8_t(((tmp_180 & tmp_181)) & 1);  // basic_and
    const uint_fast8_t tmp_183 = uint_fast8_t((tmp_34[4]) & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_184 = uint_fast8_t((tmp_41[4]) & 1);  // _basic_get_item_4
    const uint_fast8_t tmp_185 = uint_fast8_t(((tmp_183 | tmp_184)) & 1);  // basic_or
    const uint_fast8_t tmp_186 = uint_fast8_t(((tmp_182 | tmp_185)) & 1);  // basic_or
    const uint_fast8_t tmp_187 = uint_fast8_t((((~tmp_186) & 1)) & 1);  // basic_invert
    const uint_fast8_t tmp_188 = uint_fast8_t(((tmp_178 | tmp_179)) & 1);  // basic_or
    const uint_fast8_t tmp_189 = uint_fast8_t(((tmp_187 & tmp_188)) & 1);  // basic_and
    const uint_fast32_t tmp_555 = fp32_encode(tmp_154, tmp_164, tmp_177, tmp_186, tmp_189);  // fp32_encode
    return tmp_555;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}