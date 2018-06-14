#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef char Data;
typedef double Data2;

typedef struct _bTreeNode {
	Data operat;
	Data2 operand;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} Node;

/* 수정필요 */
// typedef void VisitFuncPtr(Data operat, Data2 operand);

Node* MakeNode();
Data GetOperator(Node* tree);
void SetOperator(Node* tree, Data operator);

Data2 GetOperand(Node* tree);
void SetOperand(Node* tree, Data2 operand);

Node* GetLeftSubTree(Node* tree);
Node* GetRightSubTree(Node* tree);

void MakeLeftSubTree(Node* parent, Node* child);
void MakeRightSubTree(Node* parent, Node* child);
double Traverse(Node* tree);

#endif
