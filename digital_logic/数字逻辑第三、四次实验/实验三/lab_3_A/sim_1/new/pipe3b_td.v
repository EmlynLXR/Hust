`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 01:39:34
// Design Name: 
// Module Name: pipe3b_td
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

module pipe3b_td();
  reg sig_nsyn,clk;
  wire q1,q2,sig_syn;
  
  parameter DELY=50;
  pipe3b mypipe3b(sig_nsyn,clk,q1,q2,sig_syn);
  initial begin
    clk <= 0;
    sig_nsyn <= 0;
  end
    always #(DELY/5) clk = ~clk;
    always #(DELY) sig_nsyn = ~sig_nsyn;
endmodule
