/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

/* Defs */

%{
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror (char const *s);
extern int yylineno;
%}

%union
{
   int value;
   HASH_NODE *symbol;
}

%error-verbose

%token KW_CHAR           
%token KW_INT            
%token KW_FLOAT          

%token KW_IF            
%token KW_ELSE          
%token KW_WHILE        
%token KW_READ          
%token KW_PRINT        
%token KW_RETURN         

%token ASSIGNMENT        
%token OPERATOR_LE      
%token OPERATOR_GE      
%token OPERATOR_EQ      
%token OPERATOR_DIF     

%token TK_IDENTIFIER     

%token<value> LIT_INTEGER    
%token<value> LIT_FLOAT        
%token<value> LIT_CHAR          
%token LIT_STRING        
%token TOKEN_ERROR

%type<value> expressao
// remover conflitos
//precedência de baixo para cima
%left '&' '|'
%left OPERATOR_EQ OPERATOR_DIF OPERATOR_LE OPERATOR_GE  '<' '>'
%left '+' '-'  
%left '.' '/'  
%left '~'

%%

programa: variaveis_globais programa |
	funcao programa |
	;

/* Variaveis Globais */

variaveis: LIT_INTEGER |
	LIT_CHAR |
	LIT_FLOAT 
	;

tipos_primitivos: KW_CHAR |
	KW_INT | 
	KW_FLOAT
	;

variaveis_list: variaveis variaveis_list| 
	;

vetor: TK_IDENTIFIER'['LIT_INTEGER']' variaveis_list 
	;

variaveis_globais: tipos_primitivos TK_IDENTIFIER '('variaveis')' ';' |
	tipos_primitivos vetor ';' 
	;

/* Comandos Simples */

comando: command_print |
	 command_read |
	 command_return |
	 command_atribuicao |  
	 bloco |
	 fluxo | 
	';' 	 
      	 ;

lista_print: LIT_STRING lista_print |
	 expressao lista_print |
	;
	
command_print: KW_PRINT lista_print
	;

command_read: KW_READ TK_IDENTIFIER|
	KW_READ TK_IDENTIFIER'['expressao']'
	;

command_return: KW_RETURN expressao
	;

command_atribuicao: TK_IDENTIFIER'['expressao']' ASSIGNMENT expressao |
	TK_IDENTIFIER ASSIGNMENT expressao  			{fprintf(stderr, "Expre vale %d\n", $3);}
	;

/* Funções */

funcao_entrada: tipos_primitivos TK_IDENTIFIER funcao_entrada |
	;

funcao: tipos_primitivos TK_IDENTIFIER '(' funcao_entrada ')'  bloco 
	;
/* Blocos de Comando */

bloco: '{'bloco_list'}' 
	;

bloco_list: comando bloco_list |            
	; 
	
/* Controle de Fluxo */

fluxo:  KW_IF '(' expressao ')' comando
	| KW_IF '(' expressao ')' comando KW_ELSE comando
	| KW_WHILE '(' expressao ')' comando



/* Expressoes Aritmeticas*/
  
expressao: TK_IDENTIFIER		{$$ = 0;}
    | TK_IDENTIFIER '[' expressao ']'   {$$ = 0;}
    | LIT_INTEGER 			{fprintf(stderr, "Recebi %d\n",$1);}
    | LIT_CHAR 				{$$ = 0;}
    | expressao '+' expressao		{$$ = $1 + $3;}
    | expressao '-' expressao		{$$ = $1 - $3;}
    | expressao '.' expressao		{$$ = $1 * $3;}
    | expressao '/' expressao		{$$ = $1 / $3;}
    | expressao '>' expressao		
    | expressao '<' expressao		
    | expressao '|' expressao		
    | expressao '~' expressao		
    | expressao '&' expressao		
    | expressao OPERATOR_EQ expressao    // ==
    | expressao OPERATOR_DIF expressao   // =!
    | expressao OPERATOR_LE expressao    // <=
    | expressao OPERATOR_GE expressao    // >=
    | '(' expressao ')'                 {$$ = $2;}
    | chama_funcao			{$$ = 0;}
    ;

chama_funcao: TK_IDENTIFIER '(' argumentos ')'
    ;

argumentos: expressao argumentos |
    ;



%%                  
//c-code

void yyerror (char const *s)
{
    printf("[Line %d] %s\n", yylineno, s);
    exit(3);
}
