#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

Node* MakeNode() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->operat = 0;
	node->operand = 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Data GetOperator(Node* tree) {
	return tree->operat;
}

void SetOperator(Node* tree, Data operator) {
	tree->operat = operator;
}

Data2 GetOperand(Node* tree) {
	return tree->operand;
}

void SetOperand(Node* tree, Data2 operand) {
	tree->operand = operand;
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

double Traverse(Node* tree) {
	double leftVal;
	double rightVal;

	if(GetLeftSubTree(tree) == NULL) return GetOperand(tree);
	else leftVal = Traverse(GetLeftSubTree(tree));

	if(GetRightSubTree(tree) == NULL) return GetOperand(tree); // 필요?
	else rightVal = Traverse(GetRightSubTree(tree));

	if(GetOperator(tree) == '+') return leftVal + rightVal;
	else if(GetOperator(tree) == '-') return leftVal - rightVal;
	else if(GetOperator(tree) == '*') return leftVal * rightVal;
	else return leftVal / rightVal;
	/*나누기 예외처리*/
}
