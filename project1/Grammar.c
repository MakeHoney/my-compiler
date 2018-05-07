#include <stdio.h>
#include <string.h>
#include "Grammar.h"
#include "BinaryTree.h"


void match(char* str) {
	if(!strcmp(lookahead, str) || !strcmp(lookahead, str))
		lookahead_ptr++;
	else
		printf("error occured");
}

void E() {
	T();
	EP();
}

void EP() {
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
	F();
	TP();
}

void TP() {
	lookahead = token_table[lookahead_ptr];
	if(!strcmp(lookahead, "mult")) {
		match(lookahead);
		F();
		TP();
	} else
		return;
}

void F() {
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
