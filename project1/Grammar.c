#include <stdio.h>
#include <string.h>
#include "Grammar.h"
#include "BinaryTree.h"

char* lookahead = NULL;
int lookahead_ptr = 0;

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
		if(!strcmp(lookahead, "id"))
			match(lookahead);
	}
}
