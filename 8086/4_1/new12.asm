.386  
STACK   SEGMENT     USE16   STACK
        DB 200  DUP(0)
STACK   ENDS
CODE    SEGMENT     USE16
        ASSUME  CS:CODE,  SS:STACK
START: 
		XOR AX,AX
		MOV DS,AX
		MOV BX,DS:[4H]
		MOV CX,DS:[6H]
		MOV BX,DS:[40H] 
		MOV CX,DS:[42H] 
		MOV AH,4CH 
		INT 21H 
CODE ENDS 
END START
