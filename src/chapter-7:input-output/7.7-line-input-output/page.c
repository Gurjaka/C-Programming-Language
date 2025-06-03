#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct winsize window;
void display_file(char*, char*, int);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "%s: expects at least one file like '%s file.txt'\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

    for (int i = 1; i < argc; i++)
    {
        display_file(argv[0], argv[i], i);
    }

    return EXIT_SUCCESS;
}

void display_file(char* argv, char* fname, int page)
{
    // define mandatory variables
    FILE* fptr;
    char* line = NULL;
    int linecount = 0;
    int linelen = 0;
    size_t maxline = 0;
    int current_line = 1;

    // aesthetic wise variables
    int width = window.ws_col;
    if (width <= 0)
        width = 80; // fallback

    char minus[width + 1];
    for (int i = 0; i < width; i++)
        minus[i] = '-';
    minus[width] = '\0';

    // check if file is correct
    if ((fptr = fopen(fname, "r")) == NULL)
    {
        linelen = 2;
        goto head;
    }

    // find length of max line
    char c;
    while ((c = fgetc(fptr)) != EOF)
    {
        if (c == '\n')
            linecount++;
    }

    // Calculate digits needed for line numbers
    int temp_count = linecount;
    linelen = 1;
    while (temp_count >= 10)
    {
        linelen++;
        temp_count /= 10;
    }

    goto head;

print_file:
    // Reset file pointer to beginning for reading lines
    rewind(fptr);
    // print each line with counter
    while (getline(&line, &maxline, fptr) > 0)
    {
        printf("\033[0m%*d  |\033[0m %s", linelen, current_line, line);
        current_line++;
    }
    printf("\033[0m%s\033[0m\n", minus);
    goto cleanup;

// print head of file
head:
    printf("\033[0m%s\033[0m\n", minus);
    printf("\033[0m%*s\033[0m  | File: \033[0m%s\033[0m\n", linelen, "", fname);
    printf("\033[0m%*s\033[0m  | Page: \033[0m%d\033[0m\n", linelen, "", page);
    printf("\033[0m%s\033[0m\n", minus);
    if (fptr == NULL)
    {
        fprintf(stderr, "%s: Couldn't load file '%s'.\n", argv, fname);
        return;
    }
    goto print_file;

cleanup:
    if (line)
        free(line);
    if (fptr)
        fclose(fptr);
    return;
}
