#include <stdio.h>
#include <stdlib.h>

int strend(char* s, char* t)
{
    char* s_start = s;
    char* t_start = t;

    for (; *s; s++)
        ;

    for (; *t; t++)
        ;

    if (t - t_start > s - s_start)
        return 0;

    for (; t >= t_start; s--, t--)
    {
        if (*s != *t)
            return 0;
    }

    return 1;
}

int main(void)
{
    char x[] = "world";
    char y[] = "rld";
    printf("%d", strend(x, y));
    return EXIT_SUCCESS;
}
