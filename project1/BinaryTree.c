#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

Node* MakeNode() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

BTData GetData(Node* tree) {
	return tree->data;
}

void SetData(Node* tree, BTData data) {
	tree->data = data;
}

Node* GetLeftSubTree(Node* tree) {
	return tree->left;
}

Node* GetRightSubTree(Node* tree) {
	return tree->right;
}

void MakeLeftSubTree(Node* parent, Node* child) {
//	if(parent->left != NULL)
//		free(parent->left);

	parent->left = child;
}

void MakeRightSubTree(Node* parent, Node* child) {
//	if(parent->right != NULL)
//		free(parent->right);

	parent->right = child;
}

void Traverse(Node* tree, VisitFuncPtr action, VisitFuncPtr action2) {
	if(tree == NULL) return;

	action(tree->data);
	Traverse(tree->left, action, action2);
	Traverse(tree->right, action, action2);
	action2(tree->data);
}
