#include "idt.h"
#include "../kernel/utils.h"

/*
 * set_idt_gate() : initialize a gate in IDT
 * n : the index to IDT, idt[n] is the nth descriptor
 * handler : address of the interrupt handler function
 */

idt_gate_t idt[]={}; // define the IDT as an empty array
idt_register_t idt_reg; // the IDTR

void set_idt_gate(u32 n, u32 handler){
    idt[n].lower_offset = low_16(handler);
    idt[n].selector = KERNEL_CS; // offset to code segment register in GDT
    idt[n].zero = 0;
    idt[n].flags_types = 0x8E;
    idt[n].higher_offset = high_16(handler);

}

void set_idt(){
    idt_reg.base = (u32) &idt; // address of the idt. (sizeof pointer in 32bit mode = 32 bits)
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) -1;
    /*
     * IDT should be loaded using idt_reg, not &idt 
     */ 
    /*
     * volatile disable the gcc optimization
     * Since there is no output, optimizer decides it has side effect(volatile. So, there is not need of __volatile__
     */ 
    __asm__ ("lidtl (%0)":: "r"(&idt_reg));

}
