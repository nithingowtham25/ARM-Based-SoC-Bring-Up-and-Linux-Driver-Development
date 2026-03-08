`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/11/2026 10:01:00 PM
// Design Name: 
// Module Name: even_parity
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

module even_parity (input [3:0] data, output [6:0] ham_code);

    wire p1,p2,p4;

    // Compute the parity
    assign p1 = data[0] ^ data[1] ^ data[3];
    assign p2 = data[0] ^ data[2] ^ data[3];
    assign p4 = data[1] ^ data[2] ^ data[3];

    // Final encoded data
    assign ham_code = { data[3:1], p4, data[0], p2, p1};

endmodule

