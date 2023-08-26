print_string: 			; uses the bx register
	pusha				; pushing all the register contents into stack
	start:
		mov al, [bx]	
		cmp al,0
		je done
		mov ah, 0x0e
		int 0x10
		add bx,1
		jmp start
	done:
		popa			;restore all the values of registers
		ret

print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret
