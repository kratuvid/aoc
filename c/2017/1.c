#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

int main() {
	auto input = get_input("../../inputs/2017/1");
	trim(&input.str, &input.size, isspace);

	if (input.size % 2 != 0)
		ERROR_QUIT("Input list doesn't contain an even number of elements!");

	int selective_sum = 0, selective_sum2 = 0;
	const size_t halfway = input.size / 2;
	for (size_t i=0; i < input.size; i++) {
		const char a = input.str[i], b = input.str[(i+1) % input.size];
		const int digit_a = (int)a - (int)'0';

		if (!isdigit(a))
			ERROR_QUIT("%c at index %zu isn't a digit!", a, i);

		if (a == b) {
			selective_sum += digit_a;
		}

		const char bb = input.str[(i + halfway) % input.size];
		if (a == bb) {
			selective_sum2 += digit_a;
		}
	}

	printf("%d is the selective sum\n", selective_sum);
	printf("%d is the second selective sum\n", selective_sum2);
}
