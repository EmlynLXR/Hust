`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/10 15:08:16
// Design Name: 
// Module Name: decoder3_8
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


module decoder3_8(power_led,num, sel);
    input power_led;
    input  [2: 0] num;       // 数码管编号：0~7
    output reg [7:0] sel;       // 7段数码管片选信号，低电平有效

    always @(num) begin
        if(power_led==0) sel=8'b11111111;
        else begin
            case(num)
                3'd0: sel = 8'b11111110;
                3'd1: sel = 8'b11111101;
                3'd2: sel = 8'b11111111;
                3'd3: sel = 8'b11110111;
                3'd4: sel = 8'b11101111;
                3'd5: sel = 8'b11111111;
                3'd6: sel = 8'b10111111;
                3'd7: sel = 8'b01111111;
                default: sel = 8'b11111111;
            endcase         
        end
    end

endmodule
