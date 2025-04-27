#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5000       /* max number of lines to be sorted */
#define MAX_LINE_LENGTH 1000 /* max length of any input line */

char* linePointers[MAX_LINES]; /* pointers to text lines */
int readLines(char* linePointers[], int maxLines);
void writeLines(char* linePointers[], int numberOfLines);

int main(int argc, char* argv[])
{
    int n = argc > 1 ? atoi(argv[1]) : 10;
    int numberOfLines; /* number of input lines read */
    if ((numberOfLines = readLines(linePointers, MAX_LINES)) >= 0)
    {
        int output = numberOfLines - n;
        if (output > 0)
            writeLines(&linePointers[n], output);
        for (int i = 0; i < numberOfLines; i++)
        {
            free(linePointers[i]);
        }
        return EXIT_SUCCESS;
    }
    else
    {
        printf("error: input too big to sort\n");
        return EXIT_FAILURE;
    }
}

int getLine(char* buffer, int limit)
{
    int character, index;
    for (index = 0; index < limit - 1 && (character = getchar()) != EOF && character != '\n'; ++index)
        buffer[index] = character;
    if (character == '\n')
    {
        buffer[index] = character;
        ++index;
    }
    buffer[index] = '\0';
    return index;
}

/* alloc: allocate memory for a string */
char* alloc(int length)
{
    return (char*) malloc(length * sizeof(char)); // allocate memory for the string
}

/* readLines: read input lines */
int readLines(char* linePointers[], int maxLines)
{
    int lineLength, numberOfLines;
    char *pointer, currentLine[MAX_LINE_LENGTH];
    numberOfLines = 0;
    while ((lineLength = getLine(currentLine, MAX_LINE_LENGTH)) > 0)
    {
        pointer = alloc(lineLength); // allocate memory for each line
        if (numberOfLines >= maxLines || pointer == NULL)
        {
            for (int i = 0; i < numberOfLines; i++)
            {
                free(linePointers[i]);
            }
            return -1;
        }
        else
        {
            currentLine[lineLength - 1] = '\0';      /* delete newline */
            strcpy(pointer, currentLine);            // copy line to allocated memory
            linePointers[numberOfLines++] = pointer; // store pointer to line
        }
    };
    return numberOfLines;
}

/* writeLines: write output lines */
void writeLines(char* linePointers[], int numberOfLines)
{
    int i;
    for (i = 0; i < numberOfLines; i++)
        printf("%s\n", linePointers[i]); // print each line
}
