#ifndef __DOUBLE_LINKED_LIST_H_
#define __DOUBLE_LINKED_LIST_H_

#define TRUE    1
#define FALSE   0

typedef int ElementType;
typedef struct _Node {
    ElementType data;
    struct _Node* prev;
    struct _Node* next;
} Node;

typedef struct _List {
    Node* head;     // dummy
    Node* tail;     // dummy
    Node* cur;
    int numOfData;
} DoubleLinkedList;

typedef DoubleLinkedList List;


void        makeList(List* list);
void        addNode(List* list, ElementType newData);

int         removeList(List* list);
void        removeNode(List* list, ElementType delData);
ElementType removeCur(List* list);

int         moveCurFirst(List* list, ElementType* returnData);
int         moveCurNext(List* list, ElementType* returnData);
int         moveCurPrev(List* list, ElementType* returnData);

int         getCount(List* list);


#endif