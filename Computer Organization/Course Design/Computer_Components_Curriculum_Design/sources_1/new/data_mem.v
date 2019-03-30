`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 18:37:06
// Design Name: 
// Module Name: data_mem
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


module data_mem
#(parameter DATA_WIDTH=32,parameter ADDR_WIDTH=10)
(
	input [3:0] data_addr,
  input [(ADDR_WIDTH-1):0] A,
	input [(DATA_WIDTH-1):0] inD,
	input [3:0]sel,
	input str,
	input clk,
	output reg [(DATA_WIDTH-1):0]outD,
	output reg [(DATA_WIDTH-1):0]data_out
);
	parameter BYTE_WIDTH = 8;
	
	reg[(DATA_WIDTH-1):0] ram[(2**ADDR_WIDTH-1):0];
	initial begin
			//$readmemh("F:/init_mem.txt",ram);
	end
	always @ (posedge clk) begin
		if(str)	begin
			if(sel[3])  ram[A][(DATA_WIDTH-BYTE_WIDTH*0-1):(DATA_WIDTH-BYTE_WIDTH*1)] <= inD[(DATA_WIDTH-BYTE_WIDTH*0-1):(DATA_WIDTH-BYTE_WIDTH*1)];
			if(sel[2])  ram[A][(DATA_WIDTH-BYTE_WIDTH*1-1):(DATA_WIDTH-BYTE_WIDTH*2)] <= inD[(DATA_WIDTH-BYTE_WIDTH*1-1):(DATA_WIDTH-BYTE_WIDTH*2)];
			if(sel[1])  ram[A][(DATA_WIDTH-BYTE_WIDTH*2-1):(DATA_WIDTH-BYTE_WIDTH*3)] <= inD[(DATA_WIDTH-BYTE_WIDTH*2-1):(DATA_WIDTH-BYTE_WIDTH*3)];
			if(sel[0])  ram[A][(DATA_WIDTH-BYTE_WIDTH*3-1):(DATA_WIDTH-BYTE_WIDTH*4)] <= inD[(DATA_WIDTH-BYTE_WIDTH*3-1):(DATA_WIDTH-BYTE_WIDTH*4)];
		end
		case (sel)
            4'b0000:outD[DATA_WIDTH-1:0]<=0;
            4'b0001:outD[DATA_WIDTH-1:0]<={24'b0,ram[A][BYTE_WIDTH*1-1:BYTE_WIDTH*0]};
            4'b0010:outD[DATA_WIDTH-1:0]<={24'b0,ram[A][BYTE_WIDTH*2-1:BYTE_WIDTH*1]};
            4'b0100:outD[DATA_WIDTH-1:0]<={24'b0,ram[A][BYTE_WIDTH*3-1:BYTE_WIDTH*2]};
            4'b1000:outD[DATA_WIDTH-1:0]<={24'b0,ram[A][BYTE_WIDTH*4-1:BYTE_WIDTH*3]};
            4'b1100:outD[DATA_WIDTH-1:0]<={16'b0,ram[A][BYTE_WIDTH*4-1:BYTE_WIDTH*2]};
            4'b0011:outD[DATA_WIDTH-1:0]<={16'b0,ram[A][BYTE_WIDTH*2-1:BYTE_WIDTH*0]};
            4'b1111:outD[DATA_WIDTH-1:0]<=ram[A];
            default:outD[DATA_WIDTH-1:0]<=0;
        endcase
	end

	
	wire sel_data;
	assign sel_data={6'd0,data_addr};
	always @(sel_data)
		data_out<=ram[sel_data];

endmodule
