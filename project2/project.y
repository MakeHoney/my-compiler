%{
   #include "BinaryTree.h"

   #define TRUE 1
   #define FALSE 0

   extern char symbolTable[100][17]; 

   Node* MakeBunch(char operator, double operand, double operand2);

   double symVal[100];
   int yylex(void);
   int t=-1; 

%}

%union {
   double dval;
   int vblno;
}

%right '=' 
%left L LE S SE EE NE
%left '+' '-'   
%left '*' '/'
%nonassoc UMINUS


%token <vblno> VARIABLE
%token <dval> NUMBER

%token WHILE IF PRINT
%nonassoc ELSE END

%type <dval> expr



%%


program:
    program statement ';' 
    | 
    ;
 
statement:
      expr              { printf("%.2f\n?- ", $1); };
    | PRINT expr        { printf("%.2f\n?- ", $2); };

expr:
      NUMBER{;}
    | VARIABLE  { 
  			           if($1>t)
                    {
      	               printf("%s는 정의되지 않은 변수입니다.\n", symbolTable[$1]);
                     //exit(1);
                    }
                    $$ = symVal[$1];
                }

    | VARIABLE '=' expr     {
								symVal[$1] = $3;
								$$ = symVal[$1];
								if( $1 > t)	t = $1;
							}
    | '-' expr %prec UMINUS          { $$ =  -$2; }
    | expr '+' expr					 {  
                                Node* root = MakeBunch('+', $1, $3);
                                $$ = Traverse(root);  
                             }

    | expr '-' expr					 {  
                                Node* root = MakeBunch('-', $1, $3);
                                $$ = Traverse(root);  
                             }

    | expr '*' expr					 {  
                                Node* root = MakeBunch('*', $1, $3);
                                $$ = Traverse(root);  
                             }

    | expr '/' expr          { 
                  							if($3 == 0)
                  							 yyerror("0으로 나눌 수 없습니다.");
                  							else {
                  							 Node* root = MakeBunch('/', $1, $3);
                                 $$ = Traverse(root);  
                                }
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

Node* MakeBunch(char operator, double operand, double operand2) {
  Node* operatorNode = MakeNode();
  Node* operandNode = MakeNode();
  Node* operandNode2 = MakeNode();

  SetOperator(operatorNode, operator);
  SetOperand(operandNode, operand);
  SetOperand(operandNode2, operand2);

  MakeLeftSubTree(operatorNode, operandNode);
  MakeRightSubTree(operatorNode, operandNode2);
  return operatorNode;
}


int main(void)
{
   printf("?- ");
   yyparse();
   return 0;

}
