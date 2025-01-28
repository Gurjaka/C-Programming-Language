#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Char range: from %+d to %+d\n", CHAR_MIN, CHAR_MAX);
  printf("Int range: from %+d to %+d\n", INT_MIN, INT_MAX);
  printf("Short range: from %+d to %+d\n", SHRT_MIN, SHRT_MAX);
  printf("Long range: from %ld to %ld\n", LONG_MIN, LONG_MAX);
  printf("Singed char: from %+d to %+d\n", SCHAR_MIN, SCHAR_MAX);
  printf("Unsinged char: from 0 to %+d\n", UCHAR_MAX);
  return EXIT_SUCCESS;
}
