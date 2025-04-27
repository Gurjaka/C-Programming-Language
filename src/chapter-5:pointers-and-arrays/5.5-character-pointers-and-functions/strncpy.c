#include <stdio.h>
#include <stdlib.h>

// strncpy: copy t to s at most n characters;
void strn_cpy(char* s, char* t, int n)
{
    if (n)
    {
        for (; n != 0 && *t != '\0'; (*s++ = *t++), n--)
            ;
        *s = '\0';
    }
}

int main(void)
{
    char x[1000];
    char y[] = "hello";
    strn_cpy(x, y, 2);
    printf("%s", x);
    return EXIT_SUCCESS;
}
