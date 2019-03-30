`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 07:49:19 PM
// Design Name: 
// Module Name: ID_EX
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


module ID_EX(
    input clk,
    input rst,
    input en,
    input [31:0]IRin,
    input [31:0]PCin,
    input JRin,
    input JMPin,
    input LBUin,
    input BEQin,
    input BNEin,
    input BGEZin,
    input MemToRegin,
    input MemWritein,
    input [3:0]AluOpin,
    input AluSrcBin,
    input RegWritein,
    input JALin,
    input SYSCALLin,
    input [4:0]R1_numin,
    input [4:0]R2_numin,
    input [31:0]R1in,
    input [31:0]R2in,
    input [4:0]W_numin,
    input [4:0]shamtin,
    input [31:0]imm16in,
    input [25:0]imm26in,
    
    
    output reg [31:0]IRout,
    output reg [31:0]PCout,
    output reg JRout,
    output reg JMPout,
    output reg LBUout,
    output reg BEQout,
    output reg BNEout,
    output reg BGEZout,
    output reg MemToRegout,
    output reg MemWriteout,
    output reg[3:0] AluOpout,
    output reg AluSrcBout,
    output reg RegWriteout,
    output reg JALout,
    output reg SYSCALLout,
    output reg [4:0]R1_numout,
    output reg [4:0]R2_numout,
    output reg [31:0]R1out,
    output reg [31:0]R2out,
    output reg [4:0]W_numout,
    output reg [4:0]shamtout,
    output reg [31:0]imm16out,
    output reg [25:0]imm26out 
    );
    initial begin
        IRout <= 0;
        PCout <= 0;
        JRout <= 0;
        JMPout <= 0;
        LBUout <= 0;
        BEQout <= 0;
        BNEout <= 0;
        BGEZout<=0;
        MemToRegout<=0;
        MemWriteout<=0;
        AluOpout<=0;
        AluSrcBout<=0;
        RegWriteout<=0;
        JALout<=0;
        SYSCALLout<=0;
        R1_numout<=0;
        R2_numout<=0;
        R1out<=0;
        R2out<=0;
        W_numout<=0;
        shamtout<=0;
        imm16out<=0;
        imm26out<=0; 
    end
    
    always@(posedge clk)begin
        if(en==1);
        else if(rst==1)begin
            IRout<=0;
            PCout<=0;
            JRout<=0;
            JMPout<=0;
            LBUout<=0;
            BEQout<=0;
            BNEout<=0;
            BGEZout<=0;
            MemToRegout<=0;
            MemWriteout<=0;
            AluOpout<=0;
            AluSrcBout<=0;
            RegWriteout<=0;
            JALout<=0;
            SYSCALLout<=0;
            R1_numout<=0;
            R2_numout<=0;
            R1out<=0;
            R2out<=0;
            W_numout<=0;
            shamtout<=0;
            imm16out<=0;
            imm26out<=0;         
        end
        else begin
            PCout<=PCin;
            IRout<=IRin;
            JRout<=JRin;
            JMPout<=JMPin;
            LBUout<=LBUin;
            BEQout<=BEQin;
            BNEout<=BNEin;
            BGEZout<=BGEZin;
            MemToRegout<=MemToRegin;
            MemWriteout<=MemWritein;
            AluOpout<=AluOpin;
            AluSrcBout<=AluSrcBin;
            RegWriteout<=RegWritein;
            JALout<=JALin;
            SYSCALLout<=SYSCALLin;
            R1_numout<=R1_numin;
            R2_numout<=R2_numin;
            R1out<=R1in;
            R2out<=R2in;
            W_numout<=W_numin;
            shamtout<=shamtin;
            imm16out<=imm16in;
            imm26out<=imm26in;  
        end
    end
endmodule
