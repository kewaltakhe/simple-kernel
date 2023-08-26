#ifndef SCREEN_H
#define SCREEN_H
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// attribute byte for our color scheme
#define WHITE_ON_BLACK 0x0f
//screen device I/O port
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void kprint_at(char *,int ,  int);
void kprint(char *);
void clear_screen();
#endif 
