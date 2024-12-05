#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    Node* bst;
    BST_init(&bst);
    BST_insert(&bst, 5);    BST_insert(&bst, 8);    BST_insert(&bst, 1);
    BST_insert(&bst, 6);    BST_insert(&bst, 4);    BST_insert(&bst, 9);
    BST_insert(&bst, 3);    BST_insert(&bst, 2);    BST_insert(&bst, 7);
    
    Node* tmp = NULL;
    BST_show(bst);  printf("\n");

    tmp = BST_remove(&bst, 3);
    printf("[Remove node '3'] >> ");
    BST_show(bst);  printf("\n");
    free(tmp);

    tmp = BST_remove(&bst, 8);
    printf("[Remove node '8'] >> ");
    BST_show(bst);  printf("\n");
    free(tmp);

    tmp = BST_remove(&bst, 1);
    printf("[Remove node '1'] >> ");
    BST_show(bst);  printf("\n");
    free(tmp);

    tmp = BST_remove(&bst, 6);
    printf("[Remove node '6'] >> ");
    BST_show(bst);  printf("\n");
    free(tmp);

    tmp = BST_remove(&bst, 5);
    printf("[Remove root node '5'] >> ");
    BST_show(bst);  printf("\n");
    free(tmp);

    return 0;
}