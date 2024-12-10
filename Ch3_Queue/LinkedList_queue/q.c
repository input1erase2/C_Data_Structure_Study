#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q.h"

void createQueue(Queue** q) {
    (*q) = (Queue*)malloc(sizeof(Queue));
    (*q)->count = 0;
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

void destroyQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        Node* popped = dequeue(q);
        destroyNode(popped);
    }
    free(q);
}

Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = (char*)malloc(strlen(data) + 1);
    strcpy(newNode->data, data);

    newNode->next = NULL;

    return newNode;
}

void destroyNode(Node* node) {
    free(node->data);
    free(node);
}

void enqueue(Queue* q, Node* newNode) {
    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

Node* dequeue(Queue* q) {
    if (isQueueEmpty(q)) return NULL;

    Node* popped = q->front;
    if (q->front->next == NULL) {
        q->front = NULL;
        q->rear = NULL;
    }
    else {
        q->front = q->front->next;
    }
    return popped;
}

int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}
