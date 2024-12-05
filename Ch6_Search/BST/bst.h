#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include "bintree.h"

void BST_init(Node** root);
ElementType BST_getData(Node* node);
void BST_insert(Node** root, ElementType newData);
Node* BST_search(Node* root, ElementType target);
Node* BST_remove(Node** root, ElementType target);
void BST_show(Node* root);

#endif