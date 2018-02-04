#ifndef CHUCK_AES_H
#define CHUCK_AES_H

#include <stdint.h>
#include <stdio.h>

#define NB 4
#define WORD_SIZE 4
#define BLOCK_SIZE (NB*WORD_SIZE)

typedef enum { AES128=4, AES192=6, AES256=8 } keylen_t;
typedef enum { ECB, CBC } aes_mode_t;

typedef union {
	uint8_t bytes[WORD_SIZE];
	uint32_t word;
} byteword_t;

typedef struct {
	byteword_t cols[NB];
} state_t;

void decryptCBC(const uint8_t * cipher, uint8_t * text, size_t block_count,
					const uint8_t * key, keylen_t keytype, const uint8_t * iv);
void decryptECB(const uint8_t * cipher, uint8_t * text, size_t block_count,
										const uint8_t * key, keylen_t keytype);
void encryptCBC(const uint8_t * text, uint8_t * cipher, size_t len,
				const uint8_t * key, keylen_t keytype, const uint8_t * iv);
void encryptECB(const uint8_t * text, uint8_t * cipher, size_t len,
								const uint8_t * key, keylen_t keytype);

#endif
