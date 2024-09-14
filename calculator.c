#include <stdio.h>

int main() {
    int num1;
    int num2;
    char op;

    printf("Choose Num1: \n");
    scanf("%d", &num1);

    printf("Choose Num2: \n");
    scanf("%d", &num2);

    getchar();

    printf("Choose operation: + ; - ; * ; / ;\n");
    scanf("%c", &op);

    double result;

    if (op == '+') {
        result = num1 + num2;
        printf("Result: %lf\n", result);
    } else if (op == '-') {
        result = num1 - num2;
        printf("Result: %lf\n", result);
    } else if (op == '*') {
        result = num1 * num2;
        printf("Result: %lf\n", result);
    } else if (op == '/') {
        if (num2 != 0) {
            result = (double)num1 / (double)num2;
            printf("Result: %lf\n", result);
        } else {
            printf("Error: can't devide by zero.\n");
        }
    } else {
	printf("Error: unexpected operation");
    }
    return 0;
}
