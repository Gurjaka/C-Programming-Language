#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void reverse(char string[])
{
    int i = 0, j = 0;

    while (string[i] != '\0')
        ++i;

    --i;

    while (i > j)
    {
        char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
        --i;
        ++j;
    }
}

void itoa(int n, char s[], int b)
{
    int i, sign, is_min = 0;

    if (n == INT_MIN)
    {
        is_min = 1;
        n = INT_MAX;
    }

    if ((sign = n) < 0) // record sign
        n = -n;         // make n positive

    i = 0;

    do
    {                          // generate digits in reverse order
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it

    if (sign < 0)
        s[i++] = '-';

    if (i < b)
    {
        do
            s[i++] = '0';
        while (i != b);
    }
    s[i] = '\0';

    if (is_min)
        s[0] = '8';

    reverse(s);
}

int main()
{
    char s[1000];

    itoa(10, s, 10);
    printf("%s", s);

    return EXIT_SUCCESS;
}
