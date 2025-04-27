#include <stdio.h>
#include <stdlib.h>

// strn_cat: concatenate t to end of s at most n characters;
void strn_cat(char* s, char* t, int n)
{
    if (n)
    {
        for (; *s != '\0'; s++) /* find end of s */
            ;
        for (; n != 0 && (*s = *t) != '\0'; s++, t++, n--) /* copy t */
            ;
    }
}

int main(void)
{
    char x[] = "aro";
    char y[] = "hello";
    strn_cat(x, y, 2);
    printf("%s", x);
    return EXIT_SUCCESS;
}
