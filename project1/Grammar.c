#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Grammar.h"
#include "BinaryTree.h"

char* lookahead = NULL;
int lookahead_ptr = 0;
int cnt = 1;

Node* rootNode = NULL;
Node* temp = NULL;
Node* nodeOperator = NULL;
Node* nodeOperand = NULL;

void ShowData(char* data) {
//	if(!strcmp(data, "id"))
		printf("%s\n", data);
		//printf("<%s>%s</%s>", data, id_table[cnt++], data);
//	else
//		printf("<%s>", data);
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
	puts("Traversal start!");
	PreorderTraverse(rootNode, ShowData);
//	PostorderTraverse(rootNode, ShowData2);
	free(nodeOperator);
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
		if(rootNode->data != NULL) temp = rootNode;
		rootNode = MakeNode();
		rootNode->data = lookahead;
		if(temp != NULL) MakeLeftSubTree(rootNode, temp);
		else MakeLeftSubTree(rootNode, nodeOperand);
		//free(temp)?
		nodeOperator = rootNode;
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
		nodeOperator = MakeNode();
		nodeOperator->data = lookahead;
		if(rootNode->data != NULL)
			MakeRightSubTree(rootNode, nodeOperator);
		MakeLeftSubTree(nodeOperator, nodeOperand);

		F();
		TP();
	} else
		return;
}

void F() {
	fputs("F()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	char* nextOperator = token_table[lookahead_ptr + 1];
	/* printf("nextoper : %p\n", token_table[lookahead_ptr + 50]; */
	if(!strcmp(lookahead, "(")) {
		match(lookahead);
		E();
		//lookahead = token_table[lookahead_ptr]; 필요?
		match(lookahead);
	} else {
		if(!strcmp(lookahead, "id")) {
			match(lookahead);
			nodeOperand = MakeNode(); // XML 함수에서 makenode가 필요한지 보기
			nodeOperand->data = lookahead;
			if(nodeOperator->data != NULL) {
				/* nextOperator 없는 경우 예외처리 필요함 (EOF를 토큰배열에 추가) */
				if(priority(nextOperator) <= priority(nodeOperator->data)) {
					MakeRightSubTree(nodeOperator, nodeOperand);
					nodeOperand = nodeOperator;
				}
			}
		}
	}
}
