module display_change(
input clk,
input showA0,
input [31:0] ledData,           //主显示
input [31:0] total_cycle,       //总周期数
input [31:0] num_uncontrol,     //无条件跳转数
input [31:0] num_control,       //有条件跳转数
input [31:0] data_out,          //内存数据观察
input [2:0] switch,             //选择显示的输出
output  reg [31:0] new_out
);

    reg [31:0] led_data;
    wire [3:0] T_cycle,H_cycle,Ten_cycle,O_cycle;    //总周期数
    wire [3:0] T_uncon,H_uncon,T_enuncon,O_uncon;    //无条件跳转
    wire [3:0] T_con,H_con,T_encon,O_con;            //有条件
    initial new_out = 0;
    always@(posedge clk) begin
        if(showA0) begin
             led_data = ledData;
        end
        case(switch)
            3'b000:new_out = led_data;
            3'b001:new_out = {16'd0,T_cycle,H_cycle,Ten_cycle,O_cycle};
            3'b010:new_out = {16'd0,T_uncon,H_uncon,T_enuncon,O_uncon};
            3'b011:new_out = {16'd0,T_con,H_con,T_encon,O_con};
            3'b100:new_out = data_out;
            default: new_out = 0;
        endcase
    end
    
    B2D b2d1 (total_cycle[11:0],T_cycle,H_cycle,Ten_cycle,O_cycle);
    B2D b2d2 (num_uncontrol[11:0],T_uncon,H_uncon,T_enuncon,O_uncon);
    B2D b2d3 (num_control[11:0],T_con,H_con,T_encon,O_con);                 
endmodule