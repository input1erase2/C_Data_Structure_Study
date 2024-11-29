#include <stdio.h>
#include "double_linkedlist.h"


void printList(Node* head) {
    Node* cur = head;
    // Test 'getNode' and 'getNodeCount'
    unsigned int size = getNodeCount(head);
    for (int i = 0; i < size; ++i) {
        cur = getNode(head, i);
        printf("List[%d] >> ", i);

        if (cur->prev) printf("Prev: %4d\t", cur->prev->data);
        else printf("Prev: NULL\t");
        
        printf("Curr: %4d\t", cur->data);
        
        if (cur->next) printf("Next: %4d\t", cur->next->data);
        else printf("Next: NULL\t");
        printf("\n");
    }
    printf("\n\n");
}

int main() {
    Node* head = NULL;
    Node* newNode = NULL;
    Node* cur = NULL;

    // Test adding Node
    for (int i = 0; i < 5; ++i) {
        newNode = makeNode(10 * (i + 1));
        addNode(&head, newNode);
    }
    printList(head);

    // Test 'addNodeAfter'
    printf("Inserting 3000 After [2]\n\n");
    cur = getNode(head, 2);
    newNode = makeNode(3000);
    addNodeAfter(cur, newNode);
    printList(head);


    // Test 'removeNodeByData' and 'removeNode'
    printf("Removing 3000, and [1]\n\n");
    removeNodeByData(&head, 3000);
    printList(head);

    cur = getNode(head, 1);
    removeNode(&head, cur);
    printList(head);

    // Test 'destroyList' and memory deallocation
    printf("Destroying list...\n");
    destroyList(&head);
    if (head != NULL) printList(head);
    else printf("Destroy completed\n\n");

    return 0;
}