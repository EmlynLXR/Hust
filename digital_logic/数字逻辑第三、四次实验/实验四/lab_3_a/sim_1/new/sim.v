`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/12 18:57:05
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
    reg A;
    reg B;
    wire F1,F2,F3;

initial begin
    #5 begin A<=1;B<=0;end
    #5 begin A<=0;B<=0;end
    #5 begin A<=1;B<=1;end
    #5 begin A<=0;B<=1;end
    #5 begin A<=1;B<=0;end
    #5 begin A<=0;B<=0;end
    #5 begin A<=1;B<=1;end
    #5 begin A<=0;B<=1;end
end
    compare my_compare(A,B,F1,F2,F3);
endmodule
