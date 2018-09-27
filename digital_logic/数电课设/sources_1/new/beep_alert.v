`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/11 18:25:51
// Design Name: 
// Module Name: beep_alert
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

//在仿真时和使用开发板时使用不同的参数，需注意根据使用切换
module beep_alert(
    input clk_n,
    input power_led,
    input pause,
    input button,
    input finish,

    //使用开发板或运行主模块时时注释以下三行代码
    // output reg[3:0] times,
    // output reg flag_finish,
    // output clk_n,

    output sign_led
    );

    reg temp;
    reg flag_init;

    //使用开发板或运行主模块时取消以下三行代码的注释
    reg [3:0] times;
    reg flag_finish;

    initial begin
        temp=0;
        flag_init=0;
        flag_finish=0;
        times=4'b0000;
    end

    always @(posedge clk_n)begin
        if(power_led==0) begin
            flag_finish=0;
            flag_init=0;
        end
        else if(power_led==1 && flag_init==0) begin
            temp=1;
            flag_init=1;
        end
        else if(finish && flag_finish==0)begin
            temp=1;
            flag_finish=1;
            times=4'b0001;
        end
        else if(flag_finish==1)begin
            times=times+1;

            if(times==4'b0100 || times==4'b1000) temp=0;
            else if(times>4'b1011) begin 
                temp=0;
                times=4'b0000;
                flag_finish=0;
            end
            else temp=1;
        end
        else temp=0;
    end
 
    assign sign_led = power_led && (pause || button || (clk_n&&temp));
endmodule
