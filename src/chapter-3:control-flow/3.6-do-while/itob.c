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

void itob(int n, char s[], int b)
{
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int remainder, i = 0;

    do
    {
        remainder = n % b;
        s[i++] = digits[remainder];
        n /= b;
    } while (n > 0);
    s[i] = '\0';
    reverse(s);
}

int main(void)
{
    char s[1000];

    itob(24, s, 16);
    printf("%s", s);

    return EXIT_SUCCESS;
}
