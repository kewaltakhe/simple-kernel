; load dh sector to ex:bx from drive dl
; dx:- dh stores how many sectors to read, dl stores which drive to use(see the main program)
disk_load:
	pusha

	push dx              	; Store the value of dx in the stack for furthur use
	mov ah, 0x02			; ah=0x02, BIOS disk read sector routine
	
	mov ch, 0x00			; ch=0x00, which cylinder
	mov al, dh				; al=dh, How many sector to read
 	mov dh, 0x00			; dh=0x00, which head
 	mov cl, 0x02            ; select second sector as the starting sector. i.e. after our boot sector
	int 0x13				; trigger the interrupt

	jc disk_error 			; the CF flag is set if any disk operation error happened by the BIOS.

	pop dx
	cmp dh, al              ; al is set the number of sectors that is actually read from the disk. It is 
							; compared with the expected number of sector to i.e. dh
	jne sector_error          
	popa
	ret


disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

sector_error:
	mov bx, SECTOR_ERROR_MSG
	call print_string
	jmp $

;global variable
DISK_ERROR_MSG:
	db 'disk error',0

SECTOR_ERROR_MSG:
	db 'sector error',0