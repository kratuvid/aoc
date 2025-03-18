#include <stdio.h>
#include <ctype.h>
#include "utils.h"

int main() {
  auto input = get_input("../../inputs/2017/2");
  printf("Original: %s\n\n", input.str);

  auto split = split_inplace(input.str, isspace, true);
  printf("%zu splits claimed\n", split.length);

  for (size_t i=0; i < split.length; i++) {
    printf("'%s'\t", split.strs[i]);
    if (i % 10 == 0) printf("\n");
  }
  printf("\n");
}
