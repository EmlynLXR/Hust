`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 01:55:34
// Design Name: 
// Module Name: pipe3b
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


module pipe3b(
    input sig_nsyn,
    input clk,
    output wire clk_n,
    output reg q1,
    output reg q2,
    output reg sig_syn
      );
    divider mydivider(clk,clk_n);
initial begin
    q1<=0;
    q2<=0;
    sig_syn<=0;
end 
    always@(posedge clk_n) begin
        q2<=q1;
        sig_syn<=q2;
        q1<=sig_nsyn;
    end    
endmodule

module divider(clk,clk_n);
    input clk;
    output reg clk_n;

    parameter n=10_000_000;
    reg [31:0] counter;
initial begin 
    clk_n<=0;
    counter<=0;
end
    always @(posedge clk)begin
      counter<=counter+1;
      if(counter==n/2-1)begin 
        clk_n<=~clk_n;
        counter<=0;
      end
    end
endmodule
