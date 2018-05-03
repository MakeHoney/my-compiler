project.o : lex.yy.c project.tab.c project.tab.h
	gcc -o project project.tab.c lex.yy.c -lm

lex.yy.c : project.l
	flex project.l

project.tab.c : project.y
	bison -d project.y
clean :
	rm project lex.yy.c project.tab.c project.tab.h
