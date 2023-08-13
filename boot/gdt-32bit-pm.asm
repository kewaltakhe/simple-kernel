; gdt
; Basic flat model of gdt. Contains two overlapping segments. 1.code segment, 2.data segment
gdt_start:

gdt_null: 					; compulsory. A null descriptor. dd declares 4 bytes
	dd 0x0 	;4 bytes				
	dd 0x0 	;4 bytes

; a segment descriptor in gdt is a structure of 8 bytes.
; it contains 1. address of the base of the segment(32bits), 2.limit of the segment(20bits), 3. Flags(remaining bits)

; for both Base=0x0, Limit=0xfffff, granularity--1 i.e. limit 0xfffff is multiplied by 16*16*16*16=0xfffff000 
; enabling span upto 4GB

gdt_code:
	dw 0xffff 				; limit, bits 0-15(16) 
	dw 0x0 					; base, bits 0-15(16)
	db 0x0 					; base, bits 16-23(8)
	db 10011010b 			; flags, (8bits)
	db 11001111b 			; flags(4bits), limit bits 16-19(4)
	db 0x0 					; base, bits 23-31(8)

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b 			; type of segment flag is changed
    db 11001111b
    db 0x0

gdt_end:


gdt_descriptor:
	dw gdt_end - gdt_start -1 ; size of gdt always 1 less: 16bits
	dd gdt_start 			  ; start address of the gdt: 32bits

; some handy constants for the GDT segment descriptor offsets

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start 
