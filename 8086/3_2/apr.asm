.386
.model flat, c
.data
flag db 0
.code
public apr
apr proc par1:dword,num:dword,N:dword
			mov ebx, par1
			mov ecx, N
			push ebx
			mov flag, 1
cal1:
			push ecx
			mov eax, dword ptr[ebx+12+4]
			mov edx, dword ptr[ebx+12+12]
			imul edx

			mov ecx, dword ptr[ebx+12+0]
			mov edx, dword ptr[ebx+12+8]
			imul ecx, edx

			sub eax, ecx
			mov edx, 100
			imul edx
			cmp ecx, 0
			je _end
			idiv ecx
			pop ecx
			mov [ebx+12+4 * 4], eax
			cmp flag,1
			je cal2
avg:
			mov eax, dword ptr[ebx+12+4 * 4]
			mov edx, dword ptr[edi+12+4 * 4]
			add eax,edx
			sar eax,1
			mov [edi+12+4 * 4],eax
			mov [ebx+12+4 *4],eax

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
			mov ebx,par1
			add ebx,num
			add ebx,num
			add ebx,num
			add ebx,num
loopc :		mov esi, 0
loopa :		mov al, byte ptr[edi+esi]
			cmp al, byte ptr[ebx+esi]
			jnz  fail
			inc esi
			cmp esi, 10
			jnz loopa
			jmp cal1
fail :
			add ebx, num
			jmp loopc
_end:
			ret
apr endp 
end
