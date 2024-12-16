#ifndef __BINTREE_H_
#define __BINTREE_H_


typedef int ElementType;

typedef struct _Node {
	ElementType data;
	struct _Node* left;
	struct _Node* right;
} Node;


Node* 			BT_makeNode(void);

void			BT_deleteNode(Node* node);
void			BT_deleteTree(Node* root);

ElementType		BT_getData(Node* node);
void			BT_setData(Node* node, ElementType newData);

Node* 			BT_getLeftSubtree(Node* node);
Node* 			BT_getRightSubtree(Node* node);
void 			BT_setLeftSubtree(Node* parent, Node* child);
void 			BT_setRightSubtree(Node* parent, Node* child);
void			BT_changeLeftSubtree(Node* parent, Node* child);
void			BT_changeRightSubtree(Node* parent, Node* child);
Node*			BT_removeLeftSubtree(Node* node);
Node*			BT_removeRightSubtree(Node* node);

typedef void TraverseAction(ElementType data);

void 			BT_traversePreorder(Node* node, TraverseAction act);
void 			BT_traverseInorder(Node* node, TraverseAction act);
void 			BT_traversePostorder(Node* node, TraverseAction act);

#endif