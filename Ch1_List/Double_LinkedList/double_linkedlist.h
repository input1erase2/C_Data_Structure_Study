#ifndef __DOUBLE_LINKEDLIST_H_
#define __DOUBLE_LINKEDLIST_H_

typedef int ElementType;

typedef struct _Node {
    ElementType data;
    struct _Node* prev;
    struct _Node* next;
} Node;

Node*   makeNode(ElementType data);
void    destroyNode(Node* node);
void    destroyList(Node** head);
void    addNode(Node** head, Node* newNode);
void    addNodeAfter(Node* cur, Node* newNode);
void    removeNode(Node** head, Node* delNode);
void    removeNodeByData(Node** head, ElementType delData);
Node*   getNode(Node* head, int loc);
unsigned int getNodeCount(Node* head);

#endif