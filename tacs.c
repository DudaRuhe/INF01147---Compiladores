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
jumpfalse->prev = l1;
jumptac = tacCreate(TAC_JMP, newlabel2, 0,0);
jumptac->prev = l2? l2:0;
labeltac = tacCreate(TAC_LABEL, newlabel,0,0);
labeltac->next = l3;
labeltac2 = tacCreate(TAC_LABEL, newlabel2, 0,0);
labeltac2->prev = l3;
return tacJoin(tacJoin(tacJoin(jumpfalse,jumptac),labeltac), labeltac2);

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
	case AST_ADD: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_ADD, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_SUB: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_SUB, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_MULT: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_MULT, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_DIV: result = tacJoin( tacJoin(code[0], code[1]) ,tacCreate(TAC_DIV, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
	case AST_ATTR: result = tacJoin(code[1], tacCreate(TAC_COPY,node->symbol,code[1]?code[1]->res:0,0)); break;
	
	case AST_IF: result = makeIfThen(code[0],code[1]); break;
	case AST_IFELSE: fprintf(stderr, "entrou\n"); result = makeIfElse(code[0],code[1],code[2]); break;
	default: result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2],code[3])));
	break;
}

return result;
}








