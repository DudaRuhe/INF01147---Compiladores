/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 997
#define SYMBOL_IDENTIFIER 1
#define SYMBOL_CHAR 2
#define SYMBOL_INT 3
#define SYMBOL_FLOAT 4
#define SYMBOL_IF 5
#define SYMBOL_ELSE 6
#define SYMBOL_WHILE 7
#define SYMBOL_READ 8
#define SYMBOL_PRINT 9
#define SYMBOL_RETURN 10
#define SYMBOL_ASSIGNMENT  11
#define SYMBOL_OPERATOR_LE 12
#define SYMBOL_OPERATOR_GE 13
#define SYMBOL_OPERATOR_EQ 14
#define SYMBOL_OPERATOR_DIF 15
#define SYMBOL_LIT_INTEGER 16
#define SYMBOL_LIT_FLOAT 17
#define SYMBOL_LIT_CHAR 18
#define SYMBOL_LIT_STRING 19 
#define SYMBOL_TOKEN_ERROR 20
#define SYMBOL_VARIABLE 21
#define SYMBOL_FUNCTION 22
#define SYMBOL_VECTOR 23

#define DATATYPE_INT 1
#define DATATYPE_CHAR 2
#define DATATYPE_FLOAT 3
      

typedef struct hash_node
{
	int type;
	int datatype;
	char *text;
	struct hash_node * next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text,int type);
void hashPrint(void);
int hash_check_undeclared(void);

#endif


