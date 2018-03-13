#ifndef AVR_MACROS_H
#define AVR_MACROS_H


#define PINS(LOW,HIGH)  (unsigned char)((1<<(HIGH-LOW+1))-1)<<LOW

typedef enum { false, true } bool;

#endif