`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/09 17:21:49
// Design Name: 
// Module Name: sim
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


module sim();
    reg CP;
    reg M;
    wire D,C,B,A;
    reg LD;
    reg CLR;
    wire QD,QC,QB,QA;
    wire Qcc;


initial begin
    CP<=0;
    M<=1;
    LD<=1;
    CLR<=1;
    #50 LD<=0;
    #50 LD<=1;
    #50 LD<=0;
    #50 LD<=1;
    #500 M<=0;
end
    assign {D,C,B,A}=4'b0100;
    

    always #10 CP<=~CP;
    counter my_counter(D,C,B,A,CP,M,LD,CLR,QD,QC,QB,QA,Qcc);
endmodule
