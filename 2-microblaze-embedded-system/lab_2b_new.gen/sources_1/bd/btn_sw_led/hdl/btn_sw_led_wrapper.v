//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (lin64) Build 3865809 Sun May  7 15:04:56 MDT 2023
//Date        : Thu Feb 19 00:50:40 2026
//Host        : n01-zeus.olympus.ece.tamu.edu running 64-bit Red Hat Enterprise Linux release 8.10 (Ootpa)
//Command     : generate_target btn_sw_led_wrapper.bd
//Design      : btn_sw_led_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module btn_sw_led_wrapper
   (btn_sw_ip_tri_i,
    clk_100MHz,
    leds_tri_o);
  input [7:0]btn_sw_ip_tri_i;
  input clk_100MHz;
  output [3:0]leds_tri_o;

  wire [7:0]btn_sw_ip_tri_i;
  wire clk_100MHz;
  wire [3:0]leds_tri_o;

  btn_sw_led btn_sw_led_i
       (.btn_sw_ip_tri_i(btn_sw_ip_tri_i),
        .clk_100MHz(clk_100MHz),
        .leds_tri_o(leds_tri_o));
endmodule
