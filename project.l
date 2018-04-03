%{
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "project.tab.h"
int yyerror(void);
void censorId(char*);
void censorInt(char*);
void censorSpec(char*);
void censorOper(char*);
int yynumber = 0;
%}

%%

[ \t\n]+								{ ; }

[+|-]?[0-9]+							{	
											censorInt(yytext);
											printf("<INTEGER>\t\t%s\n", yytext); 
										}

[+|-]?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { printf("<FLOAT>\t\t%s\n", yytext); }

[+\-*/=]|(and)|(or)|(eq)|(gt)			{ censorOper(yytext); }

[a-zA-z_][a-zA-Z0-9_]*					{
											censorId(yytext);
											printf("<ID, %d>\t\t%s\n", yynumber, yytext);          
							            }


[",();]									{ censorSpec(yytext); }

.                     					{ yyerror(); }

%%

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

void censorId(char* text) {
	/* 길이가 16 이상일 때는 우선적으로 길이 16으로 맞춰준다. */
	if(strlen(text) > 16) text[16] = '\0';

	/* 길이를 재정의 */
	int length = strlen(text);
	int _cnt = 0;

	/* _로만 이루어진 identifier를 거른다 */

	for(int i = 0 ; i < length ; i++)
		if(text[i] == '_') _cnt++;
	if(length == _cnt) yyerror();
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
	int length = strlen(text);
	if(length == 1) {
		if(text[0] == '=') 		printf("<ASSIGN>\t\t%s\n", text);
		else if(text[0] == '+')	printf("<PLUS>\t\t%s\n", text);
		else if(text[0] == '-') printf("<MINUS>\t\t%s\n", text);
		else if(text[0] == '*')	printf("<MUSTI>\t\t%s\n", text);
		else					printf("<DIVIS>\t\t%s\n", text);
	} else {
		if(!(strcmp(text, "and")))		printf("<AND>\t\t%s\n", text);
		else if(!(strcmp(text, "or")))	printf("<OR>\t\t%s\n", text);
		else if(!(strcmp(text, "eq")))	printf("<EQ>\t\t%s\n", text);
		else							printf("<GT>\t\t%s\n", text);
	}
}
