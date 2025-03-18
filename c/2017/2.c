#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "utils.h"

int main() {
	auto const input = get_input("../../inputs/2017/2");

	auto const nl_split = split_inplace_c(input.str, '\n', true);
	int checksum = 0, evenly_divisible_sum = 0;

	for (size_t i=0; i < nl_split.length; i++) {
		auto const ws_split = split_inplace(nl_split.strs[i], isspace, true);
		int min = INT_MAX, max = INT_MIN;
		int quotient = -1;

		for (size_t j=0; j < ws_split.length; j++) {
			const int jn = atoi(ws_split.strs[j]);
			if (jn < min) min = jn;
			if (jn > max) max = jn;

			if (quotient == -1)
				for (size_t k=0; k < ws_split.length; k++) {
					if (j != k) {
						const int kn = atoi(ws_split.strs[k]);
						if (jn % kn == 0) quotient = jn / kn;
					}
				}
		}

		checksum += max - min;
		if (quotient == -1)
			ERROR_QUIT("An evenly divisible pair wasn't found at line %zu", i);
		evenly_divisible_sum += quotient;
	}
  
	printf("Checksum is %d\n", checksum);
	printf("Evenly divisible sum is %d\n", evenly_divisible_sum);
}
