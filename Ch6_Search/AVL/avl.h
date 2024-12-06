#ifndef __AVL_TREE_H_
#define __AVL_TREE_H_

#include "bintree.h"

// 균형인수 2 이상으로 균형이 어긋난 트리의 균형을 바로잡는 함수
Node* BT_rebalance(Node** root);

#endif