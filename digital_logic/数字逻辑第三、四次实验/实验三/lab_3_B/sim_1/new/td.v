`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/07 01:56:24
// Design Name: 
// Module Name: td
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


module td();
  reg sig_nsyn,clk;
  wire clk_n,q1,q2,sig_syn;
  
   parameter n=1000_000_000;
  pipe3b mypipe3b(sig_nsyn,clk,clk_n,q1,q2,sig_syn);
  initial begin
    clk <= 0;
    sig_nsyn <= 1;
  end
    always #5 clk = ~clk;
    always #n sig_nsyn = ~sig_nsyn;
endmodule
