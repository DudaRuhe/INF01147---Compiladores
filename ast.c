/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "tacs.h"


AST* astCreat(int type, HASH_NODE* symbol, AST* son0, AST* son1, AST* son2, AST* son3, int line){
	
	
	AST*newnode;
	newnode=(AST*) calloc (1, sizeof(AST));
	newnode->type = type;
	newnode->line = line;
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
		case AST_LCMD: fprintf(stderr, "AST_LCMD"); break;
		case AST_TAIL: fprintf(stderr, "AST_TAIL"); break;
		case AST_CMD: fprintf(stderr, "AST_CMD"); break;
		case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
		case AST_READ: fprintf(stderr, "AST_READ"); break;
		case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
		case AST_PRINTL: fprintf(stderr, "AST_PRINTL"); break;
		case AST_SYMBOLL: fprintf(stderr, "AST_SYMBOLL"); break;
		case AST_VAR: fprintf(stderr, "AST_VAR"); break;
		case AST_VETOR: fprintf(stderr, "AST_VETOR"); break;
		case AST_FUNATR: fprintf(stderr, "AST_FUNATR"); break;
		case AST_FUNCAO: fprintf(stderr, "AST_FUNCAO"); break;
		case AST_IF: fprintf(stderr, "AST_IF"); break;
		case AST_IFELSE: fprintf(stderr, "AST_IFELSE"); break;
		case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
		case AST_PARENTESES: fprintf(stderr, "AST_PARENTESES"); break;
		case AST_PROG_VAR: fprintf(stderr, "AST_PROG_VAR"); break;
		case AST_PROG_FUN: fprintf(stderr, "AST_PROG_FUN"); break;
		case AST_INT: fprintf(stderr, "AST_INT"); break;
		case AST_FLOAT: fprintf(stderr, "AST_FLOAT"); break;
		case AST_CHAR: fprintf(stderr, "AST_CHAR"); break;
		

		default: fprintf(stderr,"AST_UNKNOW"); break;
	} 
	if (node->symbol !=0)
		fprintf(stderr, ",%s\n", node->symbol->text);
	else
		fprintf(stderr, ",0\n");

	for (i=0; i<MAXSON; i++)
		ast_print(node->son[i], level +1);

}
void astToFile(AST* node, FILE *f)
{
	
	if (!node) return;

	

	switch (node->type){
		case AST_SYMBOL: 
			fprintf(f," %s ",node->symbol->text);
			break;

		case AST_ADD: 
			astToFile(node->son[0],f);
			fprintf(f, "+");
			astToFile(node->son[1],f); 
			break;

		case AST_SUB: 
			astToFile(node->son[0],f);
			fprintf(f, "-");
			astToFile(node->son[1],f); 
			break; 

		case AST_MULT:
			astToFile(node->son[0],f);
			fprintf(f, ".");
			astToFile(node->son[1],f); 
			break;

		case AST_DIV: 
			astToFile(node->son[0],f);
			fprintf(f, "/");
			astToFile(node->son[1],f); 
			break;

		case AST_ATTR: 
			fprintf(f, "%s",node->symbol->text);
			if(node->son[1]!=0){
				fprintf(f,"[");
				astToFile(node->son[1],f);
				fprintf(f,"]");
			}
			fprintf(f, " <-");
			astToFile(node->son[0],f);
			break; 

		case AST_VECTOR: 
			fprintf(f," %s[",node->symbol->text);
			astToFile(node->son[0],f);
			fprintf(f,"]"); 
			break;

		case AST_GREATER: 
			astToFile(node->son[0],f);
			fprintf(f, ">");
			astToFile(node->son[1],f); 
			break;

		case AST_LESS: 
			astToFile(node->son[0],f);
			fprintf(f, "<");
			astToFile(node->son[1],f); 
			break;

		case AST_OR: 
			astToFile(node->son[0],f);
			fprintf(f, "|");
			astToFile(node->son[1],f); 
			break;

		case AST_NEG: 
			astToFile(node->son[0],f);
			fprintf(f, "~");
			astToFile(node->son[1],f); 
			break;

		case AST_AND: 
			astToFile(node->son[0],f);
			fprintf(f, "&");
			astToFile(node->son[1],f); 
			break;

		case AST_EQ: 
			astToFile(node->son[0],f);
			fprintf(f, "==");
			astToFile(node->son[1],f); 
			break;

		case AST_DIF:
			astToFile(node->son[0],f);
			fprintf(f, "!=");
			astToFile(node->son[1],f); 
			break;

		case AST_LE: 
			astToFile(node->son[0],f);
			fprintf(f, "<=");
			astToFile(node->son[1],f); 
			break;

		case AST_GE:
			astToFile(node->son[0],f);
			fprintf(f, ">=");
			astToFile(node->son[1],f); 
			break;

		case AST_FUN: 
			fprintf(f," %s(",node->symbol->text);
			astToFile(node->son[0],f);
			fprintf(f, ")");
			break;

		case AST_ARG: 
			astToFile(node->son[0],f);
			astToFile(node->son[1],f);
			break;

		case AST_LCMD: 
			astToFile(node->son[0],f);
			astToFile(node->son[1],f);
			break;

		case AST_TAIL:
			fprintf(f, ";\n");
			astToFile(node->son[0],f);
			astToFile(node->son[1],f);
			break;

		case AST_CMD: 
			fprintf(f, "{\n"); 
			astToFile(node->son[0],f);
			fprintf(f, "}\n");
			break;
			
		case AST_RETURN: 
			fprintf(f, "return");
			astToFile(node->son[0],f); 
			break;

		case AST_READ: 
			fprintf(f, "read");
			fprintf(f," %s",node->symbol->text);
			if(node->son[0] != 0){
				fprintf(f,"[");
				astToFile(node->son[0],f);
				fprintf(f,"]");	
			}
			break;

		case AST_PRINT: 
			fprintf(f, "print");
			astToFile(node->son[0],f);  
			break;

		case AST_PRINTL: 
			if(node->symbol !=0)
				fprintf(f," %s",node->symbol->text);
			astToFile(node->son[0],f); 
			astToFile(node->son[1],f); 
			break;
		case AST_SYMBOLL: 
			astToFile(node->son[0],f); 
			astToFile(node->son[1],f); 
			break;

		case AST_VAR: 	
			astToFile(node->son[0], f);
			fprintf(f," %s (",node->symbol->text);
			astToFile(node->son[1],f);
			fprintf(f,");\n");
			break;

		case AST_VETOR: 
			astToFile(node->son[0], f);
			fprintf(f," %s[",node->symbol->text);
			astToFile(node->son[1],f);
			fprintf(f,"]");
			astToFile(node->son[2],f);
			fprintf(f,";\n");
			break;

		case AST_FUNATR: 
			astToFile(node->son[1], f);
			fprintf(f," %s ",node->symbol->text);
			astToFile(node->son[0], f);
			break;

		case AST_FUNCAO:
			 astToFile(node->son[0], f);
			 fprintf(f," %s(",node->symbol->text);
			 astToFile(node->son[1], f);
			 fprintf(f,")");
			 astToFile(node->son[2], f);
			 break;

		case AST_IF: 
			fprintf(f, "if("); 
			astToFile(node->son[0], f);
			fprintf(f,")\n");
			astToFile(node->son[1], f);
			break;

		case AST_IFELSE: 
			fprintf(f, "if("); 
			astToFile(node->son[0], f);
			fprintf(f,")\n");
			astToFile(node->son[1], f);
			fprintf(f,"else\n");
			astToFile(node->son[2], f);
			break;

		case AST_WHILE:
			fprintf(f, "while("); 
			astToFile(node->son[0], f);
			fprintf(f,")\n");
			astToFile(node->son[1], f);
			break;

		case AST_PARENTESES: 
			fprintf(f, "(");
			 astToFile(node->son[0], f);
			fprintf(f, ")"); 
			break;

		case AST_PROG_VAR: 
		case AST_PROG_FUN:
			for (int i=0; i<MAXSON; i++)
				astToFile(node->son[i],f);
			break;
		case AST_INT: fprintf(f, "int"); break;
		case AST_FLOAT: fprintf(f, "float"); break;
		case AST_CHAR: fprintf(f, "char"); break;

		default: break;
	} 

}
