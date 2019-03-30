`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 19:28:00
// Design Name: 
// Module Name: B2D
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


module B2D(
  input [11:0] binary,
  output reg [3:0] Thousand,
  output reg [3:0] Hundreds,
  output reg [3:0] Tens,
  output reg [3:0] Ones
);

  integer i;
  always@(binary) begin
    Thousand = 4'd0;
    Hundreds = 4'd0;
    Tens = 4'd0;
    Ones = 4'd0;

    for(i=11; i>=0; i=i-1) begin
      if(Thousand >= 5)
        Thousand = Thousand + 3;
      if(Hundreds >= 5)
        Hundreds = Hundreds + 3;
      if(Tens >= 5)
        Tens = Tens + 3;
      if(Ones >= 5)
        Ones = Ones + 3;

      Thousand = Thousand << 1;
      Thousand[0] = Hundreds[3];
      Hundreds = Hundreds << 1;
      Hundreds[0] = Tens[3];
      Tens = Tens << 1;
      Tens[0] = Ones[3];
      Ones = Ones << 1;
      Ones[0] = binary[i];
    end
  end
endmodule
