#include <stdio.h>
#include <stdlib.h>
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
    if (center->parent == NULL) (*tree) = center;
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
    if (center->parent == NULL) (*tree) = center;
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

    newNode->color = RED;
    newNode->left = Nil;
    newNode->right = Nil;

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
                RBT_insertHelper(&((*tree)->left), newNode);
        }
        else if ((*tree)->data < newNode->data) {
            if ((*tree)->right == Nil) {
                (*tree)->right = newNode;
                newNode->parent = (*tree);
            }
            else
                RBT_insertHelper(&((*tree)->right), newNode);
        }
    }
}
// 새로운 노드 삽입 후 Red-black 트리 규칙에 따라 리밸런싱 하는 함수
void RBT_rebuildAfterInsert(Node** tree, Node* newNode) {
    while ()
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
void RBT_rebuildAfterRemove(Node** tree, Node* cur) {

}
// <노드번호><색상>[<왼쪽자식, 오른쪽자식 유무>, <부모노드 번호>] 형식으로 출력
void RBT_printTree(Node* tree, int depth, int blackCount) {

}
