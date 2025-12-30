# Fused Dot Product
Python model of the fused dot product described by Kaul et al. (2019). The project builds a strongly typed AST for fixed-point and floating-point operations, and uses it to compare a conventional BF16 dot product against an optimized, fused implementation.

## What's here
- `ast/AST.py` – Node definitions with static/dynamic type checking, constant folding, and tree printing.
- `numtypes/` – Runtime and static types for `Q`/`UQ` fixed point, BF16, and Float32, plus random value generators.
- `designs/conventional.py` and `designs/optimized.py` – Two BF16x4→FP32 dot-product designs that can be evaluated and inspected as ASTs.
- `utils/composites.py` – Common composites and primitives (e.g., mantissa helpers, max-exp tree).
- `infra/unittests.py` – Equivalence tests that sweep shared-exponent widths across both designs.
- `config.py` – Global knobs such as vector length `N`, mantissa accuracy `Wf`, local shift bits `s`, and default shared exponent bits.
- `main.py` – Small CLI that seeds random inputs, runs both designs, and asserts they match.

## Quick start
1) Ensure Python 3.10+ is available (CI uses 3.13).  
2) Install deps:
```
make install
```
3) Run the sample check (compares optimized vs conventional on random BF16 vectors):
```
python main.py --seed 0 --shared-exponent 5
```
Adjust `--shared-exponent` (must be `< BFloat16.exponent_bits`) and `config.py` parameters to explore different vector sizes or accuracy targets.

## Testing
Run the unit suite that exercises both designs over many random vectors and shared-exponent widths:
```
make unit-tests
```

## Inspecting the AST
Both designs can print their internal trees; for example, to see the optimized design structure:
```
python - <<'PY'
from fused_dot_product.designs.optimized import Optimized
from fused_dot_product.numtypes.BFloat16 import BFloat16T
from fused_dot_product.ast.AST import Var
a = [Var(f"a_{i}", BFloat16T()) for i in range(4)]
b = [Var(f"b_{i}", BFloat16T()) for i in range(4)]
Optimized(*a, *b).print_tree(depth=2)
PY
```
Use higher `depth` values to expand more of the implementation.

## Notes
- The shared exponent mask used by `BFloat16.random_generator` lets you mimic the block floating-point settings explored in the paper; tests sweep the full range of supported shared bits.
- The AST enforces both static signatures and runtime checks, making it easier to prototype new primitives or dot-product variants without losing type safety.
