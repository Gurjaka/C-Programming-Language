#include <ctype.h>
#include <stdio.h>

#define NUMBER '0'
#define VARIABLE '1'

static char buffer = 0;     // Buffered character for reusing input
static int buffer_flag = 0; // Flag to indicate if the buffer has a character

// Function to get the next character (handling the buffer)
int getch(void)
{
    if (buffer_flag)
    {
        buffer_flag = 0;
        return buffer;
    }
    return getchar();
}

// Function to handle the input for numbers or variables
int getop(char* operand)
{
    static int previous_char = 0; // Static variable to remember the last character
    int index = 0;
    int current_char;

    // Use the previous character if available
    if (previous_char)
    {
        current_char = previous_char;
        previous_char = 0;
    }
    else
    {
        current_char = getch();
    }

    // Skip whitespace characters
    while (current_char == ' ' || current_char == '\t')
        current_char = getch();

    operand[0] = current_char;
    operand[1] = '\0';

    // Check for variables (lowercase letters)
    if (islower(current_char))
    {
        return VARIABLE;
    }

    // If it's not a digit, a dot, or a minus sign, return it as is
    if (!isdigit(current_char) && current_char != '.' && current_char != '-')
    {
        return current_char;
    }

    index = 0;

    // Handle negative numbers, check if '-' is part of a number
    if (current_char == '-')
    {
        int next_char = getch();
        // If the next character is not a digit or a '.', return '-' as an operator
        if (!isdigit(next_char) && next_char != '.')
        {
            previous_char = next_char;
            return '-';
        }
        // Otherwise, it's part of a negative number
        operand[++index] = current_char = next_char;
    }

    // Collect integer part of the number
    while (isdigit(operand[++index] = current_char = getch()))
        ;

    // Collect decimal part, if any
    if (current_char == '.')
    {
        while (isdigit(operand[++index] = current_char = getch()))
            ;
    }

    operand[index] = '\0';

    // If there's a character left in the buffer, save it
    if (current_char != EOF)
    {
        previous_char = current_char;
    }

    return NUMBER; // Return NUMBER after processing
}
