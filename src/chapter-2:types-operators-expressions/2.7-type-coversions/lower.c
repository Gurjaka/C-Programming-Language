#include <stdio.h>
#include <stdlib.h>

/* lower: convert c to lower case; ASCII only
note: <ctype.h> has tolower function which is a portable replacement */
int lower(int c) {
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}

int main(void) {
  char res;
  res = lower('B');

  printf("%c\n", res);

  return EXIT_SUCCESS;
}
