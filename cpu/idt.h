#ifndef IDT_H
#define IDT_H
#include "types.h"
/*segment selector: offset of code segment descriptor in gdt*/
#define KERNEL_CS 0x08

/*
 * idt_gate_t : structure of an IDT gate
 */

typedef struct{
    u16 lower_offset;      // lower 16 bits of the address of the interrupt handler function
    u16 selector;          // kernel segment selector
    u8 zero;               // always zero
    u8 flags_types;        // (0-3) gate type, (4) interrupt gate, (5-6) DPL- privilege level of caller, (7) present
    u16 higher_offset;       // higher 16 bits of the handler funtion
} __attribute__((packed)) idt_gate_t;

/*
 *idtr : idt register holds the location of the IDT. This way 'lidt' instruction will read it
 *       This will a pointer to the array of interrupt handlers
 */

typedef struct{
    u16 limit;             // size of the IDT 
    u32 base;              // base address of the IDT
} __attribute__((packed)) idt_register_t;

/*
 * global array of the IDT gates i.e. IDT;
 * if not extern the compiler take it as definition which leads to multiple def error
 */
#define IDT_ENTRIES 256
extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(u32, u32);
void set_idt();

#endif
