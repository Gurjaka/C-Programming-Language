#include <stdio.h>
#include <stdlib.h>

/* lower: convert c to lower case; ASCII only
note: <ctype.h> has tolower function which is a portable replacement */
int lower(int c) {
  int low = (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
  return low;
}

int main(void) {
  char res;
  res = lower('B');

  printf("%c\n", res);

  return EXIT_SUCCESS;
}
