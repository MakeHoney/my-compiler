#ifndef __GRAMMAR_H__
#define __GRAMMAR_H__

#define MAX_DBNUM	1000
#define MAX_PARTH	100
#define STR_LENG	20

extern char token_table[][STR_LENG];
extern char id_table[][STR_LENG];
extern char int_table[][STR_LENG];
extern char float_table[][STR_LENG];
extern int tok_ptr;
extern char print[4096];

void initialize();
void XML();
void E();
void EP();
void T();
void TP();
void F();

#endif
