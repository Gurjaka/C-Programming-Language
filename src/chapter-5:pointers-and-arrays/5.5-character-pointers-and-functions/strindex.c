#include <stdio.h>
#include <stdlib.h>

/* strindex: return index of t in s, -1 if none */
int strindex(char* s, char* t)
{
    char* start = s;
    char *temp, *sub;

    for (; *s != '\0'; s++)
    {
        sub = s;
        temp = t;

        for (; *temp != '\0' && *sub == *temp; sub++, temp++)
            ;

        if (*temp == '\0')
            return s - start;
    }
    return -1;
}

int main(void)
{
    char x[] = "hello";
    char y[] = "ell";
    printf("%d", strindex(x, y));
    return EXIT_SUCCESS;
}
