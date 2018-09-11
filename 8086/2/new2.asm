.386
STACK 	SEGMENT USE16	STACK
		DB	200 DUP(0)
STACK 	ENDS

DATA 	SEGMENT USE16
	BNAME	DB   'ZHANGSAN',0,0  ;老板姓名（必须是自己名字的拼音）
	BPASS  	DB   '666666',0,0,0,0    ;密码
	N		EQU  30
	M 		EQU  1000
	S1  	DB   'SHOP1',0           ;网店名称，用0结束
	GA1   	DB   'PEN', 7 DUP(0)  ; 商品名称
			DW   35,56,70,25,?  ;利润率还未计算
	GA2   	DB   'BOOK', 6 DUP(0) ; 商品名称
			DW   12,30,25,5,?   ;利润率还未计算
	GA3		DB   'Bag',7 DUP(0)
			DW	 20,30,M,0
	GAN   	DB   N-3 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?) ;除了3个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
	
	S2 		DB   'SHOP2',0           ;网店名称，用0结束
	GB1   	DB   'BOOK', 6 DUP(0) ; 商品名称
			DW   12,28,20,15,?   ;利润率还未计算
	GB2   	DB   'PEN', 7 DUP(0)  ; 商品名称
			DW   35,50,30,24,?  ;利润率还未计算
	GB3		DB   'Bag',7 DUP(0)
			DW	 35,25,M,0
			DB   N-3 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?)
			;除了3个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
	MSG1    DB   'Input the name (if enter q,exit!):$'
	MSG2	DB	 'Input the password:$'
	MSG3	DB	 'Input the shop name:$'
	MSG4	DB	 'Login Success!$'
	MSG5	DB	 'Login Fail!$'
	MSG6	DB   'Successful Search!$'
	MSG7	DB   'Unsuccessful Search!$'
	MSG8	DB   'You have no access!$'
	MSG9	DB	 'The goods have sold out!$'
	
	in_name DB  10
			DB ?
			DB 10 DUP(0)
    in_pwd  DB  10
			DB ?
			DB 10 DUP(0)
	in_shop DB  10
			DB ?
			DB 10 DUP(0)
			
	AUSH	DB 0
	FLAG	DB 0
DATA 	ENDS

CODE 	SEGMENT USE16
		ASSUME CS:CODE,SS:STACK,DS:DATA		
START:  MOV	AX, DATA
        MOV DS, AX	
INPUT:	
		MOV DX, 0AH      ;输出换行符
        MOV AH, 2H
        INT 21H		
		LEA DX, MSG1      	;输入用户名，输出提示信息
        MOV AH, 9H
        INT 21H				
		LEA DX, in_name    	;读入姓名
        MOV AH, 0AH
        INT 21H	
		MOV BL,in_name+1
		MOV BH,0
		MOV BYTE PTR in_name+2[BX],'$'			
		MOV DX, 0AH             	; 输出换行符
        MOV AH, 2H
        INT 21H			
				
		CMP BYTE PTR in_name+1,0H   ;仅输入回车符号，跳过功能二进入功能三
		JE  SEARCH
		CMP BYTE PTR in_name+1,1H   ;输入超过一个字符，跳过功能二进入功能三
		JNE INPUT2	
		CMP BYTE PTR in_name+2,71H	;输入 'q', 退出程序
        JE 	OVER

INPUT2: LEA DX, MSG2      	;输入密码，输出提示信息
        MOV AH, 9H
        INT 21H		
		LEA DX, in_pwd    	; 读入密码
        MOV AH, 0AH
        INT 21H	
		MOV BL,in_pwd+1
		MOV BH,0
		MOV BYTE PTR in_pwd+2[BX],'$'	
        MOV DX, 0AH             	; 输出换行符
        MOV AH, 2H
        INT 21H			
		
CMP_NAME:
		LEA SI,BNAME	
		LEA DI,in_name+2
		MOV CL,in_name+1
		MOV CH,0
		MOV FLAG,0
		JMP CMP_
CMP_PWD:
		LEA SI,BPASS	
		LEA DI,in_pwd+2
		MOV CL,in_pwd+1
		MOV CH,0	
		MOV FLAG,1
		JMP CMP_		
CMP_:
		MOV DL,BYTE PTR DS:[SI]
		CMP BYTE PTR DS:[DI],DL
		JNE	LOGIN_FAIL
		INC SI
		INC DI
		DEC CX
		JNZ CMP_
		CMP BYTE PTR DS:[SI],0
		JNE LOGIN_FAIL
		
		CMP FLAG,0
		JE CMP_PWD
		CMP FLAG,1
		JE LOGIN_SUCCESS

LOGIN_SUCCESS:		
		MOV AUSH,1
		LEA DX, MSG4      	;登陆成功，输出提示信息
        MOV AH, 9H
        INT 21H
		JMP SEARCH
LOGIN_FAIL:
		MOV AUSH,0
		LEA DX, MSG5      	;登录失败，输出提示信息
        MOV AH, 9H
        INT 21H
		JMP INPUT
SEARCH_FAIL:
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H	
		LEA DX, MSG7      	;查找失败，输出提示信息
        MOV AH, 9H
        INT 21H	
SEARCH:
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H	
		LEA DX, MSG3      	;输入商品名称，输出提示信息
        MOV AH, 9H
        INT 21H				
		LEA DX, in_shop    	;读入商品名称
        MOV AH, 0AH
        INT 21H
		MOV BL,in_shop+1
		MOV BH,0
		MOV BYTE PTR in_shop+2[BX],'$'			
		CMP BYTE PTR in_shop+1,0H   ;仅输入回车符号，返回功能一
		JE  INPUT

		LEA BP,GA1
		MOV CH,N
		JMP LOOPC
LOOPC:	
		LEA DI,in_shop+2	
		MOV SI,BP
		MOV CL,in_shop+1
LOOPA:
		MOV DL,BYTE PTR DS:[SI]
		CMP BYTE PTR DS:[DI],DL
		JNE	LOOPB
		INC SI
		INC DI
		DEC CL
		JNZ LOOPA
		CMP BYTE PTR DS:[SI],0
		JNE LOOPB
		JMP SEARCH_SUCCESS	
LOOPB:
		DEC CH
		JZ SEARCH_FAIL
		ADD BP,20
		JMP LOOPC
SEARCH_SUCCESS:
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H	
		LEA DX, MSG6      	;查找成功，输出提示信息,且BP为字符串首地址
        MOV AH, 9H
        INT 21H	
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H	
		
		
		LEA DX,in_shop+2      ;输出商品名称
		MOV AH,9H
        INT 21H			
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H		
		
		MOV DX,WORD PTR DS:[BP+16]
		CMP DX,M
		JAE RE_INPUT


		CMP AUSH,1
		JE UPDATA_1
		LEA DX, MSG8      	;未登录，输出提示信息
        MOV AH, 9H
        INT 21H	
		JMP INPUT	
		
		
UPDATA_1:	 
		MOV  AX, 0;表示开始计时
	    CALL TIMER	
		MOV CX,WORD PTR DS:[BP+16]
UPDATA_ALL:
		PUSH CX
		PUSH BP	
		MOV CX,N
		LEA BP,GA1
UPDATA:
		PUSH CX
		PUSH BP			
		JMP CAL1
UPDATA2:	
		POP BP
		MOV DS:[BP+18],AX			
		POP CX
		ADD BP,20		
		DEC CX
		JNZ UPDATA		
		
		POP BP
		POP CX
		INC CX
		MOV WORD PTR DS:[BP+16],CX
		CMP CX,M
		JBE UPDATA_ALL
	
		MOV  AX, 1
		CALL TIMER	;终止计时并显示计时结果(ms)
		JMP OVER	
RE_INPUT:
		LEA DX, MSG9      	;输出提示信息
        MOV AH, 9H
        INT 21H	
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H			
		JMP INPUT

LOOPF:		
		MOV SI,0
LOOPG:
		MOV DL,BYTE PTR DS:[BP+SI]
		CMP BYTE PTR DS:[BX+SI],DL
		JNE	LOOPH
		INC SI
		CMP SI,10
		JNE LOOPG
		JMP CAL	
LOOPH:
		DEC CH
		ADD BP,20
		JMP LOOPF
		
CAL1:
		MOV FLAG,0
		JMP CAL
CAL2:
		MOV FLAG,1
		MOV BX,BP
		LEA BP,GB1
		MOV CH,N
		JMP LOOPF
CAL:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		MOVZX EAX,WORD PTR DS:[BP+12]
		MOVZX EBX,WORD PTR DS:[BP+16]
		IMUL EBX
		
		MOVZX ECX,WORD PTR DS:[BP+10]
		MOVZX EBX,WORD PTR DS:[BP+14]
		IMUL EBX,ECX
		
		SUB EAX,EBX	
		MOV ECX,100
		IMUL ECX		
		IDIV EBX
		
		CMP FLAG,0
		JE	CAL2
		PUSH AX		
AVG_CAL:
		POP SI
		ADD AX,SI
		SHR AX,1	

		JMP UPDATA2

TIMER	PROC NEAR
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP

OVER:   MOV AH, 4CH
        INT 21H		
CODE    ENDS
        END     START
