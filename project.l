%{

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "project.tab.h"
void censorId(char*);
int yynumber = 0;
%}

%%

[ \t\n]+								{ ; }
[+|-]?[0-9]+							{ printf("<INTEGER>\t\t%s\n", yytext); } 
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

bool isValid(char c) {
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return true;
	else
		return false;
}

void censorId(char* text) {
	int length = strlen(text);
	if(!isValid(text[0]))	yyerror();	
	else {
//		if(strlen(text) == 
	}
}
// 소수에도 위와같은 조건검사가 필요한지 짚어보기.



