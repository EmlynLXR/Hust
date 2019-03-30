`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 16:23:03
// Design Name: 
// Module Name: CycleDisplay
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


module CycleDisplay(clk,stop,rst,jmp,bjmp,dependency,
total_cycle,num_uncontrol,num_control,num_loaduse
);
  input clk, stop, rst;
  input jmp, bjmp, dependency;
  output reg [31:0] total_cycle,num_uncontrol,num_control, num_loaduse;
  
  initial begin
    total_cycle <= 0;
    num_uncontrol <= 0;
    num_control <= 0;
    num_loaduse <= 0;
  end

    always@(posedge clk) begin
    if(rst) begin num_loaduse <= 0; end
    else if(dependency) begin
        num_loaduse <= num_loaduse + 1;
    end    
  end
  
  always@(posedge clk) begin
    if(rst) begin total_cycle <= 0; end
    else if(!stop) begin
        total_cycle <= total_cycle + 1;
    end    
  end
  
  always@(posedge clk) begin
    if(rst) begin num_uncontrol <= 0; end
    else if(jmp & !stop) begin
        num_uncontrol <= num_uncontrol + 1;
    end    
  end
  
    always@(posedge clk) begin
    if(rst) begin num_control <= 0; end
    else if(bjmp & !stop) begin
        num_control <= num_control + 1;
    end    
  end
   

endmodule
