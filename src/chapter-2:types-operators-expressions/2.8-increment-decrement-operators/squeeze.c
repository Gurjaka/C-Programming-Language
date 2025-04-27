#include <stdio.h>
#include <stdlib.h>

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

int main(void)
{
    char s[1000] = "tutorial";
    squeeze(s, 'u');
    printf("%s\n", s);

    return EXIT_SUCCESS;
}
