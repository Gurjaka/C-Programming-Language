#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int a_toi(char *s) {
  int n = 0;
  for (; isdigit(*s); s++)
    n = 10 * n + (*s - '0');

  return n;
}

int main(void) {
  char x[] = "145";
  printf("%d", a_toi(x));
  return EXIT_SUCCESS;
}
