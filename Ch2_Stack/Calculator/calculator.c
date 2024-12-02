#include "calculator.h"

const char NUMBER[] = {
    '0', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', '.'
};

int isNumber(char ch) {
    const int len = sizeof(NUMBER);
    for (int i = 0; i < len; ++i)
        if (NUMBER[i] == ch) return TRUE;
    return FALSE;
}

unsigned int getNextToken(const char* exp, char* token, int* type) {
    unsigned int i = 0;
    for (; 0 != exp[i]; ++i) {
        token[i] = exp[i];
        if (isNumber(exp[i]) == TRUE) {
            *type = OPERAND;
            if (isNumber(exp[i + 1]) == FALSE) break;
        }
        else {
            *type = exp[i];
            break;
        }
    }
    token[++i] = '\0';
    return i;
}

int getPriority(char op, int isInStack) {
    int priority = -1;
    switch (op) {
    case LEFT_PARENTHESIS:  priority = (isInStack) ? 3 : 0; break;
    case MULTI: case DIV:   priority = 1; break;
    case PLUS: case MINUS:  priority = 2; break;
    }
    return priority;
}

int isPrior(char opInStack, char opInToken) {
    return getPriority(opInStack, TRUE) > getPriority(opInToken, FALSE);
}

void getPostfix(char* infixExp, char* postfixExp) {
    Stack stk;
    char token[32];
    int type = -1;
    unsigned int pos = 0;
    unsigned int len = strlen(infixExp);

    LS_initialize(&stk);

    while (pos < len) {
        // Step 1. 토큰을 가져오고, 다음 토큰의 위치를 파악한다.
        pos += getNextToken(&infixExp[pos], token, &type);

        // Step 2-1. 토큰의 종류가 피연산자일 경우,
        if (OPERAND == type) {
            strcat(postfixExp, token);  // 기존 후위연산식에 토큰을 붙이고
            strcat(postfixExp, " ");    // 띄어쓰기 한 칸 붙여준다.
        }
        // Step 2-2. 토큰의 종류가 오른쪽 괄호일 경우,
        else if (RIGHT_PARENTHESIS == type) {
            while (!LS_isEmpty(&stk)) {
                ElementType popped = LS_pop(&stk);
                if (popped[0] == LEFT_PARENTHESIS) break;
                strcat(postfixExp, popped);
            }
        }
        // Step 2-3. 토큰의 종류가 연산자일 경우,
        else {
            while (!LS_isEmpty(&stk) && !isPrior((stk.top)->data[0], token[0])) {
                ElementType popped = LS_pop(&stk);
                if (popped[0] == LEFT_PARENTHESIS) break;
                strcat(postfixExp, popped);
            }
            LS_push(&stk, token);
        }
    }
    // Step 3. 스택에 남아있는 항목들을 꺼내고 마무리.
    while (!LS_isEmpty(&stk)) {
        ElementType popped = LS_pop(&stk);
        if (popped[0] == LEFT_PARENTHESIS) break;
        strcat(postfixExp, popped);
    }
}

double calculate(char* postfixExp) {
    Stack stk;
    ElementType resultString;
    double result;
    char token[32];
    int type = -1;
    unsigned int pos = 0;
    unsigned int len = strlen(postfixExp);

    LS_initialize(&stk);

    while (pos < len) {
        pos += getNextToken(&postfixExp[pos], token, &type);
        if (type == SPACE) continue;
        
        if (type == OPERAND) LS_push(&stk, token);
        else {
            char resultString[32];
            double op1, op2, tempResult;
            ElementType operandString;

            operandString = LS_pop(&stk);
            op2 = atof(operandString);      //  string to double 
            operandString = LS_pop(&stk);
            op1 = atof(operandString);      //  string to double

            switch(type) {
            case PLUS:  tempResult = op1 + op2; break;
            case MINUS: tempResult = op1 - op2; break;
            case MULTI: tempResult = op1 * op2; break;
            case DIV:   tempResult = op1 / op2; break;
            }
            gcvt(tempResult, 10, resultString); // double -> char or string
            LS_push(&stk, resultString);
        }
    }
    resultString = LS_pop(&stk);
    result = atof(resultString);    // string to double
    return result;
}
