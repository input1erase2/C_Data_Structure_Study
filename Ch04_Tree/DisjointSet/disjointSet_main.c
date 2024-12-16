#include "disjointSet.h"

int main() {
    int a = 1, b = 2, c = 3, d = 4;
    Node* set1 = set_make(&a);
    Node* set2 = set_make(&b);
    Node* set3 = set_make(&c);
    Node* set4 = set_make(&d);

    printf("Set1 == Set2 ? %s\n", 
        (set_findRoot(set1) == set_findRoot(set2)) ? "TRUE" : "FALSE");
    
    set_union(set1, set3);
    printf("Set1 == Set3 ? %s\n", 
        (set_findRoot(set1) == set_findRoot(set3)) ? "TRUE" : "FALSE");

    set_union(set3, set4);
    printf("Set3 == Set4 ? %s\n", 
        (set_findRoot(set3) == set_findRoot(set4)) ? "TRUE" : "FALSE");
    
    return 0;
}