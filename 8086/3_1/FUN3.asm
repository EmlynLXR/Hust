;编写者：同组同学： 
		NAME FUN3
		PUBLIC FUN3
		EXTRN PRINTF:FAR
.386	
DATA 	SEGMENT USE16 PARA PUBLIC 'DATA'
		N   	EQU   4
		PR1		DW	?
		PR2		DW	?
		APR		DW 	?
		MSG		DB	0AH,'Press any key to continue!$'
DATA 	ENDS
CODE 	SEGMENT USE16 PARA PUBLIC 'CODE'
		ASSUME CS:CODE,DS:DATA	
FUN3	PROC	FAR
		PUSH SI
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		MOV SI,BX
		ADD SI,6
		MOV DI,BP
		ADD DI,6
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
		CMP AH,N     
		JE RT        ;找不到商品
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
		MOV DI,BP
		ADD DI,6
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
RT:		
		LEA  DX, MSG           
		MOV  AH, 9           
		INT  21H         
		MOV  DL,0AH          
		MOV  AH,2    
		INT  21H       
		POP DX
		POP CX
		POP BX
		POP AX
		POP SI
		RET
FUN3 	ENDP

PR		PROC NEAR
		PUSH SI
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX 
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
CODE    ENDS
        END     