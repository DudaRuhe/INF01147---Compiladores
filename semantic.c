/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */


#include "semantic.h"


int semanticerrors=0;

void check_and_set_declarations (AST *node)
{	
	int i=0;

	if (!node) return;  

	switch (node->type)
	{
		case AST_VAR: 
		     if (node->symbol)
			if (node->symbol->type!= SYMBOL_IDENTIFIER)
			{
			fprintf(stderr, "Semantic ERROR: Variable %s \n",node->symbol->text);
			++ semanticerrors;	
			} 
			node->symbol->type = SYMBOL_VARIABLE;
			if(node->son[0])
			  if(node->son[0]->type == AST_INT)
			  node->symbol->datatype = DATATYPE_INT;
			if(node->son[0])			
			  if(node->son[0]->type == AST_FLOAT)
			  node->symbol->datatype = DATATYPE_FLOAT;
			if(node->son[0])
			  if(node->son[0]->type == AST_CHAR)
			  node->symbol->datatype = DATATYPE_CHAR;
			break;
		case AST_FUNCAO: 
		      if (node->symbol)
			if (node->symbol->type!= SYMBOL_IDENTIFIER)
			{

			fprintf(stderr, "Semantic ERROR: Function %s \n",node->symbol->text);
			++ semanticerrors;	
			} 
			node->symbol->type = SYMBOL_FUNCTION;
			if(node->son[0])
			  if(node->son[0]->type == AST_INT)
			  node->symbol->datatype = DATATYPE_INT;
			if(node->son[0])			
			  if(node->son[0]->type == AST_FLOAT)
			  node->symbol->datatype = DATATYPE_FLOAT;
			if(node->son[0])
			  if(node->son[0]->type == AST_CHAR)
			  node->symbol->datatype = DATATYPE_CHAR; break;
		case AST_VETOR: 
			 if (node->symbol)
			if (node->symbol->type!= SYMBOL_IDENTIFIER)
			{

			fprintf(stderr, "Semantic ERROR: Vector %s \n",node->symbol->text);
			++ semanticerrors;	
			} 
			node->symbol->type = SYMBOL_VECTOR;
			if(node->son[0])
			  if(node->son[0]->type == AST_INT)
			  node->symbol->datatype = DATATYPE_INT;
			if(node->son[0])			
			  if(node->son[0]->type == AST_FLOAT)
			  node->symbol->datatype = DATATYPE_FLOAT;
			if(node->son[0])
			  if(node->son[0]->type == AST_CHAR)
			  node->symbol->datatype = DATATYPE_CHAR;
			
		break;
		case AST_FUNATR: 
		     if (node->symbol)
			if (node->symbol->type!= SYMBOL_IDENTIFIER)
			{
			fprintf(stderr, "Semantic ERROR: Function ATTR %s \n",node->symbol->text);
			++ semanticerrors;	
			} 
			node->symbol->type = SYMBOL_VARIABLE;
			if(node->son[0])
			  if(node->son[0]->type == AST_INT)
			  node->symbol->datatype = DATATYPE_INT;
			if(node->son[0])			
			  if(node->son[0]->type == AST_FLOAT)
			  node->symbol->datatype = DATATYPE_FLOAT;
			if(node->son[0])
			  if(node->son[0]->type == AST_CHAR)
			  node->symbol->datatype = DATATYPE_CHAR;
			break;
	
	}

	for (i=0; i<MAXSON; i++)
		check_and_set_declarations (node->son[i]);

			
}

void check_undeclared()
{
semanticerrors += hash_check_undeclared();
}

int is_number(AST *son)
{
	if(	(son->type == AST_ADD ||
			son->type == AST_SUB ||
			son->type == AST_MULT ||
			son->type == AST_DIV ||
			son->type == AST_GREATER ||
			son->type == AST_LESS ||
			son->type == AST_OR ||
			son->type == AST_NEG ||
			son->type == AST_AND ||
			son->type == AST_EQ ||
			son->type == AST_DIF ||
			son->type == AST_LE ||
			son->type == AST_GE ||
			(son->type == AST_SYMBOL && 
  				((son->symbol->type == SYMBOL_LIT_INTEGER) || (son->symbol->datatype == DATATYPE_INT) ) )||  
			(son->type == AST_FUN && 
				son->symbol->type == SYMBOL_FUNCTION && son->symbol->datatype == DATATYPE_INT)
			))
		return 1;
else return 0;
}

void check_commands(AST *node){
}
void check_operands(AST *node)
{
	int i;

	if (!node) return;

	switch (node->type)
	{
		case AST_ADD: 
		 if (! (is_number(node->son[0])))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Left Operands for ADD \n");
			++ semanticerrors;
		     };
		  if (! (is_number(node->son[1])))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Right Operands for ADD \n");
			++ semanticerrors;
		     }; break;
		case AST_SUB: 		break;
		case AST_MULT: 		break;
		case AST_DIV: 		break;
		case AST_GREATER: 	break;
		case AST_LESS: 		break;
		case AST_OR: 		break;
		case AST_NEG: 		break;
		case AST_AND: 		break;
		case AST_EQ: 		break;
		case AST_DIF: 		break;
		case AST_LE: 		break;
		case AST_GE: 		break;

		
	} //switch

	for (i=0; i<MAXSON; i++)
		check_operands(node->son[i]);
} // check_operands

