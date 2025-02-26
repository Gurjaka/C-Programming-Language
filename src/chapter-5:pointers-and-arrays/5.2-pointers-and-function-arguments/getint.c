#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static char buffer_char = 0;
static int buffer_flag = 0;

int get_char(void) {
  if (buffer_flag) {
    buffer_flag = 0;
    return buffer_char;
  }
  return getchar();
}

void put_char_back(int c) {
  if (buffer_flag)
    printf("put_char_back: too many characters\n");
  else {
    buffer_char = c;
    buffer_flag = 1;
  }
}

// get_integer: get next integer from input into *number
int get_integer(int *number) {
  int current_char, sign;

  while (isspace(current_char = get_char()))
    ;

  if (!isdigit(current_char) && current_char != EOF && current_char != '+' &&
      current_char != '-') {
    put_char_back(current_char);
    return 0;
  }
  sign = (current_char == '-') ? -1 : 1;
  if (current_char == '+' || current_char == '-')
    current_char = get_char();
  for (*number = 0; isdigit(current_char); current_char = get_char())
    *number = 10 * *number + (current_char - '0');
  *number *= sign;
  if (current_char != EOF)
    put_char_back(current_char);
  return current_char;
}

int main(void) {
  int number, result;
  result = get_integer(&number);
  printf("you entered %d", number);
  return EXIT_SUCCESS;
}
