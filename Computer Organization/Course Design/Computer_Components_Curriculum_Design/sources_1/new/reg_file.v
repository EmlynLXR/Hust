`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 16:17:32
// Design Name: 
// Module Name: regFile
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


module regFile(clk, WE, rw, ra, rb, Din, A, B);
    input clk, WE;
    input [4:0] rw, ra, rb;
    input [31:0] Din;
    output [31:0] A, B;
    
    reg [31:0] regs[0:31];

    initial begin
       regs[0] <= 0;
    end

    assign A = regs[ra];
    assign B = regs[rb];
    always @(posedge clk) begin
        if((WE == 1)&&rw!=0 ) regs[rw] = Din;  
    end
    
endmodule
