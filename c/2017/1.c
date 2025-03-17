#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
  auto const input = get_input("../../inputs/2017/1");
  printf("File of size %zu reads as follows: %s\n", input.size, input.str);
}
