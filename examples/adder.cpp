#pragma once
#include <array>
#include <cstdint>

static inline uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_5 = uint_fast32_t(((uint_fast8_t(1) << 23) | arg_0));  // basic_concat
    return tmp_5;
}
static inline uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_7 = uint_fast32_t((arg_0 << uint_fast8_t(6)));  // basic_lshift
    return tmp_7;
}
static inline uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_15 = uint_fast8_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_16 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_17 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_15), static_cast<uint_fast64_t>(tmp_16)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_18 = uint_fast8_t(tmp_17[0]);  // basic_get_item_0
    const uint_fast8_t tmp_19 = uint_fast8_t(tmp_17[1]);  // basic_get_item_1
    const uint_fast8_t tmp_20 = uint_fast8_t((tmp_18 > tmp_19 ? tmp_18 : tmp_19));  // basic_max
    return tmp_20;
}
static inline uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_22 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_23 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_24 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_22), static_cast<uint_fast64_t>(tmp_23)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_25 = uint_fast16_t(tmp_24[0]);  // basic_get_item_0
    const uint_fast16_t tmp_26 = uint_fast16_t(tmp_24[1]);  // basic_get_item_1
    const uint_fast16_t tmp_27 = uint_fast16_t((tmp_25 - tmp_26));  // basic_sub
    return tmp_27;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_29 = uint_fast32_t((arg_0 >> arg_1));  // basic_rshift
    return tmp_29;
}
static inline uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_31 = uint_fast8_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_32 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_33 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_31), static_cast<uint_fast64_t>(tmp_32)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_34 = uint_fast8_t(tmp_33[0]);  // basic_get_item_0
    const uint_fast8_t tmp_35 = uint_fast8_t(tmp_33[1]);  // basic_get_item_1
    const uint_fast8_t tmp_36 = uint_fast8_t((tmp_34 + tmp_35));  // basic_add
    return tmp_36;
}
static inline uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_37 = uq_add(uint_fast8_t(1), uint_fast8_t(1));  // uq_add
    const uint_fast32_t tmp_38 = uint_fast32_t(0);  // q_alloc
    const uint_fast32_t tmp_39 = uint_fast32_t(arg_0);  // basic_identity
    return tmp_39;
}
static inline uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_42 = uint_fast8_t((arg_0 == 1073741824));  // _q_is_min_val
    const uint_fast32_t tmp_43 = uint_fast32_t(((~arg_0) & 2147483647));  // basic_invert
    const uint_fast32_t tmp_44 = uint_fast32_t((tmp_43 + uint_fast8_t(1)));  // basic_add
    const uint_fast32_t tmp_45 = uint_fast32_t(((arg_0 ^ arg_0) & 2147483647));  // basic_xor
    const uint_fast32_t tmp_46 = uint_fast32_t(((~tmp_45) & 2147483647));  // basic_invert
    const uint_fast32_t tmp_47 = uint_fast32_t((tmp_42 ? tmp_46 : tmp_44));  // basic_mux_2_1
    return tmp_47;
}
static inline uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_48 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_49 = uint_fast32_t((arg_1 ? tmp_48 : arg_0));  // basic_mux_2_1
    return tmp_49;
}
static inline uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_60 = uint_fast8_t(((arg_0 >> 30) & 1));  // basic_select
    return tmp_60;
}
static inline uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_61 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_62 = uint_fast8_t((tmp_61 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_63 = uint_fast8_t((tmp_62 - tmp_61));  // basic_sub
    const uint_fast32_t tmp_64 = uint_fast32_t(0);  // q_alloc
    const uint_fast32_t tmp_65 = uint_fast32_t(((tmp_63 << 31) | arg_0));  // basic_concat
    return tmp_65;
}
static inline uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast32_t tmp_59 = uint_fast32_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast32_t tmp_66 = q_sign_extend(tmp_59);  // q_sign_extend
    const uint_fast32_t tmp_67 = uint_fast32_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast32_t tmp_68 = q_sign_extend(tmp_67);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_69 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_66), static_cast<uint_fast64_t>(tmp_68)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast32_t tmp_70 = uint_fast32_t(tmp_69[0]);  // basic_get_item_0
    const uint_fast32_t tmp_71 = uint_fast32_t(tmp_69[1]);  // basic_get_item_1
    const uint_fast32_t tmp_72 = uint_fast32_t((tmp_70 + tmp_71));  // basic_add
    return tmp_72;
}
static inline uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_74 = uq_add(uint_fast8_t(8), uint_fast8_t(1));  // uq_add
    const uint_fast16_t tmp_75 = uint_fast16_t(0);  // q_alloc
    const uint_fast16_t tmp_76 = uint_fast16_t(arg_0);  // basic_identity
    return tmp_76;
}
static inline uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_79 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_80 = q_add_sign(arg_0, tmp_79);  // q_add_sign
    return tmp_80;
}
static inline uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_82 = uint_fast32_t(arg_0);  // basic_identity
    return tmp_82;
}
static inline uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_84 = uint_fast8_t(((arg_0 >> 30) & 1));  // basic_select
    const uint_fast8_t tmp_85 = uint_fast8_t(((~tmp_84) & 1));  // basic_invert
    const uint_fast8_t tmp_86 = uint_fast8_t((uint_fast8_t(1) & tmp_85));  // basic_and
    const uint_fast8_t tmp_87 = uint_fast8_t((uint_fast8_t(0) + tmp_86));  // basic_add
    const uint_fast8_t tmp_88 = uint_fast8_t(((arg_0 >> 29) & 1));  // basic_select
    const uint_fast8_t tmp_89 = uint_fast8_t(((~tmp_88) & 1));  // basic_invert
    const uint_fast8_t tmp_90 = uint_fast8_t((tmp_86 & tmp_89));  // basic_and
    const uint_fast8_t tmp_91 = uint_fast8_t((tmp_87 + tmp_90));  // basic_add
    const uint_fast8_t tmp_92 = uint_fast8_t(((arg_0 >> 28) & 1));  // basic_select
    const uint_fast8_t tmp_93 = uint_fast8_t(((~tmp_92) & 1));  // basic_invert
    const uint_fast8_t tmp_94 = uint_fast8_t((tmp_90 & tmp_93));  // basic_and
    const uint_fast8_t tmp_95 = uint_fast8_t((tmp_91 + tmp_94));  // basic_add
    const uint_fast8_t tmp_96 = uint_fast8_t(((arg_0 >> 27) & 1));  // basic_select
    const uint_fast8_t tmp_97 = uint_fast8_t(((~tmp_96) & 1));  // basic_invert
    const uint_fast8_t tmp_98 = uint_fast8_t((tmp_94 & tmp_97));  // basic_and
    const uint_fast8_t tmp_99 = uint_fast8_t((tmp_95 + tmp_98));  // basic_add
    const uint_fast8_t tmp_100 = uint_fast8_t(((arg_0 >> 26) & 1));  // basic_select
    const uint_fast8_t tmp_101 = uint_fast8_t(((~tmp_100) & 1));  // basic_invert
    const uint_fast8_t tmp_102 = uint_fast8_t((tmp_98 & tmp_101));  // basic_and
    const uint_fast8_t tmp_103 = uint_fast8_t((tmp_99 + tmp_102));  // basic_add
    const uint_fast8_t tmp_104 = uint_fast8_t(((arg_0 >> 25) & 1));  // basic_select
    const uint_fast8_t tmp_105 = uint_fast8_t(((~tmp_104) & 1));  // basic_invert
    const uint_fast8_t tmp_106 = uint_fast8_t((tmp_102 & tmp_105));  // basic_and
    const uint_fast8_t tmp_107 = uint_fast8_t((tmp_103 + tmp_106));  // basic_add
    const uint_fast8_t tmp_108 = uint_fast8_t(((arg_0 >> 24) & 1));  // basic_select
    const uint_fast8_t tmp_109 = uint_fast8_t(((~tmp_108) & 1));  // basic_invert
    const uint_fast8_t tmp_110 = uint_fast8_t((tmp_106 & tmp_109));  // basic_and
    const uint_fast8_t tmp_111 = uint_fast8_t((tmp_107 + tmp_110));  // basic_add
    const uint_fast8_t tmp_112 = uint_fast8_t(((arg_0 >> 23) & 1));  // basic_select
    const uint_fast8_t tmp_113 = uint_fast8_t(((~tmp_112) & 1));  // basic_invert
    const uint_fast8_t tmp_114 = uint_fast8_t((tmp_110 & tmp_113));  // basic_and
    const uint_fast8_t tmp_115 = uint_fast8_t((tmp_111 + tmp_114));  // basic_add
    const uint_fast8_t tmp_116 = uint_fast8_t(((arg_0 >> 22) & 1));  // basic_select
    const uint_fast8_t tmp_117 = uint_fast8_t(((~tmp_116) & 1));  // basic_invert
    const uint_fast8_t tmp_118 = uint_fast8_t((tmp_114 & tmp_117));  // basic_and
    const uint_fast8_t tmp_119 = uint_fast8_t((tmp_115 + tmp_118));  // basic_add
    const uint_fast8_t tmp_120 = uint_fast8_t(((arg_0 >> 21) & 1));  // basic_select
    const uint_fast8_t tmp_121 = uint_fast8_t(((~tmp_120) & 1));  // basic_invert
    const uint_fast8_t tmp_122 = uint_fast8_t((tmp_118 & tmp_121));  // basic_and
    const uint_fast8_t tmp_123 = uint_fast8_t((tmp_119 + tmp_122));  // basic_add
    const uint_fast8_t tmp_124 = uint_fast8_t(((arg_0 >> 20) & 1));  // basic_select
    const uint_fast8_t tmp_125 = uint_fast8_t(((~tmp_124) & 1));  // basic_invert
    const uint_fast8_t tmp_126 = uint_fast8_t((tmp_122 & tmp_125));  // basic_and
    const uint_fast8_t tmp_127 = uint_fast8_t((tmp_123 + tmp_126));  // basic_add
    const uint_fast8_t tmp_128 = uint_fast8_t(((arg_0 >> 19) & 1));  // basic_select
    const uint_fast8_t tmp_129 = uint_fast8_t(((~tmp_128) & 1));  // basic_invert
    const uint_fast8_t tmp_130 = uint_fast8_t((tmp_126 & tmp_129));  // basic_and
    const uint_fast8_t tmp_131 = uint_fast8_t((tmp_127 + tmp_130));  // basic_add
    const uint_fast8_t tmp_132 = uint_fast8_t(((arg_0 >> 18) & 1));  // basic_select
    const uint_fast8_t tmp_133 = uint_fast8_t(((~tmp_132) & 1));  // basic_invert
    const uint_fast8_t tmp_134 = uint_fast8_t((tmp_130 & tmp_133));  // basic_and
    const uint_fast8_t tmp_135 = uint_fast8_t((tmp_131 + tmp_134));  // basic_add
    const uint_fast8_t tmp_136 = uint_fast8_t(((arg_0 >> 17) & 1));  // basic_select
    const uint_fast8_t tmp_137 = uint_fast8_t(((~tmp_136) & 1));  // basic_invert
    const uint_fast8_t tmp_138 = uint_fast8_t((tmp_134 & tmp_137));  // basic_and
    const uint_fast8_t tmp_139 = uint_fast8_t((tmp_135 + tmp_138));  // basic_add
    const uint_fast8_t tmp_140 = uint_fast8_t(((arg_0 >> 16) & 1));  // basic_select
    const uint_fast8_t tmp_141 = uint_fast8_t(((~tmp_140) & 1));  // basic_invert
    const uint_fast8_t tmp_142 = uint_fast8_t((tmp_138 & tmp_141));  // basic_and
    const uint_fast8_t tmp_143 = uint_fast8_t((tmp_139 + tmp_142));  // basic_add
    const uint_fast8_t tmp_144 = uint_fast8_t(((arg_0 >> 15) & 1));  // basic_select
    const uint_fast8_t tmp_145 = uint_fast8_t(((~tmp_144) & 1));  // basic_invert
    const uint_fast8_t tmp_146 = uint_fast8_t((tmp_142 & tmp_145));  // basic_and
    const uint_fast8_t tmp_147 = uint_fast8_t((tmp_143 + tmp_146));  // basic_add
    const uint_fast8_t tmp_148 = uint_fast8_t(((arg_0 >> 14) & 1));  // basic_select
    const uint_fast8_t tmp_149 = uint_fast8_t(((~tmp_148) & 1));  // basic_invert
    const uint_fast8_t tmp_150 = uint_fast8_t((tmp_146 & tmp_149));  // basic_and
    const uint_fast8_t tmp_151 = uint_fast8_t((tmp_147 + tmp_150));  // basic_add
    const uint_fast8_t tmp_152 = uint_fast8_t(((arg_0 >> 13) & 1));  // basic_select
    const uint_fast8_t tmp_153 = uint_fast8_t(((~tmp_152) & 1));  // basic_invert
    const uint_fast8_t tmp_154 = uint_fast8_t((tmp_150 & tmp_153));  // basic_and
    const uint_fast8_t tmp_155 = uint_fast8_t((tmp_151 + tmp_154));  // basic_add
    const uint_fast8_t tmp_156 = uint_fast8_t(((arg_0 >> 12) & 1));  // basic_select
    const uint_fast8_t tmp_157 = uint_fast8_t(((~tmp_156) & 1));  // basic_invert
    const uint_fast8_t tmp_158 = uint_fast8_t((tmp_154 & tmp_157));  // basic_and
    const uint_fast8_t tmp_159 = uint_fast8_t((tmp_155 + tmp_158));  // basic_add
    const uint_fast8_t tmp_160 = uint_fast8_t(((arg_0 >> 11) & 1));  // basic_select
    const uint_fast8_t tmp_161 = uint_fast8_t(((~tmp_160) & 1));  // basic_invert
    const uint_fast8_t tmp_162 = uint_fast8_t((tmp_158 & tmp_161));  // basic_and
    const uint_fast8_t tmp_163 = uint_fast8_t((tmp_159 + tmp_162));  // basic_add
    const uint_fast8_t tmp_164 = uint_fast8_t(((arg_0 >> 10) & 1));  // basic_select
    const uint_fast8_t tmp_165 = uint_fast8_t(((~tmp_164) & 1));  // basic_invert
    const uint_fast8_t tmp_166 = uint_fast8_t((tmp_162 & tmp_165));  // basic_and
    const uint_fast8_t tmp_167 = uint_fast8_t((tmp_163 + tmp_166));  // basic_add
    const uint_fast8_t tmp_168 = uint_fast8_t(((arg_0 >> 9) & 1));  // basic_select
    const uint_fast8_t tmp_169 = uint_fast8_t(((~tmp_168) & 1));  // basic_invert
    const uint_fast8_t tmp_170 = uint_fast8_t((tmp_166 & tmp_169));  // basic_and
    const uint_fast8_t tmp_171 = uint_fast8_t((tmp_167 + tmp_170));  // basic_add
    const uint_fast8_t tmp_172 = uint_fast8_t(((arg_0 >> 8) & 1));  // basic_select
    const uint_fast8_t tmp_173 = uint_fast8_t(((~tmp_172) & 1));  // basic_invert
    const uint_fast8_t tmp_174 = uint_fast8_t((tmp_170 & tmp_173));  // basic_and
    const uint_fast8_t tmp_175 = uint_fast8_t((tmp_171 + tmp_174));  // basic_add
    const uint_fast8_t tmp_176 = uint_fast8_t(((arg_0 >> 7) & 1));  // basic_select
    const uint_fast8_t tmp_177 = uint_fast8_t(((~tmp_176) & 1));  // basic_invert
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_174 & tmp_177));  // basic_and
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_175 + tmp_178));  // basic_add
    const uint_fast8_t tmp_180 = uint_fast8_t(((arg_0 >> 6) & 1));  // basic_select
    const uint_fast8_t tmp_181 = uint_fast8_t(((~tmp_180) & 1));  // basic_invert
    const uint_fast8_t tmp_182 = uint_fast8_t((tmp_178 & tmp_181));  // basic_and
    const uint_fast8_t tmp_183 = uint_fast8_t((tmp_179 + tmp_182));  // basic_add
    const uint_fast8_t tmp_184 = uint_fast8_t(((arg_0 >> 5) & 1));  // basic_select
    const uint_fast8_t tmp_185 = uint_fast8_t(((~tmp_184) & 1));  // basic_invert
    const uint_fast8_t tmp_186 = uint_fast8_t((tmp_182 & tmp_185));  // basic_and
    const uint_fast8_t tmp_187 = uint_fast8_t((tmp_183 + tmp_186));  // basic_add
    const uint_fast8_t tmp_188 = uint_fast8_t(((arg_0 >> 4) & 1));  // basic_select
    const uint_fast8_t tmp_189 = uint_fast8_t(((~tmp_188) & 1));  // basic_invert
    const uint_fast8_t tmp_190 = uint_fast8_t((tmp_186 & tmp_189));  // basic_and
    const uint_fast8_t tmp_191 = uint_fast8_t((tmp_187 + tmp_190));  // basic_add
    const uint_fast8_t tmp_192 = uint_fast8_t(((arg_0 >> 3) & 1));  // basic_select
    const uint_fast8_t tmp_193 = uint_fast8_t(((~tmp_192) & 1));  // basic_invert
    const uint_fast8_t tmp_194 = uint_fast8_t((tmp_190 & tmp_193));  // basic_and
    const uint_fast8_t tmp_195 = uint_fast8_t((tmp_191 + tmp_194));  // basic_add
    const uint_fast8_t tmp_196 = uint_fast8_t(((arg_0 >> 2) & 1));  // basic_select
    const uint_fast8_t tmp_197 = uint_fast8_t(((~tmp_196) & 1));  // basic_invert
    const uint_fast8_t tmp_198 = uint_fast8_t((tmp_194 & tmp_197));  // basic_and
    const uint_fast8_t tmp_199 = uint_fast8_t((tmp_195 + tmp_198));  // basic_add
    const uint_fast8_t tmp_200 = uint_fast8_t(((arg_0 >> 1) & 1));  // basic_select
    const uint_fast8_t tmp_201 = uint_fast8_t(((~tmp_200) & 1));  // basic_invert
    const uint_fast8_t tmp_202 = uint_fast8_t((tmp_198 & tmp_201));  // basic_and
    const uint_fast8_t tmp_203 = uint_fast8_t((tmp_199 + tmp_202));  // basic_add
    const uint_fast8_t tmp_204 = uint_fast8_t(((arg_0 >> 0) & 1));  // basic_select
    const uint_fast8_t tmp_205 = uint_fast8_t(((~tmp_204) & 1));  // basic_invert
    const uint_fast8_t tmp_206 = uint_fast8_t((tmp_202 & tmp_205));  // basic_and
    const uint_fast8_t tmp_207 = uint_fast8_t((tmp_203 + tmp_206));  // basic_add
    return tmp_207;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_209 = uq_add(uint_fast8_t(5), uint_fast8_t(1));  // uq_add
    const uint_fast8_t tmp_210 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_211 = uint_fast8_t(arg_0);  // basic_identity
    return tmp_211;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_215 = uint_fast8_t(((arg_0 >> 5) & 1));  // basic_select
    return tmp_215;
}
static inline uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_216 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_217 = uint_fast8_t((tmp_216 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_218 = uint_fast8_t((tmp_217 - tmp_216));  // basic_sub
    const uint_fast8_t tmp_219 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_220 = uint_fast8_t(((tmp_218 << 6) | arg_0));  // basic_concat
    return tmp_220;
}
static inline uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_223 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_224 = uint_fast8_t((tmp_223 << uint_fast8_t(4)));  // basic_lshift
    const uint_fast8_t tmp_225 = uint_fast8_t((tmp_224 - tmp_223));  // basic_sub
    const uint_fast8_t tmp_226 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_227 = uint_fast8_t(((tmp_225 << 3) | arg_0));  // basic_concat
    return tmp_227;
}
static inline uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_214 = uint_fast8_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_221 = q_sign_extend_1(tmp_214);  // q_sign_extend
    const uint_fast8_t tmp_222 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_228 = q_sign_extend_2(tmp_222);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_229 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_221), static_cast<uint_fast64_t>(tmp_228)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_230 = uint_fast8_t(tmp_229[0]);  // basic_get_item_0
    const uint_fast8_t tmp_231 = uint_fast8_t(tmp_229[1]);  // basic_get_item_1
    const uint_fast8_t tmp_232 = uint_fast8_t((tmp_230 - tmp_231));  // basic_sub
    return tmp_232;
}
static inline uint_fast8_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_235 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_236 = uint_fast8_t((tmp_235 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_237 = uint_fast8_t((tmp_236 - tmp_235));  // basic_sub
    const uint_fast8_t tmp_238 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_239 = uint_fast8_t(((tmp_237 << 7) | arg_0));  // basic_concat
    return tmp_239;
}
static inline uint_fast8_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_242 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_243 = uint_fast8_t((tmp_242 << uint_fast8_t(6)));  // basic_lshift
    const uint_fast8_t tmp_244 = uint_fast8_t((tmp_243 - tmp_242));  // basic_sub
    const uint_fast8_t tmp_245 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_246 = uint_fast8_t(((tmp_244 << 2) | arg_0));  // basic_concat
    return tmp_246;
}
static inline uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_234 = uint_fast8_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_240 = q_sign_extend_3(tmp_234);  // q_sign_extend
    const uint_fast8_t tmp_241 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_247 = q_sign_extend_4(tmp_241);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_248 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_240), static_cast<uint_fast64_t>(tmp_247)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_249 = uint_fast8_t(tmp_248[0]);  // basic_get_item_0
    const uint_fast8_t tmp_250 = uint_fast8_t(tmp_248[1]);  // basic_get_item_1
    const uint_fast8_t tmp_251 = uint_fast8_t((tmp_249 + tmp_250));  // basic_add
    return tmp_251;
}
static inline uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_254 = uint_fast32_t((arg_0 << uint_fast8_t(1)));  // basic_lshift
    return tmp_254;
}
static inline uint_fast8_t q_neg_1(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_257 = uint_fast8_t((arg_0 == 128));  // _q_is_min_val
    const uint_fast8_t tmp_258 = uint_fast8_t(((~arg_0) & 255));  // basic_invert
    const uint_fast8_t tmp_259 = uint_fast8_t((tmp_258 + uint_fast8_t(1)));  // basic_add
    const uint_fast8_t tmp_260 = uint_fast8_t(((arg_0 ^ arg_0) & 255));  // basic_xor
    const uint_fast8_t tmp_261 = uint_fast8_t(((~tmp_260) & 255));  // basic_invert
    const uint_fast8_t tmp_262 = uint_fast8_t((tmp_257 ? tmp_261 : tmp_259));  // basic_mux_2_1
    return tmp_262;
}
static inline uint_fast8_t q_add_sign_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_263 = q_neg_1(arg_0);  // q_neg
    const uint_fast8_t tmp_264 = uint_fast8_t((arg_1 ? tmp_263 : arg_0));  // basic_mux_2_1
    return tmp_264;
}
static inline uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_256 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_265 = q_add_sign_1(arg_0, tmp_256);  // q_add_sign
    return tmp_265;
}
static inline uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_267 = uint_fast8_t(arg_0);  // basic_identity
    return tmp_267;
}
static inline uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_269 = uint_fast32_t((arg_0 << arg_1));  // basic_lshift
    return tmp_269;
}
static inline uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_271 = uint_fast32_t((arg_0 >> arg_1));  // basic_rshift
    return tmp_271;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_275 = uint_fast8_t(((arg_0 >> 8) & 1));  // basic_select
    return tmp_275;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_276 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_277 = uint_fast8_t((tmp_276 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_278 = uint_fast8_t((tmp_277 - tmp_276));  // basic_sub
    const uint_fast16_t tmp_279 = uint_fast16_t(0);  // q_alloc
    const uint_fast16_t tmp_280 = uint_fast16_t(((tmp_278 << 9) | arg_0));  // basic_concat
    return tmp_280;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_283 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_284 = uint_fast8_t((tmp_283 << uint_fast8_t(2)));  // basic_lshift
    const uint_fast8_t tmp_285 = uint_fast8_t((tmp_284 - tmp_283));  // basic_sub
    const uint_fast16_t tmp_286 = uint_fast16_t(0);  // q_alloc
    const uint_fast16_t tmp_287 = uint_fast16_t(((tmp_285 << 8) | arg_0));  // basic_concat
    return tmp_287;
}
static inline uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_274 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_281 = q_sign_extend_5(tmp_274);  // q_sign_extend
    const uint_fast8_t tmp_282 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_288 = q_sign_extend_6(tmp_282);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_289 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_281), static_cast<uint_fast64_t>(tmp_288)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_290 = uint_fast16_t(tmp_289[0]);  // basic_get_item_0
    const uint_fast16_t tmp_291 = uint_fast16_t(tmp_289[1]);  // basic_get_item_1
    const uint_fast16_t tmp_292 = uint_fast16_t((tmp_290 - tmp_291));  // basic_sub
    return tmp_292;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_294 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_295 = q_sign_extend_5(tmp_294);  // q_sign_extend
    const uint_fast8_t tmp_296 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_297 = q_sign_extend_6(tmp_296);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_298 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_295), static_cast<uint_fast64_t>(tmp_297)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_299 = uint_fast16_t(tmp_298[0]);  // basic_get_item_0
    const uint_fast16_t tmp_300 = uint_fast16_t(tmp_298[1]);  // basic_get_item_1
    const uint_fast16_t tmp_301 = uint_fast16_t((tmp_299 + tmp_300));  // basic_add
    return tmp_301;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_308 = uint_fast8_t((arg_0 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_309 = uint_fast8_t(((~tmp_308) & 1));  // basic_invert
    return tmp_309;
}
static inline uint_fast16_t q_neg_2(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_314 = uint_fast8_t((arg_0 == 512));  // _q_is_min_val
    const uint_fast16_t tmp_315 = uint_fast16_t(((~arg_0) & 1023));  // basic_invert
    const uint_fast16_t tmp_316 = uint_fast16_t((tmp_315 + uint_fast8_t(1)));  // basic_add
    const uint_fast16_t tmp_317 = uint_fast16_t(((arg_0 ^ arg_0) & 1023));  // basic_xor
    const uint_fast16_t tmp_318 = uint_fast16_t(((~tmp_317) & 1023));  // basic_invert
    const uint_fast16_t tmp_319 = uint_fast16_t((tmp_314 ? tmp_318 : tmp_316));  // basic_mux_2_1
    return tmp_319;
}
static inline uint_fast16_t q_add_sign_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_320 = q_neg_2(arg_0);  // q_neg
    const uint_fast16_t tmp_321 = uint_fast16_t((arg_1 ? tmp_320 : arg_0));  // basic_mux_2_1
    return tmp_321;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_313 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_322 = q_add_sign_2(arg_0, tmp_313);  // q_add_sign
    return tmp_322;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_324 = uint_fast16_t(arg_0);  // basic_identity
    return tmp_324;
}
static inline uint_fast16_t uq_add_1(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_326 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_327 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_328 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_326), static_cast<uint_fast64_t>(tmp_327)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_329 = uint_fast16_t(tmp_328[0]);  // basic_get_item_0
    const uint_fast16_t tmp_330 = uint_fast16_t(tmp_328[1]);  // basic_get_item_1
    const uint_fast16_t tmp_331 = uint_fast16_t((tmp_329 + tmp_330));  // basic_add
    return tmp_331;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_334 = uint_fast64_t((arg_0 >> arg_1));  // basic_rshift
    return tmp_334;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_339 = uint_fast64_t(((arg_0 >> 0) & 1099511627775));  // basic_select
    return tmp_339;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_342 = uint_fast8_t((arg_0 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_343 = uint_fast8_t(((~tmp_342) & 1));  // basic_invert
    return tmp_343;
}
static inline uint_fast32_t uq_resize_2(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_345 = uint_fast32_t((arg_0 >> uint_fast8_t(17)));  // basic_rshift
    return tmp_345;
}
static inline uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_347 = uint_fast8_t(((arg_0 >> 16) & 1));  // basic_select
    const uint_fast8_t tmp_348 = uint_fast8_t(((arg_0 >> 15) & 1));  // basic_select
    const uint_fast16_t tmp_349 = uint_fast16_t(((arg_0 >> 0) & 32767));  // basic_select
    const uint_fast8_t tmp_350 = uint_fast8_t((tmp_349 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_351 = uint_fast8_t((tmp_348 | tmp_350));  // basic_or
    const uint_fast8_t tmp_352 = uint_fast8_t(((arg_0 >> 17) & 1));  // basic_select
    const uint_fast8_t tmp_353 = uint_fast8_t((tmp_351 | tmp_352));  // basic_or
    const uint_fast8_t tmp_354 = uint_fast8_t((tmp_347 & tmp_353));  // basic_and
    const uint_fast32_t tmp_355 = uint_fast32_t(tmp_354);  // basic_identity
    return tmp_355;
}
static inline uint_fast32_t uq_add_2(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_357 = uint_fast32_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast32_t tmp_358 = uint_fast32_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_359 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_357), static_cast<uint_fast64_t>(tmp_358)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_360 = uint_fast32_t(tmp_359[0]);  // basic_get_item_0
    const uint_fast32_t tmp_361 = uint_fast32_t(tmp_359[1]);  // basic_get_item_1
    const uint_fast32_t tmp_362 = uint_fast32_t((tmp_360 + tmp_361));  // basic_add
    return tmp_362;
}
static inline uint_fast16_t uq_add_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_365 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_366 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_367 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_365), static_cast<uint_fast64_t>(tmp_366)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_368 = uint_fast16_t(tmp_367[0]);  // basic_get_item_0
    const uint_fast16_t tmp_369 = uint_fast16_t(tmp_367[1]);  // basic_get_item_1
    const uint_fast16_t tmp_370 = uint_fast16_t((tmp_368 + tmp_369));  // basic_add
    return tmp_370;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_380 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_381 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_382 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_380), static_cast<uint_fast64_t>(tmp_381)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_383 = uint_fast16_t(tmp_382[0]);  // basic_get_item_0
    const uint_fast16_t tmp_384 = uint_fast16_t(tmp_382[1]);  // basic_get_item_1
    const uint_fast16_t tmp_385 = uint_fast16_t((tmp_383 < tmp_384 ? tmp_383 : tmp_384));  // basic_min
    return tmp_385;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_391 = uint_fast8_t((arg_0 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_392 = uint_fast8_t(((~tmp_391) & 1));  // basic_invert
    return tmp_392;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_398 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2));  // float32_alloc
    return tmp_398;
}
static inline uint_fast32_t encode_Float32(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // encode_Float32
    const uint_fast8_t tmp_78 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_81 = q_abs(arg_0);  // q_abs
    const uint_fast32_t tmp_83 = q_to_uq(tmp_81);  // q_to_uq
    // begin inline primitive fp32_normalize
    const uint_fast8_t tmp_208 = lzc(tmp_83);  // lzc
    const uint_fast8_t tmp_212 = uq_to_q_2(tmp_208);  // uq_to_q
    const uint_fast8_t tmp_213 = uq_to_q_2(uint_fast8_t(2));  // uq_to_q
    const uint_fast8_t tmp_233 = q_sub(tmp_212, tmp_213);  // q_sub
    const uint_fast8_t tmp_252 = q_add_1(tmp_233, uint_fast8_t(1));  // q_add
    const uint_fast8_t tmp_253 = q_sign_bit_1(tmp_252);  // q_sign_bit
    const uint_fast32_t tmp_255 = uq_resize_1(tmp_83);  // uq_resize
    const uint_fast8_t tmp_266 = q_abs_1(tmp_252);  // q_abs
    const uint_fast8_t tmp_268 = q_to_uq_1(tmp_266);  // q_to_uq
    const uint_fast32_t tmp_270 = uq_lshift(tmp_255, tmp_268);  // uq_lshift
    const uint_fast32_t tmp_272 = uq_rshift_1(tmp_255, tmp_268);  // uq_rshift
    const uint_fast32_t tmp_273 = uint_fast32_t((tmp_253 ? tmp_272 : tmp_270));  // basic_mux_2_1
    const uint_fast16_t tmp_293 = q_sub_1(arg_1, tmp_266);  // q_sub
    const uint_fast16_t tmp_302 = q_add_2(arg_1, tmp_266);  // q_add
    const uint_fast16_t tmp_303 = uint_fast16_t((tmp_253 ? tmp_302 : tmp_293));  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_304 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_273), static_cast<uint_fast64_t>(tmp_303)};  // basic_tuple_maker_2
    // end inline primitive fp32_normalize
    const uint_fast32_t tmp_305 = uint_fast32_t(tmp_304[0]);  // basic_get_item_0
    const uint_fast16_t tmp_306 = uint_fast16_t(tmp_304[1]);  // basic_get_item_1
    // begin inline primitive fp32_classify
    const uint_fast64_t tmp_307 = uint_fast64_t((tmp_305 << uint_fast8_t(10)));  // basic_lshift
    const uint_fast8_t tmp_310 = q_is_zero(tmp_306);  // q_is_zero
    const uint_fast8_t tmp_311 = q_sign_bit_2(tmp_306);  // q_sign_bit
    const uint_fast8_t tmp_312 = uint_fast8_t((tmp_310 | tmp_311));  // basic_or
    const uint_fast16_t tmp_323 = q_abs_2(tmp_306);  // q_abs
    const uint_fast16_t tmp_325 = q_to_uq_2(tmp_323);  // q_to_uq
    const uint_fast16_t tmp_332 = uq_add_1(uint_fast8_t(1), tmp_325);  // uq_add
    const uint_fast16_t tmp_333 = uint_fast16_t((tmp_312 ? tmp_332 : uint_fast8_t(0)));  // basic_mux_2_1
    const uint_fast64_t tmp_335 = uq_rshift_2(tmp_307, tmp_333);  // uq_rshift
    const uint_fast16_t tmp_336 = uint_fast16_t((tmp_312 ? uint_fast8_t(0) : tmp_325));  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_337 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_335), static_cast<uint_fast64_t>(tmp_336)};  // basic_tuple_maker_2
    // end inline primitive fp32_classify
    const uint_fast64_t tmp_338 = uint_fast64_t(tmp_337[0]);  // basic_get_item_0
    const uint_fast64_t tmp_340 = drop_implicit_bit(tmp_338);  // drop_implicit_bit
    const uint_fast16_t tmp_341 = uint_fast16_t(tmp_337[1]);  // basic_get_item_1
    // begin inline primitive fp32_round
    const uint_fast8_t tmp_344 = uq_is_zero(tmp_341);  // uq_is_zero
    const uint_fast32_t tmp_346 = uq_resize_2(tmp_340);  // uq_resize
    const uint_fast32_t tmp_356 = uq_RNE_IEEE(tmp_340);  // uq_RNE_IEEE
    const uint_fast32_t tmp_363 = uq_add_2(tmp_346, tmp_356);  // uq_add
    const uint_fast8_t tmp_364 = uint_fast8_t(((tmp_363 >> 23) & 1));  // basic_select
    const uint_fast16_t tmp_371 = uq_add_3(tmp_341, tmp_364);  // uq_add
    const uint_fast8_t tmp_372 = uint_fast8_t((tmp_371 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_373 = uint_fast8_t((tmp_344 & tmp_372));  // basic_and
    const uint_fast32_t tmp_374 = uint_fast32_t((tmp_363 >> uint_fast8_t(1)));  // basic_rshift
    const uint_fast32_t tmp_375 = uint_fast32_t((tmp_364 ? tmp_374 : tmp_363));  // basic_mux_2_1
    const uint_fast32_t tmp_376 = uint_fast32_t((tmp_373 ? uint_fast8_t(0) : tmp_375));  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_377 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_376), static_cast<uint_fast64_t>(tmp_371)};  // basic_tuple_maker_2
    // end inline primitive fp32_round
    const uint_fast32_t tmp_378 = uint_fast32_t(tmp_377[0]);  // basic_get_item_0
    const uint_fast16_t tmp_379 = uint_fast16_t(tmp_377[1]);  // basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_386 = uq_min(tmp_379, uint_fast8_t(255));  // uq_min
    const uint_fast8_t tmp_387 = uint_fast8_t(tmp_386);  // basic_identity
    const uint_fast8_t tmp_388 = uint_fast8_t((tmp_387 == 255));  // basic_and_reduce
    const uint_fast32_t tmp_389 = uint_fast32_t((tmp_388 ? uint_fast8_t(0) : tmp_378));  // basic_mux_2_1
    const uint_fast32_t tmp_390 = uint_fast32_t(tmp_389);  // basic_identity
    const uint_fast8_t tmp_393 = uq_is_zero_1(tmp_83);  // uq_is_zero
    const uint_fast8_t tmp_394 = uint_fast8_t((tmp_393 ? uint_fast8_t(0) : tmp_387));  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_395 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_390), static_cast<uint_fast64_t>(tmp_394)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_396 = uint_fast8_t(tmp_395[1]);  // basic_get_item_1
    const uint_fast32_t tmp_397 = uint_fast32_t(tmp_395[0]);  // basic_get_item_0
    const uint_fast32_t tmp_399 = fp32_pack(tmp_78, tmp_396, tmp_397);  // fp32_pack
    return tmp_399;
}
static inline uint_fast32_t FP32_IEEE_adder_impl(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // FP32_IEEE_adder
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp = uint_fast8_t(((arg_0 >> 31) & 1));  // _fp32_sign
    const uint_fast8_t tmp_1 = uint_fast8_t(((arg_0 >> 23) & 255));  // _fp32_exponent
    const uint_fast32_t tmp_2 = uint_fast32_t(((arg_0 >> 0) & 8388607));  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_3 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp), static_cast<uint_fast64_t>(tmp_1), static_cast<uint_fast64_t>(tmp_2)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast32_t tmp_4 = uint_fast32_t(tmp_3[2]);  // basic_get_item_2
    const uint_fast32_t tmp_6 = add_implicit_bit(tmp_4);  // add_implicit_bit
    const uint_fast32_t tmp_8 = uq_resize(tmp_6);  // uq_resize
    const uint_fast8_t tmp_9 = uint_fast8_t(tmp_3[1]);  // basic_get_item_1
    // begin inline primitive fp32_unpack
    const uint_fast8_t tmp_10 = uint_fast8_t(((arg_1 >> 31) & 1));  // _fp32_sign
    const uint_fast8_t tmp_11 = uint_fast8_t(((arg_1 >> 23) & 255));  // _fp32_exponent
    const uint_fast32_t tmp_12 = uint_fast32_t(((arg_1 >> 0) & 8388607));  // _fp32_mantissa
    const std::array<uint_fast64_t, 3> tmp_13 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_10), static_cast<uint_fast64_t>(tmp_11), static_cast<uint_fast64_t>(tmp_12)};  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const uint_fast8_t tmp_14 = uint_fast8_t(tmp_13[1]);  // basic_get_item_1
    const uint_fast8_t tmp_21 = uq_max(tmp_9, tmp_14);  // uq_max
    const uint_fast16_t tmp_28 = uq_sub(tmp_21, tmp_9);  // uq_sub
    const uint_fast32_t tmp_30 = uq_rshift(tmp_8, tmp_28);  // uq_rshift
    const uint_fast32_t tmp_40 = uq_to_q(tmp_30);  // uq_to_q
    const uint_fast8_t tmp_41 = uint_fast8_t(tmp_3[0]);  // basic_get_item_0
    const uint_fast32_t tmp_50 = q_add_sign(tmp_40, tmp_41);  // q_add_sign
    const uint_fast32_t tmp_51 = uint_fast32_t(tmp_13[2]);  // basic_get_item_2
    const uint_fast32_t tmp_52 = add_implicit_bit(tmp_51);  // add_implicit_bit
    const uint_fast32_t tmp_53 = uq_resize(tmp_52);  // uq_resize
    const uint_fast16_t tmp_54 = uq_sub(tmp_21, tmp_14);  // uq_sub
    const uint_fast32_t tmp_55 = uq_rshift(tmp_53, tmp_54);  // uq_rshift
    const uint_fast32_t tmp_56 = uq_to_q(tmp_55);  // uq_to_q
    const uint_fast8_t tmp_57 = uint_fast8_t(tmp_13[0]);  // basic_get_item_0
    const uint_fast32_t tmp_58 = q_add_sign(tmp_56, tmp_57);  // q_add_sign
    const uint_fast32_t tmp_73 = q_add(tmp_50, tmp_58);  // q_add
    const uint_fast16_t tmp_77 = uq_to_q_1(tmp_21);  // uq_to_q
    const uint_fast32_t tmp_400 = encode_Float32(tmp_73, tmp_77);  // encode_Float32
    return tmp_400;
}
extern "C" inline uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {
    return FP32_IEEE_adder_impl(arg_0, arg_1);
}