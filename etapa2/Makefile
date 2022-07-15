# Maria Eduarda Nothen Ruhe - 00287686
# Tatiana Pacheco de Almeida - 00252861
etapa2: lex.yy.c
	gcc lex.yy.c -o etapa2

y.tab.c: parser.y
	 yacc -d parser.y 
		
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa2 lex.yy.c y.tab.c
