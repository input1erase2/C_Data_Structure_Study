#ifndef __SINGLE_LINKEDLIST_H_
#define __SINGLE_LINKEDLIST_H_

typedef int ElementType;

typedef struct _Node {
    ElementType data;
    struct _Node* next;
} Node;

Node*   makeNode(ElementType newData);
void    destroyNode(Node* node);
void    destroyList(Node** head);
void    addNode(Node** head, Node* newNode);
void    addNodeByValue(Node** head, ElementType newData);
void    addNodeAfter(Node* cur, Node* newNode);
void    addNodeBefore(Node** head, Node* cur, Node* newNode);
void    addNodeNewHead(Node** head, Node* newNode);
void    removeNode(Node** head, Node* delNode);
void    removeNodeByData(Node** head, ElementType delData);
Node*   getNode(Node* head, int loc);
int     getNodeCount(Node* head);

#endif