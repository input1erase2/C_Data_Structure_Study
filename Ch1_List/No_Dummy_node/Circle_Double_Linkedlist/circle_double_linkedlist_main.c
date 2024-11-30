#include <stdio.h>
#include "circle_double_linkedlist.h"


void printList(Node* head) {
	Node* cur = head;
	// Test 'getNode' and 'getNodeCount'
	unsigned int size = getNodeCount(head);
	for (unsigned int i = 0; i < size; ++i) {
		cur = getNode(head, i);
		printf("List[%d] >> ", i);
		printf("Prev: %4d\t", cur->prev->data);
		printf("Curr: %4d\t", cur->data);
		printf("Next: %4d\t\n", cur->next->data);
	}
	printf("\n\n");
}

int main() {
	int i = 0;
	Node* list		= NULL;
	Node* cur		= NULL;
	Node* newNode	= NULL;
	
	// Testing addNode
	for (; i < 5; ++i) {
		newNode = makeNode(10 * (i + 1));
		addNode(&list, newNode);
	}
	// Testing addNodeByData
	addNodeByData(&list, 10 * (++i));	// addNodeByData(&list, 60)
	addNodeByData(&list, 10 * (++i));	// addNodeByData(&list, 70)
	printList(list);
	
	// Testing addNodeAfter
	printf("[Adding 3000 after [4], Check if [5] is 3000]\n\n");
	newNode = makeNode(3000);
	cur = getNode(list, 4);
	addNodeAfter(cur, newNode);
	printList(list);
	
	// Testing removeNode -- head
	printf("[Removing head, Check if head is changed]\n\n");
	cur = getNode(list, 0);
	removeNode(&list, cur);
	printList(list);
	
	// Testing removeNode -- not head
	printf("[Removing [4] in list]\n\n");
	cur = getNode(list, 4);
	removeNode(&list, cur);
	printList(list);
	
	// Testing removeNodeByData
	printf("[Removing 3000 in list]\n\n");
	removeNodeByData(&list, 3000);
	printList(list);
	
	// Testing destryList
	printf("[Destroying list]\n\n");
	destroyList(&list);
	if (list == NULL) printf("This is main(), list is NULL. End program...\n\n");
	else printf("Something is wrong, list is not NULL\n \
		'destoryList()' doesn't free the list properly\n\n");
	
	return 0;
}