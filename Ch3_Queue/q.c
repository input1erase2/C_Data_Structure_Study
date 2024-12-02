#include "q.h"

void Q_makeQueue(Queue* queue, int capacity) {
	queue->nodes = (Node*)malloc(sizeof(Node) * (capacity + 1));
	queue->rear		= 0;
	queue->front	= 0;
	queue->capacity = capacity;
}

void Q_destroyQueue(Queue* queue){
	free(queue->nodes);
	queue->rear		= 0;
	queue->front	= 0;
	queue->capacity = 0;
}

void Q_enqueue(Queue* queue, ElementType newData){
	int pos = queue->rear;
	queue->rear = (queue->rear == queue->capacity) ? 0 : (queue->rear + 1);
	queue->nodes[pos].data = newData;
}

ElementType Q_dequeue(Queue* queue){
	int pos = queue->front;
	queue->front = (queue->front == queue->capacity) ? 0 : (queue->front + 1);
	return queue->nodes[pos].data;
}

ElementType Q_peek(Queue* queue) {
	return queue->nodes[queue->front].data;
}

int Q_getSize(const Queue* queue){
	if (queue->front <= queue-> rear)
		return queue->rear - queue->front;
	else
		return queue->rear + (queue->capacity - queue->front) + 1;
}

int Q_isEmpty(const Queue* queue){
	return (queue->front == queue->rear);
}

int Q_isFull(const Queue* queue){
	if (queue->front < queue->rear)
		return (queue->rear - queue->front) == queue->capacity;
	else
		return (queue->rear + 1) == queue->front;
}

