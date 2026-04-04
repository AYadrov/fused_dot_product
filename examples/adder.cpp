#include <ap_int.h>
#include <tuple>

std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> fp32_unpack_0(ap_uint<32> arg_0) {  // fp32_unpack
    const ap_uint<1> tmp_1 = ap_uint<1>(((arg_0 >> 31) & ap_uint<1>(1)));  // _fp32_sign
    const ap_uint<8> tmp_2 = ap_uint<8>(((arg_0 >> 23) & ap_uint<8>(255)));  // _fp32_exponent
    const ap_uint<23> tmp_3 = ap_uint<23>(((arg_0 >> 0) & ap_uint<23>(8388607)));  // _fp32_mantissa
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_4 = std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>>(std::make_tuple(tmp_1, tmp_2, tmp_3));  // basic_tuple_maker_3
    return tmp_4;
}
ap_uint<24> add_implicit_bit_7(ap_uint<23> arg_0) {  // add_implicit_bit
    const ap_uint<24> tmp_8 = ap_uint<24>(((ap_uint<1>(1) << 23) | arg_0));  // basic_concat
    return tmp_8;
}
ap_uint<30> uq_resize_10(ap_uint<24> arg_0) {  // uq_resize
    const ap_uint<30> tmp_11 = ap_uint<30>((arg_0 << ap_uint<3>(6)));  // basic_lshift
    return tmp_11;
}
std::tuple<ap_uint<8>, ap_uint<8>> uq_aligner_17(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<8> tmp_18 = ap_uint<8>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_19 = ap_uint<8>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_20 = std::tuple<ap_uint<8>, ap_uint<8>>(std::make_tuple(tmp_18, tmp_19));  // basic_tuple_maker_2
    return tmp_20;
}
ap_uint<8> uq_max_16(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_max
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_21 = uq_aligner_17(arg_0, arg_1);  // uq_aligner
    const ap_uint<8> tmp_22 = ap_uint<8>(std::get<0>(tmp_21));  // basic_get_item_0
    const ap_uint<8> tmp_23 = ap_uint<8>(std::get<1>(tmp_21));  // basic_get_item_1
    const ap_uint<8> tmp_24 = ap_uint<8>((tmp_22 > tmp_23 ? tmp_22 : tmp_23));  // basic_max
    return tmp_24;
}
std::tuple<ap_uint<9>, ap_uint<9>> uq_aligner_27(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<9> tmp_28 = ap_uint<9>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<9> tmp_29 = ap_uint<9>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_30 = std::tuple<ap_uint<9>, ap_uint<9>>(std::make_tuple(tmp_28, tmp_29));  // basic_tuple_maker_2
    return tmp_30;
}
ap_uint<9> uq_sub_26(ap_uint<8> arg_0, ap_uint<8> arg_1) {  // uq_sub
    const std::tuple<ap_uint<9>, ap_uint<9>> tmp_31 = uq_aligner_27(arg_0, arg_1);  // uq_aligner
    const ap_uint<9> tmp_32 = ap_uint<9>(std::get<0>(tmp_31));  // basic_get_item_0
    const ap_uint<9> tmp_33 = ap_uint<9>(std::get<1>(tmp_31));  // basic_get_item_1
    const ap_uint<9> tmp_34 = ap_uint<9>((tmp_32 - tmp_33));  // basic_sub
    return tmp_34;
}
ap_uint<30> uq_rshift_36(ap_uint<30> arg_0, ap_uint<9> arg_1) {  // uq_rshift
    const ap_uint<30> tmp_37 = ap_uint<30>((arg_0 >> arg_1));  // basic_rshift
    return tmp_37;
}
std::tuple<ap_uint<2>, ap_uint<2>> uq_aligner_41(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<2> tmp_42 = ap_uint<2>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<2> tmp_43 = ap_uint<2>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_44 = std::tuple<ap_uint<2>, ap_uint<2>>(std::make_tuple(tmp_42, tmp_43));  // basic_tuple_maker_2
    return tmp_44;
}
ap_uint<2> uq_add_40(ap_uint<1> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<2>, ap_uint<2>> tmp_45 = uq_aligner_41(arg_0, arg_1);  // uq_aligner
    const ap_uint<2> tmp_46 = ap_uint<2>(std::get<0>(tmp_45));  // basic_get_item_0
    const ap_uint<2> tmp_47 = ap_uint<2>(std::get<1>(tmp_45));  // basic_get_item_1
    const ap_uint<2> tmp_48 = ap_uint<2>((tmp_46 + tmp_47));  // basic_add
    return tmp_48;
}
ap_uint<31> uq_to_q_39(ap_uint<30> arg_0) {  // uq_to_q
    const ap_uint<2> tmp_49 = uq_add_40(ap_uint<1>(1), ap_uint<1>(1));  // uq_add
    const ap_uint<31> tmp_50 = ap_uint<31>(0);  // q_alloc
    const ap_uint<31> tmp_51 = ap_uint<31>(arg_0);  // basic_identity
    return tmp_51;
}
ap_uint<31> q_neg_55(ap_uint<31> arg_0) {  // q_neg
    const ap_uint<1> tmp_56 = ap_uint<1>((arg_0 == 1073741824));  // _q_is_min_val
    const ap_uint<31> tmp_57 = ap_uint<31>((~arg_0));  // basic_invert
    const ap_uint<31> tmp_58 = ap_uint<31>((tmp_57 + ap_uint<1>(1)));  // basic_add
    const ap_uint<31> tmp_59 = ap_uint<31>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<31> tmp_60 = ap_uint<31>((~tmp_59));  // basic_invert
    const ap_uint<31> tmp_61 = ap_uint<31>((tmp_56 ? tmp_60 : tmp_58));  // basic_mux_2_1
    return tmp_61;
}
ap_uint<31> q_add_sign_54(ap_uint<31> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<31> tmp_62 = q_neg_55(arg_0);  // q_neg
    const ap_uint<31> tmp_63 = ap_uint<31>((arg_1 ? tmp_62 : arg_0));  // basic_mux_2_1
    return tmp_63;
}
ap_uint<1> q_sign_bit_77(ap_uint<31> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_78 = ap_uint<1>(((arg_0 >> 30) & ap_uint<1>(1)));  // basic_select
    return tmp_78;
}
ap_uint<32> q_sign_extend_76(ap_uint<31> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_79 = q_sign_bit_77(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_80 = ap_uint<2>((tmp_79 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_81 = ap_uint<1>((tmp_80 - tmp_79));  // basic_sub
    const ap_uint<32> tmp_82 = ap_uint<32>(0);  // q_alloc
    const ap_uint<32> tmp_83 = ap_uint<32>(((tmp_81 << 31) | arg_0));  // basic_concat
    return tmp_83;
}
std::tuple<ap_uint<32>, ap_uint<32>> q_aligner_74(ap_uint<31> arg_0, ap_uint<31> arg_1) {  // q_aligner
    const ap_uint<31> tmp_75 = ap_uint<31>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<32> tmp_84 = q_sign_extend_76(tmp_75);  // q_sign_extend
    const ap_uint<31> tmp_85 = ap_uint<31>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<32> tmp_86 = q_sign_extend_76(tmp_85);  // q_sign_extend
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_87 = std::tuple<ap_uint<32>, ap_uint<32>>(std::make_tuple(tmp_84, tmp_86));  // basic_tuple_maker_2
    return tmp_87;
}
ap_uint<32> q_add_73(ap_uint<31> arg_0, ap_uint<31> arg_1) {  // q_add
    const std::tuple<ap_uint<32>, ap_uint<32>> tmp_88 = q_aligner_74(arg_0, arg_1);  // q_aligner
    const ap_uint<32> tmp_89 = ap_uint<32>(std::get<0>(tmp_88));  // basic_get_item_0
    const ap_uint<32> tmp_90 = ap_uint<32>(std::get<1>(tmp_88));  // basic_get_item_1
    const ap_uint<32> tmp_91 = ap_uint<32>((tmp_89 + tmp_90));  // basic_add
    return tmp_91;
}
std::tuple<ap_uint<5>, ap_uint<5>> uq_aligner_95(ap_uint<4> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<5> tmp_96 = ap_uint<5>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<5> tmp_97 = ap_uint<5>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_98 = std::tuple<ap_uint<5>, ap_uint<5>>(std::make_tuple(tmp_96, tmp_97));  // basic_tuple_maker_2
    return tmp_98;
}
ap_uint<5> uq_add_94(ap_uint<4> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<5>, ap_uint<5>> tmp_99 = uq_aligner_95(arg_0, arg_1);  // uq_aligner
    const ap_uint<5> tmp_100 = ap_uint<5>(std::get<0>(tmp_99));  // basic_get_item_0
    const ap_uint<5> tmp_101 = ap_uint<5>(std::get<1>(tmp_99));  // basic_get_item_1
    const ap_uint<5> tmp_102 = ap_uint<5>((tmp_100 + tmp_101));  // basic_add
    return tmp_102;
}
ap_uint<9> uq_to_q_93(ap_uint<8> arg_0) {  // uq_to_q
    const ap_uint<5> tmp_103 = uq_add_94(ap_uint<4>(8), ap_uint<1>(1));  // uq_add
    const ap_uint<9> tmp_104 = ap_uint<9>(0);  // q_alloc
    const ap_uint<9> tmp_105 = ap_uint<9>(arg_0);  // basic_identity
    return tmp_105;
}
ap_uint<1> q_sign_bit_108(ap_uint<32> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_109 = ap_uint<1>(((arg_0 >> 31) & ap_uint<1>(1)));  // basic_select
    return tmp_109;
}
ap_uint<32> q_neg_114(ap_uint<32> arg_0) {  // q_neg
    const ap_uint<1> tmp_115 = ap_uint<1>((arg_0 == 2147483648));  // _q_is_min_val
    const ap_uint<32> tmp_116 = ap_uint<32>((~arg_0));  // basic_invert
    const ap_uint<32> tmp_117 = ap_uint<32>((tmp_116 + ap_uint<1>(1)));  // basic_add
    const ap_uint<32> tmp_118 = ap_uint<32>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<32> tmp_119 = ap_uint<32>((~tmp_118));  // basic_invert
    const ap_uint<32> tmp_120 = ap_uint<32>((tmp_115 ? tmp_119 : tmp_117));  // basic_mux_2_1
    return tmp_120;
}
ap_uint<32> q_add_sign_113(ap_uint<32> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<32> tmp_121 = q_neg_114(arg_0);  // q_neg
    const ap_uint<32> tmp_122 = ap_uint<32>((arg_1 ? tmp_121 : arg_0));  // basic_mux_2_1
    return tmp_122;
}
ap_uint<32> q_abs_111(ap_uint<32> arg_0) {  // q_abs
    const ap_uint<1> tmp_112 = q_sign_bit_108(arg_0);  // q_sign_bit
    const ap_uint<32> tmp_123 = q_add_sign_113(arg_0, tmp_112);  // q_add_sign
    return tmp_123;
}
ap_uint<31> q_to_uq_125(ap_uint<32> arg_0) {  // q_to_uq
    const ap_uint<31> tmp_126 = ap_uint<31>(arg_0);  // basic_identity
    return tmp_126;
}
ap_uint<5> lzc_129(ap_uint<31> arg_0) {  // lzc
    const ap_uint<1> tmp_130 = ap_uint<1>(((arg_0 >> 30) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_131 = ap_uint<1>((~tmp_130));  // basic_invert
    const ap_uint<1> tmp_132 = ap_uint<1>((ap_uint<1>(1) & tmp_131));  // basic_and
    const ap_uint<5> tmp_133 = ap_uint<5>((ap_uint<5>(0) + tmp_132));  // basic_add
    const ap_uint<1> tmp_134 = ap_uint<1>(((arg_0 >> 29) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_135 = ap_uint<1>((~tmp_134));  // basic_invert
    const ap_uint<1> tmp_136 = ap_uint<1>((tmp_132 & tmp_135));  // basic_and
    const ap_uint<5> tmp_137 = ap_uint<5>((tmp_133 + tmp_136));  // basic_add
    const ap_uint<1> tmp_138 = ap_uint<1>(((arg_0 >> 28) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_139 = ap_uint<1>((~tmp_138));  // basic_invert
    const ap_uint<1> tmp_140 = ap_uint<1>((tmp_136 & tmp_139));  // basic_and
    const ap_uint<5> tmp_141 = ap_uint<5>((tmp_137 + tmp_140));  // basic_add
    const ap_uint<1> tmp_142 = ap_uint<1>(((arg_0 >> 27) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_143 = ap_uint<1>((~tmp_142));  // basic_invert
    const ap_uint<1> tmp_144 = ap_uint<1>((tmp_140 & tmp_143));  // basic_and
    const ap_uint<5> tmp_145 = ap_uint<5>((tmp_141 + tmp_144));  // basic_add
    const ap_uint<1> tmp_146 = ap_uint<1>(((arg_0 >> 26) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_147 = ap_uint<1>((~tmp_146));  // basic_invert
    const ap_uint<1> tmp_148 = ap_uint<1>((tmp_144 & tmp_147));  // basic_and
    const ap_uint<5> tmp_149 = ap_uint<5>((tmp_145 + tmp_148));  // basic_add
    const ap_uint<1> tmp_150 = ap_uint<1>(((arg_0 >> 25) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_151 = ap_uint<1>((~tmp_150));  // basic_invert
    const ap_uint<1> tmp_152 = ap_uint<1>((tmp_148 & tmp_151));  // basic_and
    const ap_uint<5> tmp_153 = ap_uint<5>((tmp_149 + tmp_152));  // basic_add
    const ap_uint<1> tmp_154 = ap_uint<1>(((arg_0 >> 24) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_155 = ap_uint<1>((~tmp_154));  // basic_invert
    const ap_uint<1> tmp_156 = ap_uint<1>((tmp_152 & tmp_155));  // basic_and
    const ap_uint<5> tmp_157 = ap_uint<5>((tmp_153 + tmp_156));  // basic_add
    const ap_uint<1> tmp_158 = ap_uint<1>(((arg_0 >> 23) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_159 = ap_uint<1>((~tmp_158));  // basic_invert
    const ap_uint<1> tmp_160 = ap_uint<1>((tmp_156 & tmp_159));  // basic_and
    const ap_uint<5> tmp_161 = ap_uint<5>((tmp_157 + tmp_160));  // basic_add
    const ap_uint<1> tmp_162 = ap_uint<1>(((arg_0 >> 22) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_163 = ap_uint<1>((~tmp_162));  // basic_invert
    const ap_uint<1> tmp_164 = ap_uint<1>((tmp_160 & tmp_163));  // basic_and
    const ap_uint<5> tmp_165 = ap_uint<5>((tmp_161 + tmp_164));  // basic_add
    const ap_uint<1> tmp_166 = ap_uint<1>(((arg_0 >> 21) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_167 = ap_uint<1>((~tmp_166));  // basic_invert
    const ap_uint<1> tmp_168 = ap_uint<1>((tmp_164 & tmp_167));  // basic_and
    const ap_uint<5> tmp_169 = ap_uint<5>((tmp_165 + tmp_168));  // basic_add
    const ap_uint<1> tmp_170 = ap_uint<1>(((arg_0 >> 20) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_171 = ap_uint<1>((~tmp_170));  // basic_invert
    const ap_uint<1> tmp_172 = ap_uint<1>((tmp_168 & tmp_171));  // basic_and
    const ap_uint<5> tmp_173 = ap_uint<5>((tmp_169 + tmp_172));  // basic_add
    const ap_uint<1> tmp_174 = ap_uint<1>(((arg_0 >> 19) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_175 = ap_uint<1>((~tmp_174));  // basic_invert
    const ap_uint<1> tmp_176 = ap_uint<1>((tmp_172 & tmp_175));  // basic_and
    const ap_uint<5> tmp_177 = ap_uint<5>((tmp_173 + tmp_176));  // basic_add
    const ap_uint<1> tmp_178 = ap_uint<1>(((arg_0 >> 18) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_179 = ap_uint<1>((~tmp_178));  // basic_invert
    const ap_uint<1> tmp_180 = ap_uint<1>((tmp_176 & tmp_179));  // basic_and
    const ap_uint<5> tmp_181 = ap_uint<5>((tmp_177 + tmp_180));  // basic_add
    const ap_uint<1> tmp_182 = ap_uint<1>(((arg_0 >> 17) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_183 = ap_uint<1>((~tmp_182));  // basic_invert
    const ap_uint<1> tmp_184 = ap_uint<1>((tmp_180 & tmp_183));  // basic_and
    const ap_uint<5> tmp_185 = ap_uint<5>((tmp_181 + tmp_184));  // basic_add
    const ap_uint<1> tmp_186 = ap_uint<1>(((arg_0 >> 16) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_187 = ap_uint<1>((~tmp_186));  // basic_invert
    const ap_uint<1> tmp_188 = ap_uint<1>((tmp_184 & tmp_187));  // basic_and
    const ap_uint<5> tmp_189 = ap_uint<5>((tmp_185 + tmp_188));  // basic_add
    const ap_uint<1> tmp_190 = ap_uint<1>(((arg_0 >> 15) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_191 = ap_uint<1>((~tmp_190));  // basic_invert
    const ap_uint<1> tmp_192 = ap_uint<1>((tmp_188 & tmp_191));  // basic_and
    const ap_uint<5> tmp_193 = ap_uint<5>((tmp_189 + tmp_192));  // basic_add
    const ap_uint<1> tmp_194 = ap_uint<1>(((arg_0 >> 14) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_195 = ap_uint<1>((~tmp_194));  // basic_invert
    const ap_uint<1> tmp_196 = ap_uint<1>((tmp_192 & tmp_195));  // basic_and
    const ap_uint<5> tmp_197 = ap_uint<5>((tmp_193 + tmp_196));  // basic_add
    const ap_uint<1> tmp_198 = ap_uint<1>(((arg_0 >> 13) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_199 = ap_uint<1>((~tmp_198));  // basic_invert
    const ap_uint<1> tmp_200 = ap_uint<1>((tmp_196 & tmp_199));  // basic_and
    const ap_uint<5> tmp_201 = ap_uint<5>((tmp_197 + tmp_200));  // basic_add
    const ap_uint<1> tmp_202 = ap_uint<1>(((arg_0 >> 12) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_203 = ap_uint<1>((~tmp_202));  // basic_invert
    const ap_uint<1> tmp_204 = ap_uint<1>((tmp_200 & tmp_203));  // basic_and
    const ap_uint<5> tmp_205 = ap_uint<5>((tmp_201 + tmp_204));  // basic_add
    const ap_uint<1> tmp_206 = ap_uint<1>(((arg_0 >> 11) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_207 = ap_uint<1>((~tmp_206));  // basic_invert
    const ap_uint<1> tmp_208 = ap_uint<1>((tmp_204 & tmp_207));  // basic_and
    const ap_uint<5> tmp_209 = ap_uint<5>((tmp_205 + tmp_208));  // basic_add
    const ap_uint<1> tmp_210 = ap_uint<1>(((arg_0 >> 10) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_211 = ap_uint<1>((~tmp_210));  // basic_invert
    const ap_uint<1> tmp_212 = ap_uint<1>((tmp_208 & tmp_211));  // basic_and
    const ap_uint<5> tmp_213 = ap_uint<5>((tmp_209 + tmp_212));  // basic_add
    const ap_uint<1> tmp_214 = ap_uint<1>(((arg_0 >> 9) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_215 = ap_uint<1>((~tmp_214));  // basic_invert
    const ap_uint<1> tmp_216 = ap_uint<1>((tmp_212 & tmp_215));  // basic_and
    const ap_uint<5> tmp_217 = ap_uint<5>((tmp_213 + tmp_216));  // basic_add
    const ap_uint<1> tmp_218 = ap_uint<1>(((arg_0 >> 8) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_219 = ap_uint<1>((~tmp_218));  // basic_invert
    const ap_uint<1> tmp_220 = ap_uint<1>((tmp_216 & tmp_219));  // basic_and
    const ap_uint<5> tmp_221 = ap_uint<5>((tmp_217 + tmp_220));  // basic_add
    const ap_uint<1> tmp_222 = ap_uint<1>(((arg_0 >> 7) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_223 = ap_uint<1>((~tmp_222));  // basic_invert
    const ap_uint<1> tmp_224 = ap_uint<1>((tmp_220 & tmp_223));  // basic_and
    const ap_uint<5> tmp_225 = ap_uint<5>((tmp_221 + tmp_224));  // basic_add
    const ap_uint<1> tmp_226 = ap_uint<1>(((arg_0 >> 6) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_227 = ap_uint<1>((~tmp_226));  // basic_invert
    const ap_uint<1> tmp_228 = ap_uint<1>((tmp_224 & tmp_227));  // basic_and
    const ap_uint<5> tmp_229 = ap_uint<5>((tmp_225 + tmp_228));  // basic_add
    const ap_uint<1> tmp_230 = ap_uint<1>(((arg_0 >> 5) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_231 = ap_uint<1>((~tmp_230));  // basic_invert
    const ap_uint<1> tmp_232 = ap_uint<1>((tmp_228 & tmp_231));  // basic_and
    const ap_uint<5> tmp_233 = ap_uint<5>((tmp_229 + tmp_232));  // basic_add
    const ap_uint<1> tmp_234 = ap_uint<1>(((arg_0 >> 4) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_235 = ap_uint<1>((~tmp_234));  // basic_invert
    const ap_uint<1> tmp_236 = ap_uint<1>((tmp_232 & tmp_235));  // basic_and
    const ap_uint<5> tmp_237 = ap_uint<5>((tmp_233 + tmp_236));  // basic_add
    const ap_uint<1> tmp_238 = ap_uint<1>(((arg_0 >> 3) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_239 = ap_uint<1>((~tmp_238));  // basic_invert
    const ap_uint<1> tmp_240 = ap_uint<1>((tmp_236 & tmp_239));  // basic_and
    const ap_uint<5> tmp_241 = ap_uint<5>((tmp_237 + tmp_240));  // basic_add
    const ap_uint<1> tmp_242 = ap_uint<1>(((arg_0 >> 2) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_243 = ap_uint<1>((~tmp_242));  // basic_invert
    const ap_uint<1> tmp_244 = ap_uint<1>((tmp_240 & tmp_243));  // basic_and
    const ap_uint<5> tmp_245 = ap_uint<5>((tmp_241 + tmp_244));  // basic_add
    const ap_uint<1> tmp_246 = ap_uint<1>(((arg_0 >> 1) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_247 = ap_uint<1>((~tmp_246));  // basic_invert
    const ap_uint<1> tmp_248 = ap_uint<1>((tmp_244 & tmp_247));  // basic_and
    const ap_uint<5> tmp_249 = ap_uint<5>((tmp_245 + tmp_248));  // basic_add
    const ap_uint<1> tmp_250 = ap_uint<1>(((arg_0 >> 0) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_251 = ap_uint<1>((~tmp_250));  // basic_invert
    const ap_uint<1> tmp_252 = ap_uint<1>((tmp_248 & tmp_251));  // basic_and
    const ap_uint<5> tmp_253 = ap_uint<5>((tmp_249 + tmp_252));  // basic_add
    return tmp_253;
}
std::tuple<ap_uint<4>, ap_uint<4>> uq_aligner_257(ap_uint<3> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<4> tmp_258 = ap_uint<4>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<4> tmp_259 = ap_uint<4>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_260 = std::tuple<ap_uint<4>, ap_uint<4>>(std::make_tuple(tmp_258, tmp_259));  // basic_tuple_maker_2
    return tmp_260;
}
ap_uint<4> uq_add_256(ap_uint<3> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<4>, ap_uint<4>> tmp_261 = uq_aligner_257(arg_0, arg_1);  // uq_aligner
    const ap_uint<4> tmp_262 = ap_uint<4>(std::get<0>(tmp_261));  // basic_get_item_0
    const ap_uint<4> tmp_263 = ap_uint<4>(std::get<1>(tmp_261));  // basic_get_item_1
    const ap_uint<4> tmp_264 = ap_uint<4>((tmp_262 + tmp_263));  // basic_add
    return tmp_264;
}
ap_uint<6> uq_to_q_255(ap_uint<5> arg_0) {  // uq_to_q
    const ap_uint<4> tmp_265 = uq_add_256(ap_uint<3>(5), ap_uint<1>(1));  // uq_add
    const ap_uint<6> tmp_266 = ap_uint<6>(0);  // q_alloc
    const ap_uint<6> tmp_267 = ap_uint<6>(arg_0);  // basic_identity
    return tmp_267;
}
std::tuple<ap_uint<3>, ap_uint<3>> uq_aligner_271(ap_uint<2> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<3> tmp_272 = ap_uint<3>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<3> tmp_273 = ap_uint<3>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_274 = std::tuple<ap_uint<3>, ap_uint<3>>(std::make_tuple(tmp_272, tmp_273));  // basic_tuple_maker_2
    return tmp_274;
}
ap_uint<3> uq_add_270(ap_uint<2> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<3>, ap_uint<3>> tmp_275 = uq_aligner_271(arg_0, arg_1);  // uq_aligner
    const ap_uint<3> tmp_276 = ap_uint<3>(std::get<0>(tmp_275));  // basic_get_item_0
    const ap_uint<3> tmp_277 = ap_uint<3>(std::get<1>(tmp_275));  // basic_get_item_1
    const ap_uint<3> tmp_278 = ap_uint<3>((tmp_276 + tmp_277));  // basic_add
    return tmp_278;
}
ap_uint<3> uq_to_q_269(ap_uint<2> arg_0) {  // uq_to_q
    const ap_uint<3> tmp_279 = uq_add_270(ap_uint<2>(2), ap_uint<1>(1));  // uq_add
    const ap_uint<3> tmp_280 = ap_uint<3>(0);  // q_alloc
    const ap_uint<3> tmp_281 = ap_uint<3>(arg_0);  // basic_identity
    return tmp_281;
}
ap_uint<1> q_sign_bit_287(ap_uint<6> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_288 = ap_uint<1>(((arg_0 >> 5) & ap_uint<1>(1)));  // basic_select
    return tmp_288;
}
ap_uint<7> q_sign_extend_286(ap_uint<6> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_289 = q_sign_bit_287(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_290 = ap_uint<2>((tmp_289 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_291 = ap_uint<1>((tmp_290 - tmp_289));  // basic_sub
    const ap_uint<7> tmp_292 = ap_uint<7>(0);  // q_alloc
    const ap_uint<7> tmp_293 = ap_uint<7>(((tmp_291 << 6) | arg_0));  // basic_concat
    return tmp_293;
}
ap_uint<1> q_sign_bit_297(ap_uint<3> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_298 = ap_uint<1>(((arg_0 >> 2) & ap_uint<1>(1)));  // basic_select
    return tmp_298;
}
ap_uint<7> q_sign_extend_296(ap_uint<3> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_299 = q_sign_bit_297(arg_0);  // q_sign_bit
    const ap_uint<5> tmp_300 = ap_uint<5>((tmp_299 << ap_uint<3>(4)));  // basic_lshift
    const ap_uint<4> tmp_301 = ap_uint<4>((tmp_300 - tmp_299));  // basic_sub
    const ap_uint<7> tmp_302 = ap_uint<7>(0);  // q_alloc
    const ap_uint<7> tmp_303 = ap_uint<7>(((tmp_301 << 3) | arg_0));  // basic_concat
    return tmp_303;
}
std::tuple<ap_uint<7>, ap_uint<7>> q_aligner_284(ap_uint<6> arg_0, ap_uint<3> arg_1) {  // q_aligner
    const ap_uint<6> tmp_285 = ap_uint<6>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<7> tmp_294 = q_sign_extend_286(tmp_285);  // q_sign_extend
    const ap_uint<3> tmp_295 = ap_uint<3>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<7> tmp_304 = q_sign_extend_296(tmp_295);  // q_sign_extend
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_305 = std::tuple<ap_uint<7>, ap_uint<7>>(std::make_tuple(tmp_294, tmp_304));  // basic_tuple_maker_2
    return tmp_305;
}
ap_uint<7> q_sub_283(ap_uint<6> arg_0, ap_uint<3> arg_1) {  // q_sub
    const std::tuple<ap_uint<7>, ap_uint<7>> tmp_306 = q_aligner_284(arg_0, arg_1);  // q_aligner
    const ap_uint<7> tmp_307 = ap_uint<7>(std::get<0>(tmp_306));  // basic_get_item_0
    const ap_uint<7> tmp_308 = ap_uint<7>(std::get<1>(tmp_306));  // basic_get_item_1
    const ap_uint<7> tmp_309 = ap_uint<7>((tmp_307 - tmp_308));  // basic_sub
    return tmp_309;
}
ap_uint<1> q_sign_bit_315(ap_uint<7> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_316 = ap_uint<1>(((arg_0 >> 6) & ap_uint<1>(1)));  // basic_select
    return tmp_316;
}
ap_uint<8> q_sign_extend_314(ap_uint<7> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_317 = q_sign_bit_315(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_318 = ap_uint<2>((tmp_317 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_319 = ap_uint<1>((tmp_318 - tmp_317));  // basic_sub
    const ap_uint<8> tmp_320 = ap_uint<8>(0);  // q_alloc
    const ap_uint<8> tmp_321 = ap_uint<8>(((tmp_319 << 7) | arg_0));  // basic_concat
    return tmp_321;
}
ap_uint<1> q_sign_bit_325(ap_uint<2> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_326 = ap_uint<1>(((arg_0 >> 1) & ap_uint<1>(1)));  // basic_select
    return tmp_326;
}
ap_uint<8> q_sign_extend_324(ap_uint<2> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_327 = q_sign_bit_325(arg_0);  // q_sign_bit
    const ap_uint<7> tmp_328 = ap_uint<7>((tmp_327 << ap_uint<3>(6)));  // basic_lshift
    const ap_uint<6> tmp_329 = ap_uint<6>((tmp_328 - tmp_327));  // basic_sub
    const ap_uint<8> tmp_330 = ap_uint<8>(0);  // q_alloc
    const ap_uint<8> tmp_331 = ap_uint<8>(((tmp_329 << 2) | arg_0));  // basic_concat
    return tmp_331;
}
std::tuple<ap_uint<8>, ap_uint<8>> q_aligner_312(ap_uint<7> arg_0, ap_uint<2> arg_1) {  // q_aligner
    const ap_uint<7> tmp_313 = ap_uint<7>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_322 = q_sign_extend_314(tmp_313);  // q_sign_extend
    const ap_uint<2> tmp_323 = ap_uint<2>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<8> tmp_332 = q_sign_extend_324(tmp_323);  // q_sign_extend
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_333 = std::tuple<ap_uint<8>, ap_uint<8>>(std::make_tuple(tmp_322, tmp_332));  // basic_tuple_maker_2
    return tmp_333;
}
ap_uint<8> q_add_311(ap_uint<7> arg_0, ap_uint<2> arg_1) {  // q_add
    const std::tuple<ap_uint<8>, ap_uint<8>> tmp_334 = q_aligner_312(arg_0, arg_1);  // q_aligner
    const ap_uint<8> tmp_335 = ap_uint<8>(std::get<0>(tmp_334));  // basic_get_item_0
    const ap_uint<8> tmp_336 = ap_uint<8>(std::get<1>(tmp_334));  // basic_get_item_1
    const ap_uint<8> tmp_337 = ap_uint<8>((tmp_335 + tmp_336));  // basic_add
    return tmp_337;
}
ap_uint<1> q_sign_bit_339(ap_uint<8> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_340 = ap_uint<1>(((arg_0 >> 7) & ap_uint<1>(1)));  // basic_select
    return tmp_340;
}
ap_uint<32> uq_resize_342(ap_uint<31> arg_0) {  // uq_resize
    const ap_uint<32> tmp_343 = ap_uint<32>((arg_0 << ap_uint<1>(1)));  // basic_lshift
    return tmp_343;
}
ap_uint<8> q_neg_348(ap_uint<8> arg_0) {  // q_neg
    const ap_uint<1> tmp_349 = ap_uint<1>((arg_0 == 128));  // _q_is_min_val
    const ap_uint<8> tmp_350 = ap_uint<8>((~arg_0));  // basic_invert
    const ap_uint<8> tmp_351 = ap_uint<8>((tmp_350 + ap_uint<1>(1)));  // basic_add
    const ap_uint<8> tmp_352 = ap_uint<8>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<8> tmp_353 = ap_uint<8>((~tmp_352));  // basic_invert
    const ap_uint<8> tmp_354 = ap_uint<8>((tmp_349 ? tmp_353 : tmp_351));  // basic_mux_2_1
    return tmp_354;
}
ap_uint<8> q_add_sign_347(ap_uint<8> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<8> tmp_355 = q_neg_348(arg_0);  // q_neg
    const ap_uint<8> tmp_356 = ap_uint<8>((arg_1 ? tmp_355 : arg_0));  // basic_mux_2_1
    return tmp_356;
}
ap_uint<8> q_abs_345(ap_uint<8> arg_0) {  // q_abs
    const ap_uint<1> tmp_346 = q_sign_bit_339(arg_0);  // q_sign_bit
    const ap_uint<8> tmp_357 = q_add_sign_347(arg_0, tmp_346);  // q_add_sign
    return tmp_357;
}
ap_uint<7> q_to_uq_359(ap_uint<8> arg_0) {  // q_to_uq
    const ap_uint<7> tmp_360 = ap_uint<7>(arg_0);  // basic_identity
    return tmp_360;
}
ap_uint<32> uq_lshift_362(ap_uint<32> arg_0, ap_uint<7> arg_1) {  // uq_lshift
    const ap_uint<32> tmp_363 = ap_uint<32>((arg_0 << arg_1));  // basic_lshift
    return tmp_363;
}
ap_uint<32> uq_rshift_365(ap_uint<32> arg_0, ap_uint<7> arg_1) {  // uq_rshift
    const ap_uint<32> tmp_366 = ap_uint<32>((arg_0 >> arg_1));  // basic_rshift
    return tmp_366;
}
ap_uint<1> q_sign_bit_373(ap_uint<9> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_374 = ap_uint<1>(((arg_0 >> 8) & ap_uint<1>(1)));  // basic_select
    return tmp_374;
}
ap_uint<10> q_sign_extend_372(ap_uint<9> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_375 = q_sign_bit_373(arg_0);  // q_sign_bit
    const ap_uint<2> tmp_376 = ap_uint<2>((tmp_375 << ap_uint<1>(1)));  // basic_lshift
    const ap_uint<1> tmp_377 = ap_uint<1>((tmp_376 - tmp_375));  // basic_sub
    const ap_uint<10> tmp_378 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_379 = ap_uint<10>(((tmp_377 << 9) | arg_0));  // basic_concat
    return tmp_379;
}
ap_uint<10> q_sign_extend_382(ap_uint<8> arg_0) {  // q_sign_extend
    const ap_uint<1> tmp_383 = q_sign_bit_339(arg_0);  // q_sign_bit
    const ap_uint<3> tmp_384 = ap_uint<3>((tmp_383 << ap_uint<2>(2)));  // basic_lshift
    const ap_uint<2> tmp_385 = ap_uint<2>((tmp_384 - tmp_383));  // basic_sub
    const ap_uint<10> tmp_386 = ap_uint<10>(0);  // q_alloc
    const ap_uint<10> tmp_387 = ap_uint<10>(((tmp_385 << 8) | arg_0));  // basic_concat
    return tmp_387;
}
std::tuple<ap_uint<10>, ap_uint<10>> q_aligner_370(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_aligner
    const ap_uint<9> tmp_371 = ap_uint<9>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_380 = q_sign_extend_372(tmp_371);  // q_sign_extend
    const ap_uint<8> tmp_381 = ap_uint<8>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_388 = q_sign_extend_382(tmp_381);  // q_sign_extend
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_389 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(tmp_380, tmp_388));  // basic_tuple_maker_2
    return tmp_389;
}
ap_uint<10> q_sub_369(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_sub
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_390 = q_aligner_370(arg_0, arg_1);  // q_aligner
    const ap_uint<10> tmp_391 = ap_uint<10>(std::get<0>(tmp_390));  // basic_get_item_0
    const ap_uint<10> tmp_392 = ap_uint<10>(std::get<1>(tmp_390));  // basic_get_item_1
    const ap_uint<10> tmp_393 = ap_uint<10>((tmp_391 - tmp_392));  // basic_sub
    return tmp_393;
}
ap_uint<10> q_add_395(ap_uint<9> arg_0, ap_uint<8> arg_1) {  // q_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_396 = q_aligner_370(arg_0, arg_1);  // q_aligner
    const ap_uint<10> tmp_397 = ap_uint<10>(std::get<0>(tmp_396));  // basic_get_item_0
    const ap_uint<10> tmp_398 = ap_uint<10>(std::get<1>(tmp_396));  // basic_get_item_1
    const ap_uint<10> tmp_399 = ap_uint<10>((tmp_397 + tmp_398));  // basic_add
    return tmp_399;
}
std::tuple<ap_uint<31>, ap_uint<10>> fp32_normalize_128(ap_uint<31> arg_0, ap_uint<9> arg_1) {  // fp32_normalize
    const ap_uint<5> tmp_254 = lzc_129(arg_0);  // lzc
    const ap_uint<6> tmp_268 = uq_to_q_255(tmp_254);  // uq_to_q
    const ap_uint<3> tmp_282 = uq_to_q_269(ap_uint<2>(2));  // uq_to_q
    const ap_uint<7> tmp_310 = q_sub_283(tmp_268, tmp_282);  // q_sub
    const ap_uint<8> tmp_338 = q_add_311(tmp_310, ap_uint<2>(1));  // q_add
    const ap_uint<1> tmp_341 = q_sign_bit_339(tmp_338);  // q_sign_bit
    const ap_uint<32> tmp_344 = uq_resize_342(arg_0);  // uq_resize
    const ap_uint<8> tmp_358 = q_abs_345(tmp_338);  // q_abs
    const ap_uint<7> tmp_361 = q_to_uq_359(tmp_358);  // q_to_uq
    const ap_uint<32> tmp_364 = uq_lshift_362(tmp_344, tmp_361);  // uq_lshift
    const ap_uint<32> tmp_367 = uq_rshift_365(tmp_344, tmp_361);  // uq_rshift
    const ap_uint<31> tmp_368 = ap_uint<31>((tmp_341 ? tmp_367 : tmp_364));  // basic_mux_2_1
    const ap_uint<10> tmp_394 = q_sub_369(arg_1, tmp_358);  // q_sub
    const ap_uint<10> tmp_400 = q_add_395(arg_1, tmp_358);  // q_add
    const ap_uint<10> tmp_401 = ap_uint<10>((tmp_341 ? tmp_400 : tmp_394));  // basic_mux_2_1
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_402 = std::tuple<ap_uint<31>, ap_uint<10>>(std::make_tuple(tmp_368, tmp_401));  // basic_tuple_maker_2
    return tmp_402;
}
ap_uint<1> q_is_zero_408(ap_uint<10> arg_0) {  // q_is_zero
    const ap_uint<1> tmp_409 = ap_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_410 = ap_uint<1>((~tmp_409));  // basic_invert
    return tmp_410;
}
ap_uint<1> q_sign_bit_412(ap_uint<10> arg_0) {  // q_sign_bit
    const ap_uint<1> tmp_413 = ap_uint<1>(((arg_0 >> 9) & ap_uint<1>(1)));  // basic_select
    return tmp_413;
}
ap_uint<10> q_neg_419(ap_uint<10> arg_0) {  // q_neg
    const ap_uint<1> tmp_420 = ap_uint<1>((arg_0 == 512));  // _q_is_min_val
    const ap_uint<10> tmp_421 = ap_uint<10>((~arg_0));  // basic_invert
    const ap_uint<10> tmp_422 = ap_uint<10>((tmp_421 + ap_uint<1>(1)));  // basic_add
    const ap_uint<10> tmp_423 = ap_uint<10>((arg_0 ^ arg_0));  // basic_xor
    const ap_uint<10> tmp_424 = ap_uint<10>((~tmp_423));  // basic_invert
    const ap_uint<10> tmp_425 = ap_uint<10>((tmp_420 ? tmp_424 : tmp_422));  // basic_mux_2_1
    return tmp_425;
}
ap_uint<10> q_add_sign_418(ap_uint<10> arg_0, ap_uint<1> arg_1) {  // q_add_sign
    const ap_uint<10> tmp_426 = q_neg_419(arg_0);  // q_neg
    const ap_uint<10> tmp_427 = ap_uint<10>((arg_1 ? tmp_426 : arg_0));  // basic_mux_2_1
    return tmp_427;
}
ap_uint<10> q_abs_416(ap_uint<10> arg_0) {  // q_abs
    const ap_uint<1> tmp_417 = q_sign_bit_412(arg_0);  // q_sign_bit
    const ap_uint<10> tmp_428 = q_add_sign_418(arg_0, tmp_417);  // q_add_sign
    return tmp_428;
}
ap_uint<9> q_to_uq_430(ap_uint<10> arg_0) {  // q_to_uq
    const ap_uint<9> tmp_431 = ap_uint<9>(arg_0);  // basic_identity
    return tmp_431;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_434(ap_uint<1> arg_0, ap_uint<9> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_435 = ap_uint<10>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_436 = ap_uint<10>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_437 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(tmp_435, tmp_436));  // basic_tuple_maker_2
    return tmp_437;
}
ap_uint<10> uq_add_433(ap_uint<1> arg_0, ap_uint<9> arg_1) {  // uq_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_438 = uq_aligner_434(arg_0, arg_1);  // uq_aligner
    const ap_uint<10> tmp_439 = ap_uint<10>(std::get<0>(tmp_438));  // basic_get_item_0
    const ap_uint<10> tmp_440 = ap_uint<10>(std::get<1>(tmp_438));  // basic_get_item_1
    const ap_uint<10> tmp_441 = ap_uint<10>((tmp_439 + tmp_440));  // basic_add
    return tmp_441;
}
ap_uint<41> uq_rshift_444(ap_uint<41> arg_0, ap_uint<10> arg_1) {  // uq_rshift
    const ap_uint<41> tmp_445 = ap_uint<41>((arg_0 >> arg_1));  // basic_rshift
    return tmp_445;
}
std::tuple<ap_uint<41>, ap_uint<9>> fp32_classify_406(ap_uint<31> arg_0, ap_uint<10> arg_1) {  // fp32_classify
    const ap_uint<41> tmp_407 = ap_uint<41>((arg_0 << ap_uint<4>(10)));  // basic_lshift
    const ap_uint<1> tmp_411 = q_is_zero_408(arg_1);  // q_is_zero
    const ap_uint<1> tmp_414 = q_sign_bit_412(arg_1);  // q_sign_bit
    const ap_uint<1> tmp_415 = ap_uint<1>((tmp_411 | tmp_414));  // basic_or
    const ap_uint<10> tmp_429 = q_abs_416(arg_1);  // q_abs
    const ap_uint<9> tmp_432 = q_to_uq_430(tmp_429);  // q_to_uq
    const ap_uint<10> tmp_442 = uq_add_433(ap_uint<1>(1), tmp_432);  // uq_add
    const ap_uint<10> tmp_443 = ap_uint<10>((tmp_415 ? tmp_442 : ap_uint<1>(0)));  // basic_mux_2_1
    const ap_uint<41> tmp_446 = uq_rshift_444(tmp_407, tmp_443);  // uq_rshift
    const ap_uint<9> tmp_447 = ap_uint<9>((tmp_415 ? ap_uint<1>(0) : tmp_432));  // basic_mux_2_1
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_448 = std::tuple<ap_uint<41>, ap_uint<9>>(std::make_tuple(tmp_446, tmp_447));  // basic_tuple_maker_2
    return tmp_448;
}
ap_uint<40> drop_implicit_bit_451(ap_uint<41> arg_0) {  // drop_implicit_bit
    const ap_uint<40> tmp_452 = ap_uint<40>(((arg_0 >> 0) & ap_uint<40>(1099511627775)));  // basic_select
    return tmp_452;
}
ap_uint<1> uq_is_zero_456(ap_uint<9> arg_0) {  // uq_is_zero
    const ap_uint<1> tmp_457 = ap_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_458 = ap_uint<1>((~tmp_457));  // basic_invert
    return tmp_458;
}
ap_uint<23> uq_resize_460(ap_uint<40> arg_0) {  // uq_resize
    const ap_uint<23> tmp_461 = ap_uint<23>((arg_0 >> ap_uint<5>(17)));  // basic_rshift
    return tmp_461;
}
ap_uint<23> uq_RNE_IEEE_463(ap_uint<40> arg_0) {  // uq_RNE_IEEE
    const ap_uint<1> tmp_464 = ap_uint<1>(((arg_0 >> 16) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_465 = ap_uint<1>(((arg_0 >> 15) & ap_uint<1>(1)));  // basic_select
    const ap_uint<15> tmp_466 = ap_uint<15>(((arg_0 >> 0) & ap_uint<15>(32767)));  // basic_select
    const ap_uint<1> tmp_467 = ap_uint<1>((tmp_466 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_468 = ap_uint<1>((tmp_465 | tmp_467));  // basic_or
    const ap_uint<1> tmp_469 = ap_uint<1>(((arg_0 >> 17) & ap_uint<1>(1)));  // basic_select
    const ap_uint<1> tmp_470 = ap_uint<1>((tmp_468 | tmp_469));  // basic_or
    const ap_uint<1> tmp_471 = ap_uint<1>((tmp_464 & tmp_470));  // basic_and
    const ap_uint<23> tmp_472 = ap_uint<23>(tmp_471);  // basic_identity
    return tmp_472;
}
std::tuple<ap_uint<24>, ap_uint<24>> uq_aligner_475(ap_uint<23> arg_0, ap_uint<23> arg_1) {  // uq_aligner
    const ap_uint<24> tmp_476 = ap_uint<24>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<24> tmp_477 = ap_uint<24>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_478 = std::tuple<ap_uint<24>, ap_uint<24>>(std::make_tuple(tmp_476, tmp_477));  // basic_tuple_maker_2
    return tmp_478;
}
ap_uint<24> uq_add_474(ap_uint<23> arg_0, ap_uint<23> arg_1) {  // uq_add
    const std::tuple<ap_uint<24>, ap_uint<24>> tmp_479 = uq_aligner_475(arg_0, arg_1);  // uq_aligner
    const ap_uint<24> tmp_480 = ap_uint<24>(std::get<0>(tmp_479));  // basic_get_item_0
    const ap_uint<24> tmp_481 = ap_uint<24>(std::get<1>(tmp_479));  // basic_get_item_1
    const ap_uint<24> tmp_482 = ap_uint<24>((tmp_480 + tmp_481));  // basic_add
    return tmp_482;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_486(ap_uint<9> arg_0, ap_uint<1> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_487 = ap_uint<10>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_488 = ap_uint<10>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_489 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(tmp_487, tmp_488));  // basic_tuple_maker_2
    return tmp_489;
}
ap_uint<10> uq_add_485(ap_uint<9> arg_0, ap_uint<1> arg_1) {  // uq_add
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_490 = uq_aligner_486(arg_0, arg_1);  // uq_aligner
    const ap_uint<10> tmp_491 = ap_uint<10>(std::get<0>(tmp_490));  // basic_get_item_0
    const ap_uint<10> tmp_492 = ap_uint<10>(std::get<1>(tmp_490));  // basic_get_item_1
    const ap_uint<10> tmp_493 = ap_uint<10>((tmp_491 + tmp_492));  // basic_add
    return tmp_493;
}
std::tuple<ap_uint<23>, ap_uint<10>> fp32_round_455(ap_uint<40> arg_0, ap_uint<9> arg_1) {  // fp32_round
    const ap_uint<1> tmp_459 = uq_is_zero_456(arg_1);  // uq_is_zero
    const ap_uint<23> tmp_462 = uq_resize_460(arg_0);  // uq_resize
    const ap_uint<23> tmp_473 = uq_RNE_IEEE_463(arg_0);  // uq_RNE_IEEE
    const ap_uint<24> tmp_483 = uq_add_474(tmp_462, tmp_473);  // uq_add
    const ap_uint<1> tmp_484 = ap_uint<1>(((tmp_483 >> 23) & ap_uint<1>(1)));  // basic_select
    const ap_uint<10> tmp_494 = uq_add_485(arg_1, tmp_484);  // uq_add
    const ap_uint<1> tmp_495 = ap_uint<1>((tmp_494 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_496 = ap_uint<1>((tmp_459 & tmp_495));  // basic_and
    const ap_uint<23> tmp_497 = ap_uint<23>((tmp_483 >> ap_uint<1>(1)));  // basic_rshift
    const ap_uint<23> tmp_498 = ap_uint<23>((tmp_484 ? tmp_497 : tmp_483));  // basic_mux_2_1
    const ap_uint<23> tmp_499 = ap_uint<23>((tmp_496 ? ap_uint<1>(0) : tmp_498));  // basic_mux_2_1
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_500 = std::tuple<ap_uint<23>, ap_uint<10>>(std::make_tuple(tmp_499, tmp_494));  // basic_tuple_maker_2
    return tmp_500;
}
std::tuple<ap_uint<10>, ap_uint<10>> uq_aligner_506(ap_uint<10> arg_0, ap_uint<8> arg_1) {  // uq_aligner
    const ap_uint<10> tmp_507 = ap_uint<10>((arg_0 << ap_uint<1>(0)));  // basic_lshift
    const ap_uint<10> tmp_508 = ap_uint<10>((arg_1 << ap_uint<1>(0)));  // basic_lshift
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_509 = std::tuple<ap_uint<10>, ap_uint<10>>(std::make_tuple(tmp_507, tmp_508));  // basic_tuple_maker_2
    return tmp_509;
}
ap_uint<10> uq_min_505(ap_uint<10> arg_0, ap_uint<8> arg_1) {  // uq_min
    const std::tuple<ap_uint<10>, ap_uint<10>> tmp_510 = uq_aligner_506(arg_0, arg_1);  // uq_aligner
    const ap_uint<10> tmp_511 = ap_uint<10>(std::get<0>(tmp_510));  // basic_get_item_0
    const ap_uint<10> tmp_512 = ap_uint<10>(std::get<1>(tmp_510));  // basic_get_item_1
    const ap_uint<10> tmp_513 = ap_uint<10>((tmp_511 < tmp_512 ? tmp_511 : tmp_512));  // basic_min
    return tmp_513;
}
ap_uint<23> fraction_to_bits_518(ap_uint<23> arg_0) {  // fraction_to_bits
    const ap_uint<23> tmp_519 = ap_uint<23>(arg_0);  // basic_identity
    return tmp_519;
}
ap_uint<1> uq_is_zero_521(ap_uint<31> arg_0) {  // uq_is_zero
    const ap_uint<1> tmp_522 = ap_uint<1>((arg_0 != 0));  // basic_or_reduce
    const ap_uint<1> tmp_523 = ap_uint<1>((~tmp_522));  // basic_invert
    return tmp_523;
}
std::tuple<ap_uint<23>, ap_uint<8>> fp32_encodings_504(ap_uint<23> arg_0, ap_uint<10> arg_1, ap_uint<31> arg_2) {  // fp32_encodings
    const ap_uint<10> tmp_514 = uq_min_505(arg_1, ap_uint<8>(255));  // uq_min
    const ap_uint<8> tmp_515 = ap_uint<8>(tmp_514);  // basic_identity
    const ap_uint<1> tmp_516 = ap_uint<1>((tmp_515 == ap_uint<8>(255)));  // basic_and_reduce
    const ap_uint<23> tmp_517 = ap_uint<23>((tmp_516 ? ap_uint<1>(0) : arg_0));  // basic_mux_2_1
    const ap_uint<23> tmp_520 = fraction_to_bits_518(tmp_517);  // fraction_to_bits
    const ap_uint<1> tmp_524 = uq_is_zero_521(arg_2);  // uq_is_zero
    const ap_uint<8> tmp_525 = ap_uint<8>((tmp_524 ? ap_uint<1>(0) : tmp_515));  // basic_mux_2_1
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_526 = std::tuple<ap_uint<23>, ap_uint<8>>(std::make_tuple(tmp_520, tmp_525));  // basic_tuple_maker_2
    return tmp_526;
}
ap_uint<32> fp32_pack_530(ap_uint<1> arg_0, ap_uint<8> arg_1, ap_uint<23> arg_2) {  // fp32_pack
    const ap_uint<32> tmp_531 = ap_uint<32>(((arg_0 << 31) | (arg_1 << 23) | arg_2));  // float32_alloc
    return tmp_531;
}
ap_uint<32> encode_Float32_107(ap_uint<32> arg_0, ap_uint<9> arg_1) {  // encode_Float32
    const ap_uint<1> tmp_110 = q_sign_bit_108(arg_0);  // q_sign_bit
    const ap_uint<32> tmp_124 = q_abs_111(arg_0);  // q_abs
    const ap_uint<31> tmp_127 = q_to_uq_125(tmp_124);  // q_to_uq
    const std::tuple<ap_uint<31>, ap_uint<10>> tmp_403 = fp32_normalize_128(tmp_127, arg_1);  // fp32_normalize
    const ap_uint<31> tmp_404 = ap_uint<31>(std::get<0>(tmp_403));  // basic_get_item_0
    const ap_uint<10> tmp_405 = ap_uint<10>(std::get<1>(tmp_403));  // basic_get_item_1
    const std::tuple<ap_uint<41>, ap_uint<9>> tmp_449 = fp32_classify_406(tmp_404, tmp_405);  // fp32_classify
    const ap_uint<41> tmp_450 = ap_uint<41>(std::get<0>(tmp_449));  // basic_get_item_0
    const ap_uint<40> tmp_453 = drop_implicit_bit_451(tmp_450);  // drop_implicit_bit
    const ap_uint<9> tmp_454 = ap_uint<9>(std::get<1>(tmp_449));  // basic_get_item_1
    const std::tuple<ap_uint<23>, ap_uint<10>> tmp_501 = fp32_round_455(tmp_453, tmp_454);  // fp32_round
    const ap_uint<23> tmp_502 = ap_uint<23>(std::get<0>(tmp_501));  // basic_get_item_0
    const ap_uint<10> tmp_503 = ap_uint<10>(std::get<1>(tmp_501));  // basic_get_item_1
    const std::tuple<ap_uint<23>, ap_uint<8>> tmp_527 = fp32_encodings_504(tmp_502, tmp_503, tmp_127);  // fp32_encodings
    const ap_uint<8> tmp_528 = ap_uint<8>(std::get<1>(tmp_527));  // basic_get_item_1
    const ap_uint<23> tmp_529 = ap_uint<23>(std::get<0>(tmp_527));  // basic_get_item_0
    const ap_uint<32> tmp_532 = fp32_pack_530(tmp_110, tmp_528, tmp_529);  // fp32_pack
    return tmp_532;
}
ap_uint<32> main(ap_uint<32> arg_0, ap_uint<32> arg_1) {  // FP32_IEEE_adder
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_5 = fp32_unpack_0(arg_0);  // fp32_unpack
    const ap_uint<23> tmp_6 = ap_uint<23>(std::get<2>(tmp_5));  // basic_get_item_2
    const ap_uint<24> tmp_9 = add_implicit_bit_7(tmp_6);  // add_implicit_bit
    const ap_uint<30> tmp_12 = uq_resize_10(tmp_9);  // uq_resize
    const ap_uint<8> tmp_13 = ap_uint<8>(std::get<1>(tmp_5));  // basic_get_item_1
    const std::tuple<ap_uint<1>, ap_uint<8>, ap_uint<23>> tmp_14 = fp32_unpack_0(arg_1);  // fp32_unpack
    const ap_uint<8> tmp_15 = ap_uint<8>(std::get<1>(tmp_14));  // basic_get_item_1
    const ap_uint<8> tmp_25 = uq_max_16(tmp_13, tmp_15);  // uq_max
    const ap_uint<9> tmp_35 = uq_sub_26(tmp_25, tmp_13);  // uq_sub
    const ap_uint<30> tmp_38 = uq_rshift_36(tmp_12, tmp_35);  // uq_rshift
    const ap_uint<31> tmp_52 = uq_to_q_39(tmp_38);  // uq_to_q
    const ap_uint<1> tmp_53 = ap_uint<1>(std::get<0>(tmp_5));  // basic_get_item_0
    const ap_uint<31> tmp_64 = q_add_sign_54(tmp_52, tmp_53);  // q_add_sign
    const ap_uint<23> tmp_65 = ap_uint<23>(std::get<2>(tmp_14));  // basic_get_item_2
    const ap_uint<24> tmp_66 = add_implicit_bit_7(tmp_65);  // add_implicit_bit
    const ap_uint<30> tmp_67 = uq_resize_10(tmp_66);  // uq_resize
    const ap_uint<9> tmp_68 = uq_sub_26(tmp_25, tmp_15);  // uq_sub
    const ap_uint<30> tmp_69 = uq_rshift_36(tmp_67, tmp_68);  // uq_rshift
    const ap_uint<31> tmp_70 = uq_to_q_39(tmp_69);  // uq_to_q
    const ap_uint<1> tmp_71 = ap_uint<1>(std::get<0>(tmp_14));  // basic_get_item_0
    const ap_uint<31> tmp_72 = q_add_sign_54(tmp_70, tmp_71);  // q_add_sign
    const ap_uint<32> tmp_92 = q_add_73(tmp_64, tmp_72);  // q_add
    const ap_uint<9> tmp_106 = uq_to_q_93(tmp_25);  // uq_to_q
    const ap_uint<32> tmp_533 = encode_Float32_107(tmp_92, tmp_106);  // encode_Float32
    return tmp_533;
}


