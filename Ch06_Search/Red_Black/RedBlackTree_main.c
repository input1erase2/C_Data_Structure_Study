#include <stdio.h>
#include "RedBlackTree.h"

// 모든 리프노드의 양쪽 자식노드가 가리킬 Nil 노드
// RedBlackTree.c에서 extern으로 외부참조한다.
Node* Nil;

int main() {
    Node* tree = NULL;
    Node* tempNode = NULL;

    Nil = RBT_createNode(0);
    Nil->color = BLACK;         // Nil은 무조건 검정색이다. (RB 트리의 규칙상)

    while (1) {
        int cmd     = 0;
        int param   = 0;
        char buffer[10];
        
        printf("==============================\n");
        printf("1. Create\t2. Remove\n");
        printf("3. Search\t4. Display\n");
        printf("5. Quit\n");
        printf("==============================\n");
        printf("Enter command number please >> ");

        fgets(buffer, sizeof(buffer) - 1, stdin);
        sscanf(buffer, "%d", &cmd);
        
        if (cmd < 1 || cmd > 5) {
            printf("Invalid command number!\n");
            continue;
        }
        else if (cmd == 4) {
            printf("<Value> <Color> [<Direction>, <Parent's Value>] --- Count of black nodes\n");
            RBT_printTree(tree, 0, 0);
            printf("\n");
            continue;
        }
        else if (cmd == 5) break;
        
        printf("Enter parameter (1~200) >> ");
        
        fgets(buffer, sizeof(buffer) - 1, stdin);
        sscanf(buffer, "%d", &param);

        if (param < 1 || param > 200) {
            printf("Invalid parameter input!\n");
            continue;
        }

        switch(cmd) {
        case 1: 
            RBT_insert(&tree, RBT_createNode(param));
            break;
        case 2:
            tempNode = RBT_remove(&tree, param);
            if (tempNode == NULL)
                printf("Target delete node (%d) is not found!", param);
            else
                RBT_destroyNode(tempNode);
            break;
        case 3:
            tempNode = RBT_search(tree, param);
            if (tempNode == NULL)
                printf("Target search node (%d) is not found!", param);
            else
                printf("Found node: %d(Color: %s)\n",
                    tempNode->data, (tempNode->color == RED) ? "RED" : "BLACK");
            break;
        }
        printf("\n");
    }

    RBT_destroyTree(tree);

    return 0;
}

/*
Enter command number please >> 4
<Value> <Color> [<Direction>, <Parent's Value>] --- Count of black nodes
99 BLACK [X, -1]
    95 RED [L, 99]
        94 BLACK [L, 95] -------- 2
        97 BLACK [R, 95]
            96 RED [L, 97] -------- 2
            98 RED [R, 97] -------- 2
    101 RED [R, 99]
        100 BLACK [L, 101] -------- 2
        102 BLACK [R, 101] -------- 2

99
|
95----------101
|           |
94--97      100-102
    |   
    96--98
*/