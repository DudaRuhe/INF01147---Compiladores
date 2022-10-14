/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MULT 4
#define TAC_DIV 5
#define TAC_COPY 6
#define TAC_IF 7
#define TAC_JF 8
#define TAC_LABEL 9
#define TAC_JMP 10
#define TAC_LESS 11
#define TAC_OR 12
#define TAC_NEG 13
#define TAC_AND 14
#define TAC_EQ 15
#define TAC_DIF 16
#define TAC_LE 17
#define TAC_GE 18
#define TAC_GREATER 19
#define  MAX_SONS 4
typedef struct tac_node
{
	int type;
	HASH_NODE* res;
	HASH_NODE* op1;
	HASH_NODE* op2;	
	struct tac_node* prev;
	struct tac_node* next;
}TAC;

TAC* tacCreate(int type, HASH_NODE* res,HASH_NODE* op1,HASH_NODE* op2);
void printTAC(TAC* tac);
void tacPrintBackwards(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);
TAC* generate(AST* node);
TAC* makeIfThen(TAC* l1, TAC* l2);
TAC* makeIfElse(TAC* l1, TAC* l2, TAC* l3);
TAC* makeWhile(TAC* l1, TAC* l2);
#endif
