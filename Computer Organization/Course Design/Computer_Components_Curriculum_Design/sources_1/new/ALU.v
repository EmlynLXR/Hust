`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 15:39:28
// Design Name: 
// Module Name: ALU
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


module ALU(
    input [31:0] x,
    input [31:0] y,
    input [4:0] shamt,
    input [3:0] alu_op,

    output reg [31:0] result,
    output reg [31:0] result2,
    output wire equal
    );

    assign equal=(x==y)?1:0;

    always@(*)begin
        case(alu_op)
            4'b0000:{result2,result}<=y<<shamt;
            4'b0001:{result2,result}<=($signed(y))>>>shamt;
            4'b0010:{result2,result}<=y>>shamt;
            4'b0011:{result2,result}<=x*y;
            4'b0100:begin result<=x/y;result2<=x%y; end
            4'b0101:{result2,result}<=x+y;
            4'b0110:{result2,result}<=x-y;
            4'b0111:begin result<=x&y;result2<=0;end
            4'b1000:begin result<=x|y;result2<=0;end
            4'b1001:begin result<=x^y;result2<=0;end
            4'b1010:begin result<=~(x|y);result2<=0;end
            4'b1011:begin result<=($signed(x)<$signed(y))?1:0;result2<=0;end
            4'b1100:begin result<=($unsigned(x)<$unsigned(y))?1:0;result2<=0;end
        endcase
    end
endmodule
