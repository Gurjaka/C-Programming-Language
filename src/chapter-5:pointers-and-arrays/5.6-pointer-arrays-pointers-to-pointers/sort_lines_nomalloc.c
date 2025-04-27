#include <stdio.h>
#include <string.h>

#define MAX_LINES 5000       /* max number of lines to be sorted */
#define MAX_LINE_LENGTH 1000 /* max length of any input line */

char lineStorage[MAX_LINES][MAX_LINE_LENGTH]; /* Static storage for lines */
char* linePointers[MAX_LINES];                /* Pointers to text lines */

int readLines(char* linePointers[], int maxLines);
void writeLines(char* linePointers[], int numberOfLines);
void quickSort(char* linePointers[], int left, int right);

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

/* readLines: read input lines */
int readLines(char* linePointers[], int maxLines)
{
    int lineLength, numberOfLines = 0;

    while (numberOfLines < maxLines && (lineLength = getLine(lineStorage[numberOfLines], MAX_LINE_LENGTH)) > 0)
    {
        lineStorage[numberOfLines][lineLength - 1] = '\0';        /* Remove newline */
        linePointers[numberOfLines] = lineStorage[numberOfLines]; /* Store pointer */
        numberOfLines++;
    }

    return numberOfLines;
}

/* writeLines: write output lines */
void writeLines(char* linePointers[], int numberOfLines)
{
    for (int i = 0; i < numberOfLines; i++)
        printf("%s\n", linePointers[i]);
}

/* quicksort: sort v[left]...v[right] into increasing order */
void quickSort(char* v[], int left, int right)
{
    int i, last;
    void swap(char* v[], int i, int j);
    if (left >= right)
        return;

    swap(v, left, (left + right) / 2); /* Pivot selection */
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0) /* Compare strings */
            swap(v, ++last, i);

    swap(v, left, last);
    quickSort(v, left, last - 1);
    quickSort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char* v[], int i, int j)
{
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
