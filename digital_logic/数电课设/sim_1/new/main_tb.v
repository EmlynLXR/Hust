`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/24 14:05:53
// Design Name: 
// Module Name: main_tb
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


module main_tb();
    reg clk;
    reg reset;
    reg pause;
    reg [2:0] weight;
    reg button;//模式转换按钮

    wire clk_s;
    wire power_led;//电源/运行指示灯
    wire pause_led;//启动/暂停指示灯
    wire sign_led;//蜂鸣信号

    wire [1:0] program;
    wire [5:0] mode;
    wire [4:0] state;    
    wire [7:0] total_time;
    wire [7:0] current_time;
    wire [7:0] water_level;

    wire xd;//洗涤灯
    wire px;//漂洗灯
    wire ts;//脱水灯
    wire js;//进水灯
    wire ps;//排水灯
    wire xpt;
    wire dx;
    wire xp;
    wire p;
    wire pt;
    wire t;

    wire [7:0] seg;
    wire [7:0] an;

    initial begin
        clk = 1'b0;
        forever #5 clk = ~clk;
    end 

    initial begin
        reset=0;
        pause=0;
        weight=3;
        button=0;
        #10 reset=1;

        #60 button=1;
        #20 button=0;
        #40 button=1;
        #20 button=0;
        #40 button=1;
        #20 button=0;
        #40 button=1;
        #20 button=0;
        #40 button=1;
        #20 button=0;
        #40 button=1;
        #20 button=0;
        
        #30 pause=1;
        #10 pause=0;
        #100 button=1;
        #10 button=0;

        #40 button=1;
        #10 button=0;     
        #10 pause=1;
        #10 pause=0;
        #20 button=1;
        #10 button=0;

        #40 button=1;
        #10 button=0;   
        #10 pause=1;
        #10 pause=0;
        #40 button=1;
        #10 button=0;

        #40 button=1;
        #10 button=0;   
    end

    main mymain_tb(clk,reset,pause,weight,button,   clk_s,power_led,pause_led,sign_led, program,mode,state,total_time,current_time,water_level,    xd,px,ts,js,ps, xpt,dx,xp,p,pt,t,  seg,an);
endmodule
