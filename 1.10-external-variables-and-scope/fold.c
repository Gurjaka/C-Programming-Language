#include <stdio.h>
#define MAXLINE 1000

int column;
char line[MAXLINE];
int lineget(void);
void split(void);

int main(void) {
  printf("Enter column (n): ");
  scanf("%d", &column);

  while (lineget() > 0) {
    split();
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

void split(void) {
  int i = 0, j = 0, last_index = 0;
  int space_index = -1;
  char temp[MAXLINE];

  while (line[i] != '\0') {
    if (i - last_index == column) {
      int split_index = (space_index != -1) ? space_index : i;

      for (int k = last_index; k < split_index; ++k) {
        temp[j++] = line[k];
      }

      temp[j++] = '\n';

      last_index = (space_index != -1) ? space_index + 1 : i;
      space_index = -1;
    }

    if (line[i] == ' ')
      space_index = i;

    ++i;
  }

  for (int k = last_index; k < i; ++k) {
    temp[j++] = line[k];
  }

  temp[j] = '\0';

  for (i = 0; temp[i] != '\0'; ++i)
    line[i] = temp[i];

  line[i] = '\0';
}
