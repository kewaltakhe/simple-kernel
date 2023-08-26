#include "isr.h"
#include "idt.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "../kernel/port.h"

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

isr_t interrupt_handlers[256]={};

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

    //======= IRQ =======
   
    // REMAPPING: requires a series of steps

    port_byte_out(PIC1_CMD, 0x11);        // Restart PIC1; Tell the two pics to wait for 3 bytes See osdev/pic for more details
    port_byte_out(PIC2_CMD, 0x11);        // Restart PIC2; 3bytes (offset,cascade, give additional bytes of the environment)

    port_byte_out(PIC1_DATA, 0x20);       // PIC1 now starts at 32
    port_byte_out(PIC2_DATA, 0x28);       // PIC2 now starts at 40
                                          // SETUP PIC CASCADING
    port_byte_out(PIC1_DATA, 0x04);       // tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    port_byte_out(PIC2_DATA, 0x02);       // tell Slave PIC its cascade identity (0000 0010) 

    port_byte_out(PIC1_DATA, 0x01);       // restore saved masks
    port_byte_out(PIC2_DATA, 0x01);
   
    port_byte_out(PIC1_DATA, 0x0);        // Dunno; J.Molly code
    port_byte_out(PIC2_DATA, 0x0);

    // SETTING IDT GATES
    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);        // From PIC2 to PIC1
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);

    set_idt(); // Load with ASM
}

/* List of exception messages. The messages are ordered according to the interrupt number */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r) {
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    kprint(s);
    kprint("\n");
    kprint(exception_messages[r.int_no]); // the interrupt number is used as index to get the error message
    kprint("\n");
}

void register_interrupt_handler(u8 n, isr_t handler){ //initializer of the interrupt_handlers[]
    interrupt_handlers[n] = handler;
}


void irq_handler(registers_t r){
    // send EOI signal(0x20) to the PIC chips, to indicate end of servicing IRQ interrupt
    // if IRQ comes from PIC2 send EOI to both of them else only PIC1
    if(r.int_no >=40){
        port_byte_out(PIC2_CMD,PIC_EOI);
    }
    port_byte_out(PIC1_CMD,PIC_EOI);

    if (interrupt_handlers[r.int_no] !=0 ){  
        isr_t handler = interrupt_handlers[r.int_no];      // handler is a pointer pointing to the appropriate 
                                                                // handler funtion
        handler(r);       
    }
}
