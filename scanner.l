/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */


/* Defs */
%{
   #include "hash.h"
   #include "ast.h"
   #include "y.tab.h"
  
	
    int line = 1;
    int running =1;
%}

%option yylineno

ONE_LINE_COMMENT "##".*\n

MULTI_LINE_COMMENT_BEGIN "/#"
MULTI_LINE_COMMENT_END "#/"

%x COMMENT	 

%%


"char"		 { return KW_CHAR; } // Reserved words
"int"            { return KW_INT; }
"float"          { return KW_FLOAT; }
"if"             { return KW_IF; }
"else"           { return KW_ELSE; }
"while"          { return KW_WHILE; }
"read"		 { return KW_READ; }
"print"          { return KW_PRINT; }
"return"         { return KW_RETURN; }

 
";"         { return yytext[0]; } //Special characters
"("	    { return yytext[0]; }
")"	    { return yytext[0]; }
"["         { return yytext[0]; }
"]"         { return yytext[0]; }
"{"         { return yytext[0]; }
"}"         { return yytext[0]; }
"+"         { return yytext[0]; }
"-"         { return yytext[0]; }
"."         { return yytext[0]; }
"/"         { return yytext[0]; }
"<"         { return yytext[0]; }
">"         { return yytext[0]; }
"&"         { return yytext[0]; }
"|"         { return yytext[0]; }
"~"	    { return yytext[0]; }


"<-"	    { return ASSIGNMENT; } // Complex operators 
"<="        { return OPERATOR_LE; }
">="        { return OPERATOR_GE; }
"=="        { return OPERATOR_EQ; }
"!="        { return OPERATOR_DIF; }



[ \t]+                          { }
\n                              { line++; }


[a-zA-Z_]+[a-zA-Z_]*            { yylval.symbol = hashInsert(yytext, SYMBOL_IDENTIFIER); return TK_IDENTIFIER ; }   // Identifier  
[0-9]+            	        { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_INTEGER); return LIT_INTEGER; }  //Literals   
'[^']'                          { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_CHAR); return LIT_CHAR; }        
[-+]*[0-9]*+","+[0-9]*          { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_FLOAT); return LIT_FLOAT; }       
\"(\\.|[^\\"])*\"               { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_STRING); return LIT_STRING; }      



{ONE_LINE_COMMENT}	            { } // Comment
{MULTI_LINE_COMMENT_BEGIN} 	{ BEGIN(COMMENT); }

<COMMENT>.	{ }
<COMMENT>"\n"	{ }
<COMMENT>{MULTI_LINE_COMMENT_END} { BEGIN(INITIAL); }

.                               { return TOKEN_ERROR; }   // Error

%%



int getLineNumber(void) {            // c-code
    if(line!=1)
      yylineno--;
     return yylineno;
}



int isRunning(void){
    return running;
}

void initMe(void){
 hashInit();
}

int yywrap(void) {
	running = 0;
	return 1;
} 
