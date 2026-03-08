`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2026 10:04:44 PM
// Design Name: 
// Module Name: test_bench
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module testbench;
    reg [3:0] data;
    wire [6:0] ham_code;

    even_parity dut(.data(data), .ham_code(ham_code));

    initial begin
        data = 4'b0000;
        #10 data = 4'b1111;
        #10 data = 4'b1010;
        #10 data = 4'b1011;
        #10 $finish;
    end

    initial begin
        $dumpfile("waveform.vcd");
        $dumpvars(0, testbench);
    end
endmodule