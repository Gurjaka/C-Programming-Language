#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100

int getword(char*, int);
struct tree* talloc(void);
struct tree* addtree(struct tree*, char*);
void free_tree(struct tree*);
int compare_count(const void*, const void*);
void collect_nodes(struct tree*);

struct tree
{
    char* word;
    int count;
    struct tree* left;
    struct tree* right;
};

struct tree* root;
struct tree** nodes = NULL;

int node_index = 0;
int node_capacity = 0;

int main(void)
{
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
    {
        root = addtree(root, word);
    }

    collect_nodes(root);
    qsort(nodes, node_index, sizeof(struct tree*), compare_count);

    for (int i = 0; i < node_index; i++)
    {
        printf("%4d %s\n", nodes[i]->count, nodes[i]->word);
    }

    free_tree(root);
    free(nodes);

    return 0;
}

/* getword: get next word or character from input */
int getword(char* word, int lim)
{
    int c, d;
    char* w = word;

    while (isspace(c = getchar()))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;

    // get regular word (identifier) with underscores
    if (isalpha(c) || c == '_')
    {
        for (; --lim > 0; w++)
        {
            if (!isalnum(*w = getchar()) && *w != '_')
            {
                break;
            }
        }
        *w = '\0';
        return word[0];
    }

    // handle other characters
    *w = '\0';
    return c;
}

// talloc: make a tree
struct tree* talloc(void)
{
    return (struct tree*) malloc(sizeof(struct tree));
}

// addtree:  add a node with w, at or below p
struct tree* addtree(struct tree* p, char* w)
{
    int cond;

    if (p == NULL)
    {                 /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;    /* repeated word */
    else if (cond < 0) /* less than into left subtree */
        p->left = addtree(p->left, w);
    else /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}

// compare_count: sort tree nodes by frequency (descending)
int compare_count(const void* a, const void* b)
{
    const struct tree* groupA = *(const struct tree**) a;
    const struct tree* groupB = *(const struct tree**) b;
    return groupB->count - groupA->count; // descending
}

void collect_nodes(struct tree* p)
{
    if (p != NULL)
    {
        collect_nodes(p->left);

        if (node_index >= node_capacity)
        {
            node_capacity = node_capacity == 0 ? 16 : node_capacity * 2;
            nodes = realloc(nodes, node_capacity * sizeof(struct tree*));
            if (nodes == NULL)
            {
                fprintf(stderr, "error: out of memory, couldn't allocate nodes array");
                exit(1);
            }
        }

        nodes[node_index++] = p;

        collect_nodes(p->right);
    }
}

// free_tree: clean unused memory tree
void free_tree(struct tree* p)
{
    if (p != NULL)
    {
        free_tree(p->left);
        free_tree(p->right);
        free(p->word);
        free(p);
    }
}
