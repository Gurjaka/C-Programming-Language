#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int tabstop;
int offset;
char line[MAXLINE];
int lineget(void);
void entab(void);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("No tabsize provided, defaulting to 8\n");
        tabstop = 8;
        offset = 0;
    }
    else
    {
        char* shorthand = argv[1];
        char* plus = strchr(shorthand, '+');
        if (plus)
        {
            *plus = '\0';
            tabstop = atoi(shorthand);
            offset = atoi(plus + 1);
        }
        else
        {
            tabstop = atoi(shorthand);
            offset = 0;
        }
    }

    while (lineget() > 0)
    {
        entab();
        printf("%s\n", line);
    }

    return EXIT_SUCCESS;
}

int lineget(void)
{
    int c, i;

    for (i = 0; i < MAXLINE && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;

    if (c == '\n')
    {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i;
}

void entab(void)
{
    int i = 0, j = 0;
    char temp[MAXLINE];

    while (line[i] != '\0')
    {
        int space_count = 0;

        while (line[i] == ' ')
        {
            ++space_count;
            ++i;
        }

        if (space_count > 0)
        {
            int pos = j + offset;
            int tabs = (pos + space_count) / tabstop - pos / tabstop;
            for (int t = 0; t < tabs; ++t)
            {
                if (j < MAXLINE - 1)
                    temp[j++] = '\t';
            }

            for (int s = 0; s < (pos + space_count) % tabstop - pos % tabstop; ++s)
            {
                if (j < MAXLINE - 1)
                    temp[j++] = ' ';
            }
        }
        else
            temp[j++] = line[i++];
    }

    temp[j] = '\0';

    for (int i = 0; temp[i] != '\0'; ++i)
        line[i] = temp[i];
}
