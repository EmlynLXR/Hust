`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/04 10:21:41
// Design Name: 
// Module Name: J_K
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


module J_K(j,k,clk,q,qn);
    input j,k,clk;
    output reg q;
    output qn;
initial begin
    q<=0;
end
    assign qn = ~q;
    
    always@(negedge clk)begin
   	    case({j,k})
       	    2'b00:q<=q;
            2'b01:q<=0;
            2'b10:q<=1;
            2'b11:q<=~q;
        endcase
    end
endmodule

