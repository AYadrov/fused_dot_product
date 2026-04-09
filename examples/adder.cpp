#pragma once
#include <array>
#include <cstdint>

static inline uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_5 = uint_fast32_t(((uint_fast64_t(uint_fast8_t(1 & 1)) << 23) | arg_0) & 16777215);  // basic_concat
    return tmp_5;
}
static inline uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_7 = uint_fast32_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(6 & 7))) & 1073741823);  // basic_lshift
    return tmp_7;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_15 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast8_t tmp_16 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_17 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_15), static_cast<uint_fast64_t>(tmp_16)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_18 = uint_fast8_t(tmp_17[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_19 = uint_fast8_t(tmp_17[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_20 = uint_fast8_t((tmp_18 > tmp_19 ? tmp_18 : tmp_19) & 255);  // basic_max
    return tmp_20;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_22 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_23 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_24 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_22), static_cast<uint_fast64_t>(tmp_23)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_25 = uint_fast16_t(tmp_24[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_26 = uint_fast16_t(tmp_24[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_27 = uint_fast16_t((tmp_25 - tmp_26) & 511);  // basic_sub
    return tmp_27;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_29 = uint_fast32_t((arg_1 >= 30 ? 0 : (arg_0 >> arg_1)) & 1073741823);  // basic_rshift
    return tmp_29;
}
static inline uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_31 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_32 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_33 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_31), static_cast<uint_fast64_t>(tmp_32)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_34 = uint_fast8_t(tmp_33[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_35 = uint_fast8_t(tmp_33[1] & 3);  // _basic_get_item_1
    const uint_fast8_t tmp_36 = uint_fast8_t((tmp_34 + tmp_35) & 3);  // basic_add
    return tmp_36;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_37 = uq_add(uint_fast8_t(1 & 1), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast32_t tmp_38 = uint_fast32_t(0 & 2147483647);  // q_alloc
    const uint_fast32_t tmp_39 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_39;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_42 = uint_fast8_t((arg_0 == 1073741824) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_43 = uint_fast32_t(((~arg_0) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_44 = uint_fast32_t((tmp_43 + uint_fast8_t(1 & 1)) & 2147483647);  // basic_add
    const uint_fast32_t tmp_45 = uint_fast32_t((arg_0 ^ arg_0) & 2147483647);  // basic_xor
    const uint_fast32_t tmp_46 = uint_fast32_t(((~tmp_45) & 2147483647) & 2147483647);  // basic_invert
    const uint_fast32_t tmp_47 = uint_fast32_t((tmp_42 == 1 ? tmp_46 : tmp_44) & 2147483647);  // basic_mux_2_1
    return tmp_47;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_48 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_49 = uint_fast32_t((arg_1 == 1 ? tmp_48 : arg_0) & 2147483647);  // basic_mux_2_1
    return tmp_49;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_60 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    return tmp_60;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_61 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_62 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_61) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_63 = uint_fast8_t((tmp_62 - tmp_61) & 1);  // basic_sub
    const uint_fast32_t tmp_64 = uint_fast32_t(0 & 4294967295);  // q_alloc
    const uint_fast32_t tmp_65 = uint_fast32_t(((uint_fast64_t(tmp_63) << 31) | arg_0) & 4294967295);  // basic_concat
    return tmp_65;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_59 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_66 = q_sign_extend(tmp_59);  // q_sign_extend
    const uint_fast32_t tmp_67 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 2147483647);  // basic_lshift
    const uint_fast32_t tmp_68 = q_sign_extend(tmp_67);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_69 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_66), static_cast<uint_fast64_t>(tmp_68)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_70 = uint_fast32_t(tmp_69[0] & 4294967295);  // _basic_get_item_0
    const uint_fast32_t tmp_71 = uint_fast32_t(tmp_69[1] & 4294967295);  // _basic_get_item_1
    const uint_fast32_t tmp_72 = uint_fast32_t((tmp_70 + tmp_71) & 4294967295);  // basic_add
    return tmp_72;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_74 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_75 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_76 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_74), static_cast<uint_fast64_t>(tmp_75)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_77 = uint_fast8_t(tmp_76[0] & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_78 = uint_fast8_t(tmp_76[1] & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_79 = uint_fast8_t((tmp_77 + tmp_78) & 31);  // basic_add
    return tmp_79;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_80 = uq_add_1(uint_fast8_t(8 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_81 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_82 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_82;
}
static inline uint_fast8_t fp32_is_nan(uint_fast32_t arg_0) {  // fp32_is_nan
    const uint_fast8_t tmp_84 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast8_t tmp_85 = uint_fast8_t((tmp_84 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_86 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const uint_fast8_t tmp_87 = uint_fast8_t((tmp_86 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_88 = uint_fast8_t((tmp_85 & tmp_87) & 1);  // basic_and
    return tmp_88;
}
static inline uint_fast8_t uq_max_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_91 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1);  // basic_lshift
    const uint_fast8_t tmp_92 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_93 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_91), static_cast<uint_fast64_t>(tmp_92)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_94 = uint_fast8_t(tmp_93[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_95 = uint_fast8_t(tmp_93[1] & 1);  // _basic_get_item_1
    const uint_fast8_t tmp_96 = uint_fast8_t((tmp_94 > tmp_95 ? tmp_94 : tmp_95) & 1);  // basic_max
    return tmp_96;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_98 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    return tmp_98;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_101 = uint_fast8_t((arg_0 == 2147483648) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_102 = uint_fast32_t(((~arg_0) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_103 = uint_fast32_t((tmp_102 + uint_fast8_t(1 & 1)) & 4294967295);  // basic_add
    const uint_fast32_t tmp_104 = uint_fast32_t((arg_0 ^ arg_0) & 4294967295);  // basic_xor
    const uint_fast32_t tmp_105 = uint_fast32_t(((~tmp_104) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_106 = uint_fast32_t((tmp_101 == 1 ? tmp_105 : tmp_103) & 4294967295);  // basic_mux_2_1
    return tmp_106;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_107 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_108 = uint_fast32_t((arg_1 == 1 ? tmp_107 : arg_0) & 4294967295);  // basic_mux_2_1
    return tmp_108;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_100 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_109 = q_add_sign_1(arg_0, tmp_100);  // q_add_sign
    return tmp_109;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_111 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_111;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_113 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_114 = uint_fast8_t(((~tmp_113) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_115 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_114) & 1);  // basic_and
    const uint_fast8_t tmp_116 = uint_fast8_t((uint_fast8_t(0 & 31) + tmp_115) & 31);  // basic_add
    const uint_fast8_t tmp_117 = uint_fast8_t(((arg_0 >> 29) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_118 = uint_fast8_t(((~tmp_117) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_119 = uint_fast8_t((tmp_115 & tmp_118) & 1);  // basic_and
    const uint_fast8_t tmp_120 = uint_fast8_t((tmp_116 + tmp_119) & 31);  // basic_add
    const uint_fast8_t tmp_121 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_122 = uint_fast8_t(((~tmp_121) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_123 = uint_fast8_t((tmp_119 & tmp_122) & 1);  // basic_and
    const uint_fast8_t tmp_124 = uint_fast8_t((tmp_120 + tmp_123) & 31);  // basic_add
    const uint_fast8_t tmp_125 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_126 = uint_fast8_t(((~tmp_125) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_127 = uint_fast8_t((tmp_123 & tmp_126) & 1);  // basic_and
    const uint_fast8_t tmp_128 = uint_fast8_t((tmp_124 + tmp_127) & 31);  // basic_add
    const uint_fast8_t tmp_129 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_130 = uint_fast8_t(((~tmp_129) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_131 = uint_fast8_t((tmp_127 & tmp_130) & 1);  // basic_and
    const uint_fast8_t tmp_132 = uint_fast8_t((tmp_128 + tmp_131) & 31);  // basic_add
    const uint_fast8_t tmp_133 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_134 = uint_fast8_t(((~tmp_133) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_135 = uint_fast8_t((tmp_131 & tmp_134) & 1);  // basic_and
    const uint_fast8_t tmp_136 = uint_fast8_t((tmp_132 + tmp_135) & 31);  // basic_add
    const uint_fast8_t tmp_137 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_138 = uint_fast8_t(((~tmp_137) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_139 = uint_fast8_t((tmp_135 & tmp_138) & 1);  // basic_and
    const uint_fast8_t tmp_140 = uint_fast8_t((tmp_136 + tmp_139) & 31);  // basic_add
    const uint_fast8_t tmp_141 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_142 = uint_fast8_t(((~tmp_141) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_143 = uint_fast8_t((tmp_139 & tmp_142) & 1);  // basic_and
    const uint_fast8_t tmp_144 = uint_fast8_t((tmp_140 + tmp_143) & 31);  // basic_add
    const uint_fast8_t tmp_145 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_146 = uint_fast8_t(((~tmp_145) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_147 = uint_fast8_t((tmp_143 & tmp_146) & 1);  // basic_and
    const uint_fast8_t tmp_148 = uint_fast8_t((tmp_144 + tmp_147) & 31);  // basic_add
    const uint_fast8_t tmp_149 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_150 = uint_fast8_t(((~tmp_149) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_151 = uint_fast8_t((tmp_147 & tmp_150) & 1);  // basic_and
    const uint_fast8_t tmp_152 = uint_fast8_t((tmp_148 + tmp_151) & 31);  // basic_add
    const uint_fast8_t tmp_153 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_154 = uint_fast8_t(((~tmp_153) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_155 = uint_fast8_t((tmp_151 & tmp_154) & 1);  // basic_and
    const uint_fast8_t tmp_156 = uint_fast8_t((tmp_152 + tmp_155) & 31);  // basic_add
    const uint_fast8_t tmp_157 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_158 = uint_fast8_t(((~tmp_157) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_159 = uint_fast8_t((tmp_155 & tmp_158) & 1);  // basic_and
    const uint_fast8_t tmp_160 = uint_fast8_t((tmp_156 + tmp_159) & 31);  // basic_add
    const uint_fast8_t tmp_161 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_162 = uint_fast8_t(((~tmp_161) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_163 = uint_fast8_t((tmp_159 & tmp_162) & 1);  // basic_and
    const uint_fast8_t tmp_164 = uint_fast8_t((tmp_160 + tmp_163) & 31);  // basic_add
    const uint_fast8_t tmp_165 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_166 = uint_fast8_t(((~tmp_165) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_167 = uint_fast8_t((tmp_163 & tmp_166) & 1);  // basic_and
    const uint_fast8_t tmp_168 = uint_fast8_t((tmp_164 + tmp_167) & 31);  // basic_add
    const uint_fast8_t tmp_169 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_170 = uint_fast8_t(((~tmp_169) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_171 = uint_fast8_t((tmp_167 & tmp_170) & 1);  // basic_and
    const uint_fast8_t tmp_172 = uint_fast8_t((tmp_168 + tmp_171) & 31);  // basic_add
    const uint_fast8_t tmp_173 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_174 = uint_fast8_t(((~tmp_173) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_175 = uint_fast8_t((tmp_171 & tmp_174) & 1);  // basic_and
    const uint_fast8_t tmp_176 = uint_fast8_t((tmp_172 + tmp_175) & 31);  // basic_add
    const uint_fast8_t tmp_177 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_178 = uint_fast8_t(((~tmp_177) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_175 & tmp_178) & 1);  // basic_and
    const uint_fast8_t tmp_180 = uint_fast8_t((tmp_176 + tmp_179) & 31);  // basic_add
    const uint_fast8_t tmp_181 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_182 = uint_fast8_t(((~tmp_181) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_183 = uint_fast8_t((tmp_179 & tmp_182) & 1);  // basic_and
    const uint_fast8_t tmp_184 = uint_fast8_t((tmp_180 + tmp_183) & 31);  // basic_add
    const uint_fast8_t tmp_185 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_186 = uint_fast8_t(((~tmp_185) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_187 = uint_fast8_t((tmp_183 & tmp_186) & 1);  // basic_and
    const uint_fast8_t tmp_188 = uint_fast8_t((tmp_184 + tmp_187) & 31);  // basic_add
    const uint_fast8_t tmp_189 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_190 = uint_fast8_t(((~tmp_189) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_191 = uint_fast8_t((tmp_187 & tmp_190) & 1);  // basic_and
    const uint_fast8_t tmp_192 = uint_fast8_t((tmp_188 + tmp_191) & 31);  // basic_add
    const uint_fast8_t tmp_193 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_194 = uint_fast8_t(((~tmp_193) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_195 = uint_fast8_t((tmp_191 & tmp_194) & 1);  // basic_and
    const uint_fast8_t tmp_196 = uint_fast8_t((tmp_192 + tmp_195) & 31);  // basic_add
    const uint_fast8_t tmp_197 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_198 = uint_fast8_t(((~tmp_197) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_199 = uint_fast8_t((tmp_195 & tmp_198) & 1);  // basic_and
    const uint_fast8_t tmp_200 = uint_fast8_t((tmp_196 + tmp_199) & 31);  // basic_add
    const uint_fast8_t tmp_201 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_202 = uint_fast8_t(((~tmp_201) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_203 = uint_fast8_t((tmp_199 & tmp_202) & 1);  // basic_and
    const uint_fast8_t tmp_204 = uint_fast8_t((tmp_200 + tmp_203) & 31);  // basic_add
    const uint_fast8_t tmp_205 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_206 = uint_fast8_t(((~tmp_205) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_207 = uint_fast8_t((tmp_203 & tmp_206) & 1);  // basic_and
    const uint_fast8_t tmp_208 = uint_fast8_t((tmp_204 + tmp_207) & 31);  // basic_add
    const uint_fast8_t tmp_209 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_210 = uint_fast8_t(((~tmp_209) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_211 = uint_fast8_t((tmp_207 & tmp_210) & 1);  // basic_and
    const uint_fast8_t tmp_212 = uint_fast8_t((tmp_208 + tmp_211) & 31);  // basic_add
    const uint_fast8_t tmp_213 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_214 = uint_fast8_t(((~tmp_213) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_215 = uint_fast8_t((tmp_211 & tmp_214) & 1);  // basic_and
    const uint_fast8_t tmp_216 = uint_fast8_t((tmp_212 + tmp_215) & 31);  // basic_add
    const uint_fast8_t tmp_217 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_218 = uint_fast8_t(((~tmp_217) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_219 = uint_fast8_t((tmp_215 & tmp_218) & 1);  // basic_and
    const uint_fast8_t tmp_220 = uint_fast8_t((tmp_216 + tmp_219) & 31);  // basic_add
    const uint_fast8_t tmp_221 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_222 = uint_fast8_t(((~tmp_221) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_223 = uint_fast8_t((tmp_219 & tmp_222) & 1);  // basic_and
    const uint_fast8_t tmp_224 = uint_fast8_t((tmp_220 + tmp_223) & 31);  // basic_add
    const uint_fast8_t tmp_225 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_226 = uint_fast8_t(((~tmp_225) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_227 = uint_fast8_t((tmp_223 & tmp_226) & 1);  // basic_and
    const uint_fast8_t tmp_228 = uint_fast8_t((tmp_224 + tmp_227) & 31);  // basic_add
    const uint_fast8_t tmp_229 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_230 = uint_fast8_t(((~tmp_229) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_231 = uint_fast8_t((tmp_227 & tmp_230) & 1);  // basic_and
    const uint_fast8_t tmp_232 = uint_fast8_t((tmp_228 + tmp_231) & 31);  // basic_add
    const uint_fast8_t tmp_233 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_234 = uint_fast8_t(((~tmp_233) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_235 = uint_fast8_t((tmp_231 & tmp_234) & 1);  // basic_and
    const uint_fast8_t tmp_236 = uint_fast8_t((tmp_232 + tmp_235) & 31);  // basic_add
    return tmp_236;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_238 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_239 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_240 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_238), static_cast<uint_fast64_t>(tmp_239)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_241 = uint_fast8_t(tmp_240[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_242 = uint_fast8_t(tmp_240[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_243 = uint_fast8_t((tmp_241 + tmp_242) & 15);  // basic_add
    return tmp_243;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_244 = uq_add_2(uint_fast8_t(5 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_245 = uint_fast8_t(0 & 63);  // q_alloc
    const uint_fast8_t tmp_246 = uint_fast8_t(arg_0 & 63);  // basic_identity
    return tmp_246;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_248 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_249 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_250 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_248), static_cast<uint_fast64_t>(tmp_249)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_251 = uint_fast8_t(tmp_250[0] & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_252 = uint_fast8_t(tmp_250[1] & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_253 = uint_fast8_t((tmp_251 + tmp_252) & 7);  // basic_add
    return tmp_253;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_254 = uq_add_3(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_255 = uint_fast8_t(0 & 7);  // q_alloc
    const uint_fast8_t tmp_256 = uint_fast8_t(arg_0 & 7);  // basic_identity
    return tmp_256;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_259 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    return tmp_259;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_260 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_261 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_260) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_262 = uint_fast8_t((tmp_261 - tmp_260) & 1);  // basic_sub
    const uint_fast8_t tmp_263 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_264 = uint_fast8_t(((uint_fast64_t(tmp_262) << 6) | arg_0) & 127);  // basic_concat
    return tmp_264;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_267 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    return tmp_267;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_268 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_269 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_268) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_270 = uint_fast8_t((tmp_269 - tmp_268) & 15);  // basic_sub
    const uint_fast8_t tmp_271 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_272 = uint_fast8_t(((uint_fast64_t(tmp_270) << 3) | arg_0) & 127);  // basic_concat
    return tmp_272;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_258 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast8_t tmp_265 = q_sign_extend_1(tmp_258);  // q_sign_extend
    const uint_fast8_t tmp_266 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_273 = q_sign_extend_2(tmp_266);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_274 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_265), static_cast<uint_fast64_t>(tmp_273)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_275 = uint_fast8_t(tmp_274[0] & 127);  // _basic_get_item_0
    const uint_fast8_t tmp_276 = uint_fast8_t(tmp_274[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_277 = uint_fast8_t((tmp_275 - tmp_276) & 127);  // basic_sub
    return tmp_277;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_280 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_280;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_281 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_282 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_281) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_283 = uint_fast8_t((tmp_282 - tmp_281) & 1);  // basic_sub
    const uint_fast8_t tmp_284 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_285 = uint_fast8_t(((uint_fast64_t(tmp_283) << 7) | arg_0) & 255);  // basic_concat
    return tmp_285;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_288 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_288;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_289 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_290 = uint_fast8_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_289) << uint_fast8_t(6 & 7))) & 127);  // basic_lshift
    const uint_fast8_t tmp_291 = uint_fast8_t((tmp_290 - tmp_289) & 63);  // basic_sub
    const uint_fast8_t tmp_292 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_293 = uint_fast8_t(((uint_fast64_t(tmp_291) << 2) | arg_0) & 255);  // basic_concat
    return tmp_293;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_279 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_286 = q_sign_extend_3(tmp_279);  // q_sign_extend
    const uint_fast8_t tmp_287 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_294 = q_sign_extend_4(tmp_287);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_295 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_286), static_cast<uint_fast64_t>(tmp_294)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_296 = uint_fast8_t(tmp_295[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_297 = uint_fast8_t(tmp_295[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_298 = uint_fast8_t((tmp_296 + tmp_297) & 255);  // basic_add
    return tmp_298;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_300 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_300;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_302 = uint_fast32_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(1 & 1))) & 4294967295);  // basic_lshift
    return tmp_302;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_305 = uint_fast8_t((arg_0 == 128) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_306 = uint_fast8_t(((~arg_0) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_307 = uint_fast8_t((tmp_306 + uint_fast8_t(1 & 1)) & 255);  // basic_add
    const uint_fast8_t tmp_308 = uint_fast8_t((arg_0 ^ arg_0) & 255);  // basic_xor
    const uint_fast8_t tmp_309 = uint_fast8_t(((~tmp_308) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_310 = uint_fast8_t((tmp_305 == 1 ? tmp_309 : tmp_307) & 255);  // basic_mux_2_1
    return tmp_310;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_311 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_312 = uint_fast8_t((arg_1 == 1 ? tmp_311 : arg_0) & 255);  // basic_mux_2_1
    return tmp_312;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_304 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_313 = q_add_sign_2(arg_0, tmp_304);  // q_add_sign
    return tmp_313;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_315 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_315;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_317 = uint_fast32_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 4294967295);  // basic_lshift
    return tmp_317;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_319 = uint_fast32_t((arg_1 >= 32 ? 0 : (arg_0 >> arg_1)) & 4294967295);  // basic_rshift
    return tmp_319;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_323 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_323;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_324 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_325 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_324) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_326 = uint_fast8_t((tmp_325 - tmp_324) & 1);  // basic_sub
    const uint_fast16_t tmp_327 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_328 = uint_fast16_t(((uint_fast64_t(tmp_326) << 9) | arg_0) & 1023);  // basic_concat
    return tmp_328;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_331 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_332 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_331) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_333 = uint_fast8_t((tmp_332 - tmp_331) & 3);  // basic_sub
    const uint_fast16_t tmp_334 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_335 = uint_fast16_t(((uint_fast64_t(tmp_333) << 8) | arg_0) & 1023);  // basic_concat
    return tmp_335;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_322 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_329 = q_sign_extend_5(tmp_322);  // q_sign_extend
    const uint_fast8_t tmp_330 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_336 = q_sign_extend_6(tmp_330);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_337 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_329), static_cast<uint_fast64_t>(tmp_336)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_338 = uint_fast16_t(tmp_337[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_339 = uint_fast16_t(tmp_337[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_340 = uint_fast16_t((tmp_338 - tmp_339) & 1023);  // basic_sub
    return tmp_340;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_342 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_343 = q_sign_extend_5(tmp_342);  // q_sign_extend
    const uint_fast8_t tmp_344 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_345 = q_sign_extend_6(tmp_344);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_346 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_343), static_cast<uint_fast64_t>(tmp_345)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_347 = uint_fast16_t(tmp_346[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_348 = uint_fast16_t(tmp_346[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_349 = uint_fast16_t((tmp_347 + tmp_348) & 1023);  // basic_add
    return tmp_349;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_356 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_357 = uint_fast8_t(((~tmp_356) & 1) & 1);  // basic_invert
    return tmp_357;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_359 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_359;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_363 = uint_fast8_t((arg_0 == 512) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_364 = uint_fast16_t(((~arg_0) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_365 = uint_fast16_t((tmp_364 + uint_fast8_t(1 & 1)) & 1023);  // basic_add
    const uint_fast16_t tmp_366 = uint_fast16_t((arg_0 ^ arg_0) & 1023);  // basic_xor
    const uint_fast16_t tmp_367 = uint_fast16_t(((~tmp_366) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_368 = uint_fast16_t((tmp_363 == 1 ? tmp_367 : tmp_365) & 1023);  // basic_mux_2_1
    return tmp_368;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_369 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_370 = uint_fast16_t((arg_1 == 1 ? tmp_369 : arg_0) & 1023);  // basic_mux_2_1
    return tmp_370;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_362 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_371 = q_add_sign_3(arg_0, tmp_362);  // q_add_sign
    return tmp_371;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_373 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_373;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_375 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_376 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_377 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_375), static_cast<uint_fast64_t>(tmp_376)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_378 = uint_fast16_t(tmp_377[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_379 = uint_fast16_t(tmp_377[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_380 = uint_fast16_t((tmp_378 + tmp_379) & 1023);  // basic_add
    return tmp_380;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_383 = uint_fast64_t((arg_1 >= 41 ? 0 : (arg_0 >> arg_1)) & 2199023255551);  // basic_rshift
    return tmp_383;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_388 = uint_fast64_t(((arg_0 >> 0) & 1099511627775) & 1099511627775);  // basic_select
    return tmp_388;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_391 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_392 = uint_fast8_t(((~tmp_391) & 1) & 1);  // basic_invert
    return tmp_392;
}
static inline uint_fast32_t uq_resize_2(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_394 = uint_fast32_t((uint_fast8_t(17 & 31) >= 40 ? 0 : (arg_0 >> uint_fast8_t(17 & 31))) & 8388607);  // basic_rshift
    return tmp_394;
}
static inline uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_396 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_397 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_398 = uint_fast16_t(((arg_0 >> 0) & 32767) & 32767);  // basic_select
    const uint_fast8_t tmp_399 = uint_fast8_t((tmp_398 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_400 = uint_fast8_t((tmp_397 | tmp_399) & 1);  // basic_or
    const uint_fast8_t tmp_401 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_402 = uint_fast8_t((tmp_400 | tmp_401) & 1);  // basic_or
    const uint_fast8_t tmp_403 = uint_fast8_t((tmp_396 & tmp_402) & 1);  // basic_and
    const uint_fast32_t tmp_404 = uint_fast32_t(tmp_403 & 8388607);  // basic_identity
    return tmp_404;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_406 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_407 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_408 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_406), static_cast<uint_fast64_t>(tmp_407)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_409 = uint_fast32_t(tmp_408[0] & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_410 = uint_fast32_t(tmp_408[1] & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_411 = uint_fast32_t((tmp_409 + tmp_410) & 16777215);  // basic_add
    return tmp_411;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_414 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_415 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_416 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_414), static_cast<uint_fast64_t>(tmp_415)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_417 = uint_fast16_t(tmp_416[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_418 = uint_fast16_t(tmp_416[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_419 = uint_fast16_t((tmp_417 + tmp_418) & 1023);  // basic_add
    return tmp_419;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_429 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_430 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_431 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_429), static_cast<uint_fast64_t>(tmp_430)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_432 = uint_fast16_t(tmp_431[0] & 1023);  // _basic_get_item_0
    const uint_fast16_t tmp_433 = uint_fast16_t(tmp_431[1] & 1023);  // _basic_get_item_1
    const uint_fast16_t tmp_434 = uint_fast16_t((tmp_432 < tmp_433 ? tmp_432 : tmp_433) & 1023);  // basic_min
    return tmp_434;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_441 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_442 = uint_fast8_t(((~tmp_441) & 1) & 1);  // basic_invert
    return tmp_442;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_449 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_449;
}
static inline uint_fast32_t encode_Float32(uint_fast32_t arg_0, uint_fast16_t arg_1, uint_fast8_t arg_2) {  // encode_Float32
    const uint_fast8_t tmp_99 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_110 = q_abs(arg_0);  // q_abs
    const uint_fast32_t tmp_112 = q_to_uq(tmp_110);  // q_to_uq
    // begin inline primitive fp32_normalize
    const uint_fast8_t tmp_237 = lzc(tmp_112);  // lzc
    const uint_fast8_t tmp_247 = uq_to_q_2(tmp_237);  // uq_to_q
    const uint_fast8_t tmp_257 = uq_to_q_3(uint_fast8_t(2 & 3));  // uq_to_q
    const uint_fast8_t tmp_278 = q_sub(tmp_247, tmp_257);  // q_sub
    const uint_fast8_t tmp_299 = q_add_1(tmp_278, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_301 = q_sign_bit_6(tmp_299);  // q_sign_bit
    const uint_fast32_t tmp_303 = uq_resize_1(tmp_112);  // uq_resize
    const uint_fast8_t tmp_314 = q_abs_1(tmp_299);  // q_abs
    const uint_fast8_t tmp_316 = q_to_uq_1(tmp_314);  // q_to_uq
    const uint_fast32_t tmp_318 = uq_lshift(tmp_303, tmp_316);  // uq_lshift
    const uint_fast32_t tmp_320 = uq_rshift_1(tmp_303, tmp_316);  // uq_rshift
    const uint_fast32_t tmp_321 = uint_fast32_t((tmp_301 == 1 ? tmp_320 : tmp_318) & 2147483647);  // basic_mux_2_1
    const uint_fast16_t tmp_341 = q_sub_1(arg_1, tmp_314);  // q_sub
    const uint_fast16_t tmp_350 = q_add_2(arg_1, tmp_314);  // q_add
    const uint_fast16_t tmp_351 = uint_fast16_t((tmp_301 == 1 ? tmp_350 : tmp_341) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_352 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_321), static_cast<uint_fast64_t>(tmp_351)};  // basic_tuple_maker_2
    // end inline primitive fp32_normalize
    const uint_fast32_t tmp_353 = uint_fast32_t(tmp_352[0] & 2147483647);  // _basic_get_item_0
    const uint_fast16_t tmp_354 = uint_fast16_t(tmp_352[1] & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_classify
    const uint_fast64_t tmp_355 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_353) << uint_fast8_t(10 & 15))) & 2199023255551);  // basic_lshift
    const uint_fast8_t tmp_358 = q_is_zero(tmp_354);  // q_is_zero
    const uint_fast8_t tmp_360 = q_sign_bit_8(tmp_354);  // q_sign_bit
    const uint_fast8_t tmp_361 = uint_fast8_t((tmp_358 | tmp_360) & 1);  // basic_or
    const uint_fast16_t tmp_372 = q_abs_2(tmp_354);  // q_abs
    const uint_fast16_t tmp_374 = q_to_uq_2(tmp_372);  // q_to_uq
    const uint_fast16_t tmp_381 = uq_add_4(uint_fast8_t(1 & 1), tmp_374);  // uq_add
    const uint_fast16_t tmp_382 = uint_fast16_t((tmp_361 == 1 ? tmp_381 : uint_fast8_t(0 & 1)) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_384 = uq_rshift_2(tmp_355, tmp_382);  // uq_rshift
    const uint_fast16_t tmp_385 = uint_fast16_t((tmp_361 == 1 ? uint_fast8_t(0 & 1) : tmp_374) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_386 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_384), static_cast<uint_fast64_t>(tmp_385)};  // basic_tuple_maker_2
    // end inline primitive fp32_classify
    const uint_fast64_t tmp_387 = uint_fast64_t(tmp_386[0] & 2199023255551);  // _basic_get_item_0
    const uint_fast64_t tmp_389 = drop_implicit_bit(tmp_387);  // drop_implicit_bit
    const uint_fast16_t tmp_390 = uint_fast16_t(tmp_386[1] & 511);  // _basic_get_item_1
    // begin inline primitive fp32_round
    const uint_fast8_t tmp_393 = uq_is_zero(tmp_390);  // uq_is_zero
    const uint_fast32_t tmp_395 = uq_resize_2(tmp_389);  // uq_resize
    const uint_fast32_t tmp_405 = uq_RNE_IEEE(tmp_389);  // uq_RNE_IEEE
    const uint_fast32_t tmp_412 = uq_add_5(tmp_395, tmp_405);  // uq_add
    const uint_fast8_t tmp_413 = uint_fast8_t(((tmp_412 >> 23) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_420 = uq_add_6(tmp_390, tmp_413);  // uq_add
    const uint_fast8_t tmp_421 = uint_fast8_t((tmp_420 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_422 = uint_fast8_t((tmp_393 & tmp_421) & 1);  // basic_and
    const uint_fast32_t tmp_423 = uint_fast32_t((uint_fast8_t(1 & 1) >= 24 ? 0 : (tmp_412 >> uint_fast8_t(1 & 1))) & 8388607);  // basic_rshift
    const uint_fast32_t tmp_424 = uint_fast32_t((tmp_413 == 1 ? tmp_423 : tmp_412) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_425 = uint_fast32_t((tmp_422 == 1 ? uint_fast8_t(0 & 1) : tmp_424) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_426 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_425), static_cast<uint_fast64_t>(tmp_420)};  // basic_tuple_maker_2
    // end inline primitive fp32_round
    const uint_fast32_t tmp_427 = uint_fast32_t(tmp_426[0] & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_428 = uint_fast16_t(tmp_426[1] & 1023);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_435 = uq_min(tmp_428, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_436 = uint_fast8_t(tmp_435 & 255);  // basic_identity
    const uint_fast8_t tmp_437 = uint_fast8_t((tmp_436 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_438 = uint_fast32_t((tmp_437 == 1 ? uint_fast8_t(0 & 1) : tmp_427) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_439 = uint_fast32_t((arg_2 == 1 ? uint_fast8_t(1 & 1) : tmp_438) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_440 = uint_fast32_t(tmp_439 & 8388607);  // basic_identity
    const uint_fast8_t tmp_443 = uq_is_zero_1(tmp_112);  // uq_is_zero
    const uint_fast8_t tmp_444 = uint_fast8_t((tmp_443 == 1 ? uint_fast8_t(0 & 1) : tmp_436) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_445 = uint_fast8_t((arg_2 == 1 ? uint_fast8_t(255 & 255) : tmp_444) & 255);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_446 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_440), static_cast<uint_fast64_t>(tmp_445)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_447 = uint_fast8_t(tmp_446[1] & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_448 = uint_fast32_t(tmp_446[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_450 = fp32_pack(tmp_99, tmp_447, tmp_448);  // fp32_pack
    return tmp_450;
}
static inline uint_fast32_t FP32_IEEE_adder_impl(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // FP32_IEEE_adder
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_1 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_2 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_3 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp), static_cast<uint_fast64_t>(tmp_1), static_cast<uint_fast64_t>(tmp_2)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast32_t tmp_4 = uint_fast32_t(tmp_3[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_6 = add_implicit_bit(tmp_4);  // add_implicit_bit
    const uint_fast32_t tmp_8 = uq_resize(tmp_6);  // uq_resize
    const uint_fast8_t tmp_9 = uint_fast8_t(tmp_3[1] & 255);  // _basic_get_item_1
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_10 = uint_fast8_t(((arg_1 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_11 = uint_fast8_t(((arg_1 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_12 = uint_fast32_t(((arg_1 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_13 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_10), static_cast<uint_fast64_t>(tmp_11), static_cast<uint_fast64_t>(tmp_12)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_14 = uint_fast8_t(tmp_13[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_21 = uq_max(tmp_9, tmp_14);  // uq_max
    const uint_fast16_t tmp_28 = uq_sub(tmp_21, tmp_9);  // uq_sub
    const uint_fast32_t tmp_30 = uq_rshift(tmp_8, tmp_28);  // uq_rshift
    const uint_fast32_t tmp_40 = uq_to_q(tmp_30);  // uq_to_q
    const uint_fast8_t tmp_41 = uint_fast8_t(tmp_3[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_50 = q_add_sign(tmp_40, tmp_41);  // q_add_sign
    const uint_fast32_t tmp_51 = uint_fast32_t(tmp_13[2] & 8388607);  // _basic_get_item_2
    const uint_fast32_t tmp_52 = add_implicit_bit(tmp_51);  // add_implicit_bit
    const uint_fast32_t tmp_53 = uq_resize(tmp_52);  // uq_resize
    const uint_fast16_t tmp_54 = uq_sub(tmp_21, tmp_14);  // uq_sub
    const uint_fast32_t tmp_55 = uq_rshift(tmp_53, tmp_54);  // uq_rshift
    const uint_fast32_t tmp_56 = uq_to_q(tmp_55);  // uq_to_q
    const uint_fast8_t tmp_57 = uint_fast8_t(tmp_13[0] & 1);  // _basic_get_item_0
    const uint_fast32_t tmp_58 = q_add_sign(tmp_56, tmp_57);  // q_add_sign
    const uint_fast32_t tmp_73 = q_add(tmp_50, tmp_58);  // q_add
    const uint_fast16_t tmp_83 = uq_to_q_1(tmp_21);  // uq_to_q
    const uint_fast8_t tmp_89 = fp32_is_nan(arg_0);  // fp32_is_nan
    const uint_fast8_t tmp_90 = fp32_is_nan(arg_1);  // fp32_is_nan
    const uint_fast8_t tmp_97 = uq_max_1(tmp_89, tmp_90);  // uq_max
    const uint_fast32_t tmp_451 = encode_Float32(tmp_73, tmp_83, tmp_97);  // encode_Float32
    return tmp_451;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}