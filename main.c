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

int main() {
	int i, Nr;
	Nr = 10;

	const state_t round_keys[11] = {
		{{
			{.word=0x16157e2b},
			{.word=0xa6d2ae28},
			{.word=0x8815f7ab},
			{.word=0x3c4fcf09}
		}},
		{{
			{.word=0x17fefaa0},
			{.word=0xb12c5488},
			{.word=0x3939a323},
			{.word=0x05766c2a}
		}},
		{{
			{.word=0xf295c2f2},
			{.word=0x43b9967a},
			{.word=0x7a803559},
			{.word=0x7ff65973}
		}},
		{{
			{.word=0x7d47803d},
			{.word=0x3efe1647},
			{.word=0x447e231e},
			{.word=0x3b887a6d}
		}},
		{{
			{.word=0x41a544ef},
			{.word=0x7f5b52a8},
			{.word=0x3b2571b6},
			{.word=0x00ad0bdb}
		}},
		{{
			{.word=0xf8c6d1d4},
			{.word=0x879d837c},
			{.word=0xbcb8f2ca},
			{.word=0xbc15f911}
		}},
		{{
			{.word=0x7aa3886d},
			{.word=0xfd3e0b11},
			{.word=0x4186f9db},
			{.word=0xfd9300ca}
		}},
		{{
			{.word=0x0ef7544e},
			{.word=0xf3c95f5f},
			{.word=0xb24fa684},
			{.word=0x4fdca64e}
		}},
		{{
			{.word=0x2173d2ea},
			{.word=0xd2ba8db5},
			{.word=0x60f52b31},
			{.word=0x2f298d7f}
		}},
		{{
			{.word=0xf36677ac},
			{.word=0x21dcfa19},
			{.word=0x4129d128},
			{.word=0x6e005c57}
		}},
		{{
			{.word=0xa8f914d0},
			{.word=0x8925eec9},
			{.word=0xc80c3fe1},
			{.word=0xa60c63b6}
		}}
	};

	state_t state = {
		{
			{.word=0xa8f64332},
			{.word=0x8d305a88},
			{.word=0xa2983131},
			{.word=0x340737e0}
		}
	};

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
	return 0;
}
