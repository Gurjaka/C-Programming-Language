#include <stdio.h>
#include <stdlib.h>
#define swap(t, x, y)                                                          \
  {                                                                            \
    t temp = x;                                                                \
    x = y;                                                                     \
    y = temp;                                                                  \
  }

int main(void) {
  char x[] = "hello", y[] = "zd";
  char *a = x, *b = y;
  swap(char *, a, b);
  printf("%s %s\n", a, b);
  return EXIT_SUCCESS;
}
