`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/26 23:44:09
// Design Name: 
// Module Name: redirect
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


module redirect(
    input[31:0] IR, Din, MEM_addr, Ori_EX_R1, Ori_EX_R2,
    input [4:0] WB_RW, MEM_RW, EX_RA, EX_RB,
    input WB_RegWrite, MEM_RegWrite,
    output[31:0] EX_R1,EX_R2
    );
    wire [5:0]op = IR[31:26];
    wire [5:0]func = IR[5:0];
    wire R1_Used, R2_Used;
    assign R1_Used = (((op==6'd0)&&(func==6'd32||func==6'd33||func==6'd34||func==6'd36||func==6'd37||func==6'd39
                    ||func==6'd42||func==6'd43||func==6'd8||func==6'd12||func==6'd6||func==6'd7))
                    ||(op==6'd4||op==6'd5||op==6'd8||op==6'd12||op==6'd9||op==6'd10||op==6'd13||op==6'd35||op==6'd43||op==6'd36||op==6'd1))?1'b1:1'b0;
    assign R2_Used = (((op==6'd0)&&(func==6'd0||func==6'd3||func==6'd2||func==6'd32||func==6'd33||func==6'd34||func==6'd36||func==6'd37||func==6'd39||func==6'd42||func==6'd43||func==6'd12||func==6'd6||func==6'd7))  
                    ||(op==6'd4||op==6'd5||op==6'd43))?1'b1:1'b0;      
    
    wire R1_WB,R1_MEM,R2_WB,R2_MEM;
    assign R1_WB = (EX_RA==WB_RW) && (EX_RA!=6'd0) && R1_Used && WB_RegWrite;
    assign R1_MEM = (EX_RA==MEM_RW) && (EX_RA!=6'd0) && R1_Used && MEM_RegWrite;
    assign R2_WB = (EX_RB==WB_RW) && (EX_RB!=6'd0) && R2_Used && WB_RegWrite;
    assign R2_MEM = (EX_RB==MEM_RW) && (EX_RB!=6'd0) && R2_Used && MEM_RegWrite;
    
    assign EX_R1 = R1_MEM ? MEM_addr : (R1_WB ? Din : Ori_EX_R1);
    assign EX_R2 = R2_MEM ? MEM_addr : (R2_WB ? Din : Ori_EX_R2);  
endmodule
