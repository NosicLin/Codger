#ifndef _CODGER_SYNTAX_PARSER_H_
#define _CODGER_SYNTAX_PARSER_H_
#include"ast_object.h"
void parser_set_root(AstObject* root);
AstObject* parser_get_root();
int yyparse();
#define YYDEBUG 1
#define YYTOKEN_TABLE 1
#define YYTOKENTYPE 1

#endif /*_CODGER_SYNTAX_PARSER_H_*/
