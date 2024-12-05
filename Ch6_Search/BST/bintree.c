#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

Node* BT_makeNode(void) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void BT_deleteNode(Node* node) {
	free(node);
}

void BT_deleteTree(Node* root) {
	if (root == NULL) return;
	if (root->left) BT_deleteTree(root->left);
	if (root->right) BT_deleteTree(root->right);
	free(root);
	root = NULL;
}

ElementType BT_getData(Node* node){
	return node->data;
}

void BT_setData(Node* node, ElementType newData){
	node->data = newData;
}

Node* BT_getLeftSubtree(Node* node){
	return node->left;
}

Node* BT_getRightSubtree(Node* node){
	return node->right;
}

void BT_setLeftSubtree(Node* parent, Node* child){
	// If parent already has a sub left tree, remove it.
	if (parent->left != NULL) {
		printf("[Error/ BT_setLeftSubTree()]\n");
		printf("\tThere is a sub left tree already\n");
		printf("\tParent(%d), Left child(%d)\n", parent->data, parent->left->data);
		printf("\tNew Left child(%d)\n\n", child->data);
		BT_deleteTree(parent->left);
	}
	parent->left = child;
}

void BT_setRightSubtree(Node* parent, Node* child){
	// If parent already has a sub right tree, remove it.
	if (parent->right != NULL){
		printf("[Error/ BT_setRightSubTree()]\n");
		printf("\tThere is a sub right tree already\n");
		printf("\tParent(%d), Right child(%d)\n", parent->data, parent->right->data);
		printf("\tNew right child(%d)\n\n", child->data);
		BT_deleteTree(parent->right);
	}
	parent->right = child;
}

void BT_changeLeftSubtree(Node* parent, Node* child) {
	parent->left = child;
}

void BT_changeRightSubtree(Node* parent, Node* child){
	parent->right = child;
}

/* 삭제 또는 제거라고 하면 반드시 메모리 해제까지 담당해야 하는 것으로 오해하는 경우가 많다.
삭제와 메모리 해제는 별개의 것이다. 포함할 때도 있지만, 반드시 필요한 것은 아니다.
때에 따라서는 오히려 메모리 해제를 해서는 안 되는 경우도 존재한다.
솔직히 말해서 삭제과정에서 메모리의 해제를 포함하지 않는 경우가 더 일반적이다.
아래 함수들도 주소를 반환해서 호출자 쪽에서 메모리 해제에 대한 책임을 넘기고 있다.
*/
Node* BT_removeLeftSubtree(Node* target){
	Node* delNode = target->left;
	if (delNode == NULL) return NULL;
	delNode->left = NULL;
	return delNode;
}

Node* BT_removeRightSubtree(Node* target){
	Node* delNode = target->right;
	if (delNode == NULL) return NULL;
	delNode->right = NULL;
	return delNode;
}


void BT_traversePreorder(Node* node, TraverseAction act) {
	if (node == NULL) return;
	act(node->data);
	BT_traversePreorder(node->left, act);
	BT_traversePreorder(node->right, act);
}

void BT_traverseInorder(Node* node, TraverseAction act){
	if (node == NULL) return;
	BT_traverseInorder(node->left, act);
	act(node->data);
	BT_traverseInorder(node->right, act);
}

void BT_traversePostorder(Node* node, TraverseAction act){
	if (node == NULL) return;
	BT_traversePostorder(node->left, act);
	BT_traversePostorder(node->right, act);
	act(node->data);
}
