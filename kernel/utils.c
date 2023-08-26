#include "utils.h"

void memory_copy(u8 *source, u8 *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/* K&R */
void int_to_ascii(int n, char s[]) {
    int i, sign, rem;
    sign = n;
    if(sign <0){
        n = -n; 
    }
    i = 0;
    while(n != 0){
        rem = n % 10;
        s[i] = rem + '0';
        n /= 10;
        i++;
    }
    s[i] = '\0';
    reverse(s);
}
/* K&R */
int stringlen(char s[]){
    int i = 0;
    while (s[i] != '\0'){
        i++;
    }
    return i;
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = stringlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void hex_byte_to_ascii(u8 n, char s[]){
    u8 num = n;
    int i = 0;
    while( i != 2 ){
        n = n & 0xF;
        n = n + '0';
        if(n > 0x39) n += 7;
        s[i] = n;
        n = num >> 4;
        i++;
    }
    s[i] = 'x';
    s[i+1] = '0';
    s[i+2] = '\0';
    reverse(s);
}
