#include <stdio.h>
#include <stdlib.h>

void reverse(char string[]) {
  int i = 0, j = 0;

  while (string[i] != '\0')
    ++i;

  --i;

  while (i > j) {
    char temp = string[i];
    string[i] = string[j];
    string[j] = temp;
    --i;
    ++j;
  }
}

void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0) // record sign
    n = -n;           // make n positive
  i = 0;

  do {                     // generate digits in reverse order
    s[i++] = n % 10 + '0'; // get next digit
  } while ((n /= 10) > 0); // delete it

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main(void) {
  int n = 10;
  char s[1000];

  itoa(n, s);
  printf("%s", s);

  return EXIT_SUCCESS;
}
