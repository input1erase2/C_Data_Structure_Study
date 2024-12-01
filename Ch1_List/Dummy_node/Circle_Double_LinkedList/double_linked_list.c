#include <stdio.h> 
#include <stdlib.h>
#include "double_linked_list.h"

void makeList(List* list){
    // Dummy node 만들기
    list->tail = (Node*)malloc(sizeof(Node));
    // 자기자신 가리키기 (원형 연결리스트)
    list->tail->next = list->tail;
    list->tail->prev = list->tail;

    list->numOfData = 0;
}

void addNodeFront(List* list, ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    // Insert 'newNode' to behind of dummy head node.
    newNode->prev = list->tail;         // □ ← □   □
    newNode->next = list->tail->next;   // □ ← □ → □
    list->tail->next->prev = newNode;   // □ ← □ ↔ □
    list->tail->next = newNode;         // □ ↔ □ ↔ □

    (list->numOfData)++;
}

void addNodeBack(List* list, ElementType newData){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    // Insert 'newNode' to front of dummy tail node.
    newNode->prev = list->tail->prev;       // □ ← □   □ 
    newNode->next = list->tail;             // □ ← □ → □ 
    list->tail->prev->next = newNode;       // □ ↔ □ → □ 
    list->tail->prev = newNode;             // □ ↔ □ ↔ □ 

    (list->numOfData)++;
}

void removeList(List* list){
    Node* cur = list->tail->next;
    Node* nxt = NULL;
    while (cur != list->tail) {
        nxt = cur->next;
        printf("\tDestroying [%d]...\n", cur->data);
        free(cur);
        cur = nxt;
    }
    printf("\tDestroying [Dummy Tail Node]...\n");
    free(cur);
    list->numOfData = 0;
    list->cur = NULL;
    list->tail = NULL;
}

void removeNode(List* list, ElementType delData){
    Node* delNode = list->tail->next;
    while (delNode != list->tail && delNode->data != delData)
        delNode = delNode->next;
    if (delNode == list->tail) {
        printf("[Error] There is no such data in the list\n\n");
        return;
    }
    delNode->prev->next = delNode->next;
    delNode->next->prev = delNode->prev;
    free(delNode);
    (list->numOfData)--;
}

ElementType removeCur(List* list){
    Node* delNode = list->cur;
    ElementType ret = list->cur->data;
    
    list->cur->next->prev = list->cur->prev;
    list->cur->prev->next = list->cur->next;
    list->cur = list->cur->prev;
    
    free(delNode);
    (list->numOfData)--;
    
    return ret;
}

int moveCurFirst(List* list, ElementType* returnData){
    if (list->tail->next == list->tail) return FALSE;
    list->cur = list->tail->next;
    *returnData = list->cur->data;
    return TRUE;
}

int moveCurNext(List* list, ElementType* returnData){
    if (list->cur->next == list->tail) return FALSE;
    list->cur = list->cur->next;
    *returnData = list->cur->data;
    return TRUE;
}

int moveCurPrev(List* list, ElementType* returnData){
    if (list->cur->prev == list->tail) return FALSE;
    list->cur = list->cur->prev;
    *returnData = list->cur->data;
    return TRUE;
}

int getCount(List* list){
    return list->numOfData;
}
