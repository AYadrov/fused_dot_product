### Type notation
- `Q<I,F>`: signed fixed-point with `I` integer and `F` fractional bits; `UQ<I,F>` unsigned.
- `BFloat16`, `Float32`: IEEE754 formats.
- `T`: arbitrary bitvector type, `Any`: unconstrained node chosen by caller.
- `x`: tuple: explicit output node supplied by caller (shape must match the result).
- `n<int>, s<int> etc.`: literal integers passed as Python args, not nodes.

## Basic bitwise/arithmetic ops (`numtypes/basics.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `basic_mux_2_1` | Op | `Any -> Any -> Any -> T -> T` | 2:1 mux. |
| `basic_add` | Op | `Any -> Any -> T -> T` | Aligned addition. |
| `basic_sub` | Op | `Any -> Any -> T -> T` | Aligned subtraction. |
| `basic_mul` | Op | `Any -> Any -> T -> T` | Aligned multiplication. |
| `basic_max` | Op | `Any -> Any -> T -> T` | Bitwise max. |
| `basic_min` | Op | `Any -> Any -> T -> T` | Bitwise min. |
| `basic_rshift` | Op | `Any -> Any -> T -> T` | Logical right shift. |
| `basic_lshift` | Op | `Any -> Any -> T -> T` | Logical left shift. |
| `basic_or` | Op | `Any -> Any -> T -> T` | Bitwise OR. |
| `basic_xor` | Op | `Any -> Any -> T -> T` | Bitwise XOR. |
| `basic_and` | Op | `Any -> Any -> T -> T` | Bitwise AND. |
| `basic_concat` | Op | `Any -> Any -> T -> T` | Concatenate bits. |
| `basic_select` | Op | `Any -> int -> int -> T -> T` | Inclusive slice `[start:end]`. |
| `basic_invert` | Op | `Any -> T -> T` | Bitwise NOT. |
| `basic_identity` | Op | `Any -> T -> T` | Identity/cast. |
| `basic_or_reduce` | Op | `Any -> T -> T` | OR-reduce across bits. |
| `basic_and_reduce` | Op | `Any -> T -> T` | AND-reduce across bits. |

## Unsigned fixed-point primitives (`numtypes/UQ.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `uq_aligner` | Primitive | `UQ<I1,F1> -> UQ<I2,F2> -> int_aggr<int -> int -> int> -> frac_aggr<int -> int -> int> -> (UQ<int_aggr(I1,I2), frac_aggr(F1,F2)> x UQ<int_aggr(I1,I2), frac_aggr(F1,F2)>)` | Align two UQs to a common width. |
| `uq_zero_extend` | Primitive | `UQ<I,F> -> n<int> -> UQ<I+n,F>` | Pad high bits with `n` zeros. |
| `uq_add` | Primitive | `UQ<I1,F1> -> UQ<I2,F2> -> UQ<max(I1,I2)+1, max(F1,F2)>` | Unsigned add with alignment and carry bit. |
| `uq_sub` | Primitive | `UQ<I1,F1> -> UQ<I2,F2> -> UQ<max(I1,I2)+1, max(F1,F2)>` | Unsigned subtract with alignment and borrow bit. |
| `uq_max` | Primitive | `UQ<I1,F1> -> UQ<I2,F2> -> UQ<max(I1,I2), max(F1,F2)>` | Unsigned max with alignment. |
| `uq_min` | Primitive | `UQ<I1,F1> -> UQ<I2,F2> -> UQ<max(I1,I2), max(F1,F2)>` | Unsigned min with alignment. |
| `uq_mul` | Primitive | `UQ<I1,F1> -> UQ<I2,F2> -> UQ<I1+I2, F1+F2>` | Unsigned multiply (full precision). |
| `uq_to_q` | Primitive | `UQ<I,F> -> Q<I+1,F>` | Convert to signed (adds sign bit). |
| `uq_rshift` | Primitive | `UQ<I,F> -> Any -> UQ<I,F>` | Logical right shift without resize. |
| `uq_lshift` | Primitive | `UQ<I,F> -> Any -> UQ<I,F>` | Logical left shift without resize. |
| `uq_select` | Primitive | `UQ<I,F> -> start<int> -> end<int> -> UQ<(start-end+1)-k, k>` where `k = max(0, min(start, F-1)-end+1)` | Bit slice with fractional portion preserved when slicing frac bits. |
| `uq_resize` | Primitive | `UQ<I,F> -> I*<int> -> F*<int> -> UQ<I*, F*>` | Resize/round toward zero (no truncation allowed). |

## Signed fixed-point primitives (`numtypes/Q.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `q_aligner` | Primitive | `Q<I1,F1> -> Q<I2,F2> -> int_aggr<int -> int -> int> -> frac_aggr<int -> int -> int> -> (Q<int_aggr(I1,I2), frac_aggr(F1,F2)> x Q<int_aggr(I1,I2), frac_aggr(F1,F2)>)` | Align two Qs to a common width. |
| `q_sign_bit` | Primitive | `Q<I,F> -> UQ<1,0>` | MSB of two's complement value. |
| `q_sign_extend` | Primitive | `Q<I,F> -> n<int> -> Q<I+n, F>` | Extend sign into high bits. |
| `q_neg` | Primitive | `Q<I,F> -> Q<I,F>` | Two's complement negate (special-case overflow at min). |
| `q_add` | Primitive | `Q<I1,F1> -> Q<I2,F2> -> Q<max(I1,I2)+1, max(F1,F2)>` | Signed addition with alignment. |
| `q_sub` | Primitive | `Q<I1,F1> -> Q<I2,F2> -> Q<max(I1,I2)+1, max(F1,F2)>` | Signed subtraction with alignment. |
| `q_lshift` | Primitive | `Q<I,F> -> Any -> Q<I,F>` | Logical left shift without resize. |
| `q_rshift` | Primitive | `Q<I,F> -> Any -> Q<I,F>` | Arithmetic right shift without resize. |
| `q_to_uq` | Primitive | `Q<I,F> -> UQ<max(I-1,0), F>` | Drop sign bit (assumes non-negative). |
| `q_add_sign` | Primitive | `Q<I,F> -> UQ<1,0> -> Q<I,F>` | Apply sign bit to unsigned magnitude. |
| `q_abs` | Primitive | `Q<I,F> -> Q<I,F>` | Absolute value (safe at min). |

## BF16 helpers (`numtypes/BFloat16.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `_bf16_mantissa` | Op | `BFloat16 -> UQ<7,0>` | Extract mantissa bits. |
| `_bf16_exponent` | Op | `BFloat16 -> UQ<8,0>` | Extract exponent bits. |
| `_bf16_sign` | Op | `BFloat16 -> UQ<1,0>` | Extract sign bit. |
| `bf16_decode` | Primitive | `BFloat16 -> (UQ<1,0> x UQ<7,0> x UQ<8,0>)` | Split BF16 into sign/mantissa/exponent. |

## Float helpers (`numtypes/Float.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `_float32_alloc` | Op | `UQ<1,0> -> UQ<23,0> -> UQ<8,0> -> Float32` | Assemble FP32 from sign, mantissa, exponent fields. |

## Composite helpers (`utils/composites.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `mantissa_add_implicit_bit` | Composite | `UQ<I,0> -> UQ<1,I>` | Prefix implicit leading 1. |
| `sign_xor` | Primitive | `UQ<1,0> -> UQ<1,0> -> UQ<1,0>` | XOR sign bits. |
| `OPTIMIZED_MAX_EXP4` | Primitive | `UQ<I0,0> -> UQ<I1,0> -> UQ<I2,0> -> UQ<I3,0> -> UQ<max(I0,I1,I2,I3), 0>` | Max of four exponents via bitwise tree. |

## Carry-save adder (`designs/CSA.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `CSA_tree4` | Composite | `Q<I0,F0> -> Q<I1,F1> -> Q<I2,F2> -> Q<I3,F3> -> Q<max(I0, I1, I2, I3)+3, max(F0, F1, F2, F3)>` | 4-input CSA tree with width alignment. |

## Float32 encoder (`designs/encode_Float32.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `round_to_the_nearest_even` | Primitive | `UQ<I,F> -> UQ<E,0> -> target_bits<int> -> (UQ<min(I, t), max(t - I, 0)> x UQ<E+1,0>)` | Guard/round/sticky rounding of mantissa and exponent bump. |
| `lzc` | Primitive | `UQ<I,F> -> UQ<ceil(log2(I+F+1)), 0>` | Leading-zero count. |
| `normalize_to_1_xxx` | Primitive | `UQ<I,F> -> Q<E,0> -> (UQ<1, max(I-1,0)+F> x Q<e_width(I,F,E), 0>)` | Normalize mantissa to `1.xxx`; `e_width = max(E, max(ceil(log2(I+F+1))+1, bitlen(I)+1)+2)+1`. |
| `encode_Float32` | Primitive | `Q<I,F> -> Q<E,0> -> Float32` | Pack sign, exponent, mantissa with subnormal/inf/nan handling. |

## Optimized design helpers (`designs/optimized.py`)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `_est_global_shift` | Primitive | `UQ<I,0> -> UQ<J,0> -> s<int> -> UQ<I+s,0>` | Compute global shift `(E_max - E_p) * 2^s`. |
| `_est_local_shift` | Primitive | `UQ<I,0> -> s<int> -> UQ<s,0>` | Invert low `s` exponent bits for local alignment. |
| `_prepend_ones` | Primitive | `UQ<I,0> -> s<int> -> UQ<I+s,0>` | Append `s` ones to exponent for normalization. |

## Designs (full composites)
| Name | Kind | Type | Purpose/Notes |
| --- | --- | --- | --- |
| `Conventional` | Composite | `BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> Float32` | Baseline BF16 dot product (max exponent + global shift). |
| `Optimized` | Composite | `BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> BFloat16 -> Float32` | Fused design with shared exponent estimation and local/global shifting. |
