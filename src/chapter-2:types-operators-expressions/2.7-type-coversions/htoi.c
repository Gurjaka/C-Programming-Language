#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 1000

int htoi(char hex[])
{
    int decimal = 0;
    for (int i = 0; hex[i] != '\0'; ++i)
    {
        int value;
        if (isdigit(hex[i]))
        {
            value = hex[i] - '0';
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            value = hex[i] - 'a' + 10;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            value = hex[i] - 'A' + 10;
        }
        else
        {
            return -1;
        }
        decimal = decimal * 16 + value;
    }
    return decimal;
}

int main(void)
{
    printf("%d\n", htoi("1B"));

    return EXIT_SUCCESS;
}
