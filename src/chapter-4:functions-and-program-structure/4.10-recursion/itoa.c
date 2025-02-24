#include <stdio.h>
#include <stdlib.h>

void itoa(int number, char result[], int *index) {
  if (number < 0) { // Record sign
    result[(*index)++] = '-';
    number = -number; // Make number positive
  }
  if (number / 10)
    itoa(number / 10, result, index);
  result[(*index)++] = number % 10 + '0'; // Extract next digit
}

int main(void) {
  int index = 0;
  int number = 10;
  char outputString[1000];

  itoa(number, outputString, &index);
  outputString[index] = '\0';
  printf("%s", outputString);

  return EXIT_SUCCESS;
}
