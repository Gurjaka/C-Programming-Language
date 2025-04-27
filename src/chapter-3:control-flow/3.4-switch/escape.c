#include <stdio.h>
#include <stdlib.h>
#define LENGTH 1000

void escape(char s[], char t[])
{
    int i, j;
    for (i = 0, j = 0; t[i] != '\0' && j < LENGTH - 1; ++i)
    {
        switch (t[i])
        {
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
};

int main(void)
{
    char s[LENGTH];
    char t[] = "Hello\tWorld\n";
    escape(s, t);
    printf("%s\n", s);
    return EXIT_SUCCESS;
}
