#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int tabstop;
char line[MAXLINE];
int lineget(void);
void detab(void);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("No tabsize provided, defaulting to 8");
    tabstop = 8;
  } else
    tabstop = atoi(argv[1]);

  while (lineget() > 0) {
    detab();
    printf("%s\n", line);
  }

  return 0;
}

int lineget(void) {
  int c, i;

  for (i = 0; i < MAXLINE && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;

  if (c == '\n') {
    line[i] = c;
    ++i;
  }

  line[i] = '\0';
  return i;
}

void detab(void) {
  int i = 0, j = 0;
  int mod = 0;
  char temp[MAXLINE];

  while (line[i] != '\0') {
    if (line[i] == '\t') {
      int spaces_to_add = tabstop - j % tabstop;

      for (int k = 0; k < spaces_to_add; ++k) {
        if (j < MAXLINE - 1)
          temp[j++] = ' ';
      }
    } else {
      temp[j++] = line[i];
    }
    ++i;
  }

  temp[j] = '\0';
  for (int i = 0; temp[i] != '\0'; ++i) {
    line[i] = temp[i];
  }
}
