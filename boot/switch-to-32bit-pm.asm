[bits 16] 					  	;starts with real mode 16bits
switch_to_pm:
	cli 					  	; disable the interrupts 
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax            ; can also jump using offset as : jmp 0x08:init_pm
	jmp CODE_SEG:init_pm      	; CODE_SEG(offset=0x08) far jump to the code segment just immidiately. This causes the cpu to flush its pipeline.
								; this is important to avoid the cpu executing instructions in the real mode


[bits 32] 						; telling the assembler to incode the instructions in 32 bit mode
; Now we are in the 32 bit mode of cpu
; first thing to do is update the register contents since
; the older contents belong to 16 bit mode and are meaningless now

init_pm:
	mov ax, DATA_SEG            ; DATAS_SEG(offset=0x10)
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000 			; update the stack base so its right at the top of free space
	mov esp, ebp 				
	
	call BEGIN_PM 				; a well-known label

	


