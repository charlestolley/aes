#ifndef CHUCK_AES_H
#define CHUCK_AES_H

#include <stdint.h>

#define NB 4
#define WORD_SIZE 4

typedef union {
	uint8_t bytes[WORD_SIZE];
	uint32_t word;
} byteword_t;

typedef struct {
	byteword_t cols[NB];
} state_t;

typedef state_t key_t;

uint8_t ffmult(uint8_t a, uint8_t b);
void subbytes(state_t * state);
void shiftrows(state_t * state);
void mixcolumns(state_t * state);
void addroundkey(state_t * state, const key_t * key);

#endif
