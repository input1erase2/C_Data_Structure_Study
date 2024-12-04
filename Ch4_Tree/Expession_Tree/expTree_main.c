#include "expTree.h"

int main() {
    Node* tree = NULL;
    char postfixExp[20] = "71*52-/";
    buildExpressionTree(&tree, postfixExp);

    printf("[Preorder] >> ");
    printTreePreorder(tree); printf("\n");

    printf("[Inorder] >> ");
    printTreeInorder(tree); printf("\n");

    printf("[Postorder] >> ");
    printTreePostorder(tree); printf("\n");

    printf("Calculation result >> %lf\n\n", calculate(tree));

    destroyTree(tree);
    
    return 0;
}

/*
char postfixExp[20] = "71*52-/";

[Preorder] >>  / * 7 1 - 5 2
[Inorder] >>  7 * 1 / 5 - 2
[Postorder] >>  7 1 * 5 2 - /
Calculation result >> 2.333333
*/