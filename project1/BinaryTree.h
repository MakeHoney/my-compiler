#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef char* BTData;

typedef struct _bTreeNode {
	BTData data;
	struct _bTreeNode* left;
	struct _bTreeNode* right;
} Node;

typedef void VisitFuncPtr(BTData data);

Node* MakeNode();
BTData GetData(Node* tree);
void SetData(Node* tree, BTData data);

Node* GetLeftSubTree(Node* tree);
Node* GetRightSubTree(Node* tree);

void MakeLeftSubTree(Node* parent, Node* child);
void MakeRightSubTree(Node* parent, Node* child);
void PreorderTraverse(Node* tree);

#endif
