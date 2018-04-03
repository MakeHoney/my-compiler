%{
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "project.tab.h"
#define MAX_DBNUM	1000
#define STR_LENG	20
int yyerror(void);
void censorId(char*);
void censorInt(char*);
void censorSpec(char*);
void censorOper(char*);
void toUpper(char*);

char id_table[MAX_DBNUM][STR_LENG];
char str_table[MAX_DBNUM][STR_LENG];
int id_ptr = 0;
int str_ptr = 0;
%}

%%

[ \t\n]+								{ ; }
(\/\/.*)								{ ; }
(\/\*.*\*\/)							{ ; }

[+|-]?[0-9]+							{	
											censorInt(yytext);
											printf("<INTEGER>\t\t%s\n", yytext); 
										}

[+|-]?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { printf("<FLOAT>\t\t%s\n", yytext); }


[+\-*/=]|(and)|(or)|(eq)|(gt)			{ censorOper(yytext); }

\".*\"									{ printf("<STRING>\t\t%s\n", yytext); }


[a-zA-z_][a-zA-Z0-9_]*					{ censorId(yytext); }


[",();]									{ censorSpec(yytext); }

.                     					{ yyerror(); }

%%

// 문자열, 주석 개행 처리하기
int main(void)
{
	yyparse();
    return 0;
}

int yywrap(void)
{
	   return 0;
}

int yyerror(void)
{
	    printf("Error\n");
		    exit(1);
}

void toUpper(char* text) {
	for(int i = 0 ; i < strlen(text) ; i++)
		if(text[i] >= 'a' && text[i] <= 'z')
			text[i] -= 32;
}

void censorId(char* text) { 
	char* keyword[] = {"and", "begin", "def", "end", 
					"else", "eq", "gt", "if", "or", 
					"print", "return", "while", "identifier"};
	bool isKeyword = false;
	int idx = 0;

	/* 길이가 16 이상일 때는 우선적으로 길이 16으로 맞춰준다. */
	if(strlen(text) > 16) text[16] = '\0';

	/* 길이를 재정의 */
	int length = strlen(text);
	int idAppear = false;
	int _cnt = 0;

	/* _로만 이루어진 identifier를 거른다 */
	for(int i = 0 ; i < length ; i++)
		if(text[i] == '_') _cnt++;
	if(length == _cnt) yyerror();

	/* 키워드 검사 */
	for(int i = 0 ; i < 13 ; i++) {
		if(!strcmp(text, keyword[i])){
			isKeyword = true;
			break;
		}
	}

	/* 키워드와 같으면 출력하고 즉시 리턴 */
	if(isKeyword) {
		char tmp[STR_LENG];
		strcpy(tmp, text);
		toUpper(tmp);
		printf("<%s>\t\t%s\n", tmp, text);
		return;
	}

	/* 인덱싱 */
	for(int i = 0 ; i < MAX_DBNUM ; i++) {
		if(!(strcmp(text, id_table[i]))) {
			printf("in\n");
			idAppear = true;
			idx = i;
			break;
		}
	}

	if(!idAppear){
		strcpy(id_table[++id_ptr], text);
		printf("<ID, %d>\t\t%s\n", id_ptr, text);
	} else {
		printf("<ID, %d>\t\t%s\n", idx, text);
	}

}

void censorInt(char* text) {
	/* 길이가 10 이상일 때는 나머지 cut */
	if(strlen(text) > 10) text[10] = '\0';
}

void censorSpec(char* text) {
	/* 개인적인 사용 빈도 수에 따라 상위에 배치 */
	if(text[0] == ';')			printf("<SEMICOLON>\t\t%s\n", text);
	else if(text[0] == '(')		printf("<LPAREN>\t\t%s\n", text);
	else if(text[0] == ')')		printf("<RPAREN>\t\t%s\n", text);
	else if(text[0] == '"')		printf("<DQUOTE>\t\t%s\n", text);
	else 						printf("<COMMA>\t\t%s\n", text);
}

void censorOper(char* text) {
	if(strlen(text) == 1) {
		if(text[0] == '=') 		printf("<ASSIGN>\t\t%s\n", text);
		else if(text[0] == '+')	printf("<PLUS>\t\t%s\n", text);
		else if(text[0] == '-') printf("<MINUS>\t\t%s\n", text);
		else if(text[0] == '*')	printf("<MUSTI>\t\t%s\n", text);
		else					printf("<DIVIS>\t\t%s\n", text);
	} else {
		/* and, or, eq, gt는 keyword인가 operator인가? */
		if(!(strcmp(text, "and")))		printf("<AND>\t\t%s\n", text);
		else if(!(strcmp(text, "or")))	printf("<OR>\t\t%s\n", text);
		else if(!(strcmp(text, "eq")))	printf("<EQ>\t\t%s\n", text);
		else							printf("<GT>\t\t%s\n", text);
	}
}
