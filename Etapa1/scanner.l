/* Defs */

%%
/* Regras */

%%
/* c-code */

int get_line_number(void) {
    return yylineno;
}

int yywrap(void) {
	return 1;
} 