#include <ctype.h>
#include <stdio.h>

#define NUMBER '0'
#define VARIABLE '1'

static char buf = 0;
static int bufp = 0;

int getch(void) {
  if (bufp) {
    bufp = 0;
    return buf;
  }
  return getchar();
}

int getop(char s[]) {
  static int last_c = 0;
  int i, c;

  if (last_c) {
    c = last_c;
    last_c = 0;
  } else {
    c = getch();
  }

  while (c == ' ' || c == '\t')
    c = getch();

  s[0] = c;
  s[1] = '\0';

  if (islower(c)) {
    return VARIABLE;
  }
  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }

  i = 0;

  if (c == '-') {
    int next = getch();
    if (!isdigit(next) && next != '.') {
      last_c = next;
      return '-';
    }
    s[++i] = c = next;
  }

  while (isdigit(s[++i] = c = getch()))
    ;

  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;

  s[i] = '\0';

  if (c != EOF) {
    last_c = c;
  }

  return NUMBER;
}
