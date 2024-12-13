#include <stdio.h>

float cels_to_fahr(float cels)
{
    float fahr = cels * 1.8 + 32;
    return fahr;
}

int main() {
  printf("celsius\tfahr\n");
  for (float cels = 0; cels <= 300; cels += 20) {
    printf("%7.0f\t%4.1f\n", cels, cels_to_fahr(cels));
  }

  return 0;
}
