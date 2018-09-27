`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/26 08:47:16
// Design Name: 
// Module Name: beep_alert_tb
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


module beep_alert_tb();
    reg clk;
    reg power_led;
    reg pause;
    reg button;
    reg finish;

    wire sign_led;
    wire [3:0] times;
    wire flag_finish;
    wire clk_n;

    initial begin
        clk = 1'b0;
        power_led=0;
        pause=0;
        button=0;
        finish=0;
        forever #5 clk = ~clk;
    end 

    initial begin
        #5 pause=1;
        #5 pause=0;
        #5 power_led=1;
        #40 pause=1;
        #10 pause=0;
        #10 button=1;
        #10 button=0;
        #10 finish=1;
        #10 finish=0;
        #500 power_led=0;
    end


    beep_alert mytb(clk,power_led,pause,button,finish,times,flag_finish,clk_n,sign_led);
endmodule
