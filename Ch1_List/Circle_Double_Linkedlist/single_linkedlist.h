#ifndef __SINGLE_LINKEDLIST_H_
#define __SINGLE_LINKEDLIST_H_

typedef int ElementType;

typedef struct _Node {
    ElementType data;
    struct _Node* next;
} Node;

Node*   makeNode(ElementType newData);
void    destroyNode(Node* node);
void    addNode(Node** head, ElementType newData);
void    addNodeAfter(Node* curr, Node* newNode);
void    addNodeNewHead(Node** head, Node* newNode);
void    removeNode(Node** head, Node* delNode);
Node*   getNode(Node* head, int loc);
int     getNodeCount(Node* head);

#endif