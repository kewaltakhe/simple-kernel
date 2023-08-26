; this function creates a string format of a hex number.
; every nibbles is retrived by masking with 0x000f and a circular shift right
; mask twraba tungda hex number ama fngani, akhoina least significant nibble se ASCII char
; da onthokani. 
; ASCII da onbagi step:
; 1. akhoina mask twraba hex number ado 0x30 add twgni. Karigumba 0x30 to 0x39 gi range ta leirbdi,
; least significant nibble ado numerical ASCII ni. Range sigi wangmada leirdi alphabet onthoknaba 7 add
; twgni.
; 2. ASCII da ollaba nibbles sing do hanna declared twraba HEX_OUT sequence of byte ta store twsingni one-by-one
; 3. HEX_OUT se required oiba ASCII values of nibles yaorba tungda print_string sijinnaduna print twni 


print_hex:
	pusha
	mov cx, 0 				; initializing the counter of the loop
	hex_loop:
		cmp cx, 4			; 4 loops for 4 nibbles
		je exit_hex_loop
		mov ax, dx
		and ax, 0x000f
		add al, 0x30

		cmp al, 0x39
		jle step2
		add al, 7

	step2:
		mov bx, HEX_OUT+5
		sub bx, cx
		mov [bx], al
		ror dx, 4
		
		add cx, 1
		jmp hex_loop

	exit_hex_loop:
		mov bx, HEX_OUT
		call print_string_pm
		popa
		ret

HEX_OUT:
	db '0x0000',0        ; later to be filled with ASCII characters

