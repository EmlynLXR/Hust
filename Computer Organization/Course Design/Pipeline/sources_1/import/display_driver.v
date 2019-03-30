`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/15 12:21:27
// Design Name: 
// Module Name: display_driver
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


/* 
 * 数码管显示驱动模块， 用于将数值转化为数码管输出
 * input params: 
 *      clk_dvid: 数码管动态显示时钟
 *      price: 商品价格， 0 - no product, 1 - ￥2.5 product, 2 - ￥5 product
 *      money: 当前金额
 *      display_hello: 是否显示"HELLO"
 *      close_display: 是否关闭显示
 * output params:
 *      seg: 数码管显示信号
 *      seg_pos: 数码管片选信号
 */
module display_driver(
    input clk_dvid,
    input [31:0]seg_content,
    output reg [2:0]pos,
    output reg [3:0]num
    );
    
    initial begin
        pos = 0;
        num = 4'b0000;
    end 
    
    always@ (posedge clk_dvid) begin
        pos = pos + 1;
        case (pos)
            0: begin
//                num = 0;
                num = seg_content[3:0];
            end
            1: begin 
//                num = 1;
                num = seg_content[7:4];
            end
            2: begin 
//                num = 2;
                num = seg_content[11:8];
            end
            3: begin
//                num = 3;
                num = seg_content[15:12];
            end
            4: begin
//                num = 4;
                num = seg_content[19:16];
            end 
            5: begin
//                num = 5;
                num = seg_content[23:20];
            end
            6: begin
//                num =  6;
                num = seg_content[27:24];
            end
            7: begin
//                num = 7;
                num = seg_content[31:28];
            end
        endcase
        
    end
    
endmodule




