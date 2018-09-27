`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/11 16:24:19
// Design Name: 
// Module Name: PAUSE
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


module PAUSE(
    input power_led,
    input pause,
    input finish,

    output reg pause_led
    );

    initial begin
      pause_led<=0;
    end

    always@(posedge pause or negedge power_led or posedge finish)begin
      if(power_led==0) pause_led=0;
      else if(finish==1) pause_led=0;
      else if(pause==1) pause_led=pause_led+1;
    end

endmodule
