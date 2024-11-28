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

void addNode(Node** head, ElementType newData) {
    if ((*head) == NULL)
        (*head) = makeNode(newData);
    else {
        Node* cur = (*head);
        while (cur->next) cur = cur->next;
        cur->next = makeNode(newData);
    }
}

void addNodeAfter(Node* curr, Node* newNode) {
    newNode->next = curr->next;
    curr->next = newNode;
}

void addNodeNewHead(Node** head, Node* newNode) {
    if ((*head) != NULL) newNode->next = (*head);
    (*head) = newNode;
}

void removeNode(Node** head, Node* delNode) {
    
}

Node* getNode(Node* head, int loc) {

}

int getNodeCount(Node* head) {

}
