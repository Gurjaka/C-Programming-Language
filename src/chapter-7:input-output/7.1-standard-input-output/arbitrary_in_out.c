#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE 80

int main(void)
{
    int c, col = 0;
    while ((c = getchar()) != EOF)
    {
        if (isprint(c))
        {
            putchar(c);
            col++;
        }
        else if (c == '\n')
        {
            printf("\\n");
            col += 2;
        }
        else if (c == '\t')
        {
            printf("\\t");
            col += 2;
        }
        else if (c == '\b')
        {
            printf("\\b");
            col += 2;
        }
        else
        {
            printf("\\x%02X", c); // hex representation
            col += 4;
        }

        if (col >= LINE)
        {
            putchar('\n');
            col = 0;
        }
    }
    return EXIT_SUCCESS;
}
