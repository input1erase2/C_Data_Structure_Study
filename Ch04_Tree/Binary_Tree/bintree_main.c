#include <stdio.h>
#include "bintree.h"

void printTree(ElementType data) {
	printf("%d  ", data);
}
int main() {
	Node* bt1 = BT_makeNode();
	Node* bt2 = BT_makeNode();
	Node* bt3 = BT_makeNode();
	Node* bt4 = BT_makeNode();
	
	BT_setData(bt1, 1);
	BT_setData(bt2, 2);
	BT_setData(bt3, 3);
	BT_setData(bt4, 4);
	
	BT_setLeftSubtree(bt1, bt2);
	BT_setRightSubtree(bt1, bt3);
	BT_setLeftSubtree(bt2, bt4);
	
	// Print bt1's left child node
	printf("BT1's left child node = %d\n", BT_getData(BT_getLeftSubtree(bt1)));
	
	// Print bt1's left child's left child node
	printf("BT1's left-left child node = %d\n",
		BT_getData(BT_getLeftSubtree(BT_getLeftSubtree(bt1))));
	
	Node* bt5 = BT_makeNode();
	Node* bt6 = BT_makeNode();
	Node* bt7 = BT_makeNode();
	
	BT_setData(bt5, 10);
	BT_setData(bt6, 20);
	BT_setData(bt7, 30);
	
	BT_setLeftSubtree(bt5, bt6);
	BT_setRightSubtree(bt5, bt7);
	
	BT_setRightSubtree(bt1, bt5);	// Collision occured!
	
	BT_traverseInorder(bt1, printTree);
	
	BT_deleteTree(bt1);
	
	return 0;
}

/*
BT1's left child node = 2
BT1's left-left child node = 4
[Error/ BT_setRightSubTree()]
        There is a sub right tree already
        Parent(1), Right child(3)
        New right child(10)

4  2  1  20  10  30
 */