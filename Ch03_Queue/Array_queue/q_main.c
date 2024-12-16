#include "q.h"

int main() {
	Queue q;
	Q_makeQueue(&q, 10);
	
	int i = 1;
	// 큐에 요소 5개 넣기
	for (; i <= 5; ++i) Q_enqueue(&q, 100 * i);
	printf("Current --- capacity: %d, size: %d\n\n", q.capacity, Q_getSize(&q));
	
	// 큐가 가득 찰 때까지 요소 넣기, 오류문 출력 확인하기
	while (!Q_isFull(&q)) Q_enqueue(&q, 100 * (i++));
	printf("Current --- capacity: %d, size: %d\n\n", q.capacity, Q_getSize(&q));
	
	// 큐의 모든 요소 dequeue하기
	while (!Q_isEmpty(&q))
		printf("Dequeue [%d] ---- (Front: %d, Rear: %d)\n",
			Q_dequeue(&q), q.front, q.rear);
	
	// 큐 초기화하기
	printf("[Destroying Queue...]\n");
	Q_destroyQueue(&q);
	printf("\tq->node = 0x%p\n", q.nodes);
	printf("\tq->capacity = %d\n", q.capacity);
	printf("\tq->rear = %d\n", q.rear);
	printf("\tq->front = %d\n\n", q.front);
	return 0;
}