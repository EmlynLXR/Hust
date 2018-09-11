.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
Average	 proto :DWORD,:DWORD,:DWORD
CHANGE	 proto :DWORD

include      new1.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

      szText MACRO Name, Text:VARARG
        LOCAL lbl
          jmp lbl
            Name db Text,0
          lbl:
        ENDM
      return MACRO arg
        mov eax, arg
        ret
      ENDM
	  
info	struct
	    g_name	db	10 dup(0)
		purchase1 dw	0
		purchase2 dw	0
		selling1  dw	0
		selling2  dw	0
		apr		dw	0
info	ends

.data
ClassName    db       'MyWinClass',0
AppName      db       'MyWindow',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'My name is LiXingru',0
ExitMsg	     db       'Sure to exit?',0
hInstance    dd       0
CommandLine  dd       0

buf1		info  <'PEN',35,56,70,25,0>
			info  <'BOOK',12,30,25,5,0>
			info  <'BAG',30,50,30,0,0>
			info  <'SHOE',20,50,30,20,0>
			info  <'GLOVE',25,50,35,10,0>
			
buf2		info  <'BOOK',12,28,20,15,0>
			info  <'PEN',35,50,30,24,0>
			info  <'BAG',30,50,30,0,0>
			info  <'SHOE',20,45,30,15,0>
			info  <'GLOVE',20,50,35,10,0>

msg_shop1	db	'shop1',0
msg_shop2	db	'shop2',0
msg_name    db  'name',0
msg_purchase1	db	'pur_price',0 
msg_purchase2  	db	'pur_quantity',0
msg_selling1  	db	'sell_price',0
msg_selling2  	db	'sell_quantity',0
msg_apr 		db	'apr(%)',0
purchase1	    db  2,'35','12','30','50','20',    '12','35','30','50','20'
purchase2	    db  2,'56','30','50','50','50',	'28','50','50','20','50'
selling1	    db  2,'70','25','30','30','35',	'20','30','30','30','35'
selling2	    db	2,'25','05','00','20','10',		'15','24','0','15','10'	
APR		db 10 dup(0)
flag	db 0

.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     
		INVOKE GetMessage,addr msg,NULL,0,0
        cmp    EAX,0
        je     ExitLoop
        INVOKE TranslateMessage,addr msg
        INVOKE DispatchMessage,addr msg
	    jmp    MsgLoop 
ExitLoop:    
		mov    eax,msg.wParam
	    ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
			 invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	 
	    .IF     wParam == IDM_FILE_EXIT
			invoke SendMessage,hWnd,WM_CLOSE,0,0
		.ELSEIF wParam == IDM_ACTION_AVERAGE
			invoke Average,addr buf1,addr buf2,20;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			invoke Display,hWnd
		.ELSEIF wParam == IDM_ACTION_LIST
			invoke Display,hWnd		
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,MB_OK 
	    .ENDIF
     ;.ELSEIF uMsg == WM_PAINT
	     ;;redraw window again
     .elseif uMsg == WM_CLOSE
        szText TheText,"Please Confirm Exit"
        invoke MessageBox,hWnd,ADDR TheText,ADDR AppName,MB_YESNO
          .if eax == IDNO
            return 0
          .endif
     .ENDIF
	 
    XOR EAX,EAX     	   
	invoke DefWindowProc,hWnd,uMsg,wParam,lParam
    ret
WndProc      endp

Display      proc   hWnd:DWORD
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  100
	     YY_GAP equ  30
             LOCAL  hdc:HDC
             invoke GetDC,hWnd
             mov    hdc,eax
			 invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_shop1,5
			 
             invoke TextOut,hdc,XX+0*XX_GAP,YY+1*YY_GAP,offset msg_name,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+1*YY_GAP,offset msg_purchase1,9
             invoke TextOut,hdc,XX+2*XX_GAP,YY+1*YY_GAP,offset msg_purchase2,12
             invoke TextOut,hdc,XX+3*XX_GAP,YY+1*YY_GAP,offset msg_selling1,10
             invoke TextOut,hdc,XX+4*XX_GAP,YY+1*YY_GAP,offset msg_selling2,13
             invoke TextOut,hdc,XX+5*XX_GAP,YY+1*YY_GAP,offset msg_apr,6
			 
             invoke TextOut,hdc,XX+0*XX_GAP,YY+2*YY_GAP,offset buf1[0*20].g_name,3
             invoke TextOut,hdc,XX+1*XX_GAP,YY+2*YY_GAP,offset purchase1+1,purchase1
             invoke TextOut,hdc,XX+2*XX_GAP,YY+2*YY_GAP,offset purchase2+1,purchase2
             invoke TextOut,hdc,XX+3*XX_GAP,YY+2*YY_GAP,offset selling1+1,selling1
             invoke TextOut,hdc,XX+4*XX_GAP,YY+2*YY_GAP,offset selling2+1,selling2
			 invoke CHANGE,18
             invoke TextOut,hdc,XX+5*XX_GAP,YY+2*YY_GAP,offset APR,5
			
             invoke TextOut,hdc,XX+0*XX_GAP,YY+3*YY_GAP,offset buf1[1*20].g_name,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+3*YY_GAP,offset purchase1+3,purchase1
             invoke TextOut,hdc,XX+2*XX_GAP,YY+3*YY_GAP,offset purchase2+3,purchase2
             invoke TextOut,hdc,XX+3*XX_GAP,YY+3*YY_GAP,offset selling1+3,selling1
             invoke TextOut,hdc,XX+4*XX_GAP,YY+3*YY_GAP,offset selling2+3,selling2
			 invoke CHANGE,18+20
             invoke TextOut,hdc,XX+5*XX_GAP,YY+3*YY_GAP,offset APR,5
			 
             invoke TextOut,hdc,XX+0*XX_GAP,YY+4*YY_GAP,offset buf1[2*20].g_name,3
             invoke TextOut,hdc,XX+1*XX_GAP,YY+4*YY_GAP,offset purchase1+5,purchase1
             invoke TextOut,hdc,XX+2*XX_GAP,YY+4*YY_GAP,offset purchase2+5,purchase2
             invoke TextOut,hdc,XX+3*XX_GAP,YY+4*YY_GAP,offset selling1+5,selling1
             invoke TextOut,hdc,XX+4*XX_GAP,YY+4*YY_GAP,offset selling2+5,selling2
			 invoke CHANGE,18+40
             invoke TextOut,hdc,XX+5*XX_GAP,YY+4*YY_GAP,offset APR,5
			 
             invoke TextOut,hdc,XX+0*XX_GAP,YY+5*YY_GAP,offset buf1[3*20].g_name,4
             invoke TextOut,hdc,XX+1*XX_GAP,YY+5*YY_GAP,offset purchase1+7,purchase1
             invoke TextOut,hdc,XX+2*XX_GAP,YY+5*YY_GAP,offset purchase2+7,purchase2
             invoke TextOut,hdc,XX+3*XX_GAP,YY+5*YY_GAP,offset selling1+7,selling1
             invoke TextOut,hdc,XX+4*XX_GAP,YY+5*YY_GAP,offset selling2+7,selling2
			 invoke CHANGE,18+60
             invoke TextOut,hdc,XX+5*XX_GAP,YY+5*YY_GAP,offset APR,5
			 
             invoke TextOut,hdc,XX+0*XX_GAP,YY+6*YY_GAP,offset buf1[4*20].g_name,5
             invoke TextOut,hdc,XX+1*XX_GAP,YY+6*YY_GAP,offset purchase1+9,purchase1
             invoke TextOut,hdc,XX+2*XX_GAP,YY+6*YY_GAP,offset purchase2+9,purchase2
             invoke TextOut,hdc,XX+3*XX_GAP,YY+6*YY_GAP,offset selling1+9,selling1
             invoke TextOut,hdc,XX+4*XX_GAP,YY+6*YY_GAP,offset selling2+9,selling2
			 invoke CHANGE,18+80
             invoke TextOut,hdc,XX+5*XX_GAP,YY+6*YY_GAP,offset APR,5
             ret
Display      endp

CHANGE	PROC num:dword
		MOV ECX,num
		MOV EDI,0
		MOVSX EAX,word ptr buf1[ECX]
		TEST EAX,80000000H
		JNE A    ;正数
		MOV APR[EDI],'+'
		INC EDI	
		JMP PRIN
A:
		MOV APR[EDI],'-'
		INC EDI
		SUB EAX,1
		NOT EAX
PRIN:	
		MOV ESI,10
		XOR ECX,ECX
NEXT:	
		MOV  EDX,0
		DIV  ESI
		PUSH  EDX
		INC  ECX
		CMP  EAX,0	;商为0则完成转换
		JNZ  NEXT
OUTP:	
		POP EDX
		ADD EDX,30H
		MOV	APR[EDI],DL
		INC EDI
		LOOP OUTP 
B:		
		MOV	APR[EDI],20H
		INC EDI
		CMP EDI,11
		JNE	B
		RET
CHANGE	ENDP

Average	proc par1:dword,par2:dword,num:dword
			mov ebx, par1
			mov ecx, 5
			push ebx
			mov flag, 1
cal1:
			push ecx
			movsx eax, word ptr[ebx+10+2]
			movsx edx, word ptr[ebx+10+6]
			imul edx

			movsx ecx, word ptr[ebx+10+0]
			movsx edx, word ptr[ebx+10+4]
			imul ecx, edx

			sub eax, ecx
			mov edx, 100
			imul edx
			cmp ecx, 0
			je _end
			idiv ecx
			pop ecx
			mov [ebx+10+2 * 4], ax
			cmp flag,1
			je cal2
avg:
			movsx eax, word ptr[ebx+10+2 * 4]
			movsx edx, word ptr[edi+10+2 * 4]
			add eax,edx
			sar eax,1
			mov [edi+10+2*4],ax
			mov [ebx+10+2*4],ax

			pop ebx
			dec ecx
			add ebx, num
			cmp ecx,0
			je _end
			push ebx
			mov flag, 1
			jmp cal1
cal2:
			mov flag, 2
			mov edi,ebx
			mov ebx,par2
loopc :		mov esi, 0
loopa :		mov al, byte ptr[edi+esi]
			cmp al, byte ptr[ebx+esi]
			jnz fail
			inc esi
			cmp esi, 10
			jnz loopa
			jmp cal1
fail :
			add ebx, num
			jmp loopc
_end:
			ret
Average	endp
             end  Start
