`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/12 21:48:26
// Design Name: 
// Module Name: com_tb
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
   reg [2:0]A,B;
   wire F1,F2,F3;
   parameter DELY=10;
   compare_3 com(A,B,F1,F2,F3);
   initial begin
   A=3'b000;
   B=3'b111;
   end
   always begin #(DELY/10) A=A+1;
          #(DELY/10) B=B-1;
          end
endmodule
