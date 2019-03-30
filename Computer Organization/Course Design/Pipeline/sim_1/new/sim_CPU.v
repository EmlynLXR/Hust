`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/19 10:36:42
// Design Name: 
// Module Name: sim_CPU
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


module sim_CPU(
    
    );
    
    
    reg clk, reset;
    reg[2:0] display_switch;
    reg [31:0]count;
    wire [7:0]seg_an, seg;
    
    single_cycle_MIPS CPU(
        .clk_dvid(clk),
        .seg_dvid(clk),
        .reset(reset),
        .display_switch(display_switch),
        .seg_an(seg_an),
        .seg(seg)
        );
    
    
    initial begin
        clk = 0;
        reset = 0;
        display_switch = 0;
        count = 0;
    end
    
    
    always@(*) begin
        #1 clk = ~clk;
        count <= count + 1; 
    end
    
endmodule
