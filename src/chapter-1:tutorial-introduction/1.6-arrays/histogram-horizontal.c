#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 100

int main()
{
    // define variables
    int c;
    int wlen[MAX_WORD_LENGTH] = {0};
    int current_len = 0;

    // while loop to get input
    while ((c = getchar()) != EOF)
    {
        // check end of the word
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (current_len > 0 && current_len < MAX_WORD_LENGTH)
            {
                wlen[current_len]++;
                current_len = 0;
            }
        }
        else
        {
            current_len++;
        }
    }

    // for loop for histogram
    for (int i = 1; i < MAX_WORD_LENGTH; i++)
    {
        if (wlen[i] != 0)
        {
            printf("%d | ", i);
            for (int j = 0; j < wlen[i]; j++)
            {
                printf("*");
            }
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
