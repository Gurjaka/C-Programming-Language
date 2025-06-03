#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* find: print lines that match pattern from 1st arg */
int main(int argc, char* argv[])
{
    if (argc == 1)
        printf("Usage: find -f -x -n pattern\n");

    bool number = false;
    bool fflag = false;
    char* except = NULL;
    char* filename = NULL;
    char* line = NULL;
    FILE* fp = NULL;
    size_t maxline = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
                case 'n':
                    number = true;
                    break;
                case 'x':
                    i++;
                    except = argv[i];
                    break;
                case 'f':
                    i++;
                    if (i < argc)
                    {
                        fflag = true;
                        filename = strdup(argv[i]);
                    }
                    break;
                default:
                    fprintf(stderr, "%s: Unknown flag -%c\n", argv[0], argv[i][1]);
                    return EXIT_FAILURE;
            }
        }
    }

    if (!fflag)
        fp = stdin;
    else
        fp = fopen(filename, "r");

    long int linenum = 0;

    while (getline(&line, &maxline, fp) > 0)
    {
        linenum++;
        if ((strstr(line, except) != NULL) != 1)
        {
            if (number)
            {
                printf("%ld ", linenum);
            }

            printf("%s", line);
        }
    }

    return EXIT_SUCCESS;
}
