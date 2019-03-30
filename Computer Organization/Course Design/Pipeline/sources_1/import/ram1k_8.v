`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/19 12:36:33
// Design Name: 
// Module Name: ram1k_8
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


module ram1k_8
#(parameter BYTE_WIDTH=8,parameter ADDR_WIDTH=10)
(
    input [(ADDR_WIDTH-1):0]A,
    input [(BYTE_WIDTH-1):0]inD,
    input str,
    input clk,
    output [(BYTE_WIDTH-1):0]outD,
    input [3:0] sel_data,
    output[7:0] data_out
);
	reg[(BYTE_WIDTH-1):0] ram[(2**ADDR_WIDTH-1):0];
	assign outD = ram[A];
	always @ (posedge clk) begin
		if(str) ram[A] <= inD;
	end
	
	assign data_out = ram[sel_data];
	
endmodule