#include <stdio.h>
#include <stdlib.h>

/* strcat: concatenate t to end of s; s must be big enough */
void str_cat(char* s, char* t)
{
    for (; *s != '\0'; s++) /* find end of s */
        ;
    for (; (*s = *t) != '\0'; s++, t++) /* copy t */
        ;
}

int main(void)
{
    char x[] = "hello";
    char y[] = "world";
    str_cat(x, y);
    printf("%s", x);
    return EXIT_SUCCESS;
}
