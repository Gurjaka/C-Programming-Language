#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define MAXGROUPS 100

// clang-format off
const char *noise_words[] = {
    "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
    "has", "he", "in", "is", "it", "its", "of", "on", "that", "the",
    "to", "was", "were", "will", "with", NULL
};
// clang-format on

struct tree {
  char *word;
  int count;
  int *lines;
  int line_count;
  int line_capacity;
  struct tree *left;
  struct tree *right;
};

struct group {
  char prefix[MAXWORD];
  struct tree *root;
};

struct group groups[MAXGROUPS];

void tree_print(struct tree *);
int getword(FILE *, char *, int);
struct tree *talloc(void);
struct tree *addtree(struct tree *, char *);
void add_line(struct tree *, int);
int compare_groups(const void *, const void *);
void free_tree(struct tree *);

int group_count = 0;
int line_count = 1;

// main app logic
int main(int argc, char *argv[]) {
  char *file_name = NULL;

  // handle command line args
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '\0') {

      switch (argv[i][1]) {
      // read file name with f argument
      case 'f': {
        if (i + 1 < argc) {
          file_name = malloc(strlen(argv[i + 1]) + 1);
          if (file_name != NULL) {
            strcpy(file_name, argv[++i]);
          }
        }
        break;
      }
      // handle incorrect arguments
      default: {
        fprintf(stderr, "Unknown option: %s\n", argv[i]);
        return 1;
      }
      }
    }
  }

  // main logic
  FILE *fileptr;
  fileptr = fopen(file_name, "r");
  free(file_name);

  if (fileptr == NULL) {
    fprintf(stderr, "Error: couldn't open file.\n");
    return 1;
  }

  char word[MAXWORD];
  int group_index;

  while (getword(fileptr, word, MAXWORD) != EOF)
    if (isalpha(word[0])) {
      group_index = -1;
      for (int i = 0; i < group_count; ++i) {
        if (strncmp(groups[i].prefix, word, MAXWORD) == 0) {
          group_index = i;
          break;
        }
      }

      if (group_index == -1 && group_count < MAXGROUPS) {
        group_index = group_count++;
        strncpy(groups[group_index].prefix, word, MAXWORD);
        groups[group_index].prefix[MAXWORD - 1] = '\0';
        groups[group_index].root = NULL;
      }

      groups[group_index].root = addtree(groups[group_index].root, word);
    }

  fclose(fileptr);

  qsort(groups, group_count, sizeof(groups[0]), compare_groups);

  for (int i = 0; i < group_count; ++i) {
    if (groups[i].root) {
      printf("Group prefix: '%s'\n", groups[i].prefix);
      tree_print(groups[i].root);
      printf("\n"); // Add separation between groups
    }
  }

  for (int i = 0; i < group_count; ++i) {
    if (groups[i].root) {
      free_tree(groups[i].root);
    }
  }
  return 0;
}

// getword: reads words from passed file
int getword(FILE *fileptr, char *word, int lim) {
  int c, d;
  char *w = word;

  while (isspace(c = fgetc(fileptr))) {
    // handle new line
    if (c == '\n') {
      line_count++;
    };
  }

  if (c == EOF)
    return EOF;

  *w++ = c;

  // handle string constants
  if (c == '"') {
    while ((c = fgetc(fileptr)) != '"' && c != EOF && --lim > 0)
      *w++ = c;
    if (c == '"' && lim > 0)
      *w++ = c;
    *w = '\0';
    return word[0];
  }

  // handle comments
  if (c == '/' && (d = fgetc(fileptr)) == '*') {
    /* Skip block comment */
    while ((c = fgetc(fileptr)) != EOF) {
      if (c == '*') {
        if ((c = fgetc(fileptr)) == '/')
          break;
      }
    }
    return getword(fileptr, word, lim);
  } else if (c == '/' && d == '/') {
    while ((c = fgetc(fileptr)) != '\n' && c != EOF)
      ;
    return getword(fileptr, word, lim);
  }

  // get regular word (identifier) with underscores
  if (isalpha(c) || c == '_') {
    for (; --lim > 0; w++) {
      if (!isalnum(*w = fgetc(fileptr)) && *w != '_') {
        break;
      }
    }
    *w = '\0';

    // handle noisy words
    for (int i = 0; noise_words[i] != NULL; ++i) {
      if (strcmp(word, noise_words[i]) == 0)
        return '\0';
    }

    return word[0];
  }

  // handle other characters
  *w = '\0';
  return c;
} // might be worth breaking this function into multiple smaller ones

// tree_print:  in-order print of tree p
void tree_print(struct tree *p) {
  if (p != NULL) {
    tree_print(p->left);
    printf("%4d \"%s\" on lines ", p->count, p->word);
    for (int i = 0; i < p->line_count; ++i) {
      printf("%d", p->lines[i]);
      if (i < p->line_count - 1) {
        printf(", ");
      } else {
        printf("\n");
      }
    }
    tree_print(p->right);
  }
}

// talloc: make a tree
struct tree *talloc(void) { return (struct tree *)malloc(sizeof(struct tree)); }

// addtree:  add a node with w, at or below p
struct tree *addtree(struct tree *p, char *w) {
  int cond;

  if (p == NULL) { /* a new word has arrived */
    p = talloc();  /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->lines = NULL;
    p->line_count = 0;
    p->line_capacity = 0;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++; /* repeated word */
    add_line(p, line_count);
  } else if (cond < 0) /* less than into left subtree */
    p->left = addtree(p->left, w);
  else /* greater than into right subtree */
    p->right = addtree(p->right, w);
  return p;
}

void add_line(struct tree *p, int line) {
  // check if line already added
  for (int i = 0; i < p->line_count; ++i) {
    if (p->lines[i] == line)
      return; // avoid duplicates
  }

  if (p->line_count == p->line_capacity) {
    p->line_capacity = p->line_capacity ? p->line_capacity * 2 : 4;
    p->lines = realloc(p->lines, p->line_capacity * sizeof(int));
    if (!p->lines) {
      fprintf(stderr, "Out of memory allocating lines\n");
      exit(1);
    }
  }

  p->lines[p->line_count++] = line;
}

// compare_groups: compares groups for alphabetical sorting
int compare_groups(const void *a, const void *b) {
  return strcasecmp(((struct group *)a)->prefix, ((struct group *)b)->prefix);
}

// free_tree: clean unused memory tree
void free_tree(struct tree *p) {
  if (p != NULL) {
    free_tree(p->left);
    free_tree(p->right);
    free(p->word);
    free(p->lines);
    free(p);
  }
}
