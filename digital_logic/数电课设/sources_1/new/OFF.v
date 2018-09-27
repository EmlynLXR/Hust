`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/19 20:52:44
// Design Name: 
// Module Name: OFF
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


module OFF(
    input clk_s,
    input reset,
    input finish,
    input button,
    input pause,

    output power_led,
    output reg flag_finish
    );

    reg flag;
    reg flag_init;
    reg [3:0] times;

    initial begin
        flag=0;
        flag_finish=0;
        flag_init=0;
    end

    assign power_led = reset & flag;

    always @(posedge finish or posedge button or posedge pause or negedge flag)begin
        if(flag==0) flag_finish=0;
        else if(finish) flag_finish=1;
        else if(button) flag_finish=0;
        else if(pause) flag_finish=0;
    end

    always @(posedge clk_s or posedge reset)begin
        if(!reset)begin
            flag<=0;
            flag_init=0;
        end
        else if(reset==1&&flag_init==0)begin
            flag<=1;
            flag_init=1;
        end
        else if(reset==1&&flag_finish==1)begin
            if(times==4'b1001) begin 
                flag<=0;
                times<=4'b0000;
            end
            times<=times+1;
        end
        else times<=4'b0000;
    end   
endmodule
