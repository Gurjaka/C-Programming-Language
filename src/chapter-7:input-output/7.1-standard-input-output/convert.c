#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (!argc)
        return EXIT_FAILURE;

    int (*convert)(int) = NULL;
    if (strstr(argv[0], "upper"))
    {
        convert = toupper;
    }
    else if (strstr(argv[0], "lower"))
    {
        convert = tolower;
    }

    int c;

    while ((c = getchar()) != EOF)
    {
        putchar(convert(c));
    }
    return EXIT_SUCCESS;
}
