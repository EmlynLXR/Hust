`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/26 20:46:30
// Design Name: 
// Module Name: EX_MEM
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


module EX_MEM(
    input clk,
    input rst,
    input en,
    input [31:0]IRin,
    input [31:0]PCin,
    
    input LBUin,
    input MemToRegin,
    input MemWritein,
    input RegWritein,
    input JALin,
    input SYSCALLin,
    input [31:0]Result1in,
    input [31:0]R1in,
    input [31:0]R2in,
    input [4:0]W_numin,
    
    
    output reg [31:0]IRout,
    output reg [31:0]PCout,
    output reg LBUout,
    output reg MemToRegout,
    output reg MemWriteout,
    output reg RegWriteout,
    output reg JALout,
    output reg SYSCALLout,
    output reg [31:0]Result1out,
    output reg [31:0]R1out,
    output reg [31:0]R2out,
    output reg [4:0]W_numout
    );
    initial begin
        IRout<=0;
        PCout<=0;
        LBUout<=0;
        MemToRegout<=0;
        MemWriteout<=0;
        RegWriteout<=0;
        JALout<=0;
        SYSCALLout<=0;
        Result1out<=0;
        R1out<=0;
        R2out<=0;
        W_numout<=0;
    end
    
    always@(posedge clk)begin
        if(en==1);
        else if(rst==1)begin
            IRout<=0;
            PCout<=0;
            LBUout<=0;
            MemToRegout<=0;
            MemWriteout<=0;
            RegWriteout<=0;
            JALout<=0;
            SYSCALLout<=0;
            Result1out<=0;
            R1out<=0;
            R2out<=0;
            W_numout<=0;       
        end
        else begin
            PCout<=PCin;
            IRout<=IRin;
            LBUout<=LBUin;
            MemToRegout<=MemToRegin;
            MemWriteout<=MemWritein;
            RegWriteout<=RegWritein;
            JALout<=JALin;
            SYSCALLout<=SYSCALLin;
            Result1out<=Result1in;
            R1out<=R1in;
            R2out<=R2in;
            W_numout<=W_numin;
        end
    end
endmodule
