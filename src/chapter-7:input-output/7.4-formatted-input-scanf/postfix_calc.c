#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define VARIABLE '1'
#define MAXVAL 100
#define BUFSIZE 100
#define VAR_COUNT 26

int sp = 0;
double val[MAXVAL];
double variables[VAR_COUNT];
double last_printed = 0.0;

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[])
{
    if (scanf("%s", s) != 1)
        return EOF;

    if (islower(s[0]) && s[1] == '\0')
        return VARIABLE;

    char* p = s;
    if (*p == '-' && isdigit(*(p + 1)))
        ++p;

    while (isdigit(*p))
        ++p;

    if (*p == '.')
    {
        ++p;
        while (isdigit(*p))
            ++p;
    }

    if (*p == '\0')
        return NUMBER;

    return s[0];
}

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    int var_index = -1;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case VARIABLE:
                var_index = s[0] - 'a';
                push(variables[var_index]);
                break;
            case '=':
                pop();
                variables[var_index] = pop();
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case 's':
                push(sin(pop()));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case 'p':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 'P':
                last_printed = pop();
                printf("\t%.8g\n", last_printed);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return EXIT_SUCCESS;
}
