#include <ctype.h>
#include <stdio.h>
#define MAXWORD 100

static char buf = 0;
static int bufp = 0;

int getch(void);
void ungetch(int);
int getword(char *, int);

int main(void) {
  char word[MAXWORD];
  while (getword(word, MAXWORD) != EOF)
    ;
  return 0;
}

/* getch: returns the next character, using a buffer
 * if one was pushed back by ungetch */
int getch(void) {
  if (bufp) {
    bufp = 0;
    return buf;
  }
  return getchar();
}

/*  pushes a character back into a buffer
 *  to be returned by the next getch */
void ungetch(int c) {
  if (bufp)
    printf("ungetch: too many characters\n");
  else {
    buf = c;
    bufp = 1;
  }
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, d;
  char *w = word;

  while (isspace(c = getch()))
    ;

  if (c == EOF)
    return EOF;

  *w++ = c;

  // handle string constants
  if (c == '"') {
    while ((c = getch()) != '"' && c != EOF && --lim > 0)
      *w++ = c;
    if (c == '"' && lim > 0)
      *w++ = c;
    *w = '\0';
    return word[0];
  }

  // handle comments
  if (c == '/' && (d = getch()) == '*') {
    /* Skip block comment */
    while ((c = getch()) != EOF) {
      if (c == '*') {
        if ((c = getch()) == '/')
          break;
        else
          ungetch(c);
      }
    }
    return getword(word, lim);
  } else if (c == '/' && d == '/') {
    while ((c = getch()) != '\n' && c != EOF)
      ;
    return getword(word, lim);
  } else if (c == '/') {
    ungetch(d);
  } else if (d != EOF && d != '/') {
    ungetch(d);
  }

  // handle preprocessor directives
  if (c == '#') {
    while ((c = getch()) != '\n' && c != EOF && --lim > 0)
      *w++ = c;
    *w = '\0';
    return word[0];
  }

  // get regular word (identifier) with underscores
  if (isalpha(c) || c == '_') {
    for (; --lim > 0; w++) {
      if (!isalnum(*w = getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
    }
    *w = '\0';
    return word[0];
  }

  // handle other characters
  *w = '\0';
  return c;
} // might be worth breaking this function into multiple smaller ones
