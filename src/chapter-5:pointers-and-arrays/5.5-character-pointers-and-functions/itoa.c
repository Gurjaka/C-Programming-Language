#include <stdio.h>
#include <stdlib.h>

#include "reverse.c"

void itoa(int n, char* s)
{
    char* start = s;

    unsigned int num = (n < 0) ? -n : n; // Convert to unsigned to handle INT_MIN

    do
    {
        *s++ = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (n < 0)
        *s++ = '-';

    *s = '\0';

    reverse(start);
}

int main(void)
{
    int x = 145;
    char string[1000];
    itoa(x, string);
    printf("%s", string);
    return EXIT_SUCCESS;
}
