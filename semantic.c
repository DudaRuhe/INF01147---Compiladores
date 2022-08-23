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

int is_number(AST *son, int datatype)
{

if( datatype == DATATYPE_INT || datatype == DATATYPE_CHAR) {
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
  				((son->symbol->type == SYMBOL_LIT_INTEGER) || (son->symbol->type == SYMBOL_LIT_CHAR) || (son->symbol->datatype == DATATYPE_INT && son->symbol->type == SYMBOL_VARIABLE) ) )||  
			(son->type == AST_FUN && 
				son->symbol->type == SYMBOL_FUNCTION && son->symbol->datatype == DATATYPE_INT) ||
		(son->type == AST_VECTOR && 
				son->symbol->datatype == DATATYPE_INT && son->symbol->type == SYMBOL_VECTOR && is_number(son->son[0],0) )
			))
		return 1;
else return 0;
}

if( datatype == DATATYPE_FLOAT){
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
  				((son->symbol->type == SYMBOL_LIT_INTEGER) || (son->symbol->type == SYMBOL_LIT_CHAR) || (son->symbol->datatype == DATATYPE_INT && son->symbol->type == SYMBOL_VARIABLE) ) )||  
			(son->type == AST_FUN && 
				son->symbol->type == SYMBOL_FUNCTION && son->symbol->datatype == DATATYPE_INT) ||
		(son->type == AST_VECTOR && 
				son->symbol->datatype == DATATYPE_INT && son->symbol->type == SYMBOL_VECTOR && is_number(son->son[0],0) )
			))
		return 1;
else return 0;
}
}
void 
void check_commands(AST *node){
	int i;
	if (!node) return;

	switch (node->type)
	{
		case AST_READ: //vetores e atributos certos
			 break;
		case AST_RETURN: // tipo mesmo de função
			break;
		
		case AST_ATTR:
			if(node->son[0]!=0){
				if(node->symbol->type == SYMBOL_VECTOR)
					check_operands(node->son[0],DATATYPE_INT);
				else{
			
			  		fprintf(stderr, "Semantic ERROR: Not vector \n");
			  		++ semanticerrors;
					}
			}
			else{ if(node->symbol->type == SYMBOL_VECTOR) {
				fprintf(stderr, "Semantic ERROR: Vector whithout [] \n");
			  		++ semanticerrors;
				}
			}
			
			check_operands(node->son[1],node->symbol->datatype);	
			break;
		
	}
for (i=0; i<MAXSON; i++)
		check_commands(node->son[i]);

}
void check_operands(AST *node, int datatype)
{
	int i;

	if (!node) return;

	switch (node->type)
	{
		case AST_ADD: 
		if (datatype ==  DATATYPE_BOOL){
		  if(!(is_number(node->son[0], DATATYPE_INT) && is_number(node->son[1], DATATYPE_INT))
 && !(is_number(node->son[0], DATATYPE_FLOAT) && is_number(node->son[1], DATATYPE_FLOAT)))
		{
			fprintf(stderr, "Semantic ERROR: Invalid Operands  \n");
			++ semanticerrors;
		}
			
		}
		 else{
		 if (! (is_number(node->son[0], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Left Operands for ADD \n");
			++ semanticerrors;
		     };
		  if (! (is_number(node->son[1], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Right Operands for ADD \n");
			++ semanticerrors;
		     };
		} break;
		case AST_SUB: 
		if (datatype ==  DATATYPE_BOOL){
		  	  if(!(is_number(node->son[0], DATATYPE_INT) && is_number(node->son[1], DATATYPE_INT))
 && !(is_number(node->son[0], DATATYPE_FLOAT) && is_number(node->son[1], DATATYPE_FLOAT)))
		{
			fprintf(stderr, "Semantic ERROR: Invalid Operands \n");
			++ semanticerrors;
		}
			
		}
		 else{		
			if (! (is_number(node->son[0], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Left Operands for SUB \n");
			++ semanticerrors;
		     };
		  if (! (is_number(node->son[1], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Right Operands for SUB \n");
			++ semanticerrors;
		     };
			} break;
		case AST_MULT: 
			if (datatype ==  DATATYPE_BOOL){
		  	  if(!(is_number(node->son[0], DATATYPE_INT) && is_number(node->son[1], DATATYPE_INT))
 && !(is_number(node->son[0], DATATYPE_FLOAT) && is_number(node->son[1], DATATYPE_FLOAT)))
		{
			fprintf(stderr, "Semantic ERROR: Invalid Operands  \n");
			++ semanticerrors;
		}
			
		}
		 else{		
			if (! (is_number(node->son[0], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Left Operands for MULT \n");
			++ semanticerrors;
		     };
		  if (! (is_number(node->son[1], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Right Operands for MULT \n");
			++ semanticerrors;
		     }
		} break;
		case AST_DIV: 	
		if (datatype ==  DATATYPE_BOOL){
	 	  	 if(!(is_number(node->son[0], DATATYPE_INT) && is_number(node->son[1], DATATYPE_INT))
 && !(is_number(node->son[0], DATATYPE_FLOAT) && is_number(node->son[1], DATATYPE_FLOAT)))
		{
			fprintf(stderr, "Semantic ERROR: Operands\n");
			++ semanticerrors;
		}
			
		}
		 else{	
			if (! (is_number(node->son[0], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Left Operands for DIV \n");
			++ semanticerrors;
		     };
		  if (! (is_number(node->son[1], datatype)))
		     {
			fprintf(stderr, "Semantic ERROR: Invalid Right Operands for DIV \n");
			++ semanticerrors;
		     }
		} break;
		case AST_GREATER: 
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_LESS: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_OR: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_NEG: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_AND: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_EQ: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_DIF: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_LE: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_GE: 		
			if(datatype == DATATYPE_INT || datatype == DATATYPE_CHAR || datatype == DATATYPE_FLOAT)
				fprintf(stderr, " Type does not accept bool\n");	break;
		case AST_SYMBOL:  	
				break; 
		case AST_VECTOR:
				break;
		
	} //switch

	for (i=0; i<MAXSON; i++)
		check_operands(node->son[i], datatype);
} // check_operands

int get_semantic_erros(){
 return semanticerrors;
}

