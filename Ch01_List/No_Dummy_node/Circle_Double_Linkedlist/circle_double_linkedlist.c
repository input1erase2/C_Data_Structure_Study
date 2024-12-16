#include <stdio.h>
#include <stdlib.h>
#include "circle_double_linkedlist.h"

// 새로운 노드를 동적할당 받고 반환하는 함수
Node* makeNode(ElementType data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

// 동적 메모리 반환하고 노드를 파괴하는 함수
void destroyNode(Node* node) {
	free(node);
}

// Head부터 순회하며 동적 메모리를 반환하고 연결리스트를 파괴하는 함수
void destroyList(Node** head) {
	Node* cur = (*head);
	Node* delNode = NULL;
	while (cur->next != (*head)) {
		delNode = cur;
		cur = cur->next;
		printf("\tDestroying... [%d]\n", delNode->data);
		free(delNode);	// 메모리 해제
	}
	printf("\tDestroying... [%d]\n", cur->data);
	free(cur);			// tail 노드 처리
	printf("\n(*head) was 0x%p -> now NULL\n", (*head));
	(*head) = NULL;		// 댕글링 포인터 처리
}

// Tail 노드에 newNode를 삽입하는 함수
void addNode(Node** head, Node* newNode) {
	if ((*head) == NULL) {
		(*head) = newNode;
		(*head)->prev = (*head);
		(*head)->next = (*head);
	}
	else addNodeAfter((*head)->prev, newNode);
}

// Tail 노드에 새로운 노드를 생성해서 삽입하는 함수
void addNodeByData(Node** head, ElementType newData) {
	Node* newNode = makeNode(newData);
	addNode(head, newNode);
}

// cur 노드 뒤에 newNode를 삽입하는 함수
void addNodeAfter(Node* cur, Node* newNode) {
	newNode->prev = cur;
	newNode->next = cur->next;
	cur->next->prev = newNode;
	cur->next = newNode;
}

// 연결리스트에서 delNode를 제거하는 함수
void removeNode(Node** head, Node* delNode) {
	if ((*head) == delNode) (*head) = (*head)->next;
	delNode->next->prev = delNode->prev;
	delNode->prev->next = delNode->next;
	free(delNode);
}

// 연결리스트에서 'delData'에 해당하는 요소를 찾아 제거하는 함수
void removeNodeByData(Node** head, ElementType delData) {
	Node* delNode = NULL;
	if ((*head)->data == delData) {
		delNode = (*head);
		delNode->prev->next = delNode->next;
		delNode->next->prev = delNode->prev;
		(*head) = delNode->next;
	}
	else {
		delNode = (*head)->next;
		while (delNode != (*head) && delNode->data != delData)
			delNode = delNode->next;
		
		// At the end of list, there is no 'delData' in the list.
		if (delNode->data != delData || delNode == (*head)) {
			printf("[ERROR] There is no such data in list!\n");
			return;
		}
		// 화살표 2개를 순서대로 제거한다.
		delNode->next->prev = delNode->prev;
		delNode->prev->next = delNode->next;
	}
	free(delNode);
}

// 연결리스트에서 'loc + 1'번째 요소를 찾아 반환하는 함수
Node* getNode(Node* head, int loc) {
	// loc이 전체 연결리스트 크기보다 큰 경우, loc을 줄인다
	int sz = getNodeCount(head);
	if (loc > sz) loc %= sz;
	
	Node* cur = head;
	while (cur && (--loc >= 0)) cur = cur->next;
	return cur;
}

// 연결리스트에 포함된 요소 개수를 반환하는 함수
unsigned int getNodeCount(Node* head) {
	unsigned int ret = 0;
	Node* cur = head;
	while (cur) {
		cur = cur->next;
		ret++;
		if (cur == head) break;
	}
	return ret;
}