`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 19:59:10
// Design Name: 
// Module Name: syscall
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


module syscall(
    input [31:0]data,
    input syscall,
    input go,
    output wire show,
    output wire halt
    );

    assign show=((data==32'h00000022)&syscall)?1:0;
    assign halt=go ? 0 : ((data!=32'h00000022)&syscall)?1:0;
endmodule
