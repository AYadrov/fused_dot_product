#pragma once
#include <cstdint>
#include <tuple>
#include <ac_uint.h>

static inline ac_uint<1> fp32_is_normal(ac_uint<32> arg_0) {  // fp32_is_normal
    const ac_uint<8> tmp = ac_uint<8>(((arg_0 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<1> tmp_1 = ac_uint<1>((tmp != 0));  // basic_or_reduce
    const ac_uint<1> tmp_2 = ac_uint<1>((tmp == 255));  // basic_and_reduce
    const ac_uint<1> tmp_3 = ac_uint<1>(((~tmp_2) & 1));  // basic_invert
    const ac_uint<1> tmp_4 = ac_uint<1>((tmp_1 & tmp_3));  // basic_and
    return tmp_4;
}
static inline ac_uint<1> fp32_is_subnormal(ac_uint<32> arg_0) {  // fp32_is_subnormal
    const ac_uint<8> tmp_6 = ac_uint<8>(((arg_0 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<1> tmp_7 = ac_uint<1>((tmp_6 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_8 = ac_uint<1>(((~tmp_7) & 1));  // basic_invert
    const ac_uint<23> tmp_9 = ac_uint<23>((arg_0 & ((1 << 23) - 1)));  // _fp32_mantissa
    const ac_uint<1> tmp_10 = ac_uint<1>((tmp_9 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_11 = ac_uint<1>((tmp_8 & tmp_10));  // basic_and
    return tmp_11;
}
static inline ac_uint<1> fp32_is_zero(ac_uint<32> arg_0) {  // fp32_is_zero
    const ac_uint<8> tmp_13 = ac_uint<8>(((arg_0 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<1> tmp_14 = ac_uint<1>((tmp_13 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_15 = ac_uint<1>(((~tmp_14) & 1));  // basic_invert
    const ac_uint<23> tmp_16 = ac_uint<23>((arg_0 & ((1 << 23) - 1)));  // _fp32_mantissa
    const ac_uint<1> tmp_17 = ac_uint<1>((tmp_16 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_18 = ac_uint<1>(((~tmp_17) & 1));  // basic_invert
    const ac_uint<1> tmp_19 = ac_uint<1>((tmp_15 & tmp_18));  // basic_and
    return tmp_19;
}
static inline ac_uint<1> fp32_is_inf(ac_uint<32> arg_0) {  // fp32_is_inf
    const ac_uint<8> tmp_21 = ac_uint<8>(((arg_0 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<1> tmp_22 = ac_uint<1>((tmp_21 == 255));  // basic_and_reduce
    const ac_uint<23> tmp_23 = ac_uint<23>((arg_0 & ((1 << 23) - 1)));  // _fp32_mantissa
    const ac_uint<1> tmp_24 = ac_uint<1>((tmp_23 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_25 = ac_uint<1>(((~tmp_24) & 1));  // basic_invert
    const ac_uint<1> tmp_26 = ac_uint<1>((tmp_22 & tmp_25));  // basic_and
    return tmp_26;
}
static inline ac_uint<1> fp32_is_nan(ac_uint<32> arg_0) {  // fp32_is_nan
    const ac_uint<8> tmp_28 = ac_uint<8>(((arg_0 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<1> tmp_29 = ac_uint<1>((tmp_28 == 255));  // basic_and_reduce
    const ac_uint<23> tmp_30 = ac_uint<23>((arg_0 & ((1 << 23) - 1)));  // _fp32_mantissa
    const ac_uint<1> tmp_31 = ac_uint<1>((tmp_30 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_32 = ac_uint<1>((tmp_29 & tmp_31));  // basic_and
    return tmp_32;
}
static inline ac_uint<24> add_implicit_bit(ac_uint<23> arg_0) {  // add_implicit_bit
    const ac_uint<24> tmp_59 = ac_uint<24>(((ac_uint<24>(ac_uint<1>(1)) << 23) | arg_0));  // basic_concat
    return tmp_59;
}
static inline ac_uint<24> uq_resize(ac_uint<23> arg_0) {  // uq_resize
    const ac_uint<24> tmp_61 = ac_uint<24>(arg_0);  // basic_identity
    return tmp_61;
}
static inline ac_uint<27> uq_resize_1(ac_uint<24> arg_0) {  // uq_resize
    const ac_uint<27> tmp_64 = ac_uint<27>((ac_uint<2>(3) >= 27 ? 0 : (ac_uint<27>(arg_0) << ac_uint<2>(3))));  // basic_lshift
    return tmp_64;
}
static inline ac_uint<8> uq_max(ac_uint<8> arg_0, ac_uint<8> arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const std::tuple<ac_uint<8>, ac_uint<8>> tmp_72 = std::make_tuple(arg_0, arg_1);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<8> tmp_73 = ac_uint<8>(std::get<0>(tmp_72));  // _basic_get_item_0
    const ac_uint<8> tmp_74 = ac_uint<8>(std::get<1>(tmp_72));  // _basic_get_item_1
    const ac_uint<8> tmp_75 = ac_uint<8>((tmp_73 > tmp_74 ? tmp_73 : tmp_74));  // basic_max
    return tmp_75;
}
static inline ac_uint<9> uq_sub(ac_uint<8> arg_0, ac_uint<8> arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const ac_uint<9> tmp_77 = ac_uint<9>(arg_0);  // basic_identity
    const ac_uint<9> tmp_78 = ac_uint<9>(arg_1);  // basic_identity
    const std::tuple<ac_uint<9>, ac_uint<9>> tmp_79 = std::make_tuple(tmp_77, tmp_78);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<9> tmp_80 = ac_uint<9>(std::get<0>(tmp_79));  // _basic_get_item_0
    const ac_uint<9> tmp_81 = ac_uint<9>(std::get<1>(tmp_79));  // _basic_get_item_1
    const ac_uint<9> tmp_82 = ac_uint<9>((ac_uint<9>(tmp_80) - ac_uint<9>(tmp_81)));  // basic_sub
    return tmp_82;
}
static inline ac_uint<27> uq_rshift(ac_uint<27> arg_0, ac_uint<9> arg_1) {  // uq_rshift
    const ac_uint<27> tmp_84 = ac_uint<27>((arg_1 >= 27 ? 0 : (arg_0 >> arg_1)));  // basic_rshift
    return tmp_84;
}
static inline ac_uint<1> uq_is_zero(ac_uint<9> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_86 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_87 = ac_uint<1>(((~tmp_86) & 1));  // basic_invert
    return tmp_87;
}
static inline ac_uint<1> uq_ge(ac_uint<9> arg_0, ac_uint<5> arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const ac_uint<9> tmp_89 = ac_uint<9>(arg_1);  // basic_identity
    const std::tuple<ac_uint<9>, ac_uint<9>> tmp_90 = std::make_tuple(arg_0, tmp_89);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<9> tmp_91 = ac_uint<9>(std::get<0>(tmp_90));  // _basic_get_item_0
    const ac_uint<9> tmp_92 = ac_uint<9>(std::get<1>(tmp_90));  // _basic_get_item_1
    const ac_uint<1> tmp_93 = ac_uint<1>((tmp_91 >= tmp_92));  // basic_greater_or_equal
    return tmp_93;
}
static inline ac_uint<10> uq_sub_1(ac_uint<5> arg_0, ac_uint<9> arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_95 = ac_uint<10>(arg_0);  // basic_identity
    const ac_uint<10> tmp_96 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_97 = std::make_tuple(tmp_95, tmp_96);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_98 = ac_uint<10>(std::get<0>(tmp_97));  // _basic_get_item_0
    const ac_uint<10> tmp_99 = ac_uint<10>(std::get<1>(tmp_97));  // _basic_get_item_1
    const ac_uint<10> tmp_100 = ac_uint<10>((ac_uint<10>(tmp_98) - ac_uint<10>(tmp_99)));  // basic_sub
    return tmp_100;
}
static inline ac_uint<27> uq_rshift_jam(ac_uint<27> arg_0, ac_uint<9> arg_1) {  // uq_rshift_jam
    const ac_uint<27> tmp_85 = uq_rshift(arg_0, arg_1);  // uq_rshift
    const ac_uint<1> tmp_88 = uq_is_zero(arg_1);  // uq_is_zero
    const ac_uint<1> tmp_94 = uq_ge(arg_1, ac_uint<5>(27));  // uq_ge
    const ac_uint<10> tmp_101 = uq_sub_1(ac_uint<5>(27), arg_1);  // uq_sub
    const ac_uint<27> tmp_102 = ac_uint<27>((tmp_101 >= 27 ? 0 : (ac_uint<27>(arg_0) << tmp_101)));  // basic_lshift
    const ac_uint<1> tmp_103 = ac_uint<1>((tmp_102 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_104 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_105 = ac_uint<1>((tmp_94 != 0 ? tmp_104 : tmp_103));  // basic_mux_2_1
    const ac_uint<1> tmp_106 = ac_uint<1>((tmp_88 != 0 ? ac_uint<1>(0) : tmp_105));  // basic_mux_2_1
    const ac_uint<27> tmp_107 = ac_uint<27>((tmp_85 | tmp_106));  // basic_or
    return tmp_107;
}
static inline ac_uint<2> uq_add(ac_uint<1> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<2> tmp_109 = ac_uint<2>(arg_0);  // basic_identity
    const ac_uint<2> tmp_110 = ac_uint<2>(arg_1);  // basic_identity
    const std::tuple<ac_uint<2>, ac_uint<2>> tmp_111 = std::make_tuple(tmp_109, tmp_110);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<2> tmp_112 = ac_uint<2>(std::get<0>(tmp_111));  // _basic_get_item_0
    const ac_uint<2> tmp_113 = ac_uint<2>(std::get<1>(tmp_111));  // _basic_get_item_1
    const ac_uint<2> tmp_114 = ac_uint<2>((ac_uint<2>(tmp_112) + ac_uint<2>(tmp_113)));  // basic_add
    return tmp_114;
}
static inline ac_uint<28> uq_to_q(ac_uint<27> arg_0) {  // uq_to_q
    const ac_uint<2> tmp_115 = uq_add(ac_uint<1>(1), ac_uint<1>(1));  // uq_add
    const ac_uint<28> tmp_116 = ac_uint<28>(0);  // q_alloc
    const ac_uint<28> tmp_117 = ac_uint<28>(arg_0);  // basic_identity
    return tmp_117;
}
static inline ac_uint<28> q_neg(ac_uint<28> arg_0) {  // q_neg
    const ac_uint<1> tmp_119 = ac_uint<1>((arg_0 == 134217728));  // _q_is_min_val
    const ac_uint<28> tmp_120 = ac_uint<28>(((~arg_0) & 268435455));  // basic_invert
    const ac_uint<28> tmp_121 = ac_uint<28>((ac_uint<28>(tmp_120) + ac_uint<28>(ac_uint<1>(1))));  // basic_add
    const ac_uint<28> tmp_122 = ac_uint<28>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<28> tmp_123 = ac_uint<28>(((~tmp_122) & 268435455));  // basic_invert
    const ac_uint<28> tmp_124 = ac_uint<28>((tmp_119 != 0 ? tmp_123 : tmp_121));  // basic_mux_2_1
    return tmp_124;
}
static inline ac_uint<28> q_add_sign(ac_uint<28> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<28> tmp_125 = q_neg(arg_0);  // q_neg
    const ac_uint<28> tmp_126 = ac_uint<28>((arg_1 != 0 ? tmp_125 : arg_0));  // basic_mux_2_1
    return tmp_126;
}
static inline ac_uint<1> q_sign_bit(ac_uint<28> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_140 = ac_uint<1>(((arg_0 >> 27) & 1));  // basic_select
    return tmp_140;
}
static inline ac_uint<29> q_sign_extend(ac_uint<28> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_141 = q_sign_bit(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_142 = ac_uint<2>((ac_uint<1>(1) >= 2 ? 0 : (ac_uint<2>(tmp_141) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_143 = ac_uint<1>((ac_uint<1>(tmp_142) - ac_uint<1>(tmp_141)));  // basic_sub
    const ac_uint<29> tmp_144 = ac_uint<29>(0);  // q_alloc
    const ac_uint<29> tmp_145 = ac_uint<29>(((ac_uint<29>(tmp_143) << 28) | arg_0));  // basic_concat
    return tmp_145;
}
static inline ac_uint<29> q_add(ac_uint<28> arg_0, ac_uint<28> arg_1) {  // q_add
    // begin inline primitive q_aligner
    const ac_uint<28> tmp_139 = ac_uint<28>((ac_uint<1>(0) >= 28 ? 0 : (ac_uint<28>(arg_0) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<29> tmp_146 = q_sign_extend(tmp_139);  // q_sign_extend
    const ac_uint<28> tmp_147 = ac_uint<28>((ac_uint<1>(0) >= 28 ? 0 : (ac_uint<28>(arg_1) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<29> tmp_148 = q_sign_extend(tmp_147);  // q_sign_extend
    const std::tuple<ac_uint<29>, ac_uint<29>> tmp_149 = std::make_tuple(tmp_146, tmp_148);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<29> tmp_150 = ac_uint<29>(std::get<0>(tmp_149));  // _basic_get_item_0
    const ac_uint<29> tmp_151 = ac_uint<29>(std::get<1>(tmp_149));  // _basic_get_item_1
    const ac_uint<29> tmp_152 = ac_uint<29>((ac_uint<29>(tmp_150) + ac_uint<29>(tmp_151)));  // basic_add
    return tmp_152;
}
static inline ac_uint<1> q_sign_bit_1(ac_uint<29> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_154 = ac_uint<1>(((arg_0 >> 28) & 1));  // basic_select
    return tmp_154;
}
static inline ac_uint<5> uq_add_1(ac_uint<4> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<5> tmp_157 = ac_uint<5>(arg_0);  // basic_identity
    const ac_uint<5> tmp_158 = ac_uint<5>(arg_1);  // basic_identity
    const std::tuple<ac_uint<5>, ac_uint<5>> tmp_159 = std::make_tuple(tmp_157, tmp_158);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<5> tmp_160 = ac_uint<5>(std::get<0>(tmp_159));  // _basic_get_item_0
    const ac_uint<5> tmp_161 = ac_uint<5>(std::get<1>(tmp_159));  // _basic_get_item_1
    const ac_uint<5> tmp_162 = ac_uint<5>((ac_uint<5>(tmp_160) + ac_uint<5>(tmp_161)));  // basic_add
    return tmp_162;
}
static inline ac_uint<9> uq_to_q_1(ac_uint<8> arg_0) {  // uq_to_q
    const ac_uint<5> tmp_163 = uq_add_1(ac_uint<4>(8), ac_uint<1>(1));  // uq_add
    const ac_uint<9> tmp_164 = ac_uint<9>(0);  // q_alloc
    const ac_uint<9> tmp_165 = ac_uint<9>(arg_0);  // basic_identity
    return tmp_165;
}
static inline ac_uint<29> q_neg_1(ac_uint<29> arg_0) {  // q_neg
    const ac_uint<1> tmp_168 = ac_uint<1>((arg_0 == 268435456));  // _q_is_min_val
    const ac_uint<29> tmp_169 = ac_uint<29>(((~arg_0) & 536870911));  // basic_invert
    const ac_uint<29> tmp_170 = ac_uint<29>((ac_uint<29>(tmp_169) + ac_uint<29>(ac_uint<1>(1))));  // basic_add
    const ac_uint<29> tmp_171 = ac_uint<29>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<29> tmp_172 = ac_uint<29>(((~tmp_171) & 536870911));  // basic_invert
    const ac_uint<29> tmp_173 = ac_uint<29>((tmp_168 != 0 ? tmp_172 : tmp_170));  // basic_mux_2_1
    return tmp_173;
}
static inline ac_uint<29> q_add_sign_1(ac_uint<29> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<29> tmp_174 = q_neg_1(arg_0);  // q_neg
    const ac_uint<29> tmp_175 = ac_uint<29>((arg_1 != 0 ? tmp_174 : arg_0));  // basic_mux_2_1
    return tmp_175;
}
static inline ac_uint<29> q_abs(ac_uint<29> arg_0) {  // q_abs
    const ac_uint<1> tmp_167 = q_sign_bit_1(arg_0);  // q_sign_bit
    const ac_uint<29> tmp_176 = q_add_sign_1(arg_0, tmp_167);  // q_add_sign
    return tmp_176;
}
static inline ac_uint<28> q_to_uq(ac_uint<29> arg_0) {  // q_to_uq
    const ac_uint<28> tmp_178 = ac_uint<28>(arg_0);  // basic_identity
    return tmp_178;
}
static inline ac_uint<1> uq_is_zero_1(ac_uint<28> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_193 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_194 = ac_uint<1>(((~tmp_193) & 1));  // basic_invert
    return tmp_194;
}
static inline ac_uint<5> lzc(ac_uint<28> arg_0) {  // lzc
    const ac_uint<1> tmp_197 = ac_uint<1>(((arg_0 >> 27) & 1));  // basic_select
    const ac_uint<1> tmp_198 = ac_uint<1>(((~tmp_197) & 1));  // basic_invert
    const ac_uint<1> tmp_199 = ac_uint<1>((ac_uint<1>(1) & tmp_198));  // basic_and
    const ac_uint<5> tmp_200 = ac_uint<5>((ac_uint<5>(ac_uint<5>(0)) + ac_uint<5>(tmp_199)));  // basic_add
    const ac_uint<1> tmp_201 = ac_uint<1>(((arg_0 >> 26) & 1));  // basic_select
    const ac_uint<1> tmp_202 = ac_uint<1>(((~tmp_201) & 1));  // basic_invert
    const ac_uint<1> tmp_203 = ac_uint<1>((tmp_199 & tmp_202));  // basic_and
    const ac_uint<5> tmp_204 = ac_uint<5>((ac_uint<5>(tmp_200) + ac_uint<5>(tmp_203)));  // basic_add
    const ac_uint<1> tmp_205 = ac_uint<1>(((arg_0 >> 25) & 1));  // basic_select
    const ac_uint<1> tmp_206 = ac_uint<1>(((~tmp_205) & 1));  // basic_invert
    const ac_uint<1> tmp_207 = ac_uint<1>((tmp_203 & tmp_206));  // basic_and
    const ac_uint<5> tmp_208 = ac_uint<5>((ac_uint<5>(tmp_204) + ac_uint<5>(tmp_207)));  // basic_add
    const ac_uint<1> tmp_209 = ac_uint<1>(((arg_0 >> 24) & 1));  // basic_select
    const ac_uint<1> tmp_210 = ac_uint<1>(((~tmp_209) & 1));  // basic_invert
    const ac_uint<1> tmp_211 = ac_uint<1>((tmp_207 & tmp_210));  // basic_and
    const ac_uint<5> tmp_212 = ac_uint<5>((ac_uint<5>(tmp_208) + ac_uint<5>(tmp_211)));  // basic_add
    const ac_uint<1> tmp_213 = ac_uint<1>(((arg_0 >> 23) & 1));  // basic_select
    const ac_uint<1> tmp_214 = ac_uint<1>(((~tmp_213) & 1));  // basic_invert
    const ac_uint<1> tmp_215 = ac_uint<1>((tmp_211 & tmp_214));  // basic_and
    const ac_uint<5> tmp_216 = ac_uint<5>((ac_uint<5>(tmp_212) + ac_uint<5>(tmp_215)));  // basic_add
    const ac_uint<1> tmp_217 = ac_uint<1>(((arg_0 >> 22) & 1));  // basic_select
    const ac_uint<1> tmp_218 = ac_uint<1>(((~tmp_217) & 1));  // basic_invert
    const ac_uint<1> tmp_219 = ac_uint<1>((tmp_215 & tmp_218));  // basic_and
    const ac_uint<5> tmp_220 = ac_uint<5>((ac_uint<5>(tmp_216) + ac_uint<5>(tmp_219)));  // basic_add
    const ac_uint<1> tmp_221 = ac_uint<1>(((arg_0 >> 21) & 1));  // basic_select
    const ac_uint<1> tmp_222 = ac_uint<1>(((~tmp_221) & 1));  // basic_invert
    const ac_uint<1> tmp_223 = ac_uint<1>((tmp_219 & tmp_222));  // basic_and
    const ac_uint<5> tmp_224 = ac_uint<5>((ac_uint<5>(tmp_220) + ac_uint<5>(tmp_223)));  // basic_add
    const ac_uint<1> tmp_225 = ac_uint<1>(((arg_0 >> 20) & 1));  // basic_select
    const ac_uint<1> tmp_226 = ac_uint<1>(((~tmp_225) & 1));  // basic_invert
    const ac_uint<1> tmp_227 = ac_uint<1>((tmp_223 & tmp_226));  // basic_and
    const ac_uint<5> tmp_228 = ac_uint<5>((ac_uint<5>(tmp_224) + ac_uint<5>(tmp_227)));  // basic_add
    const ac_uint<1> tmp_229 = ac_uint<1>(((arg_0 >> 19) & 1));  // basic_select
    const ac_uint<1> tmp_230 = ac_uint<1>(((~tmp_229) & 1));  // basic_invert
    const ac_uint<1> tmp_231 = ac_uint<1>((tmp_227 & tmp_230));  // basic_and
    const ac_uint<5> tmp_232 = ac_uint<5>((ac_uint<5>(tmp_228) + ac_uint<5>(tmp_231)));  // basic_add
    const ac_uint<1> tmp_233 = ac_uint<1>(((arg_0 >> 18) & 1));  // basic_select
    const ac_uint<1> tmp_234 = ac_uint<1>(((~tmp_233) & 1));  // basic_invert
    const ac_uint<1> tmp_235 = ac_uint<1>((tmp_231 & tmp_234));  // basic_and
    const ac_uint<5> tmp_236 = ac_uint<5>((ac_uint<5>(tmp_232) + ac_uint<5>(tmp_235)));  // basic_add
    const ac_uint<1> tmp_237 = ac_uint<1>(((arg_0 >> 17) & 1));  // basic_select
    const ac_uint<1> tmp_238 = ac_uint<1>(((~tmp_237) & 1));  // basic_invert
    const ac_uint<1> tmp_239 = ac_uint<1>((tmp_235 & tmp_238));  // basic_and
    const ac_uint<5> tmp_240 = ac_uint<5>((ac_uint<5>(tmp_236) + ac_uint<5>(tmp_239)));  // basic_add
    const ac_uint<1> tmp_241 = ac_uint<1>(((arg_0 >> 16) & 1));  // basic_select
    const ac_uint<1> tmp_242 = ac_uint<1>(((~tmp_241) & 1));  // basic_invert
    const ac_uint<1> tmp_243 = ac_uint<1>((tmp_239 & tmp_242));  // basic_and
    const ac_uint<5> tmp_244 = ac_uint<5>((ac_uint<5>(tmp_240) + ac_uint<5>(tmp_243)));  // basic_add
    const ac_uint<1> tmp_245 = ac_uint<1>(((arg_0 >> 15) & 1));  // basic_select
    const ac_uint<1> tmp_246 = ac_uint<1>(((~tmp_245) & 1));  // basic_invert
    const ac_uint<1> tmp_247 = ac_uint<1>((tmp_243 & tmp_246));  // basic_and
    const ac_uint<5> tmp_248 = ac_uint<5>((ac_uint<5>(tmp_244) + ac_uint<5>(tmp_247)));  // basic_add
    const ac_uint<1> tmp_249 = ac_uint<1>(((arg_0 >> 14) & 1));  // basic_select
    const ac_uint<1> tmp_250 = ac_uint<1>(((~tmp_249) & 1));  // basic_invert
    const ac_uint<1> tmp_251 = ac_uint<1>((tmp_247 & tmp_250));  // basic_and
    const ac_uint<5> tmp_252 = ac_uint<5>((ac_uint<5>(tmp_248) + ac_uint<5>(tmp_251)));  // basic_add
    const ac_uint<1> tmp_253 = ac_uint<1>(((arg_0 >> 13) & 1));  // basic_select
    const ac_uint<1> tmp_254 = ac_uint<1>(((~tmp_253) & 1));  // basic_invert
    const ac_uint<1> tmp_255 = ac_uint<1>((tmp_251 & tmp_254));  // basic_and
    const ac_uint<5> tmp_256 = ac_uint<5>((ac_uint<5>(tmp_252) + ac_uint<5>(tmp_255)));  // basic_add
    const ac_uint<1> tmp_257 = ac_uint<1>(((arg_0 >> 12) & 1));  // basic_select
    const ac_uint<1> tmp_258 = ac_uint<1>(((~tmp_257) & 1));  // basic_invert
    const ac_uint<1> tmp_259 = ac_uint<1>((tmp_255 & tmp_258));  // basic_and
    const ac_uint<5> tmp_260 = ac_uint<5>((ac_uint<5>(tmp_256) + ac_uint<5>(tmp_259)));  // basic_add
    const ac_uint<1> tmp_261 = ac_uint<1>(((arg_0 >> 11) & 1));  // basic_select
    const ac_uint<1> tmp_262 = ac_uint<1>(((~tmp_261) & 1));  // basic_invert
    const ac_uint<1> tmp_263 = ac_uint<1>((tmp_259 & tmp_262));  // basic_and
    const ac_uint<5> tmp_264 = ac_uint<5>((ac_uint<5>(tmp_260) + ac_uint<5>(tmp_263)));  // basic_add
    const ac_uint<1> tmp_265 = ac_uint<1>(((arg_0 >> 10) & 1));  // basic_select
    const ac_uint<1> tmp_266 = ac_uint<1>(((~tmp_265) & 1));  // basic_invert
    const ac_uint<1> tmp_267 = ac_uint<1>((tmp_263 & tmp_266));  // basic_and
    const ac_uint<5> tmp_268 = ac_uint<5>((ac_uint<5>(tmp_264) + ac_uint<5>(tmp_267)));  // basic_add
    const ac_uint<1> tmp_269 = ac_uint<1>(((arg_0 >> 9) & 1));  // basic_select
    const ac_uint<1> tmp_270 = ac_uint<1>(((~tmp_269) & 1));  // basic_invert
    const ac_uint<1> tmp_271 = ac_uint<1>((tmp_267 & tmp_270));  // basic_and
    const ac_uint<5> tmp_272 = ac_uint<5>((ac_uint<5>(tmp_268) + ac_uint<5>(tmp_271)));  // basic_add
    const ac_uint<1> tmp_273 = ac_uint<1>(((arg_0 >> 8) & 1));  // basic_select
    const ac_uint<1> tmp_274 = ac_uint<1>(((~tmp_273) & 1));  // basic_invert
    const ac_uint<1> tmp_275 = ac_uint<1>((tmp_271 & tmp_274));  // basic_and
    const ac_uint<5> tmp_276 = ac_uint<5>((ac_uint<5>(tmp_272) + ac_uint<5>(tmp_275)));  // basic_add
    const ac_uint<1> tmp_277 = ac_uint<1>(((arg_0 >> 7) & 1));  // basic_select
    const ac_uint<1> tmp_278 = ac_uint<1>(((~tmp_277) & 1));  // basic_invert
    const ac_uint<1> tmp_279 = ac_uint<1>((tmp_275 & tmp_278));  // basic_and
    const ac_uint<5> tmp_280 = ac_uint<5>((ac_uint<5>(tmp_276) + ac_uint<5>(tmp_279)));  // basic_add
    const ac_uint<1> tmp_281 = ac_uint<1>(((arg_0 >> 6) & 1));  // basic_select
    const ac_uint<1> tmp_282 = ac_uint<1>(((~tmp_281) & 1));  // basic_invert
    const ac_uint<1> tmp_283 = ac_uint<1>((tmp_279 & tmp_282));  // basic_and
    const ac_uint<5> tmp_284 = ac_uint<5>((ac_uint<5>(tmp_280) + ac_uint<5>(tmp_283)));  // basic_add
    const ac_uint<1> tmp_285 = ac_uint<1>(((arg_0 >> 5) & 1));  // basic_select
    const ac_uint<1> tmp_286 = ac_uint<1>(((~tmp_285) & 1));  // basic_invert
    const ac_uint<1> tmp_287 = ac_uint<1>((tmp_283 & tmp_286));  // basic_and
    const ac_uint<5> tmp_288 = ac_uint<5>((ac_uint<5>(tmp_284) + ac_uint<5>(tmp_287)));  // basic_add
    const ac_uint<1> tmp_289 = ac_uint<1>(((arg_0 >> 4) & 1));  // basic_select
    const ac_uint<1> tmp_290 = ac_uint<1>(((~tmp_289) & 1));  // basic_invert
    const ac_uint<1> tmp_291 = ac_uint<1>((tmp_287 & tmp_290));  // basic_and
    const ac_uint<5> tmp_292 = ac_uint<5>((ac_uint<5>(tmp_288) + ac_uint<5>(tmp_291)));  // basic_add
    const ac_uint<1> tmp_293 = ac_uint<1>(((arg_0 >> 3) & 1));  // basic_select
    const ac_uint<1> tmp_294 = ac_uint<1>(((~tmp_293) & 1));  // basic_invert
    const ac_uint<1> tmp_295 = ac_uint<1>((tmp_291 & tmp_294));  // basic_and
    const ac_uint<5> tmp_296 = ac_uint<5>((ac_uint<5>(tmp_292) + ac_uint<5>(tmp_295)));  // basic_add
    const ac_uint<1> tmp_297 = ac_uint<1>(((arg_0 >> 2) & 1));  // basic_select
    const ac_uint<1> tmp_298 = ac_uint<1>(((~tmp_297) & 1));  // basic_invert
    const ac_uint<1> tmp_299 = ac_uint<1>((tmp_295 & tmp_298));  // basic_and
    const ac_uint<5> tmp_300 = ac_uint<5>((ac_uint<5>(tmp_296) + ac_uint<5>(tmp_299)));  // basic_add
    const ac_uint<1> tmp_301 = ac_uint<1>(((arg_0 >> 1) & 1));  // basic_select
    const ac_uint<1> tmp_302 = ac_uint<1>(((~tmp_301) & 1));  // basic_invert
    const ac_uint<1> tmp_303 = ac_uint<1>((tmp_299 & tmp_302));  // basic_and
    const ac_uint<5> tmp_304 = ac_uint<5>((ac_uint<5>(tmp_300) + ac_uint<5>(tmp_303)));  // basic_add
    const ac_uint<1> tmp_305 = ac_uint<1>(((arg_0 >> 0) & 1));  // basic_select
    const ac_uint<1> tmp_306 = ac_uint<1>(((~tmp_305) & 1));  // basic_invert
    const ac_uint<1> tmp_307 = ac_uint<1>((tmp_303 & tmp_306));  // basic_and
    const ac_uint<5> tmp_308 = ac_uint<5>((ac_uint<5>(tmp_304) + ac_uint<5>(tmp_307)));  // basic_add
    return tmp_308;
}
static inline ac_uint<4> uq_add_2(ac_uint<3> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<4> tmp_310 = ac_uint<4>(arg_0);  // basic_identity
    const ac_uint<4> tmp_311 = ac_uint<4>(arg_1);  // basic_identity
    const std::tuple<ac_uint<4>, ac_uint<4>> tmp_312 = std::make_tuple(tmp_310, tmp_311);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<4> tmp_313 = ac_uint<4>(std::get<0>(tmp_312));  // _basic_get_item_0
    const ac_uint<4> tmp_314 = ac_uint<4>(std::get<1>(tmp_312));  // _basic_get_item_1
    const ac_uint<4> tmp_315 = ac_uint<4>((ac_uint<4>(tmp_313) + ac_uint<4>(tmp_314)));  // basic_add
    return tmp_315;
}
static inline ac_uint<6> uq_to_q_2(ac_uint<5> arg_0) {  // uq_to_q
    const ac_uint<4> tmp_316 = uq_add_2(ac_uint<3>(5), ac_uint<1>(1));  // uq_add
    const ac_uint<6> tmp_317 = ac_uint<6>(0);  // q_alloc
    const ac_uint<6> tmp_318 = ac_uint<6>(arg_0);  // basic_identity
    return tmp_318;
}
static inline ac_uint<3> uq_add_3(ac_uint<2> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<3> tmp_320 = ac_uint<3>(arg_0);  // basic_identity
    const ac_uint<3> tmp_321 = ac_uint<3>(arg_1);  // basic_identity
    const std::tuple<ac_uint<3>, ac_uint<3>> tmp_322 = std::make_tuple(tmp_320, tmp_321);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<3> tmp_323 = ac_uint<3>(std::get<0>(tmp_322));  // _basic_get_item_0
    const ac_uint<3> tmp_324 = ac_uint<3>(std::get<1>(tmp_322));  // _basic_get_item_1
    const ac_uint<3> tmp_325 = ac_uint<3>((ac_uint<3>(tmp_323) + ac_uint<3>(tmp_324)));  // basic_add
    return tmp_325;
}
static inline ac_uint<3> uq_to_q_3(ac_uint<2> arg_0) {  // uq_to_q
    const ac_uint<3> tmp_326 = uq_add_3(ac_uint<2>(2), ac_uint<1>(1));  // uq_add
    const ac_uint<3> tmp_327 = ac_uint<3>(0);  // q_alloc
    const ac_uint<3> tmp_328 = ac_uint<3>(arg_0);  // basic_identity
    return tmp_328;
}
static inline ac_uint<1> q_sign_bit_2(ac_uint<6> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_331 = ac_uint<1>(((arg_0 >> 5) & 1));  // basic_select
    return tmp_331;
}
static inline ac_uint<7> q_sign_extend_1(ac_uint<6> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_332 = q_sign_bit_2(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_333 = ac_uint<2>((ac_uint<1>(1) >= 2 ? 0 : (ac_uint<2>(tmp_332) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_334 = ac_uint<1>((ac_uint<1>(tmp_333) - ac_uint<1>(tmp_332)));  // basic_sub
    const ac_uint<7> tmp_335 = ac_uint<7>(0);  // q_alloc
    const ac_uint<7> tmp_336 = ac_uint<7>(((ac_uint<7>(tmp_334) << 6) | arg_0));  // basic_concat
    return tmp_336;
}
static inline ac_uint<1> q_sign_bit_3(ac_uint<3> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_339 = ac_uint<1>(((arg_0 >> 2) & 1));  // basic_select
    return tmp_339;
}
static inline ac_uint<7> q_sign_extend_2(ac_uint<3> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_340 = q_sign_bit_3(arg_0);  // q_sign_bit
    const ac_uint<5> tmp_341 = ac_uint<5>((ac_uint<3>(4) >= 5 ? 0 : (ac_uint<5>(tmp_340) << ac_uint<3>(4))));  // basic_lshift
    const ac_uint<4> tmp_342 = ac_uint<4>((ac_uint<4>(tmp_341) - ac_uint<4>(tmp_340)));  // basic_sub
    const ac_uint<7> tmp_343 = ac_uint<7>(0);  // q_alloc
    const ac_uint<7> tmp_344 = ac_uint<7>(((ac_uint<7>(tmp_342) << 3) | arg_0));  // basic_concat
    return tmp_344;
}
static inline ac_uint<7> q_sub(ac_uint<6> arg_0, ac_uint<3> arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const ac_uint<6> tmp_330 = ac_uint<6>((ac_uint<1>(0) >= 6 ? 0 : (ac_uint<6>(arg_0) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<7> tmp_337 = q_sign_extend_1(tmp_330);  // q_sign_extend
    const ac_uint<3> tmp_338 = ac_uint<3>((ac_uint<1>(0) >= 3 ? 0 : (ac_uint<3>(arg_1) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<7> tmp_345 = q_sign_extend_2(tmp_338);  // q_sign_extend
    const std::tuple<ac_uint<7>, ac_uint<7>> tmp_346 = std::make_tuple(tmp_337, tmp_345);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<7> tmp_347 = ac_uint<7>(std::get<0>(tmp_346));  // _basic_get_item_0
    const ac_uint<7> tmp_348 = ac_uint<7>(std::get<1>(tmp_346));  // _basic_get_item_1
    const ac_uint<7> tmp_349 = ac_uint<7>((ac_uint<7>(tmp_347) - ac_uint<7>(tmp_348)));  // basic_sub
    return tmp_349;
}
static inline ac_uint<1> q_sign_bit_4(ac_uint<7> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_352 = ac_uint<1>(((arg_0 >> 6) & 1));  // basic_select
    return tmp_352;
}
static inline ac_uint<8> q_sign_extend_3(ac_uint<7> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_353 = q_sign_bit_4(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_354 = ac_uint<2>((ac_uint<1>(1) >= 2 ? 0 : (ac_uint<2>(tmp_353) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_355 = ac_uint<1>((ac_uint<1>(tmp_354) - ac_uint<1>(tmp_353)));  // basic_sub
    const ac_uint<8> tmp_356 = ac_uint<8>(0);  // q_alloc
    const ac_uint<8> tmp_357 = ac_uint<8>(((ac_uint<8>(tmp_355) << 7) | arg_0));  // basic_concat
    return tmp_357;
}
static inline ac_uint<1> q_sign_bit_5(ac_uint<2> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_360 = ac_uint<1>(((arg_0 >> 1) & 1));  // basic_select
    return tmp_360;
}
static inline ac_uint<8> q_sign_extend_4(ac_uint<2> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_361 = q_sign_bit_5(arg_0);  // q_sign_bit
    const ac_uint<7> tmp_362 = ac_uint<7>((ac_uint<3>(6) >= 7 ? 0 : (ac_uint<7>(tmp_361) << ac_uint<3>(6))));  // basic_lshift
    const ac_uint<6> tmp_363 = ac_uint<6>((ac_uint<6>(tmp_362) - ac_uint<6>(tmp_361)));  // basic_sub
    const ac_uint<8> tmp_364 = ac_uint<8>(0);  // q_alloc
    const ac_uint<8> tmp_365 = ac_uint<8>(((ac_uint<8>(tmp_363) << 2) | arg_0));  // basic_concat
    return tmp_365;
}
static inline ac_uint<8> q_add_1(ac_uint<7> arg_0, ac_uint<2> arg_1) {  // q_add
    // begin inline primitive q_aligner
    const ac_uint<7> tmp_351 = ac_uint<7>((ac_uint<1>(0) >= 7 ? 0 : (ac_uint<7>(arg_0) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<8> tmp_358 = q_sign_extend_3(tmp_351);  // q_sign_extend
    const ac_uint<2> tmp_359 = ac_uint<2>((ac_uint<1>(0) >= 2 ? 0 : (ac_uint<2>(arg_1) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<8> tmp_366 = q_sign_extend_4(tmp_359);  // q_sign_extend
    const std::tuple<ac_uint<8>, ac_uint<8>> tmp_367 = std::make_tuple(tmp_358, tmp_366);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<8> tmp_368 = ac_uint<8>(std::get<0>(tmp_367));  // _basic_get_item_0
    const ac_uint<8> tmp_369 = ac_uint<8>(std::get<1>(tmp_367));  // _basic_get_item_1
    const ac_uint<8> tmp_370 = ac_uint<8>((ac_uint<8>(tmp_368) + ac_uint<8>(tmp_369)));  // basic_add
    return tmp_370;
}
static inline ac_uint<1> q_sign_bit_6(ac_uint<8> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_372 = ac_uint<1>(((arg_0 >> 7) & 1));  // basic_select
    return tmp_372;
}
static inline ac_uint<29> uq_resize_2(ac_uint<28> arg_0) {  // uq_resize
    const ac_uint<29> tmp_374 = ac_uint<29>((ac_uint<1>(1) >= 29 ? 0 : (ac_uint<29>(arg_0) << ac_uint<1>(1))));  // basic_lshift
    return tmp_374;
}
static inline ac_uint<8> q_neg_2(ac_uint<8> arg_0) {  // q_neg
    const ac_uint<1> tmp_377 = ac_uint<1>((arg_0 == 128));  // _q_is_min_val
    const ac_uint<8> tmp_378 = ac_uint<8>(((~arg_0) & 255));  // basic_invert
    const ac_uint<8> tmp_379 = ac_uint<8>((ac_uint<8>(tmp_378) + ac_uint<8>(ac_uint<1>(1))));  // basic_add
    const ac_uint<8> tmp_380 = ac_uint<8>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<8> tmp_381 = ac_uint<8>(((~tmp_380) & 255));  // basic_invert
    const ac_uint<8> tmp_382 = ac_uint<8>((tmp_377 != 0 ? tmp_381 : tmp_379));  // basic_mux_2_1
    return tmp_382;
}
static inline ac_uint<8> q_add_sign_2(ac_uint<8> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<8> tmp_383 = q_neg_2(arg_0);  // q_neg
    const ac_uint<8> tmp_384 = ac_uint<8>((arg_1 != 0 ? tmp_383 : arg_0));  // basic_mux_2_1
    return tmp_384;
}
static inline ac_uint<8> q_abs_1(ac_uint<8> arg_0) {  // q_abs
    const ac_uint<1> tmp_376 = q_sign_bit_6(arg_0);  // q_sign_bit
    const ac_uint<8> tmp_385 = q_add_sign_2(arg_0, tmp_376);  // q_add_sign
    return tmp_385;
}
static inline ac_uint<7> q_to_uq_1(ac_uint<8> arg_0) {  // q_to_uq
    const ac_uint<7> tmp_387 = ac_uint<7>(arg_0);  // basic_identity
    return tmp_387;
}
static inline ac_uint<29> uq_lshift(ac_uint<29> arg_0, ac_uint<7> arg_1) {  // uq_lshift
    const ac_uint<29> tmp_389 = ac_uint<29>((arg_1 >= 29 ? 0 : (ac_uint<29>(arg_0) << arg_1)));  // basic_lshift
    return tmp_389;
}
static inline ac_uint<29> uq_rshift_1(ac_uint<29> arg_0, ac_uint<7> arg_1) {  // uq_rshift
    const ac_uint<29> tmp_391 = ac_uint<29>((arg_1 >= 29 ? 0 : (arg_0 >> arg_1)));  // basic_rshift
    return tmp_391;
}
static inline ac_uint<1> uq_is_zero_2(ac_uint<7> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_393 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_394 = ac_uint<1>(((~tmp_393) & 1));  // basic_invert
    return tmp_394;
}
static inline ac_uint<1> uq_ge_1(ac_uint<7> arg_0, ac_uint<5> arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const ac_uint<7> tmp_396 = ac_uint<7>(arg_1);  // basic_identity
    const std::tuple<ac_uint<7>, ac_uint<7>> tmp_397 = std::make_tuple(arg_0, tmp_396);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<7> tmp_398 = ac_uint<7>(std::get<0>(tmp_397));  // _basic_get_item_0
    const ac_uint<7> tmp_399 = ac_uint<7>(std::get<1>(tmp_397));  // _basic_get_item_1
    const ac_uint<1> tmp_400 = ac_uint<1>((tmp_398 >= tmp_399));  // basic_greater_or_equal
    return tmp_400;
}
static inline ac_uint<8> uq_sub_2(ac_uint<5> arg_0, ac_uint<7> arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const ac_uint<8> tmp_402 = ac_uint<8>(arg_0);  // basic_identity
    const ac_uint<8> tmp_403 = ac_uint<8>(arg_1);  // basic_identity
    const std::tuple<ac_uint<8>, ac_uint<8>> tmp_404 = std::make_tuple(tmp_402, tmp_403);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<8> tmp_405 = ac_uint<8>(std::get<0>(tmp_404));  // _basic_get_item_0
    const ac_uint<8> tmp_406 = ac_uint<8>(std::get<1>(tmp_404));  // _basic_get_item_1
    const ac_uint<8> tmp_407 = ac_uint<8>((ac_uint<8>(tmp_405) - ac_uint<8>(tmp_406)));  // basic_sub
    return tmp_407;
}
static inline ac_uint<29> uq_rshift_jam_1(ac_uint<29> arg_0, ac_uint<7> arg_1) {  // uq_rshift_jam
    const ac_uint<29> tmp_392 = uq_rshift_1(arg_0, arg_1);  // uq_rshift
    const ac_uint<1> tmp_395 = uq_is_zero_2(arg_1);  // uq_is_zero
    const ac_uint<1> tmp_401 = uq_ge_1(arg_1, ac_uint<5>(29));  // uq_ge
    const ac_uint<8> tmp_408 = uq_sub_2(ac_uint<5>(29), arg_1);  // uq_sub
    const ac_uint<29> tmp_409 = ac_uint<29>((tmp_408 >= 29 ? 0 : (ac_uint<29>(arg_0) << tmp_408)));  // basic_lshift
    const ac_uint<1> tmp_410 = ac_uint<1>((tmp_409 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_411 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_412 = ac_uint<1>((tmp_401 != 0 ? tmp_411 : tmp_410));  // basic_mux_2_1
    const ac_uint<1> tmp_413 = ac_uint<1>((tmp_395 != 0 ? ac_uint<1>(0) : tmp_412));  // basic_mux_2_1
    const ac_uint<29> tmp_414 = ac_uint<29>((tmp_392 | tmp_413));  // basic_or
    return tmp_414;
}
static inline ac_uint<1> q_sign_bit_7(ac_uint<9> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_418 = ac_uint<1>(((arg_0 >> 8) & 1));  // basic_select
    return tmp_418;
}
static inline ac_uint<10> q_sign_extend_5(ac_uint<9> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_419 = q_sign_bit_7(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_420 = ac_uint<2>((ac_uint<1>(1) >= 2 ? 0 : (ac_uint<2>(tmp_419) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_421 = ac_uint<1>((ac_uint<1>(tmp_420) - ac_uint<1>(tmp_419)));  // basic_sub
    const ac_uint<10> tmp_422 = ac_uint<10>(0);  // q_alloc
    const ac_uint<10> tmp_423 = ac_uint<10>(((ac_uint<10>(tmp_421) << 9) | arg_0));  // basic_concat
    return tmp_423;
}
static inline ac_uint<10> q_sign_extend_6(ac_uint<8> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_426 = q_sign_bit_6(arg_0);  // q_sign_bit
    const ac_uint<3> tmp_427 = ac_uint<3>((ac_uint<2>(2) >= 3 ? 0 : (ac_uint<3>(tmp_426) << ac_uint<2>(2))));  // basic_lshift
    const ac_uint<2> tmp_428 = ac_uint<2>((ac_uint<2>(tmp_427) - ac_uint<2>(tmp_426)));  // basic_sub
    const ac_uint<10> tmp_429 = ac_uint<10>(0);  // q_alloc
    const ac_uint<10> tmp_430 = ac_uint<10>(((ac_uint<10>(tmp_428) << 8) | arg_0));  // basic_concat
    return tmp_430;
}
static inline ac_uint<10> q_sub_1(ac_uint<9> arg_0, ac_uint<8> arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const ac_uint<9> tmp_417 = ac_uint<9>((ac_uint<1>(0) >= 9 ? 0 : (ac_uint<9>(arg_0) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<10> tmp_424 = q_sign_extend_5(tmp_417);  // q_sign_extend
    const ac_uint<8> tmp_425 = ac_uint<8>((ac_uint<1>(0) >= 8 ? 0 : (ac_uint<8>(arg_1) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<10> tmp_431 = q_sign_extend_6(tmp_425);  // q_sign_extend
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_432 = std::make_tuple(tmp_424, tmp_431);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<10> tmp_433 = ac_uint<10>(std::get<0>(tmp_432));  // _basic_get_item_0
    const ac_uint<10> tmp_434 = ac_uint<10>(std::get<1>(tmp_432));  // _basic_get_item_1
    const ac_uint<10> tmp_435 = ac_uint<10>((ac_uint<10>(tmp_433) - ac_uint<10>(tmp_434)));  // basic_sub
    return tmp_435;
}
static inline ac_uint<10> q_add_2(ac_uint<9> arg_0, ac_uint<8> arg_1) {  // q_add
    // begin inline primitive q_aligner
    const ac_uint<9> tmp_437 = ac_uint<9>((ac_uint<1>(0) >= 9 ? 0 : (ac_uint<9>(arg_0) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<10> tmp_438 = q_sign_extend_5(tmp_437);  // q_sign_extend
    const ac_uint<8> tmp_439 = ac_uint<8>((ac_uint<1>(0) >= 8 ? 0 : (ac_uint<8>(arg_1) << ac_uint<1>(0))));  // basic_lshift
    const ac_uint<10> tmp_440 = q_sign_extend_6(tmp_439);  // q_sign_extend
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_441 = std::make_tuple(tmp_438, tmp_440);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<10> tmp_442 = ac_uint<10>(std::get<0>(tmp_441));  // _basic_get_item_0
    const ac_uint<10> tmp_443 = ac_uint<10>(std::get<1>(tmp_441));  // _basic_get_item_1
    const ac_uint<10> tmp_444 = ac_uint<10>((ac_uint<10>(tmp_442) + ac_uint<10>(tmp_443)));  // basic_add
    return tmp_444;
}
static inline ac_uint<1> q_is_zero(ac_uint<10> arg_0) {  // q_is_zero
    const ac_uint<1> tmp_451 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_452 = ac_uint<1>(((~tmp_451) & 1));  // basic_invert
    return tmp_452;
}
static inline ac_uint<1> q_sign_bit_8(ac_uint<10> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_454 = ac_uint<1>(((arg_0 >> 9) & 1));  // basic_select
    return tmp_454;
}
static inline ac_uint<10> q_neg_3(ac_uint<10> arg_0) {  // q_neg
    const ac_uint<1> tmp_458 = ac_uint<1>((arg_0 == 512));  // _q_is_min_val
    const ac_uint<10> tmp_459 = ac_uint<10>(((~arg_0) & 1023));  // basic_invert
    const ac_uint<10> tmp_460 = ac_uint<10>((ac_uint<10>(tmp_459) + ac_uint<10>(ac_uint<1>(1))));  // basic_add
    const ac_uint<10> tmp_461 = ac_uint<10>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<10> tmp_462 = ac_uint<10>(((~tmp_461) & 1023));  // basic_invert
    const ac_uint<10> tmp_463 = ac_uint<10>((tmp_458 != 0 ? tmp_462 : tmp_460));  // basic_mux_2_1
    return tmp_463;
}
static inline ac_uint<10> q_add_sign_3(ac_uint<10> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<10> tmp_464 = q_neg_3(arg_0);  // q_neg
    const ac_uint<10> tmp_465 = ac_uint<10>((arg_1 != 0 ? tmp_464 : arg_0));  // basic_mux_2_1
    return tmp_465;
}
static inline ac_uint<10> q_abs_2(ac_uint<10> arg_0) {  // q_abs
    const ac_uint<1> tmp_457 = q_sign_bit_8(arg_0);  // q_sign_bit
    const ac_uint<10> tmp_466 = q_add_sign_3(arg_0, tmp_457);  // q_add_sign
    return tmp_466;
}
static inline ac_uint<9> q_to_uq_2(ac_uint<10> arg_0) {  // q_to_uq
    const ac_uint<9> tmp_468 = ac_uint<9>(arg_0);  // basic_identity
    return tmp_468;
}
static inline ac_uint<10> uq_add_4(ac_uint<1> arg_0, ac_uint<9> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_470 = ac_uint<10>(arg_0);  // basic_identity
    const ac_uint<10> tmp_471 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_472 = std::make_tuple(tmp_470, tmp_471);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_473 = ac_uint<10>(std::get<0>(tmp_472));  // _basic_get_item_0
    const ac_uint<10> tmp_474 = ac_uint<10>(std::get<1>(tmp_472));  // _basic_get_item_1
    const ac_uint<10> tmp_475 = ac_uint<10>((ac_uint<10>(tmp_473) + ac_uint<10>(tmp_474)));  // basic_add
    return tmp_475;
}
static inline ac_uint<38> uq_rshift_2(ac_uint<38> arg_0, ac_uint<10> arg_1) {  // uq_rshift
    const ac_uint<38> tmp_478 = ac_uint<38>((arg_1 >= 38 ? 0 : (arg_0 >> arg_1)));  // basic_rshift
    return tmp_478;
}
static inline ac_uint<1> uq_is_zero_3(ac_uint<10> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_480 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_481 = ac_uint<1>(((~tmp_480) & 1));  // basic_invert
    return tmp_481;
}
static inline ac_uint<1> uq_ge_2(ac_uint<10> arg_0, ac_uint<6> arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_483 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_484 = std::make_tuple(arg_0, tmp_483);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_485 = ac_uint<10>(std::get<0>(tmp_484));  // _basic_get_item_0
    const ac_uint<10> tmp_486 = ac_uint<10>(std::get<1>(tmp_484));  // _basic_get_item_1
    const ac_uint<1> tmp_487 = ac_uint<1>((tmp_485 >= tmp_486));  // basic_greater_or_equal
    return tmp_487;
}
static inline ac_uint<11> uq_sub_3(ac_uint<6> arg_0, ac_uint<10> arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const ac_uint<11> tmp_489 = ac_uint<11>(arg_0);  // basic_identity
    const ac_uint<11> tmp_490 = ac_uint<11>(arg_1);  // basic_identity
    const std::tuple<ac_uint<11>, ac_uint<11>> tmp_491 = std::make_tuple(tmp_489, tmp_490);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<11> tmp_492 = ac_uint<11>(std::get<0>(tmp_491));  // _basic_get_item_0
    const ac_uint<11> tmp_493 = ac_uint<11>(std::get<1>(tmp_491));  // _basic_get_item_1
    const ac_uint<11> tmp_494 = ac_uint<11>((ac_uint<11>(tmp_492) - ac_uint<11>(tmp_493)));  // basic_sub
    return tmp_494;
}
static inline ac_uint<38> uq_rshift_jam_2(ac_uint<38> arg_0, ac_uint<10> arg_1) {  // uq_rshift_jam
    const ac_uint<38> tmp_479 = uq_rshift_2(arg_0, arg_1);  // uq_rshift
    const ac_uint<1> tmp_482 = uq_is_zero_3(arg_1);  // uq_is_zero
    const ac_uint<1> tmp_488 = uq_ge_2(arg_1, ac_uint<6>(38));  // uq_ge
    const ac_uint<11> tmp_495 = uq_sub_3(ac_uint<6>(38), arg_1);  // uq_sub
    const ac_uint<38> tmp_496 = ac_uint<38>((tmp_495 >= 38 ? 0 : (ac_uint<38>(arg_0) << tmp_495)));  // basic_lshift
    const ac_uint<1> tmp_497 = ac_uint<1>((tmp_496 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_498 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_499 = ac_uint<1>((tmp_488 != 0 ? tmp_498 : tmp_497));  // basic_mux_2_1
    const ac_uint<1> tmp_500 = ac_uint<1>((tmp_482 != 0 ? ac_uint<1>(0) : tmp_499));  // basic_mux_2_1
    const ac_uint<38> tmp_501 = ac_uint<38>((tmp_479 | tmp_500));  // basic_or
    return tmp_501;
}
static inline ac_uint<37> drop_implicit_bit(ac_uint<38> arg_0) {  // drop_implicit_bit
    const ac_uint<37> tmp_506 = ac_uint<37>(((arg_0 >> 0) & 137438953471));  // basic_select
    return tmp_506;
}
static inline ac_uint<23> uq_resize_3(ac_uint<37> arg_0) {  // uq_resize
    const ac_uint<23> tmp_510 = ac_uint<23>((ac_uint<4>(14) >= 37 ? 0 : (arg_0 >> ac_uint<4>(14))));  // basic_rshift
    return tmp_510;
}
static inline ac_uint<24> uq_add_5(ac_uint<23> arg_0, ac_uint<23> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<24> tmp_521 = ac_uint<24>(arg_0);  // basic_identity
    const ac_uint<24> tmp_522 = ac_uint<24>(arg_1);  // basic_identity
    const std::tuple<ac_uint<24>, ac_uint<24>> tmp_523 = std::make_tuple(tmp_521, tmp_522);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<24> tmp_524 = ac_uint<24>(std::get<0>(tmp_523));  // _basic_get_item_0
    const ac_uint<24> tmp_525 = ac_uint<24>(std::get<1>(tmp_523));  // _basic_get_item_1
    const ac_uint<24> tmp_526 = ac_uint<24>((ac_uint<24>(tmp_524) + ac_uint<24>(tmp_525)));  // basic_add
    return tmp_526;
}
static inline ac_uint<10> uq_add_6(ac_uint<9> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_533 = ac_uint<10>(arg_0);  // basic_identity
    const ac_uint<10> tmp_534 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_535 = std::make_tuple(tmp_533, tmp_534);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_536 = ac_uint<10>(std::get<0>(tmp_535));  // _basic_get_item_0
    const ac_uint<10> tmp_537 = ac_uint<10>(std::get<1>(tmp_535));  // _basic_get_item_1
    const ac_uint<10> tmp_538 = ac_uint<10>((ac_uint<10>(tmp_536) + ac_uint<10>(tmp_537)));  // basic_add
    return tmp_538;
}
static inline ac_uint<10> uq_min(ac_uint<10> arg_0, ac_uint<8> arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_547 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_548 = std::make_tuple(arg_0, tmp_547);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_549 = ac_uint<10>(std::get<0>(tmp_548));  // _basic_get_item_0
    const ac_uint<10> tmp_550 = ac_uint<10>(std::get<1>(tmp_548));  // _basic_get_item_1
    const ac_uint<10> tmp_551 = ac_uint<10>((tmp_549 < tmp_550 ? tmp_549 : tmp_550));  // basic_min
    return tmp_551;
}
static inline ac_uint<32> fp32_pack(ac_uint<1> arg_0, ac_uint<8> arg_1, ac_uint<23> arg_2) {  // fp32_pack
    const ac_uint<32> tmp_560 = ac_uint<32>(((arg_0 << 31) | (arg_1 << 23) | arg_2));  // float32_alloc
    return tmp_560;
}
static inline ac_uint<32> fp32_encode(ac_uint<1> arg_0, ac_uint<9> arg_1, ac_uint<28> arg_2, ac_uint<1> arg_3, ac_uint<1> arg_4) {  // fp32_encode
    const ac_uint<32> tmp_192 = ac_uint<32>((arg_0 != 0 ? ac_uint<32>(4286578688) : ac_uint<32>(2139095040)));  // basic_mux_2_1
    const ac_uint<1> tmp_195 = uq_is_zero_1(arg_2);  // uq_is_zero
    const ac_uint<32> tmp_196 = ac_uint<32>((arg_0 != 0 ? ac_uint<32>(2147483648) : ac_uint<32>(0)));  // basic_mux_2_1
    // begin inline primitive normalize_to_1_xxx
    const ac_uint<5> tmp_309 = lzc(arg_2);  // lzc
    const ac_uint<6> tmp_319 = uq_to_q_2(tmp_309);  // uq_to_q
    const ac_uint<3> tmp_329 = uq_to_q_3(ac_uint<2>(2));  // uq_to_q
    const ac_uint<7> tmp_350 = q_sub(tmp_319, tmp_329);  // q_sub
    const ac_uint<8> tmp_371 = q_add_1(tmp_350, ac_uint<2>(1));  // q_add
    const ac_uint<1> tmp_373 = q_sign_bit_6(tmp_371);  // q_sign_bit
    const ac_uint<29> tmp_375 = uq_resize_2(arg_2);  // uq_resize
    const ac_uint<8> tmp_386 = q_abs_1(tmp_371);  // q_abs
    const ac_uint<7> tmp_388 = q_to_uq_1(tmp_386);  // q_to_uq
    const ac_uint<29> tmp_390 = uq_lshift(tmp_375, tmp_388);  // uq_lshift
    const ac_uint<29> tmp_415 = uq_rshift_jam_1(tmp_375, tmp_388);  // uq_rshift_jam
    const ac_uint<28> tmp_416 = ac_uint<28>((tmp_373 != 0 ? tmp_415 : tmp_390));  // basic_mux_2_1
    const ac_uint<10> tmp_436 = q_sub_1(arg_1, tmp_386);  // q_sub
    const ac_uint<10> tmp_445 = q_add_2(arg_1, tmp_386);  // q_add
    const ac_uint<10> tmp_446 = ac_uint<10>((tmp_373 != 0 ? tmp_445 : tmp_436));  // basic_mux_2_1
    const std::tuple<ac_uint<28>, ac_uint<10>> tmp_447 = std::make_tuple(tmp_416, tmp_446);  // basic_tuple_maker_2
    // end inline primitive normalize_to_1_xxx
    const ac_uint<28> tmp_448 = ac_uint<28>(std::get<0>(tmp_447));  // _basic_get_item_0
    const ac_uint<10> tmp_449 = ac_uint<10>(std::get<1>(tmp_447));  // _basic_get_item_1
    // begin inline primitive shift_if_subnormal
    const ac_uint<38> tmp_450 = ac_uint<38>((ac_uint<4>(10) >= 38 ? 0 : (ac_uint<38>(tmp_448) << ac_uint<4>(10))));  // basic_lshift
    const ac_uint<1> tmp_453 = q_is_zero(tmp_449);  // q_is_zero
    const ac_uint<1> tmp_455 = q_sign_bit_8(tmp_449);  // q_sign_bit
    const ac_uint<1> tmp_456 = ac_uint<1>((tmp_453 | tmp_455));  // basic_or
    const ac_uint<10> tmp_467 = q_abs_2(tmp_449);  // q_abs
    const ac_uint<9> tmp_469 = q_to_uq_2(tmp_467);  // q_to_uq
    const ac_uint<10> tmp_476 = uq_add_4(ac_uint<1>(1), tmp_469);  // uq_add
    const ac_uint<10> tmp_477 = ac_uint<10>((tmp_456 != 0 ? tmp_476 : ac_uint<1>(0)));  // basic_mux_2_1
    const ac_uint<38> tmp_502 = uq_rshift_jam_2(tmp_450, tmp_477);  // uq_rshift_jam
    const ac_uint<9> tmp_503 = ac_uint<9>((tmp_456 != 0 ? ac_uint<1>(0) : tmp_469));  // basic_mux_2_1
    const std::tuple<ac_uint<38>, ac_uint<9>> tmp_504 = std::make_tuple(tmp_502, tmp_503);  // basic_tuple_maker_2
    // end inline primitive shift_if_subnormal
    const ac_uint<38> tmp_505 = ac_uint<38>(std::get<0>(tmp_504));  // _basic_get_item_0
    const ac_uint<37> tmp_507 = drop_implicit_bit(tmp_505);  // drop_implicit_bit
    const ac_uint<9> tmp_508 = ac_uint<9>(std::get<1>(tmp_504));  // _basic_get_item_1
    // begin inline primitive round_mantissa
    const ac_uint<1> tmp_509 = uq_is_zero(tmp_508);  // uq_is_zero
    // begin inline primitive uq_RNE_IEEE
    const ac_uint<23> tmp_511 = uq_resize_3(tmp_507);  // uq_resize
    const ac_uint<1> tmp_512 = ac_uint<1>(((tmp_507 >> 13) & 1));  // basic_select
    const ac_uint<1> tmp_513 = ac_uint<1>(((tmp_507 >> 12) & 1));  // basic_select
    const ac_uint<12> tmp_514 = ac_uint<12>(((tmp_507 >> 0) & 4095));  // basic_select
    const ac_uint<1> tmp_515 = ac_uint<1>((tmp_514 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_516 = ac_uint<1>((tmp_513 | tmp_515));  // basic_or
    const ac_uint<1> tmp_517 = ac_uint<1>(((tmp_507 >> 14) & 1));  // basic_select
    const ac_uint<1> tmp_518 = ac_uint<1>((tmp_516 | tmp_517));  // basic_or
    const ac_uint<1> tmp_519 = ac_uint<1>((tmp_512 & tmp_518));  // basic_and
    const ac_uint<23> tmp_520 = ac_uint<23>(tmp_519);  // basic_identity
    const ac_uint<24> tmp_527 = uq_add_5(tmp_511, tmp_520);  // uq_add
    const ac_uint<1> tmp_528 = ac_uint<1>((tmp_511 == 8388607));  // basic_and_reduce
    const ac_uint<1> tmp_529 = ac_uint<1>((tmp_528 & tmp_519));  // basic_and
    const ac_uint<23> tmp_530 = ac_uint<23>((tmp_529 >= 24 ? 0 : (tmp_527 >> tmp_529)));  // basic_rshift
    const std::tuple<ac_uint<23>, ac_uint<1>> tmp_531 = std::make_tuple(tmp_530, tmp_529);  // basic_tuple_maker_2
    // end inline primitive uq_RNE_IEEE
    const ac_uint<1> tmp_532 = ac_uint<1>(std::get<1>(tmp_531));  // _basic_get_item_1
    const ac_uint<10> tmp_539 = uq_add_6(tmp_508, tmp_532);  // uq_add
    const ac_uint<1> tmp_540 = ac_uint<1>((tmp_539 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_541 = ac_uint<1>((tmp_509 & tmp_540));  // basic_and
    const ac_uint<23> tmp_542 = ac_uint<23>(std::get<0>(tmp_531));  // _basic_get_item_0
    const ac_uint<23> tmp_543 = ac_uint<23>((tmp_541 != 0 ? ac_uint<1>(0) : tmp_542));  // basic_mux_2_1
    const std::tuple<ac_uint<23>, ac_uint<10>> tmp_544 = std::make_tuple(tmp_543, tmp_539);  // basic_tuple_maker_2
    // end inline primitive round_mantissa
    const ac_uint<23> tmp_545 = ac_uint<23>(std::get<0>(tmp_544));  // _basic_get_item_0
    const ac_uint<10> tmp_546 = ac_uint<10>(std::get<1>(tmp_544));  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const ac_uint<10> tmp_552 = uq_min(tmp_546, ac_uint<8>(255));  // uq_min
    const ac_uint<8> tmp_553 = ac_uint<8>(tmp_552);  // basic_identity
    const ac_uint<1> tmp_554 = ac_uint<1>((tmp_553 == 255));  // basic_and_reduce
    const ac_uint<23> tmp_555 = ac_uint<23>((tmp_554 != 0 ? ac_uint<1>(0) : tmp_545));  // basic_mux_2_1
    const ac_uint<23> tmp_556 = ac_uint<23>(tmp_555);  // basic_identity
    const std::tuple<ac_uint<23>, ac_uint<8>> tmp_557 = std::make_tuple(tmp_556, tmp_553);  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const ac_uint<8> tmp_558 = ac_uint<8>(std::get<1>(tmp_557));  // _basic_get_item_1
    const ac_uint<23> tmp_559 = ac_uint<23>(std::get<0>(tmp_557));  // _basic_get_item_0
    const ac_uint<32> tmp_561 = fp32_pack(arg_0, tmp_558, tmp_559);  // fp32_pack
    const ac_uint<32> tmp_562 = ac_uint<32>((tmp_195 != 0 ? tmp_196 : tmp_561));  // basic_mux_2_1
    const ac_uint<32> tmp_563 = ac_uint<32>((arg_4 != 0 ? tmp_192 : tmp_562));  // basic_mux_2_1
    const ac_uint<32> tmp_564 = ac_uint<32>((arg_3 != 0 ? ac_uint<32>(2139095041) : tmp_563));  // basic_mux_2_1
    return tmp_564;
}
static inline ac_uint<32> FP32_IEEE_adder_impl(ac_uint<32> arg_0, ac_uint<32> arg_1) {  // FP32_IEEE_adder
    // begin inline composite fp32_classify
    const ac_uint<1> tmp_5 = fp32_is_normal(arg_0);  // fp32_is_normal
    const ac_uint<1> tmp_12 = fp32_is_subnormal(arg_0);  // fp32_is_subnormal
    const ac_uint<1> tmp_20 = fp32_is_zero(arg_0);  // fp32_is_zero
    const ac_uint<1> tmp_27 = fp32_is_inf(arg_0);  // fp32_is_inf
    const ac_uint<1> tmp_33 = fp32_is_nan(arg_0);  // fp32_is_nan
    const std::tuple<ac_uint<1>, ac_uint<1>, ac_uint<1>, ac_uint<1>, ac_uint<1>> tmp_34 = std::make_tuple(tmp_5, tmp_12, tmp_20, tmp_27, tmp_33);  // basic_tuple_maker_5
    // end inline composite fp32_classify
    const ac_uint<1> tmp_35 = ac_uint<1>(std::get<2>(tmp_34));  // _basic_get_item_2
    // begin inline composite fp32_classify
    const ac_uint<1> tmp_36 = fp32_is_normal(arg_1);  // fp32_is_normal
    const ac_uint<1> tmp_37 = fp32_is_subnormal(arg_1);  // fp32_is_subnormal
    const ac_uint<1> tmp_38 = fp32_is_zero(arg_1);  // fp32_is_zero
    const ac_uint<1> tmp_39 = fp32_is_inf(arg_1);  // fp32_is_inf
    const ac_uint<1> tmp_40 = fp32_is_nan(arg_1);  // fp32_is_nan
    const std::tuple<ac_uint<1>, ac_uint<1>, ac_uint<1>, ac_uint<1>, ac_uint<1>> tmp_41 = std::make_tuple(tmp_36, tmp_37, tmp_38, tmp_39, tmp_40);  // basic_tuple_maker_5
    // end inline composite fp32_classify
    const ac_uint<1> tmp_42 = ac_uint<1>(std::get<2>(tmp_41));  // _basic_get_item_2
    const ac_uint<1> tmp_43 = ac_uint<1>((tmp_35 & tmp_42));  // basic_and
    // begin inline primitive fp32_unpack
    const ac_uint<1> tmp_44 = ac_uint<1>(((arg_0 >> 31) & 1));  // _fp32_sign
    const ac_uint<8> tmp_45 = ac_uint<8>(((arg_0 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<23> tmp_46 = ac_uint<23>((arg_0 & ((1 << 23) - 1)));  // _fp32_mantissa
    const std::tuple<ac_uint<1>, ac_uint<8>, ac_uint<23>> tmp_47 = std::make_tuple(tmp_44, tmp_45, tmp_46);  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const ac_uint<1> tmp_48 = ac_uint<1>(std::get<0>(tmp_47));  // _basic_get_item_0
    // begin inline primitive fp32_unpack
    const ac_uint<1> tmp_49 = ac_uint<1>(((arg_1 >> 31) & 1));  // _fp32_sign
    const ac_uint<8> tmp_50 = ac_uint<8>(((arg_1 >> 23) & ((1 << 8) - 1)));  // _fp32_exponent
    const ac_uint<23> tmp_51 = ac_uint<23>((arg_1 & ((1 << 23) - 1)));  // _fp32_mantissa
    const std::tuple<ac_uint<1>, ac_uint<8>, ac_uint<23>> tmp_52 = std::make_tuple(tmp_49, tmp_50, tmp_51);  // basic_tuple_maker_3
    // end inline primitive fp32_unpack
    const ac_uint<1> tmp_53 = ac_uint<1>(std::get<0>(tmp_52));  // _basic_get_item_0
    const ac_uint<1> tmp_54 = ac_uint<1>((tmp_48 & tmp_53));  // basic_and
    const ac_uint<1> tmp_55 = ac_uint<1>((tmp_43 & tmp_54));  // basic_and
    const ac_uint<1> tmp_56 = ac_uint<1>(std::get<0>(tmp_34));  // _basic_get_item_0
    const ac_uint<23> tmp_57 = ac_uint<23>(std::get<2>(tmp_47));  // _basic_get_item_2
    const ac_uint<23> tmp_58 = ac_uint<23>(tmp_57);  // basic_identity
    const ac_uint<24> tmp_60 = add_implicit_bit(tmp_58);  // add_implicit_bit
    const ac_uint<24> tmp_62 = uq_resize(tmp_58);  // uq_resize
    const ac_uint<24> tmp_63 = ac_uint<24>((tmp_56 != 0 ? tmp_60 : tmp_62));  // basic_mux_2_1
    const ac_uint<27> tmp_65 = uq_resize_1(tmp_63);  // uq_resize
    const ac_uint<1> tmp_66 = ac_uint<1>(std::get<1>(tmp_34));  // _basic_get_item_1
    const ac_uint<8> tmp_67 = ac_uint<8>(std::get<1>(tmp_47));  // _basic_get_item_1
    const ac_uint<8> tmp_68 = ac_uint<8>((tmp_66 != 0 ? ac_uint<8>(1) : tmp_67));  // basic_mux_2_1
    const ac_uint<1> tmp_69 = ac_uint<1>(std::get<1>(tmp_41));  // _basic_get_item_1
    const ac_uint<8> tmp_70 = ac_uint<8>(std::get<1>(tmp_52));  // _basic_get_item_1
    const ac_uint<8> tmp_71 = ac_uint<8>((tmp_69 != 0 ? ac_uint<8>(1) : tmp_70));  // basic_mux_2_1
    const ac_uint<8> tmp_76 = uq_max(tmp_68, tmp_71);  // uq_max
    const ac_uint<9> tmp_83 = uq_sub(tmp_76, tmp_68);  // uq_sub
    const ac_uint<27> tmp_108 = uq_rshift_jam(tmp_65, tmp_83);  // uq_rshift_jam
    const ac_uint<28> tmp_118 = uq_to_q(tmp_108);  // uq_to_q
    const ac_uint<28> tmp_127 = q_add_sign(tmp_118, tmp_48);  // q_add_sign
    const ac_uint<1> tmp_128 = ac_uint<1>(std::get<0>(tmp_41));  // _basic_get_item_0
    const ac_uint<23> tmp_129 = ac_uint<23>(std::get<2>(tmp_52));  // _basic_get_item_2
    const ac_uint<23> tmp_130 = ac_uint<23>(tmp_129);  // basic_identity
    const ac_uint<24> tmp_131 = add_implicit_bit(tmp_130);  // add_implicit_bit
    const ac_uint<24> tmp_132 = uq_resize(tmp_130);  // uq_resize
    const ac_uint<24> tmp_133 = ac_uint<24>((tmp_128 != 0 ? tmp_131 : tmp_132));  // basic_mux_2_1
    const ac_uint<27> tmp_134 = uq_resize_1(tmp_133);  // uq_resize
    const ac_uint<9> tmp_135 = uq_sub(tmp_76, tmp_71);  // uq_sub
    const ac_uint<27> tmp_136 = uq_rshift_jam(tmp_134, tmp_135);  // uq_rshift_jam
    const ac_uint<28> tmp_137 = uq_to_q(tmp_136);  // uq_to_q
    const ac_uint<28> tmp_138 = q_add_sign(tmp_137, tmp_53);  // q_add_sign
    const ac_uint<29> tmp_153 = q_add(tmp_127, tmp_138);  // q_add
    const ac_uint<1> tmp_155 = q_sign_bit_1(tmp_153);  // q_sign_bit
    const ac_uint<1> tmp_156 = ac_uint<1>((tmp_55 != 0 ? ac_uint<1>(1) : tmp_155));  // basic_mux_2_1
    const ac_uint<9> tmp_166 = uq_to_q_1(tmp_76);  // uq_to_q
    const ac_uint<29> tmp_177 = q_abs(tmp_153);  // q_abs
    const ac_uint<28> tmp_179 = q_to_uq(tmp_177);  // q_to_uq
    const ac_uint<1> tmp_180 = ac_uint<1>(std::get<3>(tmp_34));  // _basic_get_item_3
    const ac_uint<1> tmp_181 = ac_uint<1>(std::get<3>(tmp_41));  // _basic_get_item_3
    const ac_uint<1> tmp_182 = ac_uint<1>((tmp_180 & tmp_181));  // basic_and
    const ac_uint<1> tmp_183 = ac_uint<1>((tmp_48 ^ tmp_53));  // basic_xor
    const ac_uint<1> tmp_184 = ac_uint<1>((tmp_182 & tmp_183));  // basic_and
    const ac_uint<1> tmp_185 = ac_uint<1>(std::get<4>(tmp_34));  // _basic_get_item_4
    const ac_uint<1> tmp_186 = ac_uint<1>(std::get<4>(tmp_41));  // _basic_get_item_4
    const ac_uint<1> tmp_187 = ac_uint<1>((tmp_185 | tmp_186));  // basic_or
    const ac_uint<1> tmp_188 = ac_uint<1>((tmp_184 | tmp_187));  // basic_or
    const ac_uint<1> tmp_189 = ac_uint<1>(((~tmp_188) & 1));  // basic_invert
    const ac_uint<1> tmp_190 = ac_uint<1>((tmp_180 | tmp_181));  // basic_or
    const ac_uint<1> tmp_191 = ac_uint<1>((tmp_189 & tmp_190));  // basic_and
    const ac_uint<32> tmp_565 = fp32_encode(tmp_156, tmp_166, tmp_179, tmp_188, tmp_191);  // fp32_encode
    return tmp_565;
}
extern "C" inline ac_uint<32> FP32_IEEE_adder(ac_uint<32> arg_0, ac_uint<32> arg_1) {
    return FP32_IEEE_adder_impl(arg_0, arg_1);
}