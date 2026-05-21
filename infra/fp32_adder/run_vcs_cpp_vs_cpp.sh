#!/usr/bin/env bash
set -euo pipefail

syn-vcs -full64 -sverilog   fp32_adder_dut_pkg.sv   fp32_adder_ref_pkg.sv   fp32_adder_cpp_vs_cpp_tb.sv   fp32_adder_dut_dpi.cpp   fp32_adder_ref_dpi.cpp   -top fp32_adder_cpp_vs_cpp_tb   -o simv_cpp_vs_cpp

./simv_cpp_vs_cpp
