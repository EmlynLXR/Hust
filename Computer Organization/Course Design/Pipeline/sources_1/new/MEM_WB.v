`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/26 20:51:28
// Design Name: 
// Module Name: MEM_WB
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


module MEM_WB(
    input clk,
    input rst,
    input en,
    input [31:0]IRin,
    input [31:0]PCin,
    
    input LBUin,
    input MemToRegin,
    input RegWritein,
    input JALin,
    input SYSCALLin,
    input [31:0]Result1in,
    input [31:0]Doutin,
    input [31:0]R1in,
    input [31:0]R2in,
    input [4:0]W_numin,
    
    
    output reg [31:0]IRout,
    output reg [31:0]PCout,
    output reg LBUout,
    output reg MemToRegout,
    output reg RegWriteout,
    output reg JALout,
    output reg SYSCALLout,
    output reg [31:0]Result1out,
    output reg [31:0]Doutout,
    output reg [31:0]R1out,
    output reg [31:0]R2out,
    output reg [4:0]W_numout
    );
    initial begin
        IRout<=0;
        PCout<=0;
        LBUout<=0;
        MemToRegout<=0;
        RegWriteout<=0;
        JALout<=0;
        SYSCALLout<=0;
        Result1out<=0;
        Doutout<=0;
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
            RegWriteout<=0;
            JALout<=0;
            SYSCALLout<=0;
            Result1out<=0;
            Doutout<=0;
            R1out<=0;
            R2out<=0;
            W_numout<=0;       
        end
        else begin
            PCout<=PCin;
            IRout<=IRin;
            LBUout<=LBUin;
            MemToRegout<=MemToRegin;
            RegWriteout<=RegWritein;
            JALout<=JALin;
            SYSCALLout<=SYSCALLin;
            Result1out<=Result1in;
            Doutout<=Doutin;
            R1out<=R1in;
            R2out<=R2in;
            W_numout<=W_numin;
        end
    end
endmodule
