/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER


#include "ast.h"
#include "hash.h"

extern int semanticerrors;

void check_and_set_declarations (AST *node);

void check_undeclared();

void check_operands();

int is_number(AST *node, int datatype);

void check_commands(AST *node);

int get_semantic_erros(); // falta testar na main com exit(4)
 
#endif



