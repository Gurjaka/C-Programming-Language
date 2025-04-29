#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100
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
int getch(void);
void ungetch(int);
int getword(char*, int);

static int buf = 0;
static int bufp = 0;

int main(void)
{
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
    {
        if (strcmp(word, "#define") == 0)
        {
            char name[MAXWORD], defn[MAXWORD];

            // Get the name
            getword(name, MAXWORD);

            // Get the definition
            getword(defn, MAXWORD);

            struct nlist* test = install(name, defn);
            if (test == NULL)
            {
                printf("Installation failed!\n");
                return EXIT_FAILURE;
            }

            printf("Installed: %s = %s\n", name, defn);
        }
        /* Only use this for debugging if needed
        else
        {
            printf("I didn't reach installation phase\n");
        }
        */
    }

    // Try to look up the installed definition
    char* lookupName = "example";
    printf("\nLooking up: %s\n", lookupName);
    struct nlist* test = lookup(lookupName);
    if (test == NULL)
    {
        printf("Couldn't find definition of '%s'\n", lookupName);
        return EXIT_FAILURE;
    }

    printf("Found - Name: %s, Definition: %s\n", test->name, test->defn);

    return EXIT_SUCCESS;
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

/* getch: returns the next character, using a buffer
 * if one was pushed back by ungetch */
int getch(void)
{
    if (bufp)
    {
        bufp = 0;
        return buf;
    }
    return getchar();
}

/*  pushes a character back into a buffer
 *  to be returned by the next getch */
void ungetch(int c)
{
    if (bufp)
        printf("ungetch: too many characters\n");
    else
    {
        buf = c;
        bufp = 1;
    }
}

// getword: get next word or character from input
int getword(char* arr, int lim)
{
    int c;
    char* w = arr;

    // Skip leading whitespace
    while (isspace(c = getch()))
        ;

    if (c == EOF)
    {
        *w = '\0';
        return EOF;
    }

    // Handle #define directive specially
    if (c == '#')
    {
        *w++ = c;
        // Get the rest of the directive
        while (--lim > 0 && !isspace(c = getch()) && c != EOF)
            *w++ = c;

        // Put back the whitespace character
        if (c != EOF)
            ungetch(c);

        *w = '\0';
        return arr[0];
    }

    // Handle other words
    *w++ = c;

    if (isalpha(c) || c == '_')
    {
        // Get identifier (variable name or similar)
        for (; --lim > 0; w++)
        {
            c = getch();
            if (!isalnum(c) && c != '_')
            {
                ungetch(c);
                break;
            }
            *w = c;
        }
    }
    else if (c == '"')
    {
        // Handle string constants
        while (--lim > 0 && (c = getch()) != '"' && c != EOF)
            *w++ = c;
        if (c == '"')
            *w++ = c;
    }
    else if (c == '/' && (c = getch()) == '*')
    {
        // Handle block comments
        while ((c = getch()) != EOF)
        {
            if (c == '*')
            {
                if ((c = getch()) == '/')
                    break;
                ungetch(c);
            }
        }
        return getword(arr, lim); // Recursive call to get next word after comment
    }
    else if (c == '/' && (c = getch()) == '/')
    {
        // Handle line comments
        while ((c = getch()) != '\n' && c != EOF)
            ;
        return getword(arr, lim); // Recursive call to get next word after comment
    }
    else if (c == '/')
    {
        // Just a regular slash
        ungetch(c);
    }

    *w = '\0';
    return arr[0];
}
