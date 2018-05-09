#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grammar.h"
#include "BinaryTree.h"

char* lookahead = NULL;
int lookahead_ptr = 0;
int id_cnt = 1;
int int_cnt = 1;
int float_cnt = 1;
int parth_ptr = 0;

Node* rootNode = NULL;
Node* temp = NULL;
Node* nodeOperator = NULL;
Node* nodeOperand = NULL;
Node* room[3] = {NULL, NULL, NULL};
//Node* parthRootNode[MAX_PARTH] = {NULL, };
Node* parthRootNode = NULL;

bool ep_flag = false;
bool parth_flag = false;
bool single_flag = false;
bool assign_flag = false;

void initialize() {
	rootNode = NULL;
	temp = NULL;
	nodeOperator = NULL;
	nodeOperand = NULL;
}

void ShowData(char* data) {
	if(!strcmp(data, "id"))
		printf("<%s>%s</%s>\n", data, id_table[id_cnt++], data); 
	else if(!strcmp(data, "int"))
		printf("<%s>%s</%s>\n", data, int_table[int_cnt++], data);
	else if(!strcmp(data, "float")){
//		printf("here\n");
		printf("<%s>%s</%s>\n", data, float_table[float_cnt++], data);
	}
	else
		printf("<%s>\n", data);
}

void ShowData2(char* data) {
	if(strcmp(data, "id") && strcmp(data, "int") && strcmp(data, "float"))
		printf("</%s>\n", data);
}

void XML() {
	rootNode = MakeNode();
	nodeOperator = MakeNode();
	nodeOperand = MakeNode();
	E();
	if(!ep_flag && !single_flag && !assign_flag) {
		rootNode = nodeOperator;
		if(parth_flag && !assign_flag) rootNode = nodeOperand;
	}
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
		if(!parth_flag) ep_flag = true;
		match(lookahead);
		if(rootNode->data != NULL && !parth_flag) temp = rootNode;
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
		char* tmpLookPtr = lookahead;
		match(lookahead);
		Node* tp1; Node* tp2;
		/* 좌변 id 하나인 경우 예외처리 */
		assign_flag = true;
		if(lookahead_ptr == 2) tp1 = nodeOperand;
        else tp1 = rootNode;
		initialize();

		rootNode = MakeNode();
		nodeOperator = MakeNode();
		nodeOperand = MakeNode();

		E();
		
		if(parth_flag) tp2 = nodeOperand;
		else tp2 = rootNode;
	//	printf("tp2 : %s\n", tp2->data);
		rootNode = MakeNode();
		rootNode->data = tmpLookPtr;
//		Traverse(tp1, ShowData, ShowData2);
//		printf("%s\n", token_table[tok_ptr]);
//		printf("%s\n", rootNode->data);
//		Traverse(tp2, ShowData, ShowData2);
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
		if(rootNode->data != NULL && !parth_flag)
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
	if(!strcmp(lookahead, "(")) {
		parth_flag = true;
		match(lookahead);
		room[0] = rootNode; rootNode = MakeNode();
		room[1] = nodeOperator; nodeOperator = MakeNode();
		room[2] = nodeOperand; nodeOperand = MakeNode();
		E();
		parthRootNode = rootNode;
		rootNode = room[0];
		nodeOperator = room[1];
		nodeOperand = room[2];
		char* nextOperator = token_table[lookahead_ptr + 1];
		match(lookahead);
		nodeOperand = parthRootNode;
		if(nodeOperator->data != NULL) {
			if(priority(nextOperator) <= priority(nodeOperator->data) ||
					!strcmp(nextOperator, "EOF") || strcmp(nextOperator, ")")) {
				MakeRightSubTree(nodeOperator, nodeOperand);
				nodeOperand = nodeOperator;
			}
		}
	} else if(!strcmp(lookahead, "id") || !strcmp(lookahead, "int") || !strcmp(lookahead, "float")) {
		char* nextOperator = token_table[lookahead_ptr + 1];
		match(lookahead);
		nodeOperand = MakeNode();
		nodeOperand->data = lookahead;
		if(!strcmp(token_table[lookahead_ptr], "EOF") && lookahead_ptr == 1) {
			single_flag = true;
			rootNode = nodeOperand;
		}
			if(nodeOperator->data != NULL) {
				if(priority(nextOperator) <= priority(nodeOperator->data) ||
					!strcmp(nextOperator, "EOF") || !strcmp(nextOperator, ")")) {
				MakeRightSubTree(nodeOperator, nodeOperand);
				nodeOperand = nodeOperator;
			}
		}
	} else
		return;
}

