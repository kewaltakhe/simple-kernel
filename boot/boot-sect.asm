; The boot sector starts from 0x7c00
[org 0x7c00]

KERNEL_OFFSET equ 0x1000                ; The memory address in main memory where the kernel code is going to be read to
mov [ BOOT_DRIVE ] , dl                 ; Select boot drive[BIOS takes care]
mov bp, 0x9000                          ; Sets the stact with base 0x9000
mov sp, bp                              

mov bx, MSG_REAL_16
call print_string
call print_nl

call load_kernel                        ; Read the kernel code to KERNEL_OFFSET
call switch_to_pm                       ; Disable interrupt, load GDT, switch to 32bit-pm mode, call BEGIN_PM

jmp $


%include "boot/print-string-rm.asm"
%include "boot/print-hex-rm.asm"
%include "boot/load-from-disk-rm.asm"
%include "boot/switch-to-32bit-pm.asm"
%include "boot/print-string-pm.asm"
%include "boot/gdt-32bit-pm.asm"

[bits 16]
load_kernel:
    mov bx,MSG_KERNEL_LOAD              ;
    call print_string
    call print_nl

    mov bx, KERNEL_OFFSET                   
    mov dh,16                            ; This was a bug when it is 2. Only 2 sectors for the kernel is not sufficient for kernel
    mov dl, [BOOT_DRIVE]                
    call disk_load                      
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_PM_32
    call print_string_pm
    call KERNEL_OFFSET                  ; Start executing the kernel code from 'main'
    jmp $

BOOT_DRIVE db 0
MSG_REAL_16 db "booting in real mode 16-bit ...",0
MSG_KERNEL_LOAD db "Loading the kernel ...",0
MSG_PM_32 db "switched to protected mode 32-bit. Kernel will start executing. Have Fun!",0


times 510 -( $ - $$ ) db 0
dw 0xaa55
