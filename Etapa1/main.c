
#include <stdio.h>
#include "tokens.h"

int yylex(void);
int yylex_destroy(void);

int main (int argc, char **argv)
{
  int token = 0;
  if(argc < 2)
{
  fprintf(stderr, "Call ./a.out file_name\n");
  exit(1);
}

yyin = fopen(argv[1],"r");

  while (token = yylex()) {
    switch (token){
		case ';':
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case '+':
		case '-':
		case '.':
		case '/':
		case '<':
		case '>':
		case '&':
		case '|':
		case '~': printf("Caracter especial: %d\n", token); break;
		case KW_CHAR: printf("KW_CHAR: %d\n",token); break;
		case KW_INT: printf("KW_INT: %d\n",token); break;
		case KW_FLOAT: printf("KW_FLOAT: %d\n",token); break;
		case KW_IF: printf("KW_IF: %d\n",token); break;
		case KW_ELSE: printf("KW_ELSE: %d\n",token); break;
		case KW_WHILE: printf("KW_WHILE: %d\n",token); break;
		case KW_READ: printf("KW_READ: %d\n",token); break;
		case KW_PRINT: printf("KW_PRINT: %d\n",token); break;
		case KW_RETURN: printf("KW_RETURN: %d\n",token); break;
		case ASSIGNMENT: printf("ASSIGNMENT: %d\n",token); break;
		case OPERATOR_LE: printf("OPERATOR_LE: %d\n",token); break;
		case OPERATOR_GE: printf("OPERATOR_GE: %d\n",token); break;
		case OPERATOR_EQ: printf("OPERATOR_EQ: %d\n",token); break;
		case OPERATOR_DIF: printf("OPERATOR_DIF: %d\n",token); break;
		case TK_IDENTIFIER: printf ("TK_IDENTIFIER: %d \n", token); break;
		case TOKEN_ERROR: printf ("TOKEN_ERROR: %d \n", token); break;
        	case LIT_INTEGER: printf ("LIT_INTEGER: %d \n", token); break;
		case LIT_CHAR: printf ("LIT_CHAR: %d \n", token); break;
		case LIT_FLOAT: printf ("LIT_FLOAT: %d \n", token); break;
		case LIT_STRING: printf ("LIT_STRING: %d \n", token); break;
		default: printf ("Invalid Token %d \n", token); return 1; break;
	}
  }
	

yylex_destroy();
return 0;
  
}

