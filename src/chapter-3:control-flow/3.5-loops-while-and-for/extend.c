#include <stdio.h>
#include <stdlib.h>
#define LIMIT 1000

void extend(char s1[], char s2[])
{
    int i, j;
    for (i = 0, j = 0; s1[i] != '\0' && j < LIMIT - 1; ++i, ++j)
    {
        if (s1[i] == '-' && i != 0 && s1[i + 1] != '\0' && s1[i - 1] != '-' && s1[i + 1] != '-')
        {
            if (s1[i - 1] < s1[i + 1])
                for (int k = s1[i - 1] + 1; k < s1[i + 1]; ++k)
                {
                    s2[j++] = k;
                }
            else if (s1[i - 1] > s1[i + 1])
                for (int k = s1[i - 1] - 1; k > s1[i + 1]; --k)
                {
                    s2[j++] = k;
                }
            continue;
        }
        s2[j] = s1[i];
    }
    s2[j] = '\0';
}

int main(void)
{
    char s2[LIMIT];
    char s1[] = "--a-z1-9";
    extend(s1, s2);
    printf("%s", s2);
    return EXIT_SUCCESS;
}
