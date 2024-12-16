#include <stdio.h>
#include <stdlib.h>
#include "list_stack.h"

void initialize(Stack* stk) {
    stk->nodes = NULL;
    stk->top = NULL;
    stk->numOfData = 0;
}

void push(Stack* stk, ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->prev = stk->top;
    stk->top = newNode;
    (stk->numOfData)++;
}

ElementType pop(Stack* stk) {
    if (stk->top == NULL) {
        printf("[ERROR/ POP] Stack is already empty\n");
        return FALSE;
    }
    ElementType ret = stk->top->data;
    Node* temp = stk->top;
    stk->top = stk->top->prev;
    free(temp);
    (stk->numOfData)--;
    return ret;
}

ElementType peek(const Stack* stk) {
    return stk->top->data;
}

int getSize(const Stack* stk) {
    return stk->numOfData;
}

int isEmpty(const Stack* stk) {
    return (stk->numOfData == 0);
}
