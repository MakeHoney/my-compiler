#include <stdio.h>
#include "BinaryTree.h"

int main(void)
{
	Node * bt1 = MakeNode();
	Node * bt2 = MakeNode();
	Node * bt3 = MakeNode();
	Node * bt4 = MakeNode();

	SetData(bt1, 1);
	SetData(bt2, 2);
	SetData(bt3, 3);
	SetData(bt4, 4);

	MakeLeftSubTree(bt1, bt2);
	MakeRightSubTree(bt1, bt3);
	MakeLeftSubTree(bt2, bt4);

	printf("%d \n",
		GetData(GetLeftSubTree(bt1)));
	printf("%d \n",
		GetData(GetLeftSubTree(GetLeftSubTree(bt1))));

	return 0;
}