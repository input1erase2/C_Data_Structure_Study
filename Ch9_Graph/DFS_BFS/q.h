#ifndef __Q_H_
#define __Q_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"                  // 정점 저장을 위해 수정한 곳

typedef struct _Node {
    Vertex* data;                   // 정점 저장을 위해 수정한 곳
    struct _Node* next;
} Node;

typedef struct _Queue {
    Node* front;
    Node* rear;
    int count;
} Queue;

void    createQueue(Queue** q);
void    destroyQueue(Queue* q);
Node*   createNode(Vertex* data);   // 정점 저장을 위해 수정한 곳
void    destroyNode(Node* node);
void    enqueue(Queue* q, Node* newNode);
Node*   dequeue(Queue* q);
int     isQueueEmpty(Queue* q);

#endif