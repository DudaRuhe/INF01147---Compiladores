/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiane Pacheco 

/* Defs */
%{
    #include "tokens.h"
    #include "main.c"
    int line = 1;
%}



%%
 /* Reserved words */
"char"		 { return KW_CHAR; }
"int"            { return KW_INT; }
"float"          { return KW_FLOAT; }
"if"             { return KW_IF; }
"else"           { return KW_ELSE; }
"while"          { return KW_WHILE; }
"read"		 { return KW_READ; }
"print"		 { return KW_PRINT; }
"return" 	 { return KW_RETURN; }

    /* Special characters */

";"         { return ';'; }
"("	    { return '('; }
")"	    { return ')'; }
"["         { return '['; }
"]"         { return ']'; }
"{"         { return '{'; }
"}"         { return '}'; }
"+"         { return '+'; }
"-"         { return '-'; }
"."         { return '.'; }
"/"         { return '/'; }
"<"         { return '<'; }
">"         { return '>'; }
"&"         { return '&'; }
"|"         { return '|'; }
"~"	    { return '~'; }

 /* Complex operators */

"<-"	    { return ASSIGNMENT; }
"<="        { return OPERATOR_LE; }
">="        { return OPERATOR_GE; }
"=="        { return OPERATOR_EQ; }
"!="        { return OPERATOR_DIF; }




%%
/* c-code */

int get_line_number(void) {
    return yylineno;
}

int yywrap(void) {
	return 1;
} 