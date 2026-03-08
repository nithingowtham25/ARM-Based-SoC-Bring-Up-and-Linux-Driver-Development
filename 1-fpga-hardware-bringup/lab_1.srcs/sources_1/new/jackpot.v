`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/05/2026 10:55:45 AM
// Design Name: 
// Module Name: jackpot
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


module jackpot(
    input [3:0] DIP,
    input reset,
    input clock,
    output [3:0] LEDS
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

    reg jackpot = 1'b0;                     // game status
    reg [3:0] prev_switch_val = 4'b0000;    // previous cycle switch status
    reg [3:0] led_status = 4'b0001;         // led status
    
    always @(posedge one_sec_pulse) begin
        // When the reset button is pressed, initialize the switch and led status
        if(reset) begin
            jackpot <= 1'b0;
            prev_switch_val <= 4'b0000;
            led_status <= 4'b0001;
        end
        else if (one_sec_pulse) begin
            // If the previous switch = OFF and current switch = ON and corresponding LED is glowing => JACKPOT
            if( jackpot != 1'b1) begin
                if (  ( !prev_switch_val[0] && DIP[0] && led_status[0] ) ||
                      ( !prev_switch_val[1] && DIP[1] && led_status[1] ) ||
                      ( !prev_switch_val[2] && DIP[2] && led_status[2] ) ||
                      ( !prev_switch_val[3] && DIP[3] && led_status[3] )
                    )  begin
                    jackpot <= 1'b1;
                    led_status <= 4'b1111;
                end
                else begin
                    if( led_status == 4'b1000) begin        //for circular shift
                            led_status <= 4'b0001;
                    end
                    else begin
                        led_status <= (led_status << 1'b1); // sequential blinking of LEDs
                    end
                end
            end
        end
        
        prev_switch_val[3:0] <= DIP[3:0];    // assign previous_switch_values as current switch value
    end 
    
    assign LEDS[3:0] = led_status[3:0];     // final LED status
    
endmodule


