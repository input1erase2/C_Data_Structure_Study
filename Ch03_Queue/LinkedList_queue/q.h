#ifndef __Q_H_
#define __Q_H_

typedef struct _Node {
    char* data;
    struct _Node* next;
} Node;

typedef struct _Queue {
    Node* front;
    Node* rear;
    int count;
} Queue;

void    createQueue(Queue** q);
void    destroyQueue(Queue* q);
Node*   createNode(char* data);
void    destroyNode(Node* node);
void    enqueue(Queue* q, Node* newNode);
Node*   dequeue(Queue* q);
int     isQueueEmpty(Queue* q);

#endif