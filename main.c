/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

extern FILE *yyin;
int yyparse();

int yylex(void);
int yylex_destroy(void);
void hashInit(void);
void hashPrint(void);
int getLineNumber();

void astToFile(AST* node, FILE *f, int level);
AST* getAST(void);

int main (int argc, char **argv)
{
 FILE *outputFile;
 int token = 0;
  if(argc < 2)
  {
    fprintf(stderr, "Call ./etapa3 file_name\n");
    exit(1);
  }

yyin = fopen(argv[1],"r");
  if((outputFile = fopen(argv[2], "w")) == 0)
 {
   fprintf(stderr, "Cannot open file %s\n", argv[2]);
   exit(4);
 }
hashInit();

yyparse();
	
hashPrint();

printf("O arquivo possui %d linhas \n", getLineNumber());
astToFile(getAST(), outputFile, 0);
yylex_destroy();

return 0;
  
}
