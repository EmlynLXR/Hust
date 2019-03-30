`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/26/2019 07:38:09 PM
// Design Name: 
// Module Name: IF_ID
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


module IF_ID(
    input clk,
    input rst,
    input en,
    input [31:0]IRin,
    input [31:0]PCin,
    output reg [31:0]IRout,
    output reg [31:0]PCout
    );
    initial begin
        IRout <= 0;
        PCout <= 0;
    end
    
    always@(posedge clk)begin
        if(en==1);
        else if(rst==1)begin
            IRout <= 0;
            PCout <= 0;           
        end
        else begin
            PCout <= PCin;
            IRout <= IRin;
        end
    end
endmodule
