#ifndef CHUCK_AES_H
#define CHUCK_AES_H

#include <stdint.h>
#include <stdio.h>

#define NB 4
#define WORD_SIZE 4
#define BLOCK_SIZE (NB*WORD_SIZE)

typedef enum { AES128=4, AES192=6, AES256=8 } keylen_t;

typedef union {
	uint8_t bytes[WORD_SIZE];
	uint32_t word;
} byteword_t;

typedef struct {
	byteword_t cols[NB];
} state_t;

/* blocks = # of blocks of text; this will just assume that the text has already been padded */
void encrypt(const uint8_t * text, uint32_t blocks, const uint8_t * key, keylen_t Nk, FILE * cipher);
void encrypt(const uint8_t * text, uint32_t blocks, const uint8_t * key, keylen_t Nk, FILE * cipher);

#endif
