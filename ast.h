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
#define  AST_SUB 4

typedef struct ast_node
{
	int type;
	struct ast_node *son[MAXSON];
	HASH_NODE *symbol;
} AST;

AST *ast_create(int type, HASH_NODE *symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void ast_print(AST* node, int level);




int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text,int type);
void hashPrint(void);

#endif




