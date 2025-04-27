#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101

struct nlist
{                       // table entry:
    struct nlist* next; // next entry in chain
    char* name;         // defined name
    char* defn;         // replacement text
};
static struct nlist* hashtab[HASHSIZE]; // pointer table

unsigned hash(char*);
struct nlist* lookup(char*);
struct nlist* install(char*, char*);
void undef(char*);

int main(void)
{
    struct nlist* test = install("example", "gamarjoba");

    if (test == NULL)
    {
        printf("Installation failed!\n");
        return 1;
    }

    test = lookup("example");
    if (test == NULL)
    {
        printf("\nCouldn't find definition of name\n");
        return 1;
    }

    printf("Name: %s\nTest: %s\n", test->name, test->defn);

    undef("example");
    test = lookup("example");

    if (test == NULL)
    {
        printf("\nremoved definition of name\n");
        return 0;
    }

    // This point will not be reached if the name was removed successfully
    printf("Name: %s\nTest: %s\n", test->name, test->defn);
    return 0;
}

// hash:  form hash value for string s
unsigned hash(char* s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

// lookup:  look for s in hashtab
struct nlist* lookup(char* s)
{
    struct nlist* np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; // found
    return NULL;       // not found
}

// install:  put (name, defn) in hashtab
struct nlist* install(char* name, char* defn)
{
    struct nlist* np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)
    { // not found
        np = (struct nlist*) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else                        // already there
        free((void*) np->defn); // free previous defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

// undef: Removes the definition of `name` from the symbol table.
void undef(char* s)
{
    unsigned hashval = hash(s);
    struct nlist* np = hashtab[hashval];
    struct nlist* prev = NULL;

    while (np != NULL)
    {
        if (strcmp(s, np->name) == 0)
        {
            if (prev == NULL)
            {
                hashtab[hashval] = np->next; // update the head of the chain
            }
            else
            {
                prev->next = np->next; // bypass the current entry
            }
            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
        prev = np;
        np = np->next;
    }
}
