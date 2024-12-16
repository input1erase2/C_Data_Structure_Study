#ifndef __EXPTREE_H_
#define __EXPTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0

typedef char ElementType;

typedef struct _Node {
    ElementType data;
    struct _Node* left;
    struct _Node* right;
} Node;

Node*   makeNode(ElementType newData); 
void    destroyNode(Node* node);
void    destroyTree(Node* root);

void    printTreePreorder(Node* root);
void    printTreeInorder(Node* root);
void    printTreePostorder(Node* root);

void    buildExpressionTree(Node** root, char* postfixExp);
double  calculate(Node* root);

#endif