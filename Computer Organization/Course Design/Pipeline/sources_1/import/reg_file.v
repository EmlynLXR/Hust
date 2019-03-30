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
       regs[0] <= 0;regs[1] <= 0;regs[2] <= 0;regs[3] <= 0;regs[4] <= 0;regs[5] <= 0;regs[6] <= 0;regs[7] <= 0;
       regs[8] <= 0;regs[9] <= 0;regs[10] <= 0;regs[11] <= 0;regs[12] <= 0;regs[13] <= 0;regs[14] <= 0;regs[15] <= 0;
       regs[16] <= 0;regs[17] <= 0;regs[18] <= 0;regs[19] <= 0;regs[20] <= 0;regs[21] <= 0;regs[22] <= 0;regs[23] <= 0;
       regs[24] <= 0;regs[25] <= 0;regs[26] <= 0;regs[27] <= 0;regs[28] <= 0;regs[29] <= 0;regs[30] <= 0;regs[31] <= 0;      
    end

    assign A = regs[ra];
    assign B = regs[rb];
    always @(negedge clk) begin
        if((WE == 1)&&rw!=0 ) regs[rw] = Din;  
    end
    
endmodule
