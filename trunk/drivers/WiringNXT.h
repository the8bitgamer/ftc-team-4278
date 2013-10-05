#ifndef __WIRENXT__
#define __WIRENXT__

#include "hitechnic-superpro.h"

#define B0 0x1
#define B1 0x2
#define B2 0x4
#define B3 0x8
#define B4 0x10
#define B5 0x20
#define B6 0x40
#define B7 0x80
#define A0 0x1
#define A1 0x2
#define A2 0x4
#define A3 0x8

#define HIGH true
#define LOW false

bool digitalWrite(ubyte mask) {
	return HTSPBwriteIO(HTSPB, mask);
}

ubyte digitalRead(ubyte mask) {
	return HTSPBreadIO(HTSPB, mask);
}

int analogRead(ubyte mask){
	return HTSPBreadADC(HTSPB, mask, 10);
}

/*
    00000000
B4  00010000 |
    00010000 -> hiddenMask

    00010000
B5  00100000 |
    00110000 -> hiddenMask

    00110000
!B4 11101111 &
    00100000 -> hiddenMask
*/

ubyte hiddenMask = 0x0;
bool setIO(ubyte port, bool enabled) {
	hiddenMask = (enabled ? (hiddenMask | port) : (hiddenMask & !port));
	return HTSPBsetupIO(HTSPB, hiddenMask);
}

#endif
