#ifndef CHUCK_AES_H
#define CHUCK_AES_H

#include <stdint.h>

typedef union {
	uint8_t bytes[4];
	uint32_t word;
} byteword_t;

/* The max nb is 8, so we'll just have an array of 8 */
typedef struct {
	byteword_t cols[8];
	uint8_t nb;
} state_t;

uint8_t ffmult(uint8_t a, uint8_t b);
uint8_t subbytes(state_t * state);

#endif
