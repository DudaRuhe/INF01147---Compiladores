/*Alunas:
Maria Eduarda Nothen Ruhe - 00287686
Tatiana Pacheco de Almeida - 00252861 */
#include "tacs.h"
TAC* tacCreate(int type, HASH_NODE* res,HASH_NODE* op1,HASH_NODE* op2){
TAC* newtac = 0;
newtac = (TAC*) calloc(1,sizeof(TAC));
newtac->type = type;
newtac->res = res;
newtac->op1 = op1;
newtac->op2 = op2;
return newtac;
}
void printTAC(TAC* tac){
if(!tac) return;
if(tac->type == TAC_SYMBOL ) return;
fprintf(stderr,"TAC(");
switch(tac->type)
{
	case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
	case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
	case TAC_MULT:fprintf(stderr, "TAC_MULT"); break;
	case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
	case TAC_COPY: fprintf(stderr, "TAC_COPY"); break;
	case TAC_JF : fprintf(stderr, "TAC_JF"); break;
	case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
	case TAC_IF: fprintf(stderr, "TAC_IF"); break;
	case TAC_JMP: fprintf(stderr, "TAC_JMP"); break;
	case TAC_LESS: fprintf(stderr, "TAC_LESS"); break;
	case TAC_OR: fprintf(stderr, "TAC_OR"); break;
	case TAC_NEG: fprintf(stderr, "TAC_NEG"); break;
	case TAC_AND: fprintf(stderr, "TAC_AND"); break;
	case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
	case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
	case TAC_LE: fprintf(stderr, "TAC_LE"); break;
	case TAC_GE: fprintf(stderr, "TAC_GE"); break;
	case TAC_GREATER: fprintf(stderr, "TAC_GREATER"); break;
	case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
	case TAC_PRINTLIST: fprintf(stderr, "TAC_PRINTLIST"); break;
	case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;
	
	default: fprintf(stderr, "TAC_UNKNOWN"); break;
}
fprintf(stderr,", %s", (tac->res)?tac->res->text:"0" );
fprintf(stderr,", %s", (tac->op1)?tac->op1->text:"0" );
fprintf(stderr,", %s", (tac->op2)?tac->op2->text:"0" );
fprintf(stderr,");\n");

}
void tacPrintBackwards(TAC* tac){
if(!tac) 
return;
else{
 tacPrintBackwards(tac->prev);
 printTAC(tac);
}

}

TAC* tacJoin(TAC* l1, TAC* l2){
TAC*point;
if(!l1) return l2;
if(!l2) return l1;

for(point = l2; point->prev !=0; point = point->prev)
	;
point->prev = l1;
return l2;
}
TAC* makeIfThen(TAC* l1, TAC* l2){
TAC* jumptac = 0;
TAC* labeltac = 0;
HASH_NODE* newlabel = 0;

newlabel = makeLabel();

jumptac = tacCreate(TAC_JF, newlabel,l1?l1->res:0,0);
jumptac->prev = l1;
labeltac = tacCreate(TAC_LABEL, newlabel,0,0);
labeltac->prev = l2;
return tacJoin(jumptac,labeltac);
}

TAC* makeIfElse(TAC* l1, TAC* l2, TAC* l3){
TAC* jumptac = 0;
TAC* jumpfalse = 0;
TAC* labeltac = 0;
TAC* labeltac2 = 0;
HASH_NODE* newlabel = 0;
HASH_NODE* newlabel2 = 0;
newlabel = makeLabel();
newlabel2 = makeLabel();

jumpfalse = tacCreate(TAC_JF, newlabel,l1?l1->res:0,0);
jumpfalse->prev = l1? l1:0;
jumptac = tacCreate(TAC_JMP, newlabel2, 0,0);
jumptac->prev = l2? l2:0;
labeltac = tacCreate(TAC_LABEL, newlabel,0,0);
labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);

return tacJoin(tacJoin(tacJoin(jumpfalse,jumptac),labeltac), labeltac2);

}

TAC* makeWhile(TAC* l1, TAC* l2){
TAC* jumptac = 0;
TAC* jumpfalse = 0;
TAC* labeltac = 0;
TAC* labeltac2 = 0;
HASH_NODE* newlabel = 0;
HASH_NODE* newlabel2 = 0;
newlabel = makeLabel();
newlabel2 = makeLabel();

jumpfalse = tacCreate(TAC_JF, newlabel,l1?l1->res:0,0);
jumpfalse->prev = l1? l1:0;
jumptac = tacCreate(TAC_JMP, newlabel2, 0,0);
jumptac->prev = l2? l2:0;
labeltac = tacCreate(TAC_LABEL, newlabel,0,0);
labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
return tacJoin(tacJoin(tacJoin(labeltac2,jumpfalse), jumptac),labeltac);
}

TAC* makePrint(HASH_NODE* res, TAC* l1, TAC* l2){
TAC* symbol = 0;
if(res){
symbol = tacCreate(TAC_SYMBOL,res,0,0);
 symbol->prev = l1;
 return tacJoin( tacJoin(symbol, l2), tacCreate(TAC_PRINTLIST,makeTemp(), symbol->res, l1?l1->res:0));
}
 return tacJoin( tacJoin(l1, l2) ,tacCreate(TAC_PRINTLIST, makeTemp(), l1?l1->res:0, l2?l2->res:0));


}

TAC* generate(AST* node){
	int i;
	TAC* result = 0;
	TAC* code[MAX_SONS];

	if(!node) return 0;

	for(i=0; i< MAX_SONS; ++i)
	 code[i] = generate(node->son[i]);

	switch(node->type){
	case AST_SYMBOL: result = tacCreate(TAC_SYMBOL,node->symbol,0,0); break;
	//ARITMETICAS
	case AST_ADD: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_ADD, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_SUB: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_SUB, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_MULT: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_MULT, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_DIV: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_DIV, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_ATTR: result = tacJoin(code[1], tacCreate(TAC_COPY,node->symbol,code[1]?code[1]->res:0,0)); break;
	//BOOL
	case AST_GREATER: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_GREATER, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_LESS: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_LESS, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_OR: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_OR, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_NEG: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_NEG, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_AND: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_AND, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_EQ: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_EQ, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_DIF: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_DIF, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_LE: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_LE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_GE: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_GE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	//Fluxo
	case AST_IF: result = makeIfThen(code[0],code[1]); break;
	case AST_IFELSE: result = makeIfElse(code[0],code[1],code[2]); break;
	case AST_WHILE: result = makeWhile(code[0], code[1]); break;
	//Comandos
	//case AST_READ:  result = 
	case AST_PRINTL: result = makePrint(node->symbol?node->symbol:0, code[0]?code[0]:0, code[1]?code[1]:0); break;
	case AST_PRINT: result = tacJoin(code[0], tacCreate(TAC_PRINT,code[0]?code[0]->res:0,0,0)); break;
	case AST_RETURN: result = tacJoin(code[0], tacCreate(TAC_RETURN,code[0]?code[0]->res:0,0,0)); break;
	default: result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2],code[3])));
	break;
}

return result;
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

		default: result = tac_join(code[0],tac_join(code[1],tac_join(code[2],code[3]))); break; 

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
fprintf (fout,"  ");

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









