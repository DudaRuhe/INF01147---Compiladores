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

// remover conflitos
//precedência de baixo para cima
%left '&' '|'
%left OPERATOR_EQ OPERATOR_DIF OPERATOR_LE OPERATOR_GE  '<' '>'
%left '+' '-'  
%left '*' '/'  
%left '~'

%%

programa: variaveis_globais programa |
	comando programa| 
	funcao programa |
        expressao programa |
        fluxo programa |
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

bloco: comando';' bloco |  // bloco de comandos
	;
	
//controle de fluxo
fluxo: TK_IDENTIFIER '=' expressao
	| TK_IDENTIFIER '[' expressao ']' '=' expressao
        | KW_IF '(' expressao ')' bloco
	| KW_IF '(' expressao ')' bloco KW_ELSE bloco
	| KW_WHILE '(' expressao ')' bloco



/* Expressoes Aritmeticas*/
  
expressao: TK_IDENTIFIER
    | TK_IDENTIFIER '[' expressao ']' 
    | LIT_INTEGER 
    | LIT_CHAR 
    | expressao '+' expressao
    | expressao '-' expressao
    | expressao '.' expressao
    | expressao '*' expressao
    | expressao '/' expressao
    | expressao '>' expressao
    | expressao '<' expressao
    | expressao '|' expressao
    | expressao '~' expressao
    | expressao '&' expressao
    | expressao OPERATOR_EQ expressao    // ==
    | expressao OPERATOR_DIF expressao   // =!
    | expressao OPERATOR_LE expressao    // <=
    | expressao OPERATOR_GE expressao    // >=
    | '(' expressao ')'
    | chama_funcao
    ;

chama_funcao: TK_IDENTIFIER '(' argumentos ')'
    ;

argumentos: expressao lista
    ;

lista: ',' argumentos
    |
    ;

%%                  
//c-code

void yyerror (char const *s)
{
    printf("[Line %d] %s\n", yylineno, s);
    exit(3);
}
 
