`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 16:22:37
// Design Name: 
// Module Name: top_module
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


module top_module(
    input clk_brd,
    input reset,
    input go,
    input [15:0]sw,
    output [7:0]seg,
    output [7:0]AN,
    output [6:0]LED
    );
    
    wire clk_dvid;
    wire clk_seg;
    
    /* 100MHz */
    clk_divider dvid(.clk(clk_brd), .change_scale(sw[3]), .delay_1(100_000_000), .clk_divd(clk_dvid), .speed(LED[2:0]));  // best: 3_000_000
    clk_divider seg_dvid(.clk(clk_brd), .change_scale(0), .delay_1(50_000), .clk_divd(clk_seg),.speed()); 
    single_cycle_MIPS CPU(
        .data_addr(sw[15:12]),
        .clk_dvid(clk_dvid),
        .seg_dvid(clk_seg),
        .go(go),
        .reset(reset),
        .display_switch(sw[2:0]),
        .seg_an(AN),
        .seg(seg)
        );
endmodule
