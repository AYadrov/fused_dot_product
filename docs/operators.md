# Operator and Primitive Reference
Row-per-operator index. Types are inlined in the Inputs/Output columns (e.g., `x[UQ]`, `n[int]`).

## Basic bitwise/arithmetic ops (`numtypes/basics.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `basic_mux_2_1` | Op | `sel`, `in0`, `in1`, `out` | `out` | 2:1 mux. |
| `basic_add` | Op | `x`, `y`, `out` | `out` | Aligned addition. |
| `basic_sub` | Op | `x`, `y`, `out` | `out` | Aligned subtraction. |
| `basic_mul` | Op | `x`, `y`, `out` | `out` | Aligned multiplication. |
| `basic_max` | Op | `x`, `y`, `out` | `out` | Bitwise max. |
| `basic_min` | Op | `x`, `y`, `out` | `out` | Bitwise min. |
| `basic_rshift` | Op | `x`, `amount`, `out` | `out` | Logical right shift. |
| `basic_lshift` | Op | `x`, `amount`, `out` | `out` | Logical left shift. |
| `basic_or` | Op | `x`, `y`, `out` | `out` | Bitwise OR. |
| `basic_xor` | Op | `x`, `y`, `out` | `out` | Bitwise XOR. |
| `basic_and` | Op | `x`, `y`, `out` | `out` | Bitwise AND. |
| `basic_concat` | Op | `x`, `y`, `out` | `out` | Bitwise concatenate. |
| `basic_select` | Op | `x`, `start`, `end`, `out` | `out` | Inclusive bit slice. |
| `basic_invert` | Op | `x`, `out` | `out` | Bitwise NOT. |
| `basic_identity` | Op | `x`, `out` | `out` | Identity/cast. |
| `basic_or_reduce` | Op | `x`, `out` | `out` | OR-reduce across bits. |
| `basic_and_reduce` | Op | `x`, `out` | `out` | AND-reduce across bits. |

## Unsigned fixed-point primitives (`numtypes/UQ.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_uq_select_shape` | Op | `x[UQ]`, `start[int]`, `end[int]` | `Tuple[int_bits, frac_bits]` | Determine slice shape. |
| `_uq_alloc` | Op | `int_bits[Any]`, `frac_bits[Any]` | `UQ<int_bits, frac_bits>` | Allocate UQ of given width. |
| `_uq_frac_bits` | Op | `x[UQ]` | `UQ<int>` | Extract fractional width. |
| `_uq_int_bits` | Op | `x[UQ]` | `UQ<int>` | Extract integer width. |
| `_uq_aligner` | Composite | `x[UQ]`, `y[UQ]` | `Tuple[UQ, UQ]` | Align two UQs to common width. |
| `uq_zero_extend` | Primitive | `x[UQ]`, `n[int]` | `UQ` | Pad high bits with `n` zeros. |
| `uq_add` | Primitive | `x[UQ]`, `y[UQ]` | `UQ` | Unsigned add with alignment. |
| `uq_sub` | Primitive | `x[UQ]`, `y[UQ]` | `UQ` | Unsigned subtract with alignment. |
| `uq_max` | Primitive | `x[UQ]`, `y[UQ]` | `UQ` | Unsigned max. |
| `uq_min` | Primitive | `x[UQ]`, `y[UQ]` | `UQ` | Unsigned min. |
| `uq_mul` | Primitive | `x[UQ]`, `y[UQ]` | `UQ` | Unsigned multiply. |
| `uq_to_q` | Primitive | `x[UQ]` | `Q` | Convert to signed (adds sign bit). |
| `uq_rshift` | Primitive | `x[UQ]`, `amount[Any]` | `UQ` | Logical right shift with resize. |
| `uq_lshift` | Primitive | `x[UQ]`, `amount[Any]` | `UQ` | Logical left shift with resize. |
| `uq_select` | Primitive | `x[UQ]`, `start[int]`, `end[int]` | `UQ` | Bit slice. |
| `uq_resize` | Primitive | `x[UQ]`, `int_bits[int]`, `frac_bits[int]` | `UQ` | Resize/round toward zero. |

## Signed fixed-point primitives (`numtypes/Q.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_q_alloc` | Op | `int_bits[Any]`, `frac_bits[Any]` | `Q` | Allocate signed width. |
| `q_aligner` | Composite | `x[Q]`, `y[Q]` | `Tuple[Q,Q]` | Align two Qs to common width. |
| `_q_frac_bits` | Op | `x[Q]` | `UQ` | Extract fractional width. |
| `_q_int_bits` | Op | `x[Q]` | `UQ` | Extract integer width. |
| `_q_is_min_val` | Op | `x[Q]` | `UQ<1,0>` | Detect min representable value. |
| `q_sign_bit` | Primitive | `x[Q]` | `UQ<1,0>` | MSB of two's complement value. |
| `q_sign_extend` | Primitive | `x[Q]`, `n[int]` | `Q` | Extend sign into high bits. |
| `q_neg` | Primitive | `x[Q]` | `Q` | Two's complement negate (with min guard). |
| `q_add` | Primitive | `x[Q]`, `y[Q]` | `Q` | Signed addition with alignment. |
| `q_sub` | Primitive | `x[Q]`, `y[Q]` | `Q` | Signed subtraction with alignment. |
| `q_lshift` | Primitive | `x[Q]`, `n[Any]` | `Q` | Logical left shift with resize. |
| `q_to_uq` | Primitive | `x[Q]` | `UQ` | Drop sign bit. |
| `q_rshift` | Primitive | `x[Q]`, `n[Any]` | `Q` | Arithmetic right shift with resize. |
| `q_add_sign` | Primitive | `x[Q]`, `s[UQ<1,0>]` | `Q` | Apply sign bit to unsigned magnitude. |
| `q_abs` | Primitive | `x[Q]` | `Q` | Absolute value (safe at min). |

## BF16 helpers (`numtypes/BFloat16.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_bf16_mantissa` | Op | `x[BFloat16]` | `UQ<7,0>` | Extract mantissa bits. |
| `_bf16_exponent` | Op | `x[BFloat16]` | `UQ<8,0>` | Extract exponent bits. |
| `_bf16_sign` | Op | `x[BFloat16]` | `UQ<1,0>` | Extract sign bit. |
| `bf16_decode` | Primitive | `x[BFloat16]` | `Tuple[UQ<1,0>, UQ<7,0>, UQ<8,0>]` | Split BF16 into components. |

## Float helpers (`numtypes/Float.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_float32_alloc` | Op | `sign_bit[UQ<1,0>]`, `mantissa[UQ]`, `exponent[UQ]` | `Float32` | Assemble FP32 from fields. |

## Composite helpers (`utils/composites.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `mantissa_add_implicit_bit` | Composite | `mantissa[UQ<7,0>]` | `UQ<1.x>` | Prefix implicit leading 1. |
| `sign_xor` | Primitive | `x[UQ<1,0>]`, `y[UQ<1,0>]` | `UQ<1,0>` | Combine sign bits. |
| `OPTIMIZED_MAX_EXP4` | Primitive | `e0..e3[UQ]` | `UQ` | Max of four exponents via bitwise tree. |

## Carry-save adder (`designs/CSA.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `CSA_tree4` | Composite | `m0..m3[Q]` | `Q` | 4-input CSA tree with width alignment. |

## Float32 encoder (`designs/encode_Float32.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `round_to_the_nearest_even` | Primitive | `m[UQ]`, `e[UQ]`, `target_bits[int]` | `Tuple[m,e]` | G/R/S rounding and exponent adjust. |
| `lzc` | Primitive | `x[UQ]` | `UQ` | Leading-zero count. |
| `normalize_to_1_xxx` | Primitive | `m[UQ]`, `e[Q]` | `Tuple[m,e]` | Normalize mantissa/exponent toward 1.xxx. |
| `encode_Float32` | Primitive | `m[Q]`, `e[Q]` | `Float32` | Pack sign, exponent, mantissa with subnormal/inf/nan handling. |

## Optimized design helpers (`designs/optimized.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_est_global_shift` | Primitive | `E_max[UQ]`, `E_p[UQ]` | `UQ` | Compute global shift = `(E_max - E_p)*2^s`. |
| `_est_local_shift` | Primitive | `E_p[UQ]` | `UQ` | Invert low `s` exponent bits for local alignment. |
| `_prepend_ones` | Primitive | `x[UQ]` | `UQ` | Append `s` ones to exponent for normalization. |

## Designs (full composites)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `Conventional` | Composite | `a0..a3[BFloat16]`, `b0..b3[BFloat16]` | `Float32` | Baseline BF16 dot product (max exponent + global shift). |
| `Optimized` | Composite | `a0..a3[BFloat16]`, `b0..b3[BFloat16]` | `Float32` | Fused design with shared exponent estimation and local/global shifting. |
