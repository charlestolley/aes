#ifndef CHUCK_AES_H
#define CHUCK_AES_H

#include <stdint.h>

#define NB 4
#define WORD_SIZE 4

typedef enum { AES128=4, AES192=6, AES256=8 } keylen_t;

typedef union {
	uint8_t bytes[WORD_SIZE];
	uint32_t word;
} byteword_t;

typedef struct {
	byteword_t cols[NB];
} state_t;

uint8_t ffmult(uint8_t a, uint8_t b);
void subbytes(state_t * state);
void shiftrows(state_t * state);
void mixcolumns(state_t * state);
void addroundkey(state_t * state, const byteword_t * key);

void subword(byteword_t * word);
void rotateword(byteword_t * word);

/* key should be Nk*4 bytes long */
/* round_keys should be NB*(Nk+7) words long */
void expand_keys(const uint8_t * key, byteword_t * round_keys, keylen_t Nk);

#endif
