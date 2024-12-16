#include <stdio.h>
#include "bintree.h"
#include "bst.h"

void myPrint(const Node* a, const Node* b) {
    printf("[L = ");
    if (a == NULL) printf("NULL, ");
    else printf("%d, ", BT_getData(a));

    printf("R = ");
    if (b == NULL) printf("NULL]\n\n");
    else printf("%d]\n\n", BT_getData(b));
}

int main() {
    Node* bst;
    BST_init(&bst);
    BST_insert(&bst, 1);    BST_insert(&bst, 2);    BST_insert(&bst, 3);
    BST_insert(&bst, 4);    BST_insert(&bst, 5);    BST_insert(&bst, 6);
    BST_insert(&bst, 7);    BST_insert(&bst, 8);    BST_insert(&bst, 9);
    
    printf("Root node = %d\n", BT_getData(bst));

    Node* l1 = BT_getLeftSubtree(bst);
    Node* r1 = BT_getRightSubtree(bst);
    myPrint(l1, r1);

    printf("Going deep to left child...\n");
    Node* l2 = BT_getLeftSubtree(l1);
    Node* r2 = BT_getRightSubtree(l1);
    myPrint(l2, r2);

    printf("Going deep to right child...\n");
    Node* l3 = BT_getLeftSubtree(r1);
    Node* r3 = BT_getRightSubtree(r1);
    myPrint(l3, r3);

    printf("Going deep to right child's right child...\n");
    Node* l4 = BT_getLeftSubtree(r3);
    Node* r4 = BT_getRightSubtree(r3);
    myPrint(l4, r4);

    return 0;
}