#include <stdio.h>
int main()
{
    float cels, fahr;
    printf("celsius\tfahr\n");
    for (cels = 0; cels <= 300; cels += 20)
    {
        fahr = cels * 1.8 + 32;
        printf("%7.0f\t%4.1f\n", cels, fahr);
    }

    return 0;
}
