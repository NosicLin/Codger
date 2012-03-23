#ifndef _REDY_SYNTAX_YYLEX_H_
#define _REDY_SYNTAX_YYLEX_H_
#include<lexical/scanner.h>
void yl_set_scanner(struct scanner* sc);
struct scanner* yl_get_scanner();
char* yl_cur_string();
void  yyerror(char* error);

/* used for parser */
int yylex();

#endif 

