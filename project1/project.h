#ifndef __PROJECT_H__
#define __PROJECT_H__

#define MAX_DBNUM	1000
#define STR_LENG	20

int yyerror(void);
void censorId(char*);
void censorStr(char*);
void censorInt(char**);
void censorSpec(char*);
void censorOper(char*);
void toUpper(char*);

char id_table[MAX_DBNUM][STR_LENG];
char int_table[MAX_DBNUM][STR_LENG];
char float_table[MAX_DBNUM][STR_LENG];
char str_table[MAX_DBNUM][STR_LENG];
char token_table[MAX_DBNUM][STR_LENG];
char print[4096];

int id_ptr = 0;
int int_ptr = 0;
int float_ptr = 0;
int str_ptr = 0;
int tok_ptr = -1;

#endif
