#ifndef CHUCK_AES_H
#define CHUCK_AES_H

#include <stdint.h>

#define NB 4

typedef union {
	uint8_t bytes[4];
	uint32_t word;
} byteword_t;

typedef struct {
	byteword_t cols[NB];
} state_t;

uint8_t ffmult(uint8_t a, uint8_t b);
void subbytes(state_t * state);


#endif
