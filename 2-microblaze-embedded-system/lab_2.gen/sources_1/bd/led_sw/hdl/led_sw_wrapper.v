//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (lin64) Build 3865809 Sun May  7 15:04:56 MDT 2023
//Date        : Tue Feb 17 19:28:25 2026
//Host        : zach-354a-02.engr.tamu.edu running 64-bit Ubuntu 22.04.5 LTS
//Command     : generate_target led_sw_wrapper.bd
//Design      : led_sw_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module led_sw_wrapper
   (clk_100MHz,
    led_tri_o);
  input clk_100MHz;
  output [3:0]led_tri_o;

  wire clk_100MHz;
  wire [3:0]led_tri_o;

  led_sw led_sw_i
       (.clk_100MHz(clk_100MHz),
        .led_tri_o(led_tri_o));
endmodule
