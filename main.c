#include <stdio.h>
#include "aes.h"

void print_state(state_t * state)
{
	int row, col;
	for (row = 0; row < 4; ++row)
	{
		for (col = 0; col < state->nb; ++col)
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
			{.word=0x12345678},
			{.word=0x87654321},
			{.word=0x11111111},
			{.word=0xffffffff}
		},
		4
	};

	print_state(&state);
	return 0;
}
