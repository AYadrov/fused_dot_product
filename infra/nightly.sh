#!/bin/bash

# exit immediately upon first error, log every command executed
set -e -x

PYTHON="${PYTHON:-python3}"
N_POINTS="10000"

# Seed is fixed for the whole day; this way two branches run the same seed
SEED=$(date "+%Y%j")
REPORTDIR="$1"; shift

mkdir -p "$REPORTDIR"
rm -rf "${REPORTDIR:?}/"* || echo "nothing to delete"

cd .. && $PYTHON -m fused_dot_product.infra.unittests --seed "$SEED" --num-points "$N_POINTS"

