module fp32_adder_cpp_vs_cpp_tb;
  import fp32_adder_dut_pkg::*;
  import fp32_adder_ref_pkg::*;

  logic [31:0] lhs_bits;
  logic [31:0] rhs_bits;
  logic [31:0] dut_sum_bits;
  logic [31:0] ref_sum_bits;

  task automatic check_case(input logic [31:0] lhs, input logic [31:0] rhs);
    begin
      lhs_bits = lhs;
      rhs_bits = rhs;
      #1;
      dut_sum_bits = fp32_adder_dut_dpi(lhs_bits, rhs_bits);
      ref_sum_bits = fp32_adder_ref_dpi(lhs_bits, rhs_bits);
      if (dut_sum_bits !== ref_sum_bits) begin
        $error("FP32 C++ mismatch lhs=%h rhs=%h dut=%h ref=%h", lhs_bits, rhs_bits, dut_sum_bits, ref_sum_bits);
        $fatal(1);
      end
    end
  endtask

  initial begin
    check_case(32'h00000000, 32'hbf800000);
    check_case(32'h80000000, 32'h80000000);
    check_case(32'h7f800000, 32'hff800000);
    check_case(32'h7f800001, 32'h3f800000);
    check_case(32'h007fffff, 32'hbf800000);

    repeat(32'hFFFF_FFFF) begin
        repeat(2048) begin
            check_case($urandom(), $urandom());
        end
    end

    $display("FP32 C++ DUT vs C++ REF passed.");
    $finish;
  end
endmodule

