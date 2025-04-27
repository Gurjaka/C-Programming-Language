#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c, prev;

    while ((c = getchar()) != EOF)
    {
        if (c != ' ' || prev != ' ')
        {
            putchar(c);
        }

        prev = c;
    }

    return EXIT_SUCCESS;
}
