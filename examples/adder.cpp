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
    const uint_fast8_t tmp_18 = uint_fast8_t(tmp_17[0] & 255);  // basic_get_item_0
    const uint_fast8_t tmp_19 = uint_fast8_t(tmp_17[1] & 255);  // basic_get_item_1
    const uint_fast8_t tmp_20 = uint_fast8_t((tmp_18 > tmp_19 ? tmp_18 : tmp_19) & 255);  // basic_max
    return tmp_20;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_22 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_23 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_24 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_22), static_cast<uint_fast64_t>(tmp_23)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_25 = uint_fast16_t(tmp_24[0] & 511);  // basic_get_item_0
    const uint_fast16_t tmp_26 = uint_fast16_t(tmp_24[1] & 511);  // basic_get_item_1
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
    const uint_fast8_t tmp_34 = uint_fast8_t(tmp_33[0] & 3);  // basic_get_item_0
    const uint_fast8_t tmp_35 = uint_fast8_t(tmp_33[1] & 3);  // basic_get_item_1
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
    const uint_fast32_t tmp_70 = uint_fast32_t(tmp_69[0] & 4294967295);  // basic_get_item_0
    const uint_fast32_t tmp_71 = uint_fast32_t(tmp_69[1] & 4294967295);  // basic_get_item_1
    const uint_fast32_t tmp_72 = uint_fast32_t((tmp_70 + tmp_71) & 4294967295);  // basic_add
    return tmp_72;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_74 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_75 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_76 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_74), static_cast<uint_fast64_t>(tmp_75)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_77 = uint_fast8_t(tmp_76[0] & 31);  // basic_get_item_0
    const uint_fast8_t tmp_78 = uint_fast8_t(tmp_76[1] & 31);  // basic_get_item_1
    const uint_fast8_t tmp_79 = uint_fast8_t((tmp_77 + tmp_78) & 31);  // basic_add
    return tmp_79;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_80 = uq_add_1(uint_fast8_t(8 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_81 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_82 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_82;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_84 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    return tmp_84;
}
static inline uint_fast32_t q_neg_1(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_87 = uint_fast8_t((arg_0 == 2147483648) & 1);  // _q_is_min_val
    const uint_fast32_t tmp_88 = uint_fast32_t(((~arg_0) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_89 = uint_fast32_t((tmp_88 + uint_fast8_t(1 & 1)) & 4294967295);  // basic_add
    const uint_fast32_t tmp_90 = uint_fast32_t((arg_0 ^ arg_0) & 4294967295);  // basic_xor
    const uint_fast32_t tmp_91 = uint_fast32_t(((~tmp_90) & 4294967295) & 4294967295);  // basic_invert
    const uint_fast32_t tmp_92 = uint_fast32_t((tmp_87 == 1 ? tmp_91 : tmp_89) & 4294967295);  // basic_mux_2_1
    return tmp_92;
}
static inline uint_fast32_t q_add_sign_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_93 = q_neg_1(arg_0);  // q_neg
    const uint_fast32_t tmp_94 = uint_fast32_t((arg_1 == 1 ? tmp_93 : arg_0) & 4294967295);  // basic_mux_2_1
    return tmp_94;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_86 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_95 = q_add_sign_1(arg_0, tmp_86);  // q_add_sign
    return tmp_95;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_97 = uint_fast32_t(arg_0 & 2147483647);  // basic_identity
    return tmp_97;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_99 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_100 = uint_fast8_t(((~tmp_99) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_101 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_100) & 1);  // basic_and
    const uint_fast8_t tmp_102 = uint_fast8_t((uint_fast8_t(0 & 31) + tmp_101) & 31);  // basic_add
    const uint_fast8_t tmp_103 = uint_fast8_t(((arg_0 >> 29) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_104 = uint_fast8_t(((~tmp_103) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_105 = uint_fast8_t((tmp_101 & tmp_104) & 1);  // basic_and
    const uint_fast8_t tmp_106 = uint_fast8_t((tmp_102 + tmp_105) & 31);  // basic_add
    const uint_fast8_t tmp_107 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_108 = uint_fast8_t(((~tmp_107) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_109 = uint_fast8_t((tmp_105 & tmp_108) & 1);  // basic_and
    const uint_fast8_t tmp_110 = uint_fast8_t((tmp_106 + tmp_109) & 31);  // basic_add
    const uint_fast8_t tmp_111 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_112 = uint_fast8_t(((~tmp_111) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_113 = uint_fast8_t((tmp_109 & tmp_112) & 1);  // basic_and
    const uint_fast8_t tmp_114 = uint_fast8_t((tmp_110 + tmp_113) & 31);  // basic_add
    const uint_fast8_t tmp_115 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_116 = uint_fast8_t(((~tmp_115) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_117 = uint_fast8_t((tmp_113 & tmp_116) & 1);  // basic_and
    const uint_fast8_t tmp_118 = uint_fast8_t((tmp_114 + tmp_117) & 31);  // basic_add
    const uint_fast8_t tmp_119 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_120 = uint_fast8_t(((~tmp_119) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_121 = uint_fast8_t((tmp_117 & tmp_120) & 1);  // basic_and
    const uint_fast8_t tmp_122 = uint_fast8_t((tmp_118 + tmp_121) & 31);  // basic_add
    const uint_fast8_t tmp_123 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_124 = uint_fast8_t(((~tmp_123) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_125 = uint_fast8_t((tmp_121 & tmp_124) & 1);  // basic_and
    const uint_fast8_t tmp_126 = uint_fast8_t((tmp_122 + tmp_125) & 31);  // basic_add
    const uint_fast8_t tmp_127 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_128 = uint_fast8_t(((~tmp_127) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_129 = uint_fast8_t((tmp_125 & tmp_128) & 1);  // basic_and
    const uint_fast8_t tmp_130 = uint_fast8_t((tmp_126 + tmp_129) & 31);  // basic_add
    const uint_fast8_t tmp_131 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_132 = uint_fast8_t(((~tmp_131) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_133 = uint_fast8_t((tmp_129 & tmp_132) & 1);  // basic_and
    const uint_fast8_t tmp_134 = uint_fast8_t((tmp_130 + tmp_133) & 31);  // basic_add
    const uint_fast8_t tmp_135 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_136 = uint_fast8_t(((~tmp_135) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_137 = uint_fast8_t((tmp_133 & tmp_136) & 1);  // basic_and
    const uint_fast8_t tmp_138 = uint_fast8_t((tmp_134 + tmp_137) & 31);  // basic_add
    const uint_fast8_t tmp_139 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_140 = uint_fast8_t(((~tmp_139) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_141 = uint_fast8_t((tmp_137 & tmp_140) & 1);  // basic_and
    const uint_fast8_t tmp_142 = uint_fast8_t((tmp_138 + tmp_141) & 31);  // basic_add
    const uint_fast8_t tmp_143 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_144 = uint_fast8_t(((~tmp_143) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_145 = uint_fast8_t((tmp_141 & tmp_144) & 1);  // basic_and
    const uint_fast8_t tmp_146 = uint_fast8_t((tmp_142 + tmp_145) & 31);  // basic_add
    const uint_fast8_t tmp_147 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_148 = uint_fast8_t(((~tmp_147) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_149 = uint_fast8_t((tmp_145 & tmp_148) & 1);  // basic_and
    const uint_fast8_t tmp_150 = uint_fast8_t((tmp_146 + tmp_149) & 31);  // basic_add
    const uint_fast8_t tmp_151 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_152 = uint_fast8_t(((~tmp_151) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_153 = uint_fast8_t((tmp_149 & tmp_152) & 1);  // basic_and
    const uint_fast8_t tmp_154 = uint_fast8_t((tmp_150 + tmp_153) & 31);  // basic_add
    const uint_fast8_t tmp_155 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_156 = uint_fast8_t(((~tmp_155) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_157 = uint_fast8_t((tmp_153 & tmp_156) & 1);  // basic_and
    const uint_fast8_t tmp_158 = uint_fast8_t((tmp_154 + tmp_157) & 31);  // basic_add
    const uint_fast8_t tmp_159 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_160 = uint_fast8_t(((~tmp_159) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_161 = uint_fast8_t((tmp_157 & tmp_160) & 1);  // basic_and
    const uint_fast8_t tmp_162 = uint_fast8_t((tmp_158 + tmp_161) & 31);  // basic_add
    const uint_fast8_t tmp_163 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_164 = uint_fast8_t(((~tmp_163) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_165 = uint_fast8_t((tmp_161 & tmp_164) & 1);  // basic_and
    const uint_fast8_t tmp_166 = uint_fast8_t((tmp_162 + tmp_165) & 31);  // basic_add
    const uint_fast8_t tmp_167 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_168 = uint_fast8_t(((~tmp_167) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_169 = uint_fast8_t((tmp_165 & tmp_168) & 1);  // basic_and
    const uint_fast8_t tmp_170 = uint_fast8_t((tmp_166 + tmp_169) & 31);  // basic_add
    const uint_fast8_t tmp_171 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_172 = uint_fast8_t(((~tmp_171) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_173 = uint_fast8_t((tmp_169 & tmp_172) & 1);  // basic_and
    const uint_fast8_t tmp_174 = uint_fast8_t((tmp_170 + tmp_173) & 31);  // basic_add
    const uint_fast8_t tmp_175 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_176 = uint_fast8_t(((~tmp_175) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_177 = uint_fast8_t((tmp_173 & tmp_176) & 1);  // basic_and
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_174 + tmp_177) & 31);  // basic_add
    const uint_fast8_t tmp_179 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_180 = uint_fast8_t(((~tmp_179) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_181 = uint_fast8_t((tmp_177 & tmp_180) & 1);  // basic_and
    const uint_fast8_t tmp_182 = uint_fast8_t((tmp_178 + tmp_181) & 31);  // basic_add
    const uint_fast8_t tmp_183 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_184 = uint_fast8_t(((~tmp_183) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_185 = uint_fast8_t((tmp_181 & tmp_184) & 1);  // basic_and
    const uint_fast8_t tmp_186 = uint_fast8_t((tmp_182 + tmp_185) & 31);  // basic_add
    const uint_fast8_t tmp_187 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_188 = uint_fast8_t(((~tmp_187) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_189 = uint_fast8_t((tmp_185 & tmp_188) & 1);  // basic_and
    const uint_fast8_t tmp_190 = uint_fast8_t((tmp_186 + tmp_189) & 31);  // basic_add
    const uint_fast8_t tmp_191 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_192 = uint_fast8_t(((~tmp_191) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_193 = uint_fast8_t((tmp_189 & tmp_192) & 1);  // basic_and
    const uint_fast8_t tmp_194 = uint_fast8_t((tmp_190 + tmp_193) & 31);  // basic_add
    const uint_fast8_t tmp_195 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_196 = uint_fast8_t(((~tmp_195) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_197 = uint_fast8_t((tmp_193 & tmp_196) & 1);  // basic_and
    const uint_fast8_t tmp_198 = uint_fast8_t((tmp_194 + tmp_197) & 31);  // basic_add
    const uint_fast8_t tmp_199 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_200 = uint_fast8_t(((~tmp_199) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_201 = uint_fast8_t((tmp_197 & tmp_200) & 1);  // basic_and
    const uint_fast8_t tmp_202 = uint_fast8_t((tmp_198 + tmp_201) & 31);  // basic_add
    const uint_fast8_t tmp_203 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_204 = uint_fast8_t(((~tmp_203) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_205 = uint_fast8_t((tmp_201 & tmp_204) & 1);  // basic_and
    const uint_fast8_t tmp_206 = uint_fast8_t((tmp_202 + tmp_205) & 31);  // basic_add
    const uint_fast8_t tmp_207 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_208 = uint_fast8_t(((~tmp_207) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_209 = uint_fast8_t((tmp_205 & tmp_208) & 1);  // basic_and
    const uint_fast8_t tmp_210 = uint_fast8_t((tmp_206 + tmp_209) & 31);  // basic_add
    const uint_fast8_t tmp_211 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_212 = uint_fast8_t(((~tmp_211) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_213 = uint_fast8_t((tmp_209 & tmp_212) & 1);  // basic_and
    const uint_fast8_t tmp_214 = uint_fast8_t((tmp_210 + tmp_213) & 31);  // basic_add
    const uint_fast8_t tmp_215 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_216 = uint_fast8_t(((~tmp_215) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_217 = uint_fast8_t((tmp_213 & tmp_216) & 1);  // basic_and
    const uint_fast8_t tmp_218 = uint_fast8_t((tmp_214 + tmp_217) & 31);  // basic_add
    const uint_fast8_t tmp_219 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_220 = uint_fast8_t(((~tmp_219) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_221 = uint_fast8_t((tmp_217 & tmp_220) & 1);  // basic_and
    const uint_fast8_t tmp_222 = uint_fast8_t((tmp_218 + tmp_221) & 31);  // basic_add
    return tmp_222;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_224 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_225 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_226 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_224), static_cast<uint_fast64_t>(tmp_225)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_227 = uint_fast8_t(tmp_226[0] & 15);  // basic_get_item_0
    const uint_fast8_t tmp_228 = uint_fast8_t(tmp_226[1] & 15);  // basic_get_item_1
    const uint_fast8_t tmp_229 = uint_fast8_t((tmp_227 + tmp_228) & 15);  // basic_add
    return tmp_229;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_230 = uq_add_2(uint_fast8_t(5 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_231 = uint_fast8_t(0 & 63);  // q_alloc
    const uint_fast8_t tmp_232 = uint_fast8_t(arg_0 & 63);  // basic_identity
    return tmp_232;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_234 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_235 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_236 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_234), static_cast<uint_fast64_t>(tmp_235)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_237 = uint_fast8_t(tmp_236[0] & 7);  // basic_get_item_0
    const uint_fast8_t tmp_238 = uint_fast8_t(tmp_236[1] & 7);  // basic_get_item_1
    const uint_fast8_t tmp_239 = uint_fast8_t((tmp_237 + tmp_238) & 7);  // basic_add
    return tmp_239;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_240 = uq_add_3(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_241 = uint_fast8_t(0 & 7);  // q_alloc
    const uint_fast8_t tmp_242 = uint_fast8_t(arg_0 & 7);  // basic_identity
    return tmp_242;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_245 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    return tmp_245;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_246 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_247 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_246) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_248 = uint_fast8_t((tmp_247 - tmp_246) & 1);  // basic_sub
    const uint_fast8_t tmp_249 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_250 = uint_fast8_t(((uint_fast64_t(tmp_248) << 6) | arg_0) & 127);  // basic_concat
    return tmp_250;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_253 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    return tmp_253;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_254 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_255 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_254) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_256 = uint_fast8_t((tmp_255 - tmp_254) & 15);  // basic_sub
    const uint_fast8_t tmp_257 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_258 = uint_fast8_t(((uint_fast64_t(tmp_256) << 3) | arg_0) & 127);  // basic_concat
    return tmp_258;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_244 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast8_t tmp_251 = q_sign_extend_1(tmp_244);  // q_sign_extend
    const uint_fast8_t tmp_252 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_259 = q_sign_extend_2(tmp_252);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_260 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_251), static_cast<uint_fast64_t>(tmp_259)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_261 = uint_fast8_t(tmp_260[0] & 127);  // basic_get_item_0
    const uint_fast8_t tmp_262 = uint_fast8_t(tmp_260[1] & 127);  // basic_get_item_1
    const uint_fast8_t tmp_263 = uint_fast8_t((tmp_261 - tmp_262) & 127);  // basic_sub
    return tmp_263;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_266 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_266;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_267 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_268 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_267) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_269 = uint_fast8_t((tmp_268 - tmp_267) & 1);  // basic_sub
    const uint_fast8_t tmp_270 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_271 = uint_fast8_t(((uint_fast64_t(tmp_269) << 7) | arg_0) & 255);  // basic_concat
    return tmp_271;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_274 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_274;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_275 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_276 = uint_fast8_t((uint_fast8_t(6 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_275) << uint_fast8_t(6 & 7))) & 127);  // basic_lshift
    const uint_fast8_t tmp_277 = uint_fast8_t((tmp_276 - tmp_275) & 63);  // basic_sub
    const uint_fast8_t tmp_278 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_279 = uint_fast8_t(((uint_fast64_t(tmp_277) << 2) | arg_0) & 255);  // basic_concat
    return tmp_279;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_265 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_272 = q_sign_extend_3(tmp_265);  // q_sign_extend
    const uint_fast8_t tmp_273 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_280 = q_sign_extend_4(tmp_273);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_281 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_272), static_cast<uint_fast64_t>(tmp_280)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_282 = uint_fast8_t(tmp_281[0] & 255);  // basic_get_item_0
    const uint_fast8_t tmp_283 = uint_fast8_t(tmp_281[1] & 255);  // basic_get_item_1
    const uint_fast8_t tmp_284 = uint_fast8_t((tmp_282 + tmp_283) & 255);  // basic_add
    return tmp_284;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_286 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_286;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_288 = uint_fast32_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(1 & 1))) & 4294967295);  // basic_lshift
    return tmp_288;
}
static inline uint_fast8_t q_neg_2(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_291 = uint_fast8_t((arg_0 == 128) & 1);  // _q_is_min_val
    const uint_fast8_t tmp_292 = uint_fast8_t(((~arg_0) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_293 = uint_fast8_t((tmp_292 + uint_fast8_t(1 & 1)) & 255);  // basic_add
    const uint_fast8_t tmp_294 = uint_fast8_t((arg_0 ^ arg_0) & 255);  // basic_xor
    const uint_fast8_t tmp_295 = uint_fast8_t(((~tmp_294) & 255) & 255);  // basic_invert
    const uint_fast8_t tmp_296 = uint_fast8_t((tmp_291 == 1 ? tmp_295 : tmp_293) & 255);  // basic_mux_2_1
    return tmp_296;
}
static inline uint_fast8_t q_add_sign_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_297 = q_neg_2(arg_0);  // q_neg
    const uint_fast8_t tmp_298 = uint_fast8_t((arg_1 == 1 ? tmp_297 : arg_0) & 255);  // basic_mux_2_1
    return tmp_298;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_290 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_299 = q_add_sign_2(arg_0, tmp_290);  // q_add_sign
    return tmp_299;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_301 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_301;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_303 = uint_fast32_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 4294967295);  // basic_lshift
    return tmp_303;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_305 = uint_fast32_t((arg_1 >= 32 ? 0 : (arg_0 >> arg_1)) & 4294967295);  // basic_rshift
    return tmp_305;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_309 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_309;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_310 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_311 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_310) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_312 = uint_fast8_t((tmp_311 - tmp_310) & 1);  // basic_sub
    const uint_fast16_t tmp_313 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_314 = uint_fast16_t(((uint_fast64_t(tmp_312) << 9) | arg_0) & 1023);  // basic_concat
    return tmp_314;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_317 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_318 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_317) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_319 = uint_fast8_t((tmp_318 - tmp_317) & 3);  // basic_sub
    const uint_fast16_t tmp_320 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_321 = uint_fast16_t(((uint_fast64_t(tmp_319) << 8) | arg_0) & 1023);  // basic_concat
    return tmp_321;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_308 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_315 = q_sign_extend_5(tmp_308);  // q_sign_extend
    const uint_fast8_t tmp_316 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_322 = q_sign_extend_6(tmp_316);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_323 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_315), static_cast<uint_fast64_t>(tmp_322)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_324 = uint_fast16_t(tmp_323[0] & 1023);  // basic_get_item_0
    const uint_fast16_t tmp_325 = uint_fast16_t(tmp_323[1] & 1023);  // basic_get_item_1
    const uint_fast16_t tmp_326 = uint_fast16_t((tmp_324 - tmp_325) & 1023);  // basic_sub
    return tmp_326;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_328 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_329 = q_sign_extend_5(tmp_328);  // q_sign_extend
    const uint_fast8_t tmp_330 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_331 = q_sign_extend_6(tmp_330);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_332 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_329), static_cast<uint_fast64_t>(tmp_331)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_333 = uint_fast16_t(tmp_332[0] & 1023);  // basic_get_item_0
    const uint_fast16_t tmp_334 = uint_fast16_t(tmp_332[1] & 1023);  // basic_get_item_1
    const uint_fast16_t tmp_335 = uint_fast16_t((tmp_333 + tmp_334) & 1023);  // basic_add
    return tmp_335;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_342 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_343 = uint_fast8_t(((~tmp_342) & 1) & 1);  // basic_invert
    return tmp_343;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_345 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_345;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_349 = uint_fast8_t((arg_0 == 512) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_350 = uint_fast16_t(((~arg_0) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_351 = uint_fast16_t((tmp_350 + uint_fast8_t(1 & 1)) & 1023);  // basic_add
    const uint_fast16_t tmp_352 = uint_fast16_t((arg_0 ^ arg_0) & 1023);  // basic_xor
    const uint_fast16_t tmp_353 = uint_fast16_t(((~tmp_352) & 1023) & 1023);  // basic_invert
    const uint_fast16_t tmp_354 = uint_fast16_t((tmp_349 == 1 ? tmp_353 : tmp_351) & 1023);  // basic_mux_2_1
    return tmp_354;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_355 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_356 = uint_fast16_t((arg_1 == 1 ? tmp_355 : arg_0) & 1023);  // basic_mux_2_1
    return tmp_356;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_348 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_357 = q_add_sign_3(arg_0, tmp_348);  // q_add_sign
    return tmp_357;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_359 = uint_fast16_t(arg_0 & 511);  // basic_identity
    return tmp_359;
}
static inline uint_fast16_t uq_add_4(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_361 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_362 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_363 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_361), static_cast<uint_fast64_t>(tmp_362)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_364 = uint_fast16_t(tmp_363[0] & 1023);  // basic_get_item_0
    const uint_fast16_t tmp_365 = uint_fast16_t(tmp_363[1] & 1023);  // basic_get_item_1
    const uint_fast16_t tmp_366 = uint_fast16_t((tmp_364 + tmp_365) & 1023);  // basic_add
    return tmp_366;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_369 = uint_fast64_t((arg_1 >= 41 ? 0 : (arg_0 >> arg_1)) & 2199023255551);  // basic_rshift
    return tmp_369;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_374 = uint_fast64_t(((arg_0 >> 0) & 1099511627775) & 1099511627775);  // basic_select
    return tmp_374;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_377 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_378 = uint_fast8_t(((~tmp_377) & 1) & 1);  // basic_invert
    return tmp_378;
}
static inline uint_fast32_t uq_resize_2(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_380 = uint_fast32_t((uint_fast8_t(17 & 31) >= 40 ? 0 : (arg_0 >> uint_fast8_t(17 & 31))) & 8388607);  // basic_rshift
    return tmp_380;
}
static inline uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_382 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_383 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_384 = uint_fast16_t(((arg_0 >> 0) & 32767) & 32767);  // basic_select
    const uint_fast8_t tmp_385 = uint_fast8_t((tmp_384 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_386 = uint_fast8_t((tmp_383 | tmp_385) & 1);  // basic_or
    const uint_fast8_t tmp_387 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_388 = uint_fast8_t((tmp_386 | tmp_387) & 1);  // basic_or
    const uint_fast8_t tmp_389 = uint_fast8_t((tmp_382 & tmp_388) & 1);  // basic_and
    const uint_fast32_t tmp_390 = uint_fast32_t(tmp_389 & 8388607);  // basic_identity
    return tmp_390;
}
static inline uint_fast32_t uq_add_5(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_392 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_393 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_394 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_392), static_cast<uint_fast64_t>(tmp_393)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_395 = uint_fast32_t(tmp_394[0] & 16777215);  // basic_get_item_0
    const uint_fast32_t tmp_396 = uint_fast32_t(tmp_394[1] & 16777215);  // basic_get_item_1
    const uint_fast32_t tmp_397 = uint_fast32_t((tmp_395 + tmp_396) & 16777215);  // basic_add
    return tmp_397;
}
static inline uint_fast16_t uq_add_6(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_400 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_401 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_402 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_400), static_cast<uint_fast64_t>(tmp_401)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_403 = uint_fast16_t(tmp_402[0] & 1023);  // basic_get_item_0
    const uint_fast16_t tmp_404 = uint_fast16_t(tmp_402[1] & 1023);  // basic_get_item_1
    const uint_fast16_t tmp_405 = uint_fast16_t((tmp_403 + tmp_404) & 1023);  // basic_add
    return tmp_405;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_415 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_416 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_417 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_415), static_cast<uint_fast64_t>(tmp_416)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_418 = uint_fast16_t(tmp_417[0] & 1023);  // basic_get_item_0
    const uint_fast16_t tmp_419 = uint_fast16_t(tmp_417[1] & 1023);  // basic_get_item_1
    const uint_fast16_t tmp_420 = uint_fast16_t((tmp_418 < tmp_419 ? tmp_418 : tmp_419) & 1023);  // basic_min
    return tmp_420;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_426 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_427 = uint_fast8_t(((~tmp_426) & 1) & 1);  // basic_invert
    return tmp_427;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_433 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_433;
}
static inline uint_fast32_t encode_Float32(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // encode_Float32
    const uint_fast8_t tmp_85 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_96 = q_abs(arg_0);  // q_abs
    const uint_fast32_t tmp_98 = q_to_uq(tmp_96);  // q_to_uq
    // begin inline primitive fp32_normalize
    const uint_fast8_t tmp_223 = lzc(tmp_98);  // lzc
    const uint_fast8_t tmp_233 = uq_to_q_2(tmp_223);  // uq_to_q
    const uint_fast8_t tmp_243 = uq_to_q_3(uint_fast8_t(2 & 3));  // uq_to_q
    const uint_fast8_t tmp_264 = q_sub(tmp_233, tmp_243);  // q_sub
    const uint_fast8_t tmp_285 = q_add_1(tmp_264, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_287 = q_sign_bit_6(tmp_285);  // q_sign_bit
    const uint_fast32_t tmp_289 = uq_resize_1(tmp_98);  // uq_resize
    const uint_fast8_t tmp_300 = q_abs_1(tmp_285);  // q_abs
    const uint_fast8_t tmp_302 = q_to_uq_1(tmp_300);  // q_to_uq
    const uint_fast32_t tmp_304 = uq_lshift(tmp_289, tmp_302);  // uq_lshift
    const uint_fast32_t tmp_306 = uq_rshift_1(tmp_289, tmp_302);  // uq_rshift
    const uint_fast32_t tmp_307 = uint_fast32_t((tmp_287 == 1 ? tmp_306 : tmp_304) & 2147483647);  // basic_mux_2_1
    const uint_fast16_t tmp_327 = q_sub_1(arg_1, tmp_300);  // q_sub
    const uint_fast16_t tmp_336 = q_add_2(arg_1, tmp_300);  // q_add
    const uint_fast16_t tmp_337 = uint_fast16_t((tmp_287 == 1 ? tmp_336 : tmp_327) & 1023);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_338 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_307), static_cast<uint_fast64_t>(tmp_337)};  // basic_tuple_maker_2
    // end inline primitive fp32_normalize
    const uint_fast32_t tmp_339 = uint_fast32_t(tmp_338[0] & 2147483647);  // basic_get_item_0
    const uint_fast16_t tmp_340 = uint_fast16_t(tmp_338[1] & 1023);  // basic_get_item_1
    // begin inline primitive fp32_classify
    const uint_fast64_t tmp_341 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_339) << uint_fast8_t(10 & 15))) & 2199023255551);  // basic_lshift
    const uint_fast8_t tmp_344 = q_is_zero(tmp_340);  // q_is_zero
    const uint_fast8_t tmp_346 = q_sign_bit_8(tmp_340);  // q_sign_bit
    const uint_fast8_t tmp_347 = uint_fast8_t((tmp_344 | tmp_346) & 1);  // basic_or
    const uint_fast16_t tmp_358 = q_abs_2(tmp_340);  // q_abs
    const uint_fast16_t tmp_360 = q_to_uq_2(tmp_358);  // q_to_uq
    const uint_fast16_t tmp_367 = uq_add_4(uint_fast8_t(1 & 1), tmp_360);  // uq_add
    const uint_fast16_t tmp_368 = uint_fast16_t((tmp_347 == 1 ? tmp_367 : uint_fast8_t(0 & 1)) & 1023);  // basic_mux_2_1
    const uint_fast64_t tmp_370 = uq_rshift_2(tmp_341, tmp_368);  // uq_rshift
    const uint_fast16_t tmp_371 = uint_fast16_t((tmp_347 == 1 ? uint_fast8_t(0 & 1) : tmp_360) & 511);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_372 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_370), static_cast<uint_fast64_t>(tmp_371)};  // basic_tuple_maker_2
    // end inline primitive fp32_classify
    const uint_fast64_t tmp_373 = uint_fast64_t(tmp_372[0] & 2199023255551);  // basic_get_item_0
    const uint_fast64_t tmp_375 = drop_implicit_bit(tmp_373);  // drop_implicit_bit
    const uint_fast16_t tmp_376 = uint_fast16_t(tmp_372[1] & 511);  // basic_get_item_1
    // begin inline primitive fp32_round
    const uint_fast8_t tmp_379 = uq_is_zero(tmp_376);  // uq_is_zero
    const uint_fast32_t tmp_381 = uq_resize_2(tmp_375);  // uq_resize
    const uint_fast32_t tmp_391 = uq_RNE_IEEE(tmp_375);  // uq_RNE_IEEE
    const uint_fast32_t tmp_398 = uq_add_5(tmp_381, tmp_391);  // uq_add
    const uint_fast8_t tmp_399 = uint_fast8_t(((tmp_398 >> 23) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_406 = uq_add_6(tmp_376, tmp_399);  // uq_add
    const uint_fast8_t tmp_407 = uint_fast8_t((tmp_406 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_408 = uint_fast8_t((tmp_379 & tmp_407) & 1);  // basic_and
    const uint_fast32_t tmp_409 = uint_fast32_t((uint_fast8_t(1 & 1) >= 24 ? 0 : (tmp_398 >> uint_fast8_t(1 & 1))) & 8388607);  // basic_rshift
    const uint_fast32_t tmp_410 = uint_fast32_t((tmp_399 == 1 ? tmp_409 : tmp_398) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_411 = uint_fast32_t((tmp_408 == 1 ? uint_fast8_t(0 & 1) : tmp_410) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_412 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_411), static_cast<uint_fast64_t>(tmp_406)};  // basic_tuple_maker_2
    // end inline primitive fp32_round
    const uint_fast32_t tmp_413 = uint_fast32_t(tmp_412[0] & 8388607);  // basic_get_item_0
    const uint_fast16_t tmp_414 = uint_fast16_t(tmp_412[1] & 1023);  // basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_421 = uq_min(tmp_414, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_422 = uint_fast8_t(tmp_421 & 255);  // basic_identity
    const uint_fast8_t tmp_423 = uint_fast8_t((tmp_422 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_424 = uint_fast32_t((tmp_423 == 1 ? uint_fast8_t(0 & 1) : tmp_413) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_425 = uint_fast32_t(tmp_424 & 8388607);  // basic_identity
    const uint_fast8_t tmp_428 = uq_is_zero_1(tmp_98);  // uq_is_zero
    const uint_fast8_t tmp_429 = uint_fast8_t((tmp_428 == 1 ? uint_fast8_t(0 & 1) : tmp_422) & 255);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_430 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_425), static_cast<uint_fast64_t>(tmp_429)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_431 = uint_fast8_t(tmp_430[1] & 255);  // basic_get_item_1
    const uint_fast32_t tmp_432 = uint_fast32_t(tmp_430[0] & 8388607);  // basic_get_item_0
    const uint_fast32_t tmp_434 = fp32_pack(tmp_85, tmp_431, tmp_432);  // fp32_pack
    return tmp_434;
}
static inline uint_fast32_t FP32_IEEE_adder_impl(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // FP32_IEEE_adder
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_1 = uint_fast8_t(((arg_0 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_2 = uint_fast32_t(((arg_0 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_3 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp), static_cast<uint_fast64_t>(tmp_1), static_cast<uint_fast64_t>(tmp_2)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast32_t tmp_4 = uint_fast32_t(tmp_3[2] & 8388607);  // basic_get_item_2
    const uint_fast32_t tmp_6 = add_implicit_bit(tmp_4);  // add_implicit_bit
    const uint_fast32_t tmp_8 = uq_resize(tmp_6);  // uq_resize
    const uint_fast8_t tmp_9 = uint_fast8_t(tmp_3[1] & 255);  // basic_get_item_1
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_10 = uint_fast8_t(((arg_1 >> 31) & 1) & 1);  // _fp32_sign
    const uint_fast8_t tmp_11 = uint_fast8_t(((arg_1 >> 23) & 255) & 255);  // _fp32_exponent
    const uint_fast32_t tmp_12 = uint_fast32_t(((arg_1 >> 0) & 8388607) & 8388607);  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_13 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_10), static_cast<uint_fast64_t>(tmp_11), static_cast<uint_fast64_t>(tmp_12)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_14 = uint_fast8_t(tmp_13[1] & 255);  // basic_get_item_1
    const uint_fast8_t tmp_21 = uq_max(tmp_9, tmp_14);  // uq_max
    const uint_fast16_t tmp_28 = uq_sub(tmp_21, tmp_9);  // uq_sub
    const uint_fast32_t tmp_30 = uq_rshift(tmp_8, tmp_28);  // uq_rshift
    const uint_fast32_t tmp_40 = uq_to_q(tmp_30);  // uq_to_q
    const uint_fast8_t tmp_41 = uint_fast8_t(tmp_3[0] & 1);  // basic_get_item_0
    const uint_fast32_t tmp_50 = q_add_sign(tmp_40, tmp_41);  // q_add_sign
    const uint_fast32_t tmp_51 = uint_fast32_t(tmp_13[2] & 8388607);  // basic_get_item_2
    const uint_fast32_t tmp_52 = add_implicit_bit(tmp_51);  // add_implicit_bit
    const uint_fast32_t tmp_53 = uq_resize(tmp_52);  // uq_resize
    const uint_fast16_t tmp_54 = uq_sub(tmp_21, tmp_14);  // uq_sub
    const uint_fast32_t tmp_55 = uq_rshift(tmp_53, tmp_54);  // uq_rshift
    const uint_fast32_t tmp_56 = uq_to_q(tmp_55);  // uq_to_q
    const uint_fast8_t tmp_57 = uint_fast8_t(tmp_13[0] & 1);  // basic_get_item_0
    const uint_fast32_t tmp_58 = q_add_sign(tmp_56, tmp_57);  // q_add_sign
    const uint_fast32_t tmp_73 = q_add(tmp_50, tmp_58);  // q_add
    const uint_fast16_t tmp_83 = uq_to_q_1(tmp_21);  // uq_to_q
    const uint_fast32_t tmp_435 = encode_Float32(tmp_73, tmp_83);  // encode_Float32
    return tmp_435;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl((arg_0 & 4294967295), (arg_1 & 4294967295));
}