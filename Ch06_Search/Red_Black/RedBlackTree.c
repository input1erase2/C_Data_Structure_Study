#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RedBlackTree.h"

extern Node* Nil;

// 새로운 노드를 메모리 동적할당으로 생성한 뒤 반환하는 함수
Node* RBT_createNode(ElementType newData) {
    Node* newNode   = (Node*)malloc(sizeof(Node));
    newNode->data   = newData;
    newNode->color  = BLACK;
    newNode->parent = NULL;
    newNode->left   = NULL;
    newNode->right  = NULL;
    return newNode;
}
// 동적할당받아 생성된 노드의 메모리를 해제하는 함수
void RBT_destroyNode(Node* node) {
    free(node);
}
// 재귀호출을 이용해 Red-black 트리의 모든 노드를 제거하는 함수
void RBT_destroyTree(Node* tree) {
    if (tree->right != Nil) RBT_destroyTree(tree->right);
    if (tree->left != Nil) RBT_destroyTree(tree->left);
    tree->left = Nil;
    tree->right = Nil;
    RBT_destroyNode(tree);
}
// Red-black 트리에서 특정 키값을 가진 노드를 찾아 반환하는 함수
Node* RBT_search(Node* tree, ElementType target) {
    if (tree == Nil) return NULL;

    if (tree->data > target) return RBT_search(tree->left, target);
    else if (tree->data < target) return RBT_search(tree->right, target);
    else return tree;
}
// Red-black 트리에서 키값이 가장 작은 노드를 찾아 반환하는 함수
Node* RBT_searchMin(Node* tree) {
    Node* ret = tree;
    while (ret->left != Nil) ret = ret->left;
    return ret;
}
// Red-black 트리에서 키값이 가장 큰 노드를 찾아 반환하는 함수
Node* RBT_searchMax(Node* tree) {
    Node* ret = tree;
    while (ret->right != Nil) ret = ret->right;
    return ret;
}
/* 리밸런싱 도구 - center 노드를 중심으로 좌회전 하는 함수
 (RR상태 회전, 화살표 6개 움직여야 함) */
void RBT_rotateLeft(Node** tree, Node* center) {
    Node* child = center->right;
    center->right = child->left;            // 1
    if (child->left != Nil)
        child->left->parent = center;       // 2
    child->parent = center->parent;         // 3
    if (center->parent == NULL) (*tree) = child;
    else {
        if (center->parent->left == center)
            center->parent->left = child;   // 4
        else
            center->parent->right = child;  // 4
    }
    child->left = center;                   // 5
    center->parent = child;                 // 6
}
/* 리밸런싱 도구 - center 노드를 중심으로 우회전 하는 함수
 (LL상태 회전, 화살표 6개 움직여야 함) */
void RBT_rotateRight(Node** tree, Node* center) {
    Node* child = center->left;
    center->left = child->right;            // 1
    if (child->right != Nil)
        child->right->parent = center;      // 2
    child->parent = center->parent;         // 3
    if (center->parent == NULL) (*tree) = child;
    else {
        if (center->parent->left == center)
            center->parent->left = child;   // 4
        else
            center->parent->right = child;  // 4
    }
    child->right = center;                  // 5
    center->parent = child;                 // 6
}
// 새로운 노드를 BST 규칙에 따라 삽입하고 Red-black 규칙에 따라 리밸런싱 하는 함수
void RBT_insert(Node** tree, Node* newNode) {
    RBT_insertHelper(tree, newNode);

    newNode->color = RED;   // 새로운 노드는 빨간색
    newNode->left = Nil;    // 새로운 노드는 두 NIL 노드를 자식으로
    newNode->right = Nil;   // 새로운 노드는 두 NIL 노드를 자식으로

    RBT_rebuildAfterInsert(tree, newNode);
}
// 새로운 노드를 BST 규칙에 따라 삽입하는 함수
void RBT_insertHelper(Node** tree, Node* newNode) {
    if ((*tree) == NULL) (*tree) = newNode;
    else {
        if ((*tree)->data > newNode->data) {
            if ((*tree)->left == Nil) {
                (*tree)->left = newNode;
                newNode->parent = (*tree);
            }
            else
                RBT_insertHelper(&(*tree)->left, newNode);
        }
        else if ((*tree)->data < newNode->data) {
            if ((*tree)->right == Nil) {
                (*tree)->right = newNode;
                newNode->parent = (*tree);
            }
            else
                RBT_insertHelper(&(*tree)->right, newNode);
        }
    }
}
// 새로운 노드 삽입 후 Red-black 트리 규칙에 따라 리밸런싱 하는 함수
void RBT_rebuildAfterInsert(Node** tree, Node* cur) {
    Node* uncle = NULL;
    while (cur != (*tree) && cur->parent->color == RED) {
        // Case 1. 부모가 왼쪽 자식노드인 경우
        if (cur->parent == cur->parent->parent->left) {
            uncle = cur->parent->parent->right;     // 삼촌은 오른쪽 자식노드
            // Case 1.1. 삼촌도 빨간색인 경우
            if (uncle->color == RED) {
                uncle->color                = BLACK;    // 삼촌을 검정색으로
                cur->parent->color          = BLACK;    // 부모를 검정색으로
                cur->parent->parent->color  = RED;      // 할아버지를 빨간색으로
                cur = cur->parent->parent;              // 재귀적으로 올라간다.
            }
            else {
                // Case 1.2. 삼촌이 검정색 + 새로운 노드가 오른쪽 자식노드인 경우 
                if (cur->parent->right == cur) {
                    // 부모노드를 기준으로 좌회전(RR상태 회전)
                    cur = cur->parent;
                    RBT_rotateLeft(tree, cur);
                }
                // Case 1.3. 삼촌이 검정색 + 새로운 노드가 왼쪽 자식노드인 경우
                cur->parent->color          = BLACK;        // 부모를 검정색으로
                cur->parent->parent->color  = RED;          // 할아버지를 빨간색으로
                // 할아버지를 기준으로 우회전(LL상태 회전)
                RBT_rotateRight(tree, cur->parent->parent);
            }
        }
        // Case 2. 부모가 오른쪽 자식노드인 경우
        else {
            uncle = cur->parent->parent->left;      // 삼촌은 왼쪽 자식노드
            if (uncle->color == RED) {
                uncle->color                = BLACK;    // 삼촌을 검정색으로
                cur->parent->color          = BLACK;    // 부모를 검정색으로
                cur->parent->parent->color  = RED;      // 할아버지를 빨간색으로
                cur = cur->parent->parent;              // 재귀적으로 올라간다
            }
            else {
                // Case 2.2. 삼촌이 검정색 + 새로운 노드가 왼쪽 자식노드인 경우
                if (cur->parent->left == cur) {
                    // 부모노드를 기준으로 우회전(RR상태 회전)
                    cur = cur->parent;
                    RBT_rotateRight(tree, cur);
                }
                // Case 2.3. 삼촌이 검정색 + 새로운 노드가 오른쪽 자식노드인 경우
                cur->parent->color          = BLACK;
                cur->parent->parent->color  = RED;
                RBT_rotateLeft(tree, cur->parent->parent);
            }
        }
    }
    (*tree)->color = BLACK;     // [중요!] Red-black 트리의 루트노드는 검정색이다 
}
// Red-black 트리에서 타겟노드를 찾아 제거하는 함수
Node* RBT_remove(Node** tree, ElementType targetData) {
    Node* delNode = NULL;
    Node* successor = NULL;
    Node* target = RBT_search((*tree), targetData);

    if (target == NULL) return NULL;    // 대상이 트리에 없음

    // Step 1. 제거할 노드인 delNode를 올바르게 설정하기
    if (target->left == Nil || target->right == Nil) {
        // 제거할 노드가 자식노드가 0개 또는 1개인 경우
        delNode = target;
    }
    else {
        // 제거할 노드가 자식노드가 2개인 경우, 우측 서브트리에서 최소노드를 찾고 교체
        delNode = RBT_searchMin(target->right);
        target->data = delNode->data;
    }
    // Step 2. 제거할 노드의 자리를 대체할 후계자 노드 successor 올바르게 설정하기
    // 자식노드가 1개인 경우, 그것도 왼쪽 자식노드인 경우 vs 자식노드가 0개 또는 2개인 경우
    successor = (delNode->left != Nil) ? delNode->left : delNode->right;

    // Step 3. successor 노드를 올바른 자리로 옮기기
    successor->parent = delNode->parent;
    if (delNode->parent == NULL) (*tree) = successor;   // 루트노드로 지정
    else {
        if (delNode->parent->left == delNode) delNode->parent->left = successor;
        else delNode->parent->right = successor;
    }
    // step 4. [중요] 제거할 노드가 검정색인경우 Red black 트리 규칙이 깨질 수 있음.
    if (delNode->color == BLACK) RBT_rebuildAfterRemove(tree, successor);

    return delNode;
}
// 타겟 노드 제거 후 Red-black 트리 규칙에 따라 리밸런싱 하는 함수
void RBT_rebuildAfterRemove(Node** tree, Node* successor) {
    Node* sibling = NULL;
    while (successor->parent != NULL && successor->color == BLACK) {
        // Case 1. 2중 검정색노드가 왼쪽 자식노드인 경우
        if (successor = successor->parent->left) {
            sibling = successor->parent->right;             // 형제는 오른쪽 자식 
            // Case 1.1. 형제노드가 빨간색인 경우
            if (sibling->color == RED) {
                sibling->color = BLACK;                     // 형제를 검은색으로
                successor->parent->color = RED;             // 부모를 빨간색으로
                RBT_rotateLeft(tree, successor->parent);    // 부모를 기준으로 좌회전
                // 회전함으로써 이제 형제노드가 검정색인 경우로 문제가 변경된다.
            }
            else {
                // Case 1.2. 형제노드가 검정색 + 양쪽 조카가 모두 검정색인 경우
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;           // 형제를 빨간색으로
                    successor = successor->parent;  // 2중 검정색노드 중 검정색 하나를 부모에게 넘겨주는 표현
                }
                else {
                    // Case 1.3. 왼쪽 조카가 빨간색인 경우
                    if (sibling->left->color == RED) {
                        sibling->color = RED;               // 형제를 빨간색으로
                        sibling->left->color = BLACK;       // 조카를 검정색으로
                        RBT_rotateRight(tree, sibling);     // 형제를 기준으로 우회전
                        // 회전함으로써 형제 위치가 바뀔 것이므로 형제를 다시 설정해줘야 한다.
                        sibling = successor->parent->right;
                    }
                    // Case 1.4. 오른쪽 조카가 빨간색인 경우
                    sibling->color = successor->parent->color;  // 부모의 색이 형제에게로
                    successor->parent->color    = BLACK;    // 부모를 검정색으로
                    sibling->right->color       = BLACK;    // 조카를 검정색으로
                    RBT_rotateLeft(tree, successor->parent);// 부모를 기준으로 좌회전
                    successor = (*tree);  // 2중 검정색노드 중 검정색 하나를 루트노드로 옮기는 표현
                }
            }
        }
        // Case 2. 2중 검정색노드가 오른쪽 자식노드인 경우
        else {
            sibling = successor->parent->left;              // 형제는 왼쪽 자식
            // Case 2.1. 형제노드가 빨간색인 경우
            if (sibling->color == RED) {
                sibling->color              = BLACK;        // 형제를 검은색으로
                successor->parent->color    = RED;          // 부모를 빨간색으로
                RBT_rotateRight(tree, successor->parent);   // 부모를 기준으로 우회전
                // 회전함으로써 이제 형제노드가 검정색인 경우로 문제가 변경된다.
            }
            else {
                // Case 2.2. 형제노드가 검정색 + 양쪽 조카가 모두 검정색인 경우
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;           // 형제를 빨간색으로
                    successor = successor->parent;  // 2중 검정색노드 중 검정색 하나를 부모에게 주는 표현
                }
                else {
                    // Case 2.3. 오른쪽 조카가 빨간색인 경우
                    if (sibling->right->color == RED) {
                        sibling->color          = RED;      // 형제를 빨간색으로
                        sibling->right->color   = BLACK;    // 조카를 검정색으로
                        RBT_rotateLeft(tree, sibling);      // 형제를 기준으로 좌회전
                        // 회전함으로써 형제 위치가 바뀔 것이므로 형제를 다시 설정해줘야 한다.
                        sibling = successor->parent->right;
                    }
                    // Case 2.4. 왼쪽 조카가 빨간색인 경우
                    sibling->color = successor->parent->color;  // 부모의 색이 형제로
                    successor->parent->color        = BLACK;    // 부모를 검정색으로
                    sibling->right->color           = BLACK;    // 조카를 검정색으로
                    RBT_rotateRight(tree, successor->parent);   // 부모를 기준으로 우회전
                    successor = (*tree);  // 2중 검정색노드 중 검정색 하나를 루트노드로
                }
            }
        }
    }
    successor->color = BLACK;
}
// <노드번호><색상>[<왼쪽자식, 오른쪽자식 유무>, <부모노드 번호>] 형식으로 출력
void RBT_printTree(Node* node, int depth, int blackCount) {
    if (node == NULL || node == Nil) return;
    if (node->color == BLACK) blackCount++;
    
    char ch = 'X';
    int var = -1;
    char cnt[30];

    if (node->parent != NULL) {
        var = node->parent->data;
        ch = (node->parent->left == node) ? 'L' : 'R';
    }
    if (node->left == Nil && node->right == Nil)
        sprintf(cnt, "-------- %d", blackCount);
    else
        strncpy(cnt, "", sizeof(cnt));
    
    for (int i = 0; i < depth; ++i) printf("    "); // 4-white space
    printf("%d %s [%c, %d] %s\n", node->data,
        (node->color == RED) ? "RED" : "BLACK", ch, var, cnt);
    
    RBT_printTree(node->left, depth + 1, blackCount);
    RBT_printTree(node->right, depth + 1, blackCount);
}
