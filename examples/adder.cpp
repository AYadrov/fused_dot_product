std::tuple<uint_fast8_t, uint_fast8_t, uint_fast32_t> fp32_unpack(uint_fast32_t arg_0) {  // fp32_unpack
    const uint_fast8_t tmp = uint_fast8_t(((arg_0 >> 31) & 1));  // _fp32_sign
    const uint_fast8_t tmp_1 = uint_fast8_t(((arg_0 >> 23) & 255));  // _fp32_exponent
    const uint_fast32_t tmp_2 = uint_fast32_t(((arg_0 >> 0) & 8388607));  // _fp32_mantissa
    const std::tuple<uint_fast8_t, uint_fast8_t, uint_fast32_t> tmp_3 = std::tuple<uint_fast8_t, uint_fast8_t, uint_fast32_t>(std::make_tuple(tmp, tmp_1, tmp_2));  // basic_tuple_maker_3
    return tmp_3;
}
uint_fast32_t add_implicit_bit(uint_fast32_t arg_0) {  // add_implicit_bit
    const uint_fast32_t tmp_6 = uint_fast32_t(((uint_fast8_t(1) << 23) | arg_0));  // basic_concat
    return tmp_6;
}
uint_fast32_t uq_resize(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_8 = uint_fast32_t((arg_0 << uint_fast8_t(6)));  // basic_lshift
    return tmp_8;
}
std::tuple<uint_fast8_t, uint_fast8_t> uq_aligner(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_aligner
    const uint_fast8_t tmp_13 = uint_fast8_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_14 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::tuple<uint_fast8_t, uint_fast8_t> tmp_15 = std::tuple<uint_fast8_t, uint_fast8_t>(std::make_tuple(tmp_13, tmp_14));  // basic_tuple_maker_2
    return tmp_15;
}
uint_fast8_t uq_max(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_max
    const std::tuple<uint_fast8_t, uint_fast8_t> tmp_16 = uq_aligner(arg_0, arg_1);  // uq_aligner
    const uint_fast8_t tmp_17 = uint_fast8_t(std::get<0>(tmp_16));  // basic_get_item_0
    const uint_fast8_t tmp_18 = uint_fast8_t(std::get<1>(tmp_16));  // basic_get_item_1
    const uint_fast8_t tmp_19 = uint_fast8_t((tmp_17 > tmp_18 ? tmp_17 : tmp_18));  // basic_max
    return tmp_19;
}
std::tuple<uint_fast16_t, uint_fast16_t> uq_aligner_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_aligner
    const uint_fast16_t tmp_21 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_22 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_23 = std::tuple<uint_fast16_t, uint_fast16_t>(std::make_tuple(tmp_21, tmp_22));  // basic_tuple_maker_2
    return tmp_23;
}
uint_fast16_t uq_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_sub
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_24 = uq_aligner_1(arg_0, arg_1);  // uq_aligner
    const uint_fast16_t tmp_25 = uint_fast16_t(std::get<0>(tmp_24));  // basic_get_item_0
    const uint_fast16_t tmp_26 = uint_fast16_t(std::get<1>(tmp_24));  // basic_get_item_1
    const uint_fast16_t tmp_27 = uint_fast16_t((tmp_25 - tmp_26));  // basic_sub
    return tmp_27;
}
uint_fast32_t uq_rshift(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_29 = uint_fast32_t((arg_0 >> arg_1));  // basic_rshift
    return tmp_29;
}
uint_fast8_t uq_add(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // uq_add
    const std::tuple<uint_fast8_t, uint_fast8_t> tmp_31 = uq_aligner(arg_0, arg_1);  // uq_aligner
    const uint_fast8_t tmp_32 = uint_fast8_t(std::get<0>(tmp_31));  // basic_get_item_0
    const uint_fast8_t tmp_33 = uint_fast8_t(std::get<1>(tmp_31));  // basic_get_item_1
    const uint_fast8_t tmp_34 = uint_fast8_t((tmp_32 + tmp_33));  // basic_add
    return tmp_34;
}
uint_fast32_t uq_to_q(uint_fast32_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_35 = uq_add(uint_fast8_t(1), uint_fast8_t(1));  // uq_add
    const uint_fast32_t tmp_36 = uint_fast32_t(0);  // q_alloc
    const uint_fast32_t tmp_37 = uint_fast32_t(arg_0);  // basic_identity
    return tmp_37;
}
uint_fast32_t q_neg(uint_fast32_t arg_0) {  // q_neg
    const uint_fast8_t tmp_40 = uint_fast8_t((arg_0 == 1073741824));  // _q_is_min_val
    const uint_fast32_t tmp_41 = uint_fast32_t((~arg_0));  // basic_invert
    const uint_fast32_t tmp_42 = uint_fast32_t((tmp_41 + uint_fast8_t(1)));  // basic_add
    const uint_fast32_t tmp_43 = uint_fast32_t((arg_0 ^ arg_0));  // basic_xor
    const uint_fast32_t tmp_44 = uint_fast32_t((~tmp_43));  // basic_invert
    const uint_fast32_t tmp_45 = uint_fast32_t((tmp_40 ? tmp_44 : tmp_42));  // basic_mux_2_1
    return tmp_45;
}
uint_fast32_t q_add_sign(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast32_t tmp_46 = q_neg(arg_0);  // q_neg
    const uint_fast32_t tmp_47 = uint_fast32_t((arg_1 ? tmp_46 : arg_0));  // basic_mux_2_1
    return tmp_47;
}
uint_fast8_t q_sign_bit(uint_fast32_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_58 = uint_fast8_t(((arg_0 >> 30) & 1));  // basic_select
    return tmp_58;
}
uint_fast32_t q_sign_extend(uint_fast32_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_59 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_60 = uint_fast8_t((tmp_59 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_61 = uint_fast8_t((tmp_60 - tmp_59));  // basic_sub
    const uint_fast32_t tmp_62 = uint_fast32_t(0);  // q_alloc
    const uint_fast32_t tmp_63 = uint_fast32_t(((tmp_61 << 31) | arg_0));  // basic_concat
    return tmp_63;
}
std::tuple<uint_fast32_t, uint_fast32_t> q_aligner(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_aligner
    const uint_fast32_t tmp_57 = uint_fast32_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast32_t tmp_64 = q_sign_extend(tmp_57);  // q_sign_extend
    const uint_fast32_t tmp_65 = uint_fast32_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast32_t tmp_66 = q_sign_extend(tmp_65);  // q_sign_extend
    const std::tuple<uint_fast32_t, uint_fast32_t> tmp_67 = std::tuple<uint_fast32_t, uint_fast32_t>(std::make_tuple(tmp_64, tmp_66));  // basic_tuple_maker_2
    return tmp_67;
}
uint_fast32_t q_add(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // q_add
    const std::tuple<uint_fast32_t, uint_fast32_t> tmp_68 = q_aligner(arg_0, arg_1);  // q_aligner
    const uint_fast32_t tmp_69 = uint_fast32_t(std::get<0>(tmp_68));  // basic_get_item_0
    const uint_fast32_t tmp_70 = uint_fast32_t(std::get<1>(tmp_68));  // basic_get_item_1
    const uint_fast32_t tmp_71 = uint_fast32_t((tmp_69 + tmp_70));  // basic_add
    return tmp_71;
}
uint_fast16_t uq_to_q_1(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_73 = uq_add(uint_fast8_t(8), uint_fast8_t(1));  // uq_add
    const uint_fast16_t tmp_74 = uint_fast16_t(0);  // q_alloc
    const uint_fast16_t tmp_75 = uint_fast16_t(arg_0);  // basic_identity
    return tmp_75;
}
uint_fast32_t q_abs(uint_fast32_t arg_0) {  // q_abs
    const uint_fast8_t tmp_78 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_79 = q_add_sign(arg_0, tmp_78);  // q_add_sign
    return tmp_79;
}
uint_fast32_t q_to_uq(uint_fast32_t arg_0) {  // q_to_uq
    const uint_fast32_t tmp_81 = uint_fast32_t(arg_0);  // basic_identity
    return tmp_81;
}
uint_fast8_t lzc(uint_fast32_t arg_0) {  // lzc
    const uint_fast8_t tmp_83 = uint_fast8_t(((arg_0 >> 30) & 1));  // basic_select
    const uint_fast8_t tmp_84 = uint_fast8_t((~tmp_83));  // basic_invert
    const uint_fast8_t tmp_85 = uint_fast8_t((uint_fast8_t(1) & tmp_84));  // basic_and
    const uint_fast8_t tmp_86 = uint_fast8_t((uint_fast8_t(0) + tmp_85));  // basic_add
    const uint_fast8_t tmp_87 = uint_fast8_t(((arg_0 >> 29) & 1));  // basic_select
    const uint_fast8_t tmp_88 = uint_fast8_t((~tmp_87));  // basic_invert
    const uint_fast8_t tmp_89 = uint_fast8_t((tmp_85 & tmp_88));  // basic_and
    const uint_fast8_t tmp_90 = uint_fast8_t((tmp_86 + tmp_89));  // basic_add
    const uint_fast8_t tmp_91 = uint_fast8_t(((arg_0 >> 28) & 1));  // basic_select
    const uint_fast8_t tmp_92 = uint_fast8_t((~tmp_91));  // basic_invert
    const uint_fast8_t tmp_93 = uint_fast8_t((tmp_89 & tmp_92));  // basic_and
    const uint_fast8_t tmp_94 = uint_fast8_t((tmp_90 + tmp_93));  // basic_add
    const uint_fast8_t tmp_95 = uint_fast8_t(((arg_0 >> 27) & 1));  // basic_select
    const uint_fast8_t tmp_96 = uint_fast8_t((~tmp_95));  // basic_invert
    const uint_fast8_t tmp_97 = uint_fast8_t((tmp_93 & tmp_96));  // basic_and
    const uint_fast8_t tmp_98 = uint_fast8_t((tmp_94 + tmp_97));  // basic_add
    const uint_fast8_t tmp_99 = uint_fast8_t(((arg_0 >> 26) & 1));  // basic_select
    const uint_fast8_t tmp_100 = uint_fast8_t((~tmp_99));  // basic_invert
    const uint_fast8_t tmp_101 = uint_fast8_t((tmp_97 & tmp_100));  // basic_and
    const uint_fast8_t tmp_102 = uint_fast8_t((tmp_98 + tmp_101));  // basic_add
    const uint_fast8_t tmp_103 = uint_fast8_t(((arg_0 >> 25) & 1));  // basic_select
    const uint_fast8_t tmp_104 = uint_fast8_t((~tmp_103));  // basic_invert
    const uint_fast8_t tmp_105 = uint_fast8_t((tmp_101 & tmp_104));  // basic_and
    const uint_fast8_t tmp_106 = uint_fast8_t((tmp_102 + tmp_105));  // basic_add
    const uint_fast8_t tmp_107 = uint_fast8_t(((arg_0 >> 24) & 1));  // basic_select
    const uint_fast8_t tmp_108 = uint_fast8_t((~tmp_107));  // basic_invert
    const uint_fast8_t tmp_109 = uint_fast8_t((tmp_105 & tmp_108));  // basic_and
    const uint_fast8_t tmp_110 = uint_fast8_t((tmp_106 + tmp_109));  // basic_add
    const uint_fast8_t tmp_111 = uint_fast8_t(((arg_0 >> 23) & 1));  // basic_select
    const uint_fast8_t tmp_112 = uint_fast8_t((~tmp_111));  // basic_invert
    const uint_fast8_t tmp_113 = uint_fast8_t((tmp_109 & tmp_112));  // basic_and
    const uint_fast8_t tmp_114 = uint_fast8_t((tmp_110 + tmp_113));  // basic_add
    const uint_fast8_t tmp_115 = uint_fast8_t(((arg_0 >> 22) & 1));  // basic_select
    const uint_fast8_t tmp_116 = uint_fast8_t((~tmp_115));  // basic_invert
    const uint_fast8_t tmp_117 = uint_fast8_t((tmp_113 & tmp_116));  // basic_and
    const uint_fast8_t tmp_118 = uint_fast8_t((tmp_114 + tmp_117));  // basic_add
    const uint_fast8_t tmp_119 = uint_fast8_t(((arg_0 >> 21) & 1));  // basic_select
    const uint_fast8_t tmp_120 = uint_fast8_t((~tmp_119));  // basic_invert
    const uint_fast8_t tmp_121 = uint_fast8_t((tmp_117 & tmp_120));  // basic_and
    const uint_fast8_t tmp_122 = uint_fast8_t((tmp_118 + tmp_121));  // basic_add
    const uint_fast8_t tmp_123 = uint_fast8_t(((arg_0 >> 20) & 1));  // basic_select
    const uint_fast8_t tmp_124 = uint_fast8_t((~tmp_123));  // basic_invert
    const uint_fast8_t tmp_125 = uint_fast8_t((tmp_121 & tmp_124));  // basic_and
    const uint_fast8_t tmp_126 = uint_fast8_t((tmp_122 + tmp_125));  // basic_add
    const uint_fast8_t tmp_127 = uint_fast8_t(((arg_0 >> 19) & 1));  // basic_select
    const uint_fast8_t tmp_128 = uint_fast8_t((~tmp_127));  // basic_invert
    const uint_fast8_t tmp_129 = uint_fast8_t((tmp_125 & tmp_128));  // basic_and
    const uint_fast8_t tmp_130 = uint_fast8_t((tmp_126 + tmp_129));  // basic_add
    const uint_fast8_t tmp_131 = uint_fast8_t(((arg_0 >> 18) & 1));  // basic_select
    const uint_fast8_t tmp_132 = uint_fast8_t((~tmp_131));  // basic_invert
    const uint_fast8_t tmp_133 = uint_fast8_t((tmp_129 & tmp_132));  // basic_and
    const uint_fast8_t tmp_134 = uint_fast8_t((tmp_130 + tmp_133));  // basic_add
    const uint_fast8_t tmp_135 = uint_fast8_t(((arg_0 >> 17) & 1));  // basic_select
    const uint_fast8_t tmp_136 = uint_fast8_t((~tmp_135));  // basic_invert
    const uint_fast8_t tmp_137 = uint_fast8_t((tmp_133 & tmp_136));  // basic_and
    const uint_fast8_t tmp_138 = uint_fast8_t((tmp_134 + tmp_137));  // basic_add
    const uint_fast8_t tmp_139 = uint_fast8_t(((arg_0 >> 16) & 1));  // basic_select
    const uint_fast8_t tmp_140 = uint_fast8_t((~tmp_139));  // basic_invert
    const uint_fast8_t tmp_141 = uint_fast8_t((tmp_137 & tmp_140));  // basic_and
    const uint_fast8_t tmp_142 = uint_fast8_t((tmp_138 + tmp_141));  // basic_add
    const uint_fast8_t tmp_143 = uint_fast8_t(((arg_0 >> 15) & 1));  // basic_select
    const uint_fast8_t tmp_144 = uint_fast8_t((~tmp_143));  // basic_invert
    const uint_fast8_t tmp_145 = uint_fast8_t((tmp_141 & tmp_144));  // basic_and
    const uint_fast8_t tmp_146 = uint_fast8_t((tmp_142 + tmp_145));  // basic_add
    const uint_fast8_t tmp_147 = uint_fast8_t(((arg_0 >> 14) & 1));  // basic_select
    const uint_fast8_t tmp_148 = uint_fast8_t((~tmp_147));  // basic_invert
    const uint_fast8_t tmp_149 = uint_fast8_t((tmp_145 & tmp_148));  // basic_and
    const uint_fast8_t tmp_150 = uint_fast8_t((tmp_146 + tmp_149));  // basic_add
    const uint_fast8_t tmp_151 = uint_fast8_t(((arg_0 >> 13) & 1));  // basic_select
    const uint_fast8_t tmp_152 = uint_fast8_t((~tmp_151));  // basic_invert
    const uint_fast8_t tmp_153 = uint_fast8_t((tmp_149 & tmp_152));  // basic_and
    const uint_fast8_t tmp_154 = uint_fast8_t((tmp_150 + tmp_153));  // basic_add
    const uint_fast8_t tmp_155 = uint_fast8_t(((arg_0 >> 12) & 1));  // basic_select
    const uint_fast8_t tmp_156 = uint_fast8_t((~tmp_155));  // basic_invert
    const uint_fast8_t tmp_157 = uint_fast8_t((tmp_153 & tmp_156));  // basic_and
    const uint_fast8_t tmp_158 = uint_fast8_t((tmp_154 + tmp_157));  // basic_add
    const uint_fast8_t tmp_159 = uint_fast8_t(((arg_0 >> 11) & 1));  // basic_select
    const uint_fast8_t tmp_160 = uint_fast8_t((~tmp_159));  // basic_invert
    const uint_fast8_t tmp_161 = uint_fast8_t((tmp_157 & tmp_160));  // basic_and
    const uint_fast8_t tmp_162 = uint_fast8_t((tmp_158 + tmp_161));  // basic_add
    const uint_fast8_t tmp_163 = uint_fast8_t(((arg_0 >> 10) & 1));  // basic_select
    const uint_fast8_t tmp_164 = uint_fast8_t((~tmp_163));  // basic_invert
    const uint_fast8_t tmp_165 = uint_fast8_t((tmp_161 & tmp_164));  // basic_and
    const uint_fast8_t tmp_166 = uint_fast8_t((tmp_162 + tmp_165));  // basic_add
    const uint_fast8_t tmp_167 = uint_fast8_t(((arg_0 >> 9) & 1));  // basic_select
    const uint_fast8_t tmp_168 = uint_fast8_t((~tmp_167));  // basic_invert
    const uint_fast8_t tmp_169 = uint_fast8_t((tmp_165 & tmp_168));  // basic_and
    const uint_fast8_t tmp_170 = uint_fast8_t((tmp_166 + tmp_169));  // basic_add
    const uint_fast8_t tmp_171 = uint_fast8_t(((arg_0 >> 8) & 1));  // basic_select
    const uint_fast8_t tmp_172 = uint_fast8_t((~tmp_171));  // basic_invert
    const uint_fast8_t tmp_173 = uint_fast8_t((tmp_169 & tmp_172));  // basic_and
    const uint_fast8_t tmp_174 = uint_fast8_t((tmp_170 + tmp_173));  // basic_add
    const uint_fast8_t tmp_175 = uint_fast8_t(((arg_0 >> 7) & 1));  // basic_select
    const uint_fast8_t tmp_176 = uint_fast8_t((~tmp_175));  // basic_invert
    const uint_fast8_t tmp_177 = uint_fast8_t((tmp_173 & tmp_176));  // basic_and
    const uint_fast8_t tmp_178 = uint_fast8_t((tmp_174 + tmp_177));  // basic_add
    const uint_fast8_t tmp_179 = uint_fast8_t(((arg_0 >> 6) & 1));  // basic_select
    const uint_fast8_t tmp_180 = uint_fast8_t((~tmp_179));  // basic_invert
    const uint_fast8_t tmp_181 = uint_fast8_t((tmp_177 & tmp_180));  // basic_and
    const uint_fast8_t tmp_182 = uint_fast8_t((tmp_178 + tmp_181));  // basic_add
    const uint_fast8_t tmp_183 = uint_fast8_t(((arg_0 >> 5) & 1));  // basic_select
    const uint_fast8_t tmp_184 = uint_fast8_t((~tmp_183));  // basic_invert
    const uint_fast8_t tmp_185 = uint_fast8_t((tmp_181 & tmp_184));  // basic_and
    const uint_fast8_t tmp_186 = uint_fast8_t((tmp_182 + tmp_185));  // basic_add
    const uint_fast8_t tmp_187 = uint_fast8_t(((arg_0 >> 4) & 1));  // basic_select
    const uint_fast8_t tmp_188 = uint_fast8_t((~tmp_187));  // basic_invert
    const uint_fast8_t tmp_189 = uint_fast8_t((tmp_185 & tmp_188));  // basic_and
    const uint_fast8_t tmp_190 = uint_fast8_t((tmp_186 + tmp_189));  // basic_add
    const uint_fast8_t tmp_191 = uint_fast8_t(((arg_0 >> 3) & 1));  // basic_select
    const uint_fast8_t tmp_192 = uint_fast8_t((~tmp_191));  // basic_invert
    const uint_fast8_t tmp_193 = uint_fast8_t((tmp_189 & tmp_192));  // basic_and
    const uint_fast8_t tmp_194 = uint_fast8_t((tmp_190 + tmp_193));  // basic_add
    const uint_fast8_t tmp_195 = uint_fast8_t(((arg_0 >> 2) & 1));  // basic_select
    const uint_fast8_t tmp_196 = uint_fast8_t((~tmp_195));  // basic_invert
    const uint_fast8_t tmp_197 = uint_fast8_t((tmp_193 & tmp_196));  // basic_and
    const uint_fast8_t tmp_198 = uint_fast8_t((tmp_194 + tmp_197));  // basic_add
    const uint_fast8_t tmp_199 = uint_fast8_t(((arg_0 >> 1) & 1));  // basic_select
    const uint_fast8_t tmp_200 = uint_fast8_t((~tmp_199));  // basic_invert
    const uint_fast8_t tmp_201 = uint_fast8_t((tmp_197 & tmp_200));  // basic_and
    const uint_fast8_t tmp_202 = uint_fast8_t((tmp_198 + tmp_201));  // basic_add
    const uint_fast8_t tmp_203 = uint_fast8_t(((arg_0 >> 0) & 1));  // basic_select
    const uint_fast8_t tmp_204 = uint_fast8_t((~tmp_203));  // basic_invert
    const uint_fast8_t tmp_205 = uint_fast8_t((tmp_201 & tmp_204));  // basic_and
    const uint_fast8_t tmp_206 = uint_fast8_t((tmp_202 + tmp_205));  // basic_add
    return tmp_206;
}
uint_fast8_t uq_to_q_2(uint_fast8_t arg_0) {  // uq_to_q
    const uint_fast8_t tmp_208 = uq_add(uint_fast8_t(5), uint_fast8_t(1));  // uq_add
    const uint_fast8_t tmp_209 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_210 = uint_fast8_t(arg_0);  // basic_identity
    return tmp_210;
}
uint_fast8_t q_sign_bit_1(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_214 = uint_fast8_t(((arg_0 >> 5) & 1));  // basic_select
    return tmp_214;
}
uint_fast8_t q_sign_extend_1(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_215 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_216 = uint_fast8_t((tmp_215 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_217 = uint_fast8_t((tmp_216 - tmp_215));  // basic_sub
    const uint_fast8_t tmp_218 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_219 = uint_fast8_t(((tmp_217 << 6) | arg_0));  // basic_concat
    return tmp_219;
}
uint_fast8_t q_sign_extend_2(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_222 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_223 = uint_fast8_t((tmp_222 << uint_fast8_t(4)));  // basic_lshift
    const uint_fast8_t tmp_224 = uint_fast8_t((tmp_223 - tmp_222));  // basic_sub
    const uint_fast8_t tmp_225 = uint_fast8_t(0);  // q_alloc
    const uint_fast8_t tmp_226 = uint_fast8_t(((tmp_224 << 3) | arg_0));  // basic_concat
    return tmp_226;
}
std::tuple<uint_fast8_t, uint_fast8_t> q_aligner_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_aligner
    const uint_fast8_t tmp_213 = uint_fast8_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_220 = q_sign_extend_1(tmp_213);  // q_sign_extend
    const uint_fast8_t tmp_221 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast8_t tmp_227 = q_sign_extend_2(tmp_221);  // q_sign_extend
    const std::tuple<uint_fast8_t, uint_fast8_t> tmp_228 = std::tuple<uint_fast8_t, uint_fast8_t>(std::make_tuple(tmp_220, tmp_227));  // basic_tuple_maker_2
    return tmp_228;
}
uint_fast8_t q_sub(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_sub
    const std::tuple<uint_fast8_t, uint_fast8_t> tmp_229 = q_aligner_1(arg_0, arg_1);  // q_aligner
    const uint_fast8_t tmp_230 = uint_fast8_t(std::get<0>(tmp_229));  // basic_get_item_0
    const uint_fast8_t tmp_231 = uint_fast8_t(std::get<1>(tmp_229));  // basic_get_item_1
    const uint_fast8_t tmp_232 = uint_fast8_t((tmp_230 - tmp_231));  // basic_sub
    return tmp_232;
}
uint_fast8_t q_add_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add
    const std::tuple<uint_fast8_t, uint_fast8_t> tmp_234 = q_aligner_1(arg_0, arg_1);  // q_aligner
    const uint_fast8_t tmp_235 = uint_fast8_t(std::get<0>(tmp_234));  // basic_get_item_0
    const uint_fast8_t tmp_236 = uint_fast8_t(std::get<1>(tmp_234));  // basic_get_item_1
    const uint_fast8_t tmp_237 = uint_fast8_t((tmp_235 + tmp_236));  // basic_add
    return tmp_237;
}
uint_fast32_t uq_resize_1(uint_fast32_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_240 = uint_fast32_t((arg_0 << uint_fast8_t(1)));  // basic_lshift
    return tmp_240;
}
uint_fast8_t q_neg_1(uint_fast8_t arg_0) {  // q_neg
    const uint_fast8_t tmp_243 = uint_fast8_t((arg_0 == 128));  // _q_is_min_val
    const uint_fast8_t tmp_244 = uint_fast8_t((~arg_0));  // basic_invert
    const uint_fast8_t tmp_245 = uint_fast8_t((tmp_244 + uint_fast8_t(1)));  // basic_add
    const uint_fast8_t tmp_246 = uint_fast8_t((arg_0 ^ arg_0));  // basic_xor
    const uint_fast8_t tmp_247 = uint_fast8_t((~tmp_246));  // basic_invert
    const uint_fast8_t tmp_248 = uint_fast8_t((tmp_243 ? tmp_247 : tmp_245));  // basic_mux_2_1
    return tmp_248;
}
uint_fast8_t q_add_sign_1(uint_fast8_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast8_t tmp_249 = q_neg_1(arg_0);  // q_neg
    const uint_fast8_t tmp_250 = uint_fast8_t((arg_1 ? tmp_249 : arg_0));  // basic_mux_2_1
    return tmp_250;
}
uint_fast8_t q_abs_1(uint_fast8_t arg_0) {  // q_abs
    const uint_fast8_t tmp_242 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_251 = q_add_sign_1(arg_0, tmp_242);  // q_add_sign
    return tmp_251;
}
uint_fast8_t q_to_uq_1(uint_fast8_t arg_0) {  // q_to_uq
    const uint_fast8_t tmp_253 = uint_fast8_t(arg_0);  // basic_identity
    return tmp_253;
}
uint_fast32_t uq_lshift(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_lshift
    const uint_fast32_t tmp_255 = uint_fast32_t((arg_0 << arg_1));  // basic_lshift
    return tmp_255;
}
uint_fast32_t uq_rshift_1(uint_fast32_t arg_0, uint_fast8_t arg_1) {  // uq_rshift
    const uint_fast32_t tmp_257 = uint_fast32_t((arg_0 >> arg_1));  // basic_rshift
    return tmp_257;
}
uint_fast8_t q_sign_bit_2(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_261 = uint_fast8_t(((arg_0 >> 8) & 1));  // basic_select
    return tmp_261;
}
uint_fast16_t q_sign_extend_3(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_262 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_263 = uint_fast8_t((tmp_262 << uint_fast8_t(1)));  // basic_lshift
    const uint_fast8_t tmp_264 = uint_fast8_t((tmp_263 - tmp_262));  // basic_sub
    const uint_fast16_t tmp_265 = uint_fast16_t(0);  // q_alloc
    const uint_fast16_t tmp_266 = uint_fast16_t(((tmp_264 << 9) | arg_0));  // basic_concat
    return tmp_266;
}
uint_fast16_t q_sign_extend_4(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_269 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_270 = uint_fast8_t((tmp_269 << uint_fast8_t(2)));  // basic_lshift
    const uint_fast8_t tmp_271 = uint_fast8_t((tmp_270 - tmp_269));  // basic_sub
    const uint_fast16_t tmp_272 = uint_fast16_t(0);  // q_alloc
    const uint_fast16_t tmp_273 = uint_fast16_t(((tmp_271 << 8) | arg_0));  // basic_concat
    return tmp_273;
}
std::tuple<uint_fast16_t, uint_fast16_t> q_aligner_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_aligner
    const uint_fast16_t tmp_260 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_267 = q_sign_extend_3(tmp_260);  // q_sign_extend
    const uint_fast8_t tmp_268 = uint_fast8_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_274 = q_sign_extend_4(tmp_268);  // q_sign_extend
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_275 = std::tuple<uint_fast16_t, uint_fast16_t>(std::make_tuple(tmp_267, tmp_274));  // basic_tuple_maker_2
    return tmp_275;
}
uint_fast16_t q_sub_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_sub
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_276 = q_aligner_2(arg_0, arg_1);  // q_aligner
    const uint_fast16_t tmp_277 = uint_fast16_t(std::get<0>(tmp_276));  // basic_get_item_0
    const uint_fast16_t tmp_278 = uint_fast16_t(std::get<1>(tmp_276));  // basic_get_item_1
    const uint_fast16_t tmp_279 = uint_fast16_t((tmp_277 - tmp_278));  // basic_sub
    return tmp_279;
}
uint_fast16_t q_add_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_281 = q_aligner_2(arg_0, arg_1);  // q_aligner
    const uint_fast16_t tmp_282 = uint_fast16_t(std::get<0>(tmp_281));  // basic_get_item_0
    const uint_fast16_t tmp_283 = uint_fast16_t(std::get<1>(tmp_281));  // basic_get_item_1
    const uint_fast16_t tmp_284 = uint_fast16_t((tmp_282 + tmp_283));  // basic_add
    return tmp_284;
}
std::tuple<uint_fast32_t, uint_fast16_t> fp32_normalize(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // fp32_normalize
    const uint_fast8_t tmp_207 = lzc(arg_0);  // lzc
    const uint_fast8_t tmp_211 = uq_to_q_2(tmp_207);  // uq_to_q
    const uint_fast8_t tmp_212 = uq_to_q_2(uint_fast8_t(2));  // uq_to_q
    const uint_fast8_t tmp_233 = q_sub(tmp_211, tmp_212);  // q_sub
    const uint_fast8_t tmp_238 = q_add_1(tmp_233, uint_fast8_t(1));  // q_add
    const uint_fast8_t tmp_239 = q_sign_bit_1(tmp_238);  // q_sign_bit
    const uint_fast32_t tmp_241 = uq_resize_1(arg_0);  // uq_resize
    const uint_fast8_t tmp_252 = q_abs_1(tmp_238);  // q_abs
    const uint_fast8_t tmp_254 = q_to_uq_1(tmp_252);  // q_to_uq
    const uint_fast32_t tmp_256 = uq_lshift(tmp_241, tmp_254);  // uq_lshift
    const uint_fast32_t tmp_258 = uq_rshift_1(tmp_241, tmp_254);  // uq_rshift
    const uint_fast32_t tmp_259 = uint_fast32_t((tmp_239 ? tmp_258 : tmp_256));  // basic_mux_2_1
    const uint_fast16_t tmp_280 = q_sub_1(arg_1, tmp_252);  // q_sub
    const uint_fast16_t tmp_285 = q_add_2(arg_1, tmp_252);  // q_add
    const uint_fast16_t tmp_286 = uint_fast16_t((tmp_239 ? tmp_285 : tmp_280));  // basic_mux_2_1
    const std::tuple<uint_fast32_t, uint_fast16_t> tmp_287 = std::tuple<uint_fast32_t, uint_fast16_t>(std::make_tuple(tmp_259, tmp_286));  // basic_tuple_maker_2
    return tmp_287;
}
uint_fast8_t q_is_zero(uint_fast16_t arg_0) {  // q_is_zero
    const uint_fast8_t tmp_292 = uint_fast8_t((arg_0 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_293 = uint_fast8_t((~tmp_292));  // basic_invert
    return tmp_293;
}
uint_fast16_t q_neg_2(uint_fast16_t arg_0) {  // q_neg
    const uint_fast8_t tmp_298 = uint_fast8_t((arg_0 == 512));  // _q_is_min_val
    const uint_fast16_t tmp_299 = uint_fast16_t((~arg_0));  // basic_invert
    const uint_fast16_t tmp_300 = uint_fast16_t((tmp_299 + uint_fast8_t(1)));  // basic_add
    const uint_fast16_t tmp_301 = uint_fast16_t((arg_0 ^ arg_0));  // basic_xor
    const uint_fast16_t tmp_302 = uint_fast16_t((~tmp_301));  // basic_invert
    const uint_fast16_t tmp_303 = uint_fast16_t((tmp_298 ? tmp_302 : tmp_300));  // basic_mux_2_1
    return tmp_303;
}
uint_fast16_t q_add_sign_2(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_add_sign
    const uint_fast16_t tmp_304 = q_neg_2(arg_0);  // q_neg
    const uint_fast16_t tmp_305 = uint_fast16_t((arg_1 ? tmp_304 : arg_0));  // basic_mux_2_1
    return tmp_305;
}
uint_fast16_t q_abs_2(uint_fast16_t arg_0) {  // q_abs
    const uint_fast8_t tmp_297 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_306 = q_add_sign_2(arg_0, tmp_297);  // q_add_sign
    return tmp_306;
}
uint_fast16_t q_to_uq_2(uint_fast16_t arg_0) {  // q_to_uq
    const uint_fast16_t tmp_308 = uint_fast16_t(arg_0);  // basic_identity
    return tmp_308;
}
std::tuple<uint_fast16_t, uint_fast16_t> uq_aligner_2(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_aligner
    const uint_fast16_t tmp_310 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_311 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_312 = std::tuple<uint_fast16_t, uint_fast16_t>(std::make_tuple(tmp_310, tmp_311));  // basic_tuple_maker_2
    return tmp_312;
}
uint_fast16_t uq_add_1(uint_fast8_t arg_0, uint_fast16_t arg_1) {  // uq_add
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_313 = uq_aligner_2(arg_0, arg_1);  // uq_aligner
    const uint_fast16_t tmp_314 = uint_fast16_t(std::get<0>(tmp_313));  // basic_get_item_0
    const uint_fast16_t tmp_315 = uint_fast16_t(std::get<1>(tmp_313));  // basic_get_item_1
    const uint_fast16_t tmp_316 = uint_fast16_t((tmp_314 + tmp_315));  // basic_add
    return tmp_316;
}
uint_fast64_t uq_rshift_2(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // uq_rshift
    const uint_fast64_t tmp_319 = uint_fast64_t((arg_0 >> arg_1));  // basic_rshift
    return tmp_319;
}
std::tuple<uint_fast64_t, uint_fast16_t> fp32_classify(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // fp32_classify
    const uint_fast64_t tmp_291 = uint_fast64_t((arg_0 << uint_fast8_t(10)));  // basic_lshift
    const uint_fast8_t tmp_294 = q_is_zero(arg_1);  // q_is_zero
    const uint_fast8_t tmp_295 = q_sign_bit_2(arg_1);  // q_sign_bit
    const uint_fast8_t tmp_296 = uint_fast8_t((tmp_294 | tmp_295));  // basic_or
    const uint_fast16_t tmp_307 = q_abs_2(arg_1);  // q_abs
    const uint_fast16_t tmp_309 = q_to_uq_2(tmp_307);  // q_to_uq
    const uint_fast16_t tmp_317 = uq_add_1(uint_fast8_t(1), tmp_309);  // uq_add
    const uint_fast16_t tmp_318 = uint_fast16_t((tmp_296 ? tmp_317 : uint_fast8_t(0)));  // basic_mux_2_1
    const uint_fast64_t tmp_320 = uq_rshift_2(tmp_291, tmp_318);  // uq_rshift
    const uint_fast16_t tmp_321 = uint_fast16_t((tmp_296 ? uint_fast8_t(0) : tmp_309));  // basic_mux_2_1
    const std::tuple<uint_fast64_t, uint_fast16_t> tmp_322 = std::tuple<uint_fast64_t, uint_fast16_t>(std::make_tuple(tmp_320, tmp_321));  // basic_tuple_maker_2
    return tmp_322;
}
uint_fast64_t drop_implicit_bit(uint_fast64_t arg_0) {  // drop_implicit_bit
    const uint_fast64_t tmp_325 = uint_fast64_t(((arg_0 >> 0) & 1099511627775));  // basic_select
    return tmp_325;
}
uint_fast8_t uq_is_zero(uint_fast16_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_328 = uint_fast8_t((arg_0 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_329 = uint_fast8_t((~tmp_328));  // basic_invert
    return tmp_329;
}
uint_fast32_t uq_resize_2(uint_fast64_t arg_0) {  // uq_resize
    const uint_fast32_t tmp_331 = uint_fast32_t((arg_0 >> uint_fast8_t(17)));  // basic_rshift
    return tmp_331;
}
uint_fast32_t uq_RNE_IEEE(uint_fast64_t arg_0) {  // uq_RNE_IEEE
    const uint_fast8_t tmp_333 = uint_fast8_t(((arg_0 >> 16) & 1));  // basic_select
    const uint_fast8_t tmp_334 = uint_fast8_t(((arg_0 >> 15) & 1));  // basic_select
    const uint_fast16_t tmp_335 = uint_fast16_t(((arg_0 >> 0) & 32767));  // basic_select
    const uint_fast8_t tmp_336 = uint_fast8_t((tmp_335 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_337 = uint_fast8_t((tmp_334 | tmp_336));  // basic_or
    const uint_fast8_t tmp_338 = uint_fast8_t(((arg_0 >> 17) & 1));  // basic_select
    const uint_fast8_t tmp_339 = uint_fast8_t((tmp_337 | tmp_338));  // basic_or
    const uint_fast8_t tmp_340 = uint_fast8_t((tmp_333 & tmp_339));  // basic_and
    const uint_fast32_t tmp_341 = uint_fast32_t(tmp_340);  // basic_identity
    return tmp_341;
}
std::tuple<uint_fast32_t, uint_fast32_t> uq_aligner_3(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_aligner
    const uint_fast32_t tmp_343 = uint_fast32_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast32_t tmp_344 = uint_fast32_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::tuple<uint_fast32_t, uint_fast32_t> tmp_345 = std::tuple<uint_fast32_t, uint_fast32_t>(std::make_tuple(tmp_343, tmp_344));  // basic_tuple_maker_2
    return tmp_345;
}
uint_fast32_t uq_add_2(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // uq_add
    const std::tuple<uint_fast32_t, uint_fast32_t> tmp_346 = uq_aligner_3(arg_0, arg_1);  // uq_aligner
    const uint_fast32_t tmp_347 = uint_fast32_t(std::get<0>(tmp_346));  // basic_get_item_0
    const uint_fast32_t tmp_348 = uint_fast32_t(std::get<1>(tmp_346));  // basic_get_item_1
    const uint_fast32_t tmp_349 = uint_fast32_t((tmp_347 + tmp_348));  // basic_add
    return tmp_349;
}
std::tuple<uint_fast16_t, uint_fast16_t> uq_aligner_4(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_aligner
    const uint_fast16_t tmp_352 = uint_fast16_t((arg_0 << uint_fast8_t(0)));  // basic_lshift
    const uint_fast16_t tmp_353 = uint_fast16_t((arg_1 << uint_fast8_t(0)));  // basic_lshift
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_354 = std::tuple<uint_fast16_t, uint_fast16_t>(std::make_tuple(tmp_352, tmp_353));  // basic_tuple_maker_2
    return tmp_354;
}
uint_fast16_t uq_add_3(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_add
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_355 = uq_aligner_4(arg_0, arg_1);  // uq_aligner
    const uint_fast16_t tmp_356 = uint_fast16_t(std::get<0>(tmp_355));  // basic_get_item_0
    const uint_fast16_t tmp_357 = uint_fast16_t(std::get<1>(tmp_355));  // basic_get_item_1
    const uint_fast16_t tmp_358 = uint_fast16_t((tmp_356 + tmp_357));  // basic_add
    return tmp_358;
}
std::tuple<uint_fast32_t, uint_fast16_t> fp32_round(uint_fast64_t arg_0, uint_fast16_t arg_1) {  // fp32_round
    const uint_fast8_t tmp_330 = uq_is_zero(arg_1);  // uq_is_zero
    const uint_fast32_t tmp_332 = uq_resize_2(arg_0);  // uq_resize
    const uint_fast32_t tmp_342 = uq_RNE_IEEE(arg_0);  // uq_RNE_IEEE
    const uint_fast32_t tmp_350 = uq_add_2(tmp_332, tmp_342);  // uq_add
    const uint_fast8_t tmp_351 = uint_fast8_t(((tmp_350 >> 23) & 1));  // basic_select
    const uint_fast16_t tmp_359 = uq_add_3(arg_1, tmp_351);  // uq_add
    const uint_fast8_t tmp_360 = uint_fast8_t((tmp_359 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_361 = uint_fast8_t((tmp_330 & tmp_360));  // basic_and
    const uint_fast32_t tmp_362 = uint_fast32_t((tmp_350 >> uint_fast8_t(1)));  // basic_rshift
    const uint_fast32_t tmp_363 = uint_fast32_t((tmp_351 ? tmp_362 : tmp_350));  // basic_mux_2_1
    const uint_fast32_t tmp_364 = uint_fast32_t((tmp_361 ? uint_fast8_t(0) : tmp_363));  // basic_mux_2_1
    const std::tuple<uint_fast32_t, uint_fast16_t> tmp_365 = std::tuple<uint_fast32_t, uint_fast16_t>(std::make_tuple(tmp_364, tmp_359));  // basic_tuple_maker_2
    return tmp_365;
}
uint_fast16_t uq_min(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // uq_min
    const std::tuple<uint_fast16_t, uint_fast16_t> tmp_369 = uq_aligner_4(arg_0, arg_1);  // uq_aligner
    const uint_fast16_t tmp_370 = uint_fast16_t(std::get<0>(tmp_369));  // basic_get_item_0
    const uint_fast16_t tmp_371 = uint_fast16_t(std::get<1>(tmp_369));  // basic_get_item_1
    const uint_fast16_t tmp_372 = uint_fast16_t((tmp_370 < tmp_371 ? tmp_370 : tmp_371));  // basic_min
    return tmp_372;
}
uint_fast8_t uq_is_zero_1(uint_fast32_t arg_0) {  // uq_is_zero
    const uint_fast8_t tmp_378 = uint_fast8_t((arg_0 != 0));  // basic_or_reduce
    const uint_fast8_t tmp_379 = uint_fast8_t((~tmp_378));  // basic_invert
    return tmp_379;
}
std::tuple<uint_fast32_t, uint_fast8_t> fp32_encodings(uint_fast32_t arg_0, uint_fast16_t arg_1, uint_fast32_t arg_2) {  // fp32_encodings
    const uint_fast16_t tmp_373 = uq_min(arg_1, uint_fast8_t(255));  // uq_min
    const uint_fast8_t tmp_374 = uint_fast8_t(tmp_373);  // basic_identity
    const uint_fast8_t tmp_375 = uint_fast8_t((tmp_374 == 255));  // basic_and_reduce
    const uint_fast32_t tmp_376 = uint_fast32_t((tmp_375 ? uint_fast8_t(0) : arg_0));  // basic_mux_2_1
    const uint_fast32_t tmp_377 = uint_fast32_t(tmp_376);  // basic_identity
    const uint_fast8_t tmp_380 = uq_is_zero_1(arg_2);  // uq_is_zero
    const uint_fast8_t tmp_381 = uint_fast8_t((tmp_380 ? uint_fast8_t(0) : tmp_374));  // basic_mux_2_1
    const std::tuple<uint_fast32_t, uint_fast8_t> tmp_382 = std::tuple<uint_fast32_t, uint_fast8_t>(std::make_tuple(tmp_377, tmp_381));  // basic_tuple_maker_2
    return tmp_382;
}
uint_fast32_t fp32_pack(uint_fast8_t arg_0, uint_fast8_t arg_1, uint_fast32_t arg_2) {  // fp32_pack
    const uint_fast32_t tmp_386 = uint_fast32_t(((arg_0 << 31) | (arg_1 << 23) | arg_2));  // float32_alloc
    return tmp_386;
}
uint_fast32_t encode_Float32(uint_fast32_t arg_0, uint_fast16_t arg_1) {  // encode_Float32
    const uint_fast8_t tmp_77 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast32_t tmp_80 = q_abs(arg_0);  // q_abs
    const uint_fast32_t tmp_82 = q_to_uq(tmp_80);  // q_to_uq
    const std::tuple<uint_fast32_t, uint_fast16_t> tmp_288 = fp32_normalize(tmp_82, arg_1);  // fp32_normalize
    const uint_fast32_t tmp_289 = uint_fast32_t(std::get<0>(tmp_288));  // basic_get_item_0
    const uint_fast16_t tmp_290 = uint_fast16_t(std::get<1>(tmp_288));  // basic_get_item_1
    const std::tuple<uint_fast64_t, uint_fast16_t> tmp_323 = fp32_classify(tmp_289, tmp_290);  // fp32_classify
    const uint_fast64_t tmp_324 = uint_fast64_t(std::get<0>(tmp_323));  // basic_get_item_0
    const uint_fast64_t tmp_326 = drop_implicit_bit(tmp_324);  // drop_implicit_bit
    const uint_fast16_t tmp_327 = uint_fast16_t(std::get<1>(tmp_323));  // basic_get_item_1
    const std::tuple<uint_fast32_t, uint_fast16_t> tmp_366 = fp32_round(tmp_326, tmp_327);  // fp32_round
    const uint_fast32_t tmp_367 = uint_fast32_t(std::get<0>(tmp_366));  // basic_get_item_0
    const uint_fast16_t tmp_368 = uint_fast16_t(std::get<1>(tmp_366));  // basic_get_item_1
    const std::tuple<uint_fast32_t, uint_fast8_t> tmp_383 = fp32_encodings(tmp_367, tmp_368, tmp_82);  // fp32_encodings
    const uint_fast8_t tmp_384 = uint_fast8_t(std::get<1>(tmp_383));  // basic_get_item_1
    const uint_fast32_t tmp_385 = uint_fast32_t(std::get<0>(tmp_383));  // basic_get_item_0
    const uint_fast32_t tmp_387 = fp32_pack(tmp_77, tmp_384, tmp_385);  // fp32_pack
    return tmp_387;
}
uint_fast32_t FP32_IEEE_adder(uint_fast32_t arg_0, uint_fast32_t arg_1) {  // FP32_IEEE_adder
    const std::tuple<uint_fast8_t, uint_fast8_t, uint_fast32_t> tmp_4 = fp32_unpack(arg_0);  // fp32_unpack
    const uint_fast32_t tmp_5 = uint_fast32_t(std::get<2>(tmp_4));  // basic_get_item_2
    const uint_fast32_t tmp_7 = add_implicit_bit(tmp_5);  // add_implicit_bit
    const uint_fast32_t tmp_9 = uq_resize(tmp_7);  // uq_resize
    const uint_fast8_t tmp_10 = uint_fast8_t(std::get<1>(tmp_4));  // basic_get_item_1
    const std::tuple<uint_fast8_t, uint_fast8_t, uint_fast32_t> tmp_11 = fp32_unpack(arg_1);  // fp32_unpack
    const uint_fast8_t tmp_12 = uint_fast8_t(std::get<1>(tmp_11));  // basic_get_item_1
    const uint_fast8_t tmp_20 = uq_max(tmp_10, tmp_12);  // uq_max
    const uint_fast16_t tmp_28 = uq_sub(tmp_20, tmp_10);  // uq_sub
    const uint_fast32_t tmp_30 = uq_rshift(tmp_9, tmp_28);  // uq_rshift
    const uint_fast32_t tmp_38 = uq_to_q(tmp_30);  // uq_to_q
    const uint_fast8_t tmp_39 = uint_fast8_t(std::get<0>(tmp_4));  // basic_get_item_0
    const uint_fast32_t tmp_48 = q_add_sign(tmp_38, tmp_39);  // q_add_sign
    const uint_fast32_t tmp_49 = uint_fast32_t(std::get<2>(tmp_11));  // basic_get_item_2
    const uint_fast32_t tmp_50 = add_implicit_bit(tmp_49);  // add_implicit_bit
    const uint_fast32_t tmp_51 = uq_resize(tmp_50);  // uq_resize
    const uint_fast16_t tmp_52 = uq_sub(tmp_20, tmp_12);  // uq_sub
    const uint_fast32_t tmp_53 = uq_rshift(tmp_51, tmp_52);  // uq_rshift
    const uint_fast32_t tmp_54 = uq_to_q(tmp_53);  // uq_to_q
    const uint_fast8_t tmp_55 = uint_fast8_t(std::get<0>(tmp_11));  // basic_get_item_0
    const uint_fast32_t tmp_56 = q_add_sign(tmp_54, tmp_55);  // q_add_sign
    const uint_fast32_t tmp_72 = q_add(tmp_48, tmp_56);  // q_add
    const uint_fast16_t tmp_76 = uq_to_q_1(tmp_20);  // uq_to_q
    const uint_fast32_t tmp_388 = encode_Float32(tmp_72, tmp_76);  // encode_Float32
    return tmp_388;
}