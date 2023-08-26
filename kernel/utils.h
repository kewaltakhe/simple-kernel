#ifndef UTILS_H
#define UTILS_H

#include "../cpu/types.h"

void memory_copy(u8 *source, u8 *dest, int nbytes);
void memory_set(u8 *dest, u8 val, u32 len);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strnglen(char s[]);
void hex_byte_to_ascii(u8 n, char s[]);
#endif
