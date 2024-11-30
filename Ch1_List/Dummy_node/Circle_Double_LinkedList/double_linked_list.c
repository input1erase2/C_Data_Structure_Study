#include <stdio.h> 
#include "double_linked_list.h"

void makeList(List* list){
    // Dummy node 만들기
    list->head = (Node*)malloc(sizeof(Node));
    list->tail = (Node*)malloc(sizeof(Node));
    // dummy head -> dummy tail 
    list->head->next = list->tail;
    list->head->prev = list->tail;
    // dummy tail -> dummy head
    list->tail->next = list->head;
    list->tail->prev = list->head;

    list->numOfData = 0;
}

void addNode(List* list, ElementType newData){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;

    // Insert 'newNode' to behind of dummy tail node.
    newNode->prev = list->tail->prev;       // □ ← □ □ 
    newNode->next = list->tail;             // □ ← □ → □ 
    list->tail->prev->next = newNode;       // □ ↔ □ → □ 
    list->tail->prev = newNode;             // □ ↔ □ ↔ □ 

    (list->numOfData)++;
}

int removeList(List* list){
    
}

void removeNode(List* list, ElementType delData){

}

ElementType removeCur(List* list){

}

int moveCurFirst(List* list, ElementType* returnData){

}

int moveCurNext(List* list, ElementType* returnData){

}

int moveCurPrev(List* list, ElementType* returnData){

}

int getCount(List* list){

}
