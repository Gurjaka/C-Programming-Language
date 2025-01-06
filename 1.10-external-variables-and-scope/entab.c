#include <stdio.h>
#define MAXLINE 1000

int tabstop;
char line[MAXLINE];
int lineget(void);
void entab(void);

int main(void) {
  printf("Enter tab stop spacing: ");
  scanf("%d", &tabstop);

  while (lineget() > 0) {
    entab();
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

void entab(void) {
  int i = 0, j = 0;
  char temp[MAXLINE];

  while (line[i] != '\0') {
    int space_count = 0;

    while (line[i] == ' ') {
      ++space_count;
      ++i;
    }

    if (space_count > 0) {
      for (int t = 0; t < space_count / tabstop; ++t) {
        if (j < MAXLINE - 1)
          temp[j++] = '\t';
      }

      for (int s = 0; s < space_count % tabstop; ++s) {
        if (j < MAXLINE - 1)
          temp[j++] = ' ';
      }
    } else
      temp[j++] = line[i++];
  }

  temp[j] = '\0';

  for (int i = 0; temp[i] != '\0'; ++i)
    line[i] = temp[i];
}
