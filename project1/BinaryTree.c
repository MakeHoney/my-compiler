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
	if(parent->left != NULL)
		free(parent->left);

	parent->left = child;
}

void MakeRightSubTree(Node* parent, Node* child) {
	if(parent->right != NULL)
		free(parent->right);

	parent->right = child;
}

void PreorderTraverse(Node* tree, VisitFuncPtr action) {
	if(tree == NULL) return;

	action(tree->data);
	PreorderTraverse(tree->left, action);
	PreorderTraverse(tree->right, action);
}

void PostorderTraverse(Node* tree, VisitFuncPtr action) {
	if(tree == NULL) return;

	PostorderTraverse(tree->left, action);
	PostorderTraverse(tree->right, action);
	action(tree->data);
}

