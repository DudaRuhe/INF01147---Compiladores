/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include "hash.h"

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

typedef struct ast_node
{
	int type;
	struct ast_node *son[MAXSON];
	HASH_NODE *symbol;
} AST;

AST *astCreat(int type, HASH_NODE *symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void ast_print(AST* node, int level);




int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text,int type);
void hashPrint(void);

#endif




