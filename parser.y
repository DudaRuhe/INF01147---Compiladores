/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

/* Defs */

%{
#include "hash.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror (char const *s);
extern int yylineno;
%}

%union
{

   HASH_NODE *symbol;
   AST *ast;
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

%token<symbol> TK_IDENTIFIER     

%token<symbol> LIT_INTEGER    
%token<symbol> LIT_FLOAT        
%token<symbol> LIT_CHAR          
%token<symbol> LIT_STRING        
%token TOKEN_ERROR


%type<ast> expressao
%type<ast> command_atribuicao
%type<ast> argumentos
%type<ast> bloco
%type<ast> bloco_list
%type<ast> comando
%type<ast> command_return
%type<ast> command_read
%type<ast> command_print
%type<ast> fluxo
%type<ast> lista_print

%type<ast> variaveis
%type<ast> variaveis_list
%type<ast> variaveis_globais
%type<ast> vetor

%type<ast> funcao
%type<ast> funcao_entrada

%type<ast> programa
%type<ast> begin

// remover conflitos
//precedência de baixo para cima
%left '&' '|'
%left OPERATOR_EQ OPERATOR_DIF OPERATOR_LE OPERATOR_GE  '<' '>'
%left '+' '-'  
%left '.' '/'  
%left '~'

%%

begin: programa {ast_print($1,0);}
;

programa: variaveis_globais programa  {$$ = astCreat(AST_PROG_VAR,0,$1,$2,0,0); }
	| funcao programa 	      {$$ = astCreat(AST_PROG_FUN,0,$1,$2,0,0); }
	| 			      {$$ = 0;}	
	;


/* Variaveis Globais */

variaveis: LIT_INTEGER {$$ = astCreat(AST_SYMBOL,$1,0,0,0,0); }
	| LIT_CHAR     {$$ = astCreat(AST_SYMBOL,$1,0,0,0,0); }
	| LIT_FLOAT    {$$ = astCreat(AST_SYMBOL,$1,0,0,0,0); }
	;

tipos_primitivos: KW_CHAR
	| KW_INT  
	| KW_FLOAT
	;

variaveis_list: variaveis variaveis_list {$$ = astCreat(AST_SYMBOLL,0,$1,$2,0,0); }
	| 				 { $$ = 0; }
	;

vetor: TK_IDENTIFIER'['LIT_INTEGER']' variaveis_list {$$ = astCreat(AST_VETOR,$1,$5,0,0,0); }
	;

variaveis_globais: tipos_primitivos TK_IDENTIFIER '('variaveis')' ';' {$$ = astCreat(AST_VAR,$2,$4,0,0,0); }
	| tipos_primitivos vetor ';' {$$ = $2;} 
	;

/* Comandos Simples */

comando:  command_print  	{$$ = $1; }
	 | command_read 	{$$ = $1; }
	 | command_return 	{$$ = $1; }
	 | command_atribuicao	{$$ = $1; }
	 | bloco 		{$$ = $1; }
	 | fluxo 		{$$ = $1; } 
	 | ';' 			{$$ = 0;} 
      	 ;

lista_print: LIT_STRING lista_print { $$ = astCreat(AST_PRINTL,$1,$2,0,0,0); } 
	| expressao lista_print { $$ = astCreat(AST_PRINTL,0,$1,$2,0,0); } 
	|			{ $$ = 0; }
	;
	
command_print: KW_PRINT lista_print { $$ = astCreat(AST_PRINT,0,$2,0,0,0); }
	;

command_read: KW_READ TK_IDENTIFIER { $$ = astCreat(AST_READ,$2,0,0,0,0); } 
	| KW_READ TK_IDENTIFIER'['expressao']' { $$ = astCreat(AST_READ,$2,$4,0,0,0); ast_print($4,0);} 
	;

command_return: KW_RETURN expressao { $$ = astCreat(AST_RETURN,0,$2,0,0,0);} 
	;

command_atribuicao: TK_IDENTIFIER'['expressao']' ASSIGNMENT expressao { $$ = astCreat(AST_ATTR,$1,$3,$6,0,0);} 
	| TK_IDENTIFIER ASSIGNMENT expressao { $$ = astCreat(AST_ATTR,$1,$3,0,0,0);}   		
	;

/* Funções */

funcao_entrada: tipos_primitivos TK_IDENTIFIER funcao_entrada { $$ = astCreat(AST_FUNATR,$2,$3,0,0,0);}
	|						{ $$ = 0; }
	;

funcao: tipos_primitivos TK_IDENTIFIER '(' funcao_entrada ')'  bloco { $$ = astCreat(AST_FUNCAO,$2,$4,$6,0,0); }
	;
/* Blocos de Comando */

bloco: '{'bloco_list'}' { $$ = astCreat(AST_CMD,0,$2,0,0,0);  }
	;

bloco_list: comando bloco_list  { $$ = astCreat(AST_LCMD,0,$1,$2,0,0);  }
            | 		        { $$ = 0; }
	; 
	
/* Controle de Fluxo */

fluxo:  KW_IF '(' expressao ')' comando			{ $$ = astCreat(AST_IF,0,$3,$5,0,0);  }
	| KW_IF '(' expressao ')' comando KW_ELSE comando  { $$ = astCreat(AST_IFELSE,0,$3,$5,0,0);  }
	| KW_WHILE '(' expressao ')' comando		{ $$ = astCreat(AST_WHILE,0,$3,$5,0,0);  }



/* Expressoes Aritmeticas*/
  
expressao: TK_IDENTIFIER		{$$ = astCreat(AST_SYMBOL,$1,0,0,0,0); }
    | TK_IDENTIFIER '[' expressao ']'   {$$ = astCreat(AST_VECTOR,$1,$3,0,0,0); }
    | LIT_INTEGER 			{$$ = astCreat(AST_SYMBOL,$1,0,0,0,0); }		
    | LIT_CHAR 				{$$ = astCreat(AST_SYMBOL,$1,0,0,0,0); }
    | expressao '+' expressao		{$$ = astCreat(AST_ADD,0,$1,$3,0,0); }
    | expressao '-' expressao		{$$ = astCreat(AST_SUB,0,$1,$3,0,0); }
    | expressao '.' expressao		{$$ = astCreat(AST_MULT,0,$1,$3,0,0); }
    | expressao '/' expressao		{$$ = astCreat(AST_DIV,0,$1,$3,0,0); }
    | expressao '>' expressao		{$$ = astCreat(AST_GREATER,0,$1,$3,0,0); }
    | expressao '<' expressao		{$$ = astCreat(AST_LESS,0,$1,$3,0,0); }
    | expressao '|' expressao		{$$ = astCreat(AST_OR,0,$1,$3,0,0); }
    | expressao '~' expressao		{$$ = astCreat(AST_NEG,0,$1,$3,0,0); }
    | expressao '&' expressao		{$$ = astCreat(AST_AND,0,$1,$3,0,0); }
    | expressao OPERATOR_EQ expressao   {$$ = astCreat(AST_EQ,0,$1,$3,0,0); } // ==
    | expressao OPERATOR_DIF expressao  {$$ = astCreat(AST_DIF,0,$1,$3,0,0); } // =!
    | expressao OPERATOR_LE expressao   {$$ = astCreat(AST_LE,0,$1,$3,0,0); } // <=
    | expressao OPERATOR_GE expressao   {$$ = astCreat(AST_GE,0,$1,$3,0,0); } // >=
    | '(' expressao ')'        		{$$ = astCreat(AST_PARENTESES,0,$2,0,0,0);}         
    | TK_IDENTIFIER '(' argumentos')'	{$$ = astCreat(AST_FUN,$1,$3,0,0,0); }		
    ;

argumentos: expressao argumentos  {$$ = astCreat(AST_ARG,0,$1,$2,0,0); }
	|			  {$$ = 0;}
    ;



%%                  
//c-code

void yyerror (char const *s)
{
    printf("[Line %d] %s\n", yylineno, s);
    exit(3);
}
