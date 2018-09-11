.386
;宏定义
READ    MACRO  A  
		PUSH AX
		LEA   DX,  A           
		MOV  AH,  10           
		INT   21H   
		POP AX
		ENDM 
WRITE   MACRO  A   
		PUSH AX        
		LEA   DX, A           
		MOV  AH, 9           
		INT   21H   
		POP AX
		ENDM 
OUT1    MACRO   A  
		PUSH AX         
		MOV   DL,  A           
		MOV   AH,  2    
		INT    21H      
		POP AX
		ENDM 
CRLF    MACRO           
		OUT1   0AH                    
		OUT1   0DH           
		ENDM 		
STACK 	SEGMENT USE16 PARA STACK 'STACK'
		DB	300 DUP(0)
STACK 	ENDS
DATA 	SEGMENT USE16 PARA PUBLIC 'DATA'
	BNAME	DB  'L'XOR'2','X'XOR'3','R'XOR'7',7 DUP(0)  ;老板姓名（必须是自己名字的拼音）
	BPASS  	DB  ('2'-17H)*5,('3'-17H)*5,('7'-17H)*5,('5'-17H)*5,('4'-17H)*5,('3'-17H)*5,4 DUP(0)    ;密码
	N		EQU 3
	S1  	DB  'S'XOR'2','H'XOR'3','O'XOR'7','P'XOR '5','1'XOR '4',0           ;网店名称，用0结束
	GA1   	DB  'P'XOR'2','E'XOR'3','N'XOR'7', 7 DUP(0)  ; 商品名称
			DW  35 XOR'2',56 XOR'3',70 XOR '7',25 XOR '5',?  ;利润率还未计算
	GA2   	DB  'B'XOR'2','O'XOR'3','O'XOR'7','K'XOR'5', 6 DUP(0) ; 商品名称
			DW  12 XOR'2',30 XOR'3',25 XOR'7',5 XOR'5',?   ;利润率还未计算
	GA3		DB	'B'XOR'2','A'XOR'3','G'XOR'7', 7 DUP(0);
			DW	30 XOR'2',50 XOR'3',30 XOR'7',0 XOR'5',?
	S2 		DB  'S'XOR'2','H'XOR'3','O'XOR'7','P'XOR '5','2'XOR '4',0             
	GB1   	DB  'B'XOR'2','O'XOR'3','O'XOR'7','K'XOR'5', 6 DUP(0) ; 商品名称
			DW  12 XOR'2',28 XOR'3',20 XOR '7',15 XOR '5',?
	GB2   	DB  'P'XOR'2','E'XOR'3','N'XOR'7', 7 DUP(0)   ; 商品名称
			DW  35 XOR'2',50 XOR'3',30 XOR '7',24 XOR '5',?
	GB3		DB	'B'XOR'2','A'XOR'3','G'XOR'7', 7 DUP(0)
			DW  30 XOR'2',50 XOR'3',3000 XOR '7',0 XOR '5',?
	MSG1    DB  'Input the name (if enter q,exit!):$'
	MSG2	DB	'Input the password:$'
	MSG3	DB	'Input the name of commodity:$'
	MSG4	DB	'Login Success!$'
	MSG5	DB	'Login Fail!$'
	MSG6	DB  'Successful Search!$'
	MSG7	DB  'Unsuccessful Search!$'
	MSG8	DB  '0E1A';定义的冗余信息，扰乱视线
	MSG9	DB	'Error input!$'
	MSG10	DB	'0B23';定义的冗余信息，扰乱视线
	MSG11	DB	'This function is not completed!$'
	MENU1	DB	'----------------------------',0AH,'1=Search information',0AH,'2=Modify product information',0AH,'3=Calculate the APR',0AH,'4=Calculate the ranking',0AH,'5=Output all information',0AH,'6=Exit',0AH,'----------------------------',0AH,'$'
	MENU2	DB	'----------------------------',0AH,'1=Search information',0AH,'6=Exit',0AH,'----------------------------',0AH,'$'
	STR2	DB	'name=(sale price,stockr,sold)$'
	
	in_name DB  10
			DB ?
			DB 10 DUP(0)
    in_pwd  DB  10
			DB ?
			DB 10 DUP(0)
	in_shop DB  '125A'	;定义的冗余信息，扰乱视线
	in_goods DB  10
			DB ?
			DB 10 DUP(0)
	in_num	DB '02AF'	;定义的冗余信息，扰乱视线
	multi	DW 1,10,100,1000,10000
	
	AUSH	DB 0
	FLAG	DB 0
	JUDGE	DB 0
	FLAG_INPUT	DB 0
	G1	DW OVER
	G2	DW IN_OP_
	OLDINT1 DW  0,0               ;1号中断的原中断矢量（用于中断矢量表反跟踪）
	OLDINT3 DW  0,0               ;3号中断的原中断矢量
DATA 	ENDS
CODE 	SEGMENT USE16 PARA PUBLIC 'CODE'
		ASSUME CS:CODE,SS:STACK,DS:DATA	
START:  MOV	AX, DATA
        MOV DS, AX		
		XOR AX,AX					;接管调试用中断，中断矢量表反跟踪
		MOV ES,AX
		MOV AX,ES:[4]				;保存原1号和3号中断矢量
		MOV OLDINT1,AX
		MOV AX,ES:[6]
		MOV OLDINT1+2,AX
		MOV AX,ES:[12]
		MOV OLDINT3,AX
		MOV AX,ES:[14]
		MOV OLDINT3+2,AX
        CLI							;设置新的中断矢量
		MOV AX,OFFSET NEWINT
		MOV ES:[4],AX
		MOV ES:[6],CS
		MOV ES:[12],AX
		MOV ES:[14],CS
		STI		
		MOV FLAG_INPUT,0
INPUT:	
		CRLF
		WRITE MSG1
		READ in_name
		MOV BL,in_name+1
		MOV BH,0
		MOV BYTE PTR in_name+2[BX],'$'			
		CRLF					
		CMP BYTE PTR in_name+1,0H   ;仅输入回车符号，跳过功能二进入功能三
		JNE A
B:		MOV AUSH,0
		JMP  IN_OP
A:		CMP BYTE PTR in_name+1,1H   ;输入超过一个字符，跳过功能二进入功能三
		JNE INPUT2	
		CMP BYTE PTR in_name+2,71H	;输入 'q', 退出程序
        JNE INPUT2 	
		JMP G1
INPUT2: 
		WRITE MSG2		;输入密码，输出提示信息
		READ in_pwd      	; 读入密码
		MOV BL,in_pwd+1
		MOV BH,0
		MOV BYTE PTR in_pwd+2[BX],'$'	
		CRLF	
		CLI 				;计时反跟踪开始
		MOV AH,2CH
		INT 21H
		PUSH DX 	
CMP_NAME:
		LEA BP,BNAME	
		LEA BX,in_name+2
		MOV CL,in_name+1
		MOV CH,0	
		MOV SI,0	
		MOV JUDGE,0
		CALL CMP_
		CMP JUDGE,0
		JE LOGIN_FAIL
CMP_PWD:
		LEA BP,BPASS	
		LEA BX,in_pwd+2
		MOV CL,in_pwd+1
		MOV CH,0	
		MOV SI,0
		MOV DL,5   
CMP_1 : MOV AL,BYTE PTR DS:[BX+SI]
		MOVZX AX,AL
		SUB AX,17H
		MUL DL
		CMP BYTE PTR DS:[BP+SI],AL
		JNE	LOGIN_FAIL
		INC SI
		DEC CL
		JNZ CMP_1
		CMP BYTE PTR DS:[BP+SI],0
		JNE LOGIN_FAIL
LOGIN_SUCCESS:	
		MOV AH,2CH;获取第二次秒与百分秒
		INT 21H
		STI 
		CMP DX,[ESP]
		POP DX
		JNE OVER
		
		CLI					;堆栈检查反跟踪
		PUSH G2				;IN_OP_的地址压栈
		MOV AUSH,1
		WRITE MSG4      	;登陆成功，输出提示信息
		CRLF
		POP AX				
		MOV BX,[ESP-2]		;把栈顶上面的字（IN_OP_的地址）取到
		STI
		JMP BX				;如果被跟踪，将不会转移到IN_OP_
LOGIN_FAIL:		
		MOV AH,2CH			;获取第二次秒与百分秒
		INT 21H
		STI 
		CMP DX,[ESP]
		POP DX
		JNE OVER			
		WRITE MSG5      	;登录失败，输出提示信息
		INC FLAG_INPUT
		CMP FLAG_INPUT,3
		JNE INPUT
		CRLF
		JMP B	
IN_OP:
		WRITE MENU2       	;输出目录
		MOV AH,1H
		INT 21H
		CMP AL,36H
		JA WRONG
		CMP AL,35H
		JA OVER
		CMP AL,31H
		JA WRONG
		CMP AL,30H
		JA OP_1		
WRONG:
		CRLF
		WRITE MSG9       	;输出错误提示
		CRLF
		JMP IN_OP
IN_OP_:
		WRITE MENU1
		MOV AH,1H
		INT 21H
		CMP AL,36H
		JA WRONG_
		CMP AL,35H
		JA OVER
		CMP AL,34H
		JA OP_5
		CMP AL,33H
		JA OP_4
		CMP AL,32H
		JA OP_3
		CMP AL,31H
		JA OP_2
		CMP AL,30H
		JA OP_1
WRONG_:
		CRLF
		WRITE MSG9       	;输出错误提示
		CRLF
		JMP G2
OP_1:
		CRLF
		WRITE MSG3      	;输入商品名称，输出提示信息			
		READ in_goods    	;读入商品名称
		CRLF
		
		MOV JUDGE,1
		CALL SEARCH
		CMP JUDGE,0
		JE OP_1
		JMP RETURN
OP_2:		
		DB  '00EA'            ;定义的冗余信息，扰乱视线
OP_3:
		DB  '00AF'            ;定义的冗余信息，扰乱视线
OP_4:
		DB  '00AD'            ;定义的冗余信息，扰乱视线
OP_5:
		DB  '52AB'            ;定义的冗余信息，扰乱视线		
		CRLF
		WRITE MSG11
		CRLF
		JMP RETURN
RETURN:
		CMP AUSH,0
		JE IN_OP
		JNE IN_OP_	
;子模块 CMP_
	;功能：对比字符串
	;入口参数：BX-字符串基址
	;		   BP-字符串基址
	;出口参数：JUDGE=1，相同；JUDGE=0，不同。
CMP_ PROC NEAR
		MOV DL,BYTE PTR DS:[BX+SI]
		XOR DL,BYTE PTR	in_pwd+2[SI]
		CMP BYTE PTR DS:[BP+SI],DL
		JNE	CMP_FAIL
		INC SI
		DEC CL
		JNZ CMP_
		CMP BYTE PTR DS:[BP+SI],0
		JNE CMP_FAIL
		MOV JUDGE,1
		RET
CMP_FAIL:
		MOV JUDGE,0
		RET
CMP_ ENDP

;子模块 SEARCH
	;功能一：查询商品信息
	;入口参数：无
	;出口参数：无	
SEARCH PROC NEAR
		MOV BL,in_goods+1
		MOV BH,0
		MOV BYTE PTR in_goods+2[BX],'$'			
		CMP BYTE PTR in_goods+1,0H   ;仅输入回车符号，返回功能一
		JE  END_SEARCH	
		
		LEA BP,GA1
		MOV FLAG,0
LOOPF:
		MOV CH,N
		LEA BX,in_goods+2
LOOPC:		
		MOV SI,0
		MOV CL,in_goods+1
	
		CALL CMP_
		CMP JUDGE,0
		JE LOOPB
		
		CMP FLAG,0
		JE SEARCH_SUCCESS
		JNE IN_SHOP2
LOOPB:
		DEC CH
		JZ WRONG_SEARCH
		ADD BP,20
		JMP LOOPC
		
		      	
SEARCH_SUCCESS:
		WRITE MSG6      	;查找成功，输出提示信息,且BP为字符串首地址
		CRLF
		
		PUSH BP
		LEA BP,S1
		CALL PRINTF_NAME
		POP BP
		JMP IN_SHOP1
IN_SHOP2:
		PUSH BP
		LEA BP,S2
		CALL PRINTF_NAME
		POP BP
IN_SHOP1:
		CRLF	
		CALL OUT_INFO
		
		CMP FLAG,1
		JE END_SEARCH
		
		CRLF
		LEA BP,GB1
		MOV FLAG,1
		JMP LOOPF
WRONG_SEARCH:		;查找失败，输出提示信息
		MOV JUDGE,0
		WRITE MSG7
		RET
END_SEARCH:	
		MOV JUDGE,1
		RET
SEARCH ENDP
;子模块 PRINTF
	;功能：以十进制形式输出AX中的值
	;入口参数：AX-要输出的值
	;出口参数：无
PRINTF 	PROC NEAR     
		PUSH SI
		PUSH DI
		PUSH CX
		TEST AX,8000H
		JE PRIN    ;正数
		PUSH AX
		MOV DL,2DH     ;输出'-'
		MOV AH,2
		INT 21H
		POP AX
		SUB AX,1
		NOT AX
PRIN:	MOV  SI,10
		XOR  CX,CX
NEXT:	
		MOV  DX,0
		DIV  SI
		PUSH  DX
		INC  CX
		CMP  AX,0	;商为0则完成转换
		JNZ  NEXT
OUTP:	
		POP  DX
		ADD  DL,30H
		MOV  AH,2
		INT  21H
		LOOP OUTP 
		POP CX
		POP DI
		POP SI
		RET
PRINTF  ENDP
;子模块 PRINTF_NAME
	;功能：输出商品的名称
	;入口参数：BP-商品偏移地址
	;出口参数：无
PRINTF_NAME PROC NEAR
		PUSH SI
		PUSH AX
		
		MOV SI,0
W1_1:	MOV DL,DS:[BP+SI]
		CMP DL,0
		JE PRINTF_NAME_END
		XOR DL,in_pwd+2[SI]
		MOV AH,2
		INT 21H
		INC SI
		JMP W1_1		
PRINTF_NAME_END:
		POP AX
		POP SI
		RET
PRINTF_NAME  ENDP
;子模块 OUT_INFO
	;功能：输出商品相关信息
	;入口参数：BP-商品偏移地址
	;出口参数：无
OUT_INFO PROC NEAR
CON1:
		WRITE STR2
		CRLF
		CALL PRINTF_NAME
		OUT1 '='
		OUT1 '('
		MOV SI,12
		MOV DI,3
LOOPO:		
        MOV AX,WORD PTR DS:[BP+SI]		
		MOV BL,BYTE PTR in_pwd+[DI]
		MOVZX BX,BL
		XOR AX,BX		
		CALL PRINTF
		ADD SI,2
		INC DI

		CMP SI,18
		JE END_OUT_INFO
CON2:
		OUT1 ','
		JMP LOOPO
END_OUT_INFO:
		OUT1 ')'
		CRLF
		RET
OUT_INFO ENDP
NEWINT: IRET
OVER:   CLI
		MOV AX,OLDINT1				;还原原1号和3号中断矢量
		MOV ES:[4],AX				
		MOV AX,OLDINT1+2
		MOV ES:[6],AX
		MOV AX,OLDINT3
		MOV ES:[12],AX
		MOV AX,OLDINT3+2
		MOV ES:[14],AX
		STI
		MOV AH, 4CH
        INT 21H		
CODE    ENDS
        END     START