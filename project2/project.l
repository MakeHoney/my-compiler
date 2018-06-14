%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hello.tab.h"

char symbolTable[100][17];
int top=0;
int yyerror(char* c);

%}

identifier		(_|[a-z]|[A-Z])[a-zA-Z0-9_]*
number			(([1-9][0-9]*)|0)(\.[0-9]*)?
under_bar		[_]*
if				[i][f]
else			[e][l][s][e]
while			[w][h][i][l][e]
end				[e][n][d]
l				[>]
le				[>][=]
s				[<]
se				[<][=]
ee				[=][=]
ne				[!][=]


%%


{identifier} {
             for(int i=0; i<top; i++)
             {
               if(strcmp(yytext, symbolTable[i])==0)
               {
                  yylval.vblno = i;
                  return VARIABLE;
               }
             }

             strcpy(symbolTable[top++], yytext);
             yylval.vblno = top-1;
             return VARIABLE;
          }

{number}   {
      yylval.dval =atof(yytext);
      return NUMBER;
      }
{under_bar}	{yyerror("lexical error\n");}

{end}		{return END;}
{while}		{return WHILE;}
{if}		{return IF;}
{else}		{return ELSE;}
{l}			{return L;}
{le}		{return LE;}
{s}			{return S;}
{se}		{return SE;}
{ee}		{return EE;}
{ne}		{return NE;}


 
[-+()=/*;] {return *yytext;}

[ \n\t]   ;     
.       yyerror("lexical error");

%%

int yywrap(void)
{
   return 0;
}

int yyerror(char* c)
{
    printf("%s\n", c);
    exit(1);
}