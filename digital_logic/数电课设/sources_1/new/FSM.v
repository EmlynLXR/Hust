`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/10 15:43:54
// Design Name: 
// Module Name: FSM
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


module FSM(
    input power_led,
    input finish,
    input in,
    input flag_run,

    output reg [5:0] mode
    );
    parameter STA=6'b100000,STB=6'b010000,STC=6'b001000,STD=6'b000100,STE=6'b000010,STF=6'b000001;

    reg flag;  

    initial begin
        mode=6'b000000;
        flag=0;
    end

    always@(posedge in or posedge finish or negedge power_led)begin
        if(power_led==0) mode=STA;
        else if(finish==1 && flag==0) begin
            mode=STA;
            flag=1; 
        end
        else if(flag_run==1);//正在运行时不能修改模式
        else begin
            flag=0;
            case(mode)
                STA:
                    if(in==1'b1)begin mode=STB;end
                    else begin mode=STA;end
                STB:
                    if(in==1'b1)begin mode=STC;end
                    else begin mode=STB;end
                STC:
                    if(in==1'b1)begin mode=STD;end
                    else begin mode=STC;end
                STD:
                    if(in==1'b1)begin mode=STE;end
                    else begin mode=STD;end
                STE:
                    if(in==1'b1)begin mode=STF;end
                    else begin mode=STE;end
                STF:
                    if(in==1'b1)begin mode=STA;end
                    else begin mode=STF;end
                default:begin mode=STA;end
            endcase 
        end  
    end
endmodule
