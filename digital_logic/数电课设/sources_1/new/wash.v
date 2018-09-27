`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/18 21:47:48
// Design Name: 
// Module Name: wash
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

//以计数到60的方式实现分钟
//在仿真和检查时将参数N设置为了3
module wash(
    input clk_s,
    input reset,
    input[2:0] weight,
    input power_led,
    input pause_led,
    input [5:0] mode,
    input flag_finish,

    output reg [1:0] program,
    output reg [4:0] state,
    output reg finish,
    output reg [7:0] total_time,
    output reg [7:0] current_time,
    output reg [7:0] water_level,
    output reg flag_run
    );
    parameter [7:0] N=3;//在仿真时设置为3，实际应为60
    wire [7:0] s_js_time;
    wire [7:0] s_ps_time;
    assign s_js_time = {4'b00000,weight};
    assign s_ps_time = {4'b00000,weight};
    wire [7:0] s_xy_time = 8'b00001001;
    wire [7:0] s_py_time = 8'b00000110;
    wire [7:0] s_sg_time = 8'b00000011;

    wire [7:0] p_xd_time;
    wire [7:0] p_px_time;
    wire [7:0] p_ts_time;
    assign p_xd_time = s_js_time+s_xy_time;
    assign p_px_time = s_ps_time+s_sg_time+s_js_time+s_py_time;
    assign p_ts_time = s_ps_time+s_sg_time;

    parameter p_reset=2'b00,p_xd=2'b01,p_px=2'b10,p_ts=2'b11;
    parameter ma=6'b100000,mb=6'b010000,mc=6'b001000,md=6'b000100,me=6'b000010,mf=6'b000001,m_reset=6'b000000;

    reg [7:0] times;
    reg flag_init;

    initial begin 
        total_time=8'b00000000;
        current_time=8'b00000000;
        water_level=8'b00000000;
        
        state=5'b00000;
        program=p_reset;

        finish=1'b0;
        flag_run=1'b0;
        flag_init=1'b0;

        times=N;
    end

    always @(posedge clk_s) begin
        if(!reset) begin //没有打开系统开关
            total_time=8'b00000000;
            current_time=8'b00000000;
            water_level=8'b00000000;
            
            state=5'b00000;
            program=p_reset;
            finish=0;
            flag_run=0;
            flag_init=0; 
            times=N;
        end
        if(reset && flag_init==0)begin//打开系统开关但没有初始化
            flag_init=1;
            current_time=p_xd_time;
            total_time=p_xd_time+p_px_time+p_ts_time;
            water_level=8'b00000000;
            program=p_xd;
            state=5'b11100;
            times=N;
        end 
        else begin//打开系统开关并已经初始化
            if(power_led==1)begin//电源指示灯亮
                if(pause_led==0)begin//暂停状态
                    if(flag_run==0)begin//没有正在运行的程序则进行以下初始化过程
                        finish=0;
                        case(mode)
                            ma: begin 
                                current_time=p_xd_time;
                                total_time=p_xd_time+p_px_time+p_ts_time;
                                water_level=8'b00000000;
                                program=p_xd;
                                state=5'b11100;
                                end                    
                            mb: begin
                                current_time=p_xd_time;
                                total_time=p_xd_time;
                                water_level=8'b00000000;
                                program=p_xd;
                                state=5'b10000;
                                end
                            mc: begin
                                current_time=p_xd_time;
                                total_time=p_xd_time+p_px_time;
                                water_level=8'b00000000;
                                program=p_xd;
                                state=5'b11000;
                                end
                            md: begin
                                current_time=p_px_time;
                                total_time=p_px_time;
                                water_level={4'b0000,weight};
                                program=p_px;
                                state=5'b01000;
                                end
                            me: begin
                                current_time=p_px_time;
                                total_time=p_px_time+p_ts_time;
                                water_level={4'b0000,weight};
                                program=p_px;
                                state=5'b01100;
                                end
                            mf: begin
                                current_time=p_ts_time;
                                total_time=p_ts_time;
                                water_level={4'b0000,weight};
                                program=p_ts;
                                state=5'b00100;
                                end
                            default:program=p_reset; 
                        endcase
                    end
                end
                else begin//启动状态
                    if(flag_finish==0) begin //若还没有结束程序或结束后又有了新的操作  
                        flag_run=1;//标志变量用来指示系统正在运行
                        case(program)  //状态机实现洗衣过程
                            p_reset:begin
                                if(mode==ma || mode==mb || mode==mc) program=p_xd;
                                else if(mode==md || mode==me) program=p_px;
                                else if(mode==mf) program=p_ts;
                                else program=p_reset;
                            end                    
                            p_xd:begin
                                times=times-1;
                                if(current_time>s_xy_time) state[1]=1;
                                else state[1]=0;

                                if(times==0)begin
                                    times=N;

                                    current_time=current_time-1;
                                    total_time=total_time-1;   
                                    if(current_time>=s_xy_time)water_level=water_level+1;
                                    if(current_time>s_xy_time) state[1]=1;
                                    else state[1]=0;  

                                    if(current_time==0)begin 
                                        state[4]=0;
                                        if(mode==ma ||mode==mc) begin program=p_px;current_time=p_px_time;state[0]=1;end
                                        else if(mode==mb) begin 
                                            finish=1;
                                            flag_run=0;

                                            current_time=p_xd_time;
                                            total_time=p_xd_time+p_px_time+p_ts_time;
                                            program=p_xd;
                                            state=5'b11100;
                                        end
                                        else program=p_reset;
                                    end                             
                                end
                            end
                            p_px:begin
                                times=times-1;
                                if(current_time>s_sg_time+s_ps_time+s_py_time)state[0]=1;
                                else if(current_time>s_ps_time+s_py_time) state[0]=0;
                                else if(current_time>s_py_time) state[1]=1;
                                else state[1]=0;

                                if(times==0)begin  
                                    times=N; 

                                    current_time=current_time-1;
                                    total_time=total_time-1;
                                    if(current_time>s_sg_time+s_ps_time+s_py_time)state[0]=1;
                                    else if(current_time>s_ps_time+s_py_time) state[0]=0;
                                    else if(current_time>s_py_time) state[1]=1;
                                    else state[1]=0;
                                    if(current_time>=s_sg_time+s_ps_time+s_py_time)water_level=water_level-1;
                                    else if(current_time>=s_ps_time+s_py_time);
                                    else if(current_time>=s_py_time)water_level=water_level+1;

                                    if(current_time==0)begin
                                        state[3]=0;
                                        if(mode==ma || mode==me) begin program=p_ts;current_time=p_ts_time;state[0]=1;end
                                        else if(mode==mc || mode==md) begin
                                            finish=1;
                                            flag_run=0;
                                            current_time=p_xd_time;
                                            total_time=p_xd_time+p_px_time+p_ts_time;
                                            program=p_xd;
                                            state=5'b11100;
                                        end
                                        else program=p_reset;
                                    end
                                end                            
                            end  
                            p_ts:begin
                                times=times-1;
                                if(current_time>s_sg_time)state[0]=1;
                                else state[0]=0;

                                if(times==0)begin
                                    times=N;
                                    current_time=current_time-1;
                                    total_time=total_time-1;
                                    if(current_time>s_sg_time)state[0]=1;
                                    else state[0]=0;
                                    if(current_time>=s_sg_time)water_level=water_level-1;

                                    if(current_time==0)begin
                                        state[2]=0;
                                        finish=1;
                                        flag_run=0;
                                        current_time=p_xd_time;
                                        total_time=p_xd_time+p_px_time+p_ts_time;
                                        program=p_xd;
                                        state=5'b11100;
                                    end
                                end        
                            end
                            default:program=p_reset;
                        endcase 
                    end 
                end 
            end 
        end
    end 
endmodule