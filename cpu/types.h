#ifndef TYPES_H
#define TYPES_H

//Typedefs to standarized data types

typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address)>>16) & 0xFFFF)
#define low_8(operand16bit) (u8)((operand16bit) & 0xFF)
#define high_8(operand16bit) (u8)(((operand16bit)>>8) & 0xFF)

#endif
