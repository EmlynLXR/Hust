.386
.model flat, c
.code
public rank
rank proc par1:dword,par2:dword,num:dword,N:dword 
				mov esi,par1
				add esi,num
				add esi,num
				add esi,num
				add esi,num
				
				MOV EDI, ESI
				MOV ECX, 0;外循环计数器
				MOV EBX,0
				MOV BH, 0;内循环计数器
				MOV BL, 1;排名
T41 :			PUSH EAX
				PUSH EBX
				MOV EAX, dword ptr[ESI+12+4*4]
				MOV EBX, dword ptr[EDI+12+4*4]
				TEST EAX, 8000H
				JE T4A;A正数
				TEST EBX, 8000H
				JNE T4B;A负数B负数
				JMP AD;A负数B正数
T4A :			TEST EBX, 8000H
				JE T4B;A正数B正数
				POP EBX
				POP EAX
				JMP T4C;A正数B负数
T4B :			CMP EBX, EAX;AB同正或同负
				JA AD
				POP EBX
				POP EAX
				JMP T4C
AD :			POP EBX
				POP EAX
				INC BL
T4C :			INC BH
				CMP BH, 4;N
				JE T42;当前商品统计完毕
				ADD EDI, num
				JMP T41;和下一商品比较
T42 :			
				MOV BH, 0
				push esi
				mov esi,par2
				MOV [esi+ECX*4], EBX;保存排名于数组
				pop esi
				INC ECX
				MOV EBX, 0
				MOV BL, 1
				CMP ECX, N
				JE T43;全部商品统计完毕
				ADD ESI, num
				mov edi,par1
				add edi,num
				add edi,num
				add edi,num
				add edi,num
				JMP T41
T43 :
				mov esi,par1
				add esi,num
				add esi,num
				add esi,num
				add esi,num
				mov ebx,par2
				MOV EDI, 0
T43_ :		
				MOV EAX,dword ptr[ebx+EDI*4]
				MOV [ESI+12+4*4],EAX
				INC EDI
				CMP EDI, N
				JE _end
				ADD ESI, num
				JMP T43_
_end:
			ret
rank endp 
end