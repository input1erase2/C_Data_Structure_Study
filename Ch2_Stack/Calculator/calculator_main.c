#include <stdio.h>
#include <string.h>
#include "calculator.h"


const int LEN = 100;

int main() {
    char infixExp[LEN];
    memset(infixExp, 0, sizeof(infixExp));
    
    char postfixExp[LEN];
    memset(postfixExp, 0, sizeof(postfixExp));
    
    printf("Enter infix expression: ");
    scanf("%s", infixExp);
    
    getPostfix(infixExp, postfixExp);

    printf("Infix: %s\n", infixExp);
    printf("Postfix: %s\n", postfixExp);
    printf("Result: %lf\n", calculate(postfixExp));

    return 0;
} 