#ifndef __LIST_STACK_H_
#define __LIST_STACK_H_

#define TRUE    1
#define FALSE   0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* ElementType;

typedef struct _Node {
    ElementType data;
    struct _Node* prev;
} Node;

typedef struct _Stack {
    Node* top;
    Node* nodes;
    int numOfData;
} LinkedlistStack;

typedef LinkedlistStack Stack;


void        LS_initialize(Stack* stk);
void        LS_destroyNode(Node* node);
void        LS_push(Stack* stk, ElementType newData);
ElementType LS_pop(Stack* stk);
ElementType LS_peek(const Stack* stk);
int         LS_getSize(const Stack* stk);
int         LS_isEmpty(const Stack* stk);

#endif