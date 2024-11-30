#include <stdio.h>
#include <stdlib.h>
#include "single_linkedlist.h"

// 동적 메모리 할당 후 새로운 노드를 만들어 반환하는 함수
Node* makeNode(ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    return newNode;
}

// 동적 메모리 반환으로 노드 파괴하는 함수
void destroyNode(Node* node) {
    free(node);
}

// Head 부터 시작해서 동적 메모리를 반환하며 연결리스트를 파괴하는 함수
void destroyList(Node** head) {
    // 원본포인터도 NULL포인터 포기화하기 위해 2중 포인터 매개변수로 받는다.
    Node* nxt = (*head)->next;

    while (nxt) {
        free((*head));
        (*head) = nxt;
        nxt = nxt->next;
    }
    free((*head));  // tail node 처리까지 마무리

    /* (중요) 이곳에서 메모리를 해제했지만, main()에서 원본포인터를 통해 해당 메모리 영역을
    다시 참조하려고 시도할 수 있다. (e.g. printList(head))
    Dangling pointer를 막기 위해 원본포인터도 NULL로 초기화해준다. */
    (*head) = NULL;
}

// tail에 새로운 노드를 추가하는 함수
void addNode(Node** head, Node* newNode) {
    if ((*head) == NULL) (*head) = newNode;
    else {
        Node* cur = (*head);
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }
}

// tail에 새로운 '만들어' 노드를 추가하는 함수
void addNodeByValue(Node** head, ElementType newData) {
    if ((*head) == NULL) (*head) = makeNode(newData);
    else {
        Node* cur = (*head);
        while (cur->next) cur = cur->next;
        cur->next = makeNode(newData);
    }
}

// 새로운 노드를 head로 바꾸는 함수
void addNodeNewHead(Node** head, Node* newNode) {
    // 빈 연결리스트가 아니라면, newNode의 next를 head를 가리키도록 한다.
    if ((*head) != NULL) newNode->next = (*head);
    // 반 연결리스트든 아니든 이제 newNode는 새로운 head가 된다.
    (*head) = newNode;
}

// 'cur'노드 뒤에 'newNode'를 삽입하는 함수
void addNodeAfter(Node* cur, Node* newNode) {
    newNode->next = cur->next;
    cur->next = newNode;
}

// 'cur'노드 앞에 'newNode'를 삽입하는 함수
// 이때, head가 바뀔 여지가 있으므로 2중 포인터 매개변수 head가 필요하다.
void addNodeBefore(Node** head, Node* cur, Node* newNode) {
    // 넣는 위치가 head 앞이라면, addNodeNewHead()와 같다.
    if ((*head) == cur) {
        addNodeNewHead(head, newNode);
        return;
    }
    Node* prevCur = (*head);
    while (prevCur->next != cur) prevCur = prevCur->next;
    newNode->next = cur;
    prevCur->next = newNode;
}

// 연결리스트 속에서 'delNode'를 삭제하는 함수
void removeNode(Node** head, Node* delNode) {
    // delNode의 앞자리를 찾은 뒤, delNode 뒷자리와 이어준다.
    if ((*head) != delNode) {
        Node* cur = (*head);
        while (cur && cur->next != delNode) cur = cur->next;
        if (cur && cur->next == delNode) cur->next = delNode->next;
    }
    else {  // (*head) == delNode
        (*head) = (*head)->next;    // new head, or NULL
    }
    // delNode를 삭제한다.
    free(delNode);
}

// 연결리스트 속에서 'delData' 값을 찾아 삭제하는 함수
void removeNodeByData(Node** head, ElementType delData) {
    Node* cur = (*head);
    if (cur == NULL) return;
    if (cur->data == delData) { // Erase head
        (*head) = (*head)->next;
        free(cur);
    }
    else {
        while (cur->next->data != delData) cur = cur->next;
        Node* delNode = cur->next;
        cur->next = cur->next->next;
        free(delNode);
    }
}

// 연결리스트 속에서 (loc + 1)번째 노드를 반환하는 함수
Node* getNode(Node* head, int loc) {
    if (loc > getNodeCount(head)) {
        printf("loc is larger than list size\n");
        return NULL;
    }
    Node* cur = head;
    while (loc-- && cur) cur = cur->next;
    return cur;
}

// 연결리스트에 포함된 노드 개수를 새는 함수
int getNodeCount(Node* head) {
    int ret = 0;
    Node* cur = head;
    while (cur) { 
        cur = cur->next;
        ret++;
    }
    return ret;
}
