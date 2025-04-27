#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* squeeze: delete all c from s */
void squeeze(char s1[], char s2[])
{
    int i, j, k;

    for (i = j = 0; s1[i] != '\0'; i++)
    {
        bool found = false;
        for (k = 0; s2[k] != '\0'; k++)
        {
            if (s1[i] == s2[k])
            {
                found = true;
                break;
            }
        }
        if (!found)
            s1[j++] = s1[i];
    }

    s1[j] = '\0';
}

int main(void)
{
    char s1[1000] = "tutorial";
    char s2[1000] = "utor";
    squeeze(s1, s2);
    printf("%s\n", s1);

    return EXIT_SUCCESS;
}
