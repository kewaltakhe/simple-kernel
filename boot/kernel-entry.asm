[bits 32]       ; now we have entered the protected in PM mode. Use 32-bit instruction 
[extern main]   ; extern declares a symbol the linker must search in other object files
call main       ; call our kernel_entry function, 'main', an external symbol
jmp $           ; hang forever when we return from the kernel
