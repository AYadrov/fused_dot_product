# FP32 IEEE Adder Demo

This demo shows the verifier proving the FP32 IEEE adder implementation, then finding counterexamples after two small mistakes are introduced in the concept specification.

## 1. Connect

Use the `artemya` account:

```sh
ssh artemya@nightly.cs.washington.edu
```

## 2. Enter The Project

The `special-values2` branch should already be active on the demo machine.

```sh
cd fused_dot_product
```

## 3. Set A Memory Limit

Set this in the same shell that will run the proof. It avoids out-of-memory crashes.

```sh
ulimit -v 8388608
```

## 4. Prove The Clean Adder

The main file for the demo is `examples/FP32_IEEE_adder.py`.

The concept specification is `spec_FP32_IEEE_adder`; the implementation is `FP32_IEEE_adder`. The implementation has inline comments pointing to the component definitions, including `fused_dot_product/components/Float.py`, `examples/common.py`, `fused_dot_product/components/UQ.py`, and `fused_dot_product/components/Q.py`.

Run:

```sh
.venv/bin/python3.11 -m examples.FP32_IEEE_adder
```

Expected final result:

```text
FP32_IEEE_adder has been proved
```

## 5. Mistake 1: Drop The Invalid NaN Case

In `spec_FP32_IEEE_adder`, change:

```python
nan = x.is_nan | y.is_nan | invalid
```

to:

```python
nan = x.is_nan | y.is_nan  # | invalid
```

Run again:

```sh
.venv/bin/python3.11 -m examples.FP32_IEEE_adder
```

Expected counterexample:

```text
FP32_IEEE_adder[arg0=inf,arg1=inf,inner_spec=nan,outer_spec=nan] 	| wrong 	| sat
```

Expected final result:

```text
FP32_IEEE_adder has not been proved
```

This demonstrates that `+inf + -inf` and `-inf + +inf` must be classified as invalid and produce NaN.

Before the next mistake, restore the clean line:

```python
nan = x.is_nan | y.is_nan | invalid
```

## 6. Mistake 2: Flip The Real Operation

In `spec_FP32_IEEE_adder`, change:

```python
result_real = x.value + y.value
```

to:

```python
result_real = x.value - y.value
```

Run again:

```sh
.venv/bin/python3.11 -m examples.FP32_IEEE_adder
```

Expected final result:

```text
FP32_IEEE_adder has not been proved
```

Before ending the demo, restore the clean line:

```python
result_real = x.value + y.value
```

## 7. Generated C++ Outputs

Each run also writes the generated C++ headers:

```text
examples/adder_jit.hpp
examples/adder_no_jit.hpp
```

`adder_jit.hpp` is the JIT-oriented version, and `adder_no_jit.hpp` is the non-JIT version.
