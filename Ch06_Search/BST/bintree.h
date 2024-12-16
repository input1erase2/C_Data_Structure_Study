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
// 메모리 소멸을 수반하며 parent의 왼쪽/오른쪽 자식노드를 변경한다
void 			BT_setLeftSubtree(Node* parent, Node* child);
void 			BT_setRightSubtree(Node* parent, Node* child);
// 메모리 소멸을 수반하지 않고 parent의 왼쪽/오른쪽 자식노드를 변경한다
void			BT_changeLeftSubtree(Node* parent, Node* child);
void			BT_changeRightSubtree(Node* parent, Node* child);
// 왼쪽/오른쪽 자식노드를 제거하고, 제거된 노드의 주소값을 반환한다.
Node*			BT_removeLeftSubtree(Node* node);
Node*			BT_removeRightSubtree(Node* node);

typedef void TraverseAction(ElementType data);

void 			BT_traversePreorder(Node* node, TraverseAction act);
void 			BT_traverseInorder(Node* node, TraverseAction act);
void 			BT_traversePostorder(Node* node, TraverseAction act);

#endif