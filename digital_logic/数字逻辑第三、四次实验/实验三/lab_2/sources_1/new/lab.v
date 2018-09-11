`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/04 10:23:33
// Design Name: 
// Module Name: main
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


module lab(
    input X,
    output Z,
    output q1,
    output q2,
    output q3,
    output q4
    );

    wire qn1,qn2,qn3,qn4;

    J_K jk1(1'b1,1'b1,X,q1,qn1);
    J_K jk2(qn4,1'b1,q1,q2,qn2);
    J_K jk3(1'b1,1'b1,q2,q3,qn3);
    J_K jk4(q3&q2,1'b1,q1,q4,qn4);  
    assign Z=X&q1&q4;
endmodule
