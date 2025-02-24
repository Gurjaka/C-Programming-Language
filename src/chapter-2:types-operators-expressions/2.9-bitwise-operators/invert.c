#include <stdio.h>
#include <stdlib.h>

/* I am not familiar with manipulating binary, this code is generated by
chatgpt, will have to come back later */

unsigned invert(unsigned x, int p, int n) {
  // Create a mask with n bits set to 1 at position p
  unsigned mask = ((1U << n) - 1) << (p - n + 1);

  // Invert the n bits in x using XOR
  return x ^ mask;
}

int main(void) {
  unsigned x = 0b10101010; // Binary representation of 170
  int p = 5, n = 3;        // Invert 3 bits starting from position 5

  x = invert(x, p, n);
  printf("X = %u\n", x); // Print the result in decimal
  return EXIT_SUCCESS;
}
