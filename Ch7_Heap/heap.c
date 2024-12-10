#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void H_init(Heap* heap, PriorityComp foo) {
	heap->comp = foo;
	heap->numOfData = 0;
}

int H_isEmpty(Heap* heap){
	return heap->numOfData == 0;
}

static int getHighPriorChild(Heap* heap, int idx) {
	int lc = 2 * idx;
	if (lc > heap->numOfData) return 0;
	if (lc == heap->numOfData) return lc;
	int rc = lc + 1;
	return (heap->comp(heap->data[lc], heap->data[rc]) < 0) ? rc : lc;
}

void H_enqueue(Heap* heap, ElementType newData){
	if (heap->numOfData >= HEAP_SIZE) {
		perror("[ERROR/ Enqueue()] Priority Queue is Full\n");
		exit(-1);
	}
	int pos = heap->numOfData + 1;
	int parentPos;
	while (pos > 1) {
		parentPos = pos / 2;
		if (heap->comp(heap->data[parentPos], newData) <= 0) break;
		heap->data[pos] = heap->data[parentPos];
		pos = parentPos;
	}
	heap->data[pos] = newData;
	(heap->numOfData)++;
}

ElementType H_dequeue(Heap* heap){
	if (heap->numOfData == 0) {
		perror("[ERROR/ Dequeue()] Priority Queue is alreay Empty\n");
		exit(-1);
	}
	
	ElementType ret = heap->data[1];
	ElementType lastElement = heap->data[heap->numOfData];
	
	int parentIdx = 1, childIdx;
	
	while (childIdx = getHighPriorChild(heap, parentIdx)) {
		if (heap->comp(lastElement, heap->data[childIdx]) >= 0) break;
		heap->data[parentIdx] = heap->data[childIdx];
		parentIdx = childIdx;
	}
	heap->data[parentIdx] = lastElement;
	(heap->numOfData)--;
	
	return ret;
}