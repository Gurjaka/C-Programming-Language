#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* minprintf: minimal printf with field width and precision */
void minprintf(char* fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }

        // Start parsing format
        p++; // skip '%'

        // Parse optional width and precision
        char format[32] = "%";
        int i = 1;

        while (isdigit(*p) || *p == '.' || *p == '-')
        {
            if (i < sizeof(format) - 1)
                format[i++] = *p++;
        }

        format[i++] = *p; // type specifier like d, f, s
        format[i] = '\0';

        switch (*p)
        {
            case 'd':
                ival = va_arg(ap, int);
                printf(format, ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf(format, dval);
                break;
            case 's':
                sval = va_arg(ap, char*);
                printf(format, sval);
                break;
            default:
                // Unrecognized specifier
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}

int main(void)
{
    minprintf("%.5d", 123);
    return EXIT_SUCCESS;
}
