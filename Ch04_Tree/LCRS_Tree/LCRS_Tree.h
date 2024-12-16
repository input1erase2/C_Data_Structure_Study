#ifndef __LCRS_TREE_H_
#define __LCRS_TREE_H_

#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef char ElementType;

typedef struct _Node {
    ElementType data;
    struct _Node* lc;   // left child
    struct _Node* rs;   // right sibling
} Node;

Node*   LCRS_makeNode(ElementType newData);
void    LCRS_destroyNode(Node* node);
void    LCRS_destroyTree(Node* root);
void    LCRS_addChild(Node* parent, Node* child);
void    LCRS_printTree(Node* node, int lv);

#endif