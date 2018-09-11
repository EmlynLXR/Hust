.386
READ    MACRO  A  ;10号调用宏定义
		PUSH AX
		LEA   DX,  A           
		MOV  AH,  10           
		INT   21H   
		POP AX
		ENDM 
WRITE   MACRO  A   ;9号调用宏定义
		PUSH AX        
		LEA   DX, A           
		MOV  AH, 9           
		INT   21H   
		POP AX
		ENDM 
OUT1    MACRO   A  ;2号调用宏定义
		PUSH AX         
		MOV   DL,  A           
		MOV   AH,  2    
		INT    21H      
		POP AX
		ENDM 
STACK  SEGMENT USE16 STACK 
       DB 200 DUP(0)
STACK  ENDS
DATA   SEGMENT USE16
BNAME 	DB  'CHEN SHUTING'  ;老板姓名（必须是自己名字的拼音）
LEN1	EQU $-BNAME
BPASS 	DB  'test'    ;密码
LEN2	EQU $-BPASS
N   	EQU   4
S1 		DB  'SHOP1',0           ;网店名称，用0结束
GA1  	DB  'PEN',7 DUP(0)  ; 商品名称
		DW  35,56,70,25,?  ;利润率还未计算
GA2  	DB  'BOOK', 6 DUP(0) ; 商品名称
		DW  12,30,25,5,?   ;利润率还未计算
GA3		DB	'BAG', 7 DUP(0);
		DW	30,50,3000,0,?
GAN 	DB  N-3 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?) ;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
S2 		DB  'SHOP2',0           ;网店名称，用0结束
GB1  	DB  'BOOK', 6 DUP(0) ; 商品名称
		DW 	12,28,20,15,?   ;利润率还未计算
GB2     DB  'PEN', 7 DUP(0)  ; 商品名称
		DW  35,50,30,24,?  ;利润率还未计算
GB3		DB	'BAG', 7 DUP(0);
		DW	32,48,100,0,?
GBN 	DB	N-3 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?) ;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
MSG1    DB	0AH,0DH,'Plese input your name!$'
MSG2    DB 	0AH,0DH,'Plese input your password!$'
MSG3	DB 	0AH,0DH,'Plese reenter your name and password!$'
MSG4	DB 	0AH,0DH,'Plese input the trade name!$'
MSG5	DB 	0AH,0DH,'Fail to find!$'
MSG6	DB 	0AH,0DH,'Level:$'
MSG7	DB	0AH,0DH,'Please input the shop name!$'
MSG8	DB	0AH,0DH,'Error input!$'
MSG9	DB	0AH,0DH,'Press any key to continue!$'
STR1	DB	0AH,0DH,'name=(stock price,sale price,stock number,sale number,profit margins)$'
STR2	DB	0AH,0DH,'name=(stock price,sale price,stock number,sale number,profit rank)$'
STR3	DB	0AH,0DH,'name:$'
STR4	DB	0AH,0DH,'sale price:$'
STR5	DB	0AH,0DH,'stock number:$'
STR6	DB	0AH,0DH,'sale number:$'
STR7	DB	0AH,0DH,'stock price:$'
MSHOP1	DB	0AH,0DH,'SHOP1$'
MSHOP2	DB	0AH,0DH,'SHOP2$'
MMM		DB 	0AH,0DH,'CLOSE$'
CRLF	DB 	0DH,0AH,'$'
MENU1	DB	'----------------------------',0AH,'1=Search information',0AH,'2=Modify product information',0AH,'3=Calculate the APR',0AH,'4=Calculate the ranking',0AH,'5=Output all information',0AH,'6=Exit',0AH,'----------------------------',0AH,'$'
MENU2	DB	'----------------------------',0AH,'1=Search information',0AH,'6=Exit',0AH,'----------------------------',0AH,'$'
PR1		DW	?
PR2		DW	?
APR		DW 	?
in_name	DB 20
		DB ?
		DB 20 DUP(0)
in_pwd	DB 20
		DB ?
		DB 20 DUP(0)
in_good	DB 20
		DB ?
		DB 20 DUP(0)
in_shop	DB 20
		DB ?
		DB 20 DUP(0)
in_num	DB 6
		DB ?
		DB 6 DUP(0)
PM		DB N DUP(0)
multi	DW 1,10,100,1000,10000
AUTH    DB ?
FLAG	DB 0
DATA   ENDS
CODE   SEGMENT USE16
ASSUME CS:CODE,DS:DATA,SS:STACK
START:	MOV AX,DATA
		MOV DS,AX
ONE:	WRITE MSG1    ;提示输入用户名
		READ in_name    ;输入用户名
		WRITE CRLF
		MOV AH,in_name+2   ;若在输入姓名时仅仅输入字符q，则程序退出
		CMP AH,'q'
		JE EXIT
		CMP AH,0DH     ;若输入姓名时只是输入了回车，则将0送到AUTH字节变量中，跳过功能二，进入功能三
		JE A
		WRITE MSG2     ;提示输入密码
		READ in_pwd    ;输入密码
		WRITE CRLF      ;回车、换行
TWO:	MOV AL,in_name+1   ;判断用户名是否等长
		CMP AL,LEN1
		JNE B             ;用户名不对，提示登录失败，并回到功能一
		LEA SI,BNAME
		LEA DI,in_name+2
		MOV BX,0
CMPN:	MOV AL,[SI]    ;循环比较用户名串每一个字符
		CMP AL,[DI]
		JNE B         ;用户名不对，提示登录失败，并回到功能一
		INC SI
		INC DI
		INC BX
		CMP BX,LEN1-1
		JNE CMPN
		
		MOV AL,in_pwd+1    ;用户名正确，判断密码是否等长
		CMP AL,LEN2
		JNE B               ;密码不对，提示登录失败，并回到功能一
		LEA SI,BPASS
		LEA DI,in_pwd+2
		MOV BX,0
CMPP:	MOV AL,[SI]     ;循环比较密码串每一个字符
		CMP AL,[DI]
		JNE B            ;密码不对，提示登录失败，并回到功能一
		INC SI
		INC DI
		INC BX
		CMP BX,LEN2-1
		JNE CMPP
		MOV AUTH,1         ;用户名和密码正确，进入功能三
THREE:	MOV AH,AUTH
		CMP AH,0
		JE MEN2
		WRITE MENU1     ;登陆成功，输出目录
		MOV AH,1H
		INT 21H
		CMP AL,36H      ;大于6
		JA H
		CMP AL,35H     ;为6
		JA EXIT
		CMP AL,34H
		JA T5
		CMP AL,33H
		JA T4
		CMP AL,32H
		JA T3
		CMP AL,31H
		JA T2
		CMP AL,30H
		JA T1
		JMP H
MEN2:	WRITE MENU2       	;登陆失败，输出目录
		MOV AH,1H
		INT 21H
		CMP AL,36H
		JA H
		CMP AL,35H
		JA EXIT
		CMP AL,31H
		JA H
		CMP AL,30H
		JA T1	
		JMP H


T4:		LEA BP,PM
		LEA SI,S2+6
		MOV DI,SI
		MOV CX,0    ;外循环计数器
		MOV BH,0    ;内循环计数器
		MOV BL,1    ;排名	
T41:	PUSH AX
		PUSH BX
		MOV AX,WORD PTR[SI+18]
		MOV BX,WORD PTR[DI+18]
		TEST AX,8000H
		JE T4A    ;A正数
		TEST BX,8000H
		JNE T4B    ;A负数B负数
		POP BX
		POP AX
		JMP T4C    ;A负数B正数
T4A:	TEST BX,8000H
		JNE T4A1    ;A正数B负数
		CMP AX,BX   ;A正数B正数
		JA AD
		POP BX
		POP AX
		JMP T4C
T4A1:	JMP AD	
T4B:	CMP AX,BX
		JA AD
		POP BX
		POP AX
		JMP T4C
T4C:	INC BH
		CMP BH,N
		JE T42    ;当前商品统计完毕
		ADD DI,20
		JMP T41     ;和下一商品比较
T42:	PUSH SI
		MOV SI,CX
		MOV [BP+SI],BL   ;保存排名于数组
		POP SI
		INC CX
		MOV BH,0
		MOV BL,1
		CMP CX,N
		JE T43        ;全部商品统计完毕
		ADD SI,20
		LEA DI,S2+6
		JMP T41
AD:		POP BX
		POP AX
		INC BL
		JMP T4C
T43:	LEA SI,S2+6   ;录入排名
		MOV CX,0
T43_:	MOV BYTE PTR[SI+19],0
		PUSH SI
		MOV SI,CX
		MOV BL,[BP+SI]
		POP SI
		MOV [SI+18],BL
		INC CX
		CMP CX,N
		JE I
		ADD SI,20
		JMP T43_

	

		
T1:		WRITE MSG4
		READ in_good
		LEA SI,S1+6
		LEA DI,in_good+2
		MOV DX,[DI]
		CMP DX,0DH
		JE THREE
		MOV AL,in_good+1
		MOV BL,0     ;计数器
T11:	CALL COMP
		MOV AH,FLAG
		CMP AH,1     
		JE T12        ;在商店1找到商品，去输出信息
		INC BL
		CMP BL,N
		JE G1            ;找不到该网店，重新输入商品名
		ADD SI,14H
		JMP T11
T15:	LEA SI,S2+6     ;在商店2查找
		LEA DI,in_good+2
		MOV AL,in_good+1
		MOV BL,0
T13:	CALL COMP
		MOV AH,FLAG
		CMP AH,1     
		JE T14        ;在商店2找到商品，去输出信息
		CMP BL,N
		JE G1            ;找不到该网店，重新输入商品名
		ADD SI,14H
		JMP T13	
T12:	WRITE MSHOP1
		WRITE STR3
		CALL WRITE1
		WRITE STR4
		MOV AX,WORD PTR[SI+12]
		CALL PRINTF
		WRITE STR5
		MOV AX,WORD PTR[SI+14]
		CALL PRINTF
		WRITE STR6
		MOV AX,WORD PTR[SI+16]
		CALL PRINTF
		JMP T15
T14:	WRITE MSHOP2
		WRITE STR3
		CALL WRITE1
		WRITE STR4
		MOV AX,WORD PTR[SI+12]
		CALL PRINTF
		WRITE STR5
		MOV AX,WORD PTR[SI+14]
		CALL PRINTF
		WRITE STR6
		MOV AX,WORD PTR[SI+16]
		CALL PRINTF
		JMP I
		
T2:		WRITE MSG7      ;提示输入商店名
		READ in_shop    ;输入商店名
		WRITE CRLF 
		MOV AH,in_shop+2    ;若只输入回车，则回到功能三目录
		CMP AH,0DH
		JE THREE
		
		LEA SI,S1
		LEA DI,in_shop+2
		MOV AL,in_shop+1
		CALL COMP
		MOV AH,FLAG
		CMP AH,1
		JE T21        ;找到网店，去查找商品
		LEA SI,S2
		CALL COMP
		MOV AH,FLAG
		CMP AH,1
		JNE G       ;找不到该网店，重新输入商店名
T21:	WRITE MSG4      ;提示输入商品名
		READ in_good      ;输入商品名
		WRITE CRLF     ;回车、换行
		MOV AH,in_good+2    ;若只输入回车，则回到功能三目录
		CMP AH,0DH
		JE THREE
		ADD SI,6
		LEA DI,in_good+2   
		MOV AL,in_good+1
		MOV BL,0
T22:	CALL COMP
		MOV AH,FLAG
		CMP AH,1
		JE T23
		INC BL
		CMP BL,N
		JE G            ;找不到该网店，重新输入商店名
		ADD SI,14H
		JMP T22
T23:	WRITE STR7
		MOV AX,WORD PTR[SI+10]
		CALL PRINTF
		OUT1 '>'
		READ in_num				   	;读入数值
		MOV BL,in_num+1
		MOV BH,0
		MOV BYTE PTR in_num+2[BX],'$'			
		CMP BYTE PTR in_num+1,0   ;仅输入回车符号，不进行修改
		JE T24
		CALL STR_NUM
		CMP FLAG,0
		JE T23
		MOV WORD PTR [SI+10],AX
T24:	WRITE STR4
		MOV AX,WORD PTR[SI+12]
		CALL PRINTF
		OUT1 '>'
		READ in_num				   	;读入数值
		MOV BL,in_num+1
		MOV BH,0
		MOV BYTE PTR in_num+2[BX],'$'			
		CMP BYTE PTR in_num+1,0   ;仅输入回车符号，不进行修改
		JE T25
		CALL STR_NUM
		CMP FLAG,0
		JE T24
		MOV WORD PTR [SI+12],AX	
T25:	WRITE STR5
		MOV AX,WORD PTR[SI+14]
		CALL PRINTF
		OUT1 '>'
		READ in_num				   	;读入数值
		MOV BL,in_num+1
		MOV BH,0
		MOV BYTE PTR in_num+2[BX],'$'			
		CMP BYTE PTR in_num+1,0   ;仅输入回车符号，不进行修改
		JE THREE
		CALL STR_NUM
		CMP FLAG,0
		JE T25
		MOV WORD PTR [SI+14],AX
		WRITE CRLF
		JMP I			
		
T3:		CALL RELODE
		JMP I	


		
		
T5:		WRITE MSHOP1       ;输出网店1信息
		WRITE STR1
		OUT1 0AH
		OUT1 0DH
		MOV CL,N
		LEA SI,S1+6
T51:	CALL WRITE1 
		OUT1 '='
		OUT1 '('
		MOV AX,WORD PTR[SI+10]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+12]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+14]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+16]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+18]
		CALL PRINTF
		OUT1 ')'
		OUT1 0AH
		OUT1 0DH
		DEC CL
		JZ T52
		ADD SI,20
		JMP T51
T52:	WRITE MSHOP2           ;输出网店2信息
		WRITE STR2
		OUT1 0AH
		OUT1 0DH
		MOV CL,N
		LEA SI,S2+6
T53:	CALL WRITE1 
		OUT1 '='
		OUT1 '('
		MOV AX,WORD PTR[SI+10]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+12]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+14]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+16]
		CALL PRINTF
		OUT1 ','
		MOV AX,WORD PTR[SI+18]
		CALL PRINTF
		OUT1 ')'
		OUT1 0AH
		OUT1 0DH
		DEC CL
		JZ I         ;全部输出完毕，回到功能三目录
		ADD SI,20
		JMP T53

		
		
RELODE	PROC
		PUSH SI
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		LEA SI,S1+6
		LEA DI,S2+6
		CALL PR      ;计算商店1中该商品利润率
		MOV CX,0       ;商店1计数器
		MOV AH,0      ;商店2计数器
		MOV DX,APR
		MOV PR1,DX
		MOV WORD PTR [SI+12H],DX
		PUSH SI
		PUSH DI	
FIND1:	MOV AL,[SI]      ;循环比较GA2名称每一个字符
		CMP AL,[DI]
		JNE FIND2      ;名字不同，比较下一商品
		CMP BYTE PTR[DI],0     ;比完最后一个字符，计算商店2中该商品利润率
		JE YES
		INC SI
		INC DI
		JMP FIND1
FIND2:	POP DI
		POP SI
		PUSH SI
		INC AH
		CMP AH,N     ;找不到该商品
		JE E
		ADD DI,14H 
		PUSH DI
		JMP FIND1        ;找商店2的下一个商品
FIND3:	PUSH AX
		MOV BX,PR1       ;计算APR
		MOV AX,PR2
		ADD AX,BX     
		CWD           ;将AX中符号扩展至DX中
		MOV BX,2
		IDIV BX        ;有符号字除法
		MOV APR,AX
		MOV DX,APR
		MOV WORD PTR[SI+12H],DX
		MOV WORD PTR[DI+12H],DX
		POP AX
		INC CX
		CMP CX,N   ;全部商品利润率更新完毕，返回
		JE RT
		ADD SI,14H
		CALL PR      ;计算商店1中下一商品利润率
		MOV DX,APR
		MOV PR1,DX
		MOV WORD PTR [SI+12H],DX
		LEA DI,S2+6
		PUSH SI
		PUSH DI
		MOV AH,0
		JMP FIND1
YES:	POP SI
		CALL PR
		MOV DI,SI
		POP SI
		MOV DX,APR
		MOV PR2,DX
		MOV WORD PTR [DI+12H],DX
		JMP FIND3
RT:		POP DX
		POP CX
		POP BX
		POP AX
		POP SI
		RET
RELODE 	ENDP		
		
		
		
		
COMP	PROC
		PUSH SI
		PUSH DI
		PUSH AX
		MOV FLAG,0
COMP_1:	MOV AH,[SI]     
		CMP AH,[DI]
		JNE RETURN
		INC SI
		INC DI
		DEC AL
		JNZ COMP_1
		CMP BYTE PTR DS:[SI],0
		JNE RETURN
		;CMP BYTE PTR DS:[DI],0
		;JNE RETURN
		MOV FLAG,1
RETURN:	POP AX
		POP DI
		POP SI
		RET
COMP	ENDP	
		
WRITE1 	PROC    ;SI,输出字符串，到0停止
		PUSH SI
		PUSH AX
		PUSH DX
W1_1:	MOV DL,[SI]
		CMP DL,0
		JE W1_END
		MOV AH,2
		INT 21H
		INC SI
		JMP W1_1
W1_END:	POP DX
		POP AX
		POP SI
		RET
WRITE1	ENDP	


PRINTF 	PROC NEAR        ;输出AX的数值
		PUSH SI
		PUSH DI
		PUSH CX
		TEST AX,8000H
		JE PRIN    ;正数
		OUT1 2DH     ;输出'-'
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
	
	
	
;将in_num中的字符串转化为数字存入到AX中,BX、SI、DI被保护
STR_NUM PROC NEAR
		PUSH SI
		PUSH DI
		PUSH BX
		MOV FLAG,1
		MOV EBX,0
		MOV CL,BYTE PTR in_num+1
		MOV CH,0
		MOV SI,0
		MOV DI,CX
		MOVZX EDI,DI
LOOPH:		
		MOVZX EAX,BYTE PTR in_num+2[SI]
		
		CMP EAX,30H
		JB WRONG_CHANGE
		CMP EAX,39H
		JA WRONG_CHANGE
		
		SUB EAX,30H
		
		MOVZX EDX,WORD PTR multi+[EDI*2-2]
		MUL EDX
		ADD EBX,EAX
		
		DEC EDI
		INC SI
		CMP EDI,0
		JNE LOOPH
		
		MOV EAX,EBX		
		JMP END_CHANGE
WRONG_CHANGE:
		MOV FLAG,0
END_CHANGE:
		POP BX
		POP DI
		POP SI
		RET
STR_NUM ENDP


PR		PROC
		PUSH SI
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		CMP AUTH,0      ;若是未登录状态，则只在下一行显示该商品的名称，然后回到功能一
		JE D   
		MOV AL,[SI+0CH]    ;若已登录，计算PR1
		MOV AH,[SI+0DH]
		MOV BL,[SI+10H]
		MOV BH,[SI+11H]
		IMUL AX,BX
		MOV CL,[SI+0AH]
		MOV CH,[SI+0BH]
		MOV DL,[SI+0EH]
		MOV DH,[SI+0FH]
		IMUL CX,DX
		SUB AX,CX
		MOV BX,100     
		IMUL BX        ;有符号字乘法
		IDIV CX        ;有符号字除法
		MOV APR,AX        ;保存PR1
		MOV [SI+12H],AL
		MOV [SI+13H],AH
		POP DX
		POP CX
		POP BX
		POP AX
		POP SI
		RET
PR		ENDP	



A:		MOV AUTH,0
		JMP THREE	
B:		WRITE MSG3
		JMP ONE
D:		MOV DL,[BX]
		CMP DL,0
		JE ONE
		MOV AH,2
		INT 21H
		INC BX
		JMP D
E:		WRITE MSG5
		JMP THREE
F:		JMP ONE
G:		WRITE MSG5
		JMP T2
G1:		WRITE MSG5
		JMP T1
H:		WRITE MSG8
		JMP THREE
I:		WRITE MSG9   ;输入任意字符继续
		MOV AH,1         
		INT 21H
		JMP THREE
EXIT:	WRITE MMM
		MOV AH,4CH
		INT 21H    
CODE   ENDS
       END START


;16277