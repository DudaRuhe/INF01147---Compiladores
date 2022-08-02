/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"


AST* ast_create (int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3){
	
	
	AST*newnode;//newnode=(AST*) calloc (1, sizeof(AST));
	newnode->type = type;
	newnode->symbol =symbol;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;
	return newnode;

}

void ast_print(AST* node, int level){

	int i;
	if (!node) return;

	for (i=0; i<level; i++)
	fprintf(stderr, " ");

	fprintf(stderr, "AST(");

	switch (node->type){
		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
		case AST_ADD: fprintf(stderr, "AST_ADD"); break;
		case AST_SUB: fprintf(stderr, "AST_SUB"); break;

		default: fprintf(stderr,"AST_UNKNOW"); break;
	} 
	if (node->symbol !=0)
		fprintf(stderr, ",%s", node->symbol->text);
	else
		fprintf(stderr, ",0");

	for (i=0; i<MAXSON; i++)
	ast_print(node->son[i], level +1);
	

}
