#include <stdio.h>
#include "single_linkedlist.h"

void printList(Node* head) {
    Node* cur = NULL;
    
    // Test 'getNode' and 'getNodeCount'
    int size = getNodeCount(head);
    printf("Current node count in list --- %d\n", size);
    
    for (int i = 0; i < size; ++i) {
        cur = getNode(head, i);
        printf("List[%d]: %d\n", i, cur->data);
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

    // Test switching head
    newNode = makeNode(-123);
    addNodeNewHead(&head, newNode);
    newNode = makeNode(-456);
    addNodeNewHead(&head, newNode);

    printList(head);
    
    // Test 'addNodeAfter'
    printf("Inserting 3000 After [2]\n\n");
    cur = getNode(head, 2);
    newNode = makeNode(3000);
    addNodeAfter(cur, newNode);
    printList(head);


    // Test 'addNodeBefore'
    printf("Inserting 5000 before [2]\n\n");
    cur = getNode(head, 2);
    newNode = makeNode(5000);
    addNodeBefore(&head, cur, newNode);
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