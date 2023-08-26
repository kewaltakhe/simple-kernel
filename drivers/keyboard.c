#include "keyboard.h"
#include "../cpu/isr.h"
#include "../kernel/port.h"
#include "screen.h"
#include "../kernel/utils.h"

static void keyboard_callback(registers_t);
static void print_character(u8);

static void keyboard_callback(registers_t reg){
    u8 ps2_data_port = 0x60;
    u8 scancode = port_byte_in(ps2_data_port);
    char scancode_ascii[5];
    hex_byte_to_ascii(scancode,scancode_ascii); 
    kprint("keyboard scancode ");
    kprint(scancode_ascii);
    kprint(":");
    print_character(scancode);
    kprint("\n");
}

void init_keyboard(){
    register_interrupt_handler(IRQ1, keyboard_callback);
}

void print_character(u8 scancode){
    switch(scancode){
		case 0x1:
			kprint("ESC");
			break;
		case 0x2:
			kprint("1");
			break;
		case 0x3:
			kprint("2");
			break;
		case 0x4:
			kprint("3");
			break;
		case 0x5:
			kprint("4");
			break;
		case 0x6:
			kprint("5");
			break;
		case 0x7:
			kprint("6");
			break;
		case 0x8:
			kprint("7");
			break;
		case 0x9:
			kprint("8");
			break;
		case 0xa:
			kprint("9");
			break;
		case 0xb:
			kprint("0");
			break;
		case 0xc:
			kprint("-");
			break;
		case 0xd:
			kprint("+");
			break;
		case 0xe:
			kprint("Back Space");
			break;
		case 0xf:
			kprint("Tab");
			break;
		case 0x10:
			kprint("Q");
			break;
		case 0x11:
			kprint("W");
			break;
		case 0x12:
			kprint("E");
			break;
		case 0x13:
			kprint("R");
			break;
		case 0x14:
			kprint("T");
			break;
		case 0x15:
			kprint("Y");
			break;
		case 0x16:
			kprint("U");
			break;
		case 0x17:
			kprint("I");
			break;
		case 0x18:
			kprint("O");
			break;
		case 0x19:
			kprint("P");
			break;
		case 0x1a:
			kprint("[");
			break;
		case 0x1b:
			kprint("]");
			break;
		case 0x1c:
			kprint("Enter");
			break;
		case 0x1d:
			kprint("LCtrl");
			break;
		case 0x1e:
			kprint("A");
			break;
		case 0x1f:
			kprint("S");
			break;
		case 0x20:
			kprint("D");
			break;
		case 0x21:
			kprint("F");
			break;
		case 0x22:
			kprint("G");
			break;
		case 0x23:
			kprint("H");
			break;
		case 0x24:
			kprint("J");
			break;
		case 0x25:
			kprint("K");
			break;
		case 0x26:
			kprint("L");
			break;
		case 0x27:
			kprint(";");
			break;
		case 0x28:
			kprint("'");
			break;
		case 0x29:
			kprint("`");
			break;
		case 0x2a:
			kprint("LShift");
			break;
		case 0x2b:
			kprint("\\");
			break;
		case 0x2c:
			kprint("Z");
			break;
		case 0x2d:
			kprint("X");
			break;
		case 0x2e:
			kprint("C");
			break;
		case 0x2f:
			kprint("V");
			break;
		case 0x30:
			kprint("B");
			break;
		case 0x31:
			kprint("N");
			break;
		case 0x32:
			kprint("M");
			break;
		case 0x33:
			kprint(",");
			break;
		case 0x34:
			kprint(".");
			break;
		case 0x35:
			kprint("/");
			break;
		case 0x36:
			kprint("Rshift");
			break;
		case 0x37:
			kprint("Keypad *");
			break;
		case 0x38:
			kprint("LAlt");
			break;
		case 0x39:
			kprint("Space");
			break;
		default:
            if(scancode < 0x7f ){
                kprint("Unknown");
                break;
            }else if(scancode <= (0x39 + 0x80)){
                print_character(scancode-0x80);
                kprint("(break)");
                break;
            }else{
                kprint("Unknown(break)");
                break;
            }   
    }
}
