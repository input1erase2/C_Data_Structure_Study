#ifndef __ARRAY_STACK_H_
#define __ARRAY_STACK_H_

#define TRUE    1
#define FALSE   0

#define STACK_SIZE 10

typedef int ElementType;

typedef struct _Node {
    ElementType data;
} Node;

typedef struct _Stack {
    int top;
    Node nodes[STACK_SIZE];
} ArrayStack;

typedef ArrayStack Stack;


void        initialize(Stack* stk);
void        push(Stack* stk, ElementType newData);
ElementType pop(Stack* stk);
ElementType peek(const Stack* stk);
int         getSize(const Stack* stk);
int         isEmpty(const Stack* stk);

#endif