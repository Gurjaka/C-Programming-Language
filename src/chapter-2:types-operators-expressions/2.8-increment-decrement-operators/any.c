#include <stdio.h>
#include <stdlib.h>

#define LIMIT 1000

int any(char s1[], char s2[]) {
  int i, j;

  for (i = 0; s1[i] != '\0'; ++i) {
    for (j = 0; s2[j] != '\0'; ++j) {
      if (s1[i] == s2[j]) {
        return i;
      }
    }
  }

  return -1;
}

int main(void) {
  char s1[LIMIT] = "tutorial";
  char s2[LIMIT] = "roial";

  printf("%d\n", any(s1, s2));
  return EXIT_SUCCESS;
}
