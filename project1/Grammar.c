#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grammar.h"
#include "BinaryTree.h"

char* lookahead = NULL;
int lookahead_ptr = 0;
int cnt = 1;

Node* rootNode = NULL;
Node* temp = NULL;
Node* nodeOperator = NULL;
Node* nodeOperand = NULL;
bool ep_flag = false;

void initialize() {
	rootNode = NULL;
	temp = NULL;
	nodeOperator = NULL;
	nodeOperand = NULL;
}

void ShowData(char* data) {
	if(!strcmp(data, "id"))
		printf("<%s>%s</%s>\n", data, id_table[cnt++], data);
	else
		printf("<%s>\n", data);
}

void ShowData2(char* data) {
	if(strcmp(data, "id"))
		printf("</%s>\n", data);
}

void XML() {
	rootNode = MakeNode();
	nodeOperator = MakeNode();
	nodeOperand = MakeNode();
	E();
	if(!ep_flag) rootNode = nodeOperator;
	puts("Traversal start!");
	Traverse(rootNode, ShowData, ShowData2);
	free(nodeOperator);
	initialize();
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
	if(!strcmp(tok, "plus") || !strcmp(tok, "minus") || !strcmp(tok, "assign")) return 0;
	else if (!strcmp(tok, "mult") || !strcmp(tok, "div")) return 1;
	else return 2;
}

void E() {
//	fputs("E()\n", stdout);
	T();
	EP();
}

void EP() {
//	fputs("EP()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	if(!strcmp(lookahead, "plus") || !strcmp(lookahead, "minus")) {
		ep_flag = true;
		match(lookahead);
		if(rootNode->data != NULL) temp = rootNode;
		rootNode = MakeNode();
		rootNode->data = lookahead;
		if(temp != NULL) MakeLeftSubTree(rootNode, temp);
		else MakeLeftSubTree(rootNode, nodeOperand);
		nodeOperator = rootNode;
		T();
		EP();
	} else if(!strcmp(lookahead, "assign")) {
		/* assign 두번 이상은 에러 출력 */
		/* lookahead_ptr은 유지된다. */
		/* E`이 return되면 전체가 끝나느 것 */
		match(lookahead);
		Node* tp1; Node* tp2;

		tp1 = rootNode; 
		initialize();

		rootNode = MakeNode();
		nodeOperator = MakeNode();
		nodeOperand = MakeNode();

		E();

		tp2 = rootNode; 
		rootNode = MakeNode();
		rootNode->data = "assign";

		MakeLeftSubTree(rootNode, tp1);
		MakeRightSubTree(rootNode, tp2);

		return;
	} else
		return;
}

void T() {
//	fputs("T()\n", stdout);
	F();
	TP();
}

void TP() {
//	fputs("TP()\n", stdout);
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
//	fputs("F()\n", stdout);
	lookahead = token_table[lookahead_ptr];
	char* nextOperator = token_table[lookahead_ptr + 1];
	if(!strcmp(lookahead, "(")) {
		match(lookahead);
		E();
		//lookahead = token_table[lookahead_ptr]; 필요?
		match(lookahead);
	} else {
		if(!strcmp(lookahead, "id")) {
			match(lookahead);
			nodeOperand = MakeNode();
			nodeOperand->data = lookahead;
			if(nodeOperator->data != NULL) {
				if(priority(nextOperator) <= priority(nodeOperator->data) ||
						!strcmp(nextOperator, "EOF")) {
					MakeRightSubTree(nodeOperator, nodeOperand);
					nodeOperand = nodeOperator;
				}
			}
		}
	}
}
