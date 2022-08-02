/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

extern FILE *yyin;
int yyparse();

int yylex(void);
int yylex_destroy(void);
void hashInit(void);
void hashPrint(void);
int getLineNumber();

int main (int argc, char **argv)
{
 int token = 0;
  if(argc < 2)
  {
    fprintf(stderr, "Call ./etapa2 file_name\n");
    exit(1);
  }

yyin = fopen(argv[1],"r");

hashInit();

yyparse();
	
hashPrint();

printf("O arquivo possui %d linhas \n", getLineNumber());

yylex_destroy();

return 0;
  
}
