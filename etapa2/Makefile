# Maria Eduarda Nothen Ruhe - 00287686
# Tatiana Pacheco de Almeida - 00252861
etapa2: lex.yy.c y.tab.c
	gcc lex.yy.c -o etapa2  
		
lex.yy.c: scanner.l
	lex scanner.l

y.tab.c: parser.y
	 yacc -d parser.y

clean:
	rm etapa2 lex.yy.c y.tab.h y.tab.c
