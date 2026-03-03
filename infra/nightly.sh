#!/bin/bash

# bash infra/nightly.sh [-output-dir DIR] [-seed N] [-num-points N]

# exit immediately upon first error, log every command executed
set -e -x

PYTHON="${PYTHON:-python3}"
N_POINTS="${N_POINTS:-1000}"
REPORTS_DIR="${REPORTS_DIR:-reports}"
SEED="${SEED:-0}"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -output-dir)
            REPORTS_DIR="$2"
            shift 2
            ;;
        -seed)
            SEED="$2"
            shift 2
            ;;
        -num-points)
            N_POINTS="$2"
            shift 2
            ;;
        -*)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 1
            ;;
        *) echo "Unknown argument: $1" >&2; usage >&2; exit 1 ;;
    esac
done

REPORT_PATH="${REPORTS_DIR}/report.json"

mkdir -p "$REPORTS_DIR"
rm -f "$REPORT_PATH"

"$PYTHON" -m infra.unittests --seed "$SEED" --num-points "$N_POINTS" --json-report "$REPORT_PATH"
echo "Nightly report written to: $REPORT_PATH"
