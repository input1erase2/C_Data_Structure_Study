#include <stdio.h>
#include "array_stack.h"
// #include <stdlib.h>
// #include "list_stack.h"

// void initialize(Stack* stk, int capacity) {
//     stk->nodes = (Node*)malloc(sizeof(Node) * capacity);
//     stk->capacity = capcaity;
//     stk->top = -1;
// }

void initialize(Stack* stk) {
    stk->top = -1;
}

void push(Stack* stk, ElementType newData) {
    if ((stk->top + 1) >= STACK_SIZE) {
        printf("[ERROR/ PUSH] Stack is already full\n");
        return;
    }
    (stk->nodes[++(stk->top)]).data = newData;
}

ElementType pop(Stack* stk) {
    if (stk->top < 0) {
        printf("[ERROR/ POP] Stack is already empty\n");
        return FALSE;
    } 
    return (stk->nodes[(stk->top)--]).data;
}

ElementType peek(const Stack* stk) {
    if (stk->top < 0) {
        printf("[ERROR/ PEEK] Stack is already empty\n");
        return FALSE;
    }
    return (stk->nodes[(stk->top)]).data;
}

int getSize(const Stack* stk) {
    return (stk->top + 1);
}

int isEmpty(const Stack* stk) {
    return (stk->top < 0);
}
