#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char buffer_char = 0;
static bool buffer_flag = false;

int get_char(void) {
  if (buffer_flag) {
    buffer_flag = false;
    return buffer_char;
  }
  return getchar();
}

void put_char_back(int c) {
  if (buffer_flag)
    printf("put_char_back: too many characters\n");
  else {
    buffer_char = c;
    buffer_flag = true;
  }
}

// get_float: get next float from input into *number
int get_float(float *number) {
  int current_char;
  float sign = 1.0;
  float value = 0.0;
  float fraction = 1.0;

  // Skip whitespace
  while (isspace(current_char = get_char()))
    ;

  // Handle optional sign
  if (current_char == '+' || current_char == '-') {
    if (current_char == '-')
      sign = -1.0;
    current_char = get_char();
  }

  // Read integer part
  while (isdigit(current_char)) {
    value = 10.0 * value + (current_char - '0');
    current_char = get_char();
  }

  // Read fractional part
  if (current_char == '.') {
    current_char = get_char();
    while (isdigit(current_char)) {
      value = 10.0 * value + (current_char - '0');
      fraction *= 10.0;
      current_char = get_char();
    }
  }

  // Combine integer and fractional parts
  *number = sign * value / fraction;

  // Push back the last character if it's not EOF
  if (current_char != EOF)
    put_char_back(current_char);

  return 1;
}

int main(void) {
  float number;
  printf("Enter a float: ");

  if (get_float(&number)) {
    printf("You entered: %f\n", number);
  } else {
    printf("Error: Not a valid float.\n");
  }

  return EXIT_SUCCESS;
}
