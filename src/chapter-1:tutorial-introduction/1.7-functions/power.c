#include <stdio.h>

// Power: raise base to n-th power; n >= 0
int power(int base, int n)
{
    int i, p;

    p = i;
    for (i = 1; i <= n; ++i)
        p = p * base;
    return p;
}

// Test power function
int main()
{
    for (int i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));
    return 0;
}
