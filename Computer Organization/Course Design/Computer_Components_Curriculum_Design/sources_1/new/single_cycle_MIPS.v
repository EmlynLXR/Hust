`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/02/18 19:06:59
// Design Name: 
// Module Name: single_cycle_MIPS
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


module single_cycle_MIPS(
    input [3:0]data_addr,
    input clk_dvid,
    input seg_dvid,
    input go,
    input reset,
    input [2:0]display_switch,
    output [7:0]seg_an,
    output [7:0]seg
    );
    
    
    reg [31:0]PC = 0;
    
    /* RAM Module */
    wire [31:0]RAM_data;
    ins_mem RAM(.A(PC[11:2]), .D(RAM_data));
    
    
    /* Controller Module */
    wire RegWrite, SYSCALL, MemToReg, MemWrite, ALU_SRC, SignedExt, RegDst;
    wire JMP, JR, JAL, BEQ, BNE;
    wire [3:0]ALU_op;
    wire BGEZ,SV,LBU;
    CPU_control CPUController(.Func(RAM_data[5:0]),
                              .OP(RAM_data[31:26]),
                              .ALU_OP(ALU_op),
                              .MemToReg(MemToReg),
                              .MemWrite(MemWrite),
                              .ALU_SRC(ALU_SRC),
                              .RegWrite(RegWrite),
                              .SysCALL(SYSCALL),
                              .SignedExt(SignedExt),
                              .RegDst(RegDst),
                              .Beq(BEQ),
                              .Bne(BNE),
                              .JR(JR),
                              .JMP(JMP),
                              .JAL(JAL),
                              .BGEZ(BGEZ),
                              .SV(SV),
                              .LBU(LBU));
    
    
    
    
    /* RegisterFile Module */
    wire[31:0]R1, R2;
    wire [4:0]RW;
    wire [4:0]RA;
    wire [4:0]RB;
    wire [31:0]R_write_data;
    regFile reg_file(.clk(clk_dvid), .WE(RegWrite), .rw(RW), .ra(RA), 
                     .rb(RB), .Din(R_write_data), .A(R1), .B(R2));
    
    
    /* ROM Module */
    reg[3:0]sel;
    //reg[3:0] sel = 4'b1111;
    always@(*)begin
        if(LBU==1)begin
            case(ALU_R1[1:0])
                2'b00:sel=4'b0001;
                2'b01:sel=4'b0010;
                2'b10:sel=4'b0100;
                2'b11:sel=4'b1000;
             endcase
        end
        else sel=4'b1111;
    end
    wire[31:0] ROM_data;
    wire [31:0] data_out;
    data_mem ROM(.data_addr(data_addr),
                 .A(ALU_R1[11:2]),
                 .inD(R2),
                 .sel(sel),
                 .str(MemWrite),
                 .clk(clk_dvid),
                 .outD(ROM_data),
                 .data_out(data_out));
    
    /* ALU Module */
    wire equal;
    wire[31:0] ALU_R1, ALU_R2;
    wire [31:0]ALU_y;
    wire [4:0]ALU_shamt;
    ALU alu(
        .x(R1),
        .y(ALU_y),
        .shamt(ALU_shamt),
        .alu_op(ALU_op),
        .result(ALU_R1),
        .result2(ALU_R2),
        .equal(equal)
        );
    
    
    /* syscall */
    wire showA0, HALT;
    syscall Syscall(.data(R1),
                    .syscall(SYSCALL),
                    .show(showA0),
                    .halt(HALT));
    
    wire BJMP = (equal & BEQ) | (!equal & BNE)|(!ALU_R1[0]&BGEZ);
    wire[31:0] totalCycle, numUncontrol, numControl;
    /* Display */
    CycleDisplay cycleDisplay(.clk(clk_dvid),
                              .stop(HALT),
                              .rst(reset),
                              .jmp(JMP),
                              .bjmp(BJMP),
                              .total_cycle(totalCycle),
                              .num_uncontrol(numUncontrol),
                              .num_control(numControl));
                              
    wire [31:0]segContent;
    display_change displayChange(.clk(clk_dvid),
                                 .showA0(showA0),
                                 .ledData(R2),           //主显�?
                                 .total_cycle(totalCycle),       //总周期数
                                 .data_out(data_out),
                                 .num_uncontrol(numUncontrol),     //无条件跳转数
                                 .num_control(numControl),       //有条件跳转数
                                 .switch(display_switch), //选择显示的输�?
                                 .new_out(segContent));
    
    wire [3:0]seg_num;
    wire [2:0]seg_pos;
    display_driver displayDriver(.clk_dvid(seg_dvid),
                                 .seg_content(segContent),
                                 .pos(seg_pos),
                                 .num(seg_num));
                                 
    decoder_38 decoder38(seg_pos, seg_an);
    seven_seg_driver sevenSegDriver(.num(seg_num),
                                    .point(0),    // 显示小数�? - 先为0
                                    .seg(seg));
    
    wire[4:0] RT = RAM_data[20:16];
    wire[4:0] RD = RAM_data[15:11];
    wire[4:0] RS = RAM_data[25:21];
    wire[15:0] IMM = RAM_data[15:0];
    
    
    initial begin
        PC = 0;
        sel = 4'b1111;
    end

    
    
    assign RA = (SYSCALL==1)?5'h02:RS;
    assign RB = (SYSCALL==1)?5'h04:RT;
    assign RW = (JAL)?31:((RegDst)?RD:RT);
    
    assign ALU_y = (ALU_SRC)?((SignedExt)?{{16{IMM[15]}}, IMM}:{16'h0, IMM}):R2;
    
            
    /* shamt -- 24 ins. version - always from ins. memory */
    assign ALU_shamt = (SV==1)?R1:RAM_data[10:6]; 
    
    assign R_write_data = (MemToReg)?ROM_data:((JAL)?PC + 4:ALU_R1);

    
    always@(posedge clk_dvid) begin
        /* ----- PC ----- */
        if (JMP) begin
            if (JR) begin
                /* PC = $RS */
                PC = R1;
            end
            else begin
                PC=PC+4;
                PC = {PC[31:28],RAM_data[25:0],2'b00};
            end
            
        end
        else if (BJMP) begin
            /* beq or bne */
            PC = PC + 4 + ( $signed(IMM) << 2);
        end
        else begin
            if (!HALT | go) begin
                PC = PC + 4;
            end
        end
        
        if (reset) begin
            PC = 0;
        end
        
//        /* Register RW selector */
//        if (JAL) begin
//            /* store PC+4 to $31 */
//            RW = 31;
//        end
//        else if (RegDst) begin
//            RW = RD;
//        end
//        else begin
//            RW = RT;
//        end
        
        
//        /* Register RA \ RB selector */
        
//        if (SYSCALL) begin
//            RA = 5'h02;
//            RB = 5'h04; 
//        end
//        else begin
//            RA <= RS;
//            RB <= RT;
//        end
        
        
        /* Register dataIn selector */
//        if (MemToReg) begin
//            R_write_data = ROM_data;
//        end
//        else begin
//            if (JAL) begin
//                /* store PC+4 to $31 */
//                R_write_data = PC + 4;
//            end
//            else begin
//                R_write_data = ALU_R1;
//            end
//        end
        
        
//        /* ALU source B selector */
//        if (ALU_SRC) begin
//            if (SignedExt) begin
//                ALU_y = {{16{IMM[15]}}, IMM};
//            end
//            else begin
//                ALU_y = {16'h0, IMM};
//            end
//        end
//        else begin
//            ALU_y = R2;
//        end   
        
        
//        /* shamt -- 24 ins. version - always from ins. memory */
//        ALU_shamt = RAM_data[10:6];   
    
    end
    
    
endmodule
