%{
   int yylex(void);
   int t=-1; 
   double symVal[100]; // 심볼들의 값
   extern char symbolTable[100][17]; // 심볼테이블
   #define TRUE 1
   #define FALSE 0

%}

 // "LEX와YACC"책의 도움을 받음(112~). 
%union {
   double dval;
   int vblno;
}

//아래에 있을 수록 우선순위가 높아진다.
%right '=' 
%left L LE S SE EE NE
%left '+' '-'   
%left '*' '/'
%nonassoc UMINUS


%token <vblno> VARIABLE
%token <dval> NUMBER
%type <dval> expr
%token WHILE IF
%nonassoc ELSE END


%%


program:
    program statement ';'
    |
    ;
 
statement:
    expr                { printf("%.2f\n?- ", $1); }
    ;

expr:
    NUMBER{;}
    | VARIABLE { 
			      if($1>t)
                  {
		               printf("%s는 정의되지 않음\n", symbolTable[$1]);
                       exit(1);
                  }
                  $$ = symVal[$1];}
   | VARIABLE '=' expr     {
								symVal[$1] = $3;
								$$ = symVal[$1];
								if( $1 > t)	t = $1;
							}
    | '-' expr %prec UMINUS          { $$ =  -$2; }
    | expr '+' expr					 { $$ = $1 + $3;  }
    | expr '-' expr					 { $$ = $1 - $3; }
    | expr '*' expr					 { $$ = $1 * $3; }
    | expr '/' expr       { 
							if($3 == 0)
							 yyerror("0으로 나눌수 없습니다.");
							 else
							  $$ = $1 / $3;
						  }
    | '(' expr ')'        { $$ = $2; }
	| expr L expr			{if ($1>$3) $$ = TRUE;
								else $$ = FALSE;}
	| expr LE expr			{if ($1>=$3) $$ = TRUE;
								else $$ = FALSE;}
	| expr S expr			{if ($1<$3) $$ = TRUE;
								else $$ = FALSE;}
	| expr SE expr			{if ($1<=$3) $$ = TRUE;
								else $$ = FALSE;}
	| expr EE expr			{if ($1==$3) $$ = TRUE;
								else $$ = FALSE;}
	| expr NE expr			{if ($1!=$3) $$ = TRUE;
								else $$ = FALSE;}
    ;


%%


int main(void)
{
   printf("?- ");
   yyparse();
   return 0;
}