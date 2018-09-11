;编写者：同组同学：
		EXTRN FUN3:FAR,FUN4:FAR,FUN5:FAR,PRINTF:FAR
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
CRLF     MACRO           
		OUT1   0AH                    
		OUT1   0DH           
		ENDM 		
STACK 	SEGMENT USE16 PARA STACK 'STACK'
		DB	300 DUP(0)
STACK 	ENDS
DATA 	SEGMENT USE16 PARA PUBLIC 'DATA'
	BNAME	DB  'LXR',7 DUP(0)  ;老板姓名（必须是自己名字的拼音）
	BPASS  	DB  '2333',6 DUP(0)    ;密码
	N		EQU 4
	S1  	DB  'SHOP1',0           ;网店名称，用0结束
	GA1   	DB  'PEN', 7 DUP(0)  ; 商品名称
			DW  35,56,70,25,?  ;利润率还未计算
	GA2   	DB  'BOOK', 6 DUP(0) ; 商品名称
			DW  12,30,25,5,?   ;利润率还未计算
	GA3		DB	'BAG', 7 DUP(0);
			DW	30,50,30,0,?
	GAN   	DB  N-2 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?) ;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
	
	S2 		DB  'SHOP2',0           ;网店名称，用0结束
	GB1   	DB  'BOOK', 6 DUP(0) ; 商品名称
			DW  12,28,20,15,?   ;利润率还未计算
	GB2   	DB  'PEN', 7 DUP(0)  ; 商品名称
			DW  35,50,30,24,?  ;利润率还未计算
	GB3		DB	'BAG', 7 DUP(0);
			DW	30,50,3000,0,?
			DB  N-2 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?)			;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
	MSG1    DB  'Input the name (if enter q,exit!):$'
	MSG2	DB	'Input the password:$'
	MSG3	DB	'Input the name of commodity:$'
	MSG4	DB	'Login Success!$'
	MSG5	DB	'Login Fail!$'
	MSG6	DB  'Successful Search!$'
	MSG7	DB  'Unsuccessful Search!$'
	MSG8	DB  'You have no access!$'
	MSG9	DB	'Error input!$'
	MSG10	DB	'Input the name of shop:$'
	MENU1	DB	'----------------------------',0AH,'1=Search information',0AH,'2=Modify product information',0AH,'3=Calculate the APR',0AH,'4=Calculate the ranking',0AH,'5=Output all information',0AH,'6=Exit',0AH,'----------------------------',0AH,'$'
	MENU2	DB	'----------------------------',0AH,'1=Search information',0AH,'6=Exit',0AH,'----------------------------',0AH,'$'
	STR1	DB	'name=$      ','sale price=$','stock=$     ','sold=$      '
	STR2	DB	'name=(sale price,stockr,sold)$'
	STR3	DB	'name=(sale price,stockr,sold,profit rank)$'
	STR4	DB	'name=(sale price,stockr,sold,profit margins)$'
	
	in_name DB  10
			DB ?
			DB 10 DUP(0)
    in_pwd  DB  10
			DB ?
			DB 10 DUP(0)
	in_shop DB  10
			DB ?
			DB 10 DUP(0)
	in_goods DB  10
			DB ?
			DB 10 DUP(0)
	in_num	DB 6
			DB ?
			DB 6 DUP(0)
	multi	DW 1,10,100,1000,10000
	
	AUSH	DB 0
	PR1		DW 0
	PR2		DW 0
	APR 	DW 0
	FLAG	DB 0
	FLAG_INFO DB 0
	JUDGE	DB 0
DATA 	ENDS

CODE 	SEGMENT USE16 PARA PUBLIC 'CODE'
		ASSUME CS:CODE,SS:STACK,DS:DATA	
START:  MOV	AX, DATA
        MOV DS, AX	
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
		MOV AUSH,0
		JMP  IN_OP
A:		CMP BYTE PTR in_name+1,1H   ;输入超过一个字符，跳过功能二进入功能三
		JNE INPUT2	
		CMP BYTE PTR in_name+2,71H	;输入 'q', 退出程序
        JE 	OVER

INPUT2: 
		WRITE MSG2		;输入密码，输出提示信息
		READ in_pwd      	; 读入密码
		MOV BL,in_pwd+1
		MOV BH,0
		MOV BYTE PTR in_pwd+2[BX],'$'	
		CRLF		
		
CMP_NAME:
		LEA BP,BNAME	
		LEA BX,in_name+2
		MOV CL,in_name+1
		MOV CH,0
		MOV FLAG,0
		JMP CMP_1
CMP_PWD:
		LEA BP,BPASS	
		LEA BX,in_pwd+2
		MOV CL,in_pwd+1
		MOV CH,0	
		MOV FLAG,1
		JMP CMP_1		
CMP_1:
		MOV SI,0
		CALL CMP_
		CMP JUDGE,0
		JE LOGIN_FAIL
		
		CMP FLAG,0
		JE CMP_PWD
		CMP FLAG,1
		JE LOGIN_SUCCESS
LOGIN_SUCCESS:		
		MOV AUSH,1
		WRITE MSG4      	;登陆成功，输出提示信息
		CRLF
		JMP IN_OP_
LOGIN_FAIL:
		WRITE MSG5      	;登录失败，输出提示信息
		JMP INPUT		
		
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
		JMP IN_OP_
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
		CRLF
		WRITE MSG10      	;输入商店名称，输出提示信息			
		READ in_shop    	;读入商店名称
		CRLF
		WRITE MSG3      	;输入商品名称，输出提示信息			
		READ in_goods    	;读入商品名称
		CRLF
		
		MOV JUDGE,1
		CALL MODIFY
		CMP JUDGE,0
		JE OP_2
		JMP RETURN		
OP_3:
		LEA BP,S2
		LEA BX,S1
		CALL FUN3
		JMP RETURN
OP_4:
		LEA DX,S2
		CALL FUN4
		JMP RETURN
OP_5:
		CRLF
		LEA BP,S2
		LEA BX,S1
		CALL FUN5
		JMP RETURN
RETURN:
		CMP AUSH,0
		JE IN_OP
		JNE IN_OP_
		
;子模块 CMP_
	;功能一：查询商品信息
	;入口参数：无
	;出口参数：无
CMP_ PROC NEAR
		MOV DL,BYTE PTR DS:[BP+SI]
		CMP BYTE PTR DS:[BX+SI],DL
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
		MOV FLAG_INFO,1
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

;子模块 MODIFY
	;功能二：修改商品信息
	;入口参数：无
	;出口参数：无
MODIFY PROC NEAR
		MOV BL,in_shop+1
		MOV BH,0
		MOV BYTE PTR in_shop+2[BX],'$'			
		CMP BYTE PTR in_shop+1,0H   ;仅输入回车符号，跳过功能二进入功能三
		JE END_MODIFY
		
		LEA BX,in_shop+2			;寻找商店
		LEA BP,S1
		MOV SI,0
		MOV FLAG,1
		JMP LOOPG
_2:
		LEA BP,S2
		MOV SI,0
		MOV FLAG,2
		JMP LOOPG
SHOP_FAIL:
		CMP FLAG,1
		JE _2
		JNE WRONG_MODIFY
LOOPG:
		MOV DL,BYTE PTR DS:[BP+SI]
		CMP BYTE PTR DS:[BX+SI],DL
		JNE	SHOP_FAIL
		INC SI
		CMP SI,5
		JNE LOOPG
			
		MOV BL,in_goods+1			
		MOV BH,0
		MOV BYTE PTR in_goods+2[BX],'$'			

		MOV CH,N				;寻找商品
		LEA BX,in_goods+2
		
		CMP	FLAG,1
		JE _1
		LEA BP,GB1	
_1:
		LEA BP,GA1
LOOPCC:		
		MOV SI,0
		MOV CL,in_goods+1
		
		CALL CMP_
		CMP JUDGE,1
		JE MODIFY_SUCCESS
LOOPBB:
		DEC CH
		JZ WRONG_MODIFY
		ADD BP,20
		JMP LOOPCC
		
MODIFY_SUCCESS:
		WRITE MSG6      	;查找成功，输出提示信息,且BP为字符串首地址
		
		LEA DI,STR1
		MOV SI,12
		ADD DI,12
LOOPOO:	
		CRLF
		WRITE [DI]
        MOV  AX,WORD PTR DS:[BP+SI]
		CALL PRINTF

		OUT1 2FH					;输出'/'
		WRITE [DI]
		READ in_num				   	;读入数值
		MOV BL,in_num+1
		MOV BH,0
		MOV BYTE PTR in_num+2[BX],'$'			
		CMP BYTE PTR in_num+1,0H   ;仅输入回车符号，不进行修改
		JE CONTI
		
		MOV JUDGE,1
		CALL STR_NUM
		CMP JUDGE,0
		JE LOOPOO
		
		MOV WORD PTR DS:[BP+SI],AX
		CRLF
		WRITE [DI]
		CALL PRINTF
CONTI:		
		ADD DI,12
		ADD SI,2
		CMP SI,18
		JNE LOOPOO
		JMP END_MODIFY
WRONG_MODIFY:
		MOV JUDGE,0
		WRITE MSG7      	;查找失败，输出提示信息	
		RET
END_MODIFY:	
		MOV JUDGE,1
		CRLF
		RET	
MODIFY ENDP

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
		MOV AH,2
		INT 21H
		INC SI
		JMP W1_1		
PRINTF_NAME_END:
		POP AX
		POP SI
		RET
PRINTF_NAME  ENDP
;子模块 STR_NUM
	;功能：将in_num中的字符串转化为数字存入到AX中,BX、SI、DI被保护
	;入口参数：无
	;出口参数：JUDGE-标志是否转化成功，JUDGE=1时转化成功，JUDGE=0时转化失败
STR_NUM PROC NEAR
		PUSH SI
		PUSH DI
		PUSH BX
				
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
		MOV JUDGE,0
END_CHANGE:
		POP BX
		POP DI
		POP SI
		RET
STR_NUM ENDP

;子模块 OUT_INFO
	;功能：输出商品相关信息
	;入口参数：BP-商品偏移地址
	;出口参数：无
OUT_INFO PROC NEAR
		CMP FLAG_INFO,1
		JE FLAG_INFO_1
		CMP FLAG_INFO,2
		JE FLAG_INFO_2
		WRITE STR3
		JMP CON1
FLAG_INFO_1:
		WRITE STR2
		JMP CON1
FLAG_INFO_2:
		WRITE STR3
CON1:
		CRLF
		CALL PRINTF_NAME
		OUT1 '='
		OUT1 '('
		MOV SI,12
LOOPO:		
        MOV  AX,WORD PTR DS:[BP+SI]
		CALL PRINTF
		ADD SI,2
		CMP FLAG_INFO,1
		JE _FLAG_INFO_1
		
		CMP SI,20
		JE END_OUT_INFO
		JMP CON2
_FLAG_INFO_1:
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

OVER:   MOV AH, 4CH
        INT 21H		
CODE    ENDS
        END     START