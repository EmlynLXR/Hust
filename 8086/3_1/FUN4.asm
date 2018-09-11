;编写者： 同组同学： 
		NAME FUN4
		PUBLIC FUN4
		EXTRN PRINTF:FAR
.386	
DATA 	SEGMENT USE16 PARA PUBLIC 'DATA'
		N   	EQU   4
		PM		DB N DUP(0)
		MSG		DB	0AH,'Press any key to continue!$'
DATA 	ENDS
CODE 	SEGMENT USE16 PARA PUBLIC 'CODE'
		ASSUME CS:CODE,DS:DATA	
FUN4	PROC FAR
		LEA BP,PM
		MOV SI,DX
		ADD SI,6
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
		JMP AD    ;A负数B正数
T4A:	TEST BX,8000H
		JE T4B    ;A正数B正数
		POP BX
		POP AX
		JMP T4C   ;A正数B负数
T4B:	CMP BX,AX ;AB同正或同负
		JA AD
		POP BX
		POP AX
		JMP T4C
		
AD:		POP BX
		POP AX
		INC BL	
T4C:	INC BH
		CMP BH,N
		JE T42    ;当前商品统计完毕
		ADD DI,20
		JMP T41     ;和下一商品比较
		
		
T42:	PUSH SI
		MOV SI,CX
		MOV DS:[BP+SI],BL   ;保存排名于数组
		POP SI
		INC CX
		MOV BH,0
		MOV BL,1
		CMP CX,N
		JE T43        ;全部商品统计完毕
		ADD SI,20
		
		MOV DI,DX
		ADD DI,6
		
		JMP T41

T43:	
		MOV SI,DX
		ADD SI,6
		MOV CX,0
T43_:	MOV BYTE PTR[SI+19],0
		PUSH SI
		MOV SI,CX
		MOV BL,DS:[BP+SI]
		POP SI
		MOV [SI+18],BL
		INC CX
		CMP CX,N
		JE EXIT
		ADD SI,20
		JMP T43_
EXIT:
		LEA  DX, MSG           
		MOV  AH, 9           
		INT  21H 
		MOV  DL,0AH          
		MOV  AH,2    
		INT  21H      
		RET
FUN4 ENDP
CODE    ENDS
        END     