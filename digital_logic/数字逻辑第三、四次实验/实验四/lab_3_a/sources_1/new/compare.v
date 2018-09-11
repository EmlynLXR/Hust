`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/12 18:52:06
// Design Name: 
// Module Name: compare
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


module compare(
    input A,
    input B,
    output F1,
    output F2,
    output F3
    );
    assign F1=A&(~B);
    assign F2=(A&B)|((~A)&(~B));
    assign F3=(~A)&B;
endmodule