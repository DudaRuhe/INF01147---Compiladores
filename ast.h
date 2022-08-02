/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#ifndef AST_HEADER
#define AST_HEADER

#define MAXSONS 4
#define AST_SYMBOL 1
#define AST_ADD 2 
#define AST_IF 3

typedef struct ast_node
{
	int type;
	struct ast_node *son[MAXSONS];
	HASH_NODE *symbol;
} AST;

AST *ast_create(int type, hash_node *symbol, AST* son0, AST* son1, AST* son2, AST* son3);
void ast_print(AST* node);




int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text,int type);
void hashPrint(void);

#endif




