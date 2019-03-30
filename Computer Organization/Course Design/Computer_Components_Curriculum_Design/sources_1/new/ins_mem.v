`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 15:41:59
// Design Name: 
// Module Name: ins_mem
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


module ins_mem
#(parameter DATA_WIDTH=32,parameter ADDR_WIDTH=10)
(
	input	[(ADDR_WIDTH-1):0] A,
	output	[(DATA_WIDTH-1):0] D
);
	reg[(DATA_WIDTH-1):0] mem[2**ADDR_WIDTH-1:0];
	initial begin
	   mem[0] = 0;
		$readmemh("C:\\Users\\LXR\\Desktop\\Computer_Components_Curriculum_Design\\benchmark_ccmb.mif",mem);
	end
	
	assign D = mem[A];
endmodule
