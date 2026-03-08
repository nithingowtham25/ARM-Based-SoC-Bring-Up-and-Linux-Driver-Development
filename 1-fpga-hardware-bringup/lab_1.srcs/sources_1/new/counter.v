`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/29/2026 11:05:30 AM
// Design Name: 
// Module Name: counter
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


module counter(
    input [1:0] BUTTONS,
    output reg [3:0] LEDS,
    input clock,
    input reset
    );
    
    reg one_sec_pulse;
    reg [27:0] clk_pulse;
    
    // Use clock divider to control the LEDs blinking
    always @(posedge clock) begin
        if (clk_pulse > 125000000) begin    // Default 125MHz = 8ns; => 1s/8ns = 125000000 cycles
            one_sec_pulse <= 1'b1;
            clk_pulse <= 0;
        end     
        else begin
            clk_pulse <= clk_pulse + 1;
            one_sec_pulse <= 1'b0;
        end
    end
    
    
    always @(posedge clock) begin
        if (reset)                  // When reset button is pressed, all LEDs should be turned OFF
            LEDS <= 4'b0000;
        else if (one_sec_pulse) begin
            if ( BUTTONS[0] && !BUTTONS[1])
                LEDS <= LEDS + 1;   // increment the counter
            else if ( !BUTTONS[0] && BUTTONS[1])
                LEDS <= LEDS - 1;   // decrement the counter
            else
                LEDS <= LEDS;       // stay in the same state
        end                
    end
endmodule
