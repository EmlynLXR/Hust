`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/10 15:03:13
// Design Name: 
// Module Name: dynamic_scan
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


module dynamic_scan(
    input             clk100MHZ,
    input power_led,
    input   [7:0]     dig0,
    input   [7:0]     dig1,
    input   [7:0]     dig2,
    input   [7:0]     dig3,
    input   [7:0]     dig4,
    input   [7:0]     dig5,
    input   [7:0]     dig6,
    input   [7:0]     dig7,
    output  [7:0]     SEG,
    output  [7:0]     AN
);
    
    wire        clk_N;
    wire [2:0]  num;
    wire [3:0]  data;
        
    divider #(3000) my_divider(clk100MHZ,clk_N);
    
    counter my_counter(clk_N,num);
    
    decoder3_8 my_d38(power_led,num,AN);
    
    seven_seg_dec my_sd(num,dig0[3:0],dig1[3:0],dig2[3:0],dig3[3:0],dig4[3:0],dig5[3:0],dig6[3:0],dig7[3:0],data);
    
    seven_seg_display my_ds(.data(data), .segments(SEG));

endmodule
