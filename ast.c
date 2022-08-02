/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"


AST* astCreat(int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3){
	
	
	AST*newnode;
	newnode=(AST*) calloc (1, sizeof(AST));
	newnode->type = type;
	newnode->symbol =symbol;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;
	return newnode;

}

void ast_print(AST* node, int level){

	int i=0;
	if (!node) return;

	for (i=0; i<level; i++)
	fprintf(stderr, "  ");

	fprintf(stderr, "AST(");

	switch (node->type){
		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
		case AST_ADD: fprintf(stderr, "AST_ADD"); break;
		case AST_SUB: fprintf(stderr, "AST_SUB"); break;
		case AST_MULT: fprintf(stderr, "AST_MULT"); break;
		case AST_DIV: fprintf(stderr, "AST_DIV"); break;
		case AST_ATTR: fprintf(stderr, "AST_ATTR"); break;
		case AST_VECTOR: fprintf(stderr, "AST_VECTOR"); break;
		case AST_GREATER: fprintf(stderr, "AST_GREATER"); break;
		case AST_LESS: fprintf(stderr, "AST_LESS"); break;
		case AST_OR: fprintf(stderr, "AST_OR"); break;
		case AST_NEG: fprintf(stderr, "AST_NEG"); break;
		case AST_AND: fprintf(stderr, "AST_AND"); break;
		case AST_EQ: fprintf(stderr, "AST_EQ"); break;
		case AST_DIF: fprintf(stderr, "AST_DIF"); break;
		case AST_LE: fprintf(stderr, "AST_LE"); break;
		case AST_GE: fprintf(stderr, "AST_GE"); break;
		case AST_FUN: fprintf(stderr, "AST_FUN"); break;
		case AST_ARG: fprintf(stderr, "AST_ARG"); break;

		default: fprintf(stderr,"AST_UNKNOW"); break;
	} 
	if (node->symbol !=0)
		fprintf(stderr, ",%s\n", node->symbol->text);
	else
		fprintf(stderr, ",0\n");

	for (i=0; i<MAXSON; i++)
		ast_print(node->son[i], level +1);

}
