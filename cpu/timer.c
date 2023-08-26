#include "timer.h"
#include "isr.h"
#include "../kernel/port.h"
#include "../kernel/utils.h"
#include "../drivers/screen.h"

u32 tick = 0;
static void timer_callback(registers_t reg){
    tick++;
    kprint("TICK: ");
    char tick_ascii[256];
    int_to_ascii(tick, tick_ascii);
    kprint(tick_ascii);
    kprint("\n");
}

void init_timer(u32 frequency){
    register_interrupt_handler(IRQ0, timer_callback); //PIT is connected to IRQ0
    int pit_internal_freq = 1193180; 
    u32 divisor = pit_internal_freq/frequency;
    u8 low = (u8)(divisor & 0xFF);
    u8 high = (u8)((divisor >> 8) & 0xFF);
    port_byte_out(0x43, 0x36);                       // 0x36 to the command port means repeated timer
    port_byte_out(0x40, low);                        // note the divisor must be sent as two bytes
    port_byte_out(0x40, high); 

}
