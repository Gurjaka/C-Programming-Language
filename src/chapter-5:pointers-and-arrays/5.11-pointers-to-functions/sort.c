#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000        /* max #lines to be sorted */
#define MAX_LINE_LENGTH 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quick_sort(void *lineptr[], int left, int right,
                int (*comp)(void *, void *));
int numcmp(const char *, const char *);
double my_atof(const char s[]);
int getLine(char *buffer, int limit);
char *alloc(int length);
void reverse(char *lineptr[], int nlines);
void lower(char *lineptr[], int nlines);
void filter_string(const char *src, char *dest);
int filter_strcmp(const char *s1, const char *s2);
char *get_field(char *line, int field_num);
int field_compare(const char *s1, const char *s2);

unsigned int fstart = 0;
unsigned int fend = 0;
unsigned int numeric = 0;
unsigned int dflag = 0;
unsigned int kflag = 0;
unsigned int nlines;
unsigned int rflag = 0;
unsigned int fflag = 0;

/* sort input lines */
int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        rflag = 1;
        break;
      case 'f':
        fflag = 1;
        break;
      case 'd':
        dflag = 1;
        break;
      case 'k': {
        i++;
        if (i < argc) {
          char *comma = strchr(argv[i], ',');
          if (comma) {
            *comma = '\0';
            fstart = atoi(argv[i]) - 1;
            fend = atoi(comma + 1) - 1;
            if (fstart > fend) {
              unsigned int temp = fstart;
              fstart = fend;
              fend = temp;
            }
          } else {
            fstart = atoi(argv[i]) - 1;
            fend = fstart;
          }
          kflag = 1;
        } else {
          printf("Error: -k requires field specification\n");
          return 1;
        }
        break;
      }
      default:
        printf("Unknown option: %s\n", argv[i]);
        return 1;
      }
    }
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    if (fflag)
      lower(lineptr, nlines);
    if (kflag) {
      quick_sort((void **)lineptr, 0, nlines - 1,
                 (int (*)(void *, void *))field_compare);
    } else {
      quick_sort((void **)lineptr, 0, nlines - 1,
                 (int (*)(void *, void *))(numeric ? numcmp
                                           : dflag ? filter_strcmp
                                                   : strcmp));
    }
    if (rflag) {
      reverse(lineptr, nlines);
    }
    writelines(lineptr, nlines);
    for (int i = 0; i < nlines; i++) {
      free(lineptr[i]);
    }
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* quick_sort: sort v[left]...v[right] into increasing order */
void quick_sort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;
  void swap(void *v[], int, int);
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  quick_sort(v, left, last - 1, comp);
  quick_sort(v, last + 1, right, comp);
}

/* my_atof: convert string to double (handles exponents like 1.23e-4) */
double my_atof(const char s[]) {
  double val, power;
  int i, sign, exp_sign, exp;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }
  if (s[i] == 'e' || s[i] == 'E') {
    i++;
    exp_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (exp = 0; isdigit(s[i]); i++)
      exp = 10 * exp + (s[i] - '0');
    val *= pow(10.0, exp_sign * exp);
  }
  return sign * val / power;
}

/* numcmp: compare strings as numbers using my_atof for conversion */
int numcmp(const char *s1, const char *s2) {
  double v1 = my_atof(s1);
  double v2 = my_atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

/* swap: exchange two pointers in a generic array */
void swap(void *v[], int i, int j) {
  void *temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* reverse: reverse order of lines in the array */
void reverse(char *lineptr[], int nlines) {
  for (int i = 0, j = nlines - 1; i < j; i++, j--) {
    char *temp = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = temp;
  }
}

/* getLine: read a line into buffer, return length */
int getLine(char *buffer, int limit) {
  int c, i = 0;
  while (i < limit - 1 && (c = getchar()) != EOF && c != '\n')
    buffer[i++] = c;
  if (c == '\n')
    buffer[i++] = c;
  buffer[i] = '\0';
  return i;
}

/* alloc: allocate memory block of given length (string) */
char *alloc(int length) { return (char *)malloc(length * sizeof(char)); }

/* readlines: read all input lines into lineptr array */
int readlines(char *lineptr[], int maxlines) {
  int len, nlines = 0;
  char line[MAX_LINE_LENGTH], *p;
  while ((len = getLine(line, MAX_LINE_LENGTH))) {
    if (nlines >= maxlines || (p = alloc(len + 1)) == NULL)
      return -1;
    line[len] = '\0';
    strcpy(p, line);
    lineptr[nlines++] = p;
  }
  return nlines;
}

/* writelines: print all lines in the array */
void writelines(char *lineptr[], int nlines) {
  for (int i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* lower: convert all characters in lines to lowercase */
void lower(char *lineptr[], int nlines) {
  for (int i = 0; i < nlines; ++i)
    for (int j = 0; lineptr[i][j]; ++j)
      lineptr[i][j] = tolower(lineptr[i][j]);
}

/* filter_string: copy only alphanumeric chars and spaces from src to dest */
void filter_string(const char *src, char *dest) {
  while (*src) {
    if (isalnum(*src) || *src == ' ')
      *dest++ = *src;
    src++;
  }
  *dest = '\0';
}

/* filter_strcmp: compare strings after filtering non-alphanumeric chars */
int filter_strcmp(const char *s1, const char *s2) {
  char f1[MAX_LINE_LENGTH], f2[MAX_LINE_LENGTH];
  filter_string(s1, f1);
  filter_string(s2, f2);
  return strcmp(f1, f2);
}

/* get_field: extract the Nth field (whitespace-separated) from line */
char *get_field(char *line, int field_num) {
  static char field[MAX_LINE_LENGTH];
  char *p = line;
  int current_field = 0;
  while (current_field < field_num) {
    while (*p && isspace(*p))
      p++;
    if (!*p) {
      field[0] = '\0';
      return field;
    }
    while (*p && !isspace(*p))
      p++;
    current_field++;
  }
  while (*p && isspace(*p))
    p++;
  int i = 0;
  while (*p && !isspace(*p) && i < MAX_LINE_LENGTH - 1)
    field[i++] = *p++;
  field[i] = '\0';
  return field;
}

/* field_compare: compare lines based on fields specified by -k option */
int field_compare(const char *s1, const char *s2) {
  char f1[MAX_LINE_LENGTH], f2[MAX_LINE_LENGTH];
  for (int i = fstart; i <= fend; i++) {
    strcpy(f1, get_field((char *)s1, i));
    strcpy(f2, get_field((char *)s2, i));
    int result;
    if (numeric)
      result = numcmp(f1, f2);
    else if (dflag)
      result = filter_strcmp(f1, f2);
    else
      result = strcmp(f1, f2);
    if (result != 0)
      return result;
  }
  return 0;
}
