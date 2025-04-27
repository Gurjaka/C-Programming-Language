#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'
#define VARIABLE '1'
#define MAXSTACK 100
#define BUFSIZE 100
#define VAR_COUNT 26

int stack_pointer = 0;
double variables[VAR_COUNT];
double last_printed = 0.0;
double stack[MAXSTACK];
char buf[BUFSIZE];
int bufp = 0;

void push(double f);
double pop(void);
int getop(char s[], char** expr);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [RPN expression]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int type;
    double op2;
    char s[MAXOP];
    int var_index = 0;

    for (int i = 1; i < argc; i++)
    {
        char* expr = argv[i];
        char* expr_ptr = expr;

        while ((type = getop(s, &expr_ptr)) != '\0')
        {
            switch (type)
            {
                case NUMBER:
                    push(atof(s));
                    break;
                case VARIABLE:
                    var_index = s[0] - 'a';
                    if (var_index >= 0 && var_index < VAR_COUNT)
                    {
                        push(variables[var_index]);
                    }
                    else
                    {
                        printf("error: invalid variable %c\n", s[0]);
                    }
                    break;
                case '=':
                    if (var_index >= 0 && var_index < VAR_COUNT)
                    {
                        variables[var_index] = pop();
                    }
                    else
                    {
                        printf("error: invalid variable assignment\n");
                        pop();
                    }
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
                case '\n':
                    last_printed = pop();
                    printf("\t%.8g\n", last_printed);
                    break;
                default:
                    printf("error: unknown command %c\n", type);
                    break;
            }
        }
    }

    if (stack_pointer > 0)
    {
        printf("\tResult: %.8g\n", pop());
    }

    return EXIT_SUCCESS;
}

void push(double f)
{
    if (stack_pointer < MAXSTACK)
    {
        stack[stack_pointer++] = f;
    }
    else
    {
        printf("Stack full, can't push %f\n", f);
    }
}

double pop(void)
{
    if (stack_pointer > 0)
    {
        return stack[--stack_pointer];
    }
    else
    {
        printf("Stack empty\n");
        return 0.0;
    }
}

int getop(char s[], char** expr)
{
    int i = 0;
    char c;

    while ((c = **expr) == ' ' || c == '\t')
        (*expr)++;

    if (c == '\0')
        return '\0';

    if (islower(c))
    {
        s[0] = c;
        s[1] = '\0';
        (*expr)++;
        return VARIABLE;
    }

    if (!isdigit(c) && c != '.' && c != '-')
    {
        s[0] = c;
        s[1] = '\0';
        (*expr)++;
        return c;
    }

    if (c == '-')
    {
        s[i++] = c;
        (*expr)++;
        if (!isdigit(**expr) && **expr != '.')
        {
            return '-';
        }
        c = **expr;
    }

    while (isdigit(c = **expr))
    {
        s[i++] = c;
        (*expr)++;
    }

    if (c == '.')
    {
        s[i++] = c;
        (*expr)++;
        while (isdigit(c = **expr))
        {
            s[i++] = c;
            (*expr)++;
        }
    }

    s[i] = '\0';
    return NUMBER;
}
