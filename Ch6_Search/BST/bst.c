#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

void BST_init(Node** root) {
	(*root) = NULL;
}

ElementType BST_getData(Node* node){
	return BT_getData(node);
}

void BST_insert(Node** root, ElementType newData){
	Node* parent = NULL;
	Node* child = (*root);
	Node* newNode = NULL;
	
	ElementType tempData;
	while (child) {
		tempData = BT_getData(child);
		if (newData == tempData) {
			perror("[ERROR/ BST Insert] Key is already in the tree\n\n");
			exit(-1);
		}
		parent = child;
		child = (tempData > newData) ? BT_getLeftSubtree(child) : BT_getRightSubtree(child);
	}
	newNode = BT_makeNode();
	BT_setData(newNode, newData);
	
	if (parent == NULL)		// if this newNode is the first node of the tree
		(*root) = newNode;
	else {
		if (newData < BT_getData(parent))
			BT_setLeftSubtree(parent, newNode);
		else
			BT_setRightSubtree(parent, newNode);
	}
}

Node* BST_search(Node* root, ElementType target){
	Node* cur = root;
	ElementType tempData;
	while (cur) {
		tempData = BT_getData(cur);
		if (target == tempData) return cur;
		cur = (target < tempData) ? BT_getLeftSubtree(cur) : BT_getRightSubtree(cur);
	}
}

Node* BST_remove(Node** root, ElementType target){
	Node* vRoot 		= BT_makeNode();	// Virtual Node for convenient
	Node* parent 		= vRoot;			// always points parent node
	Node* child 		= (*root);			// always points current node
	Node* delNode 		= NULL;				// target node
	Node* delNodeChild	= NULL;				// target node's selected child node

	// [Important] Make root node to virtual node's right child node.
	// This process makes every remove trial equivalent whether target is root or not.
	BT_changeRightSubtree(vRoot, (*root));

	while (child && BT_getData(child) != target) {
		parent = child;
		child = (BT_getData(child) > target) ?
			BT_getLeftSubtree(child) : BT_getRightSubtree(child);
	}
	if (child == NULL) {
		perror("[ERROR/ BST remove] There are no target in the tree\n\n");
		exit(-1);
	}
	delNode = child;
	// Case 1. Target node is leaf node
	if (BT_getLeftSubtree(delNode) == NULL && BT_getRightSubtree(delNode) == NULL) {
		if (BT_getLeftSubtree(parent) == delNode)
			BT_removeLeftSubtree(parent);
		else
			BT_removeRightSubtree(parent);
	}
	// Case 2. Target node has one child node
	else if (BT_getLeftSubtree(delNode) == NULL || BT_getRightSubtree(delNode) == NULL) {
		delNodeChild = (BT_getLeftSubtree(delNode)) ? 
			BT_getLeftSubtree(delNode) : BT_getRightSubtree(delNode);
		if (BT_getLeftSubtree(parent) == delNode)
			BT_changeLeftSubtree(parent, delNodeChild);
		else
			BT_changeRightSubtree(parent, delNodeChild);
	}
	// case 3. Target node has two childs
	else {
		// Find the smallest element in the right subtree of the delNode
		Node* tempNodeParent = delNode;
		Node* tempNode = BT_getRightSubtree(delNode);
		while (BT_getLeftSubtree(tempNode) != NULL) {
			tempNodeParent = tempNode;
			tempNode = BT_getLeftSubtree(tempNode);
		}
		ElementType temp = BT_getData(delNode);		// Backup
		BT_setData(delNode, BT_getData(tempNode));
		// 'tempNode' should have always right child or not have any child.
		// Because If it has left child, that left child must be a tempNode.
		if (BT_getLeftSubtree(tempNodeParent) == tempNode)
			BT_changeLeftSubtree(tempNodeParent, BT_getRightSubtree(tempNode));
		else
			BT_changeRightSubtree(tempNodeParent, BT_getRightSubtree(tempNode));
		// Change delNode points to tempNode because tempNode is no need anymore.
		delNode = tempNode;
		BT_setData(delNode, temp);	// Unroll backup
	}
	// [Important] If target was root node, vRoot's right node must changed
	if (BT_getRightSubtree(vRoot) != (*root)) 
		(*root) = BT_getRightSubtree(vRoot);

	free(vRoot);
	return delNode;
}

void showData(int data) {
	printf("%d  ", data);
}

void BST_show(Node* root){
	BT_traverseInorder(root, showData);
}
