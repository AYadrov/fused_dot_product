# Operator and Primitive Reference
Row-per-operator index. Kind uses repo terminology: Op (pure bit op), Primitive (typed wrapper), Composite (multi-node implementation).

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
| `basic_concat` | Op | `x`, `y`, `out` | concat | Bitwise concatenate. |
| `basic_select` | Op | `x`, `start`, `end`, `out` | slice | Inclusive bit slice. |
| `basic_invert` | Op | `x`, `out` | `out` | Bitwise NOT. |
| `basic_identity` | Op | `x`, `out` | `out` | Width-cast/forward. |
| `basic_or_reduce` | Op | `x`, `out` | 1-bit | OR-reduce across bits. |
| `basic_and_reduce` | Op | `x`, `out` | 1-bit | AND-reduce across bits. |

## Unsigned fixed-point primitives (`numtypes/UQ.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_uq_select_shape` | Op | `x`, `start`, `end` | `Tuple[int_bits, frac_bits]` | Determine slice shape. |
| `_uq_alloc` | Op | `int_bits`, `frac_bits` | `UQ` | Allocate UQ of given width. |
| `_uq_frac_bits` | Op | `x` | `UQ` | Extract fractional width. |
| `_uq_int_bits` | Op | `x` | `UQ` | Extract integer width. |
| `_uq_aligner` | Composite | `x`, `y`, aggregators | aligned `x`, `y` | Internal aligner used by arithmetic. |
| `uq_zero_extend` | Primitive | `x`, `n` | widened `UQ` | Pad high bits with zeros. |
| `uq_add` | Primitive | `x`, `y` | `UQ` | Unsigned add with alignment. |
| `uq_sub` | Primitive | `x`, `y` | `UQ` | Unsigned subtract with alignment. |
| `uq_max` | Primitive | `x`, `y` | `UQ` | Unsigned max. |
| `uq_min` | Primitive | `x`, `y` | `UQ` | Unsigned min. |
| `uq_mul` | Primitive | `x`, `y` | `UQ` | Unsigned multiply. |
| `uq_to_q` | Primitive | `x` | `Q` | Convert to signed (adds sign bit). |
| `uq_rshift` | Primitive | `x`, `amount` | `UQ` | Logical right shift with resize. |
| `uq_lshift` | Primitive | `x`, `amount` | `UQ` | Logical left shift with resize. |
| `uq_select` | Primitive | `x`, `start`, `end` | `UQ` slice | Bit slice. |
| `uq_resize` | Primitive | `x`, `int_bits`, `frac_bits` | `UQ` | Resize/round toward zero. |

## Signed fixed-point primitives (`numtypes/Q.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_q_alloc` | Op | `int_bits`, `frac_bits` | `Q` | Allocate signed width. |
| `q_aligner` | Composite | `x`, `y`, aggregators | aligned `x`, `y` | Common aligner for Q ops. |
| `_q_frac_bits` | Op | `x` | `UQ` | Extract fractional width. |
| `_q_int_bits` | Op | `x` | `UQ` | Extract integer width. |
| `_q_is_min_val` | Op | `x` | `UQ<1,0>` | Detect min representable value. |
| `q_sign_bit` | Primitive | `x` | `UQ<1,0>` | MSB of two's complement value. |
| `q_sign_extend` | Primitive | `x`, `n` | widened `Q` | Extend sign into high bits. |
| `q_neg` | Primitive | `x` | `Q` | Two's complement negate (with min guard). |
| `q_add` | Primitive | `x`, `y` | `Q` | Signed addition with alignment. |
| `q_sub` | Primitive | `x`, `y` | `Q` | Signed subtraction with alignment. |
| `q_lshift` | Primitive | `x`, `n` | `Q` | Logical left shift with resize. |
| `q_to_uq` | Primitive | `x` | `UQ` | Drop sign bit. |
| `q_rshift` | Primitive | `x`, `n` | `Q` | Arithmetic right shift with resize. |
| `q_add_sign` | Primitive | `x`, `s` | `Q` | Apply sign bit to unsigned magnitude. |
| `q_abs` | Primitive | `x` | `Q` | Absolute value (safe at min). |

## BF16 helpers (`numtypes/BFloat16.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_bf16_mantissa` | Op | `x` | `UQ<7,0>` | Extract mantissa bits. |
| `_bf16_exponent` | Op | `x` | `UQ<8,0>` | Extract exponent bits. |
| `_bf16_sign` | Op | `x` | `UQ<1,0>` | Extract sign bit. |
| `bf16_decode` | Primitive | `x` | `Tuple[sign, mantissa, exponent]` | Split BF16 into components. |

## Float helpers (`numtypes/Float.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `_float32_alloc` | Op | `sign_bit`, `mantissa_bits`, `exponent_bits`, `mantissa`, `exponent` | `Float32` | Assemble FP32 from fields. |

## Composite helpers (`utils/composites.py`)
| Name | Kind | Inputs | Output | Purpose/Notes |
| --- | --- | --- | --- | --- |
| `mantissa_add_implicit_bit` | Composite | `mantissa` | `UQ1.x` | Prefix implicit leading 1. |
| `sign_xor` | Primitive | `x`, `y` | `UQ<1,0>` | Combine sign bits. |
| `OPTIMIZED_MAX_EXP4` | Primitive | `e0..e3` | `UQ` | Max of four exponents via bitwise tree. |

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
| `Conventional` | Composite | `a0..a3`, `b0..b3` | `Float32` | Baseline BF16 dot product (max exponent + global shift). |
| `Optimized` | Composite | `a0..a3`, `b0..b3` | `Float32` | Fused design with shared exponent estimation and local/global shifting. |

## Tips for extending
- Reuse `_uq_*`/`_q_*` helpers to keep widths consistent; most assertion errors come from mismatched shapes.
- Prefer composing from `basic_*` plus `uq_*`/`q_*` rather than raw bit fiddling—static/dynamic checks then guard you.
- When adding a new composite, implement `spec`, `impl`, and `sign` so the AST can typecheck and evaluate both spec and implementation.
