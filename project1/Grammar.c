#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Grammar.h"
#include "BinaryTree.h"

char* lookahead = NULL;
int lookahead_ptr = 0;

Node* nodeOperator = NULL;
Node* nodeOperand = NULL;

void ShowData(char* data) {
	printf("%s\n", data);
}

void XML() {
	nodeOperator = MakeNode();
	nodeOperand = MakeNode();
	E();
	free(nodeOperator);
	puts("Traversal start!");
	PreorderTraverse(nodeOperand);
	free(nodeOperand);
}

void match(char* str) {
	if(!strcmp(lookahead, str) || !strcmp(lookahead, str))
		lookahead_ptr++;
	else
		printf("error occured");
}

void E() {
	fputs("E()\n", stdout);
	T();
	EP();
}

void EP() {
	fputs("EP()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	// 예외처리 필요?
	if(!strcmp(lookahead, "plus") || !strcmp(lookahead, "minus")) {
		match(lookahead);
		nodeOperator->data = lookahead;
		MakeLeftSubTree(nodeOperator, nodeOperand);
		nodeOperand = MakeNode();
		T();
		EP();
	} else
		return;
}

void T() {
	fputs("T()\n", stdout);
	F();
	TP();
}

void TP() {
	fputs("TP()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	if(!strcmp(lookahead, "mult")) {
		match(lookahead);
		F();
		TP();
	} else
		return;
}

void F() {
	fputs("F()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	if(!strcmp(lookahead, "(")) {
		match(lookahead);
		E();
		//lookahead = token_table[lookahead_ptr]; 필요?
		match(lookahead);
	} else {
		if(!strcmp(lookahead, "id")) {
			match(lookahead);
			nodeOperand->data = lookahead;
			if(nodeOperator->data != NULL) {
				MakeRightSubTree(nodeOperator, nodeOperand);
				nodeOperand = nodeOperator;
				nodeOperator = MakeNode();
			}
		}
	}
}
