#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char buffer_char = 0;
static bool buffer_flag = false;

// get_char: returns the next character, considering buffered characters.
int get_char(void)
{
    if (buffer_flag)
    {
        buffer_flag = false;
        return buffer_char;
    }
    return getchar();
}

// put_char_back: puts a character back into the input stream for later use.
void put_char_back(int c)
{
    if (buffer_flag)
    {
        printf("Error: too many characters put back\n");
    }
    else
    {
        buffer_char = c;
        buffer_flag = true;
    }
}

// get_integer: reads the next integer from input into *number.
// Returns 1 on success, 0 on failure.
int get_integer(int* number)
{
    int current_char, sign = 1;

    // Skip whitespace characters.
    while (isspace(current_char = get_char()))
        ;

    // Check if the character is a valid starting point for an integer.
    if (!isdigit(current_char) && current_char != EOF && current_char != '+' && current_char != '-')
    {
        put_char_back(current_char);
        return 0;
    }

    // Handle sign of the number.
    if (current_char == '-')
    {
        sign = -1;
        current_char = get_char();
    }
    else if (current_char == '+')
    {
        current_char = get_char();
    }

    // Accumulate the integer value.
    *number = 0;
    while (isdigit(current_char))
    {
        *number = 10 * *number + (current_char - '0');
        current_char = get_char();
    }

    *number *= sign;

    // If the next character is not EOF, put it back.
    if (current_char != EOF)
    {
        put_char_back(current_char);
    }

    return 1;
}

int main(void)
{
    int number;
    printf("Enter an integer: ");
    if (get_integer(&number))
    {
        printf("You entered %d\n", number);
    }
    else
    {
        printf("Error: Not a valid number\n");
    }

    return EXIT_SUCCESS;
}
