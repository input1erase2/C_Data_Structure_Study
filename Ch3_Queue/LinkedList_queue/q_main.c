#include <stdio.h>
#include "q.h"

int main() {
    Node* popped;
    Queue* q;

    createQueue(&q);
    
    enqueue(q, createNode("abc"));
    enqueue(q, createNode("def"));
    enqueue(q, createNode("efg"));
    enqueue(q, createNode("hij"));

    printf("Queue Size : %d\n", q->count);

    while (!isQueueEmpty(q)) {
        popped = dequeue(q);
        printf("Dequeue: %s \n", popped->data);
        destroyNode(popped);
    }
    destroyQueue(q);
    return 0;
}