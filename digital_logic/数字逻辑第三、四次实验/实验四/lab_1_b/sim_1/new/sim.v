`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/11 21:46:09
// Design Name: 
// Module Name: sim
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


module sim();
    reg clk;
    reg M;
    reg CLR;
    wire QD,QC,QB,QA;
    wire Qcc;
initial begin
  M<=1;
  CLR<=1;
  clk<=0;
end
    always #20 clk=~clk;
    always #600 M=~M;
    counter_8 my_counter_8(clk,M,CLR,QD,QC,QB,QA,Qcc);
endmodule
