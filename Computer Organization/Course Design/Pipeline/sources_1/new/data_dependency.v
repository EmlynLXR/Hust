`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/27 00:19:57
// Design Name: 
// Module Name: data_dependency
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


module data_dependency(
    input[5:0] op,func,
    input [4:0] EX_RW, ID_RA, ID_RB,
    input EX_RegWrite,EX_MemToReg,
    output dependency
    );
    wire R1_Used, R2_Used;
    assign R1_Used = (((op==6'd0)&&(func==6'd32||func==6'd33||func==6'd34||func==6'd36||func==6'd37||func==6'd39
                    ||func==6'd42||func==6'd43||func==6'd8||func==6'd12||func==6'd6||func==6'd7))
                    ||(op==6'd4||op==6'd5||op==6'd8||op==6'd12||op==6'd9||op==6'd10||op==6'd13||op==6'd35||op==6'd43||op==6'd36||op==6'd1))?1'b1:1'b0;
    assign R2_Used = (((op==6'd0)&&(func==6'd0||func==6'd3||func==6'd2||func==6'd32||func==6'd33||func==6'd34||func==6'd36||func==6'd37||func==6'd39||func==6'd42||func==6'd43||func==6'd12||func==6'd6||func==6'd7))  
                    ||(op==6'd4||op==6'd5||op==6'd43))?1'b1:1'b0;      
    
    wire R1_EX,R2_EX;
    assign R1_EX = (ID_RA==EX_RW) && (ID_RA!=6'd0) && R1_Used && EX_RegWrite;
    assign R2_EX = (ID_RB==EX_RW) && (ID_RB!=6'd0) && R2_Used && EX_RegWrite;
                         
    assign dependency = (R1_EX || R2_EX) && EX_MemToReg;
endmodule
