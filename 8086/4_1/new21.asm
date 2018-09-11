.386
DATA   SEGMENT USE16 
DATA   ENDS
CODE   SEGMENT USE16 
       ASSUME CS:CODE,SS:STACK
OLD_INT DW ?,?

NEW16H:	
		CMP AH,00H
		JE  CHANGE
		CMP AH,10H
		JE  CHANGE
		JMP DWORD PTR OLD_INT
CHANGE:
		PUSHF
		CALL DWORD PTR OLD_INT
		CMP AL,61H            ;比较输入的ascii码
		JB QUIT             ;
		CMP AL,7AH
		JBE NEXT
		JMP QUIT   
NEXT: 	
		SUB AL,20H
QUIT:
		IRET
       
START:  XOR AX,AX
        MOV DS,AX
        MOV AX,DS:[16H*4]        
        MOV OLD_INT,AX           ;保存偏移部分
        MOV AX,DS:[16H*4+2]
        MOV OLD_INT+2,AX         ;保存段值 
	    
		CLI
        MOV WORD PTR DS:[16H*4],OFFSET NEW16H
	    MOV DS:[16H*4+2],CS
        STI

        MOV DX,OFFSET START+15
	    SHR DX,4
        ADD DX,10H
	   
        MOV AL,0
        MOV AH,31H
        INT 21H
		
CODE   ENDS
STACK  SEGMENT USE16 STACK
       DB 200 DUP(0)
STACK  ENDS
       END START
