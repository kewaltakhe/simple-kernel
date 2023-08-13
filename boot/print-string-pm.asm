; store the address of the string to ebx
 
[bits 32] 						; tell the assembler to incode the instruction in 32 bit

VIDEO_MEM equ 0xb8000  			; the vga device memory address
WHITE_ON_BLACK equ 0x0f 		; attribute of a character

print_string_pm:
	pusha
	mov edx, VIDEO_MEM 			; set edx the start of the video memory
	
print_string_pm_loop:
	mov al, [ebx] 				; ebx stores the address of the string
	mov ah, WHITE_ON_BLACK 		; store the character attribute to ah
	
	cmp al, 0 					; check if al is null
	je print_string_pm_done 				
	
	mov [edx], ax 				; ax= ah+al(16bits). Move the ASCII and the character attribute to ax	
								; what is displayed on the screen is a visual representation of a VDA device memory
	add ebx, 1 					; next character of the string
	add edx, 2 					; next video memory position(each position is 2 bytes)
	jmp print_string_pm_loop
	
print_string_pm_done:
	popa
	ret

		
