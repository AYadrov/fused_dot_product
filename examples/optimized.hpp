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
    const uint_fast32_t tmp_19 = uint_fast32_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(3 & 3))) & 524287);  // basic_lshift
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
static inline uint_fast8_t est_local_shift(uint_fast8_t arg_0) {  // _est_local_shift
    const uint_fast8_t tmp_34 = uint_fast8_t(((~arg_0) & 3) & 3);  // basic_invert
    return tmp_34;
}
static inline uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_36 = uint_fast32_t((arg_1 >= 19 ? 0 : (arg_0 >> arg_1)) & 524287);  // basic_rshift
    return tmp_36;
}
static inline uint_fast64_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast64_t tmp_38 = uint_fast64_t((uint_fast8_t(14 & 15) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(14 & 15))) & 8589934591);  // basic_lshift
    return tmp_38;
}
static inline uint_fast8_t OPTIMIZED_MAX_EXP4(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast8_t arg_2, uint_fast8_t arg_3) {  // OPTIMIZED_MAX_EXP4
    const uint_fast8_t tmp_86 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_87 = uint_fast8_t(((~uint_fast8_t(0 & 1)) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_88 = uint_fast8_t((uint_fast8_t(0 & 1) & tmp_87) & 1);  // basic_and
    const uint_fast8_t tmp_89 = uint_fast8_t((tmp_88 | uint_fast8_t(0 & 1)) & 1);  // basic_or
    const uint_fast8_t tmp_90 = uint_fast8_t(((~tmp_89) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_91 = uint_fast8_t((tmp_86 & tmp_90) & 1);  // basic_and
    const uint_fast8_t tmp_92 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_91) & 3);  // basic_concat
    const uint_fast8_t tmp_93 = uint_fast8_t(((arg_1 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_94 = uint_fast8_t(((~uint_fast8_t(0 & 1)) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_95 = uint_fast8_t((uint_fast8_t(0 & 1) & tmp_94) & 1);  // basic_and
    const uint_fast8_t tmp_96 = uint_fast8_t((tmp_95 | uint_fast8_t(0 & 1)) & 1);  // basic_or
    const uint_fast8_t tmp_97 = uint_fast8_t(((~tmp_96) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_98 = uint_fast8_t((tmp_93 & tmp_97) & 1);  // basic_and
    const uint_fast8_t tmp_99 = uint_fast8_t(((uint_fast64_t(tmp_92) << 1) | tmp_98) & 7);  // basic_concat
    const uint_fast8_t tmp_100 = uint_fast8_t(((arg_2 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_101 = uint_fast8_t(((~uint_fast8_t(0 & 1)) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_102 = uint_fast8_t((uint_fast8_t(0 & 1) & tmp_101) & 1);  // basic_and
    const uint_fast8_t tmp_103 = uint_fast8_t((tmp_102 | uint_fast8_t(0 & 1)) & 1);  // basic_or
    const uint_fast8_t tmp_104 = uint_fast8_t(((~tmp_103) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_105 = uint_fast8_t((tmp_100 & tmp_104) & 1);  // basic_and
    const uint_fast8_t tmp_106 = uint_fast8_t(((uint_fast64_t(tmp_99) << 1) | tmp_105) & 15);  // basic_concat
    const uint_fast8_t tmp_107 = uint_fast8_t(((arg_3 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_108 = uint_fast8_t(((~uint_fast8_t(0 & 1)) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_109 = uint_fast8_t((uint_fast8_t(0 & 1) & tmp_108) & 1);  // basic_and
    const uint_fast8_t tmp_110 = uint_fast8_t((tmp_109 | uint_fast8_t(0 & 1)) & 1);  // basic_or
    const uint_fast8_t tmp_111 = uint_fast8_t(((~tmp_110) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_112 = uint_fast8_t((tmp_107 & tmp_111) & 1);  // basic_and
    const uint_fast8_t tmp_113 = uint_fast8_t(((uint_fast64_t(tmp_106) << 1) | tmp_112) & 31);  // basic_concat
    const uint_fast8_t tmp_114 = uint_fast8_t((tmp_113 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_115 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_116 = uint_fast8_t(((~tmp_86) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_117 = uint_fast8_t((tmp_114 & tmp_116) & 1);  // basic_and
    const uint_fast8_t tmp_118 = uint_fast8_t((tmp_117 | tmp_89) & 1);  // basic_or
    const uint_fast8_t tmp_119 = uint_fast8_t(((~tmp_118) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_120 = uint_fast8_t((tmp_115 & tmp_119) & 1);  // basic_and
    const uint_fast8_t tmp_121 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_120) & 3);  // basic_concat
    const uint_fast8_t tmp_122 = uint_fast8_t(((arg_1 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_123 = uint_fast8_t(((~tmp_93) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_124 = uint_fast8_t((tmp_114 & tmp_123) & 1);  // basic_and
    const uint_fast8_t tmp_125 = uint_fast8_t((tmp_124 | tmp_96) & 1);  // basic_or
    const uint_fast8_t tmp_126 = uint_fast8_t(((~tmp_125) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_127 = uint_fast8_t((tmp_122 & tmp_126) & 1);  // basic_and
    const uint_fast8_t tmp_128 = uint_fast8_t(((uint_fast64_t(tmp_121) << 1) | tmp_127) & 7);  // basic_concat
    const uint_fast8_t tmp_129 = uint_fast8_t(((arg_2 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_130 = uint_fast8_t(((~tmp_100) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_131 = uint_fast8_t((tmp_114 & tmp_130) & 1);  // basic_and
    const uint_fast8_t tmp_132 = uint_fast8_t((tmp_131 | tmp_103) & 1);  // basic_or
    const uint_fast8_t tmp_133 = uint_fast8_t(((~tmp_132) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_134 = uint_fast8_t((tmp_129 & tmp_133) & 1);  // basic_and
    const uint_fast8_t tmp_135 = uint_fast8_t(((uint_fast64_t(tmp_128) << 1) | tmp_134) & 15);  // basic_concat
    const uint_fast8_t tmp_136 = uint_fast8_t(((arg_3 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_137 = uint_fast8_t(((~tmp_107) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_138 = uint_fast8_t((tmp_114 & tmp_137) & 1);  // basic_and
    const uint_fast8_t tmp_139 = uint_fast8_t((tmp_138 | tmp_110) & 1);  // basic_or
    const uint_fast8_t tmp_140 = uint_fast8_t(((~tmp_139) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_141 = uint_fast8_t((tmp_136 & tmp_140) & 1);  // basic_and
    const uint_fast8_t tmp_142 = uint_fast8_t(((uint_fast64_t(tmp_135) << 1) | tmp_141) & 31);  // basic_concat
    const uint_fast8_t tmp_143 = uint_fast8_t((tmp_142 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_144 = uint_fast8_t(((uint_fast64_t(tmp_114) << 1) | tmp_143) & 3);  // basic_concat
    const uint_fast8_t tmp_145 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_146 = uint_fast8_t(((~tmp_115) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_147 = uint_fast8_t((tmp_143 & tmp_146) & 1);  // basic_and
    const uint_fast8_t tmp_148 = uint_fast8_t((tmp_147 | tmp_118) & 1);  // basic_or
    const uint_fast8_t tmp_149 = uint_fast8_t(((~tmp_148) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_150 = uint_fast8_t((tmp_145 & tmp_149) & 1);  // basic_and
    const uint_fast8_t tmp_151 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_150) & 3);  // basic_concat
    const uint_fast8_t tmp_152 = uint_fast8_t(((arg_1 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_153 = uint_fast8_t(((~tmp_122) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_154 = uint_fast8_t((tmp_143 & tmp_153) & 1);  // basic_and
    const uint_fast8_t tmp_155 = uint_fast8_t((tmp_154 | tmp_125) & 1);  // basic_or
    const uint_fast8_t tmp_156 = uint_fast8_t(((~tmp_155) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_157 = uint_fast8_t((tmp_152 & tmp_156) & 1);  // basic_and
    const uint_fast8_t tmp_158 = uint_fast8_t(((uint_fast64_t(tmp_151) << 1) | tmp_157) & 7);  // basic_concat
    const uint_fast8_t tmp_159 = uint_fast8_t(((arg_2 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_160 = uint_fast8_t(((~tmp_129) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_161 = uint_fast8_t((tmp_143 & tmp_160) & 1);  // basic_and
    const uint_fast8_t tmp_162 = uint_fast8_t((tmp_161 | tmp_132) & 1);  // basic_or
    const uint_fast8_t tmp_163 = uint_fast8_t(((~tmp_162) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_164 = uint_fast8_t((tmp_159 & tmp_163) & 1);  // basic_and
    const uint_fast8_t tmp_165 = uint_fast8_t(((uint_fast64_t(tmp_158) << 1) | tmp_164) & 15);  // basic_concat
    const uint_fast8_t tmp_166 = uint_fast8_t(((arg_3 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_167 = uint_fast8_t(((~tmp_136) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_168 = uint_fast8_t((tmp_143 & tmp_167) & 1);  // basic_and
    const uint_fast8_t tmp_169 = uint_fast8_t((tmp_168 | tmp_139) & 1);  // basic_or
    const uint_fast8_t tmp_170 = uint_fast8_t(((~tmp_169) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_171 = uint_fast8_t((tmp_166 & tmp_170) & 1);  // basic_and
    const uint_fast8_t tmp_172 = uint_fast8_t(((uint_fast64_t(tmp_165) << 1) | tmp_171) & 31);  // basic_concat
    const uint_fast8_t tmp_173 = uint_fast8_t((tmp_172 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_174 = uint_fast8_t(((uint_fast64_t(tmp_144) << 1) | tmp_173) & 7);  // basic_concat
    const uint_fast8_t tmp_175 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_176 = uint_fast8_t(((~tmp_145) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_177 = uint_fast8_t((tmp_173 & tmp_176) & 1);  // basic_and
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_177 | tmp_148) & 1);  // basic_or
    const uint_fast8_t tmp_179 = uint_fast8_t(((~tmp_178) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_180 = uint_fast8_t((tmp_175 & tmp_179) & 1);  // basic_and
    const uint_fast8_t tmp_181 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_180) & 3);  // basic_concat
    const uint_fast8_t tmp_182 = uint_fast8_t(((arg_1 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_183 = uint_fast8_t(((~tmp_152) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_184 = uint_fast8_t((tmp_173 & tmp_183) & 1);  // basic_and
    const uint_fast8_t tmp_185 = uint_fast8_t((tmp_184 | tmp_155) & 1);  // basic_or
    const uint_fast8_t tmp_186 = uint_fast8_t(((~tmp_185) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_187 = uint_fast8_t((tmp_182 & tmp_186) & 1);  // basic_and
    const uint_fast8_t tmp_188 = uint_fast8_t(((uint_fast64_t(tmp_181) << 1) | tmp_187) & 7);  // basic_concat
    const uint_fast8_t tmp_189 = uint_fast8_t(((arg_2 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_190 = uint_fast8_t(((~tmp_159) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_191 = uint_fast8_t((tmp_173 & tmp_190) & 1);  // basic_and
    const uint_fast8_t tmp_192 = uint_fast8_t((tmp_191 | tmp_162) & 1);  // basic_or
    const uint_fast8_t tmp_193 = uint_fast8_t(((~tmp_192) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_194 = uint_fast8_t((tmp_189 & tmp_193) & 1);  // basic_and
    const uint_fast8_t tmp_195 = uint_fast8_t(((uint_fast64_t(tmp_188) << 1) | tmp_194) & 15);  // basic_concat
    const uint_fast8_t tmp_196 = uint_fast8_t(((arg_3 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_197 = uint_fast8_t(((~tmp_166) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_198 = uint_fast8_t((tmp_173 & tmp_197) & 1);  // basic_and
    const uint_fast8_t tmp_199 = uint_fast8_t((tmp_198 | tmp_169) & 1);  // basic_or
    const uint_fast8_t tmp_200 = uint_fast8_t(((~tmp_199) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_201 = uint_fast8_t((tmp_196 & tmp_200) & 1);  // basic_and
    const uint_fast8_t tmp_202 = uint_fast8_t(((uint_fast64_t(tmp_195) << 1) | tmp_201) & 31);  // basic_concat
    const uint_fast8_t tmp_203 = uint_fast8_t((tmp_202 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_204 = uint_fast8_t(((uint_fast64_t(tmp_174) << 1) | tmp_203) & 15);  // basic_concat
    const uint_fast8_t tmp_205 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_206 = uint_fast8_t(((~tmp_175) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_207 = uint_fast8_t((tmp_203 & tmp_206) & 1);  // basic_and
    const uint_fast8_t tmp_208 = uint_fast8_t((tmp_207 | tmp_178) & 1);  // basic_or
    const uint_fast8_t tmp_209 = uint_fast8_t(((~tmp_208) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_210 = uint_fast8_t((tmp_205 & tmp_209) & 1);  // basic_and
    const uint_fast8_t tmp_211 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_210) & 3);  // basic_concat
    const uint_fast8_t tmp_212 = uint_fast8_t(((arg_1 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_213 = uint_fast8_t(((~tmp_182) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_214 = uint_fast8_t((tmp_203 & tmp_213) & 1);  // basic_and
    const uint_fast8_t tmp_215 = uint_fast8_t((tmp_214 | tmp_185) & 1);  // basic_or
    const uint_fast8_t tmp_216 = uint_fast8_t(((~tmp_215) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_217 = uint_fast8_t((tmp_212 & tmp_216) & 1);  // basic_and
    const uint_fast8_t tmp_218 = uint_fast8_t(((uint_fast64_t(tmp_211) << 1) | tmp_217) & 7);  // basic_concat
    const uint_fast8_t tmp_219 = uint_fast8_t(((arg_2 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_220 = uint_fast8_t(((~tmp_189) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_221 = uint_fast8_t((tmp_203 & tmp_220) & 1);  // basic_and
    const uint_fast8_t tmp_222 = uint_fast8_t((tmp_221 | tmp_192) & 1);  // basic_or
    const uint_fast8_t tmp_223 = uint_fast8_t(((~tmp_222) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_224 = uint_fast8_t((tmp_219 & tmp_223) & 1);  // basic_and
    const uint_fast8_t tmp_225 = uint_fast8_t(((uint_fast64_t(tmp_218) << 1) | tmp_224) & 15);  // basic_concat
    const uint_fast8_t tmp_226 = uint_fast8_t(((arg_3 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_227 = uint_fast8_t(((~tmp_196) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_228 = uint_fast8_t((tmp_203 & tmp_227) & 1);  // basic_and
    const uint_fast8_t tmp_229 = uint_fast8_t((tmp_228 | tmp_199) & 1);  // basic_or
    const uint_fast8_t tmp_230 = uint_fast8_t(((~tmp_229) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_231 = uint_fast8_t((tmp_226 & tmp_230) & 1);  // basic_and
    const uint_fast8_t tmp_232 = uint_fast8_t(((uint_fast64_t(tmp_225) << 1) | tmp_231) & 31);  // basic_concat
    const uint_fast8_t tmp_233 = uint_fast8_t((tmp_232 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_234 = uint_fast8_t(((uint_fast64_t(tmp_204) << 1) | tmp_233) & 31);  // basic_concat
    const uint_fast8_t tmp_235 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_236 = uint_fast8_t(((~tmp_205) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_237 = uint_fast8_t((tmp_233 & tmp_236) & 1);  // basic_and
    const uint_fast8_t tmp_238 = uint_fast8_t((tmp_237 | tmp_208) & 1);  // basic_or
    const uint_fast8_t tmp_239 = uint_fast8_t(((~tmp_238) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_240 = uint_fast8_t((tmp_235 & tmp_239) & 1);  // basic_and
    const uint_fast8_t tmp_241 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_240) & 3);  // basic_concat
    const uint_fast8_t tmp_242 = uint_fast8_t(((arg_1 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_243 = uint_fast8_t(((~tmp_212) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_244 = uint_fast8_t((tmp_233 & tmp_243) & 1);  // basic_and
    const uint_fast8_t tmp_245 = uint_fast8_t((tmp_244 | tmp_215) & 1);  // basic_or
    const uint_fast8_t tmp_246 = uint_fast8_t(((~tmp_245) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_247 = uint_fast8_t((tmp_242 & tmp_246) & 1);  // basic_and
    const uint_fast8_t tmp_248 = uint_fast8_t(((uint_fast64_t(tmp_241) << 1) | tmp_247) & 7);  // basic_concat
    const uint_fast8_t tmp_249 = uint_fast8_t(((arg_2 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_250 = uint_fast8_t(((~tmp_219) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_251 = uint_fast8_t((tmp_233 & tmp_250) & 1);  // basic_and
    const uint_fast8_t tmp_252 = uint_fast8_t((tmp_251 | tmp_222) & 1);  // basic_or
    const uint_fast8_t tmp_253 = uint_fast8_t(((~tmp_252) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_254 = uint_fast8_t((tmp_249 & tmp_253) & 1);  // basic_and
    const uint_fast8_t tmp_255 = uint_fast8_t(((uint_fast64_t(tmp_248) << 1) | tmp_254) & 15);  // basic_concat
    const uint_fast8_t tmp_256 = uint_fast8_t(((arg_3 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_257 = uint_fast8_t(((~tmp_226) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_258 = uint_fast8_t((tmp_233 & tmp_257) & 1);  // basic_and
    const uint_fast8_t tmp_259 = uint_fast8_t((tmp_258 | tmp_229) & 1);  // basic_or
    const uint_fast8_t tmp_260 = uint_fast8_t(((~tmp_259) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_261 = uint_fast8_t((tmp_256 & tmp_260) & 1);  // basic_and
    const uint_fast8_t tmp_262 = uint_fast8_t(((uint_fast64_t(tmp_255) << 1) | tmp_261) & 31);  // basic_concat
    const uint_fast8_t tmp_263 = uint_fast8_t((tmp_262 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_264 = uint_fast8_t(((uint_fast64_t(tmp_234) << 1) | tmp_263) & 63);  // basic_concat
    const uint_fast8_t tmp_265 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_266 = uint_fast8_t(((~tmp_235) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_267 = uint_fast8_t((tmp_263 & tmp_266) & 1);  // basic_and
    const uint_fast8_t tmp_268 = uint_fast8_t((tmp_267 | tmp_238) & 1);  // basic_or
    const uint_fast8_t tmp_269 = uint_fast8_t(((~tmp_268) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_270 = uint_fast8_t((tmp_265 & tmp_269) & 1);  // basic_and
    const uint_fast8_t tmp_271 = uint_fast8_t(((uint_fast64_t(uint_fast8_t(0 & 1)) << 1) | tmp_270) & 3);  // basic_concat
    const uint_fast8_t tmp_272 = uint_fast8_t(((arg_1 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_273 = uint_fast8_t(((~tmp_242) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_274 = uint_fast8_t((tmp_263 & tmp_273) & 1);  // basic_and
    const uint_fast8_t tmp_275 = uint_fast8_t((tmp_274 | tmp_245) & 1);  // basic_or
    const uint_fast8_t tmp_276 = uint_fast8_t(((~tmp_275) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_277 = uint_fast8_t((tmp_272 & tmp_276) & 1);  // basic_and
    const uint_fast8_t tmp_278 = uint_fast8_t(((uint_fast64_t(tmp_271) << 1) | tmp_277) & 7);  // basic_concat
    const uint_fast8_t tmp_279 = uint_fast8_t(((arg_2 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_280 = uint_fast8_t(((~tmp_249) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_281 = uint_fast8_t((tmp_263 & tmp_280) & 1);  // basic_and
    const uint_fast8_t tmp_282 = uint_fast8_t((tmp_281 | tmp_252) & 1);  // basic_or
    const uint_fast8_t tmp_283 = uint_fast8_t(((~tmp_282) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_284 = uint_fast8_t((tmp_279 & tmp_283) & 1);  // basic_and
    const uint_fast8_t tmp_285 = uint_fast8_t(((uint_fast64_t(tmp_278) << 1) | tmp_284) & 15);  // basic_concat
    const uint_fast8_t tmp_286 = uint_fast8_t(((arg_3 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_287 = uint_fast8_t(((~tmp_256) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_288 = uint_fast8_t((tmp_263 & tmp_287) & 1);  // basic_and
    const uint_fast8_t tmp_289 = uint_fast8_t((tmp_288 | tmp_259) & 1);  // basic_or
    const uint_fast8_t tmp_290 = uint_fast8_t(((~tmp_289) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_291 = uint_fast8_t((tmp_286 & tmp_290) & 1);  // basic_and
    const uint_fast8_t tmp_292 = uint_fast8_t(((uint_fast64_t(tmp_285) << 1) | tmp_291) & 31);  // basic_concat
    const uint_fast8_t tmp_293 = uint_fast8_t((tmp_292 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_294 = uint_fast8_t(((uint_fast64_t(tmp_264) << 1) | tmp_293) & 127);  // basic_concat
    return tmp_294;
}
static inline uint_fast8_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_296 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast8_t tmp_297 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_298 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_296), static_cast<uint_fast64_t>(tmp_297)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_299 = uint_fast8_t(tmp_298[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_300 = uint_fast8_t(tmp_298[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_301 = uint_fast8_t((tmp_299 - tmp_300) & 255);  // basic_sub
    return tmp_301;
}
static inline uint_fast8_t uq_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_303 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_304 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_305 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_303), static_cast<uint_fast64_t>(tmp_304)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_306 = uint_fast8_t(tmp_305[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_307 = uint_fast8_t(tmp_305[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_308 = uint_fast8_t((tmp_306 + tmp_307) & 15);  // basic_add
    return tmp_308;
}
static inline uint_fast16_t est_global_shift(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // _est_global_shift
    const uint_fast8_t tmp_302 = uq_sub(arg_0, arg_1);  // uq_sub
    const uint_fast8_t tmp_309 = uq_add_1(uint_fast8_t(7 & 7), uint_fast8_t(2 & 3));  // uq_add
    const uint_fast16_t tmp_310 = uint_fast16_t(0 & 511);  // uq_alloc
    const uint_fast16_t tmp_311 = uint_fast16_t(((uint_fast64_t(tmp_302) << 2) | uint_fast8_t(0 & 3)) & 511);  // basic_concat
    return tmp_311;
}
static inline uint_fast64_t uq_rshift_1(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_313 = uint_fast64_t((arg_1 >= 33 ? 0 : (arg_0 >> arg_1)) & 8589934591);  // basic_rshift
    return tmp_313;
}
static inline uint_fast8_t uq_add_2(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_315 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const uint_fast8_t tmp_316 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 7);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_317 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_315), static_cast<uint_fast64_t>(tmp_316)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_318 = uint_fast8_t(tmp_317[0] & 7);  // _basic_get_item_0
    const uint_fast8_t tmp_319 = uint_fast8_t(tmp_317[1] & 7);  // _basic_get_item_1
    const uint_fast8_t tmp_320 = uint_fast8_t((tmp_318 + tmp_319) & 7);  // basic_add
    return tmp_320;
}
static inline uint_fast64_t uq_to_q(uint_fast64_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_321 = uq_add_2(uint_fast8_t(2 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast64_t tmp_322 = uint_fast64_t(0 & 17179869183);  // q_alloc
    const uint_fast64_t tmp_323 = uint_fast64_t(arg_0 & 17179869183);  // basic_identity
    return tmp_323;
}
static inline uint_fast8_t sign_xor(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // sign_xor
    const uint_fast8_t tmp_327 = uint_fast8_t((arg_0 ^ arg_1) & 1);  // basic_xor
    return tmp_327;
}
static inline uint_fast64_t q_neg(uint_fast64_t arg_0) {  // q_neg
    const uint_fast8_t tmp_329 = uint_fast8_t((arg_0 == 8589934592) & 1);  // _q_is_min_val
    const uint_fast64_t tmp_330 = uint_fast64_t(((~arg_0) & 17179869183) & 17179869183);  // basic_invert
    const uint_fast64_t tmp_331 = uint_fast64_t((tmp_330 + uint_fast8_t(1 & 1)) & 17179869183);  // basic_add
    const uint_fast64_t tmp_332 = uint_fast64_t((arg_0 ^ arg_0) & 17179869183);  // basic_xor
    const uint_fast64_t tmp_333 = uint_fast64_t(((~tmp_332) & 17179869183) & 17179869183);  // basic_invert
    const uint_fast64_t tmp_334 = uint_fast64_t((tmp_329 == 1 ? tmp_333 : tmp_331) & 17179869183);  // basic_mux_2_1
    return tmp_334;
}
static inline uint_fast64_t q_add_sign(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast64_t tmp_335 = q_neg(arg_0);  // q_neg
    const uint_fast64_t tmp_336 = uint_fast64_t((arg_1 == 1 ? tmp_335 : arg_0) & 17179869183);  // basic_mux_2_1
    return tmp_336;
}
static inline uint_fast64_t q_sign_extend(uint_fast64_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast8_t q_sign_bit(uint_fast64_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_445 = uint_fast8_t(((arg_0 >> 33) & 1) & 1);  // basic_select
    return tmp_445;
}
static inline uint_fast64_t q_sign_extend_1(uint_fast64_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_446 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_447 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_446) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_448 = uint_fast8_t((tmp_447 - tmp_446) & 1);  // basic_sub
    const uint_fast64_t tmp_449 = uint_fast64_t(0 & 34359738367);  // q_alloc
    const uint_fast64_t tmp_450 = uint_fast64_t(((uint_fast64_t(tmp_448) << 34) | arg_0) & 34359738367);  // basic_concat
    return tmp_450;
}
static inline uint_fast64_t q_lshift(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // q_lshift
    const uint_fast64_t tmp_452 = uint_fast64_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 34359738367);  // basic_lshift
    return tmp_452;
}
static inline uint_fast64_t q_sign_extend_2(uint_fast64_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast64_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_513 = uint_fast8_t(((arg_0 >> 34) & 1) & 1);  // basic_select
    return tmp_513;
}
static inline uint_fast64_t q_sign_extend_3(uint_fast64_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_514 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_515 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_514) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_516 = uint_fast8_t((tmp_515 - tmp_514) & 1);  // basic_sub
    const uint_fast64_t tmp_517 = uint_fast64_t(0 & 68719476735);  // q_alloc
    const uint_fast64_t tmp_518 = uint_fast64_t(((uint_fast64_t(tmp_516) << 35) | arg_0) & 68719476735);  // basic_concat
    return tmp_518;
}
static inline uint_fast64_t q_lshift_1(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // q_lshift
    const uint_fast64_t tmp_520 = uint_fast64_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 68719476735);  // basic_lshift
    return tmp_520;
}
static inline uint_fast64_t q_sign_extend_4(uint_fast64_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_526 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_527 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_526) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_528 = uint_fast8_t((tmp_527 - tmp_526) & 3);  // basic_sub
    const uint_fast64_t tmp_529 = uint_fast64_t(0 & 137438953471);  // q_alloc
    const uint_fast64_t tmp_530 = uint_fast64_t(((uint_fast64_t(tmp_528) << 35) | arg_0) & 137438953471);  // basic_concat
    return tmp_530;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast64_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_533 = uint_fast8_t(((arg_0 >> 35) & 1) & 1);  // basic_select
    return tmp_533;
}
static inline uint_fast64_t q_sign_extend_5(uint_fast64_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_534 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_535 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_534) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_536 = uint_fast8_t((tmp_535 - tmp_534) & 1);  // basic_sub
    const uint_fast64_t tmp_537 = uint_fast64_t(0 & 137438953471);  // q_alloc
    const uint_fast64_t tmp_538 = uint_fast64_t(((uint_fast64_t(tmp_536) << 36) | arg_0) & 137438953471);  // basic_concat
    return tmp_538;
}
static inline uint_fast64_t q_add(uint_fast64_t arg_0, uint_fast64_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_525 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_531 = q_sign_extend_4(tmp_525);  // q_sign_extend
    const uint_fast64_t tmp_532 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 68719476735);  // basic_lshift
    const uint_fast64_t tmp_539 = q_sign_extend_5(tmp_532);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_540 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_531), static_cast<uint_fast64_t>(tmp_539)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_541 = uint_fast64_t(tmp_540[0] & 137438953471);  // _basic_get_item_0
    const uint_fast64_t tmp_542 = uint_fast64_t(tmp_540[1] & 137438953471);  // _basic_get_item_1
    const uint_fast64_t tmp_543 = uint_fast64_t((tmp_541 + tmp_542) & 137438953471);  // basic_add
    return tmp_543;
}
static inline uint_fast64_t CSA_tree4(uint_fast64_t arg_0, uint_fast64_t arg_1, uint_fast64_t arg_2, uint_fast64_t arg_3) {  // CSA_tree4
    // begin inline primitive CSA
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_389 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_390 = q_sign_extend(tmp_389);  // q_sign_extend
    const uint_fast64_t tmp_391 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_392 = q_sign_extend(tmp_391);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_393 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_390), static_cast<uint_fast64_t>(tmp_392)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_394 = uint_fast64_t(tmp_393[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_395 = uint_fast64_t(tmp_393[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_396 = uint_fast64_t((tmp_394 ^ tmp_395) & 17179869183);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_397 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_396) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_398 = q_sign_extend(tmp_397);  // q_sign_extend
    const uint_fast64_t tmp_399 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_2) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_400 = q_sign_extend(tmp_399);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_401 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_398), static_cast<uint_fast64_t>(tmp_400)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_402 = uint_fast64_t(tmp_401[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_403 = uint_fast64_t(tmp_401[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_404 = uint_fast64_t((tmp_402 ^ tmp_403) & 17179869183);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_405 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_406 = q_sign_extend(tmp_405);  // q_sign_extend
    const uint_fast64_t tmp_407 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_408 = q_sign_extend(tmp_407);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_409 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_406), static_cast<uint_fast64_t>(tmp_408)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_410 = uint_fast64_t(tmp_409[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_411 = uint_fast64_t(tmp_409[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_412 = uint_fast64_t((tmp_410 & tmp_411) & 17179869183);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_413 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_414 = q_sign_extend(tmp_413);  // q_sign_extend
    const uint_fast64_t tmp_415 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_2) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_416 = q_sign_extend(tmp_415);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_417 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_414), static_cast<uint_fast64_t>(tmp_416)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_418 = uint_fast64_t(tmp_417[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_419 = uint_fast64_t(tmp_417[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_420 = uint_fast64_t((tmp_418 & tmp_419) & 17179869183);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_421 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_412) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_422 = q_sign_extend(tmp_421);  // q_sign_extend
    const uint_fast64_t tmp_423 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_420) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_424 = q_sign_extend(tmp_423);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_425 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_422), static_cast<uint_fast64_t>(tmp_424)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_426 = uint_fast64_t(tmp_425[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_427 = uint_fast64_t(tmp_425[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_428 = uint_fast64_t((tmp_426 | tmp_427) & 17179869183);  // basic_or
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_429 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_430 = q_sign_extend(tmp_429);  // q_sign_extend
    const uint_fast64_t tmp_431 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_2) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_432 = q_sign_extend(tmp_431);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_433 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_430), static_cast<uint_fast64_t>(tmp_432)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_434 = uint_fast64_t(tmp_433[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_435 = uint_fast64_t(tmp_433[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_436 = uint_fast64_t((tmp_434 & tmp_435) & 17179869183);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_437 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_428) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_438 = q_sign_extend(tmp_437);  // q_sign_extend
    const uint_fast64_t tmp_439 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_436) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_440 = q_sign_extend(tmp_439);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_441 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_438), static_cast<uint_fast64_t>(tmp_440)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_442 = uint_fast64_t(tmp_441[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_443 = uint_fast64_t(tmp_441[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_444 = uint_fast64_t((tmp_442 | tmp_443) & 17179869183);  // basic_or
    const uint_fast64_t tmp_451 = q_sign_extend_1(tmp_444);  // q_sign_extend
    const uint_fast64_t tmp_453 = q_lshift(tmp_451, uint_fast8_t(1 & 1));  // q_lshift
    const std::array<uint_fast64_t, 2> tmp_454 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_404), static_cast<uint_fast64_t>(tmp_453)};  // basic_tuple_maker_2
    // end inline primitive CSA
    const uint_fast64_t tmp_455 = uint_fast64_t(tmp_454[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_456 = uint_fast64_t(tmp_454[1] & 34359738367);  // _basic_get_item_1
    // begin inline primitive CSA
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_457 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_3) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_458 = q_sign_extend(tmp_457);  // q_sign_extend
    const uint_fast64_t tmp_459 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_455) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_460 = q_sign_extend(tmp_459);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_461 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_458), static_cast<uint_fast64_t>(tmp_460)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_462 = uint_fast64_t(tmp_461[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_463 = uint_fast64_t(tmp_461[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_464 = uint_fast64_t((tmp_462 ^ tmp_463) & 17179869183);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_465 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_464) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_466 = q_sign_extend_1(tmp_465);  // q_sign_extend
    const uint_fast64_t tmp_467 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_456) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_468 = q_sign_extend_2(tmp_467);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_469 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_466), static_cast<uint_fast64_t>(tmp_468)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_470 = uint_fast64_t(tmp_469[0] & 34359738367);  // _basic_get_item_0
    const uint_fast64_t tmp_471 = uint_fast64_t(tmp_469[1] & 34359738367);  // _basic_get_item_1
    const uint_fast64_t tmp_472 = uint_fast64_t((tmp_470 ^ tmp_471) & 34359738367);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_473 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_3) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_474 = q_sign_extend(tmp_473);  // q_sign_extend
    const uint_fast64_t tmp_475 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_455) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_476 = q_sign_extend(tmp_475);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_477 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_474), static_cast<uint_fast64_t>(tmp_476)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_478 = uint_fast64_t(tmp_477[0] & 17179869183);  // _basic_get_item_0
    const uint_fast64_t tmp_479 = uint_fast64_t(tmp_477[1] & 17179869183);  // _basic_get_item_1
    const uint_fast64_t tmp_480 = uint_fast64_t((tmp_478 & tmp_479) & 17179869183);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_481 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_3) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_482 = q_sign_extend_1(tmp_481);  // q_sign_extend
    const uint_fast64_t tmp_483 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_456) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_484 = q_sign_extend_2(tmp_483);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_485 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_482), static_cast<uint_fast64_t>(tmp_484)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_486 = uint_fast64_t(tmp_485[0] & 34359738367);  // _basic_get_item_0
    const uint_fast64_t tmp_487 = uint_fast64_t(tmp_485[1] & 34359738367);  // _basic_get_item_1
    const uint_fast64_t tmp_488 = uint_fast64_t((tmp_486 & tmp_487) & 34359738367);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_489 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_480) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_490 = q_sign_extend_1(tmp_489);  // q_sign_extend
    const uint_fast64_t tmp_491 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_488) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_492 = q_sign_extend_2(tmp_491);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_493 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_490), static_cast<uint_fast64_t>(tmp_492)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_494 = uint_fast64_t(tmp_493[0] & 34359738367);  // _basic_get_item_0
    const uint_fast64_t tmp_495 = uint_fast64_t(tmp_493[1] & 34359738367);  // _basic_get_item_1
    const uint_fast64_t tmp_496 = uint_fast64_t((tmp_494 | tmp_495) & 34359738367);  // basic_or
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_497 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_455) << uint_fast8_t(0 & 1))) & 17179869183);  // basic_lshift
    const uint_fast64_t tmp_498 = q_sign_extend_1(tmp_497);  // q_sign_extend
    const uint_fast64_t tmp_499 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_456) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_500 = q_sign_extend_2(tmp_499);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_501 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_498), static_cast<uint_fast64_t>(tmp_500)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_502 = uint_fast64_t(tmp_501[0] & 34359738367);  // _basic_get_item_0
    const uint_fast64_t tmp_503 = uint_fast64_t(tmp_501[1] & 34359738367);  // _basic_get_item_1
    const uint_fast64_t tmp_504 = uint_fast64_t((tmp_502 & tmp_503) & 34359738367);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast64_t tmp_505 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_496) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_506 = q_sign_extend_2(tmp_505);  // q_sign_extend
    const uint_fast64_t tmp_507 = uint_fast64_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_504) << uint_fast8_t(0 & 1))) & 34359738367);  // basic_lshift
    const uint_fast64_t tmp_508 = q_sign_extend_2(tmp_507);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_509 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_506), static_cast<uint_fast64_t>(tmp_508)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast64_t tmp_510 = uint_fast64_t(tmp_509[0] & 34359738367);  // _basic_get_item_0
    const uint_fast64_t tmp_511 = uint_fast64_t(tmp_509[1] & 34359738367);  // _basic_get_item_1
    const uint_fast64_t tmp_512 = uint_fast64_t((tmp_510 | tmp_511) & 34359738367);  // basic_or
    const uint_fast64_t tmp_519 = q_sign_extend_3(tmp_512);  // q_sign_extend
    const uint_fast64_t tmp_521 = q_lshift_1(tmp_519, uint_fast8_t(1 & 1));  // q_lshift
    const std::array<uint_fast64_t, 2> tmp_522 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_472), static_cast<uint_fast64_t>(tmp_521)};  // basic_tuple_maker_2
    // end inline primitive CSA
    const uint_fast64_t tmp_523 = uint_fast64_t(tmp_522[0] & 34359738367);  // _basic_get_item_0
    const uint_fast64_t tmp_524 = uint_fast64_t(tmp_522[1] & 68719476735);  // _basic_get_item_1
    const uint_fast64_t tmp_544 = q_add(tmp_523, tmp_524);  // q_add
    return tmp_544;
}
static inline uint_fast16_t prepend_ones(uint_fast8_t arg_0) {  // _prepend_ones
    const uint_fast8_t tmp_546 = uq_add_1(uint_fast8_t(7 & 7), uint_fast8_t(2 & 3));  // uq_add
    const uint_fast16_t tmp_547 = uint_fast16_t(0 & 511);  // uq_alloc
    const uint_fast16_t tmp_548 = uint_fast16_t(((uint_fast64_t(arg_0) << 2) | uint_fast8_t(3 & 3)) & 511);  // basic_concat
    return tmp_548;
}
static inline uint_fast8_t uq_add_3(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_550 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const uint_fast8_t tmp_551 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 31);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_552 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_550), static_cast<uint_fast64_t>(tmp_551)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_553 = uint_fast8_t(tmp_552[0] & 31);  // _basic_get_item_0
    const uint_fast8_t tmp_554 = uint_fast8_t(tmp_552[1] & 31);  // _basic_get_item_1
    const uint_fast8_t tmp_555 = uint_fast8_t((tmp_553 + tmp_554) & 31);  // basic_add
    return tmp_555;
}
static inline uint_fast16_t uq_to_q_1(uint_fast16_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_556 = uq_add_3(uint_fast8_t(9 & 15), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast16_t tmp_557 = uint_fast16_t(0 & 1023);  // q_alloc
    const uint_fast16_t tmp_558 = uint_fast16_t(arg_0 & 1023);  // basic_identity
    return tmp_558;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_561 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    return tmp_561;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_562 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_563 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_562) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_564 = uint_fast8_t((tmp_563 - tmp_562) & 1);  // basic_sub
    const uint_fast16_t tmp_565 = uint_fast16_t(0 & 2047);  // q_alloc
    const uint_fast16_t tmp_566 = uint_fast16_t(((uint_fast64_t(tmp_564) << 10) | arg_0) & 2047);  // basic_concat
    return tmp_566;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_569 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_569;
}
static inline uint_fast16_t q_sign_extend_7(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_570 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_571 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_570) << uint_fast8_t(3 & 3))) & 15);  // basic_lshift
    const uint_fast8_t tmp_572 = uint_fast8_t((tmp_571 - tmp_570) & 7);  // basic_sub
    const uint_fast16_t tmp_573 = uint_fast16_t(0 & 2047);  // q_alloc
    const uint_fast16_t tmp_574 = uint_fast16_t(((uint_fast64_t(tmp_572) << 8) | arg_0) & 2047);  // basic_concat
    return tmp_574;
}
static inline uint_fast16_t q_sub(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_560 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 1023);  // basic_lshift
    const uint_fast16_t tmp_567 = q_sign_extend_6(tmp_560);  // q_sign_extend
    const uint_fast8_t tmp_568 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_575 = q_sign_extend_7(tmp_568);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_576 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_567), static_cast<uint_fast64_t>(tmp_575)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_577 = uint_fast16_t(tmp_576[0] & 2047);  // _basic_get_item_0
    const uint_fast16_t tmp_578 = uint_fast16_t(tmp_576[1] & 2047);  // _basic_get_item_1
    const uint_fast16_t tmp_579 = uint_fast16_t((tmp_577 - tmp_578) & 2047);  // basic_sub
    return tmp_579;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast64_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_581 = uint_fast8_t(((arg_0 >> 36) & 1) & 1);  // basic_select
    return tmp_581;
}
static inline uint_fast64_t q_neg_1(uint_fast64_t arg_0) {  // q_neg
    const uint_fast8_t tmp_584 = uint_fast8_t((arg_0 == 68719476736) & 1);  // _q_is_min_val
    const uint_fast64_t tmp_585 = uint_fast64_t(((~arg_0) & 137438953471) & 137438953471);  // basic_invert
    const uint_fast64_t tmp_586 = uint_fast64_t((tmp_585 + uint_fast8_t(1 & 1)) & 137438953471);  // basic_add
    const uint_fast64_t tmp_587 = uint_fast64_t((arg_0 ^ arg_0) & 137438953471);  // basic_xor
    const uint_fast64_t tmp_588 = uint_fast64_t(((~tmp_587) & 137438953471) & 137438953471);  // basic_invert
    const uint_fast64_t tmp_589 = uint_fast64_t((tmp_584 == 1 ? tmp_588 : tmp_586) & 137438953471);  // basic_mux_2_1
    return tmp_589;
}
static inline uint_fast64_t q_add_sign_1(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast64_t tmp_590 = q_neg_1(arg_0);  // q_neg
    const uint_fast64_t tmp_591 = uint_fast64_t((arg_1 == 1 ? tmp_590 : arg_0) & 137438953471);  // basic_mux_2_1
    return tmp_591;
}
static inline uint_fast64_t q_abs(uint_fast64_t arg_0) {  // q_abs
    const uint_fast8_t tmp_583 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast64_t tmp_592 = q_add_sign_1(arg_0, tmp_583);  // q_add_sign
    return tmp_592;
}
static inline uint_fast64_t q_to_uq(uint_fast64_t arg_0) {  // q_to_uq
    const uint_fast64_t tmp_594 = uint_fast64_t(arg_0 & 68719476735);  // basic_identity
    return tmp_594;
}
static inline uint_fast8_t lzc(uint_fast64_t arg_0) {  // lzc
    const uint_fast8_t tmp_596 = uint_fast8_t(((arg_0 >> 35) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_597 = uint_fast8_t(((~tmp_596) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_598 = uint_fast8_t((uint_fast8_t(1 & 1) & tmp_597) & 1);  // basic_and
    const uint_fast8_t tmp_599 = uint_fast8_t((uint_fast8_t(0 & 63) + tmp_598) & 63);  // basic_add
    const uint_fast8_t tmp_600 = uint_fast8_t(((arg_0 >> 34) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_601 = uint_fast8_t(((~tmp_600) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_602 = uint_fast8_t((tmp_598 & tmp_601) & 1);  // basic_and
    const uint_fast8_t tmp_603 = uint_fast8_t((tmp_599 + tmp_602) & 63);  // basic_add
    const uint_fast8_t tmp_604 = uint_fast8_t(((arg_0 >> 33) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_605 = uint_fast8_t(((~tmp_604) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_606 = uint_fast8_t((tmp_602 & tmp_605) & 1);  // basic_and
    const uint_fast8_t tmp_607 = uint_fast8_t((tmp_603 + tmp_606) & 63);  // basic_add
    const uint_fast8_t tmp_608 = uint_fast8_t(((arg_0 >> 32) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_609 = uint_fast8_t(((~tmp_608) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_610 = uint_fast8_t((tmp_606 & tmp_609) & 1);  // basic_and
    const uint_fast8_t tmp_611 = uint_fast8_t((tmp_607 + tmp_610) & 63);  // basic_add
    const uint_fast8_t tmp_612 = uint_fast8_t(((arg_0 >> 31) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_613 = uint_fast8_t(((~tmp_612) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_614 = uint_fast8_t((tmp_610 & tmp_613) & 1);  // basic_and
    const uint_fast8_t tmp_615 = uint_fast8_t((tmp_611 + tmp_614) & 63);  // basic_add
    const uint_fast8_t tmp_616 = uint_fast8_t(((arg_0 >> 30) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_617 = uint_fast8_t(((~tmp_616) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_618 = uint_fast8_t((tmp_614 & tmp_617) & 1);  // basic_and
    const uint_fast8_t tmp_619 = uint_fast8_t((tmp_615 + tmp_618) & 63);  // basic_add
    const uint_fast8_t tmp_620 = uint_fast8_t(((arg_0 >> 29) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_621 = uint_fast8_t(((~tmp_620) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_622 = uint_fast8_t((tmp_618 & tmp_621) & 1);  // basic_and
    const uint_fast8_t tmp_623 = uint_fast8_t((tmp_619 + tmp_622) & 63);  // basic_add
    const uint_fast8_t tmp_624 = uint_fast8_t(((arg_0 >> 28) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_625 = uint_fast8_t(((~tmp_624) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_626 = uint_fast8_t((tmp_622 & tmp_625) & 1);  // basic_and
    const uint_fast8_t tmp_627 = uint_fast8_t((tmp_623 + tmp_626) & 63);  // basic_add
    const uint_fast8_t tmp_628 = uint_fast8_t(((arg_0 >> 27) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_629 = uint_fast8_t(((~tmp_628) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_630 = uint_fast8_t((tmp_626 & tmp_629) & 1);  // basic_and
    const uint_fast8_t tmp_631 = uint_fast8_t((tmp_627 + tmp_630) & 63);  // basic_add
    const uint_fast8_t tmp_632 = uint_fast8_t(((arg_0 >> 26) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_633 = uint_fast8_t(((~tmp_632) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_634 = uint_fast8_t((tmp_630 & tmp_633) & 1);  // basic_and
    const uint_fast8_t tmp_635 = uint_fast8_t((tmp_631 + tmp_634) & 63);  // basic_add
    const uint_fast8_t tmp_636 = uint_fast8_t(((arg_0 >> 25) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_637 = uint_fast8_t(((~tmp_636) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_638 = uint_fast8_t((tmp_634 & tmp_637) & 1);  // basic_and
    const uint_fast8_t tmp_639 = uint_fast8_t((tmp_635 + tmp_638) & 63);  // basic_add
    const uint_fast8_t tmp_640 = uint_fast8_t(((arg_0 >> 24) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_641 = uint_fast8_t(((~tmp_640) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_642 = uint_fast8_t((tmp_638 & tmp_641) & 1);  // basic_and
    const uint_fast8_t tmp_643 = uint_fast8_t((tmp_639 + tmp_642) & 63);  // basic_add
    const uint_fast8_t tmp_644 = uint_fast8_t(((arg_0 >> 23) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_645 = uint_fast8_t(((~tmp_644) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_646 = uint_fast8_t((tmp_642 & tmp_645) & 1);  // basic_and
    const uint_fast8_t tmp_647 = uint_fast8_t((tmp_643 + tmp_646) & 63);  // basic_add
    const uint_fast8_t tmp_648 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_649 = uint_fast8_t(((~tmp_648) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_650 = uint_fast8_t((tmp_646 & tmp_649) & 1);  // basic_and
    const uint_fast8_t tmp_651 = uint_fast8_t((tmp_647 + tmp_650) & 63);  // basic_add
    const uint_fast8_t tmp_652 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_653 = uint_fast8_t(((~tmp_652) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_654 = uint_fast8_t((tmp_650 & tmp_653) & 1);  // basic_and
    const uint_fast8_t tmp_655 = uint_fast8_t((tmp_651 + tmp_654) & 63);  // basic_add
    const uint_fast8_t tmp_656 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_657 = uint_fast8_t(((~tmp_656) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_658 = uint_fast8_t((tmp_654 & tmp_657) & 1);  // basic_and
    const uint_fast8_t tmp_659 = uint_fast8_t((tmp_655 + tmp_658) & 63);  // basic_add
    const uint_fast8_t tmp_660 = uint_fast8_t(((arg_0 >> 19) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_661 = uint_fast8_t(((~tmp_660) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_662 = uint_fast8_t((tmp_658 & tmp_661) & 1);  // basic_and
    const uint_fast8_t tmp_663 = uint_fast8_t((tmp_659 + tmp_662) & 63);  // basic_add
    const uint_fast8_t tmp_664 = uint_fast8_t(((arg_0 >> 18) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_665 = uint_fast8_t(((~tmp_664) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_666 = uint_fast8_t((tmp_662 & tmp_665) & 1);  // basic_and
    const uint_fast8_t tmp_667 = uint_fast8_t((tmp_663 + tmp_666) & 63);  // basic_add
    const uint_fast8_t tmp_668 = uint_fast8_t(((arg_0 >> 17) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_669 = uint_fast8_t(((~tmp_668) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_670 = uint_fast8_t((tmp_666 & tmp_669) & 1);  // basic_and
    const uint_fast8_t tmp_671 = uint_fast8_t((tmp_667 + tmp_670) & 63);  // basic_add
    const uint_fast8_t tmp_672 = uint_fast8_t(((arg_0 >> 16) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_673 = uint_fast8_t(((~tmp_672) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_674 = uint_fast8_t((tmp_670 & tmp_673) & 1);  // basic_and
    const uint_fast8_t tmp_675 = uint_fast8_t((tmp_671 + tmp_674) & 63);  // basic_add
    const uint_fast8_t tmp_676 = uint_fast8_t(((arg_0 >> 15) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_677 = uint_fast8_t(((~tmp_676) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_678 = uint_fast8_t((tmp_674 & tmp_677) & 1);  // basic_and
    const uint_fast8_t tmp_679 = uint_fast8_t((tmp_675 + tmp_678) & 63);  // basic_add
    const uint_fast8_t tmp_680 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_681 = uint_fast8_t(((~tmp_680) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_682 = uint_fast8_t((tmp_678 & tmp_681) & 1);  // basic_and
    const uint_fast8_t tmp_683 = uint_fast8_t((tmp_679 + tmp_682) & 63);  // basic_add
    const uint_fast8_t tmp_684 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_685 = uint_fast8_t(((~tmp_684) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_686 = uint_fast8_t((tmp_682 & tmp_685) & 1);  // basic_and
    const uint_fast8_t tmp_687 = uint_fast8_t((tmp_683 + tmp_686) & 63);  // basic_add
    const uint_fast8_t tmp_688 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_689 = uint_fast8_t(((~tmp_688) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_690 = uint_fast8_t((tmp_686 & tmp_689) & 1);  // basic_and
    const uint_fast8_t tmp_691 = uint_fast8_t((tmp_687 + tmp_690) & 63);  // basic_add
    const uint_fast8_t tmp_692 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_693 = uint_fast8_t(((~tmp_692) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_694 = uint_fast8_t((tmp_690 & tmp_693) & 1);  // basic_and
    const uint_fast8_t tmp_695 = uint_fast8_t((tmp_691 + tmp_694) & 63);  // basic_add
    const uint_fast8_t tmp_696 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_697 = uint_fast8_t(((~tmp_696) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_698 = uint_fast8_t((tmp_694 & tmp_697) & 1);  // basic_and
    const uint_fast8_t tmp_699 = uint_fast8_t((tmp_695 + tmp_698) & 63);  // basic_add
    const uint_fast8_t tmp_700 = uint_fast8_t(((arg_0 >> 9) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_701 = uint_fast8_t(((~tmp_700) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_702 = uint_fast8_t((tmp_698 & tmp_701) & 1);  // basic_and
    const uint_fast8_t tmp_703 = uint_fast8_t((tmp_699 + tmp_702) & 63);  // basic_add
    const uint_fast8_t tmp_704 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_705 = uint_fast8_t(((~tmp_704) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_706 = uint_fast8_t((tmp_702 & tmp_705) & 1);  // basic_and
    const uint_fast8_t tmp_707 = uint_fast8_t((tmp_703 + tmp_706) & 63);  // basic_add
    const uint_fast8_t tmp_708 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_709 = uint_fast8_t(((~tmp_708) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_710 = uint_fast8_t((tmp_706 & tmp_709) & 1);  // basic_and
    const uint_fast8_t tmp_711 = uint_fast8_t((tmp_707 + tmp_710) & 63);  // basic_add
    const uint_fast8_t tmp_712 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_713 = uint_fast8_t(((~tmp_712) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_714 = uint_fast8_t((tmp_710 & tmp_713) & 1);  // basic_and
    const uint_fast8_t tmp_715 = uint_fast8_t((tmp_711 + tmp_714) & 63);  // basic_add
    const uint_fast8_t tmp_716 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_717 = uint_fast8_t(((~tmp_716) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_718 = uint_fast8_t((tmp_714 & tmp_717) & 1);  // basic_and
    const uint_fast8_t tmp_719 = uint_fast8_t((tmp_715 + tmp_718) & 63);  // basic_add
    const uint_fast8_t tmp_720 = uint_fast8_t(((arg_0 >> 4) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_721 = uint_fast8_t(((~tmp_720) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_722 = uint_fast8_t((tmp_718 & tmp_721) & 1);  // basic_and
    const uint_fast8_t tmp_723 = uint_fast8_t((tmp_719 + tmp_722) & 63);  // basic_add
    const uint_fast8_t tmp_724 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_725 = uint_fast8_t(((~tmp_724) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_726 = uint_fast8_t((tmp_722 & tmp_725) & 1);  // basic_and
    const uint_fast8_t tmp_727 = uint_fast8_t((tmp_723 + tmp_726) & 63);  // basic_add
    const uint_fast8_t tmp_728 = uint_fast8_t(((arg_0 >> 2) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_729 = uint_fast8_t(((~tmp_728) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_730 = uint_fast8_t((tmp_726 & tmp_729) & 1);  // basic_and
    const uint_fast8_t tmp_731 = uint_fast8_t((tmp_727 + tmp_730) & 63);  // basic_add
    const uint_fast8_t tmp_732 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_733 = uint_fast8_t(((~tmp_732) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_734 = uint_fast8_t((tmp_730 & tmp_733) & 1);  // basic_and
    const uint_fast8_t tmp_735 = uint_fast8_t((tmp_731 + tmp_734) & 63);  // basic_add
    const uint_fast8_t tmp_736 = uint_fast8_t(((arg_0 >> 0) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_737 = uint_fast8_t(((~tmp_736) & 1) & 1);  // basic_invert
    const uint_fast8_t tmp_738 = uint_fast8_t((tmp_734 & tmp_737) & 1);  // basic_and
    const uint_fast8_t tmp_739 = uint_fast8_t((tmp_735 + tmp_738) & 63);  // basic_add
    return tmp_739;
}
static inline uint_fast8_t uq_add_4(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast8_t tmp_741 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_742 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_743 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_741), static_cast<uint_fast64_t>(tmp_742)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast8_t tmp_744 = uint_fast8_t(tmp_743[0] & 15);  // _basic_get_item_0
    const uint_fast8_t tmp_745 = uint_fast8_t(tmp_743[1] & 15);  // _basic_get_item_1
    const uint_fast8_t tmp_746 = uint_fast8_t((tmp_744 + tmp_745) & 15);  // basic_add
    return tmp_746;
}
static inline uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_747 = uq_add_4(uint_fast8_t(6 & 7), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_748 = uint_fast8_t(0 & 127);  // q_alloc
    const uint_fast8_t tmp_749 = uint_fast8_t(arg_0 & 127);  // basic_identity
    return tmp_749;
}
static inline uint_fast8_t uq_to_q_3(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_751 = uq_add_2(uint_fast8_t(3 & 3), uint_fast8_t(1 & 1));  // uq_add
    const uint_fast8_t tmp_752 = uint_fast8_t(0 & 15);  // q_alloc
    const uint_fast8_t tmp_753 = uint_fast8_t(arg_0 & 15);  // basic_identity
    return tmp_753;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_756 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_756;
}
static inline uint_fast8_t q_sign_extend_8(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_757 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_758 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_757) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_759 = uint_fast8_t((tmp_758 - tmp_757) & 1);  // basic_sub
    const uint_fast8_t tmp_760 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_761 = uint_fast8_t(((uint_fast64_t(tmp_759) << 7) | arg_0) & 255);  // basic_concat
    return tmp_761;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_764 = uint_fast8_t(((arg_0 >> 3) & 1) & 1);  // basic_select
    return tmp_764;
}
static inline uint_fast8_t q_sign_extend_9(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_765 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_766 = uint_fast8_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_765) << uint_fast8_t(4 & 7))) & 31);  // basic_lshift
    const uint_fast8_t tmp_767 = uint_fast8_t((tmp_766 - tmp_765) & 15);  // basic_sub
    const uint_fast8_t tmp_768 = uint_fast8_t(0 & 255);  // q_alloc
    const uint_fast8_t tmp_769 = uint_fast8_t(((uint_fast64_t(tmp_767) << 4) | arg_0) & 255);  // basic_concat
    return tmp_769;
}
static inline uint_fast8_t q_sub_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_755 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast8_t tmp_762 = q_sign_extend_8(tmp_755);  // q_sign_extend
    const uint_fast8_t tmp_763 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 15);  // basic_lshift
    const uint_fast8_t tmp_770 = q_sign_extend_9(tmp_763);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_771 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_762), static_cast<uint_fast64_t>(tmp_770)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast8_t tmp_772 = uint_fast8_t(tmp_771[0] & 255);  // _basic_get_item_0
    const uint_fast8_t tmp_773 = uint_fast8_t(tmp_771[1] & 255);  // _basic_get_item_1
    const uint_fast8_t tmp_774 = uint_fast8_t((tmp_772 - tmp_773) & 255);  // basic_sub
    return tmp_774;
}
static inline uint_fast16_t q_sign_extend_10(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_777 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_778 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_777) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_779 = uint_fast8_t((tmp_778 - tmp_777) & 1);  // basic_sub
    const uint_fast16_t tmp_780 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_781 = uint_fast16_t(((uint_fast64_t(tmp_779) << 8) | arg_0) & 511);  // basic_concat
    return tmp_781;
}
static inline uint_fast8_t q_sign_bit_8(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_784 = uint_fast8_t(((arg_0 >> 1) & 1) & 1);  // basic_select
    return tmp_784;
}
static inline uint_fast16_t q_sign_extend_11(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_785 = q_sign_bit_8(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_786 = uint_fast8_t((uint_fast8_t(7 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_785) << uint_fast8_t(7 & 7))) & 255);  // basic_lshift
    const uint_fast8_t tmp_787 = uint_fast8_t((tmp_786 - tmp_785) & 127);  // basic_sub
    const uint_fast16_t tmp_788 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_789 = uint_fast16_t(((uint_fast64_t(tmp_787) << 2) | arg_0) & 511);  // basic_concat
    return tmp_789;
}
static inline uint_fast16_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_776 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 255);  // basic_lshift
    const uint_fast16_t tmp_782 = q_sign_extend_10(tmp_776);  // q_sign_extend
    const uint_fast8_t tmp_783 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 3);  // basic_lshift
    const uint_fast16_t tmp_790 = q_sign_extend_11(tmp_783);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_791 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_782), static_cast<uint_fast64_t>(tmp_790)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_792 = uint_fast16_t(tmp_791[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_793 = uint_fast16_t(tmp_791[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_794 = uint_fast16_t((tmp_792 + tmp_793) & 511);  // basic_add
    return tmp_794;
}
static inline uint_fast8_t q_sign_bit_9(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_796 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_796;
}
static inline uint_fast64_t uq_resize_2(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast64_t tmp_798 = uint_fast64_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(4 & 7))) & 1099511627775);  // basic_lshift
    return tmp_798;
}
static inline uint_fast16_t q_neg_2(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_801 = uint_fast8_t((arg_0 == 256) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_802 = uint_fast16_t(((~arg_0) & 511) & 511);  // basic_invert
    const uint_fast16_t tmp_803 = uint_fast16_t((tmp_802 + uint_fast8_t(1 & 1)) & 511);  // basic_add
    const uint_fast16_t tmp_804 = uint_fast16_t((arg_0 ^ arg_0) & 511);  // basic_xor
    const uint_fast16_t tmp_805 = uint_fast16_t(((~tmp_804) & 511) & 511);  // basic_invert
    const uint_fast16_t tmp_806 = uint_fast16_t((tmp_801 == 1 ? tmp_805 : tmp_803) & 511);  // basic_mux_2_1
    return tmp_806;
}
static inline uint_fast16_t q_add_sign_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_807 = q_neg_2(arg_0);  // q_neg
    const uint_fast16_t tmp_808 = uint_fast16_t((arg_1 == 1 ? tmp_807 : arg_0) & 511);  // basic_mux_2_1
    return tmp_808;
}
static inline uint_fast16_t q_abs_1(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_800 = q_sign_bit_9(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_809 = q_add_sign_2(arg_0, tmp_800);  // q_add_sign
    return tmp_809;
}
static inline uint_fast8_t q_to_uq_1(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_811 = uint_fast8_t(arg_0 & 255);  // basic_identity
    return tmp_811;
}
static inline uint_fast64_t uq_lshift(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast64_t tmp_813 = uint_fast64_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 1099511627775);  // basic_lshift
    return tmp_813;
}
static inline uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_815 = uint_fast64_t((arg_1 >= 40 ? 0 : (arg_0 >> arg_1)) & 1099511627775);  // basic_rshift
    return tmp_815;
}
static inline uint_fast8_t q_sign_bit_10(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_819 = uint_fast8_t(((arg_0 >> 10) & 1) & 1);  // basic_select
    return tmp_819;
}
static inline uint_fast16_t q_sign_extend_12(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_820 = q_sign_bit_10(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_821 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_820) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_822 = uint_fast8_t((tmp_821 - tmp_820) & 1);  // basic_sub
    const uint_fast16_t tmp_823 = uint_fast16_t(0 & 4095);  // q_alloc
    const uint_fast16_t tmp_824 = uint_fast16_t(((uint_fast64_t(tmp_822) << 11) | arg_0) & 4095);  // basic_concat
    return tmp_824;
}
static inline uint_fast16_t q_sign_extend_13(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_827 = q_sign_bit_9(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_828 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_827) << uint_fast8_t(3 & 3))) & 15);  // basic_lshift
    const uint_fast8_t tmp_829 = uint_fast8_t((tmp_828 - tmp_827) & 7);  // basic_sub
    const uint_fast16_t tmp_830 = uint_fast16_t(0 & 4095);  // q_alloc
    const uint_fast16_t tmp_831 = uint_fast16_t(((uint_fast64_t(tmp_829) << 9) | arg_0) & 4095);  // basic_concat
    return tmp_831;
}
static inline uint_fast16_t q_sub_2(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_818 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const uint_fast16_t tmp_825 = q_sign_extend_12(tmp_818);  // q_sign_extend
    const uint_fast16_t tmp_826 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_832 = q_sign_extend_13(tmp_826);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_833 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_825), static_cast<uint_fast64_t>(tmp_832)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_834 = uint_fast16_t(tmp_833[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_835 = uint_fast16_t(tmp_833[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_836 = uint_fast16_t((tmp_834 - tmp_835) & 4095);  // basic_sub
    return tmp_836;
}
static inline uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_838 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const uint_fast16_t tmp_839 = q_sign_extend_12(tmp_838);  // q_sign_extend
    const uint_fast16_t tmp_840 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_841 = q_sign_extend_13(tmp_840);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_842 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_839), static_cast<uint_fast64_t>(tmp_841)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_843 = uint_fast16_t(tmp_842[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_844 = uint_fast16_t(tmp_842[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_845 = uint_fast16_t((tmp_843 + tmp_844) & 4095);  // basic_add
    return tmp_845;
}
static inline uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_852 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_853 = uint_fast8_t(((~tmp_852) & 1) & 1);  // basic_invert
    return tmp_853;
}
static inline uint_fast8_t q_sign_bit_11(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_855 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    return tmp_855;
}
static inline uint_fast16_t q_neg_3(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_859 = uint_fast8_t((arg_0 == 2048) & 1);  // _q_is_min_val
    const uint_fast16_t tmp_860 = uint_fast16_t(((~arg_0) & 4095) & 4095);  // basic_invert
    const uint_fast16_t tmp_861 = uint_fast16_t((tmp_860 + uint_fast8_t(1 & 1)) & 4095);  // basic_add
    const uint_fast16_t tmp_862 = uint_fast16_t((arg_0 ^ arg_0) & 4095);  // basic_xor
    const uint_fast16_t tmp_863 = uint_fast16_t(((~tmp_862) & 4095) & 4095);  // basic_invert
    const uint_fast16_t tmp_864 = uint_fast16_t((tmp_859 == 1 ? tmp_863 : tmp_861) & 4095);  // basic_mux_2_1
    return tmp_864;
}
static inline uint_fast16_t q_add_sign_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_865 = q_neg_3(arg_0);  // q_neg
    const uint_fast16_t tmp_866 = uint_fast16_t((arg_1 == 1 ? tmp_865 : arg_0) & 4095);  // basic_mux_2_1
    return tmp_866;
}
static inline uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_858 = q_sign_bit_11(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_867 = q_add_sign_3(arg_0, tmp_858);  // q_add_sign
    return tmp_867;
}
static inline uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_869 = uint_fast16_t(arg_0 & 2047);  // basic_identity
    return tmp_869;
}
static inline uint_fast16_t uq_add_5(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_871 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_872 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_873 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_871), static_cast<uint_fast64_t>(tmp_872)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_874 = uint_fast16_t(tmp_873[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_875 = uint_fast16_t(tmp_873[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_876 = uint_fast16_t((tmp_874 + tmp_875) & 4095);  // basic_add
    return tmp_876;
}
static inline uint_fast64_t uq_rshift_3(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_879 = uint_fast64_t((arg_1 >= 46 ? 0 : (arg_0 >> arg_1)) & 70368744177663);  // basic_rshift
    return tmp_879;
}
static inline uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_884 = uint_fast64_t(((arg_0 >> 0) & 35184372088831) & 35184372088831);  // basic_select
    return tmp_884;
}
static inline uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_887 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_888 = uint_fast8_t(((~tmp_887) & 1) & 1);  // basic_invert
    return tmp_888;
}
static inline uint_fast32_t uq_resize_3(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_890 = uint_fast32_t((uint_fast8_t(22 & 31) >= 45 ? 0 : (arg_0 >> uint_fast8_t(22 & 31))) & 8388607);  // basic_rshift
    return tmp_890;
}
static inline uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_892 = uint_fast8_t(((arg_0 >> 21) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_893 = uint_fast8_t(((arg_0 >> 20) & 1) & 1);  // basic_select
    const uint_fast32_t tmp_894 = uint_fast32_t(((arg_0 >> 0) & 1048575) & 1048575);  // basic_select
    const uint_fast8_t tmp_895 = uint_fast8_t((tmp_894 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_896 = uint_fast8_t((tmp_893 | tmp_895) & 1);  // basic_or
    const uint_fast8_t tmp_897 = uint_fast8_t(((arg_0 >> 22) & 1) & 1);  // basic_select
    const uint_fast8_t tmp_898 = uint_fast8_t((tmp_896 | tmp_897) & 1);  // basic_or
    const uint_fast8_t tmp_899 = uint_fast8_t((tmp_892 & tmp_898) & 1);  // basic_and
    const uint_fast32_t tmp_900 = uint_fast32_t(tmp_899 & 8388607);  // basic_identity
    return tmp_900;
}
static inline uint_fast32_t uq_add_6(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast32_t tmp_902 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const uint_fast32_t tmp_903 = uint_fast32_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 16777215);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_904 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_902), static_cast<uint_fast64_t>(tmp_903)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast32_t tmp_905 = uint_fast32_t(tmp_904[0] & 16777215);  // _basic_get_item_0
    const uint_fast32_t tmp_906 = uint_fast32_t(tmp_904[1] & 16777215);  // _basic_get_item_1
    const uint_fast32_t tmp_907 = uint_fast32_t((tmp_905 + tmp_906) & 16777215);  // basic_add
    return tmp_907;
}
static inline uint_fast16_t uq_add_7(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_910 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_911 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_912 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_910), static_cast<uint_fast64_t>(tmp_911)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_913 = uint_fast16_t(tmp_912[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_914 = uint_fast16_t(tmp_912[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_915 = uint_fast16_t((tmp_913 + tmp_914) & 4095);  // basic_add
    return tmp_915;
}
static inline uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const uint_fast16_t tmp_925 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_926 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const std::array<uint_fast64_t, 2> tmp_927 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_925), static_cast<uint_fast64_t>(tmp_926)};  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const uint_fast16_t tmp_928 = uint_fast16_t(tmp_927[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_929 = uint_fast16_t(tmp_927[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_930 = uint_fast16_t((tmp_928 < tmp_929 ? tmp_928 : tmp_929) & 4095);  // basic_min
    return tmp_930;
}
static inline uint_fast8_t uq_is_zero_1(uint_fast64_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_937 = uint_fast8_t((arg_0 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_938 = uint_fast8_t(((~tmp_937) & 1) & 1);  // basic_invert
    return tmp_938;
}
static inline uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_945 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2) & 4294967295);  // float32_alloc
    return tmp_945;
}
static inline uint_fast32_t encode_Float32(uint_fast64_t arg_0, uint_fast16_t arg_1, uint_fast8_t arg_2) {  // encode_Float32
    const uint_fast8_t tmp_582 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast64_t tmp_593 = q_abs(arg_0);  // q_abs
    const uint_fast64_t tmp_595 = q_to_uq(tmp_593);  // q_to_uq
    // begin inline primitive fp32_normalize
    const uint_fast8_t tmp_740 = lzc(tmp_595);  // lzc
    const uint_fast8_t tmp_750 = uq_to_q_2(tmp_740);  // uq_to_q
    const uint_fast8_t tmp_754 = uq_to_q_3(uint_fast8_t(5 & 7));  // uq_to_q
    const uint_fast8_t tmp_775 = q_sub_1(tmp_750, tmp_754);  // q_sub
    const uint_fast16_t tmp_795 = q_add_1(tmp_775, uint_fast8_t(1 & 3));  // q_add
    const uint_fast8_t tmp_797 = q_sign_bit_9(tmp_795);  // q_sign_bit
    const uint_fast64_t tmp_799 = uq_resize_2(tmp_595);  // uq_resize
    const uint_fast16_t tmp_810 = q_abs_1(tmp_795);  // q_abs
    const uint_fast8_t tmp_812 = q_to_uq_1(tmp_810);  // q_to_uq
    const uint_fast64_t tmp_814 = uq_lshift(tmp_799, tmp_812);  // uq_lshift
    const uint_fast64_t tmp_816 = uq_rshift_2(tmp_799, tmp_812);  // uq_rshift
    const uint_fast64_t tmp_817 = uint_fast64_t((tmp_797 == 1 ? tmp_816 : tmp_814) & 68719476735);  // basic_mux_2_1
    const uint_fast16_t tmp_837 = q_sub_2(arg_1, tmp_810);  // q_sub
    const uint_fast16_t tmp_846 = q_add_2(arg_1, tmp_810);  // q_add
    const uint_fast16_t tmp_847 = uint_fast16_t((tmp_797 == 1 ? tmp_846 : tmp_837) & 4095);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_848 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_817), static_cast<uint_fast64_t>(tmp_847)};  // basic_tuple_maker_2
    // end inline primitive fp32_normalize
    const uint_fast64_t tmp_849 = uint_fast64_t(tmp_848[0] & 68719476735);  // _basic_get_item_0
    const uint_fast16_t tmp_850 = uint_fast16_t(tmp_848[1] & 4095);  // _basic_get_item_1
    // begin inline primitive fp32_classify
    const uint_fast64_t tmp_851 = uint_fast64_t((uint_fast8_t(10 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_849) << uint_fast8_t(10 & 15))) & 70368744177663);  // basic_lshift
    const uint_fast8_t tmp_854 = q_is_zero(tmp_850);  // q_is_zero
    const uint_fast8_t tmp_856 = q_sign_bit_11(tmp_850);  // q_sign_bit
    const uint_fast8_t tmp_857 = uint_fast8_t((tmp_854 | tmp_856) & 1);  // basic_or
    const uint_fast16_t tmp_868 = q_abs_2(tmp_850);  // q_abs
    const uint_fast16_t tmp_870 = q_to_uq_2(tmp_868);  // q_to_uq
    const uint_fast16_t tmp_877 = uq_add_5(uint_fast8_t(1 & 1), tmp_870);  // uq_add
    const uint_fast16_t tmp_878 = uint_fast16_t((tmp_857 == 1 ? tmp_877 : uint_fast8_t(0 & 1)) & 4095);  // basic_mux_2_1
    const uint_fast64_t tmp_880 = uq_rshift_3(tmp_851, tmp_878);  // uq_rshift
    const uint_fast16_t tmp_881 = uint_fast16_t((tmp_857 == 1 ? uint_fast8_t(0 & 1) : tmp_870) & 2047);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_882 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_880), static_cast<uint_fast64_t>(tmp_881)};  // basic_tuple_maker_2
    // end inline primitive fp32_classify
    const uint_fast64_t tmp_883 = uint_fast64_t(tmp_882[0] & 70368744177663);  // _basic_get_item_0
    const uint_fast64_t tmp_885 = drop_implicit_bit(tmp_883);  // drop_implicit_bit
    const uint_fast16_t tmp_886 = uint_fast16_t(tmp_882[1] & 2047);  // _basic_get_item_1
    // begin inline primitive fp32_round
    const uint_fast8_t tmp_889 = uq_is_zero(tmp_886);  // uq_is_zero
    const uint_fast32_t tmp_891 = uq_resize_3(tmp_885);  // uq_resize
    const uint_fast32_t tmp_901 = uq_RNE_IEEE(tmp_885);  // uq_RNE_IEEE
    const uint_fast32_t tmp_908 = uq_add_6(tmp_891, tmp_901);  // uq_add
    const uint_fast8_t tmp_909 = uint_fast8_t(((tmp_908 >> 23) & 1) & 1);  // basic_select
    const uint_fast16_t tmp_916 = uq_add_7(tmp_886, tmp_909);  // uq_add
    const uint_fast8_t tmp_917 = uint_fast8_t((tmp_916 != 0) & 1);  // basic_or_reduce
    const uint_fast8_t tmp_918 = uint_fast8_t((tmp_889 & tmp_917) & 1);  // basic_and
    const uint_fast32_t tmp_919 = uint_fast32_t((uint_fast8_t(1 & 1) >= 24 ? 0 : (tmp_908 >> uint_fast8_t(1 & 1))) & 8388607);  // basic_rshift
    const uint_fast32_t tmp_920 = uint_fast32_t((tmp_909 == 1 ? tmp_919 : tmp_908) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_921 = uint_fast32_t((tmp_918 == 1 ? uint_fast8_t(0 & 1) : tmp_920) & 8388607);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_922 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_921), static_cast<uint_fast64_t>(tmp_916)};  // basic_tuple_maker_2
    // end inline primitive fp32_round
    const uint_fast32_t tmp_923 = uint_fast32_t(tmp_922[0] & 8388607);  // _basic_get_item_0
    const uint_fast16_t tmp_924 = uint_fast16_t(tmp_922[1] & 4095);  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const uint_fast16_t tmp_931 = uq_min(tmp_924, uint_fast8_t(255 & 255));  // uq_min
    const uint_fast8_t tmp_932 = uint_fast8_t(tmp_931 & 255);  // basic_identity
    const uint_fast8_t tmp_933 = uint_fast8_t((tmp_932 == 255) & 1);  // basic_and_reduce
    const uint_fast32_t tmp_934 = uint_fast32_t((tmp_933 == 1 ? uint_fast8_t(0 & 1) : tmp_923) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_935 = uint_fast32_t((arg_2 == 1 ? uint_fast8_t(1 & 1) : tmp_934) & 8388607);  // basic_mux_2_1
    const uint_fast32_t tmp_936 = uint_fast32_t(tmp_935 & 8388607);  // basic_identity
    const uint_fast8_t tmp_939 = uq_is_zero_1(tmp_595);  // uq_is_zero
    const uint_fast8_t tmp_940 = uint_fast8_t((tmp_939 == 1 ? uint_fast8_t(0 & 1) : tmp_932) & 255);  // basic_mux_2_1
    const uint_fast8_t tmp_941 = uint_fast8_t((arg_2 == 1 ? uint_fast8_t(255 & 255) : tmp_940) & 255);  // basic_mux_2_1
    const std::array<uint_fast64_t, 2> tmp_942 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_936), static_cast<uint_fast64_t>(tmp_941)};  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const uint_fast8_t tmp_943 = uint_fast8_t(tmp_942[1] & 255);  // _basic_get_item_1
    const uint_fast32_t tmp_944 = uint_fast32_t(tmp_942[0] & 8388607);  // _basic_get_item_0
    const uint_fast32_t tmp_946 = fp32_pack(tmp_582, tmp_943, tmp_944);  // fp32_pack
    return tmp_946;
}
static inline uint_fast32_t Optimized_impl(uint_fast16_t arg_0, uint_fast16_t arg_1, uint_fast16_t arg_2, uint_fast16_t arg_3, uint_fast16_t arg_4, uint_fast16_t arg_5, uint_fast16_t arg_6, uint_fast16_t arg_7) {  // Optimized
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
    // begin inline primitive uq_split
    const uint_fast8_t tmp_30 = uint_fast8_t(((tmp_29 >> 0) & 3) & 3);  // basic_select
    const uint_fast8_t tmp_31 = uint_fast8_t(((tmp_29 >> 2) & 127) & 127);  // basic_select
    const std::array<uint_fast64_t, 2> tmp_32 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_30), static_cast<uint_fast64_t>(tmp_31)};  // basic_tuple_maker_2
    // end inline primitive uq_split
    const uint_fast8_t tmp_33 = uint_fast8_t(tmp_32[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_35 = est_local_shift(tmp_33);  // _est_local_shift
    const uint_fast32_t tmp_37 = uq_rshift(tmp_20, tmp_35);  // uq_rshift
    const uint_fast64_t tmp_39 = uq_resize_1(tmp_37);  // uq_resize
    const uint_fast8_t tmp_40 = uint_fast8_t(tmp_32[1] & 127);  // _basic_get_item_1
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_41 = uint_fast8_t(((arg_1 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_42 = uint_fast8_t(((arg_1 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_43 = uint_fast8_t(((arg_1 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_44 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_41), static_cast<uint_fast64_t>(tmp_42), static_cast<uint_fast64_t>(tmp_43)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_45 = uint_fast8_t(tmp_44[2] & 255);  // _basic_get_item_2
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_46 = uint_fast8_t(((arg_5 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_47 = uint_fast8_t(((arg_5 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_48 = uint_fast8_t(((arg_5 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_49 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_46), static_cast<uint_fast64_t>(tmp_47), static_cast<uint_fast64_t>(tmp_48)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_50 = uint_fast8_t(tmp_49[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_51 = uq_add(tmp_45, tmp_50);  // uq_add
    // begin inline primitive uq_split
    const uint_fast8_t tmp_52 = uint_fast8_t(((tmp_51 >> 0) & 3) & 3);  // basic_select
    const uint_fast8_t tmp_53 = uint_fast8_t(((tmp_51 >> 2) & 127) & 127);  // basic_select
    const std::array<uint_fast64_t, 2> tmp_54 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_52), static_cast<uint_fast64_t>(tmp_53)};  // basic_tuple_maker_2
    // end inline primitive uq_split
    const uint_fast8_t tmp_55 = uint_fast8_t(tmp_54[1] & 127);  // _basic_get_item_1
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_56 = uint_fast8_t(((arg_2 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_57 = uint_fast8_t(((arg_2 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_58 = uint_fast8_t(((arg_2 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_59 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_56), static_cast<uint_fast64_t>(tmp_57), static_cast<uint_fast64_t>(tmp_58)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_60 = uint_fast8_t(tmp_59[2] & 255);  // _basic_get_item_2
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_61 = uint_fast8_t(((arg_6 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_62 = uint_fast8_t(((arg_6 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_63 = uint_fast8_t(((arg_6 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_64 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_61), static_cast<uint_fast64_t>(tmp_62), static_cast<uint_fast64_t>(tmp_63)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_65 = uint_fast8_t(tmp_64[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_66 = uq_add(tmp_60, tmp_65);  // uq_add
    // begin inline primitive uq_split
    const uint_fast8_t tmp_67 = uint_fast8_t(((tmp_66 >> 0) & 3) & 3);  // basic_select
    const uint_fast8_t tmp_68 = uint_fast8_t(((tmp_66 >> 2) & 127) & 127);  // basic_select
    const std::array<uint_fast64_t, 2> tmp_69 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_67), static_cast<uint_fast64_t>(tmp_68)};  // basic_tuple_maker_2
    // end inline primitive uq_split
    const uint_fast8_t tmp_70 = uint_fast8_t(tmp_69[1] & 127);  // _basic_get_item_1
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_71 = uint_fast8_t(((arg_3 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_72 = uint_fast8_t(((arg_3 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_73 = uint_fast8_t(((arg_3 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_74 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_71), static_cast<uint_fast64_t>(tmp_72), static_cast<uint_fast64_t>(tmp_73)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_75 = uint_fast8_t(tmp_74[2] & 255);  // _basic_get_item_2
    // begin inline primitive bf16_decode
    const uint_fast8_t tmp_76 = uint_fast8_t(((arg_7 >> 15) & 1) & 1);  // _bf16_sign
    const uint_fast8_t tmp_77 = uint_fast8_t(((arg_7 >> 0) & 127) & 127);  // _bf16_mantissa
    const uint_fast8_t tmp_78 = uint_fast8_t(((arg_7 >> 7) & 255) & 255);  // _bf16_exponent
    const std::array<uint_fast64_t, 3> tmp_79 = std::array<uint_fast64_t, 3>{static_cast<uint_fast64_t>(tmp_76), static_cast<uint_fast64_t>(tmp_77), static_cast<uint_fast64_t>(tmp_78)};  // basic_tuple_maker_3
    // end inline primitive bf16_decode
    const uint_fast8_t tmp_80 = uint_fast8_t(tmp_79[2] & 255);  // _basic_get_item_2
    const uint_fast16_t tmp_81 = uq_add(tmp_75, tmp_80);  // uq_add
    // begin inline primitive uq_split
    const uint_fast8_t tmp_82 = uint_fast8_t(((tmp_81 >> 0) & 3) & 3);  // basic_select
    const uint_fast8_t tmp_83 = uint_fast8_t(((tmp_81 >> 2) & 127) & 127);  // basic_select
    const std::array<uint_fast64_t, 2> tmp_84 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_82), static_cast<uint_fast64_t>(tmp_83)};  // basic_tuple_maker_2
    // end inline primitive uq_split
    const uint_fast8_t tmp_85 = uint_fast8_t(tmp_84[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_295 = OPTIMIZED_MAX_EXP4(tmp_40, tmp_55, tmp_70, tmp_85);  // OPTIMIZED_MAX_EXP4
    const uint_fast16_t tmp_312 = est_global_shift(tmp_295, tmp_40);  // _est_global_shift
    const uint_fast64_t tmp_314 = uq_rshift_1(tmp_39, tmp_312);  // uq_rshift
    const uint_fast64_t tmp_324 = uq_to_q(tmp_314);  // uq_to_q
    const uint_fast8_t tmp_325 = uint_fast8_t(tmp_3[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_326 = uint_fast8_t(tmp_10[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_328 = sign_xor(tmp_325, tmp_326);  // sign_xor
    const uint_fast64_t tmp_337 = q_add_sign(tmp_324, tmp_328);  // q_add_sign
    const uint_fast8_t tmp_338 = uint_fast8_t(tmp_44[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_339 = add_implicit_bit(tmp_338);  // add_implicit_bit
    const uint_fast8_t tmp_340 = uint_fast8_t(tmp_49[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_341 = add_implicit_bit(tmp_340);  // add_implicit_bit
    const uint_fast16_t tmp_342 = uq_mul(tmp_339, tmp_341);  // uq_mul
    const uint_fast32_t tmp_343 = uq_resize(tmp_342);  // uq_resize
    const uint_fast8_t tmp_344 = uint_fast8_t(tmp_54[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_345 = est_local_shift(tmp_344);  // _est_local_shift
    const uint_fast32_t tmp_346 = uq_rshift(tmp_343, tmp_345);  // uq_rshift
    const uint_fast64_t tmp_347 = uq_resize_1(tmp_346);  // uq_resize
    const uint_fast16_t tmp_348 = est_global_shift(tmp_295, tmp_55);  // _est_global_shift
    const uint_fast64_t tmp_349 = uq_rshift_1(tmp_347, tmp_348);  // uq_rshift
    const uint_fast64_t tmp_350 = uq_to_q(tmp_349);  // uq_to_q
    const uint_fast8_t tmp_351 = uint_fast8_t(tmp_44[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_352 = uint_fast8_t(tmp_49[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_353 = sign_xor(tmp_351, tmp_352);  // sign_xor
    const uint_fast64_t tmp_354 = q_add_sign(tmp_350, tmp_353);  // q_add_sign
    const uint_fast8_t tmp_355 = uint_fast8_t(tmp_59[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_356 = add_implicit_bit(tmp_355);  // add_implicit_bit
    const uint_fast8_t tmp_357 = uint_fast8_t(tmp_64[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_358 = add_implicit_bit(tmp_357);  // add_implicit_bit
    const uint_fast16_t tmp_359 = uq_mul(tmp_356, tmp_358);  // uq_mul
    const uint_fast32_t tmp_360 = uq_resize(tmp_359);  // uq_resize
    const uint_fast8_t tmp_361 = uint_fast8_t(tmp_69[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_362 = est_local_shift(tmp_361);  // _est_local_shift
    const uint_fast32_t tmp_363 = uq_rshift(tmp_360, tmp_362);  // uq_rshift
    const uint_fast64_t tmp_364 = uq_resize_1(tmp_363);  // uq_resize
    const uint_fast16_t tmp_365 = est_global_shift(tmp_295, tmp_70);  // _est_global_shift
    const uint_fast64_t tmp_366 = uq_rshift_1(tmp_364, tmp_365);  // uq_rshift
    const uint_fast64_t tmp_367 = uq_to_q(tmp_366);  // uq_to_q
    const uint_fast8_t tmp_368 = uint_fast8_t(tmp_59[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_369 = uint_fast8_t(tmp_64[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_370 = sign_xor(tmp_368, tmp_369);  // sign_xor
    const uint_fast64_t tmp_371 = q_add_sign(tmp_367, tmp_370);  // q_add_sign
    const uint_fast8_t tmp_372 = uint_fast8_t(tmp_74[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_373 = add_implicit_bit(tmp_372);  // add_implicit_bit
    const uint_fast8_t tmp_374 = uint_fast8_t(tmp_79[1] & 127);  // _basic_get_item_1
    const uint_fast8_t tmp_375 = add_implicit_bit(tmp_374);  // add_implicit_bit
    const uint_fast16_t tmp_376 = uq_mul(tmp_373, tmp_375);  // uq_mul
    const uint_fast32_t tmp_377 = uq_resize(tmp_376);  // uq_resize
    const uint_fast8_t tmp_378 = uint_fast8_t(tmp_84[0] & 3);  // _basic_get_item_0
    const uint_fast8_t tmp_379 = est_local_shift(tmp_378);  // _est_local_shift
    const uint_fast32_t tmp_380 = uq_rshift(tmp_377, tmp_379);  // uq_rshift
    const uint_fast64_t tmp_381 = uq_resize_1(tmp_380);  // uq_resize
    const uint_fast16_t tmp_382 = est_global_shift(tmp_295, tmp_85);  // _est_global_shift
    const uint_fast64_t tmp_383 = uq_rshift_1(tmp_381, tmp_382);  // uq_rshift
    const uint_fast64_t tmp_384 = uq_to_q(tmp_383);  // uq_to_q
    const uint_fast8_t tmp_385 = uint_fast8_t(tmp_74[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_386 = uint_fast8_t(tmp_79[0] & 1);  // _basic_get_item_0
    const uint_fast8_t tmp_387 = sign_xor(tmp_385, tmp_386);  // sign_xor
    const uint_fast64_t tmp_388 = q_add_sign(tmp_384, tmp_387);  // q_add_sign
    const uint_fast64_t tmp_545 = CSA_tree4(tmp_337, tmp_354, tmp_371, tmp_388);  // CSA_tree4
    const uint_fast16_t tmp_549 = prepend_ones(tmp_295);  // _prepend_ones
    const uint_fast16_t tmp_559 = uq_to_q_1(tmp_549);  // uq_to_q
    const uint_fast16_t tmp_580 = q_sub(tmp_559, uint_fast8_t(127 & 255));  // q_sub
    const uint_fast32_t tmp_947 = encode_Float32(tmp_545, tmp_580, uint_fast8_t(0 & 1));  // encode_Float32
    return tmp_947;
}
extern "C" inline uint_fast32_t Optimized(uint_fast16_t arg_0, uint_fast16_t arg_1, uint_fast16_t arg_2, uint_fast16_t arg_3, uint_fast16_t arg_4, uint_fast16_t arg_5, uint_fast16_t arg_6, uint_fast16_t arg_7) {
    return Optimized_impl((arg_0 & 65535), (arg_1 & 65535), (arg_2 & 65535), (arg_3 & 65535), (arg_4 & 65535), (arg_5 & 65535), (arg_6 & 65535), (arg_7 & 65535));
}