#include "q.h"

int main() {
	Queue q;
	Q_makeQueue(&q, 10);
	
	int i = 1;
	for (; i <= 5; ++i) Q_enqueue(&q, 100 * i);
	printf("Current --- capacity: %d, size: %d\n\n", q.capacity, Q_getSize(&q));
	
	while (!Q_isFull(&q)) Q_enqueue(&q, 100 * (i++));
	printf("Current --- capacity: %d, size: %d\n\n", q.capacity, Q_getSize(&q));
	
	while (!Q_isEmpty(&q))
		printf("Dequeue [%d] ---- (Front: %d, Rear: %d)\n",
			Q_dequeue(&q), q.front, q.rear);
	
	return 0;
}
