# Maria Eduarda Nothen Ruhe - 00287686
# Tatiana Pacheco de Almeida - 00252861

etapa5: main.o lex.yy.o y.tab.o hash.o ast.o semantic.o
	gcc main.o lex.yy.o y.tab.o hash.o ast.c semantic.o -o etapa5

main.o: main.c
	gcc -c main.c

semantic.o: semantic.c
	gcc -c semantic.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	 yacc -d parser.y
		
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa5 lex.yy.c y.tab.c *.o
