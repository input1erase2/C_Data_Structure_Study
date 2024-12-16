#ifndef __DISJOINT_SET_H_
#define __DISJOINT_SET_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    struct _Node* parent;
    void* data;
} Node;

void    set_union(Node* s1, Node* s2);
Node*   set_findRoot(Node* set);
Node*   set_make(void* newData);
void    set_destroy(Node* set);

#endif