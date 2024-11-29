#include <stdio.h>
#include <stdlib.h>
#include "double_linkedlist.h"

// 새로운 노드를 동적할당 받고 반환하는 함수
Node* makeNode(ElementType data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;       // Double linkedlist

    return newNode;
}

// 동적 메모리 반환하고 노드를 파괴하는 함수
void destroyNode(Node* node) {
    free(node);
}

// Head부터 순회하며 동적 메모리를 반환하고 연결리스트를 파괴하는 함수
void destroyList(Node** head) {
    Node* nxt = (*head)->next;
    while (nxt) {
        printf("\tDestroying... [%d]\n", (*head)->data);
        free((*head));
        nxt = nxt->next;
        (*head) = nxt;
    }
    printf("\tDestroying... [%d]\n", (*head)->data);
    free((*head));
    (*head) = NULL;
}

// Tail 노드에 newNode를 삽입하는 함수
void addNode(Node** head, Node* newNode) {
    if ((*head) == NULL) (*head) = newNode;
    else {
        Node* cur = (*head);
        while (cur->next) cur = cur->next;

        cur->next = newNode;
        newNode->prev = cur;    // Double linkedlist
    }
}

// cur 노드 뒤에 newNode를 삽입하는 함수
void addNodeAfter(Node* cur, Node* newNode) {
    newNode->prev = cur;
    newNode->next = cur->next;
    if (cur->next != NULL) {
        cur->next->prev = newNode;
        cur->next = newNode;
    }
}

// 연결리스트에서 delNode를 제거하는 함수
void removeNode(Node** head, Node* delNode) {
    // Case 1. delNode가 head인 경우
    if ((*head) == delNode) {
        // head를 다음 칸으로 옮겨준 뒤 delNode를 제거한다.
        (*head) = (*head)->next;
        if ((*head) != NULL) {
            free((*head));
            (*head)->prev = NULL;
        }
    } 
    // Case 2. delNode가 head가 아닌 경우
    else {
        // 화살표 2개를 순서대로 제거한다.
        Node* temp = delNode;
        if (delNode->prev) delNode->prev->next = temp->next;
        if (delNode->next) delNode->next->prev = temp->prev;
        free(delNode);
    }
}

// 연결리스트에서 'delData'에 해당하는 요소를 찾아 제거하는 함수
void removeNodeByData(Node** head, ElementType delData) {
    Node* delNode = NULL;
    if ((*head)->data == delData) {
        delNode = (*head);
        (*head) = (*head)->next;
        if ((*head) != NULL) (*head)->prev = NULL;
    }
    else {
        Node* cur = (*head);
        while (cur->next && cur->next->data != delData) cur = cur->next;
        
        // At the end of list, there is no 'delData' in the list.
        if (cur->next == NULL && cur->data != delData) {
            printf("[ERROR] There is no such data in list!\n");
            return;
        }
        // 화살표 2개를 순서대로 제거한다
        delNode = cur->next;
        if (delNode->next) delNode->next->prev = cur;
        cur->next = delNode->next;
    }
    free(delNode);
    delNode->prev = NULL;
    delNode->next = NULL;
}

// 연결리스트에서 'loc + 1'번째 요소를 찾아 반환하는 함수
Node* getNode(Node* head, int loc) {
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
    }
    return ret;
}

