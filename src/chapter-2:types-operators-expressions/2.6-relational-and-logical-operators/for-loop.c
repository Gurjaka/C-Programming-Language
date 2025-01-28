#include <stdio.h>
#include <stdlib.h>

int main() {
  int lim = 1000;
  int i;
  char c;
  char s[lim];

  i = 0;
  while (i < lim - 1) {
    c = getchar();
    if (c == '\n')
      break;
    if (c == EOF)
      break;
    s[i] = c;
    ++i;
  }

  return EXIT_SUCCESS;
}
