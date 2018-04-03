%{

#include <stdlib.h>
#include <string.h>
#include "project.tab.h"
int yynumber = 0;
%}

%%
[0-9]+([^0-9 \n\t])+.*					{printf("asd\n"); }
[ \t\n]+								{ ; }
[+|-]?[0-9]+							{ printf("<INTEGER>\t\t%s\n", yytext); } 
[+|-]?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) { printf("<FLOAT>\t\t%s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*					{
		                     				//_만 있으면 무시
											printf("<ID, %d>\t\t%s\n", yynumber, yytext);          
							            }
.                     					{ printf("Error\n");}

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
