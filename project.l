%{

#include <stdlib.h>
#include <string.h>
#include "hello.tab.h"
int yynumber = 0;
%}

%%
end										{ printf("<END>\t\t%s\n", yytext); } 
[a-zA-Z_][a-zA-Z0-9_]*					{

		                     				//_만 있으면 무시
											printf("<ID, %d>\t\t%s\n", yynumber, yytext);
							                      
							            }
[-|+]?[0-9]+         					{ printf("<INTEGER>\t\t%s\n", yytext); }
[-|+]?[(0-9)*|e]      

\"										{ printf("QUOTE "); }
\=										{ printf("ASSIGN"); }
\{										{ printf("OBRACE "); }
\}										{ printf("EBRACE "); }
;										{ printf("SEMICOLON "); } 
[ \t\n]+								{ ; }
.                     					{ yyerror();  }

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
}
}
}
	}
}
