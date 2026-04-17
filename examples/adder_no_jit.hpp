#pragma once
#include <cstdint>
#include <tuple>
#include <ac_int.h>

template <int W>
using ac_uint = ac_int<W, false>;

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
    const ac_uint<27> tmp_64 = ac_uint<27>((ac_uint<2>(3) >= 27 ? ac_uint<27>(0) : (ac_uint<27>(arg_0) << ac_uint<2>(3))));  // basic_lshift
    return tmp_64;
}
static inline ac_uint<8> uq_max(ac_uint<8> arg_0, ac_uint<8> arg_1) {  // uq_max
    // begin inline primitive uq_aligner
    const std::tuple<ac_uint<8>, ac_uint<8>> tmp_72 = std::make_tuple(arg_0, arg_1);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<8> tmp_73 = ac_uint<8>(std::get<0>(tmp_72));  // _basic_get_item_0
    const ac_uint<8> tmp_74 = ac_uint<8>(std::get<1>(tmp_72));  // _basic_get_item_1
    const ac_uint<8> tmp_75 = ac_uint<8>((tmp_73 > tmp_74 ? ac_uint<8>(tmp_73) : ac_uint<8>(tmp_74)));  // basic_max
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
    const ac_uint<27> tmp_84 = ac_uint<27>((arg_1 >= 27 ? ac_uint<27>(0) : (arg_0 >> arg_1)));  // basic_rshift
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
    const ac_uint<27> tmp_102 = ac_uint<27>((tmp_101 >= 27 ? ac_uint<27>(0) : (ac_uint<27>(arg_0) << tmp_101)));  // basic_lshift
    const ac_uint<1> tmp_103 = ac_uint<1>((tmp_102 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_104 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_105 = ac_uint<1>((tmp_94 != 0 ? ac_uint<1>(tmp_104) : ac_uint<1>(tmp_103)));  // basic_mux_2_1
    const ac_uint<1> tmp_106 = ac_uint<1>((tmp_88 != 0 ? ac_uint<1>(ac_uint<1>(0)) : ac_uint<1>(tmp_105)));  // basic_mux_2_1
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
    const ac_uint<28> tmp_124 = ac_uint<28>((tmp_119 != 0 ? ac_uint<28>(tmp_123) : ac_uint<28>(tmp_121)));  // basic_mux_2_1
    return tmp_124;
}
static inline ac_uint<28> q_add_sign(ac_uint<28> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<28> tmp_125 = q_neg(arg_0);  // q_neg
    const ac_uint<28> tmp_126 = ac_uint<28>((arg_1 != 0 ? ac_uint<28>(tmp_125) : ac_uint<28>(arg_0)));  // basic_mux_2_1
    return tmp_126;
}
static inline ac_uint<1> q_sign_bit(ac_uint<28> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_139 = ac_uint<1>(((arg_0 >> 27) & 1));  // basic_select
    return tmp_139;
}
static inline ac_uint<29> q_sign_extend(ac_uint<28> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_140 = q_sign_bit(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_141 = ac_uint<2>((ac_uint<1>(1) >= 2 ? ac_uint<2>(0) : (ac_uint<2>(tmp_140) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_142 = ac_uint<1>((ac_uint<1>(tmp_141) - ac_uint<1>(tmp_140)));  // basic_sub
    const ac_uint<29> tmp_143 = ac_uint<29>(0);  // q_alloc
    const ac_uint<29> tmp_144 = ac_uint<29>(((ac_uint<29>(tmp_142) << 28) | arg_0));  // basic_concat
    return tmp_144;
}
static inline ac_uint<29> q_add(ac_uint<28> arg_0, ac_uint<28> arg_1) {  // q_add
    // begin inline primitive q_aligner
    const ac_uint<29> tmp_145 = q_sign_extend(arg_0);  // q_sign_extend
    const ac_uint<29> tmp_146 = q_sign_extend(arg_1);  // q_sign_extend
    const std::tuple<ac_uint<29>, ac_uint<29>> tmp_147 = std::make_tuple(tmp_145, tmp_146);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<29> tmp_148 = ac_uint<29>(std::get<0>(tmp_147));  // _basic_get_item_0
    const ac_uint<29> tmp_149 = ac_uint<29>(std::get<1>(tmp_147));  // _basic_get_item_1
    const ac_uint<29> tmp_150 = ac_uint<29>((ac_uint<29>(tmp_148) + ac_uint<29>(tmp_149)));  // basic_add
    return tmp_150;
}
static inline ac_uint<1> q_sign_bit_1(ac_uint<29> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_152 = ac_uint<1>(((arg_0 >> 28) & 1));  // basic_select
    return tmp_152;
}
static inline ac_uint<5> uq_add_1(ac_uint<4> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<5> tmp_155 = ac_uint<5>(arg_0);  // basic_identity
    const ac_uint<5> tmp_156 = ac_uint<5>(arg_1);  // basic_identity
    const std::tuple<ac_uint<5>, ac_uint<5>> tmp_157 = std::make_tuple(tmp_155, tmp_156);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<5> tmp_158 = ac_uint<5>(std::get<0>(tmp_157));  // _basic_get_item_0
    const ac_uint<5> tmp_159 = ac_uint<5>(std::get<1>(tmp_157));  // _basic_get_item_1
    const ac_uint<5> tmp_160 = ac_uint<5>((ac_uint<5>(tmp_158) + ac_uint<5>(tmp_159)));  // basic_add
    return tmp_160;
}
static inline ac_uint<9> uq_to_q_1(ac_uint<8> arg_0) {  // uq_to_q
    const ac_uint<5> tmp_161 = uq_add_1(ac_uint<4>(8), ac_uint<1>(1));  // uq_add
    const ac_uint<9> tmp_162 = ac_uint<9>(0);  // q_alloc
    const ac_uint<9> tmp_163 = ac_uint<9>(arg_0);  // basic_identity
    return tmp_163;
}
static inline ac_uint<29> q_neg_1(ac_uint<29> arg_0) {  // q_neg
    const ac_uint<1> tmp_166 = ac_uint<1>((arg_0 == 268435456));  // _q_is_min_val
    const ac_uint<29> tmp_167 = ac_uint<29>(((~arg_0) & 536870911));  // basic_invert
    const ac_uint<29> tmp_168 = ac_uint<29>((ac_uint<29>(tmp_167) + ac_uint<29>(ac_uint<1>(1))));  // basic_add
    const ac_uint<29> tmp_169 = ac_uint<29>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<29> tmp_170 = ac_uint<29>(((~tmp_169) & 536870911));  // basic_invert
    const ac_uint<29> tmp_171 = ac_uint<29>((tmp_166 != 0 ? ac_uint<29>(tmp_170) : ac_uint<29>(tmp_168)));  // basic_mux_2_1
    return tmp_171;
}
static inline ac_uint<29> q_add_sign_1(ac_uint<29> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<29> tmp_172 = q_neg_1(arg_0);  // q_neg
    const ac_uint<29> tmp_173 = ac_uint<29>((arg_1 != 0 ? ac_uint<29>(tmp_172) : ac_uint<29>(arg_0)));  // basic_mux_2_1
    return tmp_173;
}
static inline ac_uint<29> q_abs(ac_uint<29> arg_0) {  // q_abs
    const ac_uint<1> tmp_165 = q_sign_bit_1(arg_0);  // q_sign_bit
    const ac_uint<29> tmp_174 = q_add_sign_1(arg_0, tmp_165);  // q_add_sign
    return tmp_174;
}
static inline ac_uint<28> q_to_uq(ac_uint<29> arg_0) {  // q_to_uq
    const ac_uint<28> tmp_176 = ac_uint<28>(arg_0);  // basic_identity
    return tmp_176;
}
static inline ac_uint<1> uq_is_zero_1(ac_uint<28> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_191 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_192 = ac_uint<1>(((~tmp_191) & 1));  // basic_invert
    return tmp_192;
}
static inline ac_uint<5> lzc(ac_uint<28> arg_0) {  // lzc
    const ac_uint<1> tmp_195 = ac_uint<1>(((arg_0 >> 27) & 1));  // basic_select
    const ac_uint<1> tmp_196 = ac_uint<1>(((~tmp_195) & 1));  // basic_invert
    const ac_uint<1> tmp_197 = ac_uint<1>((ac_uint<1>(1) & tmp_196));  // basic_and
    const ac_uint<5> tmp_198 = ac_uint<5>((ac_uint<5>(ac_uint<5>(0)) + ac_uint<5>(tmp_197)));  // basic_add
    const ac_uint<1> tmp_199 = ac_uint<1>(((arg_0 >> 26) & 1));  // basic_select
    const ac_uint<1> tmp_200 = ac_uint<1>(((~tmp_199) & 1));  // basic_invert
    const ac_uint<1> tmp_201 = ac_uint<1>((tmp_197 & tmp_200));  // basic_and
    const ac_uint<5> tmp_202 = ac_uint<5>((ac_uint<5>(tmp_198) + ac_uint<5>(tmp_201)));  // basic_add
    const ac_uint<1> tmp_203 = ac_uint<1>(((arg_0 >> 25) & 1));  // basic_select
    const ac_uint<1> tmp_204 = ac_uint<1>(((~tmp_203) & 1));  // basic_invert
    const ac_uint<1> tmp_205 = ac_uint<1>((tmp_201 & tmp_204));  // basic_and
    const ac_uint<5> tmp_206 = ac_uint<5>((ac_uint<5>(tmp_202) + ac_uint<5>(tmp_205)));  // basic_add
    const ac_uint<1> tmp_207 = ac_uint<1>(((arg_0 >> 24) & 1));  // basic_select
    const ac_uint<1> tmp_208 = ac_uint<1>(((~tmp_207) & 1));  // basic_invert
    const ac_uint<1> tmp_209 = ac_uint<1>((tmp_205 & tmp_208));  // basic_and
    const ac_uint<5> tmp_210 = ac_uint<5>((ac_uint<5>(tmp_206) + ac_uint<5>(tmp_209)));  // basic_add
    const ac_uint<1> tmp_211 = ac_uint<1>(((arg_0 >> 23) & 1));  // basic_select
    const ac_uint<1> tmp_212 = ac_uint<1>(((~tmp_211) & 1));  // basic_invert
    const ac_uint<1> tmp_213 = ac_uint<1>((tmp_209 & tmp_212));  // basic_and
    const ac_uint<5> tmp_214 = ac_uint<5>((ac_uint<5>(tmp_210) + ac_uint<5>(tmp_213)));  // basic_add
    const ac_uint<1> tmp_215 = ac_uint<1>(((arg_0 >> 22) & 1));  // basic_select
    const ac_uint<1> tmp_216 = ac_uint<1>(((~tmp_215) & 1));  // basic_invert
    const ac_uint<1> tmp_217 = ac_uint<1>((tmp_213 & tmp_216));  // basic_and
    const ac_uint<5> tmp_218 = ac_uint<5>((ac_uint<5>(tmp_214) + ac_uint<5>(tmp_217)));  // basic_add
    const ac_uint<1> tmp_219 = ac_uint<1>(((arg_0 >> 21) & 1));  // basic_select
    const ac_uint<1> tmp_220 = ac_uint<1>(((~tmp_219) & 1));  // basic_invert
    const ac_uint<1> tmp_221 = ac_uint<1>((tmp_217 & tmp_220));  // basic_and
    const ac_uint<5> tmp_222 = ac_uint<5>((ac_uint<5>(tmp_218) + ac_uint<5>(tmp_221)));  // basic_add
    const ac_uint<1> tmp_223 = ac_uint<1>(((arg_0 >> 20) & 1));  // basic_select
    const ac_uint<1> tmp_224 = ac_uint<1>(((~tmp_223) & 1));  // basic_invert
    const ac_uint<1> tmp_225 = ac_uint<1>((tmp_221 & tmp_224));  // basic_and
    const ac_uint<5> tmp_226 = ac_uint<5>((ac_uint<5>(tmp_222) + ac_uint<5>(tmp_225)));  // basic_add
    const ac_uint<1> tmp_227 = ac_uint<1>(((arg_0 >> 19) & 1));  // basic_select
    const ac_uint<1> tmp_228 = ac_uint<1>(((~tmp_227) & 1));  // basic_invert
    const ac_uint<1> tmp_229 = ac_uint<1>((tmp_225 & tmp_228));  // basic_and
    const ac_uint<5> tmp_230 = ac_uint<5>((ac_uint<5>(tmp_226) + ac_uint<5>(tmp_229)));  // basic_add
    const ac_uint<1> tmp_231 = ac_uint<1>(((arg_0 >> 18) & 1));  // basic_select
    const ac_uint<1> tmp_232 = ac_uint<1>(((~tmp_231) & 1));  // basic_invert
    const ac_uint<1> tmp_233 = ac_uint<1>((tmp_229 & tmp_232));  // basic_and
    const ac_uint<5> tmp_234 = ac_uint<5>((ac_uint<5>(tmp_230) + ac_uint<5>(tmp_233)));  // basic_add
    const ac_uint<1> tmp_235 = ac_uint<1>(((arg_0 >> 17) & 1));  // basic_select
    const ac_uint<1> tmp_236 = ac_uint<1>(((~tmp_235) & 1));  // basic_invert
    const ac_uint<1> tmp_237 = ac_uint<1>((tmp_233 & tmp_236));  // basic_and
    const ac_uint<5> tmp_238 = ac_uint<5>((ac_uint<5>(tmp_234) + ac_uint<5>(tmp_237)));  // basic_add
    const ac_uint<1> tmp_239 = ac_uint<1>(((arg_0 >> 16) & 1));  // basic_select
    const ac_uint<1> tmp_240 = ac_uint<1>(((~tmp_239) & 1));  // basic_invert
    const ac_uint<1> tmp_241 = ac_uint<1>((tmp_237 & tmp_240));  // basic_and
    const ac_uint<5> tmp_242 = ac_uint<5>((ac_uint<5>(tmp_238) + ac_uint<5>(tmp_241)));  // basic_add
    const ac_uint<1> tmp_243 = ac_uint<1>(((arg_0 >> 15) & 1));  // basic_select
    const ac_uint<1> tmp_244 = ac_uint<1>(((~tmp_243) & 1));  // basic_invert
    const ac_uint<1> tmp_245 = ac_uint<1>((tmp_241 & tmp_244));  // basic_and
    const ac_uint<5> tmp_246 = ac_uint<5>((ac_uint<5>(tmp_242) + ac_uint<5>(tmp_245)));  // basic_add
    const ac_uint<1> tmp_247 = ac_uint<1>(((arg_0 >> 14) & 1));  // basic_select
    const ac_uint<1> tmp_248 = ac_uint<1>(((~tmp_247) & 1));  // basic_invert
    const ac_uint<1> tmp_249 = ac_uint<1>((tmp_245 & tmp_248));  // basic_and
    const ac_uint<5> tmp_250 = ac_uint<5>((ac_uint<5>(tmp_246) + ac_uint<5>(tmp_249)));  // basic_add
    const ac_uint<1> tmp_251 = ac_uint<1>(((arg_0 >> 13) & 1));  // basic_select
    const ac_uint<1> tmp_252 = ac_uint<1>(((~tmp_251) & 1));  // basic_invert
    const ac_uint<1> tmp_253 = ac_uint<1>((tmp_249 & tmp_252));  // basic_and
    const ac_uint<5> tmp_254 = ac_uint<5>((ac_uint<5>(tmp_250) + ac_uint<5>(tmp_253)));  // basic_add
    const ac_uint<1> tmp_255 = ac_uint<1>(((arg_0 >> 12) & 1));  // basic_select
    const ac_uint<1> tmp_256 = ac_uint<1>(((~tmp_255) & 1));  // basic_invert
    const ac_uint<1> tmp_257 = ac_uint<1>((tmp_253 & tmp_256));  // basic_and
    const ac_uint<5> tmp_258 = ac_uint<5>((ac_uint<5>(tmp_254) + ac_uint<5>(tmp_257)));  // basic_add
    const ac_uint<1> tmp_259 = ac_uint<1>(((arg_0 >> 11) & 1));  // basic_select
    const ac_uint<1> tmp_260 = ac_uint<1>(((~tmp_259) & 1));  // basic_invert
    const ac_uint<1> tmp_261 = ac_uint<1>((tmp_257 & tmp_260));  // basic_and
    const ac_uint<5> tmp_262 = ac_uint<5>((ac_uint<5>(tmp_258) + ac_uint<5>(tmp_261)));  // basic_add
    const ac_uint<1> tmp_263 = ac_uint<1>(((arg_0 >> 10) & 1));  // basic_select
    const ac_uint<1> tmp_264 = ac_uint<1>(((~tmp_263) & 1));  // basic_invert
    const ac_uint<1> tmp_265 = ac_uint<1>((tmp_261 & tmp_264));  // basic_and
    const ac_uint<5> tmp_266 = ac_uint<5>((ac_uint<5>(tmp_262) + ac_uint<5>(tmp_265)));  // basic_add
    const ac_uint<1> tmp_267 = ac_uint<1>(((arg_0 >> 9) & 1));  // basic_select
    const ac_uint<1> tmp_268 = ac_uint<1>(((~tmp_267) & 1));  // basic_invert
    const ac_uint<1> tmp_269 = ac_uint<1>((tmp_265 & tmp_268));  // basic_and
    const ac_uint<5> tmp_270 = ac_uint<5>((ac_uint<5>(tmp_266) + ac_uint<5>(tmp_269)));  // basic_add
    const ac_uint<1> tmp_271 = ac_uint<1>(((arg_0 >> 8) & 1));  // basic_select
    const ac_uint<1> tmp_272 = ac_uint<1>(((~tmp_271) & 1));  // basic_invert
    const ac_uint<1> tmp_273 = ac_uint<1>((tmp_269 & tmp_272));  // basic_and
    const ac_uint<5> tmp_274 = ac_uint<5>((ac_uint<5>(tmp_270) + ac_uint<5>(tmp_273)));  // basic_add
    const ac_uint<1> tmp_275 = ac_uint<1>(((arg_0 >> 7) & 1));  // basic_select
    const ac_uint<1> tmp_276 = ac_uint<1>(((~tmp_275) & 1));  // basic_invert
    const ac_uint<1> tmp_277 = ac_uint<1>((tmp_273 & tmp_276));  // basic_and
    const ac_uint<5> tmp_278 = ac_uint<5>((ac_uint<5>(tmp_274) + ac_uint<5>(tmp_277)));  // basic_add
    const ac_uint<1> tmp_279 = ac_uint<1>(((arg_0 >> 6) & 1));  // basic_select
    const ac_uint<1> tmp_280 = ac_uint<1>(((~tmp_279) & 1));  // basic_invert
    const ac_uint<1> tmp_281 = ac_uint<1>((tmp_277 & tmp_280));  // basic_and
    const ac_uint<5> tmp_282 = ac_uint<5>((ac_uint<5>(tmp_278) + ac_uint<5>(tmp_281)));  // basic_add
    const ac_uint<1> tmp_283 = ac_uint<1>(((arg_0 >> 5) & 1));  // basic_select
    const ac_uint<1> tmp_284 = ac_uint<1>(((~tmp_283) & 1));  // basic_invert
    const ac_uint<1> tmp_285 = ac_uint<1>((tmp_281 & tmp_284));  // basic_and
    const ac_uint<5> tmp_286 = ac_uint<5>((ac_uint<5>(tmp_282) + ac_uint<5>(tmp_285)));  // basic_add
    const ac_uint<1> tmp_287 = ac_uint<1>(((arg_0 >> 4) & 1));  // basic_select
    const ac_uint<1> tmp_288 = ac_uint<1>(((~tmp_287) & 1));  // basic_invert
    const ac_uint<1> tmp_289 = ac_uint<1>((tmp_285 & tmp_288));  // basic_and
    const ac_uint<5> tmp_290 = ac_uint<5>((ac_uint<5>(tmp_286) + ac_uint<5>(tmp_289)));  // basic_add
    const ac_uint<1> tmp_291 = ac_uint<1>(((arg_0 >> 3) & 1));  // basic_select
    const ac_uint<1> tmp_292 = ac_uint<1>(((~tmp_291) & 1));  // basic_invert
    const ac_uint<1> tmp_293 = ac_uint<1>((tmp_289 & tmp_292));  // basic_and
    const ac_uint<5> tmp_294 = ac_uint<5>((ac_uint<5>(tmp_290) + ac_uint<5>(tmp_293)));  // basic_add
    const ac_uint<1> tmp_295 = ac_uint<1>(((arg_0 >> 2) & 1));  // basic_select
    const ac_uint<1> tmp_296 = ac_uint<1>(((~tmp_295) & 1));  // basic_invert
    const ac_uint<1> tmp_297 = ac_uint<1>((tmp_293 & tmp_296));  // basic_and
    const ac_uint<5> tmp_298 = ac_uint<5>((ac_uint<5>(tmp_294) + ac_uint<5>(tmp_297)));  // basic_add
    const ac_uint<1> tmp_299 = ac_uint<1>(((arg_0 >> 1) & 1));  // basic_select
    const ac_uint<1> tmp_300 = ac_uint<1>(((~tmp_299) & 1));  // basic_invert
    const ac_uint<1> tmp_301 = ac_uint<1>((tmp_297 & tmp_300));  // basic_and
    const ac_uint<5> tmp_302 = ac_uint<5>((ac_uint<5>(tmp_298) + ac_uint<5>(tmp_301)));  // basic_add
    const ac_uint<1> tmp_303 = ac_uint<1>(((arg_0 >> 0) & 1));  // basic_select
    const ac_uint<1> tmp_304 = ac_uint<1>(((~tmp_303) & 1));  // basic_invert
    const ac_uint<1> tmp_305 = ac_uint<1>((tmp_301 & tmp_304));  // basic_and
    const ac_uint<5> tmp_306 = ac_uint<5>((ac_uint<5>(tmp_302) + ac_uint<5>(tmp_305)));  // basic_add
    return tmp_306;
}
static inline ac_uint<4> uq_add_2(ac_uint<3> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<4> tmp_308 = ac_uint<4>(arg_0);  // basic_identity
    const ac_uint<4> tmp_309 = ac_uint<4>(arg_1);  // basic_identity
    const std::tuple<ac_uint<4>, ac_uint<4>> tmp_310 = std::make_tuple(tmp_308, tmp_309);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<4> tmp_311 = ac_uint<4>(std::get<0>(tmp_310));  // _basic_get_item_0
    const ac_uint<4> tmp_312 = ac_uint<4>(std::get<1>(tmp_310));  // _basic_get_item_1
    const ac_uint<4> tmp_313 = ac_uint<4>((ac_uint<4>(tmp_311) + ac_uint<4>(tmp_312)));  // basic_add
    return tmp_313;
}
static inline ac_uint<6> uq_to_q_2(ac_uint<5> arg_0) {  // uq_to_q
    const ac_uint<4> tmp_314 = uq_add_2(ac_uint<3>(5), ac_uint<1>(1));  // uq_add
    const ac_uint<6> tmp_315 = ac_uint<6>(0);  // q_alloc
    const ac_uint<6> tmp_316 = ac_uint<6>(arg_0);  // basic_identity
    return tmp_316;
}
static inline ac_uint<3> uq_add_3(ac_uint<2> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<3> tmp_318 = ac_uint<3>(arg_0);  // basic_identity
    const ac_uint<3> tmp_319 = ac_uint<3>(arg_1);  // basic_identity
    const std::tuple<ac_uint<3>, ac_uint<3>> tmp_320 = std::make_tuple(tmp_318, tmp_319);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<3> tmp_321 = ac_uint<3>(std::get<0>(tmp_320));  // _basic_get_item_0
    const ac_uint<3> tmp_322 = ac_uint<3>(std::get<1>(tmp_320));  // _basic_get_item_1
    const ac_uint<3> tmp_323 = ac_uint<3>((ac_uint<3>(tmp_321) + ac_uint<3>(tmp_322)));  // basic_add
    return tmp_323;
}
static inline ac_uint<3> uq_to_q_3(ac_uint<2> arg_0) {  // uq_to_q
    const ac_uint<3> tmp_324 = uq_add_3(ac_uint<2>(2), ac_uint<1>(1));  // uq_add
    const ac_uint<3> tmp_325 = ac_uint<3>(0);  // q_alloc
    const ac_uint<3> tmp_326 = ac_uint<3>(arg_0);  // basic_identity
    return tmp_326;
}
static inline ac_uint<1> q_sign_bit_2(ac_uint<6> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_328 = ac_uint<1>(((arg_0 >> 5) & 1));  // basic_select
    return tmp_328;
}
static inline ac_uint<7> q_sign_extend_1(ac_uint<6> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_329 = q_sign_bit_2(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_330 = ac_uint<2>((ac_uint<1>(1) >= 2 ? ac_uint<2>(0) : (ac_uint<2>(tmp_329) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_331 = ac_uint<1>((ac_uint<1>(tmp_330) - ac_uint<1>(tmp_329)));  // basic_sub
    const ac_uint<7> tmp_332 = ac_uint<7>(0);  // q_alloc
    const ac_uint<7> tmp_333 = ac_uint<7>(((ac_uint<7>(tmp_331) << 6) | arg_0));  // basic_concat
    return tmp_333;
}
static inline ac_uint<1> q_sign_bit_3(ac_uint<3> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_335 = ac_uint<1>(((arg_0 >> 2) & 1));  // basic_select
    return tmp_335;
}
static inline ac_uint<7> q_sign_extend_2(ac_uint<3> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_336 = q_sign_bit_3(arg_0);  // q_sign_bit
    const ac_uint<5> tmp_337 = ac_uint<5>((ac_uint<3>(4) >= 5 ? ac_uint<5>(0) : (ac_uint<5>(tmp_336) << ac_uint<3>(4))));  // basic_lshift
    const ac_uint<4> tmp_338 = ac_uint<4>((ac_uint<4>(tmp_337) - ac_uint<4>(tmp_336)));  // basic_sub
    const ac_uint<7> tmp_339 = ac_uint<7>(0);  // q_alloc
    const ac_uint<7> tmp_340 = ac_uint<7>(((ac_uint<7>(tmp_338) << 3) | arg_0));  // basic_concat
    return tmp_340;
}
static inline ac_uint<7> q_sub(ac_uint<6> arg_0, ac_uint<3> arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const ac_uint<7> tmp_334 = q_sign_extend_1(arg_0);  // q_sign_extend
    const ac_uint<7> tmp_341 = q_sign_extend_2(arg_1);  // q_sign_extend
    const std::tuple<ac_uint<7>, ac_uint<7>> tmp_342 = std::make_tuple(tmp_334, tmp_341);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<7> tmp_343 = ac_uint<7>(std::get<0>(tmp_342));  // _basic_get_item_0
    const ac_uint<7> tmp_344 = ac_uint<7>(std::get<1>(tmp_342));  // _basic_get_item_1
    const ac_uint<7> tmp_345 = ac_uint<7>((ac_uint<7>(tmp_343) - ac_uint<7>(tmp_344)));  // basic_sub
    return tmp_345;
}
static inline ac_uint<1> q_sign_bit_4(ac_uint<7> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_347 = ac_uint<1>(((arg_0 >> 6) & 1));  // basic_select
    return tmp_347;
}
static inline ac_uint<8> q_sign_extend_3(ac_uint<7> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_348 = q_sign_bit_4(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_349 = ac_uint<2>((ac_uint<1>(1) >= 2 ? ac_uint<2>(0) : (ac_uint<2>(tmp_348) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_350 = ac_uint<1>((ac_uint<1>(tmp_349) - ac_uint<1>(tmp_348)));  // basic_sub
    const ac_uint<8> tmp_351 = ac_uint<8>(0);  // q_alloc
    const ac_uint<8> tmp_352 = ac_uint<8>(((ac_uint<8>(tmp_350) << 7) | arg_0));  // basic_concat
    return tmp_352;
}
static inline ac_uint<1> q_sign_bit_5(ac_uint<2> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_354 = ac_uint<1>(((arg_0 >> 1) & 1));  // basic_select
    return tmp_354;
}
static inline ac_uint<8> q_sign_extend_4(ac_uint<2> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_355 = q_sign_bit_5(arg_0);  // q_sign_bit
    const ac_uint<7> tmp_356 = ac_uint<7>((ac_uint<3>(6) >= 7 ? ac_uint<7>(0) : (ac_uint<7>(tmp_355) << ac_uint<3>(6))));  // basic_lshift
    const ac_uint<6> tmp_357 = ac_uint<6>((ac_uint<6>(tmp_356) - ac_uint<6>(tmp_355)));  // basic_sub
    const ac_uint<8> tmp_358 = ac_uint<8>(0);  // q_alloc
    const ac_uint<8> tmp_359 = ac_uint<8>(((ac_uint<8>(tmp_357) << 2) | arg_0));  // basic_concat
    return tmp_359;
}
static inline ac_uint<8> q_add_1(ac_uint<7> arg_0, ac_uint<2> arg_1) {  // q_add
    // begin inline primitive q_aligner
    const ac_uint<8> tmp_353 = q_sign_extend_3(arg_0);  // q_sign_extend
    const ac_uint<8> tmp_360 = q_sign_extend_4(arg_1);  // q_sign_extend
    const std::tuple<ac_uint<8>, ac_uint<8>> tmp_361 = std::make_tuple(tmp_353, tmp_360);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<8> tmp_362 = ac_uint<8>(std::get<0>(tmp_361));  // _basic_get_item_0
    const ac_uint<8> tmp_363 = ac_uint<8>(std::get<1>(tmp_361));  // _basic_get_item_1
    const ac_uint<8> tmp_364 = ac_uint<8>((ac_uint<8>(tmp_362) + ac_uint<8>(tmp_363)));  // basic_add
    return tmp_364;
}
static inline ac_uint<1> q_sign_bit_6(ac_uint<8> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_366 = ac_uint<1>(((arg_0 >> 7) & 1));  // basic_select
    return tmp_366;
}
static inline ac_uint<29> uq_resize_2(ac_uint<28> arg_0) {  // uq_resize
    const ac_uint<29> tmp_368 = ac_uint<29>((ac_uint<1>(1) >= 29 ? ac_uint<29>(0) : (ac_uint<29>(arg_0) << ac_uint<1>(1))));  // basic_lshift
    return tmp_368;
}
static inline ac_uint<8> q_neg_2(ac_uint<8> arg_0) {  // q_neg
    const ac_uint<1> tmp_371 = ac_uint<1>((arg_0 == 128));  // _q_is_min_val
    const ac_uint<8> tmp_372 = ac_uint<8>(((~arg_0) & 255));  // basic_invert
    const ac_uint<8> tmp_373 = ac_uint<8>((ac_uint<8>(tmp_372) + ac_uint<8>(ac_uint<1>(1))));  // basic_add
    const ac_uint<8> tmp_374 = ac_uint<8>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<8> tmp_375 = ac_uint<8>(((~tmp_374) & 255));  // basic_invert
    const ac_uint<8> tmp_376 = ac_uint<8>((tmp_371 != 0 ? ac_uint<8>(tmp_375) : ac_uint<8>(tmp_373)));  // basic_mux_2_1
    return tmp_376;
}
static inline ac_uint<8> q_add_sign_2(ac_uint<8> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<8> tmp_377 = q_neg_2(arg_0);  // q_neg
    const ac_uint<8> tmp_378 = ac_uint<8>((arg_1 != 0 ? ac_uint<8>(tmp_377) : ac_uint<8>(arg_0)));  // basic_mux_2_1
    return tmp_378;
}
static inline ac_uint<8> q_abs_1(ac_uint<8> arg_0) {  // q_abs
    const ac_uint<1> tmp_370 = q_sign_bit_6(arg_0);  // q_sign_bit
    const ac_uint<8> tmp_379 = q_add_sign_2(arg_0, tmp_370);  // q_add_sign
    return tmp_379;
}
static inline ac_uint<7> q_to_uq_1(ac_uint<8> arg_0) {  // q_to_uq
    const ac_uint<7> tmp_381 = ac_uint<7>(arg_0);  // basic_identity
    return tmp_381;
}
static inline ac_uint<29> uq_lshift(ac_uint<29> arg_0, ac_uint<7> arg_1) {  // uq_lshift
    const ac_uint<29> tmp_383 = ac_uint<29>((arg_1 >= 29 ? ac_uint<29>(0) : (ac_uint<29>(arg_0) << arg_1)));  // basic_lshift
    return tmp_383;
}
static inline ac_uint<29> uq_rshift_1(ac_uint<29> arg_0, ac_uint<7> arg_1) {  // uq_rshift
    const ac_uint<29> tmp_385 = ac_uint<29>((arg_1 >= 29 ? ac_uint<29>(0) : (arg_0 >> arg_1)));  // basic_rshift
    return tmp_385;
}
static inline ac_uint<1> uq_is_zero_2(ac_uint<7> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_387 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_388 = ac_uint<1>(((~tmp_387) & 1));  // basic_invert
    return tmp_388;
}
static inline ac_uint<1> uq_ge_1(ac_uint<7> arg_0, ac_uint<5> arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const ac_uint<7> tmp_390 = ac_uint<7>(arg_1);  // basic_identity
    const std::tuple<ac_uint<7>, ac_uint<7>> tmp_391 = std::make_tuple(arg_0, tmp_390);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<7> tmp_392 = ac_uint<7>(std::get<0>(tmp_391));  // _basic_get_item_0
    const ac_uint<7> tmp_393 = ac_uint<7>(std::get<1>(tmp_391));  // _basic_get_item_1
    const ac_uint<1> tmp_394 = ac_uint<1>((tmp_392 >= tmp_393));  // basic_greater_or_equal
    return tmp_394;
}
static inline ac_uint<8> uq_sub_2(ac_uint<5> arg_0, ac_uint<7> arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const ac_uint<8> tmp_396 = ac_uint<8>(arg_0);  // basic_identity
    const ac_uint<8> tmp_397 = ac_uint<8>(arg_1);  // basic_identity
    const std::tuple<ac_uint<8>, ac_uint<8>> tmp_398 = std::make_tuple(tmp_396, tmp_397);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<8> tmp_399 = ac_uint<8>(std::get<0>(tmp_398));  // _basic_get_item_0
    const ac_uint<8> tmp_400 = ac_uint<8>(std::get<1>(tmp_398));  // _basic_get_item_1
    const ac_uint<8> tmp_401 = ac_uint<8>((ac_uint<8>(tmp_399) - ac_uint<8>(tmp_400)));  // basic_sub
    return tmp_401;
}
static inline ac_uint<29> uq_rshift_jam_1(ac_uint<29> arg_0, ac_uint<7> arg_1) {  // uq_rshift_jam
    const ac_uint<29> tmp_386 = uq_rshift_1(arg_0, arg_1);  // uq_rshift
    const ac_uint<1> tmp_389 = uq_is_zero_2(arg_1);  // uq_is_zero
    const ac_uint<1> tmp_395 = uq_ge_1(arg_1, ac_uint<5>(29));  // uq_ge
    const ac_uint<8> tmp_402 = uq_sub_2(ac_uint<5>(29), arg_1);  // uq_sub
    const ac_uint<29> tmp_403 = ac_uint<29>((tmp_402 >= 29 ? ac_uint<29>(0) : (ac_uint<29>(arg_0) << tmp_402)));  // basic_lshift
    const ac_uint<1> tmp_404 = ac_uint<1>((tmp_403 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_405 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_406 = ac_uint<1>((tmp_395 != 0 ? ac_uint<1>(tmp_405) : ac_uint<1>(tmp_404)));  // basic_mux_2_1
    const ac_uint<1> tmp_407 = ac_uint<1>((tmp_389 != 0 ? ac_uint<1>(ac_uint<1>(0)) : ac_uint<1>(tmp_406)));  // basic_mux_2_1
    const ac_uint<29> tmp_408 = ac_uint<29>((tmp_386 | tmp_407));  // basic_or
    return tmp_408;
}
static inline ac_uint<1> q_sign_bit_7(ac_uint<9> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_411 = ac_uint<1>(((arg_0 >> 8) & 1));  // basic_select
    return tmp_411;
}
static inline ac_uint<10> q_sign_extend_5(ac_uint<9> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_412 = q_sign_bit_7(arg_0);  // q_sign_bit
    const ac_uint<2> tmp_413 = ac_uint<2>((ac_uint<1>(1) >= 2 ? ac_uint<2>(0) : (ac_uint<2>(tmp_412) << ac_uint<1>(1))));  // basic_lshift
    const ac_uint<1> tmp_414 = ac_uint<1>((ac_uint<1>(tmp_413) - ac_uint<1>(tmp_412)));  // basic_sub
    const ac_uint<10> tmp_415 = ac_uint<10>(0);  // q_alloc
    const ac_uint<10> tmp_416 = ac_uint<10>(((ac_uint<10>(tmp_414) << 9) | arg_0));  // basic_concat
    return tmp_416;
}
static inline ac_uint<10> q_sign_extend_6(ac_uint<8> arg_0) {  // q_sign_extend
    const ac_uint<1> tmp_418 = q_sign_bit_6(arg_0);  // q_sign_bit
    const ac_uint<3> tmp_419 = ac_uint<3>((ac_uint<2>(2) >= 3 ? ac_uint<3>(0) : (ac_uint<3>(tmp_418) << ac_uint<2>(2))));  // basic_lshift
    const ac_uint<2> tmp_420 = ac_uint<2>((ac_uint<2>(tmp_419) - ac_uint<2>(tmp_418)));  // basic_sub
    const ac_uint<10> tmp_421 = ac_uint<10>(0);  // q_alloc
    const ac_uint<10> tmp_422 = ac_uint<10>(((ac_uint<10>(tmp_420) << 8) | arg_0));  // basic_concat
    return tmp_422;
}
static inline ac_uint<10> q_sub_1(ac_uint<9> arg_0, ac_uint<8> arg_1) {  // q_sub
    // begin inline primitive q_aligner
    const ac_uint<10> tmp_417 = q_sign_extend_5(arg_0);  // q_sign_extend
    const ac_uint<10> tmp_423 = q_sign_extend_6(arg_1);  // q_sign_extend
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_424 = std::make_tuple(tmp_417, tmp_423);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<10> tmp_425 = ac_uint<10>(std::get<0>(tmp_424));  // _basic_get_item_0
    const ac_uint<10> tmp_426 = ac_uint<10>(std::get<1>(tmp_424));  // _basic_get_item_1
    const ac_uint<10> tmp_427 = ac_uint<10>((ac_uint<10>(tmp_425) - ac_uint<10>(tmp_426)));  // basic_sub
    return tmp_427;
}
static inline ac_uint<10> q_add_2(ac_uint<9> arg_0, ac_uint<8> arg_1) {  // q_add
    // begin inline primitive q_aligner
    const ac_uint<10> tmp_429 = q_sign_extend_5(arg_0);  // q_sign_extend
    const ac_uint<10> tmp_430 = q_sign_extend_6(arg_1);  // q_sign_extend
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_431 = std::make_tuple(tmp_429, tmp_430);  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const ac_uint<10> tmp_432 = ac_uint<10>(std::get<0>(tmp_431));  // _basic_get_item_0
    const ac_uint<10> tmp_433 = ac_uint<10>(std::get<1>(tmp_431));  // _basic_get_item_1
    const ac_uint<10> tmp_434 = ac_uint<10>((ac_uint<10>(tmp_432) + ac_uint<10>(tmp_433)));  // basic_add
    return tmp_434;
}
static inline ac_uint<1> q_is_zero(ac_uint<10> arg_0) {  // q_is_zero
    const ac_uint<1> tmp_441 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_442 = ac_uint<1>(((~tmp_441) & 1));  // basic_invert
    return tmp_442;
}
static inline ac_uint<1> q_sign_bit_8(ac_uint<10> arg_0) {  // q_sign_bit
    const ac_uint<1> tmp_444 = ac_uint<1>(((arg_0 >> 9) & 1));  // basic_select
    return tmp_444;
}
static inline ac_uint<10> q_neg_3(ac_uint<10> arg_0) {  // q_neg
    const ac_uint<1> tmp_448 = ac_uint<1>((arg_0 == 512));  // _q_is_min_val
    const ac_uint<10> tmp_449 = ac_uint<10>(((~arg_0) & 1023));  // basic_invert
    const ac_uint<10> tmp_450 = ac_uint<10>((ac_uint<10>(tmp_449) + ac_uint<10>(ac_uint<1>(1))));  // basic_add
    const ac_uint<10> tmp_451 = ac_uint<10>((arg_0 ^ arg_0));  // basic_xor
    const ac_uint<10> tmp_452 = ac_uint<10>(((~tmp_451) & 1023));  // basic_invert
    const ac_uint<10> tmp_453 = ac_uint<10>((tmp_448 != 0 ? ac_uint<10>(tmp_452) : ac_uint<10>(tmp_450)));  // basic_mux_2_1
    return tmp_453;
}
static inline ac_uint<10> q_add_sign_3(ac_uint<10> arg_0, ac_uint<1> arg_1) {  // q_add_sign
    const ac_uint<10> tmp_454 = q_neg_3(arg_0);  // q_neg
    const ac_uint<10> tmp_455 = ac_uint<10>((arg_1 != 0 ? ac_uint<10>(tmp_454) : ac_uint<10>(arg_0)));  // basic_mux_2_1
    return tmp_455;
}
static inline ac_uint<10> q_abs_2(ac_uint<10> arg_0) {  // q_abs
    const ac_uint<1> tmp_447 = q_sign_bit_8(arg_0);  // q_sign_bit
    const ac_uint<10> tmp_456 = q_add_sign_3(arg_0, tmp_447);  // q_add_sign
    return tmp_456;
}
static inline ac_uint<9> q_to_uq_2(ac_uint<10> arg_0) {  // q_to_uq
    const ac_uint<9> tmp_458 = ac_uint<9>(arg_0);  // basic_identity
    return tmp_458;
}
static inline ac_uint<10> uq_add_4(ac_uint<1> arg_0, ac_uint<9> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_460 = ac_uint<10>(arg_0);  // basic_identity
    const ac_uint<10> tmp_461 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_462 = std::make_tuple(tmp_460, tmp_461);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_463 = ac_uint<10>(std::get<0>(tmp_462));  // _basic_get_item_0
    const ac_uint<10> tmp_464 = ac_uint<10>(std::get<1>(tmp_462));  // _basic_get_item_1
    const ac_uint<10> tmp_465 = ac_uint<10>((ac_uint<10>(tmp_463) + ac_uint<10>(tmp_464)));  // basic_add
    return tmp_465;
}
static inline ac_uint<38> uq_rshift_2(ac_uint<38> arg_0, ac_uint<10> arg_1) {  // uq_rshift
    const ac_uint<38> tmp_468 = ac_uint<38>((arg_1 >= 38 ? ac_uint<38>(0) : (arg_0 >> arg_1)));  // basic_rshift
    return tmp_468;
}
static inline ac_uint<1> uq_is_zero_3(ac_uint<10> arg_0) {  // uq_is_zero
    const ac_uint<1> tmp_470 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_471 = ac_uint<1>(((~tmp_470) & 1));  // basic_invert
    return tmp_471;
}
static inline ac_uint<1> uq_ge_2(ac_uint<10> arg_0, ac_uint<6> arg_1) {  // uq_ge
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_473 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_474 = std::make_tuple(arg_0, tmp_473);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_475 = ac_uint<10>(std::get<0>(tmp_474));  // _basic_get_item_0
    const ac_uint<10> tmp_476 = ac_uint<10>(std::get<1>(tmp_474));  // _basic_get_item_1
    const ac_uint<1> tmp_477 = ac_uint<1>((tmp_475 >= tmp_476));  // basic_greater_or_equal
    return tmp_477;
}
static inline ac_uint<11> uq_sub_3(ac_uint<6> arg_0, ac_uint<10> arg_1) {  // uq_sub
    // begin inline primitive uq_aligner
    const ac_uint<11> tmp_479 = ac_uint<11>(arg_0);  // basic_identity
    const ac_uint<11> tmp_480 = ac_uint<11>(arg_1);  // basic_identity
    const std::tuple<ac_uint<11>, ac_uint<11>> tmp_481 = std::make_tuple(tmp_479, tmp_480);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<11> tmp_482 = ac_uint<11>(std::get<0>(tmp_481));  // _basic_get_item_0
    const ac_uint<11> tmp_483 = ac_uint<11>(std::get<1>(tmp_481));  // _basic_get_item_1
    const ac_uint<11> tmp_484 = ac_uint<11>((ac_uint<11>(tmp_482) - ac_uint<11>(tmp_483)));  // basic_sub
    return tmp_484;
}
static inline ac_uint<38> uq_rshift_jam_2(ac_uint<38> arg_0, ac_uint<10> arg_1) {  // uq_rshift_jam
    const ac_uint<38> tmp_469 = uq_rshift_2(arg_0, arg_1);  // uq_rshift
    const ac_uint<1> tmp_472 = uq_is_zero_3(arg_1);  // uq_is_zero
    const ac_uint<1> tmp_478 = uq_ge_2(arg_1, ac_uint<6>(38));  // uq_ge
    const ac_uint<11> tmp_485 = uq_sub_3(ac_uint<6>(38), arg_1);  // uq_sub
    const ac_uint<38> tmp_486 = ac_uint<38>((tmp_485 >= 38 ? ac_uint<38>(0) : (ac_uint<38>(arg_0) << tmp_485)));  // basic_lshift
    const ac_uint<1> tmp_487 = ac_uint<1>((tmp_486 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_488 = ac_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_489 = ac_uint<1>((tmp_478 != 0 ? ac_uint<1>(tmp_488) : ac_uint<1>(tmp_487)));  // basic_mux_2_1
    const ac_uint<1> tmp_490 = ac_uint<1>((tmp_472 != 0 ? ac_uint<1>(ac_uint<1>(0)) : ac_uint<1>(tmp_489)));  // basic_mux_2_1
    const ac_uint<38> tmp_491 = ac_uint<38>((tmp_469 | tmp_490));  // basic_or
    return tmp_491;
}
static inline ac_uint<37> drop_implicit_bit(ac_uint<38> arg_0) {  // drop_implicit_bit
    const ac_uint<37> tmp_496 = ac_uint<37>(((arg_0 >> 0) & 137438953471));  // basic_select
    return tmp_496;
}
static inline ac_uint<23> uq_resize_3(ac_uint<37> arg_0) {  // uq_resize
    const ac_uint<23> tmp_500 = ac_uint<23>((ac_uint<4>(14) >= 37 ? ac_uint<37>(0) : (arg_0 >> ac_uint<4>(14))));  // basic_rshift
    return tmp_500;
}
static inline ac_uint<24> uq_add_5(ac_uint<23> arg_0, ac_uint<23> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<24> tmp_511 = ac_uint<24>(arg_0);  // basic_identity
    const ac_uint<24> tmp_512 = ac_uint<24>(arg_1);  // basic_identity
    const std::tuple<ac_uint<24>, ac_uint<24>> tmp_513 = std::make_tuple(tmp_511, tmp_512);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<24> tmp_514 = ac_uint<24>(std::get<0>(tmp_513));  // _basic_get_item_0
    const ac_uint<24> tmp_515 = ac_uint<24>(std::get<1>(tmp_513));  // _basic_get_item_1
    const ac_uint<24> tmp_516 = ac_uint<24>((ac_uint<24>(tmp_514) + ac_uint<24>(tmp_515)));  // basic_add
    return tmp_516;
}
static inline ac_uint<10> uq_add_6(ac_uint<9> arg_0, ac_uint<1> arg_1) {  // uq_add
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_523 = ac_uint<10>(arg_0);  // basic_identity
    const ac_uint<10> tmp_524 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_525 = std::make_tuple(tmp_523, tmp_524);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_526 = ac_uint<10>(std::get<0>(tmp_525));  // _basic_get_item_0
    const ac_uint<10> tmp_527 = ac_uint<10>(std::get<1>(tmp_525));  // _basic_get_item_1
    const ac_uint<10> tmp_528 = ac_uint<10>((ac_uint<10>(tmp_526) + ac_uint<10>(tmp_527)));  // basic_add
    return tmp_528;
}
static inline ac_uint<10> uq_min(ac_uint<10> arg_0, ac_uint<8> arg_1) {  // uq_min
    // begin inline primitive uq_aligner
    const ac_uint<10> tmp_537 = ac_uint<10>(arg_1);  // basic_identity
    const std::tuple<ac_uint<10>, ac_uint<10>> tmp_538 = std::make_tuple(arg_0, tmp_537);  // basic_tuple_maker_2
    // end inline primitive uq_aligner
    const ac_uint<10> tmp_539 = ac_uint<10>(std::get<0>(tmp_538));  // _basic_get_item_0
    const ac_uint<10> tmp_540 = ac_uint<10>(std::get<1>(tmp_538));  // _basic_get_item_1
    const ac_uint<10> tmp_541 = ac_uint<10>((tmp_539 < tmp_540 ? ac_uint<10>(tmp_539) : ac_uint<10>(tmp_540)));  // basic_min
    return tmp_541;
}
static inline ac_uint<32> fp32_pack(ac_uint<1> arg_0, ac_uint<8> arg_1, ac_uint<23> arg_2) {  // fp32_pack
    const ac_uint<32> tmp_550 = ac_uint<32>(((ac_uint<32>(arg_0) << 31) | (ac_uint<32>(arg_1) << 23) | ac_uint<32>(arg_2)));  // float32_alloc
    return tmp_550;
}
static inline ac_uint<32> fp32_encode(ac_uint<1> arg_0, ac_uint<9> arg_1, ac_uint<28> arg_2, ac_uint<1> arg_3, ac_uint<1> arg_4) {  // fp32_encode
    const ac_uint<32> tmp_190 = ac_uint<32>((arg_0 != 0 ? ac_uint<32>(ac_uint<32>(4286578688)) : ac_uint<32>(ac_uint<32>(2139095040))));  // basic_mux_2_1
    const ac_uint<1> tmp_193 = uq_is_zero_1(arg_2);  // uq_is_zero
    const ac_uint<32> tmp_194 = ac_uint<32>((arg_0 != 0 ? ac_uint<32>(ac_uint<32>(2147483648)) : ac_uint<32>(ac_uint<32>(0))));  // basic_mux_2_1
    // begin inline primitive normalize_to_1_xxx
    const ac_uint<5> tmp_307 = lzc(arg_2);  // lzc
    const ac_uint<6> tmp_317 = uq_to_q_2(tmp_307);  // uq_to_q
    const ac_uint<3> tmp_327 = uq_to_q_3(ac_uint<2>(2));  // uq_to_q
    const ac_uint<7> tmp_346 = q_sub(tmp_317, tmp_327);  // q_sub
    const ac_uint<8> tmp_365 = q_add_1(tmp_346, ac_uint<2>(1));  // q_add
    const ac_uint<1> tmp_367 = q_sign_bit_6(tmp_365);  // q_sign_bit
    const ac_uint<29> tmp_369 = uq_resize_2(arg_2);  // uq_resize
    const ac_uint<8> tmp_380 = q_abs_1(tmp_365);  // q_abs
    const ac_uint<7> tmp_382 = q_to_uq_1(tmp_380);  // q_to_uq
    const ac_uint<29> tmp_384 = uq_lshift(tmp_369, tmp_382);  // uq_lshift
    const ac_uint<29> tmp_409 = uq_rshift_jam_1(tmp_369, tmp_382);  // uq_rshift_jam
    const ac_uint<28> tmp_410 = ac_uint<28>((tmp_367 != 0 ? ac_uint<28>(tmp_409) : ac_uint<28>(tmp_384)));  // basic_mux_2_1
    const ac_uint<10> tmp_428 = q_sub_1(arg_1, tmp_380);  // q_sub
    const ac_uint<10> tmp_435 = q_add_2(arg_1, tmp_380);  // q_add
    const ac_uint<10> tmp_436 = ac_uint<10>((tmp_367 != 0 ? ac_uint<10>(tmp_435) : ac_uint<10>(tmp_428)));  // basic_mux_2_1
    const std::tuple<ac_uint<28>, ac_uint<10>> tmp_437 = std::make_tuple(tmp_410, tmp_436);  // basic_tuple_maker_2
    // end inline primitive normalize_to_1_xxx
    const ac_uint<28> tmp_438 = ac_uint<28>(std::get<0>(tmp_437));  // _basic_get_item_0
    const ac_uint<10> tmp_439 = ac_uint<10>(std::get<1>(tmp_437));  // _basic_get_item_1
    // begin inline primitive shift_if_subnormal
    const ac_uint<38> tmp_440 = ac_uint<38>((ac_uint<4>(10) >= 38 ? ac_uint<38>(0) : (ac_uint<38>(tmp_438) << ac_uint<4>(10))));  // basic_lshift
    const ac_uint<1> tmp_443 = q_is_zero(tmp_439);  // q_is_zero
    const ac_uint<1> tmp_445 = q_sign_bit_8(tmp_439);  // q_sign_bit
    const ac_uint<1> tmp_446 = ac_uint<1>((tmp_443 | tmp_445));  // basic_or
    const ac_uint<10> tmp_457 = q_abs_2(tmp_439);  // q_abs
    const ac_uint<9> tmp_459 = q_to_uq_2(tmp_457);  // q_to_uq
    const ac_uint<10> tmp_466 = uq_add_4(ac_uint<1>(1), tmp_459);  // uq_add
    const ac_uint<10> tmp_467 = ac_uint<10>((tmp_446 != 0 ? ac_uint<10>(tmp_466) : ac_uint<10>(ac_uint<1>(0))));  // basic_mux_2_1
    const ac_uint<38> tmp_492 = uq_rshift_jam_2(tmp_440, tmp_467);  // uq_rshift_jam
    const ac_uint<9> tmp_493 = ac_uint<9>((tmp_446 != 0 ? ac_uint<9>(ac_uint<1>(0)) : ac_uint<9>(tmp_459)));  // basic_mux_2_1
    const std::tuple<ac_uint<38>, ac_uint<9>> tmp_494 = std::make_tuple(tmp_492, tmp_493);  // basic_tuple_maker_2
    // end inline primitive shift_if_subnormal
    const ac_uint<38> tmp_495 = ac_uint<38>(std::get<0>(tmp_494));  // _basic_get_item_0
    const ac_uint<37> tmp_497 = drop_implicit_bit(tmp_495);  // drop_implicit_bit
    const ac_uint<9> tmp_498 = ac_uint<9>(std::get<1>(tmp_494));  // _basic_get_item_1
    // begin inline primitive round_mantissa
    const ac_uint<1> tmp_499 = uq_is_zero(tmp_498);  // uq_is_zero
    // begin inline primitive uq_RNE_IEEE
    const ac_uint<23> tmp_501 = uq_resize_3(tmp_497);  // uq_resize
    const ac_uint<1> tmp_502 = ac_uint<1>(((tmp_497 >> 13) & 1));  // basic_select
    const ac_uint<1> tmp_503 = ac_uint<1>(((tmp_497 >> 12) & 1));  // basic_select
    const ac_uint<12> tmp_504 = ac_uint<12>(((tmp_497 >> 0) & 4095));  // basic_select
    const ac_uint<1> tmp_505 = ac_uint<1>((tmp_504 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_506 = ac_uint<1>((tmp_503 | tmp_505));  // basic_or
    const ac_uint<1> tmp_507 = ac_uint<1>(((tmp_497 >> 14) & 1));  // basic_select
    const ac_uint<1> tmp_508 = ac_uint<1>((tmp_506 | tmp_507));  // basic_or
    const ac_uint<1> tmp_509 = ac_uint<1>((tmp_502 & tmp_508));  // basic_and
    const ac_uint<23> tmp_510 = ac_uint<23>(tmp_509);  // basic_identity
    const ac_uint<24> tmp_517 = uq_add_5(tmp_501, tmp_510);  // uq_add
    const ac_uint<1> tmp_518 = ac_uint<1>((tmp_501 == 8388607));  // basic_and_reduce
    const ac_uint<1> tmp_519 = ac_uint<1>((tmp_518 & tmp_509));  // basic_and
    const ac_uint<23> tmp_520 = ac_uint<23>((tmp_519 >= 24 ? ac_uint<24>(0) : (tmp_517 >> tmp_519)));  // basic_rshift
    const std::tuple<ac_uint<23>, ac_uint<1>> tmp_521 = std::make_tuple(tmp_520, tmp_519);  // basic_tuple_maker_2
    // end inline primitive uq_RNE_IEEE
    const ac_uint<1> tmp_522 = ac_uint<1>(std::get<1>(tmp_521));  // _basic_get_item_1
    const ac_uint<10> tmp_529 = uq_add_6(tmp_498, tmp_522);  // uq_add
    const ac_uint<1> tmp_530 = ac_uint<1>((tmp_529 != 0));  // basic_or_reduce
    const ac_uint<1> tmp_531 = ac_uint<1>((tmp_499 & tmp_530));  // basic_and
    const ac_uint<23> tmp_532 = ac_uint<23>(std::get<0>(tmp_521));  // _basic_get_item_0
    const ac_uint<23> tmp_533 = ac_uint<23>((tmp_531 != 0 ? ac_uint<23>(ac_uint<1>(0)) : ac_uint<23>(tmp_532)));  // basic_mux_2_1
    const std::tuple<ac_uint<23>, ac_uint<10>> tmp_534 = std::make_tuple(tmp_533, tmp_529);  // basic_tuple_maker_2
    // end inline primitive round_mantissa
    const ac_uint<23> tmp_535 = ac_uint<23>(std::get<0>(tmp_534));  // _basic_get_item_0
    const ac_uint<10> tmp_536 = ac_uint<10>(std::get<1>(tmp_534));  // _basic_get_item_1
    // begin inline primitive fp32_encodings
    const ac_uint<10> tmp_542 = uq_min(tmp_536, ac_uint<8>(255));  // uq_min
    const ac_uint<8> tmp_543 = ac_uint<8>(tmp_542);  // basic_identity
    const ac_uint<1> tmp_544 = ac_uint<1>((tmp_543 == 255));  // basic_and_reduce
    const ac_uint<23> tmp_545 = ac_uint<23>((tmp_544 != 0 ? ac_uint<23>(ac_uint<1>(0)) : ac_uint<23>(tmp_535)));  // basic_mux_2_1
    const ac_uint<23> tmp_546 = ac_uint<23>(tmp_545);  // basic_identity
    const std::tuple<ac_uint<23>, ac_uint<8>> tmp_547 = std::make_tuple(tmp_546, tmp_543);  // basic_tuple_maker_2
    // end inline primitive fp32_encodings
    const ac_uint<8> tmp_548 = ac_uint<8>(std::get<1>(tmp_547));  // _basic_get_item_1
    const ac_uint<23> tmp_549 = ac_uint<23>(std::get<0>(tmp_547));  // _basic_get_item_0
    const ac_uint<32> tmp_551 = fp32_pack(arg_0, tmp_548, tmp_549);  // fp32_pack
    const ac_uint<32> tmp_552 = ac_uint<32>((tmp_193 != 0 ? ac_uint<32>(tmp_194) : ac_uint<32>(tmp_551)));  // basic_mux_2_1
    const ac_uint<32> tmp_553 = ac_uint<32>((arg_4 != 0 ? ac_uint<32>(tmp_190) : ac_uint<32>(tmp_552)));  // basic_mux_2_1
    const ac_uint<32> tmp_554 = ac_uint<32>((arg_3 != 0 ? ac_uint<32>(ac_uint<32>(2139095041)) : ac_uint<32>(tmp_553)));  // basic_mux_2_1
    return tmp_554;
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
    const ac_uint<24> tmp_63 = ac_uint<24>((tmp_56 != 0 ? ac_uint<24>(tmp_60) : ac_uint<24>(tmp_62)));  // basic_mux_2_1
    const ac_uint<27> tmp_65 = uq_resize_1(tmp_63);  // uq_resize
    const ac_uint<1> tmp_66 = ac_uint<1>(std::get<1>(tmp_34));  // _basic_get_item_1
    const ac_uint<8> tmp_67 = ac_uint<8>(std::get<1>(tmp_47));  // _basic_get_item_1
    const ac_uint<8> tmp_68 = ac_uint<8>((tmp_66 != 0 ? ac_uint<8>(ac_uint<8>(1)) : ac_uint<8>(tmp_67)));  // basic_mux_2_1
    const ac_uint<1> tmp_69 = ac_uint<1>(std::get<1>(tmp_41));  // _basic_get_item_1
    const ac_uint<8> tmp_70 = ac_uint<8>(std::get<1>(tmp_52));  // _basic_get_item_1
    const ac_uint<8> tmp_71 = ac_uint<8>((tmp_69 != 0 ? ac_uint<8>(ac_uint<8>(1)) : ac_uint<8>(tmp_70)));  // basic_mux_2_1
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
    const ac_uint<24> tmp_133 = ac_uint<24>((tmp_128 != 0 ? ac_uint<24>(tmp_131) : ac_uint<24>(tmp_132)));  // basic_mux_2_1
    const ac_uint<27> tmp_134 = uq_resize_1(tmp_133);  // uq_resize
    const ac_uint<9> tmp_135 = uq_sub(tmp_76, tmp_71);  // uq_sub
    const ac_uint<27> tmp_136 = uq_rshift_jam(tmp_134, tmp_135);  // uq_rshift_jam
    const ac_uint<28> tmp_137 = uq_to_q(tmp_136);  // uq_to_q
    const ac_uint<28> tmp_138 = q_add_sign(tmp_137, tmp_53);  // q_add_sign
    const ac_uint<29> tmp_151 = q_add(tmp_127, tmp_138);  // q_add
    const ac_uint<1> tmp_153 = q_sign_bit_1(tmp_151);  // q_sign_bit
    const ac_uint<1> tmp_154 = ac_uint<1>((tmp_55 != 0 ? ac_uint<1>(ac_uint<1>(1)) : ac_uint<1>(tmp_153)));  // basic_mux_2_1
    const ac_uint<9> tmp_164 = uq_to_q_1(tmp_76);  // uq_to_q
    const ac_uint<29> tmp_175 = q_abs(tmp_151);  // q_abs
    const ac_uint<28> tmp_177 = q_to_uq(tmp_175);  // q_to_uq
    const ac_uint<1> tmp_178 = ac_uint<1>(std::get<3>(tmp_34));  // _basic_get_item_3
    const ac_uint<1> tmp_179 = ac_uint<1>(std::get<3>(tmp_41));  // _basic_get_item_3
    const ac_uint<1> tmp_180 = ac_uint<1>((tmp_178 & tmp_179));  // basic_and
    const ac_uint<1> tmp_181 = ac_uint<1>((tmp_48 ^ tmp_53));  // basic_xor
    const ac_uint<1> tmp_182 = ac_uint<1>((tmp_180 & tmp_181));  // basic_and
    const ac_uint<1> tmp_183 = ac_uint<1>(std::get<4>(tmp_34));  // _basic_get_item_4
    const ac_uint<1> tmp_184 = ac_uint<1>(std::get<4>(tmp_41));  // _basic_get_item_4
    const ac_uint<1> tmp_185 = ac_uint<1>((tmp_183 | tmp_184));  // basic_or
    const ac_uint<1> tmp_186 = ac_uint<1>((tmp_182 | tmp_185));  // basic_or
    const ac_uint<1> tmp_187 = ac_uint<1>(((~tmp_186) & 1));  // basic_invert
    const ac_uint<1> tmp_188 = ac_uint<1>((tmp_178 | tmp_179));  // basic_or
    const ac_uint<1> tmp_189 = ac_uint<1>((tmp_187 & tmp_188));  // basic_and
    const ac_uint<32> tmp_555 = fp32_encode(tmp_154, tmp_164, tmp_177, tmp_186, tmp_189);  // fp32_encode
    return tmp_555;
}
extern "C" inline ac_uint<32> FP32_IEEE_adder(ac_uint<32> arg_0, ac_uint<32> arg_1) {
    return FP32_IEEE_adder_impl(arg_0, arg_1);
}