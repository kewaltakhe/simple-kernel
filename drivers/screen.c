#include "../kernel/port.h"
#include "../kernel/utils.h"
#include "screen.h"

int get_cursor();
int get_screen_offset(int,int);
void set_cursor(int);
int handle_scrolling(int);
int get_col_from_offset(int);
int get_row_from_offset(int);
int print_char(char, int ,int ,char);

void kprint_at(char *message, int col, int row){
    int offset;
    if(col >= 0 && row >= 0){
        offset = get_screen_offset(col, row);
    }else{
        offset = get_cursor();
        row = get_row_from_offset(offset);
        col = get_col_from_offset(offset);
    }

    int i = 0;
    while(message[i] != '\0'){
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_row_from_offset(offset);
        col = get_col_from_offset(offset);
    }
}

void kprint(char *message){
    kprint_at(message, -1, -1);
}


void clear_screen(){
    int screen_size = MAX_COLS*MAX_ROWS;
    int i;
    unsigned char *screen = (unsigned char *)VIDEO_ADDRESS;

    for (i=0; i<screen_size; i++){
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor(get_screen_offset(0,0));
}

int print_char(char c, int col, int row, char attr){
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    
    int offset;
    if(col >= 0 && row >= 0){                        
        offset = get_screen_offset(col, row);
    }else{
        offset = get_cursor();                      // Get current cursor offset if row or col is negative
    }

    if(c == '\n'){                                  // If c is newline, start writing first column of the next row
        row = offset / (2*MAX_COLS); 
        offset = get_screen_offset(0, row+1);
    }else{                                          // otherwise write on the offset
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    offset = handle_scrolling(offset);    
    set_cursor(offset);
    return offset;
}

int handle_scrolling(int offset){
    unsigned char *vidmem =(unsigned char *)VIDEO_ADDRESS;
    if(offset < MAX_COLS*MAX_ROWS*2){
        return offset;
    }
    int i;
    for(i = 1; i < MAX_ROWS; i++){                        // If offset exceeds the screen size, replace ith row with (i-1)th row
        memory_copy(get_screen_offset(0,i)+vidmem,
                    get_screen_offset(0,i-1)+vidmem,
                    MAX_COLS*2);
    }
    unsigned char *lastline = get_screen_offset(0,MAX_ROWS-1) + vidmem; 
    for(i=0; i<MAX_COLS; i++){                            // Fill the last line with empty characters
        lastline[i] = 0;
    }
    offset -= 2*MAX_COLS;
    return offset;
}

int get_cursor(){
    port_byte_out(REG_SCREEN_CTRL, 14);                 // write 14 on CTRL port to get the higher byte of cursor offset
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;    
    port_byte_out(REG_SCREEN_CTRL, 15);                 // For lower byte of the cursor offset
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset*2; 
}

void set_cursor(int offset){
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8)); // Be aware of parenthesis. This could be an ugly bug.
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xFF));
}


int get_screen_offset(int col, int row){
    return 2*(MAX_COLS*row + col);
}
int get_row_from_offset(int offset){
    return offset/(MAX_COLS*2);
}
int get_col_from_offset(int offset) { 
    return (offset - (get_row_from_offset(offset)*2*MAX_COLS))/2; 
}
