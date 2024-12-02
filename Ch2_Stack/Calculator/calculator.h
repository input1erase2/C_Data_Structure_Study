#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_

#include "list_stack.h"

typedef enum {
    LEFT_PARENTHESIS    = '(',
    RIGHT_PARENTHESIS   = ')',
    PLUS                = '+',
    MINUS               = '-',
    MULTI               = '*',
    DIV                 = '/',
    SPACE               = ' ',
    OPERAND
} SYMBOL;

int isNumber(char ch);
unsigned int getNextToken(const char* exp, char* token, int* type);
int isPrior(char op1, char op2);
void getPostfix(char* infixExp, char* postfixExp);
double calculate(char* postfixExp);

#endif