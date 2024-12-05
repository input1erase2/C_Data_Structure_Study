#include <stdio.h>
#include "heap.h"

int dataPriorityComp(char ch1, char ch2) {
	return ch2 - ch1;
}

int main() {
	Heap heap;
	H_init(&heap, dataPriorityComp);
	
	H_enqueue(&heap, 'A');
	H_enqueue(&heap, 'B');
	H_enqueue(&heap, 'C');
	printf("[Dequeue] >> %c\n", H_dequeue(&heap));
	
	H_enqueue(&heap, 'A');
	H_enqueue(&heap, 'B');
	H_enqueue(&heap, 'C');
	printf("[Dequeue] >> %c\n", H_dequeue(&heap));
	
	printf("[Print all elements in the heap]\n");
	while(!H_isEmpty(&heap))
		printf(">> %c\n", H_dequeue(&heap));
	return 0;
}