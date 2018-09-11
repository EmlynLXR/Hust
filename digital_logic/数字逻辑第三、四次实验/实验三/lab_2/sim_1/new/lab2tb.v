`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/05 19:58:45
// Design Name: 
// Module Name: lab2tb
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


module lab2tb();
    reg X;
    wire Z,Q1,Q2,Q3,Q4;
    
    parameter DELY=10;
    lab mylab2(X,Z,Q1,Q2,Q3,Q4);
      
    initial begin
        X<=0;
    end
    always #(DELY) X = ~X; 
endmodule
