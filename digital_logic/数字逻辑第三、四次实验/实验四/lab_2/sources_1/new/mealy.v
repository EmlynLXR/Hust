`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/12 17:43:49
// Design Name: 
// Module Name: mealy
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


module mealy(
    input clk,
    input in,
    // output wire clk_n,
    output reg [4:0] state,
    output reg out
    );
    // divider my_divider(clk,clk_n);
    parameter STA=5'b00001,STB=5'b00010,STC=5'b00100,STD=5'b01000,STE=5'b10000;
    
    initial state<=STA;

    always@(posedge clk)begin
    case(state)
        STA:
            if(in==1'b0)begin state<=STA;out<=1'b0;end
            else begin state<=STB;out<=1'b0;end
        STB:
            if(in==1'b0)begin state<=STC;out<=1'b0;end
            else begin state<=STB;out<=1'b0;end
        STC:
            if(in==1'b0)begin state<=STA;out<=1'b0;end
            else begin state<=STD;out<=1'b0;end
        STD:
            if(in==1'b0)begin state<=STC;out<=1'b0;end
            else begin state<=STE;out<=1'b0;end
        STE:
            if(in==1'b0)begin state<=STA;out<=1'b1;end
            else begin state<=STB;out<=1'b0;end
        default:begin state<=STA;out<=1'b0;end
    endcase
    end
endmodule

// module divider(clk,clk_n);
//     input clk;
//     output reg clk_n;

//     parameter n=100_000_000;
//     reg [31:0] counter;
// initial begin 
//     clk_n<=0;
//     counter<=0;
// end
//     always @(posedge clk)begin
//       counter<=counter+1;
//       if(counter==n/2-1)begin 
//         clk_n<=~clk_n;
//         counter<=0;
//       end
//     end
// endmodule
