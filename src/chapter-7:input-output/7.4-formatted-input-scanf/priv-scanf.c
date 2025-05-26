#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000

static void skip_whitespace(void);
static int read_integer(int*);
static int read_float(float*);
static int read_string(char*, int);
static int match_literal(char);
int minscanf(const char* format, ...);

int main(void)
{
    int day;
    char month[30];
    int year;

    printf("Enter a date (e.g., 23/Dec/2009): ");
    minscanf("%d/%s/%d", &day, month, &year);
    printf("You entered: %d/%s/%d\n", day, month, year);

    return EXIT_SUCCESS;
}

// helper function to skip white spaces
static void skip_whitespace(void)
{
    int c;
    while ((c = getchar()) != EOF && isspace(c))
        ;

    if (c != EOF)
        ungetc(c, stdin);
}

// read_integer: retrieve integers from stdin
static int read_integer(int* result)
{
    int c, sign = 1, value = 0;
    int digits_read = 0;

    skip_whitespace();

    c = getchar();

    if (c == '-' || c == '+')
    {
        sign = (c == '-') ? -1 : 1;
        c = getchar();
    }

    while (c != EOF && isdigit(c))
    {
        value = value * 10 + (c - '0');
        digits_read++;
        c = getchar();
    }

    if (c != EOF)
        ungetc(c, stdin);

    if (digits_read == 0)
        return 0;

    *result = value * sign;
    return 1;
}

// read_float: retrieve floats from stdin
static int read_float(float* result)
{
    int c, sign = 1;
    float value = 0.0, fraction = 0.0, divisor = 0.0;
    int digits_read = 0, decimal_digits = 0;
    int in_fraction = 0;

    skip_whitespace();

    c = getchar();

    if (c == '-' || c == '+')
    {
        sign = (c == '-') ? -1 : 1;
        c = getchar();
    }

    while (c != EOF && isdigit(c))
    {
        value = value * 10 + (c - '0');
        digits_read++;
        c = getchar();
    }

    if (c == '.')
    {
        in_fraction = 1;
        c = getchar();
        while (c != EOF && isdigit(c))
        {
            fraction = fraction * 10.0 + (c - '0');
            divisor *= 10.0;
            decimal_digits++;
            c = getchar();
        }
    }

    if (c != EOF)
        ungetc(c, stdin);

    if (digits_read == 0 && decimal_digits == 0)
        return 0;

    *result = sign * (value + fraction / divisor);
    return 1;
}

// read_string: retrieve strings from stdin
static int read_string(char* str, int maxlen)
{
    int c, i = 0;

    skip_whitespace();

    while ((c = getchar()) != EOF && isalnum(c) && i < maxlen - 1)
    {
        str[i++] = c;
    }

    if (c != EOF)
        ungetc(c, stdin);

    str[i] = '\0';

    return (i > 0) ? 1 : 0;
}

static int match_literal(char expected)
{
    int c;

    skip_whitespace();
    c = getchar();

    if (c == expected)
        return 1;

    if (c != EOF)
        ungetc(c, stdin);

    return 0;
}

// minscanf: minimal scanf implementation supporting %d, %f, %s
int minscanf(const char* format, ...)
{
    va_list args;
    const char* cur_input;
    char* string_ptr;
    int* integer_ptr;
    float* float_ptr;
    int converted = 0;

    va_start(args, format);
    for (cur_input = format; *cur_input; cur_input++)
    {
        if (*cur_input != '%')
        {
            if (!match_literal(*cur_input))
                break;
            continue;
        }

        // Start parsing format
        cur_input++; // skip '%'

        switch (*cur_input)
        {
            case 'd':
                integer_ptr = va_arg(args, int*);
                if (read_integer(integer_ptr))
                {
                    converted++;
                }
                else
                {
                    goto done;
                }
                break;
            case 'f':
                float_ptr = va_arg(args, float*);
                if (read_float(float_ptr))
                {
                    converted++;
                }
                else
                {
                    goto done;
                }
                break;
            case 's':
                string_ptr = va_arg(args, char*);
                if (read_string(string_ptr, MAXLEN))
                {
                    converted++;
                }
                else
                {
                    goto done;
                }
                break;
            case '%':
                if (!match_literal('%'))
                {
                    goto done;
                }
                break;
            default:
                // Unrecognized specifier
                fprintf(stderr, "minscanf: unsupported format %%%c\n", *cur_input);
                goto done;
        }
    }
done:
    va_end(args);
    return converted;
}
