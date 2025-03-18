#include <stdio.h>
#include <ctype.h>
#include "utils.h"

int main() {
  auto const input = get_input("../../inputs/2017/2");
  /* printf("Original: %s\n\n", input.str); */

  auto const nl_split = split_inplace_c(input.str, '\n', true);
  for (size_t i=0; i < nl_split.length; i++) {
    auto const ws_split = split_inplace(nl_split.strs[i], isspace, true);
    printf("%zu splits at line %zu\n", ws_split.length, i);
  }
}
