#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

struct winsize window;
void display_file(char*, char*, int);
ssize_t getline_custom(int, char *, size_t);

int main(int argc, char* argv[])
{
    if (argc == 1) {
        fprintf(stderr, "%s: expects at least one file like '%s file.txt'\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

    for (int i = 1; i < argc; i++) {
        display_file(argv[0], argv[i], i);
    }

    return EXIT_SUCCESS;
}

void display_file(char* argv, char* fname, int page)
{
    // define mandatory variables
    int file;
    char line[BUFSIZ];
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
    if ((file = open(fname, O_RDONLY)) < 0) {
        fprintf(stderr, "%s: Couldn't load file '%s'.\n", argv, fname);
        return;
    }

    linelen = 2;

    // find length of max line
    char c;
    int n;
    while ((n = read(file, &c, 1)) > 0)
        if (c == '\n')
            linecount++;

    // Calculate digits needed for line numbers
    linelen = 1;
    while (linecount >= 10) {
        linelen++;
        linecount /= 10;
    }

    printf("\033[0m%s\033[0m\n", minus);
    printf("\033[0m%*s\033[0m  | File: \033[0m%s\033[0m\n", linelen, "", fname);
    printf("\033[0m%*s\033[0m  | Page: \033[0m%d\033[0m\n", linelen, "", page);
    printf("\033[0m%s\033[0m\n", minus);

    // Reset file pointer to beginning for reading lines
    if (lseek(file, 0, SEEK_SET) == -1) {
        fprintf(stderr, "Couldn't reset file pointer to beginning for reading lines.\n");
        exit(EXIT_FAILURE);
    }

    // print each line with counter
    while (getline_custom(file, line, BUFSIZ) > 0) {
        printf("\033[0m%*d  |\033[0m %s", linelen, current_line, line);
        current_line++;
    }
    printf("\033[0m%s\033[0m\n", minus);
    return;
}

ssize_t getline_custom(int fd, char *buf, size_t maxlen) {
    ssize_t n = 0;
    char c;
    while (n < maxlen - 1) {
        ssize_t r = read(fd, &c, 1);
        if (r <= 0) {
            break;
        }
        buf[n++] = c;
        if (c == '\n') break;
    }
    if (n == 0) return -1;
    buf[n] = '\0';
    return n;
}
