%{

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "project.tab.h"
bool idValid(char);
void censorId(char*);
void censorInt(char*);
int yynumber = 0;
%}

%%

[ \t\n]+								{ ; }
[+|-]?[0-9]+							{	
											censorInt(yytext);
											printf("<INTEGER>\t\t%s\n", yytext); 
										} 
[+|-]?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { printf("<FLOAT>\t\t%s\n", yytext); }
[a-zA-Z0-9_]+							{
											censorId(yytext);
		                     				//_만 있으면 무시
											printf("<ID, %d>\t\t%s\n", yynumber, yytext);          
							            }
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

bool idValid(char c) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return true;
	else
		return false;
}

void censorId(char* text) {
	/* 길이가 16 이상일 때는 우선적으로 길이 16으로 맞춰준다. */
	if(strlen(text) > 16) text[16] = '\0';

	/* 길이를 재정의 */
	int length = strlen(text);
	int _cnt = 0;

	/* 첫 글자 기준으로 valid여부 검사 */
	if(!idValid(text[0]))	yyerror();	

	/* 위 조건검사 통과시 _로만 이루어진 identifier를 거른다 */
	else {
		for(int i = 0 ; i < length ; i++)
			if(text[i] == '_') _cnt++;
		if(length == _cnt) yyerror();
	}
}
// 소수에도 위와같은 조건검사가 필요한지 짚어보기.
void censorInt(char* text) {
	/* 길이가 10 이상일 때는 나머지 cut */
	if(strlen(text) > 10) text[10] = '\0';
}


