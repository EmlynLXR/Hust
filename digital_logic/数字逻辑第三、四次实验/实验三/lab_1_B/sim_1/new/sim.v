`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/04 21:28:30
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
  reg clk,X;
  wire Y,Q0,Q1,T0,T1;
  
  parameter DELY=50;
  main mymain(X,clk,Y,T0,Q0,T1,Q1);
  initial begin
    clk <= 0;
    X <= 0;
  end
    always #(DELY/5) clk = ~clk;
    always #(DELY) X = ~X;
endmodule
