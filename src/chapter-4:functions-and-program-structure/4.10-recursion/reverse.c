#include <stdio.h>
#include <stdlib.h>

void reverse(char *str, int leftIndex, int rightIndex) {
  // Swap characters until the two indices meet
  if (leftIndex >= rightIndex)
    return;
  char temp = str[rightIndex];
  str[rightIndex] = str[leftIndex];
  str[leftIndex] = temp;
  reverse(str, ++leftIndex, --rightIndex);
}

int main(void) {
  char str[] = "hello";
  int rightIndex = 0;
  while (str[rightIndex] != '\0')
    ++rightIndex;
  --rightIndex;

  reverse(str, 0, rightIndex);
  printf("%s\n", str);
  return EXIT_SUCCESS;
}
