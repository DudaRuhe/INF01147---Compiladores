
/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

/* Defs */

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror (char const *s);
extern int yylineno;
%}

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

%token LIT_INTEGER      
%token LIT_FLOAT        
%token LIT_CHAR          
%token LIT_STRING        
%token TOKEN_ERROR


%left '+' '-'  // remover conflitos
%left '*' '/'  // remover conflitos

%%

programa:  variaveis_globais programa |
	comando programa | 
	funcao programa |
	
	;

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
//Comandos Simples

expressao:  LIT_INTEGER |
	'(' LIT_INTEGER '+' TK_IDENTIFIER ')'
	;
comando: command_print |
	command_read |
	command_return |
	command_atribuicao
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
	TK_IDENTIFIER ASSIGNMENT expressao
	;

//Funções

funcao_entrada: tipos_primitivos TK_IDENTIFIER funcao_entrada |
	;

funcao: tipos_primitivos TK_IDENTIFIER '(' funcao_entrada ')' '{' bloco '}'
	;

bloco: comando';' bloco|
	;

%%                  //c-code

void yyerror (char const *s)
{
    printf("[Line %d] %s\n", yylineno, s);
    exit(3);
}
 
