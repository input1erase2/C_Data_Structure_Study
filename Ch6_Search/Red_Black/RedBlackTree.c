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
// Red-black 트리에서 타겟노드를 찾아 제거하는 함수
Node* RBT_remove(Node** tree, ElementType targetData) {
    Node* delNode = NULL;
    Node* successor = NULL;
    Node* target = RBT_search((*tree), targetData);

    if (target == NULL) return NULL;    // 대상이 트리에 없음

    if (target->left == Nil || target->right == Nil) {

    }
}
// 새로운 노드 삽입 후 Red-black 트리 규칙에 따라 리밸런싱 하는 함수
void RBT_rebuildAfterInsert(Node** tree, Node* newNode) {

}
// 타겟 노드 제거 후 Red-black 트리 규칙에 따라 리밸런싱 하는 함수
void RBT_rebuildAfterRemove(Node** tree, Node* cur) {

}
// 리밸런싱 도구 - center 노드를 중심으로 우회전 하는 함수 (LL상태 회전)
void RBT_rotateRight(Node** tree, Node* center) {

}
// 리밸런싱 도구 - center 노드를 중심으로 좌회전 하는 함수 (RR상태 회전)
void RBT_rotateLeft(Node** tree, Node* center) {

}
// <노드번호><색상>[<왼쪽자식, 오른쪽자식 유무>, <부모노드 번호>] 형식으로 출력
void RBT_printTree(Node* tree, int depth, int blackCount) {

}
