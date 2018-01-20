#include <stdio.h>
#include "aes.h"

void print_state(const state_t * state)
{
	int row, col;
	for (row = 0; row < WORD_SIZE; ++row)
	{
		for (col = 0; col < NB; ++col)
		{
			if (col)
				putchar('\t');
			printf("0x%02x", state->cols[col].bytes[row]);
		}
		putchar('\n');
	}
	putchar('\n');
}

void print_byteword(const byteword_t * word)
{
	int i;
	for (i = 0; i < WORD_SIZE; ++i)
	{
		if (i)
			putchar('\t');
		printf("0x%02x", word->bytes[i]);
	}
	putchar('\n');
}

/* ascii is of length byte_count*2, bytes of length byte_count */
int hex_to_bytes(uint8_t * ascii, uint8_t * bytes, size_t byte_count)
{
	int i;
	for (i = 0; i < byte_count; ++i)
	{
		int j;
		uint8_t byte = 0;
		for (j = 0; j < 2; ++j)
		{
			uint8_t hexchar, nibble;
			hexchar = ascii[2*i+j];
			if (hexchar >= '0' && hexchar <= '9')
				nibble = hexchar - '0';
			else if (hexchar >= 'a' && hexchar <= 'f')
				nibble = hexchar - 'a'+10;
			else
				return -1;
			byte = (byte << 4) | nibble;
		}
		bytes[i] = byte;
	}
}

int hex_to_state(uint8_t hex[32], state_t * state)
{
	uint8_t bytes[16];
	hex_to_bytes(hex, bytes, 16);

	int i;
	for (i = 0; i < 16; ++i)
	{
		state->cols[i/4].bytes[i%4] = bytes[i];
	}
}

void test(const uint8_t * text, const uint8_t * key, uint8_t * cipher, keylen_t mode)
{
	int i;
	encrypt_block(text, key, cipher, mode);
	for (i = 0; i < 16; ++i)
	{
		if (i)
			putchar(' ');
		printf("%02x", cipher[i]);
	}
	putchar('\n');
}

int main() {
	uint8_t key128[16];
	uint8_t key192[24];
	uint8_t key256[32];
	uint8_t text[16];
	uint8_t cipher[16];

	hex_to_bytes("00112233445566778899aabbccddeeff", text, 16);
	hex_to_bytes("000102030405060708090a0b0c0d0e0f", key128, 16);
	hex_to_bytes("000102030405060708090a0b0c0d0e0f1011121314151617", key192, 24);
	hex_to_bytes("000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f", key256, 32);

	test(text, key128, cipher, AES128);
	test(text, key192, cipher, AES192);
	test(text, key256, cipher, AES256);
}
