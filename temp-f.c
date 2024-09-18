#include <stdio.h>
int main() {
  float fahr, celsius;
  printf("fahr\tcelsius\n");

  for (fahr = 0; fahr <= 300; fahr += 20) {
    celsius = (5.0/9.0) * (fahr-32.0);
    printf("%3.0f\t%6.1f\n", fahr, celsius);
  }

  return 0;
}
