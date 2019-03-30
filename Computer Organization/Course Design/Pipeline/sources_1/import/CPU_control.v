`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 15:39:28
// Design Name: PWN
// Module Name: CPU_control
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


module CPU_control(
    input [5:0] Func,
    input [5:0] OP,
    output  [3:0] ALU_OP,
    output  MemToReg,
    output  MemWrite,
    output  ALU_SRC,
    output  RegWrite,
    output  SysCALL,
    output  SignedExt,
    output  RegDst,
    output  Beq,
    output  Bne,
    output  JR,
    output  JMP,
    output  JAL,
    output BGEZ,
    output SV,
    output LBU
    );

    ALU_control calc_signal(Func,OP,ALU_OP);
    GEN_control cpu_signal(Func,OP,MemToReg,MemWrite,ALU_SRC,
                           RegWrite,SysCALL,SignedExt,RegDst,
                           Beq, Bne,JR,JMP,JAL,BGEZ,SV,LBU);

endmodule

module GEN_control(
    input [5:0] Func,
    input [5:0] OP,
    output  MemToReg,
    output  MemWrite,
    output  ALU_SRC,
    output  RegWrite,
    output  SysCALL,
    output  SignedExt,
    output  RegDst,
    output  Beq,
    output  Bne,
    output  JR,
    output  JMP,
    output  JAL,
    output BGEZ,
    output SV,
    output LBU
);
    assign  MemToReg= (OP==6'd35||OP==36)?1:0;
    assign  MemWrite=(OP==6'd43)?1:0;
    assign  ALU_SRC = (OP==6'd8)?1'b1:
                        (OP==6'd12)?1'b1:
                        (OP==6'd9)?1'b1:
                        (OP==6'd10)?1'b1:
                        (OP==6'd13)?1'b1:
                        (OP==6'd35||OP==36)?1'b1:
                        (OP==6'd43)?1'b1:1'b0;
    assign  RegWrite=((OP==0)&&(Func==6'd0||Func==6'd3||Func==6'd2||Func==6'd32
                    ||Func==6'd33||Func==6'd34||Func==6'd36||Func==6'd37
                    ||Func==6'd39||Func==6'd42||Func==6'd43||Func==6||Func==7))||
                    (OP==6'd3||OP==6'd8||OP==6'd12||
                        OP==6'd9||OP==6'd10||OP==6'd13||OP==6'd35||OP==36)?1'b1:1'b0;
    assign  SysCALL=((OP==6'd0)&&(Func==6'd12))?1'b1:1'b0;
    assign  SignedExt= (OP==6'd8||OP==1||OP==36)?1'b1:
                        (OP==6'd9)?1'b1:
                        (OP==6'd10)?1'b1:
                        (OP==6'd35)?1'b1:
                        (OP==6'd43)?1'b1:
                        (OP==6'd40)?1'b1:1'b0;
    assign  RegDst=(OP!=0)?1'b0:
                    ((Func==0)||(Func==3)||(Func==2)||
                    (Func==32)||(Func==33)||(Func==34)||
                    (Func==36)||(Func==37)||(Func==39)||
                    (Func==42)||(Func==43)||Func==6||Func==7)?1'b1:1'b0;
    assign  Beq=(OP==4)?1'b1:1'b0;
    assign  Bne=(OP==5)?1:0;
    assign  JR=((OP==0)&&(Func==8))?1'b1:1'b0;
    assign  JMP=((OP==0)&&(Func==8)||(OP==2)||(OP==3))?1'b1:1'b0;
    assign  JAL=(OP==3)?1'b1:1'b0;
    assign BGEZ=(OP==1)?1'b1:1'b0;
    assign SV=((OP==0)&&(Func==6||Func==7))?1'b1:1'b0;
    assign LBU=(OP==36)?1'b1:1'b0;
endmodule // 
module ALU_control(
    input [5:0] Func,
    input [5:0] OP,
    output  [3:0] ALU_OP
);
    assign ALU_OP=  (OP==0&&Func==0)?4'd0:
                    (OP==0&&(Func==3||Func==7))?4'd1:
                    (OP==0&&(Func==2||Func==6))?4'd2:
                    ((OP==0&&(Func==32||Func==33))||OP==8||OP==9||OP==35||OP==43||OP==36)?4'd5:
                    (OP==0&&(Func==34||Func==34))?4'd6:
                    ((OP==0&&Func==36)||OP==12)?4'd7:
                    ((OP==0&&Func==37)||OP==13)?4'd8:
                    (OP==0&&Func==39)?4'd10:
                    ((OP==0&&Func==42)||OP==10||OP==1)?4'd11:
                    (OP==0&&Func==43)?4'd12:4'd0;
endmodule // ALU_control
