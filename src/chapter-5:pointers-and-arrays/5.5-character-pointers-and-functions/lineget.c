#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000

char line[MAXLINE];

/* lineget: spcialized version */
int lineget(void)
{
    char* i = line;

    for (; i < line + MAXLINE - 1 && (*i = getchar()) != EOF && *i != '\n'; i++)
        ;

    *i = '\0';

    return i - line;
}

int main(void)
{
    lineget();
    printf("%s", line);
    return EXIT_SUCCESS;
}
