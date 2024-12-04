#include "LCRS_Tree.h"

Node*   LCRS_makeNode(ElementType newData) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newData;
    newNode->lc = NULL;
    newNode->rs = NULL;
    
    return newNode;
}

void    LCRS_destroyNode(Node* node) {
    free(node);
}

void    LCRS_destroyTree(Node* root) {
    if (root->rs != NULL) LCRS_destroyTree(root->rs);
    if (root->lc != NULL) LCRS_destroyTree(root->lc);
    root->rs = NULL;
    root->lc = NULL;
    LCRS_destroyNode(root);
}

void    LCRS_addChild(Node* parent, Node* child) {
    if (parent->lc == NULL) parent->lc = child;
    else {
        Node* temp = parent->lc;
        while (temp->rs) temp = temp->rs;
        temp->rs = child;
    }
}

void    LCRS_printTree(Node* node, int lv) {
    for (int i = 0; i < lv - 1; ++i) printf("   ");     // 3 whitespace
    if (lv > 0) printf("+--");
    printf("%c\n", node->data);
    if (node->lc) LCRS_printTree(node->lc, lv + 1);
    if (node->rs) LCRS_printTree(node->rs, lv);
}
