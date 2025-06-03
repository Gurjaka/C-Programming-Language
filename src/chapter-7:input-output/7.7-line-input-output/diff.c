#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        // If no search flags are provided, show usage
        fprintf(stderr, "Usage: %s [OPTIONS]\n", argv[0]);
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "  -c <file1>        File to compare\n");
        fprintf(stderr, "  -f <file2>        File to compare\n");
        return EXIT_FAILURE;
    }

    bool cflag = 0;
    bool fflag = 0;
    FILE* fp1;
    FILE* fp2;
    char* file1;
    char* file2;
    char line1[MAXLINE];
    char line2[MAXLINE];
    int count = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
                case 'c':
                    i++;
                    if (i < argc)
                    {
                        cflag = 1;
                        file1 = strdup(argv[i]);
                    }
                    break;
                case 'f':
                    i++;
                    if (i < argc)
                    {
                        fflag = 1;
                        file2 = strdup(argv[i]);
                    }
                    break;
                default:
                    fprintf(stderr, "Unknown flag: -%c\n", argv[i][1]);
                    return EXIT_FAILURE;
            }
        }
    }

    if (!cflag || !fflag)
    {
        fprintf(stderr, "%s: program expects two arguments -c and -f\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp1 = fopen(file1, "r")) == NULL || (fp2 = fopen(file2, "r")) == NULL)
    {
        fprintf(stderr, "%s: failed to open file \"%s\"\n", argv[0], fp1 != NULL ? file2 : file1);
        exit(EXIT_FAILURE);
    }

    do
    {
        count++;
        fgets(line1, MAXLINE, fp1);
        fgets(line2, MAXLINE, fp2);
        if (strcmp(line1, line2))
        {
            printf("%s: diff found, on line %d:\n", argv[0], count);
            printf("%s\n", line2);
            exit(EXIT_SUCCESS);
        }
    } while (ferror(fp1) == 0 && ferror(fp2) == 0);

    printf("%s: diff not found, exitting.\n", argv[0]);
    fclose(fp1);
    fclose(fp2);

    return EXIT_SUCCESS;
}
