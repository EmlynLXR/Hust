.386
STACK 	SEGMENT USE16	STACK
		DB	200 DUP(0)
STACK 	ENDS

DATA 	SEGMENT USE16
	BNAME	DB   'ZHANGSAN',0,0  ;老板姓名（必须是自己名字的拼音）
	BPASS  	DB   '666666',0,0,0,0    ;密码
	N		EQU  30
	S1  	DB   'SHOP1',0           ;网店名称，用0结束
	GA1   	DB   'PEN', 7 DUP(0)  ; 商品名称
			DW   35,56,70,25,?  ;利润率还未计算
	GA2   	DB   'BOOK', 6 DUP(0) ; 商品名称
			DW   12,30,25,5,?   ;利润率还未计算
	GAN   	DB   N-2 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?) ;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
	
	S2 		DB   'SHOP2',0           ;网店名称，用0结束
	GB1   	DB   'BOOK', 6 DUP(0) ; 商品名称
			DW   12,28,20,15,?   ;利润率还未计算
	GB2   	DB   'PEN', 7 DUP(0)  ; 商品名称
			DW   35,50,30,24,?  ;利润率还未计算
			DB   N-2 DUP( 'TempValue',0,15,0,20,0,30,0,2,0,?,?) ;除了2个已经具体定义了商品信息以外，其他商品信息暂时假定为一样的。
	MSG1    DB   'Input the name (if enter q,exit!):$'
	MSG2	DB	 'Input the password:$'
	MSG3	DB	 'Input the shop name:$'
	MSG4	DB	 'Login Success!$'
	MSG5	DB	 'Login Fail!$'
	MSG6	DB   'Successful Search!$'
	MSG7	DB   'Unsuccessful Search!$'
	MSG8	DB   'You have no access!$'
	
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
	PR1		DW 0
	PR2		DW 0
	APR 	DW 0
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
		MOV FLAG,0
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
		
		CMP FLAG,0
		JE SEARCH_SUCCESS
		JNE CAL	
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
		
		CMP AUSH,1
		JE CAL1
		LEA DX, MSG8      	;未登录，输出提示信息
        MOV AH, 9H
        INT 21H	
		JMP INPUT
CAL1:
		MOV FLAG,0
		JMP CAL
CAL2:
		MOV FLAG,1
		LEA BP,GB1
		MOV CH,N
		JMP LOOPC
CAL:
		ADD BP,10
		MOV AX,WORD PTR DS:[BP+2]
		MOV BX,WORD PTR DS:[BP+6]
		IMUL AX,BX
		MOV DI,AX
		
		
		MOV AX,WORD PTR DS:[BP]
		MOV BX,WORD PTR DS:[BP+4]
		IMUL AX,BX
		MOV SI,AX
		
		SUB DI,SI		
		MOV AX,DI
		MOV CX,100
		IMUL CX		
		IDIV SI
		
		CMP FLAG,1
		JE	JUDGE
		MOV PR1,AX
		JMP CAL2
JUDGE:		
		MOV	PR2,AX
		JMP AVG_CAL	
		
AVG_CAL:
		MOV SI,PR1
		MOV DI,PR2
		ADD SI,DI
		MOV AX,SI
		MOV CL,2
		IDIV CL
		CBW				;将AL中的符号扩展至AH中
		MOV APR,AX	
		MOV BX,AX
		
		TEST BX,8000H
		JE OUTLET
		SUB BX,1
		NOT BX
		MOV DL,2DH ;'-' ascii 2dh
		MOV AH,2   
		INT 21h		
OUTLET:		
		JMP PRINTF1
PRINTF2:
		MOV DL, 25H         ;输出%
        MOV AH, 2H
        INT 21H			
		MOV DX, 0AH         ;输出换行符
        MOV AH, 2H
        INT 21H		
		
        CMP APR, 90      
        JGE LEVELA
        CMP APR, 50
        JGE LEVELB
        CMP APR, 20
        JGE LEVELC
        CMP APR, 0
        JGE LEVELD
        JMP LEVELF
LEVELA: 
		MOV DL, 41H    ;输出成绩等级
		JMP OUTPUT
LEVELB: 
		MOV DL, 42H
		JMP OUTPUT
LEVELC: 
		MOV DL, 43H
		JMP OUTPUT
LEVELD: 
		MOV DL, 44H
		JMP OUTPUT
LEVELF: 
		MOV DL, 46H
		JMP OUTPUT
OUTPUT:
        MOV AH, 2H
        INT 21H
        JMP INPUT		

PRINTF1:
		MOV  SI,10
		XOR  CX,CX
		MOV AX,BX
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
		JMP PRINTF2 

OVER:   MOV AH, 4CH
        INT 21H		
CODE    ENDS
        END     START