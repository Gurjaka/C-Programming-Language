#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE '1'
#define MAXVAL 100
#define BUFSIZE 100
#define VAR_COUNT 26

int sp = 0;
double val[MAXVAL];
double variables[VAR_COUNT];
double last_printed = 0.0;

char buf = 0;
int bufp = 0;

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getch(void) {
  if (bufp) {
    bufp = 0;
    return buf;
  }
  return getchar();
}

void ungetch(int c) {
  if (bufp)
    printf("ungetch: too many characters\n");
  else {
    buf = c;
    bufp = 1;
  }
}

void ungets(char s[]) {
  int len = strlen(s);
  while (len > 0)
    ungetch(s[--len]);
}

int getop(char s[]) {
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';

  if (islower(c)) {
    return VARIABLE;
  }
  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  i = 0;
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;

  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  int var_index;

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case VARIABLE:
      var_index = s[0] - 'a';
      push(variables[var_index]);
      break;
    case '=':
      pop();
      variables[var_index] = pop();
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        push(fmod(pop(), op2));
      else
        printf("error: zero divisor\n");
      break;
    case 's':
      push(sin(pop()));
      break;
    case 'e':
      push(exp(pop()));
      break;
    case 'p':
      op2 = pop();
      push(pow(pop(), op2));
      break;
    case '\n':
      last_printed = pop();
      printf("\t%.8g\n", last_printed);
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return EXIT_SUCCESS;
}
