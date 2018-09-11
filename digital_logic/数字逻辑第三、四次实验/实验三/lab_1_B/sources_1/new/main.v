`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/04 20:32:22
// Design Name: 
// Module Name: main
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

module main(
    input X,
    input clk,
    output reg Y,
    output reg T0,
    output Q0,
    output reg T1,
    output Q1
    );

    wire NQ0,NQ1;
    T TT0(clk,1,Q0,NQ0);
    T TT1(clk,Q0^X,Q1,NQ1);
    always @(*)begin
        T0<=1;
        T1<=Q0^X;
        Y<=~( X & NQ1 );
    end
endmodule

module T(clk,t,q,nq);
    input clk;
    input t;
    output reg q;
    output nq;

initial begin
    q <= 0;
end
    assign nq=~q;
always @(negedge clk)begin
    if(t == 0)
        q <= q;
    else 
        q <= ~q;
end
endmodule