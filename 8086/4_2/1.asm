.386
STACK SEGMENT USE16 STACK
      DB 200 DUP(0)
STACK ENDS
;
DATA SEGMENT USE16
NUM  DD 3
RADX DD 10
BASE DB 10

D1   DB 0DH,0AH,'STUDENT NAME:$'
D2   DB 0DH,0AH,'GRADE:$'
PROMPT  db  0dh, 0ah, 'please enter password: $'
MSG     db  0dh, 0ah, 'please input target name : $'

BUF  DB  'z' XOR  's','h'XOR 's','a'XOR 's', 7 DUP(0)       
     DB    100 XOR 'B' ,85 XOR 'a', 80 XOR 't', ?       
     DB  'l' XOR  's','i'XOR 's','s'XOR 's','i' XOR 's',6 DUP(0)
     DB    80 XOR 'B', 98 XOR 'a', 70 XOR 't',?

PWD  DB  3 XOR 'C'       ;密码串的长度为3，采用与常数43H异或的方式编码成密文
     DB  ('B' -29H)*3    ;真实密码为Bat。采用函数(X-29H)*3对保存的密码进行编码。
     DB  ('a' -29H)*3
     DB  ('t' -29H)*3    
     DB  0A1H,5FH,0D3H   ;用随机数填充密码区到6个字符，防止破解者猜到密码长度
;
IN_PWD  DB 7             ;输入密码，最大长度6个字符
        DB ?
        DB 7 DUP(0)
;

INPUT   DB  11
        DB  ?
        DB  11 DUP(0)

P1      DW  PASS1             ;地址表
E1      DW  OVER
P2      DW  PASS2
P3      DW  PASS3
DATA ENDS
;
CODE SEGMENT USE16
     ASSUME CS:CODE,DS:DATA,SS:STACK
START: MOV AX,DATA
       MOV DS,AX
       LEA DX,PROMPT
       MOV AH,9
       INT 21H
       LEA DX,IN_PWD               ;输入密码字符串
       MOV AH,10
       INT 21H

       cli                       ;计时反跟踪开始 
       mov  ah,2ch 
       int  21h
       push dx                   ;保存获取的秒和百分秒
       MOV CL,IN_PWD+1             ;比较输入的串长与密码长度是否一样
       XOR CL,'C'
       SUB CL,PWD
       MOVSX  BX,CL
       ADD  BX,OFFSET P1    
         mov  ah,2ch                 ;获取第二次秒与百分秒
         int  21h
         sti
         cmp  dx,[esp]               ;计时是否相同
         pop  dx
         jz   OK1                    ;如果计时相同，通过本次计时反跟踪   
         mov  bx,offset E1           ;如果计时不同，则把转移地址偏离P1
OK1:     mov  bx,[bx]
         cmp  word ptr cs:[bx],0B60FH   ;是否是PASS1处的指令，其实是用于判断前面比较的
;串长是否相同
         jz   OK2
         jmp   E1
OK2:     jmp   bx
         db  'How to go'            ;定义的冗余信息

PASS1: MOVZX CX,IN_PWD+1
          cli                       ;堆栈检查反跟踪
          push  P2                  ;PASS2的地址压栈
       MOV  SI,0
       MOV  DL,3
          pop  ax
          mov  bx,[esp-2]           ;把栈顶上面的字（PASS2的地址）取到
          sti
          jmp  bx                   ;如果被跟踪，将不会转移到PASS2
          db  'i donot know！'
PASS2:  MOVZX  AX,IN_PWD+2[SI]    ;比较密码是否相同。把输入的串变成密文，与保存的密文比较
        SUB  AX,29H
        MUL  DL
        CMP  AL,PWD+1[SI]
        JNZ  ERR2
        INC  SI
        DEC  CX
        CMP  CX,0
        JNE  PASS2
        JMP  PASS3
ERR2:   MOV  EBX,OFFSET P1
        MOV  EDX,1
        JMP  WORD PTR [EBX+EDX*2]   ;指向OVER
        db  'YES,get it'
;
PASS3: ;　正常功能区
        lea   dx, msg                ; 输出提示信息 - 请输入姓名
        mov   ah, 9h
        int   21h
        lea   dx, input              ; 读入学生姓名, 以 '$' 符号结尾
        mov   ah, 0ah
        int   21h

        lea   esi, input+2
        lea   edi, buf
        xor   ebx, ebx
        xor   ecx, ecx
search_loop:
    cmp   ecx, num
    jge   search_finish
    xor   eax, eax
search_inner:
    cmp   eax, radx
    jge   search_finish
    mov   dl, [esi + eax]
        xor   dl, 's'
        cmp   [edi + ebx], dl
    jnz   search_next
    cmp   byte ptr [edi + ebx + 1], 0
    jz    search_finish
    inc   eax
    inc   ebx
    jmp   search_inner
        db   'the future will be better tomorrow'
search_next:
    inc   ecx
    imul  ebx, ecx, 14
    jmp   search_loop
        db  'welcome to hust'
search_finish:
    xor   ebx, ebx
output:
        sub     ebx,ecx
        imul    bx,14               ; 根据目标学生下标值, 找到分数缓冲区首地址
        mov     si,0
        mov     ax, 0
        mov     dx, 0
        mov     al,buf+10[bx+si]
        xor     al,in_pwd+2[si]
        add     ax, ax
        inc     si
        mov     dl, buf+10[bx+si]
        xor     dl,in_pwd+2[si]
        add     ax, dx              ; al = zh * 2 + ma
        inc     si
        mov     dl, buf+10[bx+si]
        xor     dl,in_pwd+2[si]
        sar     dl, 1
        add     ax, dx              ; al = zh * 2 + ma + en / 2
        sal     ax, 1               ; al = 2 * al
        mov     dx, 7
        idiv    dl                  ; al = al / 7
        inc     si
        mov     buf+10[bx+si], al   ; avg = al ( al / 3.5)
        push    ax
        mov     dl, 0ah
        mov     ah, 2h
        int     21h
        mov     dl, 0dh
        mov     ah, 2h
        int     21h
        pop     ax
        cmp     al, 90      ; switch 语句
        jge     gradea
        cmp     al, 80
        jge     gradeb
        cmp     al, 70
        jge     gradec
        cmp     al, 60
        jge     graded
        jmp     gradee
        db  'my sunshine'
gradea: mov     dl, 41h
        mov     ah, 2h
        int     21h
        jmp     pass3
gradeb: mov     dl, 42h
        mov     ah, 2h
        int     21h
        jmp     pass3
gradec: mov     dl, 43h
        mov     ah, 2h
        int     21h
        jmp     pass3
graded: mov     dl, 44h
        mov     ah, 2h
        int     21h
        jmp     pass3
gradee: mov     dl, 45h
        mov     ah, 2h
        int     21h
        jmp     pass3
  
OVER:
       MOV AH,4CH
       INT 21H
CODE   ENDS
       END START
