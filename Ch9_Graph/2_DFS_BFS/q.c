#include "q.h"

void createQueue(Queue** q) {
    (*q) = (Queue*)malloc(sizeof(Queue));
    (*q)->count     = 0;
    (*q)->front     = NULL;
    (*q)->rear      = NULL;
}

void destroyQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        Node* popped = dequeue(q);
        destroyNode(popped);
    }
    free(q);
}

Node* createNode(Vertex* v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
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
