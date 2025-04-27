#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 5000       /* max number of lines to be sorted */
#define MAX_LINE_LENGTH 1000 /* max length of any input line */

char* linePointers[MAX_LINES]; /* pointers to text lines */
int readLines(char* linePointers[], int maxLines);
void writeLines(char* linePointers[], int numberOfLines);
void quickSort(char* linePointers[], int left, int right);
char* alloc(int);

/* sort input lines */
int main(void)
{
    int numberOfLines; /* number of input lines read */
    if ((numberOfLines = readLines(linePointers, MAX_LINES)) >= 0)
    {
        quickSort(linePointers, 0, numberOfLines - 1);
        writeLines(linePointers, numberOfLines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
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
            return -1;
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

/* quicksort: sort v[left]...v[right] into increasing order */
void quickSort(char* v[], int left, int right)
{
    int i, last;
    void swap(char* v[], int i, int j);
    if (left >= right)                 /* do nothing if array contains */
        return;                        /* fewer than two elements */
    swap(v, left, (left + right) / 2); // pivot selection
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0) // compare strings
            swap(v, ++last, i);        // swap if necessary
    swap(v, left, last);               // swap pivot into place
    quickSort(v, left, last - 1);      // sort left part
    quickSort(v, last + 1, right);     // sort right part
}

/* swap: interchange v[i] and v[j] */
void swap(char* v[], int i, int j)
{
    char* temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp; // swap pointers
}
