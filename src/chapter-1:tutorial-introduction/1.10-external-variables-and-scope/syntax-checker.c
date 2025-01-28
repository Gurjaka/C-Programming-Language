#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STACK 1000

int add_elem(char elements[MAX_STACK], int *count, char c);
char rem_elem(int *count, char elements[MAX_STACK]);
bool is_pair(char open, char close);

int main(void) {
  char elements[MAX_STACK];
  char last;
  int count = -1;
  char path[PATH_MAX];

  printf("File path: ");
  fflush(stdout);

  ssize_t length = read(STDIN_FILENO, path, sizeof path - 1);

  if (length < 0)
    return EXIT_FAILURE;

  if (path[length - 1] == '\n')
    path[length - 1] = '\0';

  FILE *file = fopen(path, "r");

  if (file == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  int in_comment = false;
  int in_string = false;
  int escape = false;
  char c;

  while ((c = fgetc(file)) != EOF) {

    if (escape) {
      escape = false;
      continue;
    }

    if (c == '\\') {
      escape = true;
      continue;
    }

    if (c == '\'' || c == '"') {
      in_string = !in_string;
      continue;
    }

    if (in_string)
      continue;

    if (!in_comment && c == '/' && (c = fgetc(file)) == '*') {
      in_comment = true;
      continue;
    } else if (in_comment && c == '*' && (c = fgetc(file)) == '/') {
      in_comment = false;
      continue;
    } else if (!in_comment && c == '/' && (c = fgetc(file)) == '/') {
      continue;
    }
    if (c == '(' || c == '[' || c == '{') {
      if (add_elem(elements, &count, c) != EXIT_SUCCESS) {
        fclose(file);
        return EXIT_FAILURE;
      }
    } else if (c == ')' || c == ']' || c == '}') {
      last = rem_elem(&count, elements);

      if (!is_pair(last, c)) {
        printf("Syntax error: unmatched '%c'\n", c);
        fclose(file);
        return EXIT_FAILURE;
      }
    }
  }

  fclose(file);

  if (count >= 0) {
    printf("Syntax error: unmatched '%c'\n", elements[count]);
    return EXIT_FAILURE;
  }

  printf("No syntax errors found\n");
  return EXIT_SUCCESS;
}

int add_elem(char elements[MAX_STACK], int *count, char c) {
  if (*count >= MAX_STACK - 1) {
    printf("Error: Out of bounds, overflow\n");
    return EXIT_FAILURE;
  }
  elements[++(*count)] = c;
  return EXIT_SUCCESS;
}

char rem_elem(int *count, char elements[MAX_STACK]) {
  if (*count < 0) {
    printf("Error: Out of bounds, underflow\n");
    return '\0';
  }
  return elements[(*count)--];
}

bool is_pair(char open, char close) {
  return (open == '(' && close == ')') || (open == '[' && close == ']') ||
         (open == '{' && close == '}');
}
