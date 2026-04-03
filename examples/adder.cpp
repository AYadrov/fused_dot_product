#include <ap_int.h>
#include <tuple>

std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> make_Tuple_7(ap_uint<1> arg_0, ap_uint<8> arg_1, ap_uint<23> arg_2) {  // make_Tuple
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_11 = std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>>(std::make_tuple(arg_0_8, arg_1_9, arg_2_10));  // basic_tuple_maker_3
    return tmp_11;
}
std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> fp32_unpack_2(ap_uint<32> arg_0) {  // fp32_unpack
    const ap_uint<1> tmp_4 = ap_uint<1>(((arg_0_3 >> 31) & ap_uint<1>(1)));  // _fp32_sign
    const ap_uint<8> tmp_5 = ap_uint<8>(((arg_0_3 >> 23) & ap_uint<8>(255)));  // _fp32_exponent
    const ap_uint<23> tmp_6 = ap_uint<23>(((arg_0_3 >> 0) & ap_uint<23>(8388607)));  // _fp32_mantissa
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_12 = make_Tuple_7(tmp_4, tmp_5, tmp_6);  // make_Tuple
    return tmp_12;
}
ap_uint<23> Tuple_get_item_2_14(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_2
    const ap_uint<23> tmp_16 = ap_uint<23>(std::get<2>(arg_0_15));  // basic_get_item_2
    return tmp_16;
}
ap_uint<24> add_implicit_bit_18(ap_uint<23> arg_0) {  // add_implicit_bit
    const ap_uint<24> tmp_20 = ap_uint<24>(((ap_uint<1>(1) << 23) | arg_0_19));  // basic_concat
    return tmp_20;
}
ap_uint<30> uq_resize_22(ap_uint<24> arg_0) {  // uq_resize
    const ap_uint<30> tmp_24 = ap_uint<30>((arg_0_23 << ap_uint<3>(6)));  // basic_lshift
    return tmp_24;
}
ap_uint<8> Tuple_get_item_1_26(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_28 = ap_uint<8>(std::get<1>(arg_0_27));  // basic_get_item_1
    return tmp_28;
}
std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> make_Tuple_35(ap_uint<1> arg_0, ap_uint<8> arg_1, ap_uint<23> arg_2) {  // make_Tuple
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_39 = std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>>(std::make_tuple(arg_0_36, arg_1_37, arg_2_38));  // basic_tuple_maker_3
    return tmp_39;
}
std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> fp32_unpack_30(ap_uint<32> arg_0) {  // fp32_unpack
    const ap_uint<1> tmp_32 = ap_uint<1>(((arg_0_31 >> 31) & ap_uint<1>(1)));  // _fp32_sign
    const ap_uint<8> tmp_33 = ap_uint<8>(((arg_0_31 >> 23) & ap_uint<8>(255)));  // _fp32_exponent
    const ap_uint<23> tmp_34 = ap_uint<23>(((arg_0_31 >> 0) & ap_uint<23>(8388607)));  // _fp32_mantissa
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_40 = make_Tuple_35(tmp_32, tmp_33, tmp_34);  // make_Tuple
    return tmp_40;
}
ap_uint<8> Tuple_get_item_1_42(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_44 = ap_uint<8>(std::get<1>(arg_0_43));  // basic_get_item_1
    return tmp_44;
}
std::tuple<ap_uint<8>, ap_uint<8>> make_Tuple_54(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_57 = std::tuple<ap_uint<8>, ap_uint<8>>(std::make_tuple(arg_0_55, arg_1_56));  // basic_tuple_maker_2
    return tmp_57;
}
std::tuple<ap_uint<8>, ap_uint<8>> uq_aligner_49(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<8> tmp_52 = ap_uint<8>((arg_0_50 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_53 = ap_uint<8>((arg_1_51 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_58 = make_Tuple_54(tmp_52, tmp_53);  // make_Tuple
    return tmp_58;
}
ap_uint<8> Tuple_get_item_0_60(std::tuple<ap_uint<8>, ap_uint<8>> arg_0) {  // Tuple_get_item_0
    const ap_uint<8> tmp_62 = ap_uint<8>(std::get<0>(arg_0_61));  // basic_get_item_0
    return tmp_62;
}
ap_uint<8> Tuple_get_item_1_64(std::tuple<ap_uint<8>, ap_uint<8>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_66 = ap_uint<8>(std::get<1>(arg_0_65));  // basic_get_item_1
    return tmp_66;
}
ap_uint<8> Copy_68(ap_uint<8> arg_0) {  // Copy
    return arg_0_69;
}
ap_uint<8> uq_max_46(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_max
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_59 = uq_aligner_49(arg_0_47, arg_1_48);  // uq_aligner
    const ap_uint<8> tmp_63 = Tuple_get_item_0_60(tmp_59);  // Tuple_get_item_0
    const ap_uint<8> tmp_67 = Tuple_get_item_1_64(tmp_59);  // Tuple_get_item_1
    const ap_uint<8> tmp_70 = Copy_68(tmp_63);  // Copy
    const ap_uint<8> tmp_71 = ap_uint<8>((tmp_63 > tmp_67 ? tmp_63 : tmp_67));  // basic_max
    return tmp_71;
}
std::tuple<ap_uint<9>, ap_uint<9>> make_Tuple_81(ap_uint<9> arg_0, ap_uint<9> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_84 = std::tuple<ap_uint<9>, ap_uint<9>>(std::make_tuple(arg_0_82, arg_1_83));  // basic_tuple_maker_2
    return tmp_84;
}
std::tuple<ap_uint<9>, ap_uint<9>> uq_aligner_76(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<9> tmp_79 = ap_uint<9>((arg_0_77 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<9> tmp_80 = ap_uint<9>((arg_1_78 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_85 = make_Tuple_81(tmp_79, tmp_80);  // make_Tuple
    return tmp_85;
}
ap_uint<9> Tuple_get_item_0_87(std::tuple<ap_uint<9>, ap_uint<9>> arg_0) {  // Tuple_get_item_0
    const ap_uint<9> tmp_89 = ap_uint<9>(std::get<0>(arg_0_88));  // basic_get_item_0
    return tmp_89;
}
ap_uint<9> Tuple_get_item_1_91(std::tuple<ap_uint<9>, ap_uint<9>> arg_0) {  // Tuple_get_item_1
    const ap_uint<9> tmp_93 = ap_uint<9>(std::get<1>(arg_0_92));  // basic_get_item_1
    return tmp_93;
}
ap_uint<9> Copy_95(ap_uint<9> arg_0) {  // Copy
    return arg_0_96;
}
ap_uint<9> uq_sub_73(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_sub
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_86 = uq_aligner_76(arg_0_74, arg_1_75);  // uq_aligner
    const ap_uint<9> tmp_90 = Tuple_get_item_0_87(tmp_86);  // Tuple_get_item_0
    const ap_uint<9> tmp_94 = Tuple_get_item_1_91(tmp_86);  // Tuple_get_item_1
    const ap_uint<9> tmp_97 = Copy_95(tmp_90);  // Copy
    const ap_uint<9> tmp_98 = ap_uint<9>((tmp_90 - tmp_94));  // basic_sub
    return tmp_98;
}
ap_uint<30> Copy_103(ap_uint<30> arg_0) {  // Copy
    return arg_0_104;
}
ap_uint<30> uq_rshift_100(ap_uint<30> arg_0, ap_uint<9> arg_1) {  // uq_rshift
    const ap_uint<30> tmp_105 = Copy_103(arg_0_101);  // Copy
    const ap_uint<30> tmp_106 = ap_uint<30>((arg_0_101 >> arg_1_102));  // basic_rshift
    return tmp_106;
}
std::tuple<ap_uint<2>, ap_uint<2>> make_Tuple_118(ap_uint<2> arg_0, ap_uint<2> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_121 = std::tuple<ap_uint<2>, ap_uint<2>>(std::make_tuple(arg_0_119, arg_1_120));  // basic_tuple_maker_2
    return tmp_121;
}
std::tuple<ap_uint<2>, ap_uint<2>> uq_aligner_113(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<2> tmp_116 = ap_uint<2>((arg_0_114 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<2> tmp_117 = ap_uint<2>((arg_1_115 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_122 = make_Tuple_118(tmp_116, tmp_117);  // make_Tuple
    return tmp_122;
}
ap_uint<2> Tuple_get_item_0_124(std::tuple<ap_uint<2>, ap_uint<2>> arg_0) {  // Tuple_get_item_0
    const ap_uint<2> tmp_126 = ap_uint<2>(std::get<0>(arg_0_125));  // basic_get_item_0
    return tmp_126;
}
ap_uint<2> Tuple_get_item_1_128(std::tuple<ap_uint<2>, ap_uint<2>> arg_0) {  // Tuple_get_item_1
    const ap_uint<2> tmp_130 = ap_uint<2>(std::get<1>(arg_0_129));  // basic_get_item_1
    return tmp_130;
}
ap_uint<2> Copy_132(ap_uint<2> arg_0) {  // Copy
    return arg_0_133;
}
ap_uint<2> uq_add_110(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_123 = uq_aligner_113(arg_0_111, arg_1_112);  // uq_aligner
    const ap_uint<2> tmp_127 = Tuple_get_item_0_124(tmp_123);  // Tuple_get_item_0
    const ap_uint<2> tmp_131 = Tuple_get_item_1_128(tmp_123);  // Tuple_get_item_1
    const ap_uint<2> tmp_134 = Copy_132(tmp_127);  // Copy
    const ap_uint<2> tmp_135 = ap_uint<2>((tmp_127 + tmp_131));  // basic_add
    return tmp_135;
}
ap_uint<31> uq_to_q_108(ap_uint<30> arg_0) {  // uq_to_q
    const ap_uint<2> tmp_136 = uq_add_110(ap_uint<1>(1), ap_uint<1>(1));  // uq_add
    const ap_uint<31> tmp_137 = ap_uint<31>(0);  // q_alloc
    const ap_uint<31> tmp_138 = ap_uint<31>(arg_0_109);  // basic_identity
    return tmp_138;
}
ap_uint<1> Tuple_get_item_0_140(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_0
    const ap_uint<1> tmp_142 = ap_uint<1>(std::get<0>(arg_0_141));  // basic_get_item_0
    return tmp_142;
}
ap_uint<31> Copy_147(ap_uint<31> arg_0) {  // Copy
    return arg_0_148;
}
ap_uint<31> Copy_153(ap_uint<31> arg_0) {  // Copy
    return arg_0_154;
}
ap_uint<31> Copy_157(ap_uint<31> arg_0) {  // Copy
    return arg_0_158;
}
ap_uint<31> Copy_161(ap_uint<31> arg_0) {  // Copy
    return arg_0_162;
}
ap_uint<31> Copy_165(ap_uint<31> arg_0) {  // Copy
    return arg_0_166;
}
ap_uint<31> Copy_169(ap_uint<31> arg_0) {  // Copy
    return arg_0_170;
}
ap_uint<31> q_neg_150(ap_uint<31> arg_0) {  // q_neg
    const ap_uint<1> tmp_152 = ap_uint<1>((arg_0_151 == 1073741824));  // _q_is_min_val
    const ap_uint<31> tmp_155 = Copy_153(arg_0_151);  // Copy
    const ap_uint<31> tmp_156 = ap_uint<31>((~arg_0_151));  // basic_invert
    const ap_uint<31> tmp_159 = Copy_157(arg_0_151);  // Copy
    const ap_uint<31> tmp_160 = ap_uint<31>((tmp_156 + ap_uint<1>(1)));  // basic_add
    const ap_uint<31> tmp_163 = Copy_161(arg_0_151);  // Copy
    const ap_uint<31> tmp_164 = ap_uint<31>((arg_0_151 ^ arg_0_151));  // basic_xor
    const ap_uint<31> tmp_167 = Copy_165(arg_0_151);  // Copy
    const ap_uint<31> tmp_168 = ap_uint<31>((~tmp_164));  // basic_invert
    const ap_uint<31> tmp_171 = Copy_169(arg_0_151);  // Copy
    const ap_uint<31> tmp_172 = ap_uint<31>((tmp_152 ? tmp_168 : tmp_160));  // basic_mux_2_1
    return tmp_172;
}
ap_uint<31> Copy_174(ap_uint<31> arg_0) {  // Copy
    return arg_0_175;
}
ap_uint<31> q_add_sign_144(ap_uint<31> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<31> tmp_149 = Copy_147(arg_0_145);  // Copy
    const ap_uint<31> tmp_173 = q_neg_150(arg_0_145);  // q_neg
    const ap_uint<31> tmp_176 = Copy_174(arg_0_145);  // Copy
    const ap_uint<31> tmp_177 = ap_uint<31>((arg_1_146 ? tmp_173 : tmp_149));  // basic_mux_2_1
    return tmp_177;
}
ap_uint<23> Tuple_get_item_2_179(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_2
    const ap_uint<23> tmp_181 = ap_uint<23>(std::get<2>(arg_0_180));  // basic_get_item_2
    return tmp_181;
}
ap_uint<24> add_implicit_bit_183(ap_uint<23> arg_0) {  // add_implicit_bit
    const ap_uint<24> tmp_185 = ap_uint<24>(((ap_uint<1>(1) << 23) | arg_0_184));  // basic_concat
    return tmp_185;
}
ap_uint<30> uq_resize_187(ap_uint<24> arg_0) {  // uq_resize
    const ap_uint<30> tmp_189 = ap_uint<30>((arg_0_188 << ap_uint<3>(6)));  // basic_lshift
    return tmp_189;
}
std::tuple<ap_uint<9>, ap_uint<9>> make_Tuple_199(ap_uint<9> arg_0, ap_uint<9> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_202 = std::tuple<ap_uint<9>, ap_uint<9>>(std::make_tuple(arg_0_200, arg_1_201));  // basic_tuple_maker_2
    return tmp_202;
}
std::tuple<ap_uint<9>, ap_uint<9>> uq_aligner_194(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<9> tmp_197 = ap_uint<9>((arg_0_195 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<9> tmp_198 = ap_uint<9>((arg_1_196 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_203 = make_Tuple_199(tmp_197, tmp_198);  // make_Tuple
    return tmp_203;
}
ap_uint<9> Tuple_get_item_0_205(std::tuple<ap_uint<9>, ap_uint<9>> arg_0) {  // Tuple_get_item_0
    const ap_uint<9> tmp_207 = ap_uint<9>(std::get<0>(arg_0_206));  // basic_get_item_0
    return tmp_207;
}
ap_uint<9> Tuple_get_item_1_209(std::tuple<ap_uint<9>, ap_uint<9>> arg_0) {  // Tuple_get_item_1
    const ap_uint<9> tmp_211 = ap_uint<9>(std::get<1>(arg_0_210));  // basic_get_item_1
    return tmp_211;
}
ap_uint<9> Copy_213(ap_uint<9> arg_0) {  // Copy
    return arg_0_214;
}
ap_uint<9> uq_sub_191(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_sub
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_204 = uq_aligner_194(arg_0_192, arg_1_193);  // uq_aligner
    const ap_uint<9> tmp_208 = Tuple_get_item_0_205(tmp_204);  // Tuple_get_item_0
    const ap_uint<9> tmp_212 = Tuple_get_item_1_209(tmp_204);  // Tuple_get_item_1
    const ap_uint<9> tmp_215 = Copy_213(tmp_208);  // Copy
    const ap_uint<9> tmp_216 = ap_uint<9>((tmp_208 - tmp_212));  // basic_sub
    return tmp_216;
}
ap_uint<30> Copy_221(ap_uint<30> arg_0) {  // Copy
    return arg_0_222;
}
ap_uint<30> uq_rshift_218(ap_uint<30> arg_0, ap_uint<9> arg_1) {  // uq_rshift
    const ap_uint<30> tmp_223 = Copy_221(arg_0_219);  // Copy
    const ap_uint<30> tmp_224 = ap_uint<30>((arg_0_219 >> arg_1_220));  // basic_rshift
    return tmp_224;
}
std::tuple<ap_uint<2>, ap_uint<2>> make_Tuple_236(ap_uint<2> arg_0, ap_uint<2> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_239 = std::tuple<ap_uint<2>, ap_uint<2>>(std::make_tuple(arg_0_237, arg_1_238));  // basic_tuple_maker_2
    return tmp_239;
}
std::tuple<ap_uint<2>, ap_uint<2>> uq_aligner_231(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<2> tmp_234 = ap_uint<2>((arg_0_232 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<2> tmp_235 = ap_uint<2>((arg_1_233 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_240 = make_Tuple_236(tmp_234, tmp_235);  // make_Tuple
    return tmp_240;
}
ap_uint<2> Tuple_get_item_0_242(std::tuple<ap_uint<2>, ap_uint<2>> arg_0) {  // Tuple_get_item_0
    const ap_uint<2> tmp_244 = ap_uint<2>(std::get<0>(arg_0_243));  // basic_get_item_0
    return tmp_244;
}
ap_uint<2> Tuple_get_item_1_246(std::tuple<ap_uint<2>, ap_uint<2>> arg_0) {  // Tuple_get_item_1
    const ap_uint<2> tmp_248 = ap_uint<2>(std::get<1>(arg_0_247));  // basic_get_item_1
    return tmp_248;
}
ap_uint<2> Copy_250(ap_uint<2> arg_0) {  // Copy
    return arg_0_251;
}
ap_uint<2> uq_add_228(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_241 = uq_aligner_231(arg_0_229, arg_1_230);  // uq_aligner
    const ap_uint<2> tmp_245 = Tuple_get_item_0_242(tmp_241);  // Tuple_get_item_0
    const ap_uint<2> tmp_249 = Tuple_get_item_1_246(tmp_241);  // Tuple_get_item_1
    const ap_uint<2> tmp_252 = Copy_250(tmp_245);  // Copy
    const ap_uint<2> tmp_253 = ap_uint<2>((tmp_245 + tmp_249));  // basic_add
    return tmp_253;
}
ap_uint<31> uq_to_q_226(ap_uint<30> arg_0) {  // uq_to_q
    const ap_uint<2> tmp_254 = uq_add_228(ap_uint<1>(1), ap_uint<1>(1));  // uq_add
    const ap_uint<31> tmp_255 = ap_uint<31>(0);  // q_alloc
    const ap_uint<31> tmp_256 = ap_uint<31>(arg_0_227);  // basic_identity
    return tmp_256;
}
ap_uint<1> Tuple_get_item_0_258(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_0
    const ap_uint<1> tmp_260 = ap_uint<1>(std::get<0>(arg_0_259));  // basic_get_item_0
    return tmp_260;
}
ap_uint<31> Copy_265(ap_uint<31> arg_0) {  // Copy
    return arg_0_266;
}
ap_uint<31> Copy_271(ap_uint<31> arg_0) {  // Copy
    return arg_0_272;
}
ap_uint<31> Copy_275(ap_uint<31> arg_0) {  // Copy
    return arg_0_276;
}
ap_uint<31> Copy_279(ap_uint<31> arg_0) {  // Copy
    return arg_0_280;
}
ap_uint<31> Copy_283(ap_uint<31> arg_0) {  // Copy
    return arg_0_284;
}
ap_uint<31> Copy_287(ap_uint<31> arg_0) {  // Copy
    return arg_0_288;
}
ap_uint<31> q_neg_268(ap_uint<31> arg_0) {  // q_neg
    const ap_uint<1> tmp_270 = ap_uint<1>((arg_0_269 == 1073741824));  // _q_is_min_val
    const ap_uint<31> tmp_273 = Copy_271(arg_0_269);  // Copy
    const ap_uint<31> tmp_274 = ap_uint<31>((~arg_0_269));  // basic_invert
    const ap_uint<31> tmp_277 = Copy_275(arg_0_269);  // Copy
    const ap_uint<31> tmp_278 = ap_uint<31>((tmp_274 + ap_uint<1>(1)));  // basic_add
    const ap_uint<31> tmp_281 = Copy_279(arg_0_269);  // Copy
    const ap_uint<31> tmp_282 = ap_uint<31>((arg_0_269 ^ arg_0_269));  // basic_xor
    const ap_uint<31> tmp_285 = Copy_283(arg_0_269);  // Copy
    const ap_uint<31> tmp_286 = ap_uint<31>((~tmp_282));  // basic_invert
    const ap_uint<31> tmp_289 = Copy_287(arg_0_269);  // Copy
    const ap_uint<31> tmp_290 = ap_uint<31>((tmp_270 ? tmp_286 : tmp_278));  // basic_mux_2_1
    return tmp_290;
}
ap_uint<31> Copy_292(ap_uint<31> arg_0) {  // Copy
    return arg_0_293;
}
ap_uint<31> q_add_sign_262(ap_uint<31> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<31> tmp_267 = Copy_265(arg_0_263);  // Copy
    const ap_uint<31> tmp_291 = q_neg_268(arg_0_263);  // q_neg
    const ap_uint<31> tmp_294 = Copy_292(arg_0_263);  // Copy
    const ap_uint<31> tmp_295 = ap_uint<31>((arg_1_264 ? tmp_291 : tmp_267));  // basic_mux_2_1
    return tmp_295;
}
ap_uint<1> q_sign_bit_306(ap_uint<31> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_308 = ap_uint<1>(((arg_0_307 >> 30) & ap_uint<1>(1)));  // basic_select
    return tmp_308;
}
ap_uint<32> q_sign_extend_304(ap_uint<31> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_309 = q_sign_bit_306(arg_0_305);  // q_sign_bit
    const ap_uint<2> tmp_310 = ap_uint<2>((tmp_309 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_311 = ap_uint<1>((tmp_310 - tmp_309));  // basic_sub
    const ap_uint<32> tmp_312 = ap_uint<32>(0);  // q_alloc
    const ap_uint<32> tmp_313 = ap_uint<32>(((tmp_311 << 31) | arg_0_305));  // basic_concat
    return tmp_313;
}
ap_uint<1> q_sign_bit_318(ap_uint<31> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_320 = ap_uint<1>(((arg_0_319 >> 30) & ap_uint<1>(1)));  // basic_select
    return tmp_320;
}
ap_uint<32> q_sign_extend_316(ap_uint<31> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_321 = q_sign_bit_318(arg_0_317);  // q_sign_bit
    const ap_uint<2> tmp_322 = ap_uint<2>((tmp_321 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_323 = ap_uint<1>((tmp_322 - tmp_321));  // basic_sub
    const ap_uint<32> tmp_324 = ap_uint<32>(0);  // q_alloc
    const ap_uint<32> tmp_325 = ap_uint<32>(((tmp_323 << 31) | arg_0_317));  // basic_concat
    return tmp_325;
}
std::tuple<ap_uint<32>, ap_uint<32>> make_Tuple_327(ap_uint<32> arg_0, ap_uint<32> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_330 = std::tuple<ap_uint<32>, ap_uint<32>>(std::make_tuple(arg_0_328, arg_1_329));  // basic_tuple_maker_2
    return tmp_330;
}
std::tuple<ap_uint<32>, ap_uint<32>> q_aligner_300(ap_uint<31> arg_0, ap_uint<31> arg_1) {  // q_aligner
    const ap_uint<31> tmp_303 = ap_uint<31>((arg_0_301 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<32> tmp_314 = q_sign_extend_304(tmp_303);  // q_sign_extend
    const ap_uint<31> tmp_315 = ap_uint<31>((arg_1_302 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<32> tmp_326 = q_sign_extend_316(tmp_315);  // q_sign_extend
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_331 = make_Tuple_327(tmp_314, tmp_326);  // make_Tuple
    return tmp_331;
}
ap_uint<32> Tuple_get_item_0_333(std::tuple<ap_uint<32>, ap_uint<32>> arg_0) {  // Tuple_get_item_0
    const ap_uint<32> tmp_335 = ap_uint<32>(std::get<0>(arg_0_334));  // basic_get_item_0
    return tmp_335;
}
ap_uint<32> Tuple_get_item_1_337(std::tuple<ap_uint<32>, ap_uint<32>> arg_0) {  // Tuple_get_item_1
    const ap_uint<32> tmp_339 = ap_uint<32>(std::get<1>(arg_0_338));  // basic_get_item_1
    return tmp_339;
}
ap_uint<32> Copy_341(ap_uint<32> arg_0) {  // Copy
    return arg_0_342;
}
ap_uint<32> q_add_297(ap_uint<31> arg_0, ap_uint<31> arg_1) {  // q_add
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_332 = q_aligner_300(arg_0_298, arg_1_299);  // q_aligner
    const ap_uint<32> tmp_336 = Tuple_get_item_0_333(tmp_332);  // Tuple_get_item_0
    const ap_uint<32> tmp_340 = Tuple_get_item_1_337(tmp_332);  // Tuple_get_item_1
    const ap_uint<32> tmp_343 = Copy_341(tmp_336);  // Copy
    const ap_uint<32> tmp_344 = ap_uint<32>((tmp_336 + tmp_340));  // basic_add
    return tmp_344;
}
std::tuple<ap_uint<5>, ap_uint<5>> make_Tuple_356(ap_uint<5> arg_0, ap_uint<5> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_359 = std::tuple<ap_uint<5>, ap_uint<5>>(std::make_tuple(arg_0_357, arg_1_358));  // basic_tuple_maker_2
    return tmp_359;
}
std::tuple<ap_uint<5>, ap_uint<5>> uq_aligner_351(ap_uint<4> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<5> tmp_354 = ap_uint<5>((arg_0_352 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<5> tmp_355 = ap_uint<5>((arg_1_353 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_360 = make_Tuple_356(tmp_354, tmp_355);  // make_Tuple
    return tmp_360;
}
ap_uint<5> Tuple_get_item_0_362(std::tuple<ap_uint<5>, ap_uint<5>> arg_0) {  // Tuple_get_item_0
    const ap_uint<5> tmp_364 = ap_uint<5>(std::get<0>(arg_0_363));  // basic_get_item_0
    return tmp_364;
}
ap_uint<5> Tuple_get_item_1_366(std::tuple<ap_uint<5>, ap_uint<5>> arg_0) {  // Tuple_get_item_1
    const ap_uint<5> tmp_368 = ap_uint<5>(std::get<1>(arg_0_367));  // basic_get_item_1
    return tmp_368;
}
ap_uint<5> Copy_370(ap_uint<5> arg_0) {  // Copy
    return arg_0_371;
}
ap_uint<5> uq_add_348(ap_uint<4> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_361 = uq_aligner_351(arg_0_349, arg_1_350);  // uq_aligner
    const ap_uint<5> tmp_365 = Tuple_get_item_0_362(tmp_361);  // Tuple_get_item_0
    const ap_uint<5> tmp_369 = Tuple_get_item_1_366(tmp_361);  // Tuple_get_item_1
    const ap_uint<5> tmp_372 = Copy_370(tmp_365);  // Copy
    const ap_uint<5> tmp_373 = ap_uint<5>((tmp_365 + tmp_369));  // basic_add
    return tmp_373;
}
ap_uint<9> uq_to_q_346(ap_uint<8> arg_0) {  // uq_to_q
    const ap_uint<5> tmp_374 = uq_add_348(ap_uint<4>(8), ap_uint<1>(1));  // uq_add
    const ap_uint<9> tmp_375 = ap_uint<9>(0);  // q_alloc
    const ap_uint<9> tmp_376 = ap_uint<9>(arg_0_347);  // basic_identity
    return tmp_376;
}
ap_uint<1> q_sign_bit_381(ap_uint<32> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_383 = ap_uint<1>(((arg_0_382 >> 31) & ap_uint<1>(1)));  // basic_select
    return tmp_383;
}
ap_uint<1> q_sign_bit_387(ap_uint<32> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_389 = ap_uint<1>(((arg_0_388 >> 31) & ap_uint<1>(1)));  // basic_select
    return tmp_389;
}
ap_uint<32> Copy_394(ap_uint<32> arg_0) {  // Copy
    return arg_0_395;
}
ap_uint<32> Copy_400(ap_uint<32> arg_0) {  // Copy
    return arg_0_401;
}
ap_uint<32> Copy_404(ap_uint<32> arg_0) {  // Copy
    return arg_0_405;
}
ap_uint<32> Copy_408(ap_uint<32> arg_0) {  // Copy
    return arg_0_409;
}
ap_uint<32> Copy_412(ap_uint<32> arg_0) {  // Copy
    return arg_0_413;
}
ap_uint<32> Copy_416(ap_uint<32> arg_0) {  // Copy
    return arg_0_417;
}
ap_uint<32> q_neg_397(ap_uint<32> arg_0) {  // q_neg
    const ap_uint<1> tmp_399 = ap_uint<1>((arg_0_398 == 2147483648));  // _q_is_min_val
    const ap_uint<32> tmp_402 = Copy_400(arg_0_398);  // Copy
    const ap_uint<32> tmp_403 = ap_uint<32>((~arg_0_398));  // basic_invert
    const ap_uint<32> tmp_406 = Copy_404(arg_0_398);  // Copy
    const ap_uint<32> tmp_407 = ap_uint<32>((tmp_403 + ap_uint<1>(1)));  // basic_add
    const ap_uint<32> tmp_410 = Copy_408(arg_0_398);  // Copy
    const ap_uint<32> tmp_411 = ap_uint<32>((arg_0_398 ^ arg_0_398));  // basic_xor
    const ap_uint<32> tmp_414 = Copy_412(arg_0_398);  // Copy
    const ap_uint<32> tmp_415 = ap_uint<32>((~tmp_411));  // basic_invert
    const ap_uint<32> tmp_418 = Copy_416(arg_0_398);  // Copy
    const ap_uint<32> tmp_419 = ap_uint<32>((tmp_399 ? tmp_415 : tmp_407));  // basic_mux_2_1
    return tmp_419;
}
ap_uint<32> Copy_421(ap_uint<32> arg_0) {  // Copy
    return arg_0_422;
}
ap_uint<32> q_add_sign_391(ap_uint<32> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<32> tmp_396 = Copy_394(arg_0_392);  // Copy
    const ap_uint<32> tmp_420 = q_neg_397(arg_0_392);  // q_neg
    const ap_uint<32> tmp_423 = Copy_421(arg_0_392);  // Copy
    const ap_uint<32> tmp_424 = ap_uint<32>((arg_1_393 ? tmp_420 : tmp_396));  // basic_mux_2_1
    return tmp_424;
}
ap_uint<32> q_abs_385(ap_uint<32> arg_0) {  // q_abs
    const ap_uint<1> tmp_390 = q_sign_bit_387(arg_0_386);  // q_sign_bit
    const ap_uint<32> tmp_425 = q_add_sign_391(arg_0_386, tmp_390);  // q_add_sign
    return tmp_425;
}
ap_uint<31> q_to_uq_427(ap_uint<32> arg_0) {  // q_to_uq
    const ap_uint<31> tmp_429 = ap_uint<31>(arg_0_428);  // basic_identity
    return tmp_429;
}
ap_uint<1> uq_select_436(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_438 = ap_uint<1>(((arg_0_437 >> 30) & ap_uint<1>(1)));  // basic_select
    return tmp_438;
}
ap_uint<1> Copy_440(ap_uint<1> arg_0) {  // Copy
    return arg_0_441;
}
ap_uint<1> Copy_444(ap_uint<1> arg_0) {  // Copy
    return arg_0_445;
}
ap_uint<5> Copy_448(ap_uint<5> arg_0) {  // Copy
    return arg_0_449;
}
ap_uint<1> uq_select_452(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_454 = ap_uint<1>(((arg_0_453 >> 29) & ap_uint<1>(1)));  // basic_select
    return tmp_454;
}
ap_uint<1> Copy_456(ap_uint<1> arg_0) {  // Copy
    return arg_0_457;
}
ap_uint<1> Copy_460(ap_uint<1> arg_0) {  // Copy
    return arg_0_461;
}
ap_uint<5> Copy_464(ap_uint<5> arg_0) {  // Copy
    return arg_0_465;
}
ap_uint<1> uq_select_468(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_470 = ap_uint<1>(((arg_0_469 >> 28) & ap_uint<1>(1)));  // basic_select
    return tmp_470;
}
ap_uint<1> Copy_472(ap_uint<1> arg_0) {  // Copy
    return arg_0_473;
}
ap_uint<1> Copy_476(ap_uint<1> arg_0) {  // Copy
    return arg_0_477;
}
ap_uint<5> Copy_480(ap_uint<5> arg_0) {  // Copy
    return arg_0_481;
}
ap_uint<1> uq_select_484(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_486 = ap_uint<1>(((arg_0_485 >> 27) & ap_uint<1>(1)));  // basic_select
    return tmp_486;
}
ap_uint<1> Copy_488(ap_uint<1> arg_0) {  // Copy
    return arg_0_489;
}
ap_uint<1> Copy_492(ap_uint<1> arg_0) {  // Copy
    return arg_0_493;
}
ap_uint<5> Copy_496(ap_uint<5> arg_0) {  // Copy
    return arg_0_497;
}
ap_uint<1> uq_select_500(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_502 = ap_uint<1>(((arg_0_501 >> 26) & ap_uint<1>(1)));  // basic_select
    return tmp_502;
}
ap_uint<1> Copy_504(ap_uint<1> arg_0) {  // Copy
    return arg_0_505;
}
ap_uint<1> Copy_508(ap_uint<1> arg_0) {  // Copy
    return arg_0_509;
}
ap_uint<5> Copy_512(ap_uint<5> arg_0) {  // Copy
    return arg_0_513;
}
ap_uint<1> uq_select_516(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_518 = ap_uint<1>(((arg_0_517 >> 25) & ap_uint<1>(1)));  // basic_select
    return tmp_518;
}
ap_uint<1> Copy_520(ap_uint<1> arg_0) {  // Copy
    return arg_0_521;
}
ap_uint<1> Copy_524(ap_uint<1> arg_0) {  // Copy
    return arg_0_525;
}
ap_uint<5> Copy_528(ap_uint<5> arg_0) {  // Copy
    return arg_0_529;
}
ap_uint<1> uq_select_532(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_534 = ap_uint<1>(((arg_0_533 >> 24) & ap_uint<1>(1)));  // basic_select
    return tmp_534;
}
ap_uint<1> Copy_536(ap_uint<1> arg_0) {  // Copy
    return arg_0_537;
}
ap_uint<1> Copy_540(ap_uint<1> arg_0) {  // Copy
    return arg_0_541;
}
ap_uint<5> Copy_544(ap_uint<5> arg_0) {  // Copy
    return arg_0_545;
}
ap_uint<1> uq_select_548(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_550 = ap_uint<1>(((arg_0_549 >> 23) & ap_uint<1>(1)));  // basic_select
    return tmp_550;
}
ap_uint<1> Copy_552(ap_uint<1> arg_0) {  // Copy
    return arg_0_553;
}
ap_uint<1> Copy_556(ap_uint<1> arg_0) {  // Copy
    return arg_0_557;
}
ap_uint<5> Copy_560(ap_uint<5> arg_0) {  // Copy
    return arg_0_561;
}
ap_uint<1> uq_select_564(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_566 = ap_uint<1>(((arg_0_565 >> 22) & ap_uint<1>(1)));  // basic_select
    return tmp_566;
}
ap_uint<1> Copy_568(ap_uint<1> arg_0) {  // Copy
    return arg_0_569;
}
ap_uint<1> Copy_572(ap_uint<1> arg_0) {  // Copy
    return arg_0_573;
}
ap_uint<5> Copy_576(ap_uint<5> arg_0) {  // Copy
    return arg_0_577;
}
ap_uint<1> uq_select_580(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_582 = ap_uint<1>(((arg_0_581 >> 21) & ap_uint<1>(1)));  // basic_select
    return tmp_582;
}
ap_uint<1> Copy_584(ap_uint<1> arg_0) {  // Copy
    return arg_0_585;
}
ap_uint<1> Copy_588(ap_uint<1> arg_0) {  // Copy
    return arg_0_589;
}
ap_uint<5> Copy_592(ap_uint<5> arg_0) {  // Copy
    return arg_0_593;
}
ap_uint<1> uq_select_596(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_598 = ap_uint<1>(((arg_0_597 >> 20) & ap_uint<1>(1)));  // basic_select
    return tmp_598;
}
ap_uint<1> Copy_600(ap_uint<1> arg_0) {  // Copy
    return arg_0_601;
}
ap_uint<1> Copy_604(ap_uint<1> arg_0) {  // Copy
    return arg_0_605;
}
ap_uint<5> Copy_608(ap_uint<5> arg_0) {  // Copy
    return arg_0_609;
}
ap_uint<1> uq_select_612(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_614 = ap_uint<1>(((arg_0_613 >> 19) & ap_uint<1>(1)));  // basic_select
    return tmp_614;
}
ap_uint<1> Copy_616(ap_uint<1> arg_0) {  // Copy
    return arg_0_617;
}
ap_uint<1> Copy_620(ap_uint<1> arg_0) {  // Copy
    return arg_0_621;
}
ap_uint<5> Copy_624(ap_uint<5> arg_0) {  // Copy
    return arg_0_625;
}
ap_uint<1> uq_select_628(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_630 = ap_uint<1>(((arg_0_629 >> 18) & ap_uint<1>(1)));  // basic_select
    return tmp_630;
}
ap_uint<1> Copy_632(ap_uint<1> arg_0) {  // Copy
    return arg_0_633;
}
ap_uint<1> Copy_636(ap_uint<1> arg_0) {  // Copy
    return arg_0_637;
}
ap_uint<5> Copy_640(ap_uint<5> arg_0) {  // Copy
    return arg_0_641;
}
ap_uint<1> uq_select_644(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_646 = ap_uint<1>(((arg_0_645 >> 17) & ap_uint<1>(1)));  // basic_select
    return tmp_646;
}
ap_uint<1> Copy_648(ap_uint<1> arg_0) {  // Copy
    return arg_0_649;
}
ap_uint<1> Copy_652(ap_uint<1> arg_0) {  // Copy
    return arg_0_653;
}
ap_uint<5> Copy_656(ap_uint<5> arg_0) {  // Copy
    return arg_0_657;
}
ap_uint<1> uq_select_660(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_662 = ap_uint<1>(((arg_0_661 >> 16) & ap_uint<1>(1)));  // basic_select
    return tmp_662;
}
ap_uint<1> Copy_664(ap_uint<1> arg_0) {  // Copy
    return arg_0_665;
}
ap_uint<1> Copy_668(ap_uint<1> arg_0) {  // Copy
    return arg_0_669;
}
ap_uint<5> Copy_672(ap_uint<5> arg_0) {  // Copy
    return arg_0_673;
}
ap_uint<1> uq_select_676(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_678 = ap_uint<1>(((arg_0_677 >> 15) & ap_uint<1>(1)));  // basic_select
    return tmp_678;
}
ap_uint<1> Copy_680(ap_uint<1> arg_0) {  // Copy
    return arg_0_681;
}
ap_uint<1> Copy_684(ap_uint<1> arg_0) {  // Copy
    return arg_0_685;
}
ap_uint<5> Copy_688(ap_uint<5> arg_0) {  // Copy
    return arg_0_689;
}
ap_uint<1> uq_select_692(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_694 = ap_uint<1>(((arg_0_693 >> 14) & ap_uint<1>(1)));  // basic_select
    return tmp_694;
}
ap_uint<1> Copy_696(ap_uint<1> arg_0) {  // Copy
    return arg_0_697;
}
ap_uint<1> Copy_700(ap_uint<1> arg_0) {  // Copy
    return arg_0_701;
}
ap_uint<5> Copy_704(ap_uint<5> arg_0) {  // Copy
    return arg_0_705;
}
ap_uint<1> uq_select_708(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_710 = ap_uint<1>(((arg_0_709 >> 13) & ap_uint<1>(1)));  // basic_select
    return tmp_710;
}
ap_uint<1> Copy_712(ap_uint<1> arg_0) {  // Copy
    return arg_0_713;
}
ap_uint<1> Copy_716(ap_uint<1> arg_0) {  // Copy
    return arg_0_717;
}
ap_uint<5> Copy_720(ap_uint<5> arg_0) {  // Copy
    return arg_0_721;
}
ap_uint<1> uq_select_724(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_726 = ap_uint<1>(((arg_0_725 >> 12) & ap_uint<1>(1)));  // basic_select
    return tmp_726;
}
ap_uint<1> Copy_728(ap_uint<1> arg_0) {  // Copy
    return arg_0_729;
}
ap_uint<1> Copy_732(ap_uint<1> arg_0) {  // Copy
    return arg_0_733;
}
ap_uint<5> Copy_736(ap_uint<5> arg_0) {  // Copy
    return arg_0_737;
}
ap_uint<1> uq_select_740(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_742 = ap_uint<1>(((arg_0_741 >> 11) & ap_uint<1>(1)));  // basic_select
    return tmp_742;
}
ap_uint<1> Copy_744(ap_uint<1> arg_0) {  // Copy
    return arg_0_745;
}
ap_uint<1> Copy_748(ap_uint<1> arg_0) {  // Copy
    return arg_0_749;
}
ap_uint<5> Copy_752(ap_uint<5> arg_0) {  // Copy
    return arg_0_753;
}
ap_uint<1> uq_select_756(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_758 = ap_uint<1>(((arg_0_757 >> 10) & ap_uint<1>(1)));  // basic_select
    return tmp_758;
}
ap_uint<1> Copy_760(ap_uint<1> arg_0) {  // Copy
    return arg_0_761;
}
ap_uint<1> Copy_764(ap_uint<1> arg_0) {  // Copy
    return arg_0_765;
}
ap_uint<5> Copy_768(ap_uint<5> arg_0) {  // Copy
    return arg_0_769;
}
ap_uint<1> uq_select_772(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_774 = ap_uint<1>(((arg_0_773 >> 9) & ap_uint<1>(1)));  // basic_select
    return tmp_774;
}
ap_uint<1> Copy_776(ap_uint<1> arg_0) {  // Copy
    return arg_0_777;
}
ap_uint<1> Copy_780(ap_uint<1> arg_0) {  // Copy
    return arg_0_781;
}
ap_uint<5> Copy_784(ap_uint<5> arg_0) {  // Copy
    return arg_0_785;
}
ap_uint<1> uq_select_788(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_790 = ap_uint<1>(((arg_0_789 >> 8) & ap_uint<1>(1)));  // basic_select
    return tmp_790;
}
ap_uint<1> Copy_792(ap_uint<1> arg_0) {  // Copy
    return arg_0_793;
}
ap_uint<1> Copy_796(ap_uint<1> arg_0) {  // Copy
    return arg_0_797;
}
ap_uint<5> Copy_800(ap_uint<5> arg_0) {  // Copy
    return arg_0_801;
}
ap_uint<1> uq_select_804(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_806 = ap_uint<1>(((arg_0_805 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_806;
}
ap_uint<1> Copy_808(ap_uint<1> arg_0) {  // Copy
    return arg_0_809;
}
ap_uint<1> Copy_812(ap_uint<1> arg_0) {  // Copy
    return arg_0_813;
}
ap_uint<5> Copy_816(ap_uint<5> arg_0) {  // Copy
    return arg_0_817;
}
ap_uint<1> uq_select_820(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_822 = ap_uint<1>(((arg_0_821 >> 6) & ap_uint<1>(1)));  // basic_select
    return tmp_822;
}
ap_uint<1> Copy_824(ap_uint<1> arg_0) {  // Copy
    return arg_0_825;
}
ap_uint<1> Copy_828(ap_uint<1> arg_0) {  // Copy
    return arg_0_829;
}
ap_uint<5> Copy_832(ap_uint<5> arg_0) {  // Copy
    return arg_0_833;
}
ap_uint<1> uq_select_836(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_838 = ap_uint<1>(((arg_0_837 >> 5) & ap_uint<1>(1)));  // basic_select
    return tmp_838;
}
ap_uint<1> Copy_840(ap_uint<1> arg_0) {  // Copy
    return arg_0_841;
}
ap_uint<1> Copy_844(ap_uint<1> arg_0) {  // Copy
    return arg_0_845;
}
ap_uint<5> Copy_848(ap_uint<5> arg_0) {  // Copy
    return arg_0_849;
}
ap_uint<1> uq_select_852(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_854 = ap_uint<1>(((arg_0_853 >> 4) & ap_uint<1>(1)));  // basic_select
    return tmp_854;
}
ap_uint<1> Copy_856(ap_uint<1> arg_0) {  // Copy
    return arg_0_857;
}
ap_uint<1> Copy_860(ap_uint<1> arg_0) {  // Copy
    return arg_0_861;
}
ap_uint<5> Copy_864(ap_uint<5> arg_0) {  // Copy
    return arg_0_865;
}
ap_uint<1> uq_select_868(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_870 = ap_uint<1>(((arg_0_869 >> 3) & ap_uint<1>(1)));  // basic_select
    return tmp_870;
}
ap_uint<1> Copy_872(ap_uint<1> arg_0) {  // Copy
    return arg_0_873;
}
ap_uint<1> Copy_876(ap_uint<1> arg_0) {  // Copy
    return arg_0_877;
}
ap_uint<5> Copy_880(ap_uint<5> arg_0) {  // Copy
    return arg_0_881;
}
ap_uint<1> uq_select_884(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_886 = ap_uint<1>(((arg_0_885 >> 2) & ap_uint<1>(1)));  // basic_select
    return tmp_886;
}
ap_uint<1> Copy_888(ap_uint<1> arg_0) {  // Copy
    return arg_0_889;
}
ap_uint<1> Copy_892(ap_uint<1> arg_0) {  // Copy
    return arg_0_893;
}
ap_uint<5> Copy_896(ap_uint<5> arg_0) {  // Copy
    return arg_0_897;
}
ap_uint<1> uq_select_900(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_902 = ap_uint<1>(((arg_0_901 >> 1) & ap_uint<1>(1)));  // basic_select
    return tmp_902;
}
ap_uint<1> Copy_904(ap_uint<1> arg_0) {  // Copy
    return arg_0_905;
}
ap_uint<1> Copy_908(ap_uint<1> arg_0) {  // Copy
    return arg_0_909;
}
ap_uint<5> Copy_912(ap_uint<5> arg_0) {  // Copy
    return arg_0_913;
}
ap_uint<1> uq_select_916(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_918 = ap_uint<1>(((arg_0_917 >> 0) & ap_uint<1>(1)));  // basic_select
    return tmp_918;
}
ap_uint<1> Copy_920(ap_uint<1> arg_0) {  // Copy
    return arg_0_921;
}
ap_uint<1> Copy_924(ap_uint<1> arg_0) {  // Copy
    return arg_0_925;
}
ap_uint<5> Copy_928(ap_uint<5> arg_0) {  // Copy
    return arg_0_929;
}
ap_uint<5> lzc_434(ap_uint<31> arg_0) {  // lzc
    const ap_uint<1> tmp_439 = uq_select_436(arg_0_435);  // uq_select
    const ap_uint<1> tmp_442 = Copy_440(tmp_439);  // Copy
    const ap_uint<1> tmp_443 = ap_uint<1>((~tmp_439));  // basic_invert
    const ap_uint<1> tmp_446 = Copy_444(ap_uint<1>(1));  // Copy
    const ap_uint<1> tmp_447 = ap_uint<1>((ap_uint<1>(1) & tmp_443));  // basic_and
    const ap_uint<5> tmp_450 = Copy_448(ap_uint<5>(0));  // Copy
    const ap_uint<5> tmp_451 = ap_uint<5>((ap_uint<5>(0) + tmp_447));  // basic_add
    const ap_uint<1> tmp_455 = uq_select_452(arg_0_435);  // uq_select
    const ap_uint<1> tmp_458 = Copy_456(tmp_455);  // Copy
    const ap_uint<1> tmp_459 = ap_uint<1>((~tmp_455));  // basic_invert
    const ap_uint<1> tmp_462 = Copy_460(tmp_447);  // Copy
    const ap_uint<1> tmp_463 = ap_uint<1>((tmp_447 & tmp_459));  // basic_and
    const ap_uint<5> tmp_466 = Copy_464(tmp_451);  // Copy
    const ap_uint<5> tmp_467 = ap_uint<5>((tmp_451 + tmp_463));  // basic_add
    const ap_uint<1> tmp_471 = uq_select_468(arg_0_435);  // uq_select
    const ap_uint<1> tmp_474 = Copy_472(tmp_471);  // Copy
    const ap_uint<1> tmp_475 = ap_uint<1>((~tmp_471));  // basic_invert
    const ap_uint<1> tmp_478 = Copy_476(tmp_463);  // Copy
    const ap_uint<1> tmp_479 = ap_uint<1>((tmp_463 & tmp_475));  // basic_and
    const ap_uint<5> tmp_482 = Copy_480(tmp_467);  // Copy
    const ap_uint<5> tmp_483 = ap_uint<5>((tmp_467 + tmp_479));  // basic_add
    const ap_uint<1> tmp_487 = uq_select_484(arg_0_435);  // uq_select
    const ap_uint<1> tmp_490 = Copy_488(tmp_487);  // Copy
    const ap_uint<1> tmp_491 = ap_uint<1>((~tmp_487));  // basic_invert
    const ap_uint<1> tmp_494 = Copy_492(tmp_479);  // Copy
    const ap_uint<1> tmp_495 = ap_uint<1>((tmp_479 & tmp_491));  // basic_and
    const ap_uint<5> tmp_498 = Copy_496(tmp_483);  // Copy
    const ap_uint<5> tmp_499 = ap_uint<5>((tmp_483 + tmp_495));  // basic_add
    const ap_uint<1> tmp_503 = uq_select_500(arg_0_435);  // uq_select
    const ap_uint<1> tmp_506 = Copy_504(tmp_503);  // Copy
    const ap_uint<1> tmp_507 = ap_uint<1>((~tmp_503));  // basic_invert
    const ap_uint<1> tmp_510 = Copy_508(tmp_495);  // Copy
    const ap_uint<1> tmp_511 = ap_uint<1>((tmp_495 & tmp_507));  // basic_and
    const ap_uint<5> tmp_514 = Copy_512(tmp_499);  // Copy
    const ap_uint<5> tmp_515 = ap_uint<5>((tmp_499 + tmp_511));  // basic_add
    const ap_uint<1> tmp_519 = uq_select_516(arg_0_435);  // uq_select
    const ap_uint<1> tmp_522 = Copy_520(tmp_519);  // Copy
    const ap_uint<1> tmp_523 = ap_uint<1>((~tmp_519));  // basic_invert
    const ap_uint<1> tmp_526 = Copy_524(tmp_511);  // Copy
    const ap_uint<1> tmp_527 = ap_uint<1>((tmp_511 & tmp_523));  // basic_and
    const ap_uint<5> tmp_530 = Copy_528(tmp_515);  // Copy
    const ap_uint<5> tmp_531 = ap_uint<5>((tmp_515 + tmp_527));  // basic_add
    const ap_uint<1> tmp_535 = uq_select_532(arg_0_435);  // uq_select
    const ap_uint<1> tmp_538 = Copy_536(tmp_535);  // Copy
    const ap_uint<1> tmp_539 = ap_uint<1>((~tmp_535));  // basic_invert
    const ap_uint<1> tmp_542 = Copy_540(tmp_527);  // Copy
    const ap_uint<1> tmp_543 = ap_uint<1>((tmp_527 & tmp_539));  // basic_and
    const ap_uint<5> tmp_546 = Copy_544(tmp_531);  // Copy
    const ap_uint<5> tmp_547 = ap_uint<5>((tmp_531 + tmp_543));  // basic_add
    const ap_uint<1> tmp_551 = uq_select_548(arg_0_435);  // uq_select
    const ap_uint<1> tmp_554 = Copy_552(tmp_551);  // Copy
    const ap_uint<1> tmp_555 = ap_uint<1>((~tmp_551));  // basic_invert
    const ap_uint<1> tmp_558 = Copy_556(tmp_543);  // Copy
    const ap_uint<1> tmp_559 = ap_uint<1>((tmp_543 & tmp_555));  // basic_and
    const ap_uint<5> tmp_562 = Copy_560(tmp_547);  // Copy
    const ap_uint<5> tmp_563 = ap_uint<5>((tmp_547 + tmp_559));  // basic_add
    const ap_uint<1> tmp_567 = uq_select_564(arg_0_435);  // uq_select
    const ap_uint<1> tmp_570 = Copy_568(tmp_567);  // Copy
    const ap_uint<1> tmp_571 = ap_uint<1>((~tmp_567));  // basic_invert
    const ap_uint<1> tmp_574 = Copy_572(tmp_559);  // Copy
    const ap_uint<1> tmp_575 = ap_uint<1>((tmp_559 & tmp_571));  // basic_and
    const ap_uint<5> tmp_578 = Copy_576(tmp_563);  // Copy
    const ap_uint<5> tmp_579 = ap_uint<5>((tmp_563 + tmp_575));  // basic_add
    const ap_uint<1> tmp_583 = uq_select_580(arg_0_435);  // uq_select
    const ap_uint<1> tmp_586 = Copy_584(tmp_583);  // Copy
    const ap_uint<1> tmp_587 = ap_uint<1>((~tmp_583));  // basic_invert
    const ap_uint<1> tmp_590 = Copy_588(tmp_575);  // Copy
    const ap_uint<1> tmp_591 = ap_uint<1>((tmp_575 & tmp_587));  // basic_and
    const ap_uint<5> tmp_594 = Copy_592(tmp_579);  // Copy
    const ap_uint<5> tmp_595 = ap_uint<5>((tmp_579 + tmp_591));  // basic_add
    const ap_uint<1> tmp_599 = uq_select_596(arg_0_435);  // uq_select
    const ap_uint<1> tmp_602 = Copy_600(tmp_599);  // Copy
    const ap_uint<1> tmp_603 = ap_uint<1>((~tmp_599));  // basic_invert
    const ap_uint<1> tmp_606 = Copy_604(tmp_591);  // Copy
    const ap_uint<1> tmp_607 = ap_uint<1>((tmp_591 & tmp_603));  // basic_and
    const ap_uint<5> tmp_610 = Copy_608(tmp_595);  // Copy
    const ap_uint<5> tmp_611 = ap_uint<5>((tmp_595 + tmp_607));  // basic_add
    const ap_uint<1> tmp_615 = uq_select_612(arg_0_435);  // uq_select
    const ap_uint<1> tmp_618 = Copy_616(tmp_615);  // Copy
    const ap_uint<1> tmp_619 = ap_uint<1>((~tmp_615));  // basic_invert
    const ap_uint<1> tmp_622 = Copy_620(tmp_607);  // Copy
    const ap_uint<1> tmp_623 = ap_uint<1>((tmp_607 & tmp_619));  // basic_and
    const ap_uint<5> tmp_626 = Copy_624(tmp_611);  // Copy
    const ap_uint<5> tmp_627 = ap_uint<5>((tmp_611 + tmp_623));  // basic_add
    const ap_uint<1> tmp_631 = uq_select_628(arg_0_435);  // uq_select
    const ap_uint<1> tmp_634 = Copy_632(tmp_631);  // Copy
    const ap_uint<1> tmp_635 = ap_uint<1>((~tmp_631));  // basic_invert
    const ap_uint<1> tmp_638 = Copy_636(tmp_623);  // Copy
    const ap_uint<1> tmp_639 = ap_uint<1>((tmp_623 & tmp_635));  // basic_and
    const ap_uint<5> tmp_642 = Copy_640(tmp_627);  // Copy
    const ap_uint<5> tmp_643 = ap_uint<5>((tmp_627 + tmp_639));  // basic_add
    const ap_uint<1> tmp_647 = uq_select_644(arg_0_435);  // uq_select
    const ap_uint<1> tmp_650 = Copy_648(tmp_647);  // Copy
    const ap_uint<1> tmp_651 = ap_uint<1>((~tmp_647));  // basic_invert
    const ap_uint<1> tmp_654 = Copy_652(tmp_639);  // Copy
    const ap_uint<1> tmp_655 = ap_uint<1>((tmp_639 & tmp_651));  // basic_and
    const ap_uint<5> tmp_658 = Copy_656(tmp_643);  // Copy
    const ap_uint<5> tmp_659 = ap_uint<5>((tmp_643 + tmp_655));  // basic_add
    const ap_uint<1> tmp_663 = uq_select_660(arg_0_435);  // uq_select
    const ap_uint<1> tmp_666 = Copy_664(tmp_663);  // Copy
    const ap_uint<1> tmp_667 = ap_uint<1>((~tmp_663));  // basic_invert
    const ap_uint<1> tmp_670 = Copy_668(tmp_655);  // Copy
    const ap_uint<1> tmp_671 = ap_uint<1>((tmp_655 & tmp_667));  // basic_and
    const ap_uint<5> tmp_674 = Copy_672(tmp_659);  // Copy
    const ap_uint<5> tmp_675 = ap_uint<5>((tmp_659 + tmp_671));  // basic_add
    const ap_uint<1> tmp_679 = uq_select_676(arg_0_435);  // uq_select
    const ap_uint<1> tmp_682 = Copy_680(tmp_679);  // Copy
    const ap_uint<1> tmp_683 = ap_uint<1>((~tmp_679));  // basic_invert
    const ap_uint<1> tmp_686 = Copy_684(tmp_671);  // Copy
    const ap_uint<1> tmp_687 = ap_uint<1>((tmp_671 & tmp_683));  // basic_and
    const ap_uint<5> tmp_690 = Copy_688(tmp_675);  // Copy
    const ap_uint<5> tmp_691 = ap_uint<5>((tmp_675 + tmp_687));  // basic_add
    const ap_uint<1> tmp_695 = uq_select_692(arg_0_435);  // uq_select
    const ap_uint<1> tmp_698 = Copy_696(tmp_695);  // Copy
    const ap_uint<1> tmp_699 = ap_uint<1>((~tmp_695));  // basic_invert
    const ap_uint<1> tmp_702 = Copy_700(tmp_687);  // Copy
    const ap_uint<1> tmp_703 = ap_uint<1>((tmp_687 & tmp_699));  // basic_and
    const ap_uint<5> tmp_706 = Copy_704(tmp_691);  // Copy
    const ap_uint<5> tmp_707 = ap_uint<5>((tmp_691 + tmp_703));  // basic_add
    const ap_uint<1> tmp_711 = uq_select_708(arg_0_435);  // uq_select
    const ap_uint<1> tmp_714 = Copy_712(tmp_711);  // Copy
    const ap_uint<1> tmp_715 = ap_uint<1>((~tmp_711));  // basic_invert
    const ap_uint<1> tmp_718 = Copy_716(tmp_703);  // Copy
    const ap_uint<1> tmp_719 = ap_uint<1>((tmp_703 & tmp_715));  // basic_and
    const ap_uint<5> tmp_722 = Copy_720(tmp_707);  // Copy
    const ap_uint<5> tmp_723 = ap_uint<5>((tmp_707 + tmp_719));  // basic_add
    const ap_uint<1> tmp_727 = uq_select_724(arg_0_435);  // uq_select
    const ap_uint<1> tmp_730 = Copy_728(tmp_727);  // Copy
    const ap_uint<1> tmp_731 = ap_uint<1>((~tmp_727));  // basic_invert
    const ap_uint<1> tmp_734 = Copy_732(tmp_719);  // Copy
    const ap_uint<1> tmp_735 = ap_uint<1>((tmp_719 & tmp_731));  // basic_and
    const ap_uint<5> tmp_738 = Copy_736(tmp_723);  // Copy
    const ap_uint<5> tmp_739 = ap_uint<5>((tmp_723 + tmp_735));  // basic_add
    const ap_uint<1> tmp_743 = uq_select_740(arg_0_435);  // uq_select
    const ap_uint<1> tmp_746 = Copy_744(tmp_743);  // Copy
    const ap_uint<1> tmp_747 = ap_uint<1>((~tmp_743));  // basic_invert
    const ap_uint<1> tmp_750 = Copy_748(tmp_735);  // Copy
    const ap_uint<1> tmp_751 = ap_uint<1>((tmp_735 & tmp_747));  // basic_and
    const ap_uint<5> tmp_754 = Copy_752(tmp_739);  // Copy
    const ap_uint<5> tmp_755 = ap_uint<5>((tmp_739 + tmp_751));  // basic_add
    const ap_uint<1> tmp_759 = uq_select_756(arg_0_435);  // uq_select
    const ap_uint<1> tmp_762 = Copy_760(tmp_759);  // Copy
    const ap_uint<1> tmp_763 = ap_uint<1>((~tmp_759));  // basic_invert
    const ap_uint<1> tmp_766 = Copy_764(tmp_751);  // Copy
    const ap_uint<1> tmp_767 = ap_uint<1>((tmp_751 & tmp_763));  // basic_and
    const ap_uint<5> tmp_770 = Copy_768(tmp_755);  // Copy
    const ap_uint<5> tmp_771 = ap_uint<5>((tmp_755 + tmp_767));  // basic_add
    const ap_uint<1> tmp_775 = uq_select_772(arg_0_435);  // uq_select
    const ap_uint<1> tmp_778 = Copy_776(tmp_775);  // Copy
    const ap_uint<1> tmp_779 = ap_uint<1>((~tmp_775));  // basic_invert
    const ap_uint<1> tmp_782 = Copy_780(tmp_767);  // Copy
    const ap_uint<1> tmp_783 = ap_uint<1>((tmp_767 & tmp_779));  // basic_and
    const ap_uint<5> tmp_786 = Copy_784(tmp_771);  // Copy
    const ap_uint<5> tmp_787 = ap_uint<5>((tmp_771 + tmp_783));  // basic_add
    const ap_uint<1> tmp_791 = uq_select_788(arg_0_435);  // uq_select
    const ap_uint<1> tmp_794 = Copy_792(tmp_791);  // Copy
    const ap_uint<1> tmp_795 = ap_uint<1>((~tmp_791));  // basic_invert
    const ap_uint<1> tmp_798 = Copy_796(tmp_783);  // Copy
    const ap_uint<1> tmp_799 = ap_uint<1>((tmp_783 & tmp_795));  // basic_and
    const ap_uint<5> tmp_802 = Copy_800(tmp_787);  // Copy
    const ap_uint<5> tmp_803 = ap_uint<5>((tmp_787 + tmp_799));  // basic_add
    const ap_uint<1> tmp_807 = uq_select_804(arg_0_435);  // uq_select
    const ap_uint<1> tmp_810 = Copy_808(tmp_807);  // Copy
    const ap_uint<1> tmp_811 = ap_uint<1>((~tmp_807));  // basic_invert
    const ap_uint<1> tmp_814 = Copy_812(tmp_799);  // Copy
    const ap_uint<1> tmp_815 = ap_uint<1>((tmp_799 & tmp_811));  // basic_and
    const ap_uint<5> tmp_818 = Copy_816(tmp_803);  // Copy
    const ap_uint<5> tmp_819 = ap_uint<5>((tmp_803 + tmp_815));  // basic_add
    const ap_uint<1> tmp_823 = uq_select_820(arg_0_435);  // uq_select
    const ap_uint<1> tmp_826 = Copy_824(tmp_823);  // Copy
    const ap_uint<1> tmp_827 = ap_uint<1>((~tmp_823));  // basic_invert
    const ap_uint<1> tmp_830 = Copy_828(tmp_815);  // Copy
    const ap_uint<1> tmp_831 = ap_uint<1>((tmp_815 & tmp_827));  // basic_and
    const ap_uint<5> tmp_834 = Copy_832(tmp_819);  // Copy
    const ap_uint<5> tmp_835 = ap_uint<5>((tmp_819 + tmp_831));  // basic_add
    const ap_uint<1> tmp_839 = uq_select_836(arg_0_435);  // uq_select
    const ap_uint<1> tmp_842 = Copy_840(tmp_839);  // Copy
    const ap_uint<1> tmp_843 = ap_uint<1>((~tmp_839));  // basic_invert
    const ap_uint<1> tmp_846 = Copy_844(tmp_831);  // Copy
    const ap_uint<1> tmp_847 = ap_uint<1>((tmp_831 & tmp_843));  // basic_and
    const ap_uint<5> tmp_850 = Copy_848(tmp_835);  // Copy
    const ap_uint<5> tmp_851 = ap_uint<5>((tmp_835 + tmp_847));  // basic_add
    const ap_uint<1> tmp_855 = uq_select_852(arg_0_435);  // uq_select
    const ap_uint<1> tmp_858 = Copy_856(tmp_855);  // Copy
    const ap_uint<1> tmp_859 = ap_uint<1>((~tmp_855));  // basic_invert
    const ap_uint<1> tmp_862 = Copy_860(tmp_847);  // Copy
    const ap_uint<1> tmp_863 = ap_uint<1>((tmp_847 & tmp_859));  // basic_and
    const ap_uint<5> tmp_866 = Copy_864(tmp_851);  // Copy
    const ap_uint<5> tmp_867 = ap_uint<5>((tmp_851 + tmp_863));  // basic_add
    const ap_uint<1> tmp_871 = uq_select_868(arg_0_435);  // uq_select
    const ap_uint<1> tmp_874 = Copy_872(tmp_871);  // Copy
    const ap_uint<1> tmp_875 = ap_uint<1>((~tmp_871));  // basic_invert
    const ap_uint<1> tmp_878 = Copy_876(tmp_863);  // Copy
    const ap_uint<1> tmp_879 = ap_uint<1>((tmp_863 & tmp_875));  // basic_and
    const ap_uint<5> tmp_882 = Copy_880(tmp_867);  // Copy
    const ap_uint<5> tmp_883 = ap_uint<5>((tmp_867 + tmp_879));  // basic_add
    const ap_uint<1> tmp_887 = uq_select_884(arg_0_435);  // uq_select
    const ap_uint<1> tmp_890 = Copy_888(tmp_887);  // Copy
    const ap_uint<1> tmp_891 = ap_uint<1>((~tmp_887));  // basic_invert
    const ap_uint<1> tmp_894 = Copy_892(tmp_879);  // Copy
    const ap_uint<1> tmp_895 = ap_uint<1>((tmp_879 & tmp_891));  // basic_and
    const ap_uint<5> tmp_898 = Copy_896(tmp_883);  // Copy
    const ap_uint<5> tmp_899 = ap_uint<5>((tmp_883 + tmp_895));  // basic_add
    const ap_uint<1> tmp_903 = uq_select_900(arg_0_435);  // uq_select
    const ap_uint<1> tmp_906 = Copy_904(tmp_903);  // Copy
    const ap_uint<1> tmp_907 = ap_uint<1>((~tmp_903));  // basic_invert
    const ap_uint<1> tmp_910 = Copy_908(tmp_895);  // Copy
    const ap_uint<1> tmp_911 = ap_uint<1>((tmp_895 & tmp_907));  // basic_and
    const ap_uint<5> tmp_914 = Copy_912(tmp_899);  // Copy
    const ap_uint<5> tmp_915 = ap_uint<5>((tmp_899 + tmp_911));  // basic_add
    const ap_uint<1> tmp_919 = uq_select_916(arg_0_435);  // uq_select
    const ap_uint<1> tmp_922 = Copy_920(tmp_919);  // Copy
    const ap_uint<1> tmp_923 = ap_uint<1>((~tmp_919));  // basic_invert
    const ap_uint<1> tmp_926 = Copy_924(tmp_911);  // Copy
    const ap_uint<1> tmp_927 = ap_uint<1>((tmp_911 & tmp_923));  // basic_and
    const ap_uint<5> tmp_930 = Copy_928(tmp_915);  // Copy
    const ap_uint<5> tmp_931 = ap_uint<5>((tmp_915 + tmp_927));  // basic_add
    return tmp_931;
}
std::tuple<ap_uint<4>, ap_uint<4>> make_Tuple_943(ap_uint<4> arg_0, ap_uint<4> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_946 = std::tuple<ap_uint<4>, ap_uint<4>>(std::make_tuple(arg_0_944, arg_1_945));  // basic_tuple_maker_2
    return tmp_946;
}
std::tuple<ap_uint<4>, ap_uint<4>> uq_aligner_938(ap_uint<3> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<4> tmp_941 = ap_uint<4>((arg_0_939 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<4> tmp_942 = ap_uint<4>((arg_1_940 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_947 = make_Tuple_943(tmp_941, tmp_942);  // make_Tuple
    return tmp_947;
}
ap_uint<4> Tuple_get_item_0_949(std::tuple<ap_uint<4>, ap_uint<4>> arg_0) {  // Tuple_get_item_0
    const ap_uint<4> tmp_951 = ap_uint<4>(std::get<0>(arg_0_950));  // basic_get_item_0
    return tmp_951;
}
ap_uint<4> Tuple_get_item_1_953(std::tuple<ap_uint<4>, ap_uint<4>> arg_0) {  // Tuple_get_item_1
    const ap_uint<4> tmp_955 = ap_uint<4>(std::get<1>(arg_0_954));  // basic_get_item_1
    return tmp_955;
}
ap_uint<4> Copy_957(ap_uint<4> arg_0) {  // Copy
    return arg_0_958;
}
ap_uint<4> uq_add_935(ap_uint<3> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_948 = uq_aligner_938(arg_0_936, arg_1_937);  // uq_aligner
    const ap_uint<4> tmp_952 = Tuple_get_item_0_949(tmp_948);  // Tuple_get_item_0
    const ap_uint<4> tmp_956 = Tuple_get_item_1_953(tmp_948);  // Tuple_get_item_1
    const ap_uint<4> tmp_959 = Copy_957(tmp_952);  // Copy
    const ap_uint<4> tmp_960 = ap_uint<4>((tmp_952 + tmp_956));  // basic_add
    return tmp_960;
}
ap_uint<6> uq_to_q_933(ap_uint<5> arg_0) {  // uq_to_q
    const ap_uint<4> tmp_961 = uq_add_935(ap_uint<3>(5), ap_uint<1>(1));  // uq_add
    const ap_uint<6> tmp_962 = ap_uint<6>(0);  // q_alloc
    const ap_uint<6> tmp_963 = ap_uint<6>(arg_0_934);  // basic_identity
    return tmp_963;
}
std::tuple<ap_uint<3>, ap_uint<3>> make_Tuple_975(ap_uint<3> arg_0, ap_uint<3> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_978 = std::tuple<ap_uint<3>, ap_uint<3>>(std::make_tuple(arg_0_976, arg_1_977));  // basic_tuple_maker_2
    return tmp_978;
}
std::tuple<ap_uint<3>, ap_uint<3>> uq_aligner_970(ap_uint<2> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<3> tmp_973 = ap_uint<3>((arg_0_971 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<3> tmp_974 = ap_uint<3>((arg_1_972 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_979 = make_Tuple_975(tmp_973, tmp_974);  // make_Tuple
    return tmp_979;
}
ap_uint<3> Tuple_get_item_0_981(std::tuple<ap_uint<3>, ap_uint<3>> arg_0) {  // Tuple_get_item_0
    const ap_uint<3> tmp_983 = ap_uint<3>(std::get<0>(arg_0_982));  // basic_get_item_0
    return tmp_983;
}
ap_uint<3> Tuple_get_item_1_985(std::tuple<ap_uint<3>, ap_uint<3>> arg_0) {  // Tuple_get_item_1
    const ap_uint<3> tmp_987 = ap_uint<3>(std::get<1>(arg_0_986));  // basic_get_item_1
    return tmp_987;
}
ap_uint<3> Copy_989(ap_uint<3> arg_0) {  // Copy
    return arg_0_990;
}
ap_uint<3> uq_add_967(ap_uint<2> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_980 = uq_aligner_970(arg_0_968, arg_1_969);  // uq_aligner
    const ap_uint<3> tmp_984 = Tuple_get_item_0_981(tmp_980);  // Tuple_get_item_0
    const ap_uint<3> tmp_988 = Tuple_get_item_1_985(tmp_980);  // Tuple_get_item_1
    const ap_uint<3> tmp_991 = Copy_989(tmp_984);  // Copy
    const ap_uint<3> tmp_992 = ap_uint<3>((tmp_984 + tmp_988));  // basic_add
    return tmp_992;
}
ap_uint<3> uq_to_q_965(ap_uint<2> arg_0) {  // uq_to_q
    const ap_uint<3> tmp_993 = uq_add_967(ap_uint<2>(2), ap_uint<1>(1));  // uq_add
    const ap_uint<3> tmp_994 = ap_uint<3>(0);  // q_alloc
    const ap_uint<3> tmp_995 = ap_uint<3>(arg_0_966);  // basic_identity
    return tmp_995;
}
ap_uint<1> q_sign_bit_1006(ap_uint<6> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1008 = ap_uint<1>(((arg_0_1007 >> 5) & ap_uint<1>(1)));  // basic_select
    return tmp_1008;
}
ap_uint<7> q_sign_extend_1004(ap_uint<6> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1009 = q_sign_bit_1006(arg_0_1005);  // q_sign_bit
    const ap_uint<2> tmp_1010 = ap_uint<2>((tmp_1009 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_1011 = ap_uint<1>((tmp_1010 - tmp_1009));  // basic_sub
    const ap_uint<7> tmp_1012 = ap_uint<7>(0);  // q_alloc
    const ap_uint<7> tmp_1013 = ap_uint<7>(((tmp_1011 << 6) | arg_0_1005));  // basic_concat
    return tmp_1013;
}
ap_uint<1> q_sign_bit_1018(ap_uint<3> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1020 = ap_uint<1>(((arg_0_1019 >> 2) & ap_uint<1>(1)));  // basic_select
    return tmp_1020;
}
ap_uint<7> q_sign_extend_1016(ap_uint<3> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1021 = q_sign_bit_1018(arg_0_1017);  // q_sign_bit
    const ap_uint<5> tmp_1022 = ap_uint<5>((tmp_1021 << ap_uint<3>(4)));  // basic_lshift
    const ap_uint<4> tmp_1023 = ap_uint<4>((tmp_1022 - tmp_1021));  // basic_sub
    const ap_uint<7> tmp_1024 = ap_uint<7>(0);  // q_alloc
    const ap_uint<7> tmp_1025 = ap_uint<7>(((tmp_1023 << 3) | arg_0_1017));  // basic_concat
    return tmp_1025;
}
std::tuple<ap_uint<7>, ap_uint<7>> make_Tuple_1027(ap_uint<7> arg_0, ap_uint<7> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_1030 = std::tuple<ap_uint<7>, ap_uint<7>>(std::make_tuple(arg_0_1028, arg_1_1029));  // basic_tuple_maker_2
    return tmp_1030;
}
std::tuple<ap_uint<7>, ap_uint<7>> q_aligner_1000(ap_uint<6> arg_0, ap_uint<3> arg_1) {  // q_aligner
    const ap_uint<6> tmp_1003 = ap_uint<6>((arg_0_1001 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<7> tmp_1014 = q_sign_extend_1004(tmp_1003);  // q_sign_extend
    const ap_uint<3> tmp_1015 = ap_uint<3>((arg_1_1002 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<7> tmp_1026 = q_sign_extend_1016(tmp_1015);  // q_sign_extend
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_1031 = make_Tuple_1027(tmp_1014, tmp_1026);  // make_Tuple
    return tmp_1031;
}
ap_uint<7> Tuple_get_item_0_1033(std::tuple<ap_uint<7>, ap_uint<7>> arg_0) {  // Tuple_get_item_0
    const ap_uint<7> tmp_1035 = ap_uint<7>(std::get<0>(arg_0_1034));  // basic_get_item_0
    return tmp_1035;
}
ap_uint<7> Tuple_get_item_1_1037(std::tuple<ap_uint<7>, ap_uint<7>> arg_0) {  // Tuple_get_item_1
    const ap_uint<7> tmp_1039 = ap_uint<7>(std::get<1>(arg_0_1038));  // basic_get_item_1
    return tmp_1039;
}
ap_uint<7> Copy_1041(ap_uint<7> arg_0) {  // Copy
    return arg_0_1042;
}
ap_uint<7> q_sub_997(ap_uint<6> arg_0, ap_uint<3> arg_1) {  // q_sub
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_1032 = q_aligner_1000(arg_0_998, arg_1_999);  // q_aligner
    const ap_uint<7> tmp_1036 = Tuple_get_item_0_1033(tmp_1032);  // Tuple_get_item_0
    const ap_uint<7> tmp_1040 = Tuple_get_item_1_1037(tmp_1032);  // Tuple_get_item_1
    const ap_uint<7> tmp_1043 = Copy_1041(tmp_1036);  // Copy
    const ap_uint<7> tmp_1044 = ap_uint<7>((tmp_1036 - tmp_1040));  // basic_sub
    return tmp_1044;
}
ap_uint<1> q_sign_bit_1055(ap_uint<7> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1057 = ap_uint<1>(((arg_0_1056 >> 6) & ap_uint<1>(1)));  // basic_select
    return tmp_1057;
}
ap_uint<8> q_sign_extend_1053(ap_uint<7> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1058 = q_sign_bit_1055(arg_0_1054);  // q_sign_bit
    const ap_uint<2> tmp_1059 = ap_uint<2>((tmp_1058 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_1060 = ap_uint<1>((tmp_1059 - tmp_1058));  // basic_sub
    const ap_uint<8> tmp_1061 = ap_uint<8>(0);  // q_alloc
    const ap_uint<8> tmp_1062 = ap_uint<8>(((tmp_1060 << 7) | arg_0_1054));  // basic_concat
    return tmp_1062;
}
ap_uint<1> q_sign_bit_1067(ap_uint<2> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1069 = ap_uint<1>(((arg_0_1068 >> 1) & ap_uint<1>(1)));  // basic_select
    return tmp_1069;
}
ap_uint<8> q_sign_extend_1065(ap_uint<2> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1070 = q_sign_bit_1067(arg_0_1066);  // q_sign_bit
    const ap_uint<7> tmp_1071 = ap_uint<7>((tmp_1070 << ap_uint<3>(6)));  // basic_lshift
    const ap_uint<6> tmp_1072 = ap_uint<6>((tmp_1071 - tmp_1070));  // basic_sub
    const ap_uint<8> tmp_1073 = ap_uint<8>(0);  // q_alloc
    const ap_uint<8> tmp_1074 = ap_uint<8>(((tmp_1072 << 2) | arg_0_1066));  // basic_concat
    return tmp_1074;
}
std::tuple<ap_uint<8>, ap_uint<8>> make_Tuple_1076(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_1079 = std::tuple<ap_uint<8>, ap_uint<8>>(std::make_tuple(arg_0_1077, arg_1_1078));  // basic_tuple_maker_2
    return tmp_1079;
}
std::tuple<ap_uint<8>, ap_uint<8>> q_aligner_1049(ap_uint<7> arg_0, ap_uint<2> arg_1) {  // q_aligner
    const ap_uint<7> tmp_1052 = ap_uint<7>((arg_0_1050 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_1063 = q_sign_extend_1053(tmp_1052);  // q_sign_extend
    const ap_uint<2> tmp_1064 = ap_uint<2>((arg_1_1051 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_1075 = q_sign_extend_1065(tmp_1064);  // q_sign_extend
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_1080 = make_Tuple_1076(tmp_1063, tmp_1075);  // make_Tuple
    return tmp_1080;
}
ap_uint<8> Tuple_get_item_0_1082(std::tuple<ap_uint<8>, ap_uint<8>> arg_0) {  // Tuple_get_item_0
    const ap_uint<8> tmp_1084 = ap_uint<8>(std::get<0>(arg_0_1083));  // basic_get_item_0
    return tmp_1084;
}
ap_uint<8> Tuple_get_item_1_1086(std::tuple<ap_uint<8>, ap_uint<8>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_1088 = ap_uint<8>(std::get<1>(arg_0_1087));  // basic_get_item_1
    return tmp_1088;
}
ap_uint<8> Copy_1090(ap_uint<8> arg_0) {  // Copy
    return arg_0_1091;
}
ap_uint<8> q_add_1046(ap_uint<7> arg_0, ap_uint<2> arg_1) {  // q_add
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_1081 = q_aligner_1049(arg_0_1047, arg_1_1048);  // q_aligner
    const ap_uint<8> tmp_1085 = Tuple_get_item_0_1082(tmp_1081);  // Tuple_get_item_0
    const ap_uint<8> tmp_1089 = Tuple_get_item_1_1086(tmp_1081);  // Tuple_get_item_1
    const ap_uint<8> tmp_1092 = Copy_1090(tmp_1085);  // Copy
    const ap_uint<8> tmp_1093 = ap_uint<8>((tmp_1085 + tmp_1089));  // basic_add
    return tmp_1093;
}
ap_uint<1> q_sign_bit_1095(ap_uint<8> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1097 = ap_uint<1>(((arg_0_1096 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_1097;
}
ap_uint<32> uq_resize_1099(ap_uint<31> arg_0) {  // uq_resize
    const ap_uint<32> tmp_1101 = ap_uint<32>((arg_0_1100 << ap_uint<1>(1)));  // basic_lshift
    return tmp_1101;
}
ap_uint<1> q_sign_bit_1105(ap_uint<8> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1107 = ap_uint<1>(((arg_0_1106 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_1107;
}
ap_uint<8> Copy_1112(ap_uint<8> arg_0) {  // Copy
    return arg_0_1113;
}
ap_uint<8> Copy_1118(ap_uint<8> arg_0) {  // Copy
    return arg_0_1119;
}
ap_uint<8> Copy_1122(ap_uint<8> arg_0) {  // Copy
    return arg_0_1123;
}
ap_uint<8> Copy_1126(ap_uint<8> arg_0) {  // Copy
    return arg_0_1127;
}
ap_uint<8> Copy_1130(ap_uint<8> arg_0) {  // Copy
    return arg_0_1131;
}
ap_uint<8> Copy_1134(ap_uint<8> arg_0) {  // Copy
    return arg_0_1135;
}
ap_uint<8> q_neg_1115(ap_uint<8> arg_0) {  // q_neg
    const ap_uint<1> tmp_1117 = ap_uint<1>((arg_0_1116 == 128));  // _q_is_min_val
    const ap_uint<8> tmp_1120 = Copy_1118(arg_0_1116);  // Copy
    const ap_uint<8> tmp_1121 = ap_uint<8>((~arg_0_1116));  // basic_invert
    const ap_uint<8> tmp_1124 = Copy_1122(arg_0_1116);  // Copy
    const ap_uint<8> tmp_1125 = ap_uint<8>((tmp_1121 + ap_uint<1>(1)));  // basic_add
    const ap_uint<8> tmp_1128 = Copy_1126(arg_0_1116);  // Copy
    const ap_uint<8> tmp_1129 = ap_uint<8>((arg_0_1116 ^ arg_0_1116));  // basic_xor
    const ap_uint<8> tmp_1132 = Copy_1130(arg_0_1116);  // Copy
    const ap_uint<8> tmp_1133 = ap_uint<8>((~tmp_1129));  // basic_invert
    const ap_uint<8> tmp_1136 = Copy_1134(arg_0_1116);  // Copy
    const ap_uint<8> tmp_1137 = ap_uint<8>((tmp_1117 ? tmp_1133 : tmp_1125));  // basic_mux_2_1
    return tmp_1137;
}
ap_uint<8> Copy_1139(ap_uint<8> arg_0) {  // Copy
    return arg_0_1140;
}
ap_uint<8> q_add_sign_1109(ap_uint<8> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<8> tmp_1114 = Copy_1112(arg_0_1110);  // Copy
    const ap_uint<8> tmp_1138 = q_neg_1115(arg_0_1110);  // q_neg
    const ap_uint<8> tmp_1141 = Copy_1139(arg_0_1110);  // Copy
    const ap_uint<8> tmp_1142 = ap_uint<8>((arg_1_1111 ? tmp_1138 : tmp_1114));  // basic_mux_2_1
    return tmp_1142;
}
ap_uint<8> q_abs_1103(ap_uint<8> arg_0) {  // q_abs
    const ap_uint<1> tmp_1108 = q_sign_bit_1105(arg_0_1104);  // q_sign_bit
    const ap_uint<8> tmp_1143 = q_add_sign_1109(arg_0_1104, tmp_1108);  // q_add_sign
    return tmp_1143;
}
ap_uint<7> q_to_uq_1145(ap_uint<8> arg_0) {  // q_to_uq
    const ap_uint<7> tmp_1147 = ap_uint<7>(arg_0_1146);  // basic_identity
    return tmp_1147;
}
ap_uint<32> Copy_1152(ap_uint<32> arg_0) {  // Copy
    return arg_0_1153;
}
ap_uint<32> uq_lshift_1149(ap_uint<32> arg_0, ap_uint<7> arg_1) {  // uq_lshift
    const ap_uint<32> tmp_1154 = Copy_1152(arg_0_1150);  // Copy
    const ap_uint<32> tmp_1155 = ap_uint<32>((arg_0_1150 << arg_1_1151));  // basic_lshift
    return tmp_1155;
}
ap_uint<32> Copy_1160(ap_uint<32> arg_0) {  // Copy
    return arg_0_1161;
}
ap_uint<32> uq_rshift_1157(ap_uint<32> arg_0, ap_uint<7> arg_1) {  // uq_rshift
    const ap_uint<32> tmp_1162 = Copy_1160(arg_0_1158);  // Copy
    const ap_uint<32> tmp_1163 = ap_uint<32>((arg_0_1158 >> arg_1_1159));  // basic_rshift
    return tmp_1163;
}
ap_uint<1> q_sign_bit_1175(ap_uint<9> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1177 = ap_uint<1>(((arg_0_1176 >> 8) & ap_uint<1>(1)));  // basic_select
    return tmp_1177;
}
ap_uint<10> q_sign_extend_1173(ap_uint<9> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1178 = q_sign_bit_1175(arg_0_1174);  // q_sign_bit
    const ap_uint<2> tmp_1179 = ap_uint<2>((tmp_1178 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_1180 = ap_uint<1>((tmp_1179 - tmp_1178));  // basic_sub
    const ap_uint<10> tmp_1181 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_1182 = ap_uint<10>(((tmp_1180 << 9) | arg_0_1174));  // basic_concat
    return tmp_1182;
}
ap_uint<1> q_sign_bit_1187(ap_uint<8> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1189 = ap_uint<1>(((arg_0_1188 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_1189;
}
ap_uint<10> q_sign_extend_1185(ap_uint<8> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1190 = q_sign_bit_1187(arg_0_1186);  // q_sign_bit
    const ap_uint<3> tmp_1191 = ap_uint<3>((tmp_1190 << ap_uint<2>(2)));  // basic_lshift
    const ap_uint<2> tmp_1192 = ap_uint<2>((tmp_1191 - tmp_1190));  // basic_sub
    const ap_uint<10> tmp_1193 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_1194 = ap_uint<10>(((tmp_1192 << 8) | arg_0_1186));  // basic_concat
    return tmp_1194;
}
std::tuple<ap_uint<10>, ap_uint<10>> make_Tuple_1196(ap_uint<10> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1199 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(arg_0_1197, arg_1_1198));  // basic_tuple_maker_2
    return tmp_1199;
}
std::tuple<ap_uint<10>, ap_uint<10>> q_aligner_1169(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_aligner
    const ap_uint<9> tmp_1172 = ap_uint<9>((arg_0_1170 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1183 = q_sign_extend_1173(tmp_1172);  // q_sign_extend
    const ap_uint<8> tmp_1184 = ap_uint<8>((arg_1_1171 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1195 = q_sign_extend_1185(tmp_1184);  // q_sign_extend
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1200 = make_Tuple_1196(tmp_1183, tmp_1195);  // make_Tuple
    return tmp_1200;
}
ap_uint<10> Tuple_get_item_0_1202(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<10> tmp_1204 = ap_uint<10>(std::get<0>(arg_0_1203));  // basic_get_item_0
    return tmp_1204;
}
ap_uint<10> Tuple_get_item_1_1206(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1208 = ap_uint<10>(std::get<1>(arg_0_1207));  // basic_get_item_1
    return tmp_1208;
}
ap_uint<10> Copy_1210(ap_uint<10> arg_0) {  // Copy
    return arg_0_1211;
}
ap_uint<10> q_sub_1166(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_sub
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1201 = q_aligner_1169(arg_0_1167, arg_1_1168);  // q_aligner
    const ap_uint<10> tmp_1205 = Tuple_get_item_0_1202(tmp_1201);  // Tuple_get_item_0
    const ap_uint<10> tmp_1209 = Tuple_get_item_1_1206(tmp_1201);  // Tuple_get_item_1
    const ap_uint<10> tmp_1212 = Copy_1210(tmp_1205);  // Copy
    const ap_uint<10> tmp_1213 = ap_uint<10>((tmp_1205 - tmp_1209));  // basic_sub
    return tmp_1213;
}
ap_uint<1> q_sign_bit_1224(ap_uint<9> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1226 = ap_uint<1>(((arg_0_1225 >> 8) & ap_uint<1>(1)));  // basic_select
    return tmp_1226;
}
ap_uint<10> q_sign_extend_1222(ap_uint<9> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1227 = q_sign_bit_1224(arg_0_1223);  // q_sign_bit
    const ap_uint<2> tmp_1228 = ap_uint<2>((tmp_1227 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_1229 = ap_uint<1>((tmp_1228 - tmp_1227));  // basic_sub
    const ap_uint<10> tmp_1230 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_1231 = ap_uint<10>(((tmp_1229 << 9) | arg_0_1223));  // basic_concat
    return tmp_1231;
}
ap_uint<1> q_sign_bit_1236(ap_uint<8> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1238 = ap_uint<1>(((arg_0_1237 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_1238;
}
ap_uint<10> q_sign_extend_1234(ap_uint<8> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_1239 = q_sign_bit_1236(arg_0_1235);  // q_sign_bit
    const ap_uint<3> tmp_1240 = ap_uint<3>((tmp_1239 << ap_uint<2>(2)));  // basic_lshift
    const ap_uint<2> tmp_1241 = ap_uint<2>((tmp_1240 - tmp_1239));  // basic_sub
    const ap_uint<10> tmp_1242 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_1243 = ap_uint<10>(((tmp_1241 << 8) | arg_0_1235));  // basic_concat
    return tmp_1243;
}
std::tuple<ap_uint<10>, ap_uint<10>> make_Tuple_1245(ap_uint<10> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1248 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(arg_0_1246, arg_1_1247));  // basic_tuple_maker_2
    return tmp_1248;
}
std::tuple<ap_uint<10>, ap_uint<10>> q_aligner_1218(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_aligner
    const ap_uint<9> tmp_1221 = ap_uint<9>((arg_0_1219 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1232 = q_sign_extend_1222(tmp_1221);  // q_sign_extend
    const ap_uint<8> tmp_1233 = ap_uint<8>((arg_1_1220 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1244 = q_sign_extend_1234(tmp_1233);  // q_sign_extend
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1249 = make_Tuple_1245(tmp_1232, tmp_1244);  // make_Tuple
    return tmp_1249;
}
ap_uint<10> Tuple_get_item_0_1251(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<10> tmp_1253 = ap_uint<10>(std::get<0>(arg_0_1252));  // basic_get_item_0
    return tmp_1253;
}
ap_uint<10> Tuple_get_item_1_1255(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1257 = ap_uint<10>(std::get<1>(arg_0_1256));  // basic_get_item_1
    return tmp_1257;
}
ap_uint<10> Copy_1259(ap_uint<10> arg_0) {  // Copy
    return arg_0_1260;
}
ap_uint<10> q_add_1215(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1250 = q_aligner_1218(arg_0_1216, arg_1_1217);  // q_aligner
    const ap_uint<10> tmp_1254 = Tuple_get_item_0_1251(tmp_1250);  // Tuple_get_item_0
    const ap_uint<10> tmp_1258 = Tuple_get_item_1_1255(tmp_1250);  // Tuple_get_item_1
    const ap_uint<10> tmp_1261 = Copy_1259(tmp_1254);  // Copy
    const ap_uint<10> tmp_1262 = ap_uint<10>((tmp_1254 + tmp_1258));  // basic_add
    return tmp_1262;
}
ap_uint<10> Copy_1264(ap_uint<10> arg_0) {  // Copy
    return arg_0_1265;
}
std::tuple<ap_uint<31>, ap_uint<10>> make_Tuple_1268(ap_uint<31> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_1271 = std::tuple<ap_uint<31>, ap_uint<10>>(std::make_tuple(arg_0_1269, arg_1_1270));  // basic_tuple_maker_2
    return tmp_1271;
}
std::tuple<ap_uint<31>, ap_uint<10>> fp32_normalize_431(ap_uint<31> arg_0, ap_uint<9> arg_1) {  // fp32_normalize
    const ap_uint<5> tmp_932 = lzc_434(arg_0_432);  // lzc
    const ap_uint<6> tmp_964 = uq_to_q_933(tmp_932);  // uq_to_q
    const ap_uint<3> tmp_996 = uq_to_q_965(ap_uint<2>(2));  // uq_to_q
    const ap_uint<7> tmp_1045 = q_sub_997(tmp_964, tmp_996);  // q_sub
    const ap_uint<8> tmp_1094 = q_add_1046(tmp_1045, ap_uint<2>(1));  // q_add
    const ap_uint<1> tmp_1098 = q_sign_bit_1095(tmp_1094);  // q_sign_bit
    const ap_uint<32> tmp_1102 = uq_resize_1099(arg_0_432);  // uq_resize
    const ap_uint<8> tmp_1144 = q_abs_1103(tmp_1094);  // q_abs
    const ap_uint<7> tmp_1148 = q_to_uq_1145(tmp_1144);  // q_to_uq
    const ap_uint<32> tmp_1156 = uq_lshift_1149(tmp_1102, tmp_1148);  // uq_lshift
    const ap_uint<32> tmp_1164 = uq_rshift_1157(tmp_1102, tmp_1148);  // uq_rshift
    const ap_uint<31> tmp_1165 = ap_uint<31>((tmp_1098 ? tmp_1164 : tmp_1156));  // basic_mux_2_1
    const ap_uint<10> tmp_1214 = q_sub_1166(arg_1_433, tmp_1144);  // q_sub
    const ap_uint<10> tmp_1263 = q_add_1215(arg_1_433, tmp_1144);  // q_add
    const ap_uint<10> tmp_1266 = Copy_1264(tmp_1263);  // Copy
    const ap_uint<10> tmp_1267 = ap_uint<10>((tmp_1098 ? tmp_1263 : tmp_1214));  // basic_mux_2_1
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_1272 = make_Tuple_1268(tmp_1165, tmp_1267);  // make_Tuple
    return tmp_1272;
}
ap_uint<31> Tuple_get_item_0_1274(std::tuple<ap_uint<31>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<31> tmp_1276 = ap_uint<31>(std::get<0>(arg_0_1275));  // basic_get_item_0
    return tmp_1276;
}
ap_uint<10> Tuple_get_item_1_1278(std::tuple<ap_uint<31>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1280 = ap_uint<10>(std::get<1>(arg_0_1279));  // basic_get_item_1
    return tmp_1280;
}
ap_uint<1> q_is_zero_1286(ap_uint<10> arg_0) {  // q_is_zero
    const ap_uint<1> tmp_1288 = ap_uint<1>((arg_0_1287 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_1289 = ap_uint<1>((~tmp_1288));  // basic_invert
    return tmp_1289;
}
ap_uint<1> q_sign_bit_1291(ap_uint<10> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1293 = ap_uint<1>(((arg_0_1292 >> 9) & ap_uint<1>(1)));  // basic_select
    return tmp_1293;
}
ap_uint<1> q_sign_bit_1298(ap_uint<10> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_1300 = ap_uint<1>(((arg_0_1299 >> 9) & ap_uint<1>(1)));  // basic_select
    return tmp_1300;
}
ap_uint<10> Copy_1305(ap_uint<10> arg_0) {  // Copy
    return arg_0_1306;
}
ap_uint<10> Copy_1311(ap_uint<10> arg_0) {  // Copy
    return arg_0_1312;
}
ap_uint<10> Copy_1315(ap_uint<10> arg_0) {  // Copy
    return arg_0_1316;
}
ap_uint<10> Copy_1319(ap_uint<10> arg_0) {  // Copy
    return arg_0_1320;
}
ap_uint<10> Copy_1323(ap_uint<10> arg_0) {  // Copy
    return arg_0_1324;
}
ap_uint<10> Copy_1327(ap_uint<10> arg_0) {  // Copy
    return arg_0_1328;
}
ap_uint<10> q_neg_1308(ap_uint<10> arg_0) {  // q_neg
    const ap_uint<1> tmp_1310 = ap_uint<1>((arg_0_1309 == 512));  // _q_is_min_val
    const ap_uint<10> tmp_1313 = Copy_1311(arg_0_1309);  // Copy
    const ap_uint<10> tmp_1314 = ap_uint<10>((~arg_0_1309));  // basic_invert
    const ap_uint<10> tmp_1317 = Copy_1315(arg_0_1309);  // Copy
    const ap_uint<10> tmp_1318 = ap_uint<10>((tmp_1314 + ap_uint<1>(1)));  // basic_add
    const ap_uint<10> tmp_1321 = Copy_1319(arg_0_1309);  // Copy
    const ap_uint<10> tmp_1322 = ap_uint<10>((arg_0_1309 ^ arg_0_1309));  // basic_xor
    const ap_uint<10> tmp_1325 = Copy_1323(arg_0_1309);  // Copy
    const ap_uint<10> tmp_1326 = ap_uint<10>((~tmp_1322));  // basic_invert
    const ap_uint<10> tmp_1329 = Copy_1327(arg_0_1309);  // Copy
    const ap_uint<10> tmp_1330 = ap_uint<10>((tmp_1310 ? tmp_1326 : tmp_1318));  // basic_mux_2_1
    return tmp_1330;
}
ap_uint<10> Copy_1332(ap_uint<10> arg_0) {  // Copy
    return arg_0_1333;
}
ap_uint<10> q_add_sign_1302(ap_uint<10> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<10> tmp_1307 = Copy_1305(arg_0_1303);  // Copy
    const ap_uint<10> tmp_1331 = q_neg_1308(arg_0_1303);  // q_neg
    const ap_uint<10> tmp_1334 = Copy_1332(arg_0_1303);  // Copy
    const ap_uint<10> tmp_1335 = ap_uint<10>((arg_1_1304 ? tmp_1331 : tmp_1307));  // basic_mux_2_1
    return tmp_1335;
}
ap_uint<10> q_abs_1296(ap_uint<10> arg_0) {  // q_abs
    const ap_uint<1> tmp_1301 = q_sign_bit_1298(arg_0_1297);  // q_sign_bit
    const ap_uint<10> tmp_1336 = q_add_sign_1302(arg_0_1297, tmp_1301);  // q_add_sign
    return tmp_1336;
}
ap_uint<9> q_to_uq_1338(ap_uint<10> arg_0) {  // q_to_uq
    const ap_uint<9> tmp_1340 = ap_uint<9>(arg_0_1339);  // basic_identity
    return tmp_1340;
}
std::tuple<ap_uint<10>, ap_uint<10>> make_Tuple_1350(ap_uint<10> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1353 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(arg_0_1351, arg_1_1352));  // basic_tuple_maker_2
    return tmp_1353;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_1345(ap_uint<1> arg_0, ap_uint<9> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_1348 = ap_uint<10>((arg_0_1346 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1349 = ap_uint<10>((arg_1_1347 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1354 = make_Tuple_1350(tmp_1348, tmp_1349);  // make_Tuple
    return tmp_1354;
}
ap_uint<10> Tuple_get_item_0_1356(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<10> tmp_1358 = ap_uint<10>(std::get<0>(arg_0_1357));  // basic_get_item_0
    return tmp_1358;
}
ap_uint<10> Tuple_get_item_1_1360(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1362 = ap_uint<10>(std::get<1>(arg_0_1361));  // basic_get_item_1
    return tmp_1362;
}
ap_uint<10> Copy_1364(ap_uint<10> arg_0) {  // Copy
    return arg_0_1365;
}
ap_uint<10> uq_add_1342(ap_uint<1> arg_0, ap_uint<9> arg_1) {  // uq_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1355 = uq_aligner_1345(arg_0_1343, arg_1_1344);  // uq_aligner
    const ap_uint<10> tmp_1359 = Tuple_get_item_0_1356(tmp_1355);  // Tuple_get_item_0
    const ap_uint<10> tmp_1363 = Tuple_get_item_1_1360(tmp_1355);  // Tuple_get_item_1
    const ap_uint<10> tmp_1366 = Copy_1364(tmp_1359);  // Copy
    const ap_uint<10> tmp_1367 = ap_uint<10>((tmp_1359 + tmp_1363));  // basic_add
    return tmp_1367;
}
ap_uint<10> Copy_1369(ap_uint<10> arg_0) {  // Copy
    return arg_0_1370;
}
ap_uint<41> Copy_1376(ap_uint<41> arg_0) {  // Copy
    return arg_0_1377;
}
ap_uint<41> uq_rshift_1373(ap_uint<41> arg_0, ap_uint<10> arg_1) {  // uq_rshift
    const ap_uint<41> tmp_1378 = Copy_1376(arg_0_1374);  // Copy
    const ap_uint<41> tmp_1379 = ap_uint<41>((arg_0_1374 >> arg_1_1375));  // basic_rshift
    return tmp_1379;
}
ap_uint<9> Copy_1381(ap_uint<9> arg_0) {  // Copy
    return arg_0_1382;
}
std::tuple<ap_uint<41>, ap_uint<9>> make_Tuple_1385(ap_uint<41> arg_0, ap_uint<9> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_1388 = std::tuple<ap_uint<41>, ap_uint<9>>(std::make_tuple(arg_0_1386, arg_1_1387));  // basic_tuple_maker_2
    return tmp_1388;
}
std::tuple<ap_uint<41>, ap_uint<9>> fp32_classify_1282(ap_uint<31> arg_0, ap_uint<10> arg_1) {  // fp32_classify
    const ap_uint<41> tmp_1285 = ap_uint<41>((arg_0_1283 << ap_uint<4>(10)));  // basic_lshift
    const ap_uint<1> tmp_1290 = q_is_zero_1286(arg_1_1284);  // q_is_zero
    const ap_uint<1> tmp_1294 = q_sign_bit_1291(arg_1_1284);  // q_sign_bit
    const ap_uint<1> tmp_1295 = ap_uint<1>((tmp_1290 | tmp_1294));  // basic_or
    const ap_uint<10> tmp_1337 = q_abs_1296(arg_1_1284);  // q_abs
    const ap_uint<9> tmp_1341 = q_to_uq_1338(tmp_1337);  // q_to_uq
    const ap_uint<10> tmp_1368 = uq_add_1342(ap_uint<1>(1), tmp_1341);  // uq_add
    const ap_uint<10> tmp_1371 = Copy_1369(tmp_1368);  // Copy
    const ap_uint<10> tmp_1372 = ap_uint<10>((tmp_1295 ? tmp_1368 : ap_uint<1>(0)));  // basic_mux_2_1
    const ap_uint<41> tmp_1380 = uq_rshift_1373(tmp_1285, tmp_1372);  // uq_rshift
    const ap_uint<9> tmp_1383 = Copy_1381(tmp_1341);  // Copy
    const ap_uint<9> tmp_1384 = ap_uint<9>((tmp_1295 ? ap_uint<1>(0) : tmp_1341));  // basic_mux_2_1
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_1389 = make_Tuple_1385(tmp_1380, tmp_1384);  // make_Tuple
    return tmp_1389;
}
ap_uint<41> Tuple_get_item_0_1391(std::tuple<ap_uint<41>, ap_uint<9>> arg_0) {  // Tuple_get_item_0
    const ap_uint<41> tmp_1393 = ap_uint<41>(std::get<0>(arg_0_1392));  // basic_get_item_0
    return tmp_1393;
}
ap_uint<40> uq_select_1397(ap_uint<41> arg_0) {  // uq_select
    const ap_uint<40> tmp_1399 = ap_uint<40>(((arg_0_1398 >> 0) & ap_uint<40>(1099511627775)));  // basic_select
    return tmp_1399;
}
ap_uint<40> drop_implicit_bit_1395(ap_uint<41> arg_0) {  // drop_implicit_bit
    const ap_uint<40> tmp_1400 = uq_select_1397(arg_0_1396);  // uq_select
    return tmp_1400;
}
ap_uint<9> Tuple_get_item_1_1402(std::tuple<ap_uint<41>, ap_uint<9>> arg_0) {  // Tuple_get_item_1
    const ap_uint<9> tmp_1404 = ap_uint<9>(std::get<1>(arg_0_1403));  // basic_get_item_1
    return tmp_1404;
}
ap_uint<1> uq_is_zero_1409(ap_uint<9> arg_0) {  // uq_is_zero
    const ap_uint<1> tmp_1411 = ap_uint<1>((arg_0_1410 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_1412 = ap_uint<1>((~tmp_1411));  // basic_invert
    return tmp_1412;
}
ap_uint<23> uq_resize_1414(ap_uint<40> arg_0) {  // uq_resize
    const ap_uint<23> tmp_1416 = ap_uint<23>((arg_0_1415 >> ap_uint<5>(17)));  // basic_rshift
    return tmp_1416;
}
ap_uint<1> uq_select_1420(ap_uint<40> arg_0) {  // uq_select
    const ap_uint<1> tmp_1422 = ap_uint<1>(((arg_0_1421 >> 16) & ap_uint<1>(1)));  // basic_select
    return tmp_1422;
}
ap_uint<1> uq_select_1424(ap_uint<40> arg_0) {  // uq_select
    const ap_uint<1> tmp_1426 = ap_uint<1>(((arg_0_1425 >> 15) & ap_uint<1>(1)));  // basic_select
    return tmp_1426;
}
ap_uint<15> uq_select_1428(ap_uint<40> arg_0) {  // uq_select
    const ap_uint<15> tmp_1430 = ap_uint<15>(((arg_0_1429 >> 0) & ap_uint<15>(32767)));  // basic_select
    return tmp_1430;
}
ap_uint<1> Copy_1432(ap_uint<1> arg_0) {  // Copy
    return arg_0_1433;
}
ap_uint<1> uq_select_1437(ap_uint<40> arg_0) {  // uq_select
    const ap_uint<1> tmp_1439 = ap_uint<1>(((arg_0_1438 >> 17) & ap_uint<1>(1)));  // basic_select
    return tmp_1439;
}
ap_uint<23> uq_RNE_IEEE_1418(ap_uint<40> arg_0) {  // uq_RNE_IEEE
    const ap_uint<1> tmp_1423 = uq_select_1420(arg_0_1419);  // uq_select
    const ap_uint<1> tmp_1427 = uq_select_1424(arg_0_1419);  // uq_select
    const ap_uint<15> tmp_1431 = uq_select_1428(arg_0_1419);  // uq_select
    const ap_uint<1> tmp_1434 = Copy_1432(ap_uint<1>(0));  // Copy
    const ap_uint<1> tmp_1435 = ap_uint<1>((tmp_1431 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_1436 = ap_uint<1>((tmp_1427 | tmp_1435));  // basic_or
    const ap_uint<1> tmp_1440 = uq_select_1437(arg_0_1419);  // uq_select
    const ap_uint<1> tmp_1441 = ap_uint<1>((tmp_1436 | tmp_1440));  // basic_or
    const ap_uint<1> tmp_1442 = ap_uint<1>((tmp_1423 & tmp_1441));  // basic_and
    const ap_uint<23> tmp_1443 = ap_uint<23>(tmp_1442);  // basic_identity
    return tmp_1443;
}
std::tuple<ap_uint<24>, ap_uint<24>> make_Tuple_1453(ap_uint<24> arg_0, ap_uint<24> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_1456 = std::tuple<ap_uint<24>, ap_uint<24>>(std::make_tuple(arg_0_1454, arg_1_1455));  // basic_tuple_maker_2
    return tmp_1456;
}
std::tuple<ap_uint<24>, ap_uint<24>> uq_aligner_1448(ap_uint<23> arg_0, ap_uint<23> arg_1) {  // uq_aligner
    const ap_uint<24> tmp_1451 = ap_uint<24>((arg_0_1449 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<24> tmp_1452 = ap_uint<24>((arg_1_1450 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_1457 = make_Tuple_1453(tmp_1451, tmp_1452);  // make_Tuple
    return tmp_1457;
}
ap_uint<24> Tuple_get_item_0_1459(std::tuple<ap_uint<24>, ap_uint<24>> arg_0) {  // Tuple_get_item_0
    const ap_uint<24> tmp_1461 = ap_uint<24>(std::get<0>(arg_0_1460));  // basic_get_item_0
    return tmp_1461;
}
ap_uint<24> Tuple_get_item_1_1463(std::tuple<ap_uint<24>, ap_uint<24>> arg_0) {  // Tuple_get_item_1
    const ap_uint<24> tmp_1465 = ap_uint<24>(std::get<1>(arg_0_1464));  // basic_get_item_1
    return tmp_1465;
}
ap_uint<24> Copy_1467(ap_uint<24> arg_0) {  // Copy
    return arg_0_1468;
}
ap_uint<24> uq_add_1445(ap_uint<23> arg_0, ap_uint<23> arg_1) {  // uq_add
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_1458 = uq_aligner_1448(arg_0_1446, arg_1_1447);  // uq_aligner
    const ap_uint<24> tmp_1462 = Tuple_get_item_0_1459(tmp_1458);  // Tuple_get_item_0
    const ap_uint<24> tmp_1466 = Tuple_get_item_1_1463(tmp_1458);  // Tuple_get_item_1
    const ap_uint<24> tmp_1469 = Copy_1467(tmp_1462);  // Copy
    const ap_uint<24> tmp_1470 = ap_uint<24>((tmp_1462 + tmp_1466));  // basic_add
    return tmp_1470;
}
std::tuple<ap_uint<10>, ap_uint<10>> make_Tuple_1481(ap_uint<10> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1484 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(arg_0_1482, arg_1_1483));  // basic_tuple_maker_2
    return tmp_1484;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_1476(ap_uint<9> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_1479 = ap_uint<10>((arg_0_1477 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1480 = ap_uint<10>((arg_1_1478 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1485 = make_Tuple_1481(tmp_1479, tmp_1480);  // make_Tuple
    return tmp_1485;
}
ap_uint<10> Tuple_get_item_0_1487(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<10> tmp_1489 = ap_uint<10>(std::get<0>(arg_0_1488));  // basic_get_item_0
    return tmp_1489;
}
ap_uint<10> Tuple_get_item_1_1491(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1493 = ap_uint<10>(std::get<1>(arg_0_1492));  // basic_get_item_1
    return tmp_1493;
}
ap_uint<10> Copy_1495(ap_uint<10> arg_0) {  // Copy
    return arg_0_1496;
}
ap_uint<10> uq_add_1473(ap_uint<9> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1486 = uq_aligner_1476(arg_0_1474, arg_1_1475);  // uq_aligner
    const ap_uint<10> tmp_1490 = Tuple_get_item_0_1487(tmp_1486);  // Tuple_get_item_0
    const ap_uint<10> tmp_1494 = Tuple_get_item_1_1491(tmp_1486);  // Tuple_get_item_1
    const ap_uint<10> tmp_1497 = Copy_1495(tmp_1490);  // Copy
    const ap_uint<10> tmp_1498 = ap_uint<10>((tmp_1490 + tmp_1494));  // basic_add
    return tmp_1498;
}
ap_uint<23> Copy_1503(ap_uint<23> arg_0) {  // Copy
    return arg_0_1504;
}
ap_uint<23> Copy_1507(ap_uint<23> arg_0) {  // Copy
    return arg_0_1508;
}
std::tuple<ap_uint<23>, ap_uint<10>> make_Tuple_1511(ap_uint<23> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_1514 = std::tuple<ap_uint<23>, ap_uint<10>>(std::make_tuple(arg_0_1512, arg_1_1513));  // basic_tuple_maker_2
    return tmp_1514;
}
std::tuple<ap_uint<23>, ap_uint<10>> fp32_round_1406(ap_uint<40> arg_0, ap_uint<9> arg_1) {  // fp32_round
    const ap_uint<1> tmp_1413 = uq_is_zero_1409(arg_1_1408);  // uq_is_zero
    const ap_uint<23> tmp_1417 = uq_resize_1414(arg_0_1407);  // uq_resize
    const ap_uint<23> tmp_1444 = uq_RNE_IEEE_1418(arg_0_1407);  // uq_RNE_IEEE
    const ap_uint<24> tmp_1471 = uq_add_1445(tmp_1417, tmp_1444);  // uq_add
    const ap_uint<1> tmp_1472 = ap_uint<1>(((tmp_1471 >> 23) & ap_uint<1>(1)));  // basic_select
    const ap_uint<10> tmp_1499 = uq_add_1473(arg_1_1408, tmp_1472);  // uq_add
    const ap_uint<1> tmp_1500 = ap_uint<1>((tmp_1499 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_1501 = ap_uint<1>((tmp_1413 & tmp_1500));  // basic_and
    const ap_uint<23> tmp_1502 = ap_uint<23>((tmp_1471 >> ap_uint<1>(1)));  // basic_rshift
    const ap_uint<23> tmp_1505 = Copy_1503(tmp_1502);  // Copy
    const ap_uint<23> tmp_1506 = ap_uint<23>((tmp_1472 ? tmp_1502 : tmp_1471));  // basic_mux_2_1
    const ap_uint<23> tmp_1509 = Copy_1507(tmp_1506);  // Copy
    const ap_uint<23> tmp_1510 = ap_uint<23>((tmp_1501 ? ap_uint<1>(0) : tmp_1506));  // basic_mux_2_1
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_1515 = make_Tuple_1511(tmp_1510, tmp_1499);  // make_Tuple
    return tmp_1515;
}
ap_uint<23> Tuple_get_item_0_1517(std::tuple<ap_uint<23>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<23> tmp_1519 = ap_uint<23>(std::get<0>(arg_0_1518));  // basic_get_item_0
    return tmp_1519;
}
ap_uint<10> Tuple_get_item_1_1521(std::tuple<ap_uint<23>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1523 = ap_uint<10>(std::get<1>(arg_0_1522));  // basic_get_item_1
    return tmp_1523;
}
std::tuple<ap_uint<10>, ap_uint<10>> make_Tuple_1537(ap_uint<10> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1540 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(arg_0_1538, arg_1_1539));  // basic_tuple_maker_2
    return tmp_1540;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_1532(ap_uint<10> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_1535 = ap_uint<10>((arg_0_1533 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_1536 = ap_uint<10>((arg_1_1534 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1541 = make_Tuple_1537(tmp_1535, tmp_1536);  // make_Tuple
    return tmp_1541;
}
ap_uint<10> Tuple_get_item_0_1543(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<10> tmp_1545 = ap_uint<10>(std::get<0>(arg_0_1544));  // basic_get_item_0
    return tmp_1545;
}
ap_uint<10> Tuple_get_item_1_1547(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_1549 = ap_uint<10>(std::get<1>(arg_0_1548));  // basic_get_item_1
    return tmp_1549;
}
ap_uint<10> Copy_1551(ap_uint<10> arg_0) {  // Copy
    return arg_0_1552;
}
ap_uint<10> uq_min_1529(ap_uint<10> arg_0, ap_uint<8> arg_1) {  // uq_min
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_1542 = uq_aligner_1532(arg_0_1530, arg_1_1531);  // uq_aligner
    const ap_uint<10> tmp_1546 = Tuple_get_item_0_1543(tmp_1542);  // Tuple_get_item_0
    const ap_uint<10> tmp_1550 = Tuple_get_item_1_1547(tmp_1542);  // Tuple_get_item_1
    const ap_uint<10> tmp_1553 = Copy_1551(tmp_1546);  // Copy
    const ap_uint<10> tmp_1554 = ap_uint<10>((tmp_1546 < tmp_1550 ? tmp_1546 : tmp_1550));  // basic_min
    return tmp_1554;
}
ap_uint<23> Copy_1558(ap_uint<23> arg_0) {  // Copy
    return arg_0_1559;
}
ap_uint<23> fraction_to_bits_1562(ap_uint<23> arg_0) {  // fraction_to_bits
    const ap_uint<23> tmp_1564 = ap_uint<23>(arg_0_1563);  // basic_identity
    return tmp_1564;
}
ap_uint<1> uq_is_zero_1566(ap_uint<31> arg_0) {  // uq_is_zero
    const ap_uint<1> tmp_1568 = ap_uint<1>((arg_0_1567 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_1569 = ap_uint<1>((~tmp_1568));  // basic_invert
    return tmp_1569;
}
ap_uint<8> Copy_1571(ap_uint<8> arg_0) {  // Copy
    return arg_0_1572;
}
std::tuple<ap_uint<23>, ap_uint<8>> make_Tuple_1575(ap_uint<23> arg_0, ap_uint<8> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_1578 = std::tuple<ap_uint<23>, ap_uint<8>>(std::make_tuple(arg_0_1576, arg_1_1577));  // basic_tuple_maker_2
    return tmp_1578;
}
std::tuple<ap_uint<23>, ap_uint<8>> fp32_encodings_1525(ap_uint<23> arg_0, ap_uint<10> arg_1, ap_uint<31> arg_2) {  // fp32_encodings
    const ap_uint<10> tmp_1555 = uq_min_1529(arg_1_1527, ap_uint<8>(255));  // uq_min
    const ap_uint<8> tmp_1556 = ap_uint<8>(tmp_1555);  // basic_identity
    const ap_uint<1> tmp_1557 = ap_uint<1>((tmp_1556 == ap_uint<8>(255)));  // basic_and_reduce
    const ap_uint<23> tmp_1560 = Copy_1558(arg_0_1526);  // Copy
    const ap_uint<23> tmp_1561 = ap_uint<23>((tmp_1557 ? ap_uint<1>(0) : arg_0_1526));  // basic_mux_2_1
    const ap_uint<23> tmp_1565 = fraction_to_bits_1562(tmp_1561);  // fraction_to_bits
    const ap_uint<1> tmp_1570 = uq_is_zero_1566(arg_2_1528);  // uq_is_zero
    const ap_uint<8> tmp_1573 = Copy_1571(tmp_1556);  // Copy
    const ap_uint<8> tmp_1574 = ap_uint<8>((tmp_1570 ? ap_uint<1>(0) : tmp_1556));  // basic_mux_2_1
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_1579 = make_Tuple_1575(tmp_1565, tmp_1574);  // make_Tuple
    return tmp_1579;
}
ap_uint<8> Tuple_get_item_1_1581(std::tuple<ap_uint<23>, ap_uint<8>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_1583 = ap_uint<8>(std::get<1>(arg_0_1582));  // basic_get_item_1
    return tmp_1583;
}
ap_uint<23> Tuple_get_item_0_1585(std::tuple<ap_uint<23>, ap_uint<8>> arg_0) {  // Tuple_get_item_0
    const ap_uint<23> tmp_1587 = ap_uint<23>(std::get<0>(arg_0_1586));  // basic_get_item_0
    return tmp_1587;
}
ap_uint<32> fp32_pack_1589(ap_uint<1> arg_0, ap_uint<8> arg_1, ap_uint<23> arg_2) {  // fp32_pack
    const ap_uint<32> tmp_1593 = ap_uint<32>(((arg_0_1590 << 31) | (arg_1_1591 << 23) | arg_2_1592));  // float32_alloc
    return tmp_1593;
}
ap_uint<32> encode_Float32_378(ap_uint<32> arg_0, ap_uint<9> arg_1) {  // encode_Float32
    const ap_uint<1> tmp_384 = q_sign_bit_381(arg_0_379);  // q_sign_bit
    const ap_uint<32> tmp_426 = q_abs_385(arg_0_379);  // q_abs
    const ap_uint<31> tmp_430 = q_to_uq_427(tmp_426);  // q_to_uq
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_1273 = fp32_normalize_431(tmp_430, arg_1_380);  // fp32_normalize
    const ap_uint<31> tmp_1277 = Tuple_get_item_0_1274(tmp_1273);  // Tuple_get_item_0
    const ap_uint<10> tmp_1281 = Tuple_get_item_1_1278(tmp_1273);  // Tuple_get_item_1
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_1390 = fp32_classify_1282(tmp_1277, tmp_1281);  // fp32_classify
    const ap_uint<41> tmp_1394 = Tuple_get_item_0_1391(tmp_1390);  // Tuple_get_item_0
    const ap_uint<40> tmp_1401 = drop_implicit_bit_1395(tmp_1394);  // drop_implicit_bit
    const ap_uint<9> tmp_1405 = Tuple_get_item_1_1402(tmp_1390);  // Tuple_get_item_1
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_1516 = fp32_round_1406(tmp_1401, tmp_1405);  // fp32_round
    const ap_uint<23> tmp_1520 = Tuple_get_item_0_1517(tmp_1516);  // Tuple_get_item_0
    const ap_uint<10> tmp_1524 = Tuple_get_item_1_1521(tmp_1516);  // Tuple_get_item_1
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_1580 = fp32_encodings_1525(tmp_1520, tmp_1524, tmp_430);  // fp32_encodings
    const ap_uint<8> tmp_1584 = Tuple_get_item_1_1581(tmp_1580);  // Tuple_get_item_1
    const ap_uint<23> tmp_1588 = Tuple_get_item_0_1585(tmp_1580);  // Tuple_get_item_0
    const ap_uint<32> tmp_1594 = fp32_pack_1589(tmp_384, tmp_1584, tmp_1588);  // fp32_pack
    return tmp_1594;
}
ap_uint<32> main(ap_uint<32> arg_0, ap_uint<32> arg_1) {  // FP32_IEEE_adder
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_13 = fp32_unpack_2(arg_0_0);  // fp32_unpack
    const ap_uint<23> tmp_17 = Tuple_get_item_2_14(tmp_13);  // Tuple_get_item_2
    const ap_uint<24> tmp_21 = add_implicit_bit_18(tmp_17);  // add_implicit_bit
    const ap_uint<30> tmp_25 = uq_resize_22(tmp_21);  // uq_resize
    const ap_uint<8> tmp_29 = Tuple_get_item_1_26(tmp_13);  // Tuple_get_item_1
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_41 = fp32_unpack_30(arg_1_1);  // fp32_unpack
    const ap_uint<8> tmp_45 = Tuple_get_item_1_42(tmp_41);  // Tuple_get_item_1
    const ap_uint<8> tmp_72 = uq_max_46(tmp_29, tmp_45);  // uq_max
    const ap_uint<9> tmp_99 = uq_sub_73(tmp_72, tmp_29);  // uq_sub
    const ap_uint<30> tmp_107 = uq_rshift_100(tmp_25, tmp_99);  // uq_rshift
    const ap_uint<31> tmp_139 = uq_to_q_108(tmp_107);  // uq_to_q
    const ap_uint<1> tmp_143 = Tuple_get_item_0_140(tmp_13);  // Tuple_get_item_0
    const ap_uint<31> tmp_178 = q_add_sign_144(tmp_139, tmp_143);  // q_add_sign
    const ap_uint<23> tmp_182 = Tuple_get_item_2_179(tmp_41);  // Tuple_get_item_2
    const ap_uint<24> tmp_186 = add_implicit_bit_183(tmp_182);  // add_implicit_bit
    const ap_uint<30> tmp_190 = uq_resize_187(tmp_186);  // uq_resize
    const ap_uint<9> tmp_217 = uq_sub_191(tmp_72, tmp_45);  // uq_sub
    const ap_uint<30> tmp_225 = uq_rshift_218(tmp_190, tmp_217);  // uq_rshift
    const ap_uint<31> tmp_257 = uq_to_q_226(tmp_225);  // uq_to_q
    const ap_uint<1> tmp_261 = Tuple_get_item_0_258(tmp_41);  // Tuple_get_item_0
    const ap_uint<31> tmp_296 = q_add_sign_262(tmp_257, tmp_261);  // q_add_sign
    const ap_uint<32> tmp_345 = q_add_297(tmp_178, tmp_296);  // q_add
    const ap_uint<9> tmp_377 = uq_to_q_346(tmp_72);  // uq_to_q
    const ap_uint<32> tmp_1595 = encode_Float32_378(tmp_345, tmp_377);  // encode_Float32
    return tmp_1595;
}

