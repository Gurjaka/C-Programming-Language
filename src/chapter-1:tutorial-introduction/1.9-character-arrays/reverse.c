#include <stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int lineget(char line[], int maxline);
void reverse(char string[]);

/* print the reversed input line */
int main(void)
{
    char line[MAXLINE]; /* current input line */

    while (lineget(line, MAXLINE) > 0)
    {
        reverse(line);
        printf("%s\n", line);
    }
    return 0;
}

/* lineget: read a line into s, return length */
int lineget(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* reverse return reversed line */
void reverse(char string[])
{
    int i = 0, j = 0;

    while (string[i] != '\0')
        ++i;

    --i;

    while (i > j)
    {
        char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
        --i;
        ++j;
    }
}
