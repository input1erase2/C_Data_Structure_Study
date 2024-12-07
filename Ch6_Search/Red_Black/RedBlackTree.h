#ifndef __RED_BLACK_H_
#define __RED_BLACK_H_

typedef int ElementType;

typedef struct _Node {
    ElementType data;           // now, ElementType is 4bytes
    enum { RED, BLACK } color;  // enum is 4bytes
    struct _Node* parent;
    struct _Node* left;
    struct _Node* right;
} Node;                         // total 32bytes (no padding bytes)


Node*   RBT_createNode(ElementType newData);
void    RBT_destroyNode(Node* node);
void    RBT_destroyTree(Node* tree);

Node*   RBT_search(Node* tree, ElementType targetData);
Node*   RBT_searchMin(Node* tree);
Node*   RBT_searchMax(Node* tree);

void    RBT_rotateLeft(Node** tree, Node* center);
void    RBT_rotateRight(Node** tree, Node* center);

void    RBT_insert(Node** tree, Node* newNode);
void    RBT_insertHelper(Node** tree, Node* newNode);
void    RBT_rebuildAfterInsert(Node** tree, Node* cur);

Node*   RBT_remove(Node** tree, ElementType targetData);
void    RBT_rebuildAfterRemove(Node** tree, Node* successor);

void    RBT_printTree(Node* tree, int depth, int blackCount);

#endif