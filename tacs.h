/* Maria Eduarda Nothen Ruhe - 00287686
   Tatiana Pacheco de Almeida - 00252861 */


#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"
#include "hash.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MULT 4
#define TAC_DIV 5
#define TAC_EQ 6
#define TAC_DIF 7
#define TAC_LE 8
#define TAC_GE 9
#define TAC_COPY 10 // é  a move
#define TAC_JFALSE 11 //é o IF zero
#define TAC_LABEL 12


#define TAC_BEGINFUN 13
#define TAC_ENDFUN 14
#define TAC_JUMP 15
#define TAC_CALL 16
#define TAC_ARG 17
#define TAC_RETURN 18
#define TAC_PRINT 19
#define TAC_READ 20
#define TAC_WRITE 21


// falta




typedef struct tac_node {

	int type;
	HASH_NODE *res;
	HASH_NODE *operando1;
	HASH_NODE *operando2;
	struct tac_node* prev;
	struct tac_node* next;
	

} TAC;

TAC* tac_create(int type, HASH_NODE* res, HASH_NODE* operando1, HASH_NODE* operando2);

void print_tac(TAC* tac);

void print_tac_back(TAC* tac);

TAC* tac_join(TAC* l1, TAC*l2);

TAC* generate_code(AST *node); // Geração de Codigo 

TAC* make_if_then(TAC* code0, TAC* code1);


#endif
