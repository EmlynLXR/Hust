`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/09 17:07:58
// Design Name: 
// Module Name: counter
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
        else if(LD==0)begin
          {QD,QC,QB,QA}<={D,C,B,A};
        end
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

// module divider(clk,clk_n);
//     input clk;
//     output reg clk_n;

//     parameter n=10_000_000;
//     reg [31:0] counter;
// initial begin 
//     clk_n<=0;
//     counter<=0;
// end
//     always @(posedge clk)begin
//       counter<=counter+1;
//       if(counter==n/2-1)begin 
//         clk_n<=~clk_n;
//         counter<=0;
//       end
//     end
// endmodule
