`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/09/20 08:38:23
// Design Name: 
// Module Name: seven_seg_driver
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
 * <-- led map -->
 * center - 6
 * right top - 1
 * top - 0
 * right bottom - 2
 * left top - 5
 * left bottom - 4
 * bottom - 3
 */
/*
 * 七段数码管显示驱动模块
 * @input params:
 *      num: 显示的数值, 0-9:数字0-9, 10:H, 11:E, 12:L, 13:O, 其它：不显示
 *      point: 是否显示小数点
 * @output parans:
 *      seg: 数码管显示信号
 */
module seven_seg_driver(
    input [3:0]num,
    input point,
    output reg [7:0]seg);
    
    always@ (num or point) begin
        case (num)
            0: begin
                if (point == 0) 
                    seg = 8'b11000000;
                else
                    seg = 8'b01000000;
            end
            1: begin
                if (point == 0) 
                    seg = 8'b11111001;
                else
                    seg = 8'b01111001;
            end                    
            2: begin
                if (point == 0) 
                    seg = 8'b10100100;
                else
                    seg = 8'b00100100;
            end
            3: begin
                if (point == 0) 
                    seg = 8'b10110000;
                else
                    seg = 8'b00110000;
            end   
            4: begin
                if (point == 0) 
                    seg = 8'b10011001;
                else
                    seg = 8'b00011001;
            end
            5: begin
                if (point == 0) 
                    seg = 8'b10010010;
                else
                    seg = 8'b00010010;
            end                    
            6: begin
                if (point == 0) 
                    seg = 8'b10000010;
                else
                    seg = 8'b00000010;
            end
            7: begin
                if (point == 0) 
                    seg = 8'b11111000;
                else
                    seg = 8'b01111000;
            end 
            8: begin
                if (point == 0)
                    seg = 8'b10000000;
                else
                    seg = 8'b00000000;
            end
            9: begin
                if (point == 0)
                    seg = 8'b10010000;
                else
                    seg = 8'b00010000;
            end
            10: begin
                /* A */
                seg = 8'b10001000;
            end
            
            11: begin
                /* E */
                seg = 8'b10000011;
            end
            
            12: begin
                /* L */
                seg = 8'b11000110;
                
            end
            
            13: begin
                /* O - same as number 0 */
                seg = 8'b10100001;
            end
            14: begin
                seg = 8'b10000110;
            end
            15: begin
                seg = 8'b10001110;
            end
            default: begin
                seg = 8'b11111111;
            end
        endcase
    end
        
endmodule

