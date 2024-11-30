#include <stdio.h>
#include <stdlib.h>
#include "single_linked_list.h"

void makeList(List* list) {
    list->head = (Node*)malloc(sizeof(Node));   // Dummy
    list->head->next = NULL;
    list->comp = NULL;
    list->numOfData = 0;
}

static void addNodeFront(List* list, ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = list->head->next;
    list->head->next = newNode;
    (list->numOfData)++;
}

static void addNodeSort(List* list, ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    
    Node* temp = list->head;
    while (temp->next && list->comp(temp->next->data, newData) != 0)
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
    (list->numOfData)++;
}

void addNode(List* list, ElementType newData) {
    if (list->comp) addNodeSort(list, newData);
    else addNodeFront(list, newData);
}

int removeList(List* list) {
    Node* cur = list->head;
    Node* nxt = list->head->next;

    while (cur) {
        free(cur);
        cur = nxt;
        if (nxt) nxt = nxt->next;
    }
    list->cur       = NULL;
    list->before    = NULL;
    list->head      = NULL;
    list->numOfData = 0;
}

void removeNode(List* list, ElementType delData) {
    Node* cur = list->head;

    while (cur->next && cur->next->data != delData)
        cur = cur->next;

    if (cur->next == NULL) {
        printf("[ERROR] There is no such data in list\n");
        return;
    }
    Node* delNode = cur->next;
    cur->next = cur->next->next;

    free(delNode);
    (list->numOfData)--;
}

ElementType removeCur(List* list) {
    Node* delNode = list->cur;
    ElementType ret = delNode->data;

    list->before->next = list->cur->next;
    list->cur = list->before;   // Before 위치로 cur를 갱신
    
    free(delNode);
    (list->numOfData)--;

    return ret;
}

int moveCurFirst(List* list, ElementType* returnData) {
    // 리스트에 아무런 노드가 없는 경우
    if (list->head->next == NULL) return 0; // return False;

    list->before = list->head;
    list->cur = list->head->next;
    *returnData = list->cur->data;

    return 1;   // return True;
}

int moveCurNext(List* list, ElementType* returnData) {
    // cur 노드가 tail 노드인 경우
    if (list->cur->next == NULL) return 0;  // return False;

    list->before = list->cur;
    list->cur = list->cur->next;
    *returnData = list->cur->data;

    return 1;   // return True;
}

int getCount(List* list) {
    return list->numOfData;
}

void setSortRule(List* list, int (*comp)(ElementType a, ElementType b)) {
    list->comp = comp;
}
