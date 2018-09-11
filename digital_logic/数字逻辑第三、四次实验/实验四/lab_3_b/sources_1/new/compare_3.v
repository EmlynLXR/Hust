`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/12 18:56:14
// Design Name: 
// Module Name: compare_3
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


module compare_3(
    input [2:0]A,
    input [2:0]B,
    output F1,
    output F2,
    output F3
    );
    wire F10,F11,F12,F20,F21,F22,F30,F31,F32;
    compare my_compare0(A[0],B[0],F10,F20,F30);
    compare my_compare1(A[1],B[1],F11,F21,F31);
    compare my_compare2(A[2],B[2],F12,F22,F32);
    assign F1=F12|(F22&F11)|(F22&F21&F10);
    assign F2=F22&F21&F20;
    assign F3=(~F1)&(~F2);
endmodule

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