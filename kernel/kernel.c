#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../cpu/timer.h"
void main(){
    isr_install();
    clear_screen();
    __asm__("sti");
    //__asm__ __volatile__("int $10");
    init_timer(50);
}
