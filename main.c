#include <stdio.h>
#include "aes.h"

void print_state(state_t * state)
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
}

int main() {
	int i;
	state_t state = {
		{
			{.word=0xbee33d19},
			{.word=0x2be2f4a0},
			{.word=0x2a8dc69a},
			{.word=0x0848f8e9}
		}
	};

	print_state(&state);
	putchar('\n');
	subbytes(&state);
	shiftrows(&state);
	mixcolumns(&state);
	print_state(&state);
	return 0;
}
