#pragma once
#include <array>
#include <cstdint>

static inline uint_fast8_t q_sign_bit(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_1 = uint_fast8_t(((arg_0 >> 6) & 1) & 1);  // basic_select
    return tmp_1;
}
static inline uint_fast16_t q_sign_extend(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_2 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_3 = uint_fast8_t((uint_fast8_t(5 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_2) << uint_fast8_t(5 & 7))) & 63);  // basic_lshift
    const uint_fast8_t tmp_4 = uint_fast8_t((tmp_3 - tmp_2) & 31);  // basic_sub
    const uint_fast16_t tmp_5 = uint_fast16_t(0 & 4095);  // q_alloc
    const uint_fast16_t tmp_6 = uint_fast16_t(((uint_fast64_t(tmp_4) << 7) | arg_0) & 4095);  // basic_concat
    return tmp_6;
}
static inline uint_fast16_t q_sign_extend_1(uint_fast16_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast8_t q_sign_bit_1(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_17 = uint_fast8_t(((arg_0 >> 8) & 1) & 1);  // basic_select
    return tmp_17;
}
static inline uint_fast16_t q_sign_extend_2(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_18 = q_sign_bit_1(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_19 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_18) << uint_fast8_t(3 & 3))) & 15);  // basic_lshift
    const uint_fast8_t tmp_20 = uint_fast8_t((tmp_19 - tmp_18) & 7);  // basic_sub
    const uint_fast16_t tmp_21 = uint_fast16_t(0 & 4095);  // q_alloc
    const uint_fast16_t tmp_22 = uint_fast16_t(((uint_fast64_t(tmp_20) << 9) | arg_0) & 4095);  // basic_concat
    return tmp_22;
}
static inline uint_fast16_t q_sign_extend_3(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_37 = q_sign_bit(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_38 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_37) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_39 = uint_fast8_t((tmp_38 - tmp_37) & 3);  // basic_sub
    const uint_fast16_t tmp_40 = uint_fast16_t(0 & 511);  // q_alloc
    const uint_fast16_t tmp_41 = uint_fast16_t(((uint_fast64_t(tmp_39) << 7) | arg_0) & 511);  // basic_concat
    return tmp_41;
}
static inline uint_fast16_t q_sign_extend_4(uint_fast16_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast16_t q_sign_extend_5(uint_fast16_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast8_t q_sign_bit_2(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_60 = uint_fast8_t(((arg_0 >> 7) & 1) & 1);  // basic_select
    return tmp_60;
}
static inline uint_fast16_t q_sign_extend_6(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_61 = q_sign_bit_2(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_62 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_61) << uint_fast8_t(3 & 3))) & 15);  // basic_lshift
    const uint_fast8_t tmp_63 = uint_fast8_t((tmp_62 - tmp_61) & 7);  // basic_sub
    const uint_fast16_t tmp_64 = uint_fast16_t(0 & 2047);  // q_alloc
    const uint_fast16_t tmp_65 = uint_fast16_t(((uint_fast64_t(tmp_63) << 8) | arg_0) & 2047);  // basic_concat
    return tmp_65;
}
static inline uint_fast8_t q_sign_bit_3(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_79 = uint_fast8_t(((arg_0 >> 11) & 1) & 1);  // basic_select
    return tmp_79;
}
static inline uint_fast16_t q_sign_extend_7(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_80 = q_sign_bit_3(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_81 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_80) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_82 = uint_fast8_t((tmp_81 - tmp_80) & 1);  // basic_sub
    const uint_fast16_t tmp_83 = uint_fast16_t(0 & 8191);  // q_alloc
    const uint_fast16_t tmp_84 = uint_fast16_t(((uint_fast64_t(tmp_82) << 12) | arg_0) & 8191);  // basic_concat
    return tmp_84;
}
static inline uint_fast16_t q_lshift(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_lshift
    const uint_fast16_t tmp_86 = uint_fast16_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 8191);  // basic_lshift
    return tmp_86;
}
static inline uint_fast8_t q_sign_bit_4(uint_fast8_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_92 = uint_fast8_t(((arg_0 >> 5) & 1) & 1);  // basic_select
    return tmp_92;
}
static inline uint_fast16_t q_sign_extend_8(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_93 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_94 = uint_fast8_t((uint_fast8_t(7 & 7) >= 64 ? 0 : (uint_fast64_t(tmp_93) << uint_fast8_t(7 & 7))) & 255);  // basic_lshift
    const uint_fast8_t tmp_95 = uint_fast8_t((tmp_94 - tmp_93) & 127);  // basic_sub
    const uint_fast16_t tmp_96 = uint_fast16_t(0 & 8191);  // q_alloc
    const uint_fast16_t tmp_97 = uint_fast16_t(((uint_fast64_t(tmp_95) << 6) | arg_0) & 8191);  // basic_concat
    return tmp_97;
}
static inline uint_fast16_t q_sign_extend_9(uint_fast16_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast8_t q_sign_bit_5(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_106 = uint_fast8_t(((arg_0 >> 12) & 1) & 1);  // basic_select
    return tmp_106;
}
static inline uint_fast16_t q_sign_extend_10(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_107 = q_sign_bit_5(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_108 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_107) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_109 = uint_fast8_t((tmp_108 - tmp_107) & 1);  // basic_sub
    const uint_fast16_t tmp_110 = uint_fast16_t(0 & 16383);  // q_alloc
    const uint_fast16_t tmp_111 = uint_fast16_t(((uint_fast64_t(tmp_109) << 13) | arg_0) & 16383);  // basic_concat
    return tmp_111;
}
static inline uint_fast16_t q_sign_extend_11(uint_fast16_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast16_t q_sign_extend_12(uint_fast8_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_128 = q_sign_bit_4(arg_0);  // q_sign_bit
    const uint_fast16_t tmp_129 = uint_fast16_t((uint_fast8_t(8 & 15) >= 64 ? 0 : (uint_fast64_t(tmp_128) << uint_fast8_t(8 & 15))) & 511);  // basic_lshift
    const uint_fast8_t tmp_130 = uint_fast8_t((tmp_129 - tmp_128) & 255);  // basic_sub
    const uint_fast16_t tmp_131 = uint_fast16_t(0 & 16383);  // q_alloc
    const uint_fast16_t tmp_132 = uint_fast16_t(((uint_fast64_t(tmp_130) << 6) | arg_0) & 16383);  // basic_concat
    return tmp_132;
}
static inline uint_fast16_t q_sign_extend_13(uint_fast16_t arg_0) {  // q_sign_extend
    return arg_0;
}
static inline uint_fast8_t q_sign_bit_6(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_164 = uint_fast8_t(((arg_0 >> 13) & 1) & 1);  // basic_select
    return tmp_164;
}
static inline uint_fast16_t q_sign_extend_14(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_165 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_166 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_165) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_167 = uint_fast8_t((tmp_166 - tmp_165) & 1);  // basic_sub
    const uint_fast16_t tmp_168 = uint_fast16_t(0 & 32767);  // q_alloc
    const uint_fast16_t tmp_169 = uint_fast16_t(((uint_fast64_t(tmp_167) << 14) | arg_0) & 32767);  // basic_concat
    return tmp_169;
}
static inline uint_fast16_t q_lshift_1(uint_fast16_t arg_0, uint_fast8_t arg_1) {  // q_lshift
    const uint_fast16_t tmp_171 = uint_fast16_t((arg_1 >= 64 ? 0 : (uint_fast64_t(arg_0) << arg_1)) & 32767);  // basic_lshift
    return tmp_171;
}
static inline uint_fast16_t q_sign_extend_15(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_177 = q_sign_bit_6(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_178 = uint_fast8_t((uint_fast8_t(2 & 3) >= 64 ? 0 : (uint_fast64_t(tmp_177) << uint_fast8_t(2 & 3))) & 7);  // basic_lshift
    const uint_fast8_t tmp_179 = uint_fast8_t((tmp_178 - tmp_177) & 3);  // basic_sub
    const uint_fast16_t tmp_180 = uint_fast16_t(0 & 65535);  // q_alloc
    const uint_fast16_t tmp_181 = uint_fast16_t(((uint_fast64_t(tmp_179) << 14) | arg_0) & 65535);  // basic_concat
    return tmp_181;
}
static inline uint_fast8_t q_sign_bit_7(uint_fast16_t arg_0) {  // q_sign_bit
    const uint_fast8_t tmp_184 = uint_fast8_t(((arg_0 >> 14) & 1) & 1);  // basic_select
    return tmp_184;
}
static inline uint_fast16_t q_sign_extend_16(uint_fast16_t arg_0) {  // q_sign_extend
    const uint_fast8_t tmp_185 = q_sign_bit_7(arg_0);  // q_sign_bit
    const uint_fast8_t tmp_186 = uint_fast8_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_185) << uint_fast8_t(1 & 1))) & 3);  // basic_lshift
    const uint_fast8_t tmp_187 = uint_fast8_t((tmp_186 - tmp_185) & 1);  // basic_sub
    const uint_fast16_t tmp_188 = uint_fast16_t(0 & 65535);  // q_alloc
    const uint_fast16_t tmp_189 = uint_fast16_t(((uint_fast64_t(tmp_187) << 15) | arg_0) & 65535);  // basic_concat
    return tmp_189;
}
static inline uint_fast16_t q_add(uint_fast16_t arg_0, uint_fast16_t arg_1) {  // q_add
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_176 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 16383);  // basic_lshift
    const uint_fast16_t tmp_182 = q_sign_extend_15(tmp_176);  // q_sign_extend
    const uint_fast16_t tmp_183 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 32767);  // basic_lshift
    const uint_fast16_t tmp_190 = q_sign_extend_16(tmp_183);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_191 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_182), static_cast<uint_fast64_t>(tmp_190)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_192 = uint_fast16_t(tmp_191[0] & 65535);  // _basic_get_item_0
    const uint_fast16_t tmp_193 = uint_fast16_t(tmp_191[1] & 65535);  // _basic_get_item_1
    const uint_fast16_t tmp_194 = uint_fast16_t((tmp_192 + tmp_193) & 65535);  // basic_add
    return tmp_194;
}
static inline uint_fast16_t CSA_tree4_impl(uint_fast8_t arg_0, uint_fast16_t arg_1, uint_fast8_t arg_2, uint_fast8_t arg_3) {  // CSA_tree4
    // begin inline primitive CSA
    // begin inline primitive q_aligner
    const uint_fast8_t tmp = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast16_t tmp_7 = q_sign_extend(tmp);  // q_sign_extend
    const uint_fast16_t tmp_8 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(1 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_9 = q_sign_extend_1(tmp_8);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_10 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_7), static_cast<uint_fast64_t>(tmp_9)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_11 = uint_fast16_t(tmp_10[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_12 = uint_fast16_t(tmp_10[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_13 = uint_fast16_t((tmp_11 ^ tmp_12) & 4095);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_14 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_13) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_15 = q_sign_extend_1(tmp_14);  // q_sign_extend
    const uint_fast16_t tmp_16 = uint_fast16_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(arg_2) << uint_fast8_t(4 & 7))) & 511);  // basic_lshift
    const uint_fast16_t tmp_23 = q_sign_extend_2(tmp_16);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_24 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_15), static_cast<uint_fast64_t>(tmp_23)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_25 = uint_fast16_t(tmp_24[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_26 = uint_fast16_t(tmp_24[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_27 = uint_fast16_t((tmp_25 ^ tmp_26) & 4095);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_28 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast16_t tmp_29 = q_sign_extend(tmp_28);  // q_sign_extend
    const uint_fast16_t tmp_30 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(1 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_31 = q_sign_extend_1(tmp_30);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_32 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_29), static_cast<uint_fast64_t>(tmp_31)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_33 = uint_fast16_t(tmp_32[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_34 = uint_fast16_t(tmp_32[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_35 = uint_fast16_t((tmp_33 & tmp_34) & 4095);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_36 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_0) << uint_fast8_t(0 & 1))) & 127);  // basic_lshift
    const uint_fast16_t tmp_42 = q_sign_extend_3(tmp_36);  // q_sign_extend
    const uint_fast16_t tmp_43 = uint_fast16_t((uint_fast8_t(4 & 7) >= 64 ? 0 : (uint_fast64_t(arg_2) << uint_fast8_t(4 & 7))) & 511);  // basic_lshift
    const uint_fast16_t tmp_44 = q_sign_extend_4(tmp_43);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_45 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_42), static_cast<uint_fast64_t>(tmp_44)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_46 = uint_fast16_t(tmp_45[0] & 511);  // _basic_get_item_0
    const uint_fast16_t tmp_47 = uint_fast16_t(tmp_45[1] & 511);  // _basic_get_item_1
    const uint_fast16_t tmp_48 = uint_fast16_t((tmp_46 & tmp_47) & 511);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_49 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_35) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_50 = q_sign_extend_1(tmp_49);  // q_sign_extend
    const uint_fast16_t tmp_51 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_48) << uint_fast8_t(0 & 1))) & 511);  // basic_lshift
    const uint_fast16_t tmp_52 = q_sign_extend_2(tmp_51);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_53 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_50), static_cast<uint_fast64_t>(tmp_52)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_54 = uint_fast16_t(tmp_53[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_55 = uint_fast16_t(tmp_53[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_56 = uint_fast16_t((tmp_54 | tmp_55) & 4095);  // basic_or
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_57 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_1) << uint_fast8_t(0 & 1))) & 2047);  // basic_lshift
    const uint_fast16_t tmp_58 = q_sign_extend_5(tmp_57);  // q_sign_extend
    const uint_fast8_t tmp_59 = uint_fast8_t((uint_fast8_t(3 & 3) >= 64 ? 0 : (uint_fast64_t(arg_2) << uint_fast8_t(3 & 3))) & 255);  // basic_lshift
    const uint_fast16_t tmp_66 = q_sign_extend_6(tmp_59);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_67 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_58), static_cast<uint_fast64_t>(tmp_66)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_68 = uint_fast16_t(tmp_67[0] & 2047);  // _basic_get_item_0
    const uint_fast16_t tmp_69 = uint_fast16_t(tmp_67[1] & 2047);  // _basic_get_item_1
    const uint_fast16_t tmp_70 = uint_fast16_t((tmp_68 & tmp_69) & 2047);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_71 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_56) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_72 = q_sign_extend_1(tmp_71);  // q_sign_extend
    const uint_fast16_t tmp_73 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_70) << uint_fast8_t(1 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_74 = q_sign_extend_1(tmp_73);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_75 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_72), static_cast<uint_fast64_t>(tmp_74)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_76 = uint_fast16_t(tmp_75[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_77 = uint_fast16_t(tmp_75[1] & 4095);  // _basic_get_item_1
    const uint_fast16_t tmp_78 = uint_fast16_t((tmp_76 | tmp_77) & 4095);  // basic_or
    const uint_fast16_t tmp_85 = q_sign_extend_7(tmp_78);  // q_sign_extend
    const uint_fast16_t tmp_87 = q_lshift(tmp_85, uint_fast8_t(1 & 1));  // q_lshift
    const std::array<uint_fast64_t, 2> tmp_88 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_27), static_cast<uint_fast64_t>(tmp_87)};  // basic_tuple_maker_2
    // end inline primitive CSA
    const uint_fast16_t tmp_89 = uint_fast16_t(tmp_88[0] & 4095);  // _basic_get_item_0
    const uint_fast16_t tmp_90 = uint_fast16_t(tmp_88[1] & 8191);  // _basic_get_item_1
    // begin inline primitive CSA
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_91 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_3) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast16_t tmp_98 = q_sign_extend_8(tmp_91);  // q_sign_extend
    const uint_fast16_t tmp_99 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_89) << uint_fast8_t(1 & 1))) & 8191);  // basic_lshift
    const uint_fast16_t tmp_100 = q_sign_extend_9(tmp_99);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_101 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_98), static_cast<uint_fast64_t>(tmp_100)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_102 = uint_fast16_t(tmp_101[0] & 8191);  // _basic_get_item_0
    const uint_fast16_t tmp_103 = uint_fast16_t(tmp_101[1] & 8191);  // _basic_get_item_1
    const uint_fast16_t tmp_104 = uint_fast16_t((tmp_102 ^ tmp_103) & 8191);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_105 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_104) << uint_fast8_t(0 & 1))) & 8191);  // basic_lshift
    const uint_fast16_t tmp_112 = q_sign_extend_10(tmp_105);  // q_sign_extend
    const uint_fast16_t tmp_113 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_90) << uint_fast8_t(1 & 1))) & 16383);  // basic_lshift
    const uint_fast16_t tmp_114 = q_sign_extend_11(tmp_113);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_115 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_112), static_cast<uint_fast64_t>(tmp_114)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_116 = uint_fast16_t(tmp_115[0] & 16383);  // _basic_get_item_0
    const uint_fast16_t tmp_117 = uint_fast16_t(tmp_115[1] & 16383);  // _basic_get_item_1
    const uint_fast16_t tmp_118 = uint_fast16_t((tmp_116 ^ tmp_117) & 16383);  // basic_xor
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_119 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_3) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast16_t tmp_120 = q_sign_extend_8(tmp_119);  // q_sign_extend
    const uint_fast16_t tmp_121 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_89) << uint_fast8_t(1 & 1))) & 8191);  // basic_lshift
    const uint_fast16_t tmp_122 = q_sign_extend_9(tmp_121);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_123 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_120), static_cast<uint_fast64_t>(tmp_122)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_124 = uint_fast16_t(tmp_123[0] & 8191);  // _basic_get_item_0
    const uint_fast16_t tmp_125 = uint_fast16_t(tmp_123[1] & 8191);  // _basic_get_item_1
    const uint_fast16_t tmp_126 = uint_fast16_t((tmp_124 & tmp_125) & 8191);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast8_t tmp_127 = uint_fast8_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(arg_3) << uint_fast8_t(0 & 1))) & 63);  // basic_lshift
    const uint_fast16_t tmp_133 = q_sign_extend_12(tmp_127);  // q_sign_extend
    const uint_fast16_t tmp_134 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_90) << uint_fast8_t(1 & 1))) & 16383);  // basic_lshift
    const uint_fast16_t tmp_135 = q_sign_extend_11(tmp_134);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_136 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_133), static_cast<uint_fast64_t>(tmp_135)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_137 = uint_fast16_t(tmp_136[0] & 16383);  // _basic_get_item_0
    const uint_fast16_t tmp_138 = uint_fast16_t(tmp_136[1] & 16383);  // _basic_get_item_1
    const uint_fast16_t tmp_139 = uint_fast16_t((tmp_137 & tmp_138) & 16383);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_140 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_126) << uint_fast8_t(0 & 1))) & 8191);  // basic_lshift
    const uint_fast16_t tmp_141 = q_sign_extend_10(tmp_140);  // q_sign_extend
    const uint_fast16_t tmp_142 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_139) << uint_fast8_t(0 & 1))) & 16383);  // basic_lshift
    const uint_fast16_t tmp_143 = q_sign_extend_11(tmp_142);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_144 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_141), static_cast<uint_fast64_t>(tmp_143)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_145 = uint_fast16_t(tmp_144[0] & 16383);  // _basic_get_item_0
    const uint_fast16_t tmp_146 = uint_fast16_t(tmp_144[1] & 16383);  // _basic_get_item_1
    const uint_fast16_t tmp_147 = uint_fast16_t((tmp_145 | tmp_146) & 16383);  // basic_or
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_148 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_89) << uint_fast8_t(0 & 1))) & 4095);  // basic_lshift
    const uint_fast16_t tmp_149 = q_sign_extend_7(tmp_148);  // q_sign_extend
    const uint_fast16_t tmp_150 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_90) << uint_fast8_t(0 & 1))) & 8191);  // basic_lshift
    const uint_fast16_t tmp_151 = q_sign_extend_13(tmp_150);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_152 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_149), static_cast<uint_fast64_t>(tmp_151)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_153 = uint_fast16_t(tmp_152[0] & 8191);  // _basic_get_item_0
    const uint_fast16_t tmp_154 = uint_fast16_t(tmp_152[1] & 8191);  // _basic_get_item_1
    const uint_fast16_t tmp_155 = uint_fast16_t((tmp_153 & tmp_154) & 8191);  // basic_and
    // begin inline primitive q_aligner
    const uint_fast16_t tmp_156 = uint_fast16_t((uint_fast8_t(0 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_147) << uint_fast8_t(0 & 1))) & 16383);  // basic_lshift
    const uint_fast16_t tmp_157 = q_sign_extend_11(tmp_156);  // q_sign_extend
    const uint_fast16_t tmp_158 = uint_fast16_t((uint_fast8_t(1 & 1) >= 64 ? 0 : (uint_fast64_t(tmp_155) << uint_fast8_t(1 & 1))) & 16383);  // basic_lshift
    const uint_fast16_t tmp_159 = q_sign_extend_11(tmp_158);  // q_sign_extend
    const std::array<uint_fast64_t, 2> tmp_160 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_157), static_cast<uint_fast64_t>(tmp_159)};  // basic_tuple_maker_2
    // end inline primitive q_aligner
    const uint_fast16_t tmp_161 = uint_fast16_t(tmp_160[0] & 16383);  // _basic_get_item_0
    const uint_fast16_t tmp_162 = uint_fast16_t(tmp_160[1] & 16383);  // _basic_get_item_1
    const uint_fast16_t tmp_163 = uint_fast16_t((tmp_161 | tmp_162) & 16383);  // basic_or
    const uint_fast16_t tmp_170 = q_sign_extend_14(tmp_163);  // q_sign_extend
    const uint_fast16_t tmp_172 = q_lshift_1(tmp_170, uint_fast8_t(1 & 1));  // q_lshift
    const std::array<uint_fast64_t, 2> tmp_173 = std::array<uint_fast64_t, 2>{static_cast<uint_fast64_t>(tmp_118), static_cast<uint_fast64_t>(tmp_172)};  // basic_tuple_maker_2
    // end inline primitive CSA
    const uint_fast16_t tmp_174 = uint_fast16_t(tmp_173[0] & 16383);  // _basic_get_item_0
    const uint_fast16_t tmp_175 = uint_fast16_t(tmp_173[1] & 32767);  // _basic_get_item_1
    const uint_fast16_t tmp_195 = q_add(tmp_174, tmp_175);  // q_add
    return tmp_195;
}
extern "C" inline uint_fast16_t CSA_tree4(uint_fast8_t arg_0, uint_fast16_t arg_1, uint_fast8_t arg_2, uint_fast8_t arg_3) {
    return CSA_tree4_impl((arg_0 & 127), (arg_1 & 2047), (arg_2 & 31), (arg_3 & 63));
}