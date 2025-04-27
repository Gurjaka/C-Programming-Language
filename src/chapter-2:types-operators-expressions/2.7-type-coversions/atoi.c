#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* stlib already contains atoi function,
so we define a_toi instead to demonstrate the code*/
int a_toi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; isdigit(s[i]); ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

int main(void)
{
    int res;
    res = a_toi("105");

    printf("%d\n", res);

    return EXIT_SUCCESS;
}
