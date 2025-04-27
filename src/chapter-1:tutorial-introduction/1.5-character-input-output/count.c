#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nl, bl, tab = 0;
    int c;

    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
            case '\n':
                ++nl;
                break;
            case ' ':
                ++bl;
                break;
            case '\t':
                ++tab;
                break;
        }
    }

    printf("Blank: %d\nTabs: %d\nNewlines: %d", bl, tab, nl);

    return EXIT_SUCCESS;
}
