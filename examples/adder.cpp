#include <ap_int.h>
#include <tuple>

std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> make_Tuple_4(ap_uint<1> arg_0, ap_uint<8> arg_1, ap_uint<23> arg_2) {  // make_Tuple
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_5 = std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>>(std::make_tuple(arg_0, arg_1, arg_2));  // basic_tuple_maker_3
    return tmp_5;
}
std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> fp32_unpack_0(ap_uint<32> arg_0) {  // fp32_unpack
    const ap_uint<1> tmp_1 = ap_uint<1>(((arg_0 >> 31) & ap_uint<1>(1)));  // _fp32_sign
    const ap_uint<8> tmp_2 = ap_uint<8>(((arg_0 >> 23) & ap_uint<8>(255)));  // _fp32_exponent
    const ap_uint<23> tmp_3 = ap_uint<23>(((arg_0 >> 0) & ap_uint<23>(8388607)));  // _fp32_mantissa
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_6 = make_Tuple_4(tmp_1, tmp_2, tmp_3);  // make_Tuple
    return tmp_6;
}
ap_uint<23> Tuple_get_item_2_8(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_2
    const ap_uint<23> tmp_9 = ap_uint<23>(std::get<2>(arg_0));  // basic_get_item_2
    return tmp_9;
}
ap_uint<24> add_implicit_bit_11(ap_uint<23> arg_0) {  // add_implicit_bit
    const ap_uint<24> tmp_12 = ap_uint<24>(((ap_uint<1>(1) << 23) | arg_0));  // basic_concat
    return tmp_12;
}
ap_uint<30> uq_resize_14(ap_uint<24> arg_0) {  // uq_resize
    const ap_uint<30> tmp_15 = ap_uint<30>((arg_0 << ap_uint<3>(6)));  // basic_lshift
    return tmp_15;
}
ap_uint<8> Tuple_get_item_1_17(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_18 = ap_uint<8>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_18;
}
std::tuple<ap_uint<8>, ap_uint<8>> make_Tuple_26(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_27 = std::tuple<ap_uint<8>, ap_uint<8>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_27;
}
std::tuple<ap_uint<8>, ap_uint<8>> uq_aligner_23(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<8> tmp_24 = ap_uint<8>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_25 = ap_uint<8>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_28 = make_Tuple_26(tmp_24, tmp_25);  // make_Tuple
    return tmp_28;
}
ap_uint<8> Tuple_get_item_0_30(std::tuple<ap_uint<8>, ap_uint<8>> arg_0) {  // Tuple_get_item_0
    const ap_uint<8> tmp_31 = ap_uint<8>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_31;
}
ap_uint<8> Tuple_get_item_1_33(std::tuple<ap_uint<8>, ap_uint<8>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_34 = ap_uint<8>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_34;
}
ap_uint<8> Copy_36(ap_uint<8> arg_0) {  // Copy
    return arg_0;
}
ap_uint<8> uq_max_22(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_max
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_29 = uq_aligner_23(arg_0, arg_1);  // uq_aligner
    const ap_uint<8> tmp_32 = Tuple_get_item_0_30(tmp_29);  // Tuple_get_item_0
    const ap_uint<8> tmp_35 = Tuple_get_item_1_33(tmp_29);  // Tuple_get_item_1
    const ap_uint<8> tmp_37 = Copy_36(tmp_32);  // Copy
    const ap_uint<8> tmp_38 = ap_uint<8>((tmp_32 > tmp_35 ? tmp_32 : tmp_35));  // basic_max
    return tmp_38;
}
std::tuple<ap_uint<9>, ap_uint<9>> make_Tuple_44(ap_uint<9> arg_0, ap_uint<9> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_45 = std::tuple<ap_uint<9>, ap_uint<9>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_45;
}
std::tuple<ap_uint<9>, ap_uint<9>> uq_aligner_41(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<9> tmp_42 = ap_uint<9>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<9> tmp_43 = ap_uint<9>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_46 = make_Tuple_44(tmp_42, tmp_43);  // make_Tuple
    return tmp_46;
}
ap_uint<9> Tuple_get_item_0_48(std::tuple<ap_uint<9>, ap_uint<9>> arg_0) {  // Tuple_get_item_0
    const ap_uint<9> tmp_49 = ap_uint<9>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_49;
}
ap_uint<9> Tuple_get_item_1_51(std::tuple<ap_uint<9>, ap_uint<9>> arg_0) {  // Tuple_get_item_1
    const ap_uint<9> tmp_52 = ap_uint<9>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_52;
}
ap_uint<9> Copy_54(ap_uint<9> arg_0) {  // Copy
    return arg_0;
}
ap_uint<9> uq_sub_40(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_sub
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_47 = uq_aligner_41(arg_0, arg_1);  // uq_aligner
    const ap_uint<9> tmp_50 = Tuple_get_item_0_48(tmp_47);  // Tuple_get_item_0
    const ap_uint<9> tmp_53 = Tuple_get_item_1_51(tmp_47);  // Tuple_get_item_1
    const ap_uint<9> tmp_55 = Copy_54(tmp_50);  // Copy
    const ap_uint<9> tmp_56 = ap_uint<9>((tmp_50 - tmp_53));  // basic_sub
    return tmp_56;
}
ap_uint<30> Copy_59(ap_uint<30> arg_0) {  // Copy
    return arg_0;
}
ap_uint<30> uq_rshift_58(ap_uint<30> arg_0, ap_uint<9> arg_1) {  // uq_rshift
    const ap_uint<30> tmp_60 = Copy_59(arg_0);  // Copy
    const ap_uint<30> tmp_61 = ap_uint<30>((arg_0 >> arg_1));  // basic_rshift
    return tmp_61;
}
std::tuple<ap_uint<2>, ap_uint<2>> make_Tuple_68(ap_uint<2> arg_0, ap_uint<2> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_69 = std::tuple<ap_uint<2>, ap_uint<2>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_69;
}
std::tuple<ap_uint<2>, ap_uint<2>> uq_aligner_65(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<2> tmp_66 = ap_uint<2>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<2> tmp_67 = ap_uint<2>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_70 = make_Tuple_68(tmp_66, tmp_67);  // make_Tuple
    return tmp_70;
}
ap_uint<2> Tuple_get_item_0_72(std::tuple<ap_uint<2>, ap_uint<2>> arg_0) {  // Tuple_get_item_0
    const ap_uint<2> tmp_73 = ap_uint<2>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_73;
}
ap_uint<2> Tuple_get_item_1_75(std::tuple<ap_uint<2>, ap_uint<2>> arg_0) {  // Tuple_get_item_1
    const ap_uint<2> tmp_76 = ap_uint<2>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_76;
}
ap_uint<2> Copy_78(ap_uint<2> arg_0) {  // Copy
    return arg_0;
}
ap_uint<2> uq_add_64(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_71 = uq_aligner_65(arg_0, arg_1);  // uq_aligner
    const ap_uint<2> tmp_74 = Tuple_get_item_0_72(tmp_71);  // Tuple_get_item_0
    const ap_uint<2> tmp_77 = Tuple_get_item_1_75(tmp_71);  // Tuple_get_item_1
    const ap_uint<2> tmp_79 = Copy_78(tmp_74);  // Copy
    const ap_uint<2> tmp_80 = ap_uint<2>((tmp_74 + tmp_77));  // basic_add
    return tmp_80;
}
ap_uint<31> uq_to_q_63(ap_uint<30> arg_0) {  // uq_to_q
    const ap_uint<2> tmp_81 = uq_add_64(ap_uint<1>(1), ap_uint<1>(1));  // uq_add
    const ap_uint<31> tmp_82 = ap_uint<31>(0);  // q_alloc
    const ap_uint<31> tmp_83 = ap_uint<31>(arg_0);  // basic_identity
    return tmp_83;
}
ap_uint<1> Tuple_get_item_0_85(std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> arg_0) {  // Tuple_get_item_0
    const ap_uint<1> tmp_86 = ap_uint<1>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_86;
}
ap_uint<31> Copy_89(ap_uint<31> arg_0) {  // Copy
    return arg_0;
}
ap_uint<31> q_neg_91(ap_uint<31> arg_0) {  // q_neg
    const ap_uint<1> tmp_92 = ap_uint<1>((arg_0 == 1073741824));  // _q_is_min_val
    const ap_uint<31> tmp_93 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_94 = ap_uint<31>((~arg_0));  // basic_invert
    const ap_uint<31> tmp_95 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_96 = ap_uint<31>((tmp_94 + ap_uint<1>(1)));  // basic_add
    const ap_uint<31> tmp_97 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_98 = ap_uint<31>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<31> tmp_99 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_100 = ap_uint<31>((~tmp_98));  // basic_invert
    const ap_uint<31> tmp_101 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_102 = ap_uint<31>((tmp_92 ? tmp_100 : tmp_96));  // basic_mux_2_1
    return tmp_102;
}
ap_uint<31> q_add_sign_88(ap_uint<31> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<31> tmp_90 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_103 = q_neg_91(arg_0);  // q_neg
    const ap_uint<31> tmp_104 = Copy_89(arg_0);  // Copy
    const ap_uint<31> tmp_105 = ap_uint<31>((arg_1 ? tmp_103 : tmp_90));  // basic_mux_2_1
    return tmp_105;
}
ap_uint<1> q_sign_bit_119(ap_uint<31> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_120 = ap_uint<1>(((arg_0 >> 30) & ap_uint<1>(1)));  // basic_select
    return tmp_120;
}
ap_uint<32> q_sign_extend_118(ap_uint<31> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_121 = q_sign_bit_119(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_122 = ap_uint<2>((tmp_121 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_123 = ap_uint<1>((tmp_122 - tmp_121));  // basic_sub
    const ap_uint<32> tmp_124 = ap_uint<32>(0);  // q_alloc
    const ap_uint<32> tmp_125 = ap_uint<32>(((tmp_123 << 31) | arg_0));  // basic_concat
    return tmp_125;
}
std::tuple<ap_uint<32>, ap_uint<32>> make_Tuple_129(ap_uint<32> arg_0, ap_uint<32> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_130 = std::tuple<ap_uint<32>, ap_uint<32>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_130;
}
std::tuple<ap_uint<32>, ap_uint<32>> q_aligner_116(ap_uint<31> arg_0, ap_uint<31> arg_1) {  // q_aligner
    const ap_uint<31> tmp_117 = ap_uint<31>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<32> tmp_126 = q_sign_extend_118(tmp_117);  // q_sign_extend
    const ap_uint<31> tmp_127 = ap_uint<31>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<32> tmp_128 = q_sign_extend_118(tmp_127);  // q_sign_extend
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_131 = make_Tuple_129(tmp_126, tmp_128);  // make_Tuple
    return tmp_131;
}
ap_uint<32> Tuple_get_item_0_133(std::tuple<ap_uint<32>, ap_uint<32>> arg_0) {  // Tuple_get_item_0
    const ap_uint<32> tmp_134 = ap_uint<32>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_134;
}
ap_uint<32> Tuple_get_item_1_136(std::tuple<ap_uint<32>, ap_uint<32>> arg_0) {  // Tuple_get_item_1
    const ap_uint<32> tmp_137 = ap_uint<32>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_137;
}
ap_uint<32> Copy_139(ap_uint<32> arg_0) {  // Copy
    return arg_0;
}
ap_uint<32> q_add_115(ap_uint<31> arg_0, ap_uint<31> arg_1) {  // q_add
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_132 = q_aligner_116(arg_0, arg_1);  // q_aligner
    const ap_uint<32> tmp_135 = Tuple_get_item_0_133(tmp_132);  // Tuple_get_item_0
    const ap_uint<32> tmp_138 = Tuple_get_item_1_136(tmp_132);  // Tuple_get_item_1
    const ap_uint<32> tmp_140 = Copy_139(tmp_135);  // Copy
    const ap_uint<32> tmp_141 = ap_uint<32>((tmp_135 + tmp_138));  // basic_add
    return tmp_141;
}
std::tuple<ap_uint<5>, ap_uint<5>> make_Tuple_148(ap_uint<5> arg_0, ap_uint<5> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_149 = std::tuple<ap_uint<5>, ap_uint<5>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_149;
}
std::tuple<ap_uint<5>, ap_uint<5>> uq_aligner_145(ap_uint<4> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<5> tmp_146 = ap_uint<5>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<5> tmp_147 = ap_uint<5>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_150 = make_Tuple_148(tmp_146, tmp_147);  // make_Tuple
    return tmp_150;
}
ap_uint<5> Tuple_get_item_0_152(std::tuple<ap_uint<5>, ap_uint<5>> arg_0) {  // Tuple_get_item_0
    const ap_uint<5> tmp_153 = ap_uint<5>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_153;
}
ap_uint<5> Tuple_get_item_1_155(std::tuple<ap_uint<5>, ap_uint<5>> arg_0) {  // Tuple_get_item_1
    const ap_uint<5> tmp_156 = ap_uint<5>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_156;
}
ap_uint<5> Copy_158(ap_uint<5> arg_0) {  // Copy
    return arg_0;
}
ap_uint<5> uq_add_144(ap_uint<4> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_151 = uq_aligner_145(arg_0, arg_1);  // uq_aligner
    const ap_uint<5> tmp_154 = Tuple_get_item_0_152(tmp_151);  // Tuple_get_item_0
    const ap_uint<5> tmp_157 = Tuple_get_item_1_155(tmp_151);  // Tuple_get_item_1
    const ap_uint<5> tmp_159 = Copy_158(tmp_154);  // Copy
    const ap_uint<5> tmp_160 = ap_uint<5>((tmp_154 + tmp_157));  // basic_add
    return tmp_160;
}
ap_uint<9> uq_to_q_143(ap_uint<8> arg_0) {  // uq_to_q
    const ap_uint<5> tmp_161 = uq_add_144(ap_uint<4>(8), ap_uint<1>(1));  // uq_add
    const ap_uint<9> tmp_162 = ap_uint<9>(0);  // q_alloc
    const ap_uint<9> tmp_163 = ap_uint<9>(arg_0);  // basic_identity
    return tmp_163;
}
ap_uint<1> q_sign_bit_166(ap_uint<32> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_167 = ap_uint<1>(((arg_0 >> 31) & ap_uint<1>(1)));  // basic_select
    return tmp_167;
}
ap_uint<32> q_neg_173(ap_uint<32> arg_0) {  // q_neg
    const ap_uint<1> tmp_174 = ap_uint<1>((arg_0 == 2147483648));  // _q_is_min_val
    const ap_uint<32> tmp_175 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_176 = ap_uint<32>((~arg_0));  // basic_invert
    const ap_uint<32> tmp_177 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_178 = ap_uint<32>((tmp_176 + ap_uint<1>(1)));  // basic_add
    const ap_uint<32> tmp_179 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_180 = ap_uint<32>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<32> tmp_181 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_182 = ap_uint<32>((~tmp_180));  // basic_invert
    const ap_uint<32> tmp_183 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_184 = ap_uint<32>((tmp_174 ? tmp_182 : tmp_178));  // basic_mux_2_1
    return tmp_184;
}
ap_uint<32> q_add_sign_171(ap_uint<32> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<32> tmp_172 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_185 = q_neg_173(arg_0);  // q_neg
    const ap_uint<32> tmp_186 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_187 = ap_uint<32>((arg_1 ? tmp_185 : tmp_172));  // basic_mux_2_1
    return tmp_187;
}
ap_uint<32> q_abs_169(ap_uint<32> arg_0) {  // q_abs
    const ap_uint<1> tmp_170 = q_sign_bit_166(arg_0);  // q_sign_bit
    const ap_uint<32> tmp_188 = q_add_sign_171(arg_0, tmp_170);  // q_add_sign
    return tmp_188;
}
ap_uint<31> q_to_uq_190(ap_uint<32> arg_0) {  // q_to_uq
    const ap_uint<31> tmp_191 = ap_uint<31>(arg_0);  // basic_identity
    return tmp_191;
}
ap_uint<1> uq_select_195(ap_uint<31> arg_0) {  // uq_select
    const ap_uint<1> tmp_196 = ap_uint<1>(((arg_0 >> 30) & ap_uint<1>(1)));  // basic_select
    return tmp_196;
}
ap_uint<1> Copy_198(ap_uint<1> arg_0) {  // Copy
    return arg_0;
}
ap_uint<5> lzc_194(ap_uint<31> arg_0) {  // lzc
    const ap_uint<1> tmp_197 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_199 = Copy_198(tmp_197);  // Copy
    const ap_uint<1> tmp_200 = ap_uint<1>((~tmp_197));  // basic_invert
    const ap_uint<1> tmp_201 = Copy_198(ap_uint<1>(1));  // Copy
    const ap_uint<1> tmp_202 = ap_uint<1>((ap_uint<1>(1) & tmp_200));  // basic_and
    const ap_uint<5> tmp_203 = Copy_158(ap_uint<5>(0));  // Copy
    const ap_uint<5> tmp_204 = ap_uint<5>((ap_uint<5>(0) + tmp_202));  // basic_add
    const ap_uint<1> tmp_205 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_206 = Copy_198(tmp_205);  // Copy
    const ap_uint<1> tmp_207 = ap_uint<1>((~tmp_205));  // basic_invert
    const ap_uint<1> tmp_208 = Copy_198(tmp_202);  // Copy
    const ap_uint<1> tmp_209 = ap_uint<1>((tmp_202 & tmp_207));  // basic_and
    const ap_uint<5> tmp_210 = Copy_158(tmp_204);  // Copy
    const ap_uint<5> tmp_211 = ap_uint<5>((tmp_204 + tmp_209));  // basic_add
    const ap_uint<1> tmp_212 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_213 = Copy_198(tmp_212);  // Copy
    const ap_uint<1> tmp_214 = ap_uint<1>((~tmp_212));  // basic_invert
    const ap_uint<1> tmp_215 = Copy_198(tmp_209);  // Copy
    const ap_uint<1> tmp_216 = ap_uint<1>((tmp_209 & tmp_214));  // basic_and
    const ap_uint<5> tmp_217 = Copy_158(tmp_211);  // Copy
    const ap_uint<5> tmp_218 = ap_uint<5>((tmp_211 + tmp_216));  // basic_add
    const ap_uint<1> tmp_219 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_220 = Copy_198(tmp_219);  // Copy
    const ap_uint<1> tmp_221 = ap_uint<1>((~tmp_219));  // basic_invert
    const ap_uint<1> tmp_222 = Copy_198(tmp_216);  // Copy
    const ap_uint<1> tmp_223 = ap_uint<1>((tmp_216 & tmp_221));  // basic_and
    const ap_uint<5> tmp_224 = Copy_158(tmp_218);  // Copy
    const ap_uint<5> tmp_225 = ap_uint<5>((tmp_218 + tmp_223));  // basic_add
    const ap_uint<1> tmp_226 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_227 = Copy_198(tmp_226);  // Copy
    const ap_uint<1> tmp_228 = ap_uint<1>((~tmp_226));  // basic_invert
    const ap_uint<1> tmp_229 = Copy_198(tmp_223);  // Copy
    const ap_uint<1> tmp_230 = ap_uint<1>((tmp_223 & tmp_228));  // basic_and
    const ap_uint<5> tmp_231 = Copy_158(tmp_225);  // Copy
    const ap_uint<5> tmp_232 = ap_uint<5>((tmp_225 + tmp_230));  // basic_add
    const ap_uint<1> tmp_233 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_234 = Copy_198(tmp_233);  // Copy
    const ap_uint<1> tmp_235 = ap_uint<1>((~tmp_233));  // basic_invert
    const ap_uint<1> tmp_236 = Copy_198(tmp_230);  // Copy
    const ap_uint<1> tmp_237 = ap_uint<1>((tmp_230 & tmp_235));  // basic_and
    const ap_uint<5> tmp_238 = Copy_158(tmp_232);  // Copy
    const ap_uint<5> tmp_239 = ap_uint<5>((tmp_232 + tmp_237));  // basic_add
    const ap_uint<1> tmp_240 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_241 = Copy_198(tmp_240);  // Copy
    const ap_uint<1> tmp_242 = ap_uint<1>((~tmp_240));  // basic_invert
    const ap_uint<1> tmp_243 = Copy_198(tmp_237);  // Copy
    const ap_uint<1> tmp_244 = ap_uint<1>((tmp_237 & tmp_242));  // basic_and
    const ap_uint<5> tmp_245 = Copy_158(tmp_239);  // Copy
    const ap_uint<5> tmp_246 = ap_uint<5>((tmp_239 + tmp_244));  // basic_add
    const ap_uint<1> tmp_247 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_248 = Copy_198(tmp_247);  // Copy
    const ap_uint<1> tmp_249 = ap_uint<1>((~tmp_247));  // basic_invert
    const ap_uint<1> tmp_250 = Copy_198(tmp_244);  // Copy
    const ap_uint<1> tmp_251 = ap_uint<1>((tmp_244 & tmp_249));  // basic_and
    const ap_uint<5> tmp_252 = Copy_158(tmp_246);  // Copy
    const ap_uint<5> tmp_253 = ap_uint<5>((tmp_246 + tmp_251));  // basic_add
    const ap_uint<1> tmp_254 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_255 = Copy_198(tmp_254);  // Copy
    const ap_uint<1> tmp_256 = ap_uint<1>((~tmp_254));  // basic_invert
    const ap_uint<1> tmp_257 = Copy_198(tmp_251);  // Copy
    const ap_uint<1> tmp_258 = ap_uint<1>((tmp_251 & tmp_256));  // basic_and
    const ap_uint<5> tmp_259 = Copy_158(tmp_253);  // Copy
    const ap_uint<5> tmp_260 = ap_uint<5>((tmp_253 + tmp_258));  // basic_add
    const ap_uint<1> tmp_261 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_262 = Copy_198(tmp_261);  // Copy
    const ap_uint<1> tmp_263 = ap_uint<1>((~tmp_261));  // basic_invert
    const ap_uint<1> tmp_264 = Copy_198(tmp_258);  // Copy
    const ap_uint<1> tmp_265 = ap_uint<1>((tmp_258 & tmp_263));  // basic_and
    const ap_uint<5> tmp_266 = Copy_158(tmp_260);  // Copy
    const ap_uint<5> tmp_267 = ap_uint<5>((tmp_260 + tmp_265));  // basic_add
    const ap_uint<1> tmp_268 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_269 = Copy_198(tmp_268);  // Copy
    const ap_uint<1> tmp_270 = ap_uint<1>((~tmp_268));  // basic_invert
    const ap_uint<1> tmp_271 = Copy_198(tmp_265);  // Copy
    const ap_uint<1> tmp_272 = ap_uint<1>((tmp_265 & tmp_270));  // basic_and
    const ap_uint<5> tmp_273 = Copy_158(tmp_267);  // Copy
    const ap_uint<5> tmp_274 = ap_uint<5>((tmp_267 + tmp_272));  // basic_add
    const ap_uint<1> tmp_275 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_276 = Copy_198(tmp_275);  // Copy
    const ap_uint<1> tmp_277 = ap_uint<1>((~tmp_275));  // basic_invert
    const ap_uint<1> tmp_278 = Copy_198(tmp_272);  // Copy
    const ap_uint<1> tmp_279 = ap_uint<1>((tmp_272 & tmp_277));  // basic_and
    const ap_uint<5> tmp_280 = Copy_158(tmp_274);  // Copy
    const ap_uint<5> tmp_281 = ap_uint<5>((tmp_274 + tmp_279));  // basic_add
    const ap_uint<1> tmp_282 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_283 = Copy_198(tmp_282);  // Copy
    const ap_uint<1> tmp_284 = ap_uint<1>((~tmp_282));  // basic_invert
    const ap_uint<1> tmp_285 = Copy_198(tmp_279);  // Copy
    const ap_uint<1> tmp_286 = ap_uint<1>((tmp_279 & tmp_284));  // basic_and
    const ap_uint<5> tmp_287 = Copy_158(tmp_281);  // Copy
    const ap_uint<5> tmp_288 = ap_uint<5>((tmp_281 + tmp_286));  // basic_add
    const ap_uint<1> tmp_289 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_290 = Copy_198(tmp_289);  // Copy
    const ap_uint<1> tmp_291 = ap_uint<1>((~tmp_289));  // basic_invert
    const ap_uint<1> tmp_292 = Copy_198(tmp_286);  // Copy
    const ap_uint<1> tmp_293 = ap_uint<1>((tmp_286 & tmp_291));  // basic_and
    const ap_uint<5> tmp_294 = Copy_158(tmp_288);  // Copy
    const ap_uint<5> tmp_295 = ap_uint<5>((tmp_288 + tmp_293));  // basic_add
    const ap_uint<1> tmp_296 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_297 = Copy_198(tmp_296);  // Copy
    const ap_uint<1> tmp_298 = ap_uint<1>((~tmp_296));  // basic_invert
    const ap_uint<1> tmp_299 = Copy_198(tmp_293);  // Copy
    const ap_uint<1> tmp_300 = ap_uint<1>((tmp_293 & tmp_298));  // basic_and
    const ap_uint<5> tmp_301 = Copy_158(tmp_295);  // Copy
    const ap_uint<5> tmp_302 = ap_uint<5>((tmp_295 + tmp_300));  // basic_add
    const ap_uint<1> tmp_303 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_304 = Copy_198(tmp_303);  // Copy
    const ap_uint<1> tmp_305 = ap_uint<1>((~tmp_303));  // basic_invert
    const ap_uint<1> tmp_306 = Copy_198(tmp_300);  // Copy
    const ap_uint<1> tmp_307 = ap_uint<1>((tmp_300 & tmp_305));  // basic_and
    const ap_uint<5> tmp_308 = Copy_158(tmp_302);  // Copy
    const ap_uint<5> tmp_309 = ap_uint<5>((tmp_302 + tmp_307));  // basic_add
    const ap_uint<1> tmp_310 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_311 = Copy_198(tmp_310);  // Copy
    const ap_uint<1> tmp_312 = ap_uint<1>((~tmp_310));  // basic_invert
    const ap_uint<1> tmp_313 = Copy_198(tmp_307);  // Copy
    const ap_uint<1> tmp_314 = ap_uint<1>((tmp_307 & tmp_312));  // basic_and
    const ap_uint<5> tmp_315 = Copy_158(tmp_309);  // Copy
    const ap_uint<5> tmp_316 = ap_uint<5>((tmp_309 + tmp_314));  // basic_add
    const ap_uint<1> tmp_317 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_318 = Copy_198(tmp_317);  // Copy
    const ap_uint<1> tmp_319 = ap_uint<1>((~tmp_317));  // basic_invert
    const ap_uint<1> tmp_320 = Copy_198(tmp_314);  // Copy
    const ap_uint<1> tmp_321 = ap_uint<1>((tmp_314 & tmp_319));  // basic_and
    const ap_uint<5> tmp_322 = Copy_158(tmp_316);  // Copy
    const ap_uint<5> tmp_323 = ap_uint<5>((tmp_316 + tmp_321));  // basic_add
    const ap_uint<1> tmp_324 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_325 = Copy_198(tmp_324);  // Copy
    const ap_uint<1> tmp_326 = ap_uint<1>((~tmp_324));  // basic_invert
    const ap_uint<1> tmp_327 = Copy_198(tmp_321);  // Copy
    const ap_uint<1> tmp_328 = ap_uint<1>((tmp_321 & tmp_326));  // basic_and
    const ap_uint<5> tmp_329 = Copy_158(tmp_323);  // Copy
    const ap_uint<5> tmp_330 = ap_uint<5>((tmp_323 + tmp_328));  // basic_add
    const ap_uint<1> tmp_331 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_332 = Copy_198(tmp_331);  // Copy
    const ap_uint<1> tmp_333 = ap_uint<1>((~tmp_331));  // basic_invert
    const ap_uint<1> tmp_334 = Copy_198(tmp_328);  // Copy
    const ap_uint<1> tmp_335 = ap_uint<1>((tmp_328 & tmp_333));  // basic_and
    const ap_uint<5> tmp_336 = Copy_158(tmp_330);  // Copy
    const ap_uint<5> tmp_337 = ap_uint<5>((tmp_330 + tmp_335));  // basic_add
    const ap_uint<1> tmp_338 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_339 = Copy_198(tmp_338);  // Copy
    const ap_uint<1> tmp_340 = ap_uint<1>((~tmp_338));  // basic_invert
    const ap_uint<1> tmp_341 = Copy_198(tmp_335);  // Copy
    const ap_uint<1> tmp_342 = ap_uint<1>((tmp_335 & tmp_340));  // basic_and
    const ap_uint<5> tmp_343 = Copy_158(tmp_337);  // Copy
    const ap_uint<5> tmp_344 = ap_uint<5>((tmp_337 + tmp_342));  // basic_add
    const ap_uint<1> tmp_345 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_346 = Copy_198(tmp_345);  // Copy
    const ap_uint<1> tmp_347 = ap_uint<1>((~tmp_345));  // basic_invert
    const ap_uint<1> tmp_348 = Copy_198(tmp_342);  // Copy
    const ap_uint<1> tmp_349 = ap_uint<1>((tmp_342 & tmp_347));  // basic_and
    const ap_uint<5> tmp_350 = Copy_158(tmp_344);  // Copy
    const ap_uint<5> tmp_351 = ap_uint<5>((tmp_344 + tmp_349));  // basic_add
    const ap_uint<1> tmp_352 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_353 = Copy_198(tmp_352);  // Copy
    const ap_uint<1> tmp_354 = ap_uint<1>((~tmp_352));  // basic_invert
    const ap_uint<1> tmp_355 = Copy_198(tmp_349);  // Copy
    const ap_uint<1> tmp_356 = ap_uint<1>((tmp_349 & tmp_354));  // basic_and
    const ap_uint<5> tmp_357 = Copy_158(tmp_351);  // Copy
    const ap_uint<5> tmp_358 = ap_uint<5>((tmp_351 + tmp_356));  // basic_add
    const ap_uint<1> tmp_359 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_360 = Copy_198(tmp_359);  // Copy
    const ap_uint<1> tmp_361 = ap_uint<1>((~tmp_359));  // basic_invert
    const ap_uint<1> tmp_362 = Copy_198(tmp_356);  // Copy
    const ap_uint<1> tmp_363 = ap_uint<1>((tmp_356 & tmp_361));  // basic_and
    const ap_uint<5> tmp_364 = Copy_158(tmp_358);  // Copy
    const ap_uint<5> tmp_365 = ap_uint<5>((tmp_358 + tmp_363));  // basic_add
    const ap_uint<1> tmp_366 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_367 = Copy_198(tmp_366);  // Copy
    const ap_uint<1> tmp_368 = ap_uint<1>((~tmp_366));  // basic_invert
    const ap_uint<1> tmp_369 = Copy_198(tmp_363);  // Copy
    const ap_uint<1> tmp_370 = ap_uint<1>((tmp_363 & tmp_368));  // basic_and
    const ap_uint<5> tmp_371 = Copy_158(tmp_365);  // Copy
    const ap_uint<5> tmp_372 = ap_uint<5>((tmp_365 + tmp_370));  // basic_add
    const ap_uint<1> tmp_373 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_374 = Copy_198(tmp_373);  // Copy
    const ap_uint<1> tmp_375 = ap_uint<1>((~tmp_373));  // basic_invert
    const ap_uint<1> tmp_376 = Copy_198(tmp_370);  // Copy
    const ap_uint<1> tmp_377 = ap_uint<1>((tmp_370 & tmp_375));  // basic_and
    const ap_uint<5> tmp_378 = Copy_158(tmp_372);  // Copy
    const ap_uint<5> tmp_379 = ap_uint<5>((tmp_372 + tmp_377));  // basic_add
    const ap_uint<1> tmp_380 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_381 = Copy_198(tmp_380);  // Copy
    const ap_uint<1> tmp_382 = ap_uint<1>((~tmp_380));  // basic_invert
    const ap_uint<1> tmp_383 = Copy_198(tmp_377);  // Copy
    const ap_uint<1> tmp_384 = ap_uint<1>((tmp_377 & tmp_382));  // basic_and
    const ap_uint<5> tmp_385 = Copy_158(tmp_379);  // Copy
    const ap_uint<5> tmp_386 = ap_uint<5>((tmp_379 + tmp_384));  // basic_add
    const ap_uint<1> tmp_387 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_388 = Copy_198(tmp_387);  // Copy
    const ap_uint<1> tmp_389 = ap_uint<1>((~tmp_387));  // basic_invert
    const ap_uint<1> tmp_390 = Copy_198(tmp_384);  // Copy
    const ap_uint<1> tmp_391 = ap_uint<1>((tmp_384 & tmp_389));  // basic_and
    const ap_uint<5> tmp_392 = Copy_158(tmp_386);  // Copy
    const ap_uint<5> tmp_393 = ap_uint<5>((tmp_386 + tmp_391));  // basic_add
    const ap_uint<1> tmp_394 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_395 = Copy_198(tmp_394);  // Copy
    const ap_uint<1> tmp_396 = ap_uint<1>((~tmp_394));  // basic_invert
    const ap_uint<1> tmp_397 = Copy_198(tmp_391);  // Copy
    const ap_uint<1> tmp_398 = ap_uint<1>((tmp_391 & tmp_396));  // basic_and
    const ap_uint<5> tmp_399 = Copy_158(tmp_393);  // Copy
    const ap_uint<5> tmp_400 = ap_uint<5>((tmp_393 + tmp_398));  // basic_add
    const ap_uint<1> tmp_401 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_402 = Copy_198(tmp_401);  // Copy
    const ap_uint<1> tmp_403 = ap_uint<1>((~tmp_401));  // basic_invert
    const ap_uint<1> tmp_404 = Copy_198(tmp_398);  // Copy
    const ap_uint<1> tmp_405 = ap_uint<1>((tmp_398 & tmp_403));  // basic_and
    const ap_uint<5> tmp_406 = Copy_158(tmp_400);  // Copy
    const ap_uint<5> tmp_407 = ap_uint<5>((tmp_400 + tmp_405));  // basic_add
    const ap_uint<1> tmp_408 = uq_select_195(arg_0);  // uq_select
    const ap_uint<1> tmp_409 = Copy_198(tmp_408);  // Copy
    const ap_uint<1> tmp_410 = ap_uint<1>((~tmp_408));  // basic_invert
    const ap_uint<1> tmp_411 = Copy_198(tmp_405);  // Copy
    const ap_uint<1> tmp_412 = ap_uint<1>((tmp_405 & tmp_410));  // basic_and
    const ap_uint<5> tmp_413 = Copy_158(tmp_407);  // Copy
    const ap_uint<5> tmp_414 = ap_uint<5>((tmp_407 + tmp_412));  // basic_add
    return tmp_414;
}
std::tuple<ap_uint<4>, ap_uint<4>> make_Tuple_421(ap_uint<4> arg_0, ap_uint<4> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_422 = std::tuple<ap_uint<4>, ap_uint<4>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_422;
}
std::tuple<ap_uint<4>, ap_uint<4>> uq_aligner_418(ap_uint<3> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<4> tmp_419 = ap_uint<4>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<4> tmp_420 = ap_uint<4>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_423 = make_Tuple_421(tmp_419, tmp_420);  // make_Tuple
    return tmp_423;
}
ap_uint<4> Tuple_get_item_0_425(std::tuple<ap_uint<4>, ap_uint<4>> arg_0) {  // Tuple_get_item_0
    const ap_uint<4> tmp_426 = ap_uint<4>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_426;
}
ap_uint<4> Tuple_get_item_1_428(std::tuple<ap_uint<4>, ap_uint<4>> arg_0) {  // Tuple_get_item_1
    const ap_uint<4> tmp_429 = ap_uint<4>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_429;
}
ap_uint<4> Copy_431(ap_uint<4> arg_0) {  // Copy
    return arg_0;
}
ap_uint<4> uq_add_417(ap_uint<3> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_424 = uq_aligner_418(arg_0, arg_1);  // uq_aligner
    const ap_uint<4> tmp_427 = Tuple_get_item_0_425(tmp_424);  // Tuple_get_item_0
    const ap_uint<4> tmp_430 = Tuple_get_item_1_428(tmp_424);  // Tuple_get_item_1
    const ap_uint<4> tmp_432 = Copy_431(tmp_427);  // Copy
    const ap_uint<4> tmp_433 = ap_uint<4>((tmp_427 + tmp_430));  // basic_add
    return tmp_433;
}
ap_uint<6> uq_to_q_416(ap_uint<5> arg_0) {  // uq_to_q
    const ap_uint<4> tmp_434 = uq_add_417(ap_uint<3>(5), ap_uint<1>(1));  // uq_add
    const ap_uint<6> tmp_435 = ap_uint<6>(0);  // q_alloc
    const ap_uint<6> tmp_436 = ap_uint<6>(arg_0);  // basic_identity
    return tmp_436;
}
std::tuple<ap_uint<3>, ap_uint<3>> make_Tuple_443(ap_uint<3> arg_0, ap_uint<3> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_444 = std::tuple<ap_uint<3>, ap_uint<3>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_444;
}
std::tuple<ap_uint<3>, ap_uint<3>> uq_aligner_440(ap_uint<2> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<3> tmp_441 = ap_uint<3>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<3> tmp_442 = ap_uint<3>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_445 = make_Tuple_443(tmp_441, tmp_442);  // make_Tuple
    return tmp_445;
}
ap_uint<3> Tuple_get_item_0_447(std::tuple<ap_uint<3>, ap_uint<3>> arg_0) {  // Tuple_get_item_0
    const ap_uint<3> tmp_448 = ap_uint<3>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_448;
}
ap_uint<3> Tuple_get_item_1_450(std::tuple<ap_uint<3>, ap_uint<3>> arg_0) {  // Tuple_get_item_1
    const ap_uint<3> tmp_451 = ap_uint<3>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_451;
}
ap_uint<3> Copy_453(ap_uint<3> arg_0) {  // Copy
    return arg_0;
}
ap_uint<3> uq_add_439(ap_uint<2> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_446 = uq_aligner_440(arg_0, arg_1);  // uq_aligner
    const ap_uint<3> tmp_449 = Tuple_get_item_0_447(tmp_446);  // Tuple_get_item_0
    const ap_uint<3> tmp_452 = Tuple_get_item_1_450(tmp_446);  // Tuple_get_item_1
    const ap_uint<3> tmp_454 = Copy_453(tmp_449);  // Copy
    const ap_uint<3> tmp_455 = ap_uint<3>((tmp_449 + tmp_452));  // basic_add
    return tmp_455;
}
ap_uint<3> uq_to_q_438(ap_uint<2> arg_0) {  // uq_to_q
    const ap_uint<3> tmp_456 = uq_add_439(ap_uint<2>(2), ap_uint<1>(1));  // uq_add
    const ap_uint<3> tmp_457 = ap_uint<3>(0);  // q_alloc
    const ap_uint<3> tmp_458 = ap_uint<3>(arg_0);  // basic_identity
    return tmp_458;
}
ap_uint<1> q_sign_bit_464(ap_uint<6> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_465 = ap_uint<1>(((arg_0 >> 5) & ap_uint<1>(1)));  // basic_select
    return tmp_465;
}
ap_uint<7> q_sign_extend_463(ap_uint<6> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_466 = q_sign_bit_464(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_467 = ap_uint<2>((tmp_466 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_468 = ap_uint<1>((tmp_467 - tmp_466));  // basic_sub
    const ap_uint<7> tmp_469 = ap_uint<7>(0);  // q_alloc
    const ap_uint<7> tmp_470 = ap_uint<7>(((tmp_468 << 6) | arg_0));  // basic_concat
    return tmp_470;
}
ap_uint<1> q_sign_bit_474(ap_uint<3> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_475 = ap_uint<1>(((arg_0 >> 2) & ap_uint<1>(1)));  // basic_select
    return tmp_475;
}
ap_uint<7> q_sign_extend_473(ap_uint<3> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_476 = q_sign_bit_474(arg_0);  // q_sign_bit
    const ap_uint<5> tmp_477 = ap_uint<5>((tmp_476 << ap_uint<3>(4)));  // basic_lshift
    const ap_uint<4> tmp_478 = ap_uint<4>((tmp_477 - tmp_476));  // basic_sub
    const ap_uint<7> tmp_479 = ap_uint<7>(0);  // q_alloc
    const ap_uint<7> tmp_480 = ap_uint<7>(((tmp_478 << 3) | arg_0));  // basic_concat
    return tmp_480;
}
std::tuple<ap_uint<7>, ap_uint<7>> make_Tuple_482(ap_uint<7> arg_0, ap_uint<7> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_483 = std::tuple<ap_uint<7>, ap_uint<7>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_483;
}
std::tuple<ap_uint<7>, ap_uint<7>> q_aligner_461(ap_uint<6> arg_0, ap_uint<3> arg_1) {  // q_aligner
    const ap_uint<6> tmp_462 = ap_uint<6>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<7> tmp_471 = q_sign_extend_463(tmp_462);  // q_sign_extend
    const ap_uint<3> tmp_472 = ap_uint<3>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<7> tmp_481 = q_sign_extend_473(tmp_472);  // q_sign_extend
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_484 = make_Tuple_482(tmp_471, tmp_481);  // make_Tuple
    return tmp_484;
}
ap_uint<7> Tuple_get_item_0_486(std::tuple<ap_uint<7>, ap_uint<7>> arg_0) {  // Tuple_get_item_0
    const ap_uint<7> tmp_487 = ap_uint<7>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_487;
}
ap_uint<7> Tuple_get_item_1_489(std::tuple<ap_uint<7>, ap_uint<7>> arg_0) {  // Tuple_get_item_1
    const ap_uint<7> tmp_490 = ap_uint<7>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_490;
}
ap_uint<7> Copy_492(ap_uint<7> arg_0) {  // Copy
    return arg_0;
}
ap_uint<7> q_sub_460(ap_uint<6> arg_0, ap_uint<3> arg_1) {  // q_sub
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_485 = q_aligner_461(arg_0, arg_1);  // q_aligner
    const ap_uint<7> tmp_488 = Tuple_get_item_0_486(tmp_485);  // Tuple_get_item_0
    const ap_uint<7> tmp_491 = Tuple_get_item_1_489(tmp_485);  // Tuple_get_item_1
    const ap_uint<7> tmp_493 = Copy_492(tmp_488);  // Copy
    const ap_uint<7> tmp_494 = ap_uint<7>((tmp_488 - tmp_491));  // basic_sub
    return tmp_494;
}
ap_uint<1> q_sign_bit_500(ap_uint<7> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_501 = ap_uint<1>(((arg_0 >> 6) & ap_uint<1>(1)));  // basic_select
    return tmp_501;
}
ap_uint<8> q_sign_extend_499(ap_uint<7> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_502 = q_sign_bit_500(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_503 = ap_uint<2>((tmp_502 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_504 = ap_uint<1>((tmp_503 - tmp_502));  // basic_sub
    const ap_uint<8> tmp_505 = ap_uint<8>(0);  // q_alloc
    const ap_uint<8> tmp_506 = ap_uint<8>(((tmp_504 << 7) | arg_0));  // basic_concat
    return tmp_506;
}
ap_uint<1> q_sign_bit_510(ap_uint<2> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_511 = ap_uint<1>(((arg_0 >> 1) & ap_uint<1>(1)));  // basic_select
    return tmp_511;
}
ap_uint<8> q_sign_extend_509(ap_uint<2> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_512 = q_sign_bit_510(arg_0);  // q_sign_bit
    const ap_uint<7> tmp_513 = ap_uint<7>((tmp_512 << ap_uint<3>(6)));  // basic_lshift
    const ap_uint<6> tmp_514 = ap_uint<6>((tmp_513 - tmp_512));  // basic_sub
    const ap_uint<8> tmp_515 = ap_uint<8>(0);  // q_alloc
    const ap_uint<8> tmp_516 = ap_uint<8>(((tmp_514 << 2) | arg_0));  // basic_concat
    return tmp_516;
}
std::tuple<ap_uint<8>, ap_uint<8>> q_aligner_497(ap_uint<7> arg_0, ap_uint<2> arg_1) {  // q_aligner
    const ap_uint<7> tmp_498 = ap_uint<7>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_507 = q_sign_extend_499(tmp_498);  // q_sign_extend
    const ap_uint<2> tmp_508 = ap_uint<2>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_517 = q_sign_extend_509(tmp_508);  // q_sign_extend
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_518 = make_Tuple_26(tmp_507, tmp_517);  // make_Tuple
    return tmp_518;
}
ap_uint<8> q_add_496(ap_uint<7> arg_0, ap_uint<2> arg_1) {  // q_add
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_519 = q_aligner_497(arg_0, arg_1);  // q_aligner
    const ap_uint<8> tmp_520 = Tuple_get_item_0_30(tmp_519);  // Tuple_get_item_0
    const ap_uint<8> tmp_521 = Tuple_get_item_1_33(tmp_519);  // Tuple_get_item_1
    const ap_uint<8> tmp_522 = Copy_36(tmp_520);  // Copy
    const ap_uint<8> tmp_523 = ap_uint<8>((tmp_520 + tmp_521));  // basic_add
    return tmp_523;
}
ap_uint<1> q_sign_bit_525(ap_uint<8> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_526 = ap_uint<1>(((arg_0 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_526;
}
ap_uint<32> uq_resize_528(ap_uint<31> arg_0) {  // uq_resize
    const ap_uint<32> tmp_529 = ap_uint<32>((arg_0 << ap_uint<1>(1)));  // basic_lshift
    return tmp_529;
}
ap_uint<8> q_neg_535(ap_uint<8> arg_0) {  // q_neg
    const ap_uint<1> tmp_536 = ap_uint<1>((arg_0 == 128));  // _q_is_min_val
    const ap_uint<8> tmp_537 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_538 = ap_uint<8>((~arg_0));  // basic_invert
    const ap_uint<8> tmp_539 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_540 = ap_uint<8>((tmp_538 + ap_uint<1>(1)));  // basic_add
    const ap_uint<8> tmp_541 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_542 = ap_uint<8>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<8> tmp_543 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_544 = ap_uint<8>((~tmp_542));  // basic_invert
    const ap_uint<8> tmp_545 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_546 = ap_uint<8>((tmp_536 ? tmp_544 : tmp_540));  // basic_mux_2_1
    return tmp_546;
}
ap_uint<8> q_add_sign_533(ap_uint<8> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<8> tmp_534 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_547 = q_neg_535(arg_0);  // q_neg
    const ap_uint<8> tmp_548 = Copy_36(arg_0);  // Copy
    const ap_uint<8> tmp_549 = ap_uint<8>((arg_1 ? tmp_547 : tmp_534));  // basic_mux_2_1
    return tmp_549;
}
ap_uint<8> q_abs_531(ap_uint<8> arg_0) {  // q_abs
    const ap_uint<1> tmp_532 = q_sign_bit_525(arg_0);  // q_sign_bit
    const ap_uint<8> tmp_550 = q_add_sign_533(arg_0, tmp_532);  // q_add_sign
    return tmp_550;
}
ap_uint<7> q_to_uq_552(ap_uint<8> arg_0) {  // q_to_uq
    const ap_uint<7> tmp_553 = ap_uint<7>(arg_0);  // basic_identity
    return tmp_553;
}
ap_uint<32> uq_lshift_555(ap_uint<32> arg_0, ap_uint<7> arg_1) {  // uq_lshift
    const ap_uint<32> tmp_556 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_557 = ap_uint<32>((arg_0 << arg_1));  // basic_lshift
    return tmp_557;
}
ap_uint<32> uq_rshift_559(ap_uint<32> arg_0, ap_uint<7> arg_1) {  // uq_rshift
    const ap_uint<32> tmp_560 = Copy_139(arg_0);  // Copy
    const ap_uint<32> tmp_561 = ap_uint<32>((arg_0 >> arg_1));  // basic_rshift
    return tmp_561;
}
ap_uint<1> q_sign_bit_568(ap_uint<9> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_569 = ap_uint<1>(((arg_0 >> 8) & ap_uint<1>(1)));  // basic_select
    return tmp_569;
}
ap_uint<10> q_sign_extend_567(ap_uint<9> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_570 = q_sign_bit_568(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_571 = ap_uint<2>((tmp_570 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_572 = ap_uint<1>((tmp_571 - tmp_570));  // basic_sub
    const ap_uint<10> tmp_573 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_574 = ap_uint<10>(((tmp_572 << 9) | arg_0));  // basic_concat
    return tmp_574;
}
ap_uint<10> q_sign_extend_577(ap_uint<8> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_578 = q_sign_bit_525(arg_0);  // q_sign_bit
    const ap_uint<3> tmp_579 = ap_uint<3>((tmp_578 << ap_uint<2>(2)));  // basic_lshift
    const ap_uint<2> tmp_580 = ap_uint<2>((tmp_579 - tmp_578));  // basic_sub
    const ap_uint<10> tmp_581 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_582 = ap_uint<10>(((tmp_580 << 8) | arg_0));  // basic_concat
    return tmp_582;
}
std::tuple<ap_uint<10>, ap_uint<10>> make_Tuple_584(ap_uint<10> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_585 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_585;
}
std::tuple<ap_uint<10>, ap_uint<10>> q_aligner_565(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_aligner
    const ap_uint<9> tmp_566 = ap_uint<9>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_575 = q_sign_extend_567(tmp_566);  // q_sign_extend
    const ap_uint<8> tmp_576 = ap_uint<8>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_583 = q_sign_extend_577(tmp_576);  // q_sign_extend
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_586 = make_Tuple_584(tmp_575, tmp_583);  // make_Tuple
    return tmp_586;
}
ap_uint<10> Tuple_get_item_0_588(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<10> tmp_589 = ap_uint<10>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_589;
}
ap_uint<10> Tuple_get_item_1_591(std::tuple<ap_uint<10>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_592 = ap_uint<10>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_592;
}
ap_uint<10> Copy_594(ap_uint<10> arg_0) {  // Copy
    return arg_0;
}
ap_uint<10> q_sub_564(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_sub
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_587 = q_aligner_565(arg_0, arg_1);  // q_aligner
    const ap_uint<10> tmp_590 = Tuple_get_item_0_588(tmp_587);  // Tuple_get_item_0
    const ap_uint<10> tmp_593 = Tuple_get_item_1_591(tmp_587);  // Tuple_get_item_1
    const ap_uint<10> tmp_595 = Copy_594(tmp_590);  // Copy
    const ap_uint<10> tmp_596 = ap_uint<10>((tmp_590 - tmp_593));  // basic_sub
    return tmp_596;
}
ap_uint<10> q_add_598(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_599 = q_aligner_565(arg_0, arg_1);  // q_aligner
    const ap_uint<10> tmp_600 = Tuple_get_item_0_588(tmp_599);  // Tuple_get_item_0
    const ap_uint<10> tmp_601 = Tuple_get_item_1_591(tmp_599);  // Tuple_get_item_1
    const ap_uint<10> tmp_602 = Copy_594(tmp_600);  // Copy
    const ap_uint<10> tmp_603 = ap_uint<10>((tmp_600 + tmp_601));  // basic_add
    return tmp_603;
}
std::tuple<ap_uint<31>, ap_uint<10>> make_Tuple_607(ap_uint<31> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_608 = std::tuple<ap_uint<31>, ap_uint<10>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_608;
}
std::tuple<ap_uint<31>, ap_uint<10>> fp32_normalize_193(ap_uint<31> arg_0, ap_uint<9> arg_1) {  // fp32_normalize
    const ap_uint<5> tmp_415 = lzc_194(arg_0);  // lzc
    const ap_uint<6> tmp_437 = uq_to_q_416(tmp_415);  // uq_to_q
    const ap_uint<3> tmp_459 = uq_to_q_438(ap_uint<2>(2));  // uq_to_q
    const ap_uint<7> tmp_495 = q_sub_460(tmp_437, tmp_459);  // q_sub
    const ap_uint<8> tmp_524 = q_add_496(tmp_495, ap_uint<2>(1));  // q_add
    const ap_uint<1> tmp_527 = q_sign_bit_525(tmp_524);  // q_sign_bit
    const ap_uint<32> tmp_530 = uq_resize_528(arg_0);  // uq_resize
    const ap_uint<8> tmp_551 = q_abs_531(tmp_524);  // q_abs
    const ap_uint<7> tmp_554 = q_to_uq_552(tmp_551);  // q_to_uq
    const ap_uint<32> tmp_558 = uq_lshift_555(tmp_530, tmp_554);  // uq_lshift
    const ap_uint<32> tmp_562 = uq_rshift_559(tmp_530, tmp_554);  // uq_rshift
    const ap_uint<31> tmp_563 = ap_uint<31>((tmp_527 ? tmp_562 : tmp_558));  // basic_mux_2_1
    const ap_uint<10> tmp_597 = q_sub_564(arg_1, tmp_551);  // q_sub
    const ap_uint<10> tmp_604 = q_add_598(arg_1, tmp_551);  // q_add
    const ap_uint<10> tmp_605 = Copy_594(tmp_604);  // Copy
    const ap_uint<10> tmp_606 = ap_uint<10>((tmp_527 ? tmp_604 : tmp_597));  // basic_mux_2_1
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_609 = make_Tuple_607(tmp_563, tmp_606);  // make_Tuple
    return tmp_609;
}
ap_uint<31> Tuple_get_item_0_611(std::tuple<ap_uint<31>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<31> tmp_612 = ap_uint<31>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_612;
}
ap_uint<10> Tuple_get_item_1_614(std::tuple<ap_uint<31>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_615 = ap_uint<10>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_615;
}
ap_uint<1> q_is_zero_619(ap_uint<10> arg_0) {  // q_is_zero
    const ap_uint<1> tmp_620 = ap_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_621 = ap_uint<1>((~tmp_620));  // basic_invert
    return tmp_621;
}
ap_uint<1> q_sign_bit_623(ap_uint<10> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_624 = ap_uint<1>(((arg_0 >> 9) & ap_uint<1>(1)));  // basic_select
    return tmp_624;
}
ap_uint<10> q_neg_631(ap_uint<10> arg_0) {  // q_neg
    const ap_uint<1> tmp_632 = ap_uint<1>((arg_0 == 512));  // _q_is_min_val
    const ap_uint<10> tmp_633 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_634 = ap_uint<10>((~arg_0));  // basic_invert
    const ap_uint<10> tmp_635 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_636 = ap_uint<10>((tmp_634 + ap_uint<1>(1)));  // basic_add
    const ap_uint<10> tmp_637 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_638 = ap_uint<10>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<10> tmp_639 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_640 = ap_uint<10>((~tmp_638));  // basic_invert
    const ap_uint<10> tmp_641 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_642 = ap_uint<10>((tmp_632 ? tmp_640 : tmp_636));  // basic_mux_2_1
    return tmp_642;
}
ap_uint<10> q_add_sign_629(ap_uint<10> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<10> tmp_630 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_643 = q_neg_631(arg_0);  // q_neg
    const ap_uint<10> tmp_644 = Copy_594(arg_0);  // Copy
    const ap_uint<10> tmp_645 = ap_uint<10>((arg_1 ? tmp_643 : tmp_630));  // basic_mux_2_1
    return tmp_645;
}
ap_uint<10> q_abs_627(ap_uint<10> arg_0) {  // q_abs
    const ap_uint<1> tmp_628 = q_sign_bit_623(arg_0);  // q_sign_bit
    const ap_uint<10> tmp_646 = q_add_sign_629(arg_0, tmp_628);  // q_add_sign
    return tmp_646;
}
ap_uint<9> q_to_uq_648(ap_uint<10> arg_0) {  // q_to_uq
    const ap_uint<9> tmp_649 = ap_uint<9>(arg_0);  // basic_identity
    return tmp_649;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_652(ap_uint<1> arg_0, ap_uint<9> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_653 = ap_uint<10>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_654 = ap_uint<10>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_655 = make_Tuple_584(tmp_653, tmp_654);  // make_Tuple
    return tmp_655;
}
ap_uint<10> uq_add_651(ap_uint<1> arg_0, ap_uint<9> arg_1) {  // uq_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_656 = uq_aligner_652(arg_0, arg_1);  // uq_aligner
    const ap_uint<10> tmp_657 = Tuple_get_item_0_588(tmp_656);  // Tuple_get_item_0
    const ap_uint<10> tmp_658 = Tuple_get_item_1_591(tmp_656);  // Tuple_get_item_1
    const ap_uint<10> tmp_659 = Copy_594(tmp_657);  // Copy
    const ap_uint<10> tmp_660 = ap_uint<10>((tmp_657 + tmp_658));  // basic_add
    return tmp_660;
}
ap_uint<41> Copy_665(ap_uint<41> arg_0) {  // Copy
    return arg_0;
}
ap_uint<41> uq_rshift_664(ap_uint<41> arg_0, ap_uint<10> arg_1) {  // uq_rshift
    const ap_uint<41> tmp_666 = Copy_665(arg_0);  // Copy
    const ap_uint<41> tmp_667 = ap_uint<41>((arg_0 >> arg_1));  // basic_rshift
    return tmp_667;
}
std::tuple<ap_uint<41>, ap_uint<9>> make_Tuple_671(ap_uint<41> arg_0, ap_uint<9> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_672 = std::tuple<ap_uint<41>, ap_uint<9>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_672;
}
std::tuple<ap_uint<41>, ap_uint<9>> fp32_classify_617(ap_uint<31> arg_0, ap_uint<10> arg_1) {  // fp32_classify
    const ap_uint<41> tmp_618 = ap_uint<41>((arg_0 << ap_uint<4>(10)));  // basic_lshift
    const ap_uint<1> tmp_622 = q_is_zero_619(arg_1);  // q_is_zero
    const ap_uint<1> tmp_625 = q_sign_bit_623(arg_1);  // q_sign_bit
    const ap_uint<1> tmp_626 = ap_uint<1>((tmp_622 | tmp_625));  // basic_or
    const ap_uint<10> tmp_647 = q_abs_627(arg_1);  // q_abs
    const ap_uint<9> tmp_650 = q_to_uq_648(tmp_647);  // q_to_uq
    const ap_uint<10> tmp_661 = uq_add_651(ap_uint<1>(1), tmp_650);  // uq_add
    const ap_uint<10> tmp_662 = Copy_594(tmp_661);  // Copy
    const ap_uint<10> tmp_663 = ap_uint<10>((tmp_626 ? tmp_661 : ap_uint<1>(0)));  // basic_mux_2_1
    const ap_uint<41> tmp_668 = uq_rshift_664(tmp_618, tmp_663);  // uq_rshift
    const ap_uint<9> tmp_669 = Copy_54(tmp_650);  // Copy
    const ap_uint<9> tmp_670 = ap_uint<9>((tmp_626 ? ap_uint<1>(0) : tmp_650));  // basic_mux_2_1
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_673 = make_Tuple_671(tmp_668, tmp_670);  // make_Tuple
    return tmp_673;
}
ap_uint<41> Tuple_get_item_0_675(std::tuple<ap_uint<41>, ap_uint<9>> arg_0) {  // Tuple_get_item_0
    const ap_uint<41> tmp_676 = ap_uint<41>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_676;
}
ap_uint<40> uq_select_679(ap_uint<41> arg_0) {  // uq_select
    const ap_uint<40> tmp_680 = ap_uint<40>(((arg_0 >> 0) & ap_uint<40>(1099511627775)));  // basic_select
    return tmp_680;
}
ap_uint<40> drop_implicit_bit_678(ap_uint<41> arg_0) {  // drop_implicit_bit
    const ap_uint<40> tmp_681 = uq_select_679(arg_0);  // uq_select
    return tmp_681;
}
ap_uint<9> Tuple_get_item_1_683(std::tuple<ap_uint<41>, ap_uint<9>> arg_0) {  // Tuple_get_item_1
    const ap_uint<9> tmp_684 = ap_uint<9>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_684;
}
ap_uint<1> uq_is_zero_687(ap_uint<9> arg_0) {  // uq_is_zero
    const ap_uint<1> tmp_688 = ap_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_689 = ap_uint<1>((~tmp_688));  // basic_invert
    return tmp_689;
}
ap_uint<23> uq_resize_691(ap_uint<40> arg_0) {  // uq_resize
    const ap_uint<23> tmp_692 = ap_uint<23>((arg_0 >> ap_uint<5>(17)));  // basic_rshift
    return tmp_692;
}
ap_uint<1> uq_select_695(ap_uint<40> arg_0) {  // uq_select
    const ap_uint<1> tmp_696 = ap_uint<1>(((arg_0 >> 16) & ap_uint<1>(1)));  // basic_select
    return tmp_696;
}
ap_uint<15> uq_select_699(ap_uint<40> arg_0) {  // uq_select
    const ap_uint<15> tmp_700 = ap_uint<15>(((arg_0 >> 0) & ap_uint<15>(32767)));  // basic_select
    return tmp_700;
}
ap_uint<23> uq_RNE_IEEE_694(ap_uint<40> arg_0) {  // uq_RNE_IEEE
    const ap_uint<1> tmp_697 = uq_select_695(arg_0);  // uq_select
    const ap_uint<1> tmp_698 = uq_select_695(arg_0);  // uq_select
    const ap_uint<15> tmp_701 = uq_select_699(arg_0);  // uq_select
    const ap_uint<1> tmp_702 = Copy_198(ap_uint<1>(0));  // Copy
    const ap_uint<1> tmp_703 = ap_uint<1>((tmp_701 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_704 = ap_uint<1>((tmp_698 | tmp_703));  // basic_or
    const ap_uint<1> tmp_705 = uq_select_695(arg_0);  // uq_select
    const ap_uint<1> tmp_706 = ap_uint<1>((tmp_704 | tmp_705));  // basic_or
    const ap_uint<1> tmp_707 = ap_uint<1>((tmp_697 & tmp_706));  // basic_and
    const ap_uint<23> tmp_708 = ap_uint<23>(tmp_707);  // basic_identity
    return tmp_708;
}
std::tuple<ap_uint<24>, ap_uint<24>> make_Tuple_714(ap_uint<24> arg_0, ap_uint<24> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_715 = std::tuple<ap_uint<24>, ap_uint<24>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_715;
}
std::tuple<ap_uint<24>, ap_uint<24>> uq_aligner_711(ap_uint<23> arg_0, ap_uint<23> arg_1) {  // uq_aligner
    const ap_uint<24> tmp_712 = ap_uint<24>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<24> tmp_713 = ap_uint<24>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_716 = make_Tuple_714(tmp_712, tmp_713);  // make_Tuple
    return tmp_716;
}
ap_uint<24> Tuple_get_item_0_718(std::tuple<ap_uint<24>, ap_uint<24>> arg_0) {  // Tuple_get_item_0
    const ap_uint<24> tmp_719 = ap_uint<24>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_719;
}
ap_uint<24> Tuple_get_item_1_721(std::tuple<ap_uint<24>, ap_uint<24>> arg_0) {  // Tuple_get_item_1
    const ap_uint<24> tmp_722 = ap_uint<24>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_722;
}
ap_uint<24> Copy_724(ap_uint<24> arg_0) {  // Copy
    return arg_0;
}
ap_uint<24> uq_add_710(ap_uint<23> arg_0, ap_uint<23> arg_1) {  // uq_add
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_717 = uq_aligner_711(arg_0, arg_1);  // uq_aligner
    const ap_uint<24> tmp_720 = Tuple_get_item_0_718(tmp_717);  // Tuple_get_item_0
    const ap_uint<24> tmp_723 = Tuple_get_item_1_721(tmp_717);  // Tuple_get_item_1
    const ap_uint<24> tmp_725 = Copy_724(tmp_720);  // Copy
    const ap_uint<24> tmp_726 = ap_uint<24>((tmp_720 + tmp_723));  // basic_add
    return tmp_726;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_730(ap_uint<9> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_731 = ap_uint<10>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_732 = ap_uint<10>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_733 = make_Tuple_584(tmp_731, tmp_732);  // make_Tuple
    return tmp_733;
}
ap_uint<10> uq_add_729(ap_uint<9> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_734 = uq_aligner_730(arg_0, arg_1);  // uq_aligner
    const ap_uint<10> tmp_735 = Tuple_get_item_0_588(tmp_734);  // Tuple_get_item_0
    const ap_uint<10> tmp_736 = Tuple_get_item_1_591(tmp_734);  // Tuple_get_item_1
    const ap_uint<10> tmp_737 = Copy_594(tmp_735);  // Copy
    const ap_uint<10> tmp_738 = ap_uint<10>((tmp_735 + tmp_736));  // basic_add
    return tmp_738;
}
ap_uint<23> Copy_743(ap_uint<23> arg_0) {  // Copy
    return arg_0;
}
std::tuple<ap_uint<23>, ap_uint<10>> make_Tuple_748(ap_uint<23> arg_0, ap_uint<10> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_749 = std::tuple<ap_uint<23>, ap_uint<10>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_749;
}
std::tuple<ap_uint<23>, ap_uint<10>> fp32_round_686(ap_uint<40> arg_0, ap_uint<9> arg_1) {  // fp32_round
    const ap_uint<1> tmp_690 = uq_is_zero_687(arg_1);  // uq_is_zero
    const ap_uint<23> tmp_693 = uq_resize_691(arg_0);  // uq_resize
    const ap_uint<23> tmp_709 = uq_RNE_IEEE_694(arg_0);  // uq_RNE_IEEE
    const ap_uint<24> tmp_727 = uq_add_710(tmp_693, tmp_709);  // uq_add
    const ap_uint<1> tmp_728 = ap_uint<1>(((tmp_727 >> 23) & ap_uint<1>(1)));  // basic_select
    const ap_uint<10> tmp_739 = uq_add_729(arg_1, tmp_728);  // uq_add
    const ap_uint<1> tmp_740 = ap_uint<1>((tmp_739 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_741 = ap_uint<1>((tmp_690 & tmp_740));  // basic_and
    const ap_uint<23> tmp_742 = ap_uint<23>((tmp_727 >> ap_uint<1>(1)));  // basic_rshift
    const ap_uint<23> tmp_744 = Copy_743(tmp_742);  // Copy
    const ap_uint<23> tmp_745 = ap_uint<23>((tmp_728 ? tmp_742 : tmp_727));  // basic_mux_2_1
    const ap_uint<23> tmp_746 = Copy_743(tmp_745);  // Copy
    const ap_uint<23> tmp_747 = ap_uint<23>((tmp_741 ? ap_uint<1>(0) : tmp_745));  // basic_mux_2_1
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_750 = make_Tuple_748(tmp_747, tmp_739);  // make_Tuple
    return tmp_750;
}
ap_uint<23> Tuple_get_item_0_752(std::tuple<ap_uint<23>, ap_uint<10>> arg_0) {  // Tuple_get_item_0
    const ap_uint<23> tmp_753 = ap_uint<23>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_753;
}
ap_uint<10> Tuple_get_item_1_755(std::tuple<ap_uint<23>, ap_uint<10>> arg_0) {  // Tuple_get_item_1
    const ap_uint<10> tmp_756 = ap_uint<10>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_756;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_760(ap_uint<10> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_761 = ap_uint<10>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_762 = ap_uint<10>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_763 = make_Tuple_584(tmp_761, tmp_762);  // make_Tuple
    return tmp_763;
}
ap_uint<10> uq_min_759(ap_uint<10> arg_0, ap_uint<8> arg_1) {  // uq_min
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_764 = uq_aligner_760(arg_0, arg_1);  // uq_aligner
    const ap_uint<10> tmp_765 = Tuple_get_item_0_588(tmp_764);  // Tuple_get_item_0
    const ap_uint<10> tmp_766 = Tuple_get_item_1_591(tmp_764);  // Tuple_get_item_1
    const ap_uint<10> tmp_767 = Copy_594(tmp_765);  // Copy
    const ap_uint<10> tmp_768 = ap_uint<10>((tmp_765 < tmp_766 ? tmp_765 : tmp_766));  // basic_min
    return tmp_768;
}
ap_uint<23> fraction_to_bits_774(ap_uint<23> arg_0) {  // fraction_to_bits
    const ap_uint<23> tmp_775 = ap_uint<23>(arg_0);  // basic_identity
    return tmp_775;
}
ap_uint<1> uq_is_zero_777(ap_uint<31> arg_0) {  // uq_is_zero
    const ap_uint<1> tmp_778 = ap_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_779 = ap_uint<1>((~tmp_778));  // basic_invert
    return tmp_779;
}
std::tuple<ap_uint<23>, ap_uint<8>> make_Tuple_783(ap_uint<23> arg_0, ap_uint<8> arg_1) {  // make_Tuple
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_784 = std::tuple<ap_uint<23>, ap_uint<8>>(std::make_tuple(arg_0, arg_1));  // basic_tuple_maker_2
    return tmp_784;
}
std::tuple<ap_uint<23>, ap_uint<8>> fp32_encodings_758(ap_uint<23> arg_0, ap_uint<10> arg_1, ap_uint<31> arg_2) {  // fp32_encodings
    const ap_uint<10> tmp_769 = uq_min_759(arg_1, ap_uint<8>(255));  // uq_min
    const ap_uint<8> tmp_770 = ap_uint<8>(tmp_769);  // basic_identity
    const ap_uint<1> tmp_771 = ap_uint<1>((tmp_770 == ap_uint<8>(255)));  // basic_and_reduce
    const ap_uint<23> tmp_772 = Copy_743(arg_0);  // Copy
    const ap_uint<23> tmp_773 = ap_uint<23>((tmp_771 ? ap_uint<1>(0) : arg_0));  // basic_mux_2_1
    const ap_uint<23> tmp_776 = fraction_to_bits_774(tmp_773);  // fraction_to_bits
    const ap_uint<1> tmp_780 = uq_is_zero_777(arg_2);  // uq_is_zero
    const ap_uint<8> tmp_781 = Copy_36(tmp_770);  // Copy
    const ap_uint<8> tmp_782 = ap_uint<8>((tmp_780 ? ap_uint<1>(0) : tmp_770));  // basic_mux_2_1
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_785 = make_Tuple_783(tmp_776, tmp_782);  // make_Tuple
    return tmp_785;
}
ap_uint<8> Tuple_get_item_1_787(std::tuple<ap_uint<23>, ap_uint<8>> arg_0) {  // Tuple_get_item_1
    const ap_uint<8> tmp_788 = ap_uint<8>(std::get<1>(arg_0));  // basic_get_item_1
    return tmp_788;
}
ap_uint<23> Tuple_get_item_0_790(std::tuple<ap_uint<23>, ap_uint<8>> arg_0) {  // Tuple_get_item_0
    const ap_uint<23> tmp_791 = ap_uint<23>(std::get<0>(arg_0));  // basic_get_item_0
    return tmp_791;
}
ap_uint<32> fp32_pack_793(ap_uint<1> arg_0, ap_uint<8> arg_1, ap_uint<23> arg_2) {  // fp32_pack
    const ap_uint<32> tmp_794 = ap_uint<32>(((arg_0 << 31) | (arg_1 << 23) | arg_2));  // float32_alloc
    return tmp_794;
}
ap_uint<32> encode_Float32_165(ap_uint<32> arg_0, ap_uint<9> arg_1) {  // encode_Float32
    const ap_uint<1> tmp_168 = q_sign_bit_166(arg_0);  // q_sign_bit
    const ap_uint<32> tmp_189 = q_abs_169(arg_0);  // q_abs
    const ap_uint<31> tmp_192 = q_to_uq_190(tmp_189);  // q_to_uq
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_610 = fp32_normalize_193(tmp_192, arg_1);  // fp32_normalize
    const ap_uint<31> tmp_613 = Tuple_get_item_0_611(tmp_610);  // Tuple_get_item_0
    const ap_uint<10> tmp_616 = Tuple_get_item_1_614(tmp_610);  // Tuple_get_item_1
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_674 = fp32_classify_617(tmp_613, tmp_616);  // fp32_classify
    const ap_uint<41> tmp_677 = Tuple_get_item_0_675(tmp_674);  // Tuple_get_item_0
    const ap_uint<40> tmp_682 = drop_implicit_bit_678(tmp_677);  // drop_implicit_bit
    const ap_uint<9> tmp_685 = Tuple_get_item_1_683(tmp_674);  // Tuple_get_item_1
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_751 = fp32_round_686(tmp_682, tmp_685);  // fp32_round
    const ap_uint<23> tmp_754 = Tuple_get_item_0_752(tmp_751);  // Tuple_get_item_0
    const ap_uint<10> tmp_757 = Tuple_get_item_1_755(tmp_751);  // Tuple_get_item_1
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_786 = fp32_encodings_758(tmp_754, tmp_757, tmp_192);  // fp32_encodings
    const ap_uint<8> tmp_789 = Tuple_get_item_1_787(tmp_786);  // Tuple_get_item_1
    const ap_uint<23> tmp_792 = Tuple_get_item_0_790(tmp_786);  // Tuple_get_item_0
    const ap_uint<32> tmp_795 = fp32_pack_793(tmp_168, tmp_789, tmp_792);  // fp32_pack
    return tmp_795;
}
ap_uint<32> main(ap_uint<32> arg_0, ap_uint<32> arg_1) {  // FP32_IEEE_adder
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_7 = fp32_unpack_0(arg_0);  // fp32_unpack
    const ap_uint<23> tmp_10 = Tuple_get_item_2_8(tmp_7);  // Tuple_get_item_2
    const ap_uint<24> tmp_13 = add_implicit_bit_11(tmp_10);  // add_implicit_bit
    const ap_uint<30> tmp_16 = uq_resize_14(tmp_13);  // uq_resize
    const ap_uint<8> tmp_19 = Tuple_get_item_1_17(tmp_7);  // Tuple_get_item_1
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_20 = fp32_unpack_0(arg_1);  // fp32_unpack
    const ap_uint<8> tmp_21 = Tuple_get_item_1_17(tmp_20);  // Tuple_get_item_1
    const ap_uint<8> tmp_39 = uq_max_22(tmp_19, tmp_21);  // uq_max
    const ap_uint<9> tmp_57 = uq_sub_40(tmp_39, tmp_19);  // uq_sub
    const ap_uint<30> tmp_62 = uq_rshift_58(tmp_16, tmp_57);  // uq_rshift
    const ap_uint<31> tmp_84 = uq_to_q_63(tmp_62);  // uq_to_q
    const ap_uint<1> tmp_87 = Tuple_get_item_0_85(tmp_7);  // Tuple_get_item_0
    const ap_uint<31> tmp_106 = q_add_sign_88(tmp_84, tmp_87);  // q_add_sign
    const ap_uint<23> tmp_107 = Tuple_get_item_2_8(tmp_20);  // Tuple_get_item_2
    const ap_uint<24> tmp_108 = add_implicit_bit_11(tmp_107);  // add_implicit_bit
    const ap_uint<30> tmp_109 = uq_resize_14(tmp_108);  // uq_resize
    const ap_uint<9> tmp_110 = uq_sub_40(tmp_39, tmp_21);  // uq_sub
    const ap_uint<30> tmp_111 = uq_rshift_58(tmp_109, tmp_110);  // uq_rshift
    const ap_uint<31> tmp_112 = uq_to_q_63(tmp_111);  // uq_to_q
    const ap_uint<1> tmp_113 = Tuple_get_item_0_85(tmp_20);  // Tuple_get_item_0
    const ap_uint<31> tmp_114 = q_add_sign_88(tmp_112, tmp_113);  // q_add_sign
    const ap_uint<32> tmp_142 = q_add_115(tmp_106, tmp_114);  // q_add
    const ap_uint<9> tmp_164 = uq_to_q_143(tmp_39);  // uq_to_q
    const ap_uint<32> tmp_796 = encode_Float32_165(tmp_142, tmp_164);  // encode_Float32
    return tmp_796;
}

