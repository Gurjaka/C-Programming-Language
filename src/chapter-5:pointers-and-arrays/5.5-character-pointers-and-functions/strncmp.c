#include <stdio.h>
#include <stdlib.h>

// strn_cmp: return <0 if s<t, 0 if s==t, >0 if s>t at most n characters
int strn_cmp(char* s, char* t, int n)
{
    if (n)
    {
        for (; n != 0 && *s == *t; s++, t++, n--)
            if (*s == '\0')
                return 0;
        return *s - *t;
    }
    return 0;
}

int main(void)
{
    char x[] = "hello";
    char y[] = "world";
    printf("%d", strn_cmp(x, y, 2));
    return EXIT_SUCCESS;
}
