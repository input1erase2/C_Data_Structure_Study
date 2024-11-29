#include <stdio.h>
#include <stdlib.h>
#include "single_linkedlist.h"

Node* makeNode(ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    return newNode;
}

void destroyNode(Node* node) {
    free(node);
}

void destroyList(Node** head) {
    Node* nxt = (*head)->next;

    while (nxt) {
        free((*head));
        (*head) = nxt;
        nxt = nxt->next;
    }
    free((*head));  // for tail node
    (*head) = NULL;
}

void addNode(Node** head, Node* newNode) {
    if ((*head) == NULL) (*head) = newNode;
    else {
        Node* cur = (*head);
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }
}

void addNodeByValue(Node** head, ElementType newData) {
    if ((*head) == NULL) (*head) = makeNode(newData);
    else {
        Node* cur = (*head);
        while (cur->next) cur = cur->next;
        cur->next = makeNode(newData);
    }
}

void addNodeAfter(Node* cur, Node* newNode) {
    newNode->next = cur->next;
    cur->next = newNode;
}

void addNodeNewHead(Node** head, Node* newNode) {
    if ((*head) != NULL) newNode->next = (*head);
    (*head) = newNode;
}

void addNodeBefore(Node** head, Node* cur, Node* newNode) {
    if ((*head) == cur) {
        addNodeNewHead(head, newNode);
        return;
    }
    Node* prevCur = (*head);
    while (prevCur->next != cur) prevCur = prevCur->next;
    newNode->next = cur;
    prevCur->next = newNode;
}

void removeNode(Node** head, Node* delNode) {
    if ((*head) != delNode) {
        Node* cur = (*head);
        while (cur && cur->next != delNode) cur = cur->next;
        if (cur && cur->next == delNode) cur->next = delNode->next;
    }
    else {  // (*head) == delNode
        (*head) = (*head)->next;    // new head, or NULL
    }
    free(delNode);
}

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

Node* getNode(Node* head, int loc) {
    if (loc > getNodeCount(head)) {
        printf("loc is larger than list size\n");
        return NULL;
    }
    Node* cur = head;
    while (loc-- && cur) cur = cur->next;
    return cur;
}

int getNodeCount(Node* head) {
    int ret = 0;
    Node* cur = head;
    while (cur) { 
        cur = cur->next;
        ret++;
    }
    return ret;
}
