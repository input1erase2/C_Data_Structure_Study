#ifndef __Q_H_
#define __Q_H_

#include <stdio.h>
#include <stdlib.h>

#define TRUE	1
#define FALSE	0

typedef int ElementType;

typedef struct _Node {
	ElementType data;
} Node;

typedef struct _Queue {
	int capacity;
	int front; 
	int rear;
	Node* nodes;
} Queue;

void 		Q_makeQueue(Queue* queue, int capacity);
void 		Q_destroyQueue(Queue* queue);
void 		Q_enqueue(Queue* queue, ElementType newData);
ElementType Q_dequeue(Queue* queue);
int 		Q_getSize(const Queue* queue);
int 		Q_isEmpty(const Queue* queue);
int 		Q_isFull(const Queue* queue);

#endif
