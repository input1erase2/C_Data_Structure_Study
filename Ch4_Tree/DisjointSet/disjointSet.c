#include "disjointSet.h"

void set_union(Node* s1, Node* s2) {
    s2 = set_findRoot(s2);
    s2->parent = s1;
}

Node* set_findRoot(Node* set) {
    while (set->parent != NULL)
        set = set->parent;
    return set;
}

Node* set_make(void* newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->parent = NULL;
    newNode->data = newData;
    return newNode;
}

void set_destroy(Node* set) {
    free(set);
}
