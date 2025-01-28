#include <stdio.h>
int main() {
  int numbers[4];
  for (int i = 0; i < 4; i++) {
    printf("Num%d\n", i + 1);
    scanf("%d", &numbers[i]);
  }
  int max = numbers[0];
  for (int i = 1; i < 4; i++) {
    if (numbers[i] > max) {
      max = numbers[i];
    }
  }
  printf("\nMax is: %d", max);
  return 0;
}
