#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"

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
			perror("[ERROR/ Insert Error, Key is already in the tree\n\n");
			exit(-1);
		}
		parent = child;
		child = (tempData > newData) ? BT_getLeftSubtree(child) : BT_getRightSubtree(child);
	}
	newNode = BT_makeNode();
	BT_setData(newNode, newData);
	// if, this newNode is the first node of the tree
	if (parent == NULL) (*root) = newNode;
	else (newData < BT_getData(parent)) ? BT_setLeftSubtree(parent, newNode) : BT_setRightSubtree(parent, newNode);
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
	
}

void BST_show(Node* root){
	
}
