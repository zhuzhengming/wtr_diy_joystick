#ifndef _PRINTF_h
#define _PRINTF_h
#include "string.h"

//������������
typedef unsigned char       uint8;   //  8 bits
typedef unsigned short int  uint16;  // 16 bits
typedef unsigned long int   uint32;  // 32 bits
typedef unsigned long long  uint64;  // 64 bits

typedef char                int8;    //  8 bits
typedef short int           int16;   // 16 bits
typedef long  int           int32;   // 32 bits
typedef long  long          int64;   // 64 bits

typedef volatile int8       vint8;   //  8 bits 
typedef volatile int16      vint16;  // 16 bits 
typedef volatile int32      vint32;  // 32 bits 
typedef volatile int64      vint64;  // 64 bits 

typedef volatile uint8      vuint8;  //  8 bits 
typedef volatile uint16     vuint16; // 16 bits 
typedef volatile uint32     vuint32; // 32 bits 
typedef volatile uint64     vuint64; // 64 bits 
//void    printf(const char *format, ...);
uint32  zf_sprintf(char *buf, const char *fmt, ...);

#endif
