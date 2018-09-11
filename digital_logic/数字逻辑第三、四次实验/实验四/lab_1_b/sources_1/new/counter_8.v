`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/11 21:19:45
// Design Name: 
// Module Name: counter_8
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

module counter_8(
    input clk,
    input M,
    input CLR,
    output wire QD,QC,QB,QA,
    output wire Qcc
    );
    wire LD;
    wire [3:0]in;
    reg Q;
    counter my_counter(in[3],in[2],in[1],in[0],clk,M,LD,CLR,QD,QC,QB,QA,);
    assign LD=({QD,QC,QB,QA}==10&&M==1)|({QD,QC,QB,QA}==1&&M==0)|({QD,QC,QB,QA}==0)?0:1;
    assign in=(M==1)?4'b0010:4'b1001;
    assign Qcc=Q;


    always @(posedge clk)begin
        Q<=1;
        if({QD,QC,QB,QA}==9&&M==1)
            Q<=0;
        else if({QD,QC,QB,QA}==2&&M==0)
            Q<=0;
    end
endmodule

module counter(
    input D,C,B,A,
    input clk,
    input M,
    input LD,
    input CLR,
    output reg QD,QC,QB,QA,
    output reg Qcc
    );
initial begin
    {QD,QC,QB,QA}<=4'b0000;
    Qcc<=1'b1;
end
    always @(posedge clk or negedge LD or negedge CLR)begin
        Qcc<=1;
        if(CLR==0)
            {QD,QC,QB,QA}<=4'b0000;
        else if(LD==0)
          {QD,QC,QB,QA}<={D,C,B,A};
        else if(M==1&&{QD,QC,QB,QA}==4'b1111)begin
            {QD,QC,QB,QA}<=4'b0000;
            Qcc<=0;
            end
        else if(M==0&&{QD,QC,QB,QA}==4'b0000)begin
            {QD,QC,QB,QA}<=4'b1111;
            Qcc<=0;
            end
        else if(M==1)
            {QD,QC,QB,QA}<={QD,QC,QB,QA}+1;
        else if(M==0)
            {QD,QC,QB,QA}<={QD,QC,QB,QA}-1;
    end
endmodule