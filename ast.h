/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef AST_HEADER
#define AST_HEADER

#define MAXSON 4
#define AST_SYMBOL 1
#define AST_ADD 2 
#define AST_IF 3
#define AST_MULT 5
#define AST_DIV 6
#define AST_ATTR 7
#define AST_SUB 8
#define AST_VECTOR 9
#define AST_GREATER 10
#define AST_LESS 11
#define AST_OR 12
#define AST_NEG 13
#define AST_AND 14
#define AST_EQ 15
#define AST_DIF 16
#define AST_LE 17
#define AST_GE 18
#define AST_FUN 19
#define AST_ARG 20
#define AST_CMD 21
#define AST_LCMD 22
#define AST_TAIL 23
#define AST_RETURN 24
#define AST_READ 25
#define AST_PRINT 26
#define AST_PRINTL 27
#define AST_SYMBOLL 28
#define AST_VAR 29
#define AST_VETOR 30
#define AST_FUNATR 31
#define AST_FUNCAO 32
#define AST_IFELSE 33
#define AST_WHILE 34
#define AST_PARENTESES 35
#define AST_PROG_VAR 36
#define AST_PROG_FUN 37
#define AST_INT 38
#define AST_FLOAT 39
#define AST_CHAR 40

typedef struct ast_node
{
	int type;
	int line;
	struct ast_node *son[MAXSON];
	HASH_NODE *symbol;
} AST;

AST *astCreat(int type, HASH_NODE *symbol, AST* son0, AST* son1, AST* son2, AST* son3, int line);
void ast_print(AST* node, int level);
void astToFile(AST* node, FILE *f);



int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text,int type);
void hashPrint(void);

#endif




