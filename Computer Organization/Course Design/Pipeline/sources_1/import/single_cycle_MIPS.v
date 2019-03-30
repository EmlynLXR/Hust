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
    
    reg [31:0]IF_PC = 0;
    wire [31:0] ID_PC , EX_PC , MEM_PC, WB_PC;
    wire [31:0]IF_IR, ID_IR, EX_IR, MEM_IR, WB_IR;   

    wire ID_RegWrite, ID_SYSCALL, ID_MemToReg, ID_MemWrite, ID_ALU_SRC, ID_SignedExt, ID_RegDst, ID_JMP, ID_JR, ID_JAL, ID_BEQ, ID_BNE, ID_BGEZ,ID_SV,ID_LBU;
    wire [3:0]ID_ALUop;
    wire [31:0]ID_R1, ID_R2;
    wire [4:0]ID_RA = (ID_SYSCALL==1)?5'h2:ID_IR[25:21];
    wire [4:0]ID_RB = (ID_SYSCALL==1)?5'h4:ID_IR[20:16];
    wire[4:0] ID_RW =  ID_JAL ? 5'h1f : ID_RegDst ? ID_IR[15:11] : ID_IR[20:16];
    wire[15:0] ID_Shamt = ID_SV ?ID_R1[4:0]:ID_IR[10:6]; 
    wire[15:0] IMM = ID_IR[15:0];
    wire[31:0] ID_imm16 = (ID_SignedExt==1) ? {{16{IMM[15]}}, IMM}:{16'h0, IMM};
    
    wire dependency;

    wire EX_RegWrite, EX_SYSCALL, EX_MemToReg, EX_MemWrite, EX_ALU_SRC, EX_SignedExt, EX_RegDst, EX_JMP, EX_JR, EX_JAL, EX_BEQ, EX_BNE, EX_BGEZ, EX_SV,EX_LBU;
    wire [3:0]EX_ALUop;  
    wire [31:0]EX_R1, EX_R2, Ori_EX_R1, Ori_EX_R2, EX_imm16, EX_Result1, EX_Result2;
    reg [31:0] NewPC;
    wire [4:0]EX_RW, EX_RA, EX_RB, EX_shamt;     
    wire [25:0]EX_imm26; 
    wire EX_equal;
    wire EX_B = EX_BEQ || EX_BNE || EX_BGEZ;
    wire EX_EQUAL = EX_BGEZ ? EX_Result1[0] : EX_equal;
    wire EX_B_en = (EX_EQUAL&&EX_BEQ) || (!EX_EQUAL&&EX_BNE) || (!EX_EQUAL&&EX_BGEZ); 
    wire EX_Branch = EX_JR || EX_JMP || EX_B_en;
    
    wire MEM_LBU, MEM_MemToReg, MEM_MemWrite, MEM_RegWrite, MEM_JAL, MEM_SYSCALL;
    wire[31:0]MEM_addr, MEM_R1, MEM_R2;
    wire [4:0]MEM_RW;
      
    wire WB_LBU, WB_MemToReg, WB_RegWrite, WB_JAL, WB_SYSCALL;
    wire[31:0]WB_Result1,WB_R1, WB_R2, WB_Dout, WB_Din;   
    wire [4:0]WB_RW; 
    
    wire PC_en;
    wire showA0, HALT;
    assign PC_en = (!HALT || go) && (!dependency);

    initial begin
        IF_PC = 0;
    end
        
    /* IF */

    /* RAM Module */  
    ins_mem RAM(.A(IF_PC[11:2]), .D(IF_IR));
    
    /* IF/ID */
    IF_ID IFID(.clk(clk_dvid),
               .rst(reset||(EX_Branch==1)),
               .en(PC_en==0),
               .IRin(IF_IR),
               .PCin(IF_PC),
               .IRout(ID_IR),
               .PCout(ID_PC)
               );
               
    always@(posedge clk_dvid)begin
        if(PC_en == 0);
        else if(EX_Branch)
            IF_PC <= NewPC;
        else if(!HALT || go)
            IF_PC <= IF_PC + 4;
        
        if(reset)
            IF_PC <= 0;
    end 
    /* ID */
    /* Controller Module */

    CPU_control CPUController(.Func(ID_IR[5:0]),
                              .OP(ID_IR[31:26]),
                              .ALU_OP(ID_ALUop),
                              .MemToReg(ID_MemToReg),
                              .MemWrite(ID_MemWrite),
                              .ALU_SRC(ID_ALU_SRC),
                              .RegWrite(ID_RegWrite),
                              .SysCALL(ID_SYSCALL),
                              .SignedExt(ID_SignedExt),
                              .RegDst(ID_RegDst),
                              .Beq(ID_BEQ),
                              .Bne(ID_BNE),
                              .JR(ID_JR),
                              .JMP(ID_JMP),
                              .JAL(ID_JAL),
                              .BGEZ(ID_BGEZ),
                              .SV(ID_SV),
                              .LBU(ID_LBU));


        
    /* RegisterFile Module */
    regFile reg_file(.clk(clk_dvid), .WE(WB_RegWrite), .rw(WB_RW), .ra(ID_RA), .rb(ID_RB), 
                     .Din(WB_Din), .A(ID_R1), .B(ID_R2));
                     
    /* LoadUse�������*/     
    data_dependency datadependency(.op(ID_IR[31:26]),.func(ID_IR[5:0]),
                                    .EX_RW(EX_RW),.ID_RA(ID_RA),.ID_RB(ID_RB),.EX_RegWrite(EX_RegWrite),.EX_MemToReg(EX_MemToReg),
                                    .dependency(dependency));            
                 
    /* ID/EX */                 
    ID_EX IDEX(.clk(clk_dvid),.rst(reset||(EX_Branch==1)||(PC_en==0)),.en(HALT),.IRin(ID_IR),.PCin(ID_PC),
                .JRin(ID_JR),.JMPin(ID_JMP),.LBUin(ID_LBU),.BEQin(ID_BEQ),.BNEin(ID_BNE),.BGEZin(ID_BGEZ),
                .MemToRegin(ID_MemToReg),.MemWritein(ID_MemWrite),.AluOpin(ID_ALUop),.AluSrcBin(ID_ALU_SRC),
                .RegWritein(ID_RegWrite),.JALin(ID_JAL),.SYSCALLin(ID_SYSCALL),.R1_numin(ID_RA),.R2_numin(ID_RB),
                .R1in(ID_R1),.R2in(ID_R2),.W_numin(ID_RW),.shamtin(ID_Shamt),.imm16in(ID_imm16),.imm26in(ID_IR[25:0]),
                .IRout(EX_IR),.PCout(EX_PC),
                .JRout(EX_JR),.JMPout(EX_JMP),.LBUout(EX_LBU),.BEQout(EX_BEQ),.BNEout(EX_BNE),.BGEZout(EX_BGEZ),
                .MemToRegout(EX_MemToReg),.MemWriteout(EX_MemWrite),.AluOpout(EX_ALUop),.AluSrcBout(EX_ALU_SRC),
                .RegWriteout(EX_RegWrite),.JALout(EX_JAL),.SYSCALLout(EX_SYSCALL),
                .R1_numout(EX_RA),.R2_numout(EX_RB),.R1out(Ori_EX_R1),.R2out(Ori_EX_R2),.W_numout(EX_RW),.shamtout(EX_shamt),
                .imm16out(EX_imm16),.imm26out(EX_imm26));

    /* EX */

    /* Redirect */
    redirect Redirect(.IR(EX_IR),.Din(WB_Din),.MEM_addr(MEM_addr),.Ori_EX_R1(Ori_EX_R1),.Ori_EX_R2(Ori_EX_R2),
                    .WB_RW(WB_RW),.MEM_RW(MEM_RW),.EX_RA(EX_RA),.EX_RB(EX_RB),.WB_RegWrite(WB_RegWrite),.MEM_RegWrite(MEM_RegWrite),
                    .EX_R1(EX_R1),.EX_R2(EX_R2));
                     
    /* ALU Module */
    ALU alu(.x(EX_R1),.y((EX_ALU_SRC==1)?EX_imm16:EX_R2),
            .shamt(EX_shamt),.alu_op(EX_ALUop),.result(EX_Result1),.result2(EX_Result2),.equal(EX_equal));    

    always@(*)begin
        case({EX_B||EX_JR,EX_JMP})
            2'b00: NewPC = 0;
            2'b01: begin NewPC = EX_PC+4; NewPC = {NewPC[31:28],EX_imm26,2'b00};end
            2'b10: NewPC = EX_PC + 4 + ( $signed(EX_imm16) << 2);
            2'b11: NewPC = EX_R1;
           endcase         
    end
    

                    
    /* EX/MEM */
    EX_MEM EXMEM(.clk(clk_dvid),.rst(reset),.en(HALT),.IRin(EX_IR),.PCin(EX_PC),
                .LBUin(EX_LBU),.MemToRegin(EX_MemToReg),.MemWritein(EX_MemWrite),.RegWritein(EX_RegWrite),.JALin(EX_JAL),.SYSCALLin(EX_SYSCALL),
                .Result1in(EX_Result1),.R1in(EX_R1),.R2in(EX_R2),.W_numin(EX_RW),
                .IRout(MEM_IR),.PCout(MEM_PC),
                .LBUout(MEM_LBU),.MemToRegout(MEM_MemToReg),.MemWriteout(MEM_MemWrite),.RegWriteout(MEM_RegWrite),.JALout(MEM_JAL),.SYSCALLout(MEM_SYSCALL),
                .Result1out(MEM_addr),.R1out(MEM_R1),.R2out(MEM_R2),.W_numout(MEM_RW));
    
  
    /* MEM */      
    /* ROM Module */
    reg[3:0]sel;
    always@(*)begin
        if(MEM_LBU==1)begin
            case(MEM_addr[1:0])
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
                 .A(MEM_addr[11:2]),
                 .inD(MEM_R2),
                 .sel(sel),
                 .str(MEM_MemWrite),
                 .clk(clk_dvid),
                 .outD(ROM_data),
                 .data_out(data_out));
                 
    /* MEM/WB */
    MEM_WB MEMWB(.clk(clk_dvid),.rst(reset),.en(HALT),.IRin(MEM_IR),.PCin(MEM_PC),
                .LBUin(MEM_LBU),.MemToRegin(MEM_MemToReg),.RegWritein(MEM_RegWrite),.JALin(MEM_JAL),.SYSCALLin(MEM_SYSCALL),
                .Result1in(MEM_addr),.Doutin(ROM_data),.R1in(MEM_R1),.R2in(MEM_R2),.W_numin(MEM_RW),
                .IRout(WB_IR),.PCout(WB_PC),
                .LBUout(WB_LBU),.MemToRegout(WB_MemToReg),.RegWriteout(WB_RegWrite),.JALout(WB_JAL),.SYSCALLout(WB_SYSCALL),
                .Result1out(WB_Result1),.Doutout(WB_Dout),.R1out(WB_R1),.R2out(WB_R2),.W_numout(WB_RW));

    /* WB */
    
    assign WB_Din = WB_JAL? (WB_PC + 4) : (WB_MemToReg ? WB_Dout : WB_Result1); 
    
    /* syscall */

    syscall Syscall(.data(WB_R1),
                    .syscall(WB_SYSCALL),
                    .go(go),
                    .show(showA0),
                    .halt(HALT));                    
    
    wire[31:0] totalCycle, numUncontrol, numControl, numLoaduse;
    /* Display */
    CycleDisplay cycleDisplay(.clk(clk_dvid),
                              .stop(HALT),
                              .rst(reset),
                              .jmp(EX_JMP),
                              .bjmp(EX_B_en),
                              .dependency(dependency),
                              .total_cycle(totalCycle),
                              .num_uncontrol(numUncontrol),
                              .num_control(numControl),
                              .num_loaduse(numLoaduse));
                              
    wire [31:0]segContent;
    display_change displayChange(.clk(clk_dvid),
                                 .showA0(showA0),
                                 .ledData(WB_R2),           //主显�?
                                 .total_cycle(totalCycle),       //总周期数
                                 .data_out(data_out),
                                 .LoadUse(numLoaduse),
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
    
endmodule
