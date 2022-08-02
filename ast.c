/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include <stdio.h>
#include <ast.h>
#include <hash.h>

AST* ast_create (int type, hash_node* symbol, AST* son0, AST* son1, AST* son2, AST* son3){
	
	newnode=(AST*) calloc (1, sizeof(AST));
	newnode->type=type;
	newnode->symbol=symbol;
	newnode->son[0]=son0;
	newnode->son[1]=son1;
	newnode->son[2]=son2;
	newnode->son[3]=son3;
	return newnode;

}

void ast_print(AST* node, int level){

	int i;
	if (!node) return;

	for (i=0; i<level; i++)
	fprint (stderr, " ");

	fprint (stderr, "AST(");

	switch (node->type){
		case *AST symbol: fprint (stderr, " "); break;
		default: fprint ("UNKNOW"); 
	} 

	for (i=0; i<MAXSON; i++)
	ast_print(node->[1], level +1);

}
