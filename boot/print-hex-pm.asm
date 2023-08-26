[bits 32]

print_hex_pm:
	pusha
	mov ecx, 0
	hex_loop_pm:
		cmp ecx, 8
		je exit_loop
		mov eax, edx
		and eax, 0x0000000f
		add al, 0x30
		cmp al, 0x39
		jle step_two
		add al, 7
	
	step_two:
		mov ebx, (HEX_OUT_PM+9)
		sub ebx, ecx
		mov [ebx], al
		add ecx, 1
		ror edx, 4
		jmp hex_loop_pm	
	exit_loop:
		mov ebx,HEX_OUT_PM
		call print_string_pm
		popa 
		ret

HEX_OUT_PM:
	 db '0x00000000',0
