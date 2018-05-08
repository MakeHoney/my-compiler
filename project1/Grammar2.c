#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Grammar.h"
#include "BinaryTree.h"

char* lookahead = NULL;
int lookahead_ptr = 0;
int cnt = 1;

Node* rootNode = NULL;
Node* nodeOperator = NULL;
Node* nodeOperand = NULL;

void ShowData(char* data) {
	if(!strcmp(data, "id"))
		printf("<%s>%s</%s>", data, id_table[cnt++], data);
	else
		printf("<%s>", data);
}

void ShowData2(char* data) {
	if(strcmp(data, "id"))
		printf("</%s>", data);
}

void XML() {
	rootNode = MakeNode();
	nodeOperator = MakeNode();
	nodeOperand = MakeNode();
	E();
	free(nodeOperator);
	puts("Traversal start!");
	PreorderTraverse(nodeOperand, ShowData);
	PostorderTraverse(nodeOperand, ShowData2);
	free(nodeOperand);
}

void match(char* str) {
	if(!strcmp(lookahead, str) || !strcmp(lookahead, str))
		lookahead_ptr++;
	else {
		printf("error occured");
		exit(0);
	}
}

int priority(char* tok) {
	if(!strcmp(tok, "plus") || !strcmp(tok, "minus")) return 0;
	else if (!strcmp(tok, "mult") || !strcmp(tok, "div")) return 1;
	else return 2;
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
	if(!strcmp(lookahead, "mult") || !strcmp(lookahead, "div")) {
		match(lookahead);
		nodeOperator->data = lookahead;
		MakeLeftSubTree(nodeOperator, nodeOperand);
//		MakeLeftSubTree(nodeOperator, rootNode);
//		rootNode = nodeOperator;
		nodeOperand = MakeNode();
		F();
		TP();
	} else
		return;
}

void F() {
	fputs("F()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	nextOperator = token_table[lookahead_ptr + 1];
	/* printf("nextoper : %p\n", token_table[lookahead_ptr + 50]; */
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
				/* nextOperator 없는 경우 예외처리 필요함 */
				if(priority(nextOperator) > priority(nodeOperator->data)) {
					rootNode = nodeOperator;
//					MakeRightSubTree(rootNode, nodeOperator);
					rootNode->right = MakeNode();
					nodeOperator = rootNode->right;
//					temp->data = nextOperator; 연산자 값 대입은 TP에서
//					MakeRightSubTree(nodeOperator, temp);
				}
				else {
					
				/* 우선순위가 낮거나 같을 때  */
					MakeRightSubTree(nodeOperator, nodeOperand);
					if(rootNode == )
						rootNode = nodeOperator;
					nodeOperator = MakeNode();
					/* nodeOperand = nodeOperator; */
//					nodeOperator = MakeNode();
					
				}
			}
		}
	}
}
