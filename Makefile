# Maria Eduarda Nothen Ruhe - 00287686
# Tatiana Pacheco de Almeida - 00252861

etapa3: main.o lex.yy.o y.tab.o hash.o
	gcc main.o lex.yy.o y.tab.o hash.o -o etapa3

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	 yacc -d parser.y
		
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa3 lex.yy.c y.tab.c *.o
