/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiane Pacheco 

/* Defs */
%{
    #include "tokens.h"
    #include "main.c"
    int line = 1;
%}



ONE_LINE_COMMENT "##".*\n

MULTI_LINE_COMMENT_BEGIN "/#"
MULTI_LINE_COMMENT_END "#/"

%x COMMENT	 

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

 /* INDENTIFIER */
[ \t]                           { }
"\n"                            { ++line; }

[a-zA-Z_]+[a-zA-Z_]*            { return TK_IDENTIFIER; }   // identificadores
.                               { return TOKEN_ERROR; }
[-+]?[0-9]+            	        { return LIT_INTEGER; }     // tipo literal inteiro
'[^']'                          { return LIT_CHAR; }        // tipo literal caracter
[-+]*[0-9]*+"."+[0-9]*          { return LIT_FLOAT; }       // tipo literal float
\"[^\"]*\"                      { return LIT_STRING; }      // tipo literal strig

{ONE_LINE_COMMENT}	        { }
{MULTI_LINE_COMMENT_BEGIN} 	{ BEGIN(COMMENT); }

<COMMENT>.	{ }
<COMMENT>"\n"	{ }
<COMMENT>{MULTI_LINE_COMMENT_END} { BEGIN(INITIAL); }

%%
/* c-code */

int get_line_number(void) {
    return yylineno;
}

int yywrap(void) {
	return 1;
} 
