etapa_1: lex.yy.o main.o
	gcc -o etapa1 lex.yy.o main.o

main.o: main.c
	gcc -c main.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex scanner.l

clean:
	rm -f *.o lex.yy.c lex.yy.h etapa1 ./output/*