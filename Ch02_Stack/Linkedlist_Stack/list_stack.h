#ifndef __LIST_STACK_H_
#define __LIST_STACK_H_

#define TRUE    1
#define FALSE   0


typedef int ElementType;

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


void        initialize(Stack* stk);
void        push(Stack* stk, ElementType newData);
ElementType pop(Stack* stk);
ElementType peek(const Stack* stk);
int         getSize(const Stack* stk);
int         isEmpty(const Stack* stk);

#endif