#ifndef _CODGER_SYNTAX_YYLEX_H_
#define _CODGER_SYNTAX_YYLEX_H_
#include<lexical/scanner.h>
void yl_set_scanner(struct scanner* sc);
struct scanner* yl_get_scanner();
char* yl_cur_string();
void  yyerror(char* error);

void yl_ignore_newline();
void yl_restore_newline();

/* used for parser */
int yylex();

#endif 

