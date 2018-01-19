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

void print_key(const key_t * key, keylen_t Nk)
{
	int row, col;
	for (row = 0; row < WORD_SIZE; ++row)
	{
		for (col = 0; col < Nk; ++col)
		{
			if (col)
				putchar('\t');
			printf("0x%02x", key->cols[col].bytes[row]);
		}
		putchar('\n');
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

int main() {
	int i;

	uint8_t cipher_key[16];
	key_t round_keys[11];
	state_t state;

	hex_to_bytes("000102030405060708090a0b0c0d0e0f", cipher_key, 16);
	hex_to_state("00112233445566778899aabbccddeeff", &state);
	expand_keys(cipher_key, round_keys, AES128);

	addroundkey(&state, round_keys);
	for (i = 1; i < 10; ++i) {
		subbytes(&state);
		shiftrows(&state);
		mixcolumns(&state);
		addroundkey(&state, round_keys + i);
	}
	subbytes(&state);
	shiftrows(&state);
	addroundkey(&state, round_keys + 10);

	print_state(&state);
}
