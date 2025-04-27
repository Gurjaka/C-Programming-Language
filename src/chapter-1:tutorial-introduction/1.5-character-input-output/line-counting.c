#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c, nl;

    nl = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            ++nl;
        }
    }

    printf("%d", nl);
    return EXIT_SUCCESS;
}
