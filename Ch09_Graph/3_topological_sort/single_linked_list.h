#ifndef __SINGLE_LINKED_LIST_H_
#define __SINGLE_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"              // 위상정렬을 위해 수정한 곳

typedef Vertex* ElementType;    // 위상정렬을 위해 수정한 곳

typedef struct _Node {
    ElementType data;
    struct _Node* next;
} Node;

typedef struct _List {
    Node* head;
    Node* cur;          // 각 연산에 도움을 주기 위한 노드
    Node* before;       // 특정 삭제 연산에 도움을 주기 위한 노드
    int numOfData;
    int (*comp)(ElementType lhs, ElementType rhs);
} SingleLinkedList;
typedef SingleLinkedList List;

void        makeList(List* list);
void        addNode(List* list, ElementType newData);
int         removeList(List* list);
void        removeNode(List* list, ElementType delData);
ElementType removeCur(List* list);
int         moveCurFirst(List* list, ElementType* returnData);
int         moveCurNext(List* list, ElementType* returnData);
int         getCount(List* list);
void        setSortRule(List* list, int (*comp)(ElementType a, ElementType b));

#endif