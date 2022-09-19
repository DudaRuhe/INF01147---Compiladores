/* Maria Eduarda Nothen Ruhe - 00287686
   Tatiana Pacheco de Almeida - 00252861 */



#include "tacs.h"
#include "hash.h"


TAC* tac_create(int type, HASH_NODE* res, HASH_NODE* operando1, HASH_NODE* operando2)
{
	TAC* newtac =0;
	newtac = (TAC*) calloc(1,sizeof(TAC));
	newtac->type = type;
	newtac->res = res;
	newtac->operando1 = operando1;
	newtac->operando2 = operando2;
	newtac->prev = 0;
	newtac->next = 0;
	return newtac;
}

void print_tac (TAC* tac)
{
if (!tac) return;
if (tac->type == TAC_SYMBOL) return;
fprintf(stderr, "TAC(");

	switch(tac->type)
	{
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
		case TAC_COPY: fprintf(stderr, "TAC_COPY"); break;
		case TAC_JFALSE: fprintf(stderr, "TAC_JFALSE"); break;
		case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
		case TAC_MULT: fprintf(stderr, "TAC_MULT"); break;
		case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
		case TAC_EQ: fprintf(stderr, "EQ"); break;
		case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
		case TAC_LE: fprintf(stderr, "TAC_LE"); break;
		case TAC_GE: fprintf(stderr, "TAC_GE"); break;
		default: fprintf(stderr, "TAC_UNKNOWN"); break;		
	} // switch

fprintf(stderr, "%s", (tac->res)?tac->res->text:"");
fprintf(stderr, "%s", (tac->operando1)?tac->operando1->text:"");
fprintf(stderr, "%s", (tac->operando2)?tac->operando2->text:"");
fprintf(stderr, ");\n");	


}

void print_tac_back (TAC* tac)
{
TAC* node;
for (node=tac; node; node = node->prev)
     print_tac(node);	

}


TAC* tac_join(TAC* l1, TAC* l2)
{

	TAC* point;

	if (!l1) return l2;
	if (!l2) return l1;
	for(point = l2; point->prev != 0 ; point = point->prev);
	point->prev = l1;
	return l2;
}

// Geração de Codigo 

TAC* generate_code( AST *node)
{
	int i;
	TAC *result = 0;
	TAC *code[MAX_SONS];

	if(!node) return 0;

	for (i=0; i<MAX_SONS; ++i)
		code[i] = generate_code(node->son[i]);

	switch (node->type)
	{

		case AST_SYMBOL: result = tac_create(TAC_SYMBOL,node->symbol,0,0); break;
		case AST_ADD: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_ADD, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;
		case AST_ATTR: result = tac_join(code[0],tac_create(TAC_COPY,node->symbol,code[0]?code[0]->res:0,0));
		case AST_SUB: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_SUB, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;
		case AST_DIV: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_DIV, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;
		case AST_MULT: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_MULT, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;
		case AST_EQ: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_EQ, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;
		case AST_LE: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_LE, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;
		case AST_GE: result = tac_join(tac_join(code[0],code[1]), 
		     tac_create(TAC_GE, make_temp(), code[0]?code[0]->res, code[1]?code[1]->res)); break;

		default: result = tac_join(code[0],tac_join(code[1],tac_join(code[2],code[3]))); break; //default está ok

	}//switch

return result;
	
} // generate_code

TAC* make_if_then(TAC* code0, TAC* code1)
{
	TAC * jumptac = 0;
	TAC * labeltac = 0;
	HASH_NODE * newlabel = 0;
	newlabel = make_label();
	jumptac = tac_create(TAC_JFALSE,0,code0?code0->res,0);
	jumptac->prev = code0;
	labeltac = tac_create(TAC_LABEL, newlabel,0,0);
	labetac->prev = code1;
	return tac_join(jumptac, label);
}

// Geração do ASM

TAC* tac_reverse(TAC* tac)
{
TAC* t = tac;
for (t = tac;t->prev; t = t->prev)
     t->prev->next = t;
return t;	
}

void generate_asm(TAC* first)
{
FILE *fout;
fout = fopen ("out.s","w");

// Inicialização
fprintf (fout," xxxxxxxx ");

// TAC

for (tac=first; tac; tac = tac->next)
{
	switch (tac->type)
	{
	case TAC_BEGINFUN: fprintf (fout,"## TAC_BEGINFUN \n"
	"\t .globl	main \n"
	".type	main, @function \n"
	" main: \n"
	".LFB0: \n"
	"\t pushq	%rbp \n"
	"\t movq	%rsp, %rbp \n",tac->res->text,tac->res->text); 
	break;

	case TAC_ENDFUN: fprintf (fout,"## TAC_ENDFUN	\n"
	"\t popq	%rbp \n"
	"\t ret\n"); 
	break;

	case TAC_PRINT:fprintf (fout,"## TAC_PRINT\n"	
	"\t leaq	.LC0(%rip), %rdi \n"
	"\t movl	$0, %eax \n"
	"\t call	printf@PLT \n"
	"\t movl	$0, %eax \n", tac->operando1->text); 
	break;
	} 
} 


// Hash 

print_ams(fout);



fclose;

}



