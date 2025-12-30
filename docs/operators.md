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
| `basic_identity` | Op | `x`, `out` | `out` | Identity/cast |
| `basic_or_reduce` | Op | `x`, `out` | `out` | OR-reduce across bits. |
| `basic_and_reduce` | Op | `x`, `out` | `out` | AND-reduce across bits. |

## Unsigned fixed-point primitives (`numtypes/UQ.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| Private | | | |
| `_uq_select_shape` | Op | `x`, `start`, `end` | `Tuple[int_bits, frac_bits]` | Determine slice shape. |
| `_uq_alloc` | Op | `int_bits`, `frac_bits` | `UQ` | Allocate dynamically UQ of given width. |
| `_uq_frac_bits` | Op | `x` | `UQ` | Extract fractional width. |
| `_uq_int_bits` | Op | `x` | `UQ` | Extract integer width. |
| `_uq_aligner` | Composite | `x`, `y`, aggregators | aligned `x`, `y` | Internal aligner. |
| Public | | | |
| `uq_zero_extend` | Primitive | `x`, `n` | widened `UQ` | Pad high `n` bits with zeros. |
| `uq_add` | Primitive | `x`, `y` | `UQ` | Addition of two `UQ`s with proper alignment. |
| `uq_sub` | Primitive | `x`, `y` | `UQ` | Subtraction of two `UQ`s with proper alignment. |
| `uq_max` | Primitive | `x`, `y` | `UQ` | Max of two `UQ`s with proper alignment. |
| `uq_min` | Primitive | `x`, `y` | `UQ` | Min of two `UQ`s with proper alignment. |
| `uq_mul` | Primitive | `x`, `y` | `UQ` | Multiplication of two `UQ`s with proper alignment. |
| `uq_to_q` | Primitive | `x` | `Q` | Convert `UQ` to `Q` (adds sign bit). |
| `uq_rshift` | Primitive | `x`, `amount` | `UQ` | Logical right shift without resize. |
| `uq_lshift` | Primitive | `x`, `amount` | `UQ` | Logical left shift without resize. |
| `uq_select` | Primitive | `x`, `start`, `end` | `UQ` | Bit slice. |
| `uq_resize` | Primitive | `x`, `int_bits`, `frac_bits` | `UQ` | Resize/round toward zero. |

## Signed fixed-point primitives (`numtypes/Q.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| Private | | | |
| `_q_alloc` | Op | `int_bits`, `frac_bits` | `Q` | Allocate signed width. |
| `q_aligner` | Composite | `x`, `y`, aggregators | aligned `x`, `y` | Common aligner for Q ops. |
| `_q_frac_bits` | Op | `x` | `UQ` | Extract fractional width. |
| `_q_int_bits` | Op | `x` | `UQ` | Extract integer width. |
| `_q_is_min_val` | Op | `x` | `UQ<1,0>` | Detect min representable value. |
| Public | | | |
| `q_sign_bit` | Primitive | `x` | `UQ<1,0>` | MSB of a signed fixed point. |
| `q_sign_extend` | Primitive | `x`, `n` | widened `Q` | Extend sign by high `n` bits. |
| `q_neg` | Primitive | `x` | `Q` | `Q` negate (with min guard). |
| `q_add` | Primitive | `x`, `y` | `Q` | Addition of two Qs with proper alignment. |
| `q_sub` | Primitive | `x`, `y` | `Q` | Subtraction of two Qs with proper alignment.  |
| `q_lshift` | Primitive | `x`, `n` | `Q` | Logical left shift without resize. |
| `q_to_uq` | Primitive | `x` | `UQ` | Drops sign bit. |
| `q_rshift` | Primitive | `x`, `n` | `Q` | Arithmetic right shift without resize. |
| `q_add_sign` | Primitive | `x`, `s` | `Q` | Apply sign bit `s` to unsigned magnitude. |
| `q_abs` | Primitive | `x` | `Q` | Absolute value of `Q` (safe at min). |

## BF16 helpers (`numtypes/BFloat16.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| Private | | | |
| `_bf16_mantissa` | Op | `x` | `UQ<7,0>` | Extract mantissa bits. |
| `_bf16_exponent` | Op | `x` | `UQ<8,0>` | Extract exponent bits. |
| `_bf16_sign` | Op | `x` | `UQ<1,0>` | Extract sign bit. |
| Public | | | |
| `bf16_decode` | Primitive | `x` | `Tuple[UQ<1,0>, UQ<7,0>, UQ<8,0>]` | Split BF16 into components. |

## Float helpers (`numtypes/Float.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| Private | | | |
| `_float32_alloc` | Op | `sign_bit`, `mantissa`, `exponent` | `Float32` | Assemble FP32 from fields. |

## Composite helpers (`utils/composites.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `mantissa_add_implicit_bit` | Composite | `mantissa` | `UQ<1.x>` | Prefix implicit leading 1. |
| `sign_xor` | Primitive | `x`, `y` | `UQ<1,0>` | Combine sign bits. |
| `OPTIMIZED_MAX_EXP4` | Primitive | `e0..e3` | `UQ` | Max of four exponents via an optimized bitwise tree. |

## Carry-save adder (`designs/CSA.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `CSA_tree4` | Composite | `m0..m3` | `Q` | 4-input CSA tree with width alignment. |

## Float32 encoder (`designs/encode_Float32.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `round_to_the_nearest_even` | Primitive | `m`, `e`, `target_bits` | `Tuple[m,e]` | G/R/S rounding and exponent adjust. |
| `lzc` | Primitive | `x` | `UQ` | Leading-zero count. |
| `normalize_to_1_xxx` | Primitive | `m`, `e` | `Tuple[m,e]` | Normalize mantissa/exponent toward 1.xxx. |
| `encode_Float32` | Primitive | `m`, `e` | `Float32` | Pack sign, exponent, mantissa with subnormal/inf/nan handling. |

## Optimized design helpers (`designs/optimized.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_est_global_shift` | Primitive | `E_max`, `E_p` | `UQ` | Compute global shift = `(E_max - E_p)*2^s`. |
| `_est_local_shift` | Primitive | `E_p` | `UQ` | Invert low `s` exponent bits for local alignment. |
| `_prepend_ones` | Primitive | `x` | `UQ` | Append `s` ones to exponent for normalization. |

## Designs (full composites)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `Conventional` | Composite | `a0..a3`, `b0..b3` | `Float32` | Conventional BF16 dot product (max exponent + global shift). |
| `Optimized` | Composite | `a0..a3`, `b0..b3` | `Float32` | Optimized BF16 dot product (max exponent + local shift + global shift). |
