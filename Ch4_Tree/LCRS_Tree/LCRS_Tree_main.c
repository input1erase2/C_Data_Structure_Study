#include "LCRS_Tree.h"

int main() {
    Node* a = LCRS_makeNode('A');
    Node* b = LCRS_makeNode('B');
    Node* c = LCRS_makeNode('C');
    Node* d = LCRS_makeNode('D');
    Node* e = LCRS_makeNode('E');
    Node* f = LCRS_makeNode('F');
    Node* g = LCRS_makeNode('G');
    Node* h = LCRS_makeNode('H');
    Node* i = LCRS_makeNode('I');
    Node* j = LCRS_makeNode('J');
    Node* k = LCRS_makeNode('K');

    LCRS_addChild(a, b);
        LCRS_addChild(b, c);
        LCRS_addChild(b, d);
            LCRS_addChild(d, e);
            LCRS_addChild(d, f);
    LCRS_addChild(a, g);
        LCRS_addChild(g, h);
    LCRS_addChild(a, i);
        LCRS_addChild(i, j);
            LCRS_addChild(j, k);
    
    printf("[Print all nodes in tree]\n");
    LCRS_printTree(a, 0);

    LCRS_destroyTree(a);
    return 0;
}