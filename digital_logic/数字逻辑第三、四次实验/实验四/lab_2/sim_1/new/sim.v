`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/12 17:57:02
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
    reg in;
    wire out;
    wire [4:0]state;

    always #5 clk=~clk;
initial begin
  in<=0;
  clk<=0;
  #3 in<=0;#10 in<=1;
  #10 in<=1;#10 in<=0;
  #10 in<=1;#10 in<=1;
  #10 in<=0;#10 in<=1;
  #10 in<=1;#10 in<=0;
  #10 in<=0;#10 in<=1;
  #10 in<=0;#10 in<=1;
  #10 in<=0;#10 in<=1;
  #10 in<=1;#10 in<=0;
  #10 in<=1;#10 in<=1;
  #10 in<=0;#10 in<=1;
  #10 in<=1;#10 in<=0;
  #10 in<=1;#10 in<=1;
  #10 in<=0;#10 in<=1;

  #10 in<=1;#10 in<=0;
end

    mealy my_mealy(clk,in,state,out);
endmodule
