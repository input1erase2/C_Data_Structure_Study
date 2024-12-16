#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include "bintree.h"

// BST의 생성 및 초기화 함수 (root 노드 주소 변경 여지 있으므로 2중 포인터 사용)
void        BST_init(Node** root);
// BST의 노드에 저장된 데이터를 반환하는 함수
ElementType BST_getData(Node* node);
// BST 삽입함수, 노드 생성 포함 (root 노드 주소 변경 여지 있으므로 2중 포인터 사용)
// void        BST_insert(Node** root, ElementType newData);
// AVL 트리를 위한 BST 삽입함수, 재귀적으로 자리를 찾아가며 리밸런싱한다.
Node*       BST_insert(Node** root, ElementType newData);
// BST에서 target값을 찾아 해당 노드 주소값 반환
Node*       BST_search(Node* root, ElementType target);
// BST 제거함수, target 값을 찾아 해당 노드 주소값 반환
Node*       BST_remove(Node** root, ElementType target);
// BST에 저장된 모든 노드를 중위순회로 출력하는 함수
void        BST_show(Node* root);

#endif