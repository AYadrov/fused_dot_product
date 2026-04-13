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
static inline uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_11 = uint_fast32_t(((uint_fast64_t(uint_fast8_t(1 & 1)) << 23) | arg_0) & 16777215);  // basic_concat
    return tmp_11;
}
static inline uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_14 = uint_fast32_t(arg_0 & 16777215);  // basic_identity
    return tmp_14;
}
static inline uint_fast32_t if_then_else(uint_fast8_t arg_0, uint_fast32_t arg_1, uint_fast32_t arg_2) {  // if_then_else
    const uint_fast32_t tmp_16 = uint_fast32_t((arg_0 == 1 ? arg_1 : arg_2) & 16777215);  // basic_mux_2_1
    return tmp_16;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_18 = uint_fast32_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(6 & 7))) & 1073741823);  // basic_lshift
    return tmp_18;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_26 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast8_t tmp_27 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_28 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_26), static_cast<uint_fast64_t>(tmp_27)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_29 = uint_fast8_t(tmp_28[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_30 = uint_fast8_t(tmp_28[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_31 = uint_fast8_t((tmp_29 > tmp_30 ? tmp_29 : tmp_30) & 255);  // basic_max
    return tmp_31;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_33 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_34 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_35 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_33), static_cast<uint_fast64_t>(tmp_34)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_36 = uint_fast16_t(tmp_35[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_37 = uint_fast16_t(tmp_35[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_38 = uint_fast16_t((tmp_36 - tmp_37) & 511);  // basic_sub
    return tmp_38;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_40 = uint_fast32_t((arg_1 >= 30 ? 0 : (arg_0 >> arg_1)) & 1073741823);  // basic_rshift
    return tmp_40;
}
static inline uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_42 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_43 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_44 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_42), static_cast<uint_fast64_t>(tmp_43)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_45 = uint_fast8_t(tmp_44[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_46 = uint_fast8_t(tmp_44[1] & 3);  // _basic_get_item_1
    const uint_fast8_t tmp_47 = uint_fast8_t((tmp_45 + tmp_46) & 3);  // basic_add
    return tmp_47;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_48 = uq_add(uint_fast8_t(1 & 1), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast32_t tmp_49 = uint_fast32_t(0 & 2147483647);  // q_alloc
    const uint_fast32_t tmp_50 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_50;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_53 = uint_fast8_t((arg_0 == 1073741824) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_54 = uint_fast32_t(((~arg_0) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_55 = uint_fast32_t((tmp_54 + uint_fast8_t(1 & 1)) & 2147483647);  // basic_add
    const uint_fast32_t tmp_56 = uint_fast32_t((arg_0 ^ arg_0) & 2147483647);  // basic_xor
    const uint_fast32_t tmp_57 = uint_fast32_t(((~tmp_56) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_58 = uint_fast32_t((tmp_53 == 1 ? tmp_57 : tmp_55) & 2147483647);  // basic_mux_2_1
    return tmp_58;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_59 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_60 = uint_fast32_t((arg_1 == 1 ? tmp_59 : arg_0) & 2147483647);  // basic_mux_2_1
    return tmp_60;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_75 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    return tmp_75;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_76 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_77 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_76) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_78 = uint_fast8_t((tmp_77 - tmp_76) & 1);  // basic_sub
    const uint_fast32_t tmp_79 = uint_fast32_t(0 & 4294967295);  // q_alloc
    const uint_fast32_t tmp_80 = uint_fast32_t(((uint_fast64_t(tmp_78) << 31) | arg_0) & 4294967295);  // basic_concat
    return tmp_80;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_74 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_81 = q_sign_extend(tmp_74);  // q_sign_extend
    const uint_fast32_t tmp_82 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_83 = q_sign_extend(tmp_82);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_84 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_81), static_cast<uint_fast64_t>(tmp_83)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_85 = uint_fast32_t(tmp_84[0] & 4294967295);  // _basic_get_item_0
    const uint_fast32_t tmp_86 = uint_fast32_t(tmp_84[1] & 4294967295);  // _basic_get_item_1
    const uint_fast32_t tmp_87 = uint_fast32_t((tmp_85 + tmp_86) & 4294967295);  // basic_add
    return tmp_87;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_89 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_90 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_91 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_89), static_cast<uint_fast64_t>(tmp_90)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_92 = uint_fast8_t(tmp_91[0] & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_93 = uint_fast8_t(tmp_91[1] & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_94 = uint_fast8_t((tmp_92 + tmp_93) & 31);  // basic_add
    return tmp_94;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_95 = uq_add_1(uint_fast8_t(8 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_96 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_97 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_97;
}
static inline uint_fast8_t fp32_is_nan(uint_fast32_t arg_0) {  // fp32_is_nan
    const uint_fast8_t tmp_99 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_100 = uint_fast8_t((tmp_99 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_101 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_102 = uint_fast8_t((tmp_101 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_103 = uint_fast8_t((tmp_100 & tmp_102) & 1);  // basic_and
    return tmp_103;
}
static inline uint_fast8_t uq_max_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_106 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1);  // basic_lshift
    const uint_fast8_t tmp_107 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_108 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_106), static_cast<uint_fast64_t>(tmp_107)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_109 = uint_fast8_t(tmp_108[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_110 = uint_fast8_t(tmp_108[1] & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_111 = uint_fast8_t((tmp_109 > tmp_110 ? tmp_109 : tmp_110) & 1);  // basic_max
    return tmp_111;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_113 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    return tmp_113;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_116 = uint_fast8_t((arg_0 == 2147483648) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_117 = uint_fast32_t(((~arg_0) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_118 = uint_fast32_t((tmp_117 + uint_fast8_t(1 & 1)) & 4294967295);  // basic_add
    const uint_fast32_t tmp_119 = uint_fast32_t((arg_0 ^ arg_0) & 4294967295);  // basic_xor
    const uint_fast32_t tmp_120 = uint_fast32_t(((~tmp_119) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_121 = uint_fast32_t((tmp_116 == 1 ? tmp_120 : tmp_118) & 4294967295);  // basic_mux_2_1
    return tmp_121;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_122 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_123 = uint_fast32_t((arg_1 == 1 ? tmp_122 : arg_0) & 4294967295);  // basic_mux_2_1
    return tmp_123;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_115 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_124 = q_add_sign_1(arg_0, tmp_115);  // q_add_sign
    return tmp_124;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_126 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_126;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_128 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_129 = uint_fast8_t(((~tmp_128) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_130 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_129) & 1);  // basic_and
    const uint_fast8_t tmp_131 = uint_fast8_t((uint_fast8_t(0 & 31) + tmp_130) & 31);  // basic_add
    const uint_fast8_t tmp_132 = uint_fast8_t(((arg_0 >> 29) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_133 = uint_fast8_t(((~tmp_132) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_134 = uint_fast8_t((tmp_130 & tmp_133) & 1);  // basic_and
    const uint_fast8_t tmp_135 = uint_fast8_t((tmp_131 + tmp_134) & 31);  // basic_add
    const uint_fast8_t tmp_136 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_137 = uint_fast8_t(((~tmp_136) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_138 = uint_fast8_t((tmp_134 & tmp_137) & 1);  // basic_and
    const uint_fast8_t tmp_139 = uint_fast8_t((tmp_135 + tmp_138) & 31);  // basic_add
    const uint_fast8_t tmp_140 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_141 = uint_fast8_t(((~tmp_140) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_142 = uint_fast8_t((tmp_138 & tmp_141) & 1);  // basic_and
    const uint_fast8_t tmp_143 = uint_fast8_t((tmp_139 + tmp_142) & 31);  // basic_add
    const uint_fast8_t tmp_144 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_145 = uint_fast8_t(((~tmp_144) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_146 = uint_fast8_t((tmp_142 & tmp_145) & 1);  // basic_and
    const uint_fast8_t tmp_147 = uint_fast8_t((tmp_143 + tmp_146) & 31);  // basic_add
    const uint_fast8_t tmp_148 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_149 = uint_fast8_t(((~tmp_148) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_150 = uint_fast8_t((tmp_146 & tmp_149) & 1);  // basic_and
    const uint_fast8_t tmp_151 = uint_fast8_t((tmp_147 + tmp_150) & 31);  // basic_add
    const uint_fast8_t tmp_152 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_153 = uint_fast8_t(((~tmp_152) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_154 = uint_fast8_t((tmp_150 & tmp_153) & 1);  // basic_and
    const uint_fast8_t tmp_155 = uint_fast8_t((tmp_151 + tmp_154) & 31);  // basic_add
    const uint_fast8_t tmp_156 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_157 = uint_fast8_t(((~tmp_156) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_158 = uint_fast8_t((tmp_154 & tmp_157) & 1);  // basic_and
    const uint_fast8_t tmp_159 = uint_fast8_t((tmp_155 + tmp_158) & 31);  // basic_add
    const uint_fast8_t tmp_160 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_161 = uint_fast8_t(((~tmp_160) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_162 = uint_fast8_t((tmp_158 & tmp_161) & 1);  // basic_and
    const uint_fast8_t tmp_163 = uint_fast8_t((tmp_159 + tmp_162) & 31);  // basic_add
    const uint_fast8_t tmp_164 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_165 = uint_fast8_t(((~tmp_164) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_166 = uint_fast8_t((tmp_162 & tmp_165) & 1);  // basic_and
    const uint_fast8_t tmp_167 = uint_fast8_t((tmp_163 + tmp_166) & 31);  // basic_add
    const uint_fast8_t tmp_168 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_169 = uint_fast8_t(((~tmp_168) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_170 = uint_fast8_t((tmp_166 & tmp_169) & 1);  // basic_and
    const uint_fast8_t tmp_171 = uint_fast8_t((tmp_167 + tmp_170) & 31);  // basic_add
    const uint_fast8_t tmp_172 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_173 = uint_fast8_t(((~tmp_172) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_174 = uint_fast8_t((tmp_170 & tmp_173) & 1);  // basic_and
    const uint_fast8_t tmp_175 = uint_fast8_t((tmp_171 + tmp_174) & 31);  // basic_add
    const uint_fast8_t tmp_176 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_177 = uint_fast8_t(((~tmp_176) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_174 & tmp_177) & 1);  // basic_and
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_175 + tmp_178) & 31);  // basic_add
    const uint_fast8_t tmp_180 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_181 = uint_fast8_t(((~tmp_180) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_182 = uint_fast8_t((tmp_178 & tmp_181) & 1);  // basic_and
    const uint_fast8_t tmp_183 = uint_fast8_t((tmp_179 + tmp_182) & 31);  // basic_add
    const uint_fast8_t tmp_184 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_185 = uint_fast8_t(((~tmp_184) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_186 = uint_fast8_t((tmp_182 & tmp_185) & 1);  // basic_and
    const uint_fast8_t tmp_187 = uint_fast8_t((tmp_183 + tmp_186) & 31);  // basic_add
    const uint_fast8_t tmp_188 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_189 = uint_fast8_t(((~tmp_188) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_190 = uint_fast8_t((tmp_186 & tmp_189) & 1);  // basic_and
    const uint_fast8_t tmp_191 = uint_fast8_t((tmp_187 + tmp_190) & 31);  // basic_add
    const uint_fast8_t tmp_192 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_193 = uint_fast8_t(((~tmp_192) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_194 = uint_fast8_t((tmp_190 & tmp_193) & 1);  // basic_and
    const uint_fast8_t tmp_195 = uint_fast8_t((tmp_191 + tmp_194) & 31);  // basic_add
    const uint_fast8_t tmp_196 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_197 = uint_fast8_t(((~tmp_196) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_198 = uint_fast8_t((tmp_194 & tmp_197) & 1);  // basic_and
    const uint_fast8_t tmp_199 = uint_fast8_t((tmp_195 + tmp_198) & 31);  // basic_add
    const uint_fast8_t tmp_200 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_201 = uint_fast8_t(((~tmp_200) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_202 = uint_fast8_t((tmp_198 & tmp_201) & 1);  // basic_and
    const uint_fast8_t tmp_203 = uint_fast8_t((tmp_199 + tmp_202) & 31);  // basic_add
    const uint_fast8_t tmp_204 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_205 = uint_fast8_t(((~tmp_204) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_206 = uint_fast8_t((tmp_202 & tmp_205) & 1);  // basic_and
    const uint_fast8_t tmp_207 = uint_fast8_t((tmp_203 + tmp_206) & 31);  // basic_add
    const uint_fast8_t tmp_208 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_209 = uint_fast8_t(((~tmp_208) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_210 = uint_fast8_t((tmp_206 & tmp_209) & 1);  // basic_and
    const uint_fast8_t tmp_211 = uint_fast8_t((tmp_207 + tmp_210) & 31);  // basic_add
    const uint_fast8_t tmp_212 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_213 = uint_fast8_t(((~tmp_212) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_214 = uint_fast8_t((tmp_210 & tmp_213) & 1);  // basic_and
    const uint_fast8_t tmp_215 = uint_fast8_t((tmp_211 + tmp_214) & 31);  // basic_add
    const uint_fast8_t tmp_216 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_217 = uint_fast8_t(((~tmp_216) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_218 = uint_fast8_t((tmp_214 & tmp_217) & 1);  // basic_and
    const uint_fast8_t tmp_219 = uint_fast8_t((tmp_215 + tmp_218) & 31);  // basic_add
    const uint_fast8_t tmp_220 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_221 = uint_fast8_t(((~tmp_220) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_222 = uint_fast8_t((tmp_218 & tmp_221) & 1);  // basic_and
    const uint_fast8_t tmp_223 = uint_fast8_t((tmp_219 + tmp_222) & 31);  // basic_add
    const uint_fast8_t tmp_224 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_225 = uint_fast8_t(((~tmp_224) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_226 = uint_fast8_t((tmp_222 & tmp_225) & 1);  // basic_and
    const uint_fast8_t tmp_227 = uint_fast8_t((tmp_223 + tmp_226) & 31);  // basic_add
    const uint_fast8_t tmp_228 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_229 = uint_fast8_t(((~tmp_228) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_230 = uint_fast8_t((tmp_226 & tmp_229) & 1);  // basic_and
    const uint_fast8_t tmp_231 = uint_fast8_t((tmp_227 + tmp_230) & 31);  // basic_add
    const uint_fast8_t tmp_232 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_233 = uint_fast8_t(((~tmp_232) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_234 = uint_fast8_t((tmp_230 & tmp_233) & 1);  // basic_and
    const uint_fast8_t tmp_235 = uint_fast8_t((tmp_231 + tmp_234) & 31);  // basic_add
    const uint_fast8_t tmp_236 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_237 = uint_fast8_t(((~tmp_236) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_238 = uint_fast8_t((tmp_234 & tmp_237) & 1);  // basic_and
    const uint_fast8_t tmp_239 = uint_fast8_t((tmp_235 + tmp_238) & 31);  // basic_add
    const uint_fast8_t tmp_240 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_241 = uint_fast8_t(((~tmp_240) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_242 = uint_fast8_t((tmp_238 & tmp_241) & 1);  // basic_and
    const uint_fast8_t tmp_243 = uint_fast8_t((tmp_239 + tmp_242) & 31);  // basic_add
    const uint_fast8_t tmp_244 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_245 = uint_fast8_t(((~tmp_244) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_246 = uint_fast8_t((tmp_242 & tmp_245) & 1);  // basic_and
    const uint_fast8_t tmp_247 = uint_fast8_t((tmp_243 + tmp_246) & 31);  // basic_add
    const uint_fast8_t tmp_248 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_249 = uint_fast8_t(((~tmp_248) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_250 = uint_fast8_t((tmp_246 & tmp_249) & 1);  // basic_and
    const uint_fast8_t tmp_251 = uint_fast8_t((tmp_247 + tmp_250) & 31);  // basic_add
    return tmp_251;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_253 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_254 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_255 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_253), static_cast<uint_fast64_t>(tmp_254)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_256 = uint_fast8_t(tmp_255[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_257 = uint_fast8_t(tmp_255[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_258 = uint_fast8_t((tmp_256 + tmp_257) & 15);  // basic_add
    return tmp_258;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_259 = uq_add_2(uint_fast8_t(5 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_260 = uint_fast8_t(0 & 63);  // q_alloc
    const uint_fast8_t tmp_261 = uint_fast8_t(arg_0 & 63);  // basic_identity
    return tmp_261;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_263 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_264 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_265 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_263), static_cast<uint_fast64_t>(tmp_264)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_266 = uint_fast8_t(tmp_265[0] & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_267 = uint_fast8_t(tmp_265[1] & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_268 = uint_fast8_t((tmp_266 + tmp_267) & 7);  // basic_add
    return tmp_268;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_269 = uq_add_3(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_270 = uint_fast8_t(0 & 7);  // q_alloc
    const uint_fast8_t tmp_271 = uint_fast8_t(arg_0 & 7);  // basic_identity
    return tmp_271;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_274 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    return tmp_274;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_275 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_276 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_275) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_277 = uint_fast8_t((tmp_276 - tmp_275) & 1);  // basic_sub
    const uint_fast8_t tmp_278 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_279 = uint_fast8_t(((uint_fast64_t(tmp_277) << 6) | arg_0) & 127);  // basic_concat
    return tmp_279;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_282 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    return tmp_282;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_283 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_284 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_283) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_285 = uint_fast8_t((tmp_284 - tmp_283) & 15);  // basic_sub
    const uint_fast8_t tmp_286 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_287 = uint_fast8_t(((uint_fast64_t(tmp_285) << 3) | arg_0) & 127);  // basic_concat
    return tmp_287;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_273 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast8_t tmp_280 = q_sign_extend_1(tmp_273);  // q_sign_extend
    const uint_fast8_t tmp_281 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_288 = q_sign_extend_2(tmp_281);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_289 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_280), static_cast<uint_fast64_t>(tmp_288)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_290 = uint_fast8_t(tmp_289[0] & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_291 = uint_fast8_t(tmp_289[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_292 = uint_fast8_t((tmp_290 - tmp_291) & 127);  // basic_sub
    return tmp_292;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_295 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_295;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_296 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_297 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_296) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_298 = uint_fast8_t((tmp_297 - tmp_296) & 1);  // basic_sub
    const uint_fast8_t tmp_299 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_300 = uint_fast8_t(((uint_fast64_t(tmp_298) << 7) | arg_0) & 255);  // basic_concat
    return tmp_300;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_303 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_303;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_304 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_305 = uint_fast8_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_304) << uint_fast8_t(6 & 7))) & 127);  // basic_lshift
    const uint_fast8_t tmp_306 = uint_fast8_t((tmp_305 - tmp_304) & 63);  // basic_sub
    const uint_fast8_t tmp_307 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_308 = uint_fast8_t(((uint_fast64_t(tmp_306) << 2) | arg_0) & 255);  // basic_concat
    return tmp_308;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_294 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_301 = q_sign_extend_3(tmp_294);  // q_sign_extend
    const uint_fast8_t tmp_302 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_309 = q_sign_extend_4(tmp_302);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_310 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_301), static_cast<uint_fast64_t>(tmp_309)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_311 = uint_fast8_t(tmp_310[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_312 = uint_fast8_t(tmp_310[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_313 = uint_fast8_t((tmp_311 + tmp_312) & 255);  // basic_add
    return tmp_313;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_315 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_315;
}
static inline uint_fast32_t uq_resize_2(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_317 = uint_fast32_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(1 & 1))) & 4294967295);  // basic_lshift
    return tmp_317;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_320 = uint_fast8_t((arg_0 == 128) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_321 = uint_fast8_t(((~arg_0) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_322 = uint_fast8_t((tmp_321 + uint_fast8_t(1 & 1)) & 255);  // basic_add
    const uint_fast8_t tmp_323 = uint_fast8_t((arg_0 ^ arg_0) & 255);  // basic_xor
    const uint_fast8_t tmp_324 = uint_fast8_t(((~tmp_323) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_325 = uint_fast8_t((tmp_320 == 1 ? tmp_324 : tmp_322) & 255);  // basic_mux_2_1
    return tmp_325;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_326 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_327 = uint_fast8_t((arg_1 == 1 ? tmp_326 : arg_0) & 255);  // basic_mux_2_1
    return tmp_327;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_319 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_328 = q_add_sign_2(arg_0, tmp_319);  // q_add_sign
    return tmp_328;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_330 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_330;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_332 = uint_fast32_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 4294967295);  // basic_lshift
    return tmp_332;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_334 = uint_fast32_t((arg_1 >= 32 ? 0 : (arg_0 >> arg_1)) & 4294967295);  // basic_rshift
    return tmp_334;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_338 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_338;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_339 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_340 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_339) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_341 = uint_fast8_t((tmp_340 - tmp_339) & 1);  // basic_sub
    const uint_fast16_t tmp_342 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_343 = uint_fast16_t(((uint_fast64_t(tmp_341) << 9) | arg_0) & 1023);  // basic_concat
    return tmp_343;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_346 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_347 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_346) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_348 = uint_fast8_t((tmp_347 - tmp_346) & 3);  // basic_sub
    const uint_fast16_t tmp_349 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_350 = uint_fast16_t(((uint_fast64_t(tmp_348) << 8) | arg_0) & 1023);  // basic_concat
    return tmp_350;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_337 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_344 = q_sign_extend_5(tmp_337);  // q_sign_extend
    const uint_fast8_t tmp_345 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_351 = q_sign_extend_6(tmp_345);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_352 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_344), static_cast<uint_fast64_t>(tmp_351)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_353 = uint_fast16_t(tmp_352[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_354 = uint_fast16_t(tmp_352[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_355 = uint_fast16_t((tmp_353 - tmp_354) & 1023);  // basic_sub
    return tmp_355;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_357 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_358 = q_sign_extend_5(tmp_357);  // q_sign_extend
    const uint_fast8_t tmp_359 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_360 = q_sign_extend_6(tmp_359);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_361 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_358), static_cast<uint_fast64_t>(tmp_360)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_362 = uint_fast16_t(tmp_361[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_363 = uint_fast16_t(tmp_361[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_364 = uint_fast16_t((tmp_362 + tmp_363) & 1023);  // basic_add
    return tmp_364;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_371 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_372 = uint_fast8_t(((~tmp_371) & 1) & 1);  // basic_invert
    return tmp_372;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_374 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_374;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_378 = uint_fast8_t((arg_0 == 512) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_379 = uint_fast16_t(((~arg_0) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_380 = uint_fast16_t((tmp_379 + uint_fast8_t(1 & 1)) & 1023);  // basic_add
    const uint_fast16_t tmp_381 = uint_fast16_t((arg_0 ^ arg_0) & 1023);  // basic_xor
    const uint_fast16_t tmp_382 = uint_fast16_t(((~tmp_381) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_383 = uint_fast16_t((tmp_378 == 1 ? tmp_382 : tmp_380) & 1023);  // basic_mux_2_1
    return tmp_383;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_384 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_385 = uint_fast16_t((arg_1 == 1 ? tmp_384 : arg_0) & 1023);  // basic_mux_2_1
    return tmp_385;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_377 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_386 = q_add_sign_3(arg_0, tmp_377);  // q_add_sign
    return tmp_386;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_388 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_388;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_390 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_391 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_392 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_390), static_cast<uint_fast64_t>(tmp_391)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_393 = uint_fast16_t(tmp_392[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_394 = uint_fast16_t(tmp_392[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_395 = uint_fast16_t((tmp_393 + tmp_394) & 1023);  // basic_add
    return tmp_395;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_398 = uint_fast64_t((arg_1 >= 41 ? 0 : (arg_0 >> arg_1)) & 2199023255551);  // basic_rshift
    return tmp_398;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_403 = uint_fast64_t(((arg_0 >> 0) & 1099511627775) & 1099511627775);  // basic_select
    return tmp_403;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_406 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_407 = uint_fast8_t(((~tmp_406) & 1) & 1);  // basic_invert
    return tmp_407;
}
static inline uint_fast32_t uq_resize_3(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_409 = uint_fast32_t((uint_fast8_t(17 & 31) >= 40 ? 0 : (arg_0 >> uint_fast8_t(17 & 31))) & 8388607);  // basic_rshift
    return tmp_409;
}
static inline uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_411 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_412 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_413 = uint_fast16_t(((arg_0 >> 0) & 32767) & 32767);  // basic_select
    const uint_fast8_t tmp_414 = uint_fast8_t((tmp_413 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_415 = uint_fast8_t((tmp_412 | tmp_414) & 1);  // basic_or
    const uint_fast8_t tmp_416 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_417 = uint_fast8_t((tmp_415 | tmp_416) & 1);  // basic_or
    const uint_fast8_t tmp_418 = uint_fast8_t((tmp_411 & tmp_417) & 1);  // basic_and
    const uint_fast32_t tmp_419 = uint_fast32_t(tmp_418 & 8388607);  // basic_identity
    return tmp_419;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_421 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_422 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_423 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_421), static_cast<uint_fast64_t>(tmp_422)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_424 = uint_fast32_t(tmp_423[0] & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_425 = uint_fast32_t(tmp_423[1] & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_426 = uint_fast32_t((tmp_424 + tmp_425) & 16777215);  // basic_add
    return tmp_426;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_429 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_430 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_431 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_429), static_cast<uint_fast64_t>(tmp_430)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_432 = uint_fast16_t(tmp_431[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_433 = uint_fast16_t(tmp_431[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_434 = uint_fast16_t((tmp_432 + tmp_433) & 1023);  // basic_add
    return tmp_434;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_444 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_445 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_446 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_444), static_cast<uint_fast64_t>(tmp_445)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_447 = uint_fast16_t(tmp_446[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_448 = uint_fast16_t(tmp_446[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_449 = uint_fast16_t((tmp_447 < tmp_448 ? tmp_447 : tmp_448) & 1023);  // basic_min
    return tmp_449;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_456 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_457 = uint_fast8_t(((~tmp_456) & 1) & 1);  // basic_invert
    return tmp_457;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_464 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_464;
}
static inline uint_fast32_t encode_Float32(uint_fast32_t arg_0, uint_fast16_t arg_1, uint_fast8_t arg_2) {  // encode_Float32
    const uint_fast8_t tmp_114 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_125 = q_abs(arg_0);  // q_abs
    const uint_fast32_t tmp_127 = q_to_uq(tmp_125);  // q_to_uq
    // begin inline primitive fp32_normalize
    const uint_fast8_t tmp_252 = lzc(tmp_127);  // lzc
    const uint_fast8_t tmp_262 = uq_to_q_2(tmp_252);  // uq_to_q
    const uint_fast8_t tmp_272 = uq_to_q_3(uint_fast8_t(2 & 3));  // uq_to_q
    const uint_fast8_t tmp_293 = q_sub(tmp_262, tmp_272);  // q_sub
    const uint_fast8_t tmp_314 = q_add_1(tmp_293, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_316 = q_sign_bit_6(tmp_314);  // q_sign_bit
    const uint_fast32_t tmp_318 = uq_resize_2(tmp_127);  // uq_resize
    const uint_fast8_t tmp_329 = q_abs_1(tmp_314);  // q_abs
    const uint_fast8_t tmp_331 = q_to_uq_1(tmp_329);  // q_to_uq
    const uint_fast32_t tmp_333 = uq_lshift(tmp_318, tmp_331);  // uq_lshift
    const uint_fast32_t tmp_335 = uq_rshift_1(tmp_318, tmp_331);  // uq_rshift
    const uint_fast32_t tmp_336 = uint_fast32_t((tmp_316 == 1 ? tmp_335 : tmp_333) & 2147483647);  // basic_mux_2_1
    const uint_fast16_t tmp_356 = q_sub_1(arg_1, tmp_329);  // q_sub
    const uint_fast16_t tmp_365 = q_add_2(arg_1, tmp_329);  // q_add
    const uint_fast16_t tmp_366 = uint_fast16_t((tmp_316 == 1 ? tmp_365 : tmp_356) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_367 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_336), static_cast<uint_fast64_t>(tmp_366)};  // basic_tuple_maker_2
    // end inline primitive fp32_normalize
    const uint_fast32_t tmp_368 = uint_fast32_t(tmp_367[0] & 2147483647);  // _basic_get_item_0
    const uint_fast16_t tmp_369 = uint_fast16_t(tmp_367[1] & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_classify
    const uint_fast64_t tmp_370 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_368) << uint_fast8_t(10 & 15))) & 2199023255551);  // basic_lshift
    const uint_fast8_t tmp_373 = q_is_zero(tmp_369);  // q_is_zero
    const uint_fast8_t tmp_375 = q_sign_bit_8(tmp_369);  // q_sign_bit
    const uint_fast8_t tmp_376 = uint_fast8_t((tmp_373 | tmp_375) & 1);  // basic_or
    const uint_fast16_t tmp_387 = q_abs_2(tmp_369);  // q_abs
    const uint_fast16_t tmp_389 = q_to_uq_2(tmp_387);  // q_to_uq
    const uint_fast16_t tmp_396 = uq_add_4(uint_fast8_t(1 & 1), tmp_389);  // uq_add
    const uint_fast16_t tmp_397 = uint_fast16_t((tmp_376 == 1 ? tmp_396 : uint_fast8_t(0 & 1)) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_399 = uq_rshift_2(tmp_370, tmp_397);  // uq_rshift
    const uint_fast16_t tmp_400 = uint_fast16_t((tmp_376 == 1 ? uint_fast8_t(0 & 1) : tmp_389) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_401 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_399), static_cast<uint_fast64_t>(tmp_400)};  // basic_tuple_maker_2
    // end inline primitive fp32_classify
    const uint_fast64_t tmp_402 = uint_fast64_t(tmp_401[0] & 2199023255551);  // _basic_get_item_0
    const uint_fast64_t tmp_404 = drop_implicit_bit(tmp_402);  // drop_implicit_bit
    const uint_fast16_t tmp_405 = uint_fast16_t(tmp_401[1] & 511);  // _basic_get_item_1
    // begin inline primitive fp32_round
    const uint_fast8_t tmp_408 = uq_is_zero(tmp_405);  // uq_is_zero
    const uint_fast32_t tmp_410 = uq_resize_3(tmp_404);  // uq_resize
    const uint_fast32_t tmp_420 = uq_RNE_IEEE(tmp_404);  // uq_RNE_IEEE
    const uint_fast32_t tmp_427 = uq_add_5(tmp_410, tmp_420);  // uq_add
    const uint_fast8_t tmp_428 = uint_fast8_t(((tmp_427 >> 23) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_435 = uq_add_6(tmp_405, tmp_428);  // uq_add
    const uint_fast8_t tmp_436 = uint_fast8_t((tmp_435 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_437 = uint_fast8_t((tmp_408 & tmp_436) & 1);  // basic_and
    const uint_fast32_t tmp_438 = uint_fast32_t((uint_fast8_t(1 & 1) >= 24 ? 0 : (tmp_427 >> uint_fast8_t(1 & 1))) & 8388607);  // basic_rshift
    const uint_fast32_t tmp_439 = uint_fast32_t((tmp_428 == 1 ? tmp_438 : tmp_427) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_440 = uint_fast32_t((tmp_437 == 1 ? uint_fast8_t(0 & 1) : tmp_439) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_441 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_440), static_cast<uint_fast64_t>(tmp_435)};  // basic_tuple_maker_2
    // end inline primitive fp32_round
    const uint_fast32_t tmp_442 = uint_fast32_t(tmp_441[0] & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_443 = uint_fast16_t(tmp_441[1] & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_450 = uq_min(tmp_443, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_451 = uint_fast8_t(tmp_450 & 255);  // basic_identity
    const uint_fast8_t tmp_452 = uint_fast8_t((tmp_451 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_453 = uint_fast32_t((tmp_452 == 1 ? uint_fast8_t(0 & 1) : tmp_442) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_454 = uint_fast32_t((arg_2 == 1 ? uint_fast8_t(1 & 1) : tmp_453) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_455 = uint_fast32_t(tmp_454 & 8388607);  // basic_identity
    const uint_fast8_t tmp_458 = uq_is_zero_1(tmp_127);  // uq_is_zero
    const uint_fast8_t tmp_459 = uint_fast8_t((tmp_458 == 1 ? uint_fast8_t(0 & 1) : tmp_451) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_460 = uint_fast8_t((arg_2 == 1 ? uint_fast8_t(255 & 255) : tmp_459) & 255);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_461 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_455), static_cast<uint_fast64_t>(tmp_460)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_462 = uint_fast8_t(tmp_461[1] & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_463 = uint_fast32_t(tmp_461[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_465 = fp32_pack(tmp_114, tmp_462, tmp_463);  // fp32_pack
    return tmp_465;
}
static inline uint_fast32_t FP32_IEEE_adder_impl(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // FP32_IEEE_adder
    const uint_fast8_t tmp_5 = fp32_is_normal(arg_0);  // fp32_is_normal
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_6 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_7 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_8 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_9 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_6), static_cast<uint_fast64_t>(tmp_7), static_cast<uint_fast64_t>(tmp_8)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast32_t tmp_10 = uint_fast32_t(tmp_9[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_12 = add_implicit_bit(tmp_10);  // add_implicit_bit
    const uint_fast32_t tmp_13 = uint_fast32_t(tmp_10 & 8388607);  // basic_identity
    const uint_fast32_t tmp_15 = uq_resize(tmp_13);  // uq_resize
    const uint_fast32_t tmp_17 = if_then_else(tmp_5, tmp_12, tmp_15);  // if_then_else
    const uint_fast32_t tmp_19 = uq_resize_1(tmp_17);  // uq_resize
    const uint_fast8_t tmp_20 = uint_fast8_t(tmp_9[1] & 255);  // _basic_get_item_1
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_21 = uint_fast8_t(((arg_1 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_22 = uint_fast8_t(((arg_1 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_23 = uint_fast32_t(((arg_1 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_24 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_21), static_cast<uint_fast64_t>(tmp_22), static_cast<uint_fast64_t>(tmp_23)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_25 = uint_fast8_t(tmp_24[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_32 = uq_max(tmp_20, tmp_25);  // uq_max
    const uint_fast16_t tmp_39 = uq_sub(tmp_32, tmp_20);  // uq_sub
    const uint_fast32_t tmp_41 = uq_rshift(tmp_19, tmp_39);  // uq_rshift
    const uint_fast32_t tmp_51 = uq_to_q(tmp_41);  // uq_to_q
    const uint_fast8_t tmp_52 = uint_fast8_t(tmp_9[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_61 = q_add_sign(tmp_51, tmp_52);  // q_add_sign
    const uint_fast8_t tmp_62 = fp32_is_normal(arg_1);  // fp32_is_normal
    const uint_fast32_t tmp_63 = uint_fast32_t(tmp_24[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_64 = add_implicit_bit(tmp_63);  // add_implicit_bit
    const uint_fast32_t tmp_65 = uint_fast32_t(tmp_63 & 8388607);  // basic_identity
    const uint_fast32_t tmp_66 = uq_resize(tmp_65);  // uq_resize
    const uint_fast32_t tmp_67 = if_then_else(tmp_62, tmp_64, tmp_66);  // if_then_else
    const uint_fast32_t tmp_68 = uq_resize_1(tmp_67);  // uq_resize
    const uint_fast16_t tmp_69 = uq_sub(tmp_32, tmp_25);  // uq_sub
    const uint_fast32_t tmp_70 = uq_rshift(tmp_68, tmp_69);  // uq_rshift
    const uint_fast32_t tmp_71 = uq_to_q(tmp_70);  // uq_to_q
    const uint_fast8_t tmp_72 = uint_fast8_t(tmp_24[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_73 = q_add_sign(tmp_71, tmp_72);  // q_add_sign
    const uint_fast32_t tmp_88 = q_add(tmp_61, tmp_73);  // q_add
    const uint_fast16_t tmp_98 = uq_to_q_1(tmp_32);  // uq_to_q
    const uint_fast8_t tmp_104 = fp32_is_nan(arg_0);  // fp32_is_nan
    const uint_fast8_t tmp_105 = fp32_is_nan(arg_1);  // fp32_is_nan
    const uint_fast8_t tmp_112 = uq_max_1(tmp_104, tmp_105);  // uq_max
    const uint_fast32_t tmp_466 = encode_Float32(tmp_88, tmp_98, tmp_112);  // encode_Float32
    return tmp_466;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}