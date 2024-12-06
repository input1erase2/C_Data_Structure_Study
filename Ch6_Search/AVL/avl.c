#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

// LL회전 함수 (노드를 기준으로 오른쪽 회전)
Node* rotateLL(Node* node) {
    Node* parent = node;
    Node* child = BT_getLeftSubtree(node);
    BT_changeLeftSubtree(parent, BT_getRightSubtree(child));
    BT_changeRightSubtree(child, parent);
    return child;
}

// RR회전 함수 (노드를 기준으로 왼쪽 회전)
Node* rotateRR(Node* node) {
    Node* parent = node;
    Node* child = BT_getRightSubtree(node);
    BT_changeRightSubtree(parent, BT_getLeftSubtree(child));
    BT_changeLeftSubtree(child, parent);
    return child;
}

// LR회전 함수 (부분 RR회전 후 전체 LL 회전)
Node* rotateLR(Node* node) {
    Node* parent = node;
    Node* child = BT_getLeftSubtree(node);
    BT_changeLeftSubtree(parent, rotateRR(child));
    return rotateLL(parent);
}

// RL회전 함수 (부분 LL회전 후 전체 RR 회전)
Node* rotateRL(Node* node) {
    Node* parent = node;
    Node* child = BT_getRightSubtree(node);
    BT_changeRightSubtree(parent, rotateLL(child));
    return rotateRR(parent);
}

// 해당 노드의 높이를 반환하는 함수
int getHeight(Node* node) {
    if (node == NULL) return 0;
    int hL = getHeight(BT_getLeftSubtree(node));
    int hR = getHeight(BT_getRightSubtree(node));
    return (hL > hR) ? hL + 1 : hR + 1;
}

// 해당 노드의 양쪽 서브트리의 높이 차를 반환하는 함수
int getHeightDiff(Node* node) {
    if (node == NULL) return 0;
    int hL = getHeight(BT_getLeftSubtree(node));
    int hR = getHeight(BT_getRightSubtree(node));
    return hL - hR;
}


Node* BT_rebalance(Node** root) {
    int hDiff = getHeightDiff(*root);     // 균형인수 계산
    if (hDiff > 1) {            // +2 이상이면 LL 또는 LR
                // 왼쪽 자식의 균형인수가 1 이상인 경우 LL
        if (getHeight(BT_getLeftSubtree(*root)) > 0)
            (*root) = rotateLL(*root);
        else    // 0 이하인 경우 LR
            (*root) = rotateLR(*root);
    }
    else if (hDiff < -1) {      // -2 이하면 RR 또는 RL
                // 오른쪽 자식의 균형인수가 1 이상인 경우 RR
        if (getHeight(BT_getRightSubtree(*root)) > 0)
            (*root) = rotateRR(*root);
        else    // 0 이하인 경우 RL
            (*root) = rotateRL(*root);
    }
    return (*root);
}
