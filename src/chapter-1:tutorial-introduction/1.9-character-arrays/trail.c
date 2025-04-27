#include <stdio.h>
#define MAXLINE 1000 /* maximum input line lenght */

int lineget(char line[], int maxline);
int rem_blank(char line[]);

/* print the longest input line */
int main(void)
{
    char line[MAXLINE]; /* current input line */

    while (lineget(line, MAXLINE) > 0)
        if (rem_blank(line) > 0)
            printf("%s\n", line);
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

int rem_blank(char line[])
{
    int i = 0;
    while (line[i] != '\0')
        ++i;

    --i;

    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        --i;

    line[i + 1] = '\0';

    return i + 1;
}
