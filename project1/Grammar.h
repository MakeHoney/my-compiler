#ifndef __GRAMMAR_H__
#define __GRAMMAR_H__

#define MAX_DBNUM	1000
#define STR_LENG	20

extern char token_table[][STR_LENG];
extern int tok_ptr;

void XML();
void E();
void EP();
void T();
void TP();
void F();

#endif
