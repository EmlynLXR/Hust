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
	output [(DATA_WIDTH-1):0]data_out
);
    wire [9:0]sel_data;
    reg [31:0] inBytes;
    
    always @(sel,inD) begin
        case(sel) 
            4'b0000:inBytes= 32'b0;   
            4'b0001:inBytes= {24'b0,inD[7:0]};
            4'b0010:inBytes= {24'b0,inD[15:8]};
            4'b0100:inBytes= {24'b0,inD[23:16]};
            4'b1000:inBytes= {24'b0,inD[31:24]};
            4'b1100:inBytes= {16'b0,inD[31:16]};
            4'b0011:inBytes= {16'b0,inD[15:0]};
            4'b1111:inBytes= inD;
            default:inBytes= 0;
        endcase
    end
    
	assign sel_data={6'd0,data_addr};
	wire [7:0] Byte0,Byte1,Byte2,Byte3;
	ram1k_8 ram0(.A(A),.inD(inBytes[7:0]) , .str(sel[0]&str),.clk(clk),.outD(Byte0),.sel_data(sel_data),.data_out(data_out[7:0]));
	ram1k_8 ram1(.A(A),.inD(inBytes[15:8]), .str(sel[1]&str),.clk(clk),.outD(Byte1),.sel_data(sel_data),.data_out(data_out[15:8]));
	ram1k_8 ram2(.A(A),.inD(inBytes[23:16]),.str(sel[2]&str),.clk(clk),.outD(Byte2),.sel_data(sel_data),.data_out(data_out[23:16]));
	ram1k_8 ram3(.A(A),.inD(inBytes[31:24]),.str(sel[3]&str),.clk(clk),.outD(Byte3),.sel_data(sel_data),.data_out(data_out[31:24]));
	

	always @(sel,Byte0,Byte1,Byte2,Byte3) begin
		case (sel)
			4'b0000:outD = 0;
			4'b0001:outD = {24'b0,Byte0};
			4'b0010:outD = {24'b0,Byte1};
			4'b0100:outD = {24'b0,Byte2};
			4'b1000:outD = {24'b0,Byte3};
			4'b1100:outD = {16'b0,Byte3,Byte2};
			4'b0011:outD = {16'b0,Byte2,Byte1};
			4'b1111:outD = {Byte3,Byte2,Byte1,Byte0};
			default:outD = 32'd0;
		endcase
	end

endmodule
