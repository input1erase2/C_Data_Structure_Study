#ifndef __HEAP_H_
#define __HEAP_H_

#define TRUE		1
#define FALSE		0
#define HEAP_SIZE 100
typedef char ElementType;

typedef int PriorityComp(ElementType lhs, ElementType rhs);

typedef struct _Heap {
	ElementType data[HEAP_SIZE];
	int numOfData;
	PriorityComp* comp;
} Heap;

void H_init(Heap* heap, PriorityComp foo);
int H_isEmpty(Heap* heap);
void H_enqueue(Heap* heap, ElementType newData);
ElementType H_dequeue(Heap* heap);

#endif