`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/10 14:37:44
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


//在仿真时和使用开发板时使用不同的参数和分频，需注意根据使用切换
module main(
    input clk,
    input reset,
    input pause,
    input [2:0] weight,
    input button,//模式转换按钮

    output clk_s,
    output power_led,//电源/运行指示灯
    output pause_led,//启动/暂停指示灯
    output sign_led,//蜂鸣信号

    //仿真时使用的参数声明
    output [1:0] program,
    output [5:0] mode,
    output [4:0] state,
    output [7:0] total_time,
    output [7:0] current_time,
    output [7:0] water_level,

    output xd_led,//洗涤灯
    output px_led,//漂洗灯
    output ts_led,//脱水灯
    output js_led,//进水灯
    output ps_led,//排水灯
    output x_p_t_led,//洗漂脱
    output x_led,//单洗
    output x_p_led,//洗漂
    output p_led,//单漂
    output p_t_led,//漂脱
    output t_led,//单脱

    output [7:0] seg,
    output [7:0] an
    );

    // // 使用开发板时使用的参数声明
    // wire [1:0] program;
    // wire [5:0] mode;
    // wire [4:0] state;    
    // wire [7:0] total_time;
    // wire [7:0] current_time;
    // wire [7:0] water_level;

    wire clk_n;
    // // 使用开发板时使用的分频
    // divider my_divider1(clk,   clk_s);
    // divider #(25_000_000) my_divider2(clk,   clk_n);

    //仿真时使用的分频
    divider #(2) my_divider1(clk,   clk_s);
    divider #(1) my_divider2(clk,   clk_n);

    wire finish;
    wire flag_finish;
    wire flag_run;

    //六位mode用六种状态表示六种模式，并直接与指示灯绑定
    parameter ma=6'b100000,mb=6'b010000,mc=6'b001000,md=6'b000100,me=6'b000010,mf=6'b000001,m_reset=6'b000000;
    assign {x_p_t_led,x_led,x_p_led,p_led,p_t_led,t_led} = power_led ? mode : 6'b000000;
    //五位state用来表示状态，xp_led、px_led、ts_led需要满足制定洗衣过程正在进行时闪烁，结束后熄灭
    assign {js_led,ps_led} = power_led ? state[1:0] : 0;
    assign xd_led = power_led ? ((program==2'b01 && flag_run==1 && pause_led==1) ? (state[4]&clk_s) :state[4]) :0;
    assign px_led = power_led ? ((program==2'b10 && flag_run==1 && pause_led==1) ? (state[3]&clk_s) :state[3]) :0;
    assign ts_led = power_led ? ((program==2'b11 && flag_run==1 && pause_led==1) ? (state[2]&clk_s) :state[2]) :0;    

    //显示数字
    dynamic_scan u_dscan (clk,power_led,water_level%10,power_led ? {4'b0000,weight}:0,4'hf,current_time%10,current_time/10,4'hf,total_time%10,total_time/10,seg,an);
    PAUSE pause_or_start(power_led,pause,finish,  pause_led);//控制暂停启动模块
    FSM change_mode(power_led,finish,button,flag_run,   mode);//模式选择模块
    beep_alert beep_alert(clk_n,power_led,pause,button,finish,   sign_led);//控制蜂鸣报警模块
    //最重要的模块：洗衣模块
    wash my_wash(clk_s,reset,weight,power_led,pause_led,mode,flag_finish,  program,state,finish,total_time,current_time,water_level,flag_run);
    OFF ONOFF(clk_s,reset,finish,button,pause,   power_led,flag_finish);//控制电源启动关闭模块
endmodule