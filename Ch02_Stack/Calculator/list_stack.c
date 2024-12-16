#include "list_stack.h"

void LS_initialize(Stack* stk) {
    stk->nodes = NULL;
    stk->top = NULL;
    stk->numOfData = 0;
}

void LS_push(Stack* stk, ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(newData) + 1);
    strcpy(newNode->data, newData);
    newNode->prev = stk->top;
    stk->top = newNode;
    (stk->numOfData)++;
}

void LS_destroyNode(Node* node) {
    free(node);
}

ElementType LS_pop(Stack* stk) {
    if (stk->top == NULL) {
        printf("[ERROR/ POP] Stack is already empty\n");
        return FALSE;
    }
    ElementType ret = stk->top->data;
    stk->top = stk->top->prev;
    (stk->numOfData)--;
    return ret;
}

ElementType LS_peek(const Stack* stk) {
    return stk->top->data;
}

int LS_getSize(const Stack* stk) {
    return stk->numOfData;
}

int LS_isEmpty(const Stack* stk) {
    return (stk->numOfData == 0);
}
